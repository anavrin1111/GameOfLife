#pragma once

#include "Cell.h"
#include <vector>

constexpr auto SquareLength = 16.0f;

class Rules {

private:
	int rows;
	int columns;
	float widthPixels;
	float heightPixels;
	float squareLengthSize;

	std::vector<std::vector<CELL*>> newGrid;

	// Calculates how many rows and columns based on the size 
	// of the window client.
	int CalculateRows();
	int CalculateColumns();

	// Creates both grids.
	void CreateGrid();

	// Clean up and deletes each cell.
	void DestroyGrid();

	// Used to initialise cells alive or dead.
	bool GetRandomBool();

	// Methods to check what position the current grid is in.

	inline bool isTopLeftCorner(int, int);

	inline bool isTopRightCorner(int, int);

	inline bool isTopRow(int, int);

	inline bool isBottomLeftCorner(int, int);

	inline bool isBottomRightCorner(int, int);

	inline bool isBottomRow(int, int);

	inline bool isLeftMostColumn(int, int);

	inline bool isRightMostColumn(int, int);

	inline bool isNormalCell(int, int);


	// These methods sum the neighbours depending on
	// grid position.

	int TopLeftCorner(int, int);

	int TopRightCorner(int, int);

	int TopRow(int, int);

	int BottomLeftCorner(int, int);

	int BottomRightCorner(int, int);

	int BottomRow(int, int);

	int LeftMostColumn(int, int);

	int RightMostColumn(int, int);

	int NormalCell(int , int);


	// Calculates whether cell should be alive or 
	bool CalculateIsAlive(int, int, int);

	// Swaps the newly calculated grid for the current 
	// grid to draw
	void SwapGrid();

public:
	std::vector<std::vector<CELL*>> grid;

	Rules() : rows(0), columns(0), widthPixels(0.0f), heightPixels(0.0f), squareLengthSize(16.0f) {}

	Rules(float width, float height) {
		widthPixels = width;
		heightPixels = height;
		squareLengthSize = SquareLength;
		rows = CalculateRows();
		columns = CalculateColumns();
		CreateGrid();
	};

	~Rules() {
		DestroyGrid();
	};

	// Recalculates grid on every new generation.
	void ReCalculateGrid();

	// Public api.
	void Update();
};