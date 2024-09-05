#include "Graphics.h"
#include "Rules.h"
#include "HighPerfTimer.h"
#include <vector>

//Implementation file of the Graphics class.

// Safely release com resources.
template<class Interface> inline void SafeRelease(Interface** ppInterfaceToRelease)
{
    if (*ppInterfaceToRelease != NULL)
    {
        (*ppInterfaceToRelease)->Release();
        (*ppInterfaceToRelease) = NULL;
    }
}

Graphics::Graphics(){
}

Graphics::~Graphics()
{
    DiscardGraphicsResources();
    DestroyObjects();
}

void Graphics::Initialise() {

    HRESULT hr;

    hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pFactory);

    hr = CreateGraphicsResources();

    D2D1_SIZE_F rtSize = pRenderTarget->GetSize();

    rule = new Rules(rtSize.width, rtSize.height);
}

void Graphics::onPaint()
{
    HRESULT hr;

    pRenderTarget->BeginDraw();

    std::vector<std::vector<CELL*>> gridOfCells = rule->grid;

    for (int i = 0; i < gridOfCells.size(); i++) {
        for (int j = 0; j < gridOfCells[i].size(); j++) {
            D2D1_RECT_F square = D2D1::RectF(gridOfCells[i][j]->left, gridOfCells[i][j]->top, gridOfCells[i][j]->right, gridOfCells[i][j]->bottom);
            
            if (gridOfCells[i][j]->isAlive) {
                pRenderTarget->FillRectangle(&square, pDarkGrayBrush);
                pRenderTarget->DrawRectangle(&square, pWhiteBrush, 1.0f);
            }
            else {
                pRenderTarget->FillRectangle(&square, pBlackBrush);
                pRenderTarget->DrawRectangle(&square, pWhiteBrush, 1.0f);
            }
        }
    }

    hr = pRenderTarget->EndDraw();

    if (FAILED(hr) || hr == D2DERR_RECREATE_TARGET)
    {
        DiscardGraphicsResources();
    }
}

void Graphics::update()
{
    rule->Update();
}

HRESULT Graphics::CreateGraphicsResources()
{
    HRESULT hr = S_OK;

        if (pRenderTarget == NULL)
        {
            RECT rc;
            GetClientRect(m_hwnd, &rc);

            D2D1_SIZE_U size = D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top);

            hr = pFactory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(),D2D1::HwndRenderTargetProperties(m_hwnd, size), &pRenderTarget);

            // This is where brushes etc are created.
            if (SUCCEEDED(hr))
            {
                hr = pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &pBlackBrush);
            }

            if (SUCCEEDED(hr))
            {
                hr = pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::LightGray), &pLightGrayBrush);
            }

            if (SUCCEEDED(hr))
            {
                hr = pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::DarkGray), &pDarkGrayBrush);
            }

            if (SUCCEEDED(hr))
            {
                hr = pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White), &pWhiteBrush);
            }
        }
        return hr;
}

void Graphics::DiscardGraphicsResources()
{
    SafeRelease(&pFactory);
    SafeRelease(&pRenderTarget);
    SafeRelease(&pBlackBrush);
    SafeRelease(&pLightGrayBrush);
    SafeRelease(&pDarkGrayBrush);
    SafeRelease(&pWhiteBrush);
}

void Graphics::DestroyObjects()
{
    delete rule;
}

LRESULT Graphics::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_DESTROY:
    {
        PostQuitMessage(0);
        return 0;
    }

    case WM_CREATE:
    {
        return 0;
    }

    case WM_PAINT:
    {
        onPaint();
        if (timer.timeElapsed())
        {
            update();
        }
        return 0;
    }

    default:
        return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
    }
    return TRUE;
}