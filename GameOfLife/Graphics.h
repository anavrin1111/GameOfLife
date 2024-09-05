#pragma once
#include <windows.h>
#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>
#include "BaseWin.h"
#include "Rules.h"
#include "HighPerfTimer.h"


class Graphics : public BaseWindow<Graphics> {

private:
	ID2D1Factory* pFactory = NULL;
	ID2D1HwndRenderTarget* pRenderTarget = NULL;
	ID2D1SolidColorBrush* pBlackBrush = NULL;
	ID2D1SolidColorBrush* pLightGrayBrush = NULL;
	ID2D1SolidColorBrush* pDarkGrayBrush = NULL;
	ID2D1SolidColorBrush* pWhiteBrush = NULL;
	Rules* rule;
	HighPerfTimer timer;

public:
	Graphics();

	~Graphics();

	void Initialise();

	PCWSTR  ClassName() const { return L"Game Of Life"; }

	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

	HRESULT CreateGraphicsResources();

	void DiscardGraphicsResources();

	void onPaint();

	void update();

	void DestroyObjects();
};