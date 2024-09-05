// Implementation file of the Rules class
#include "Rules.h"
#include <cstdlib>
#include <ctime>

int Rules::CalculateRows() {

	int heightPixelsInt = static_cast<int>(heightPixels);

	int squareLengthSizeInt = static_cast<int>(squareLengthSize);

	return heightPixelsInt / squareLengthSizeInt;
}

int Rules::CalculateColumns() {

	int widthPixelsInt = static_cast<int>(widthPixels);

	int squareLengthSizeInt = static_cast<int>(squareLengthSize);

	return widthPixelsInt / squareLengthSizeInt;
}

void Rules::CreateGrid() {

	float left = 0.0f;
	float top = 0.0f;
	float right = squareLengthSize;
	float bottom = squareLengthSize;

	srand((unsigned)time(NULL));

	for (int i = 0; i < rows; i++) {
		grid.push_back(std::vector<CELL*>(0));
		newGrid.push_back(std::vector<CELL*>(0));
		for (int j = 0; j < columns; j++) {

			grid[i].push_back(new CELL{left, top, right, bottom, GetRandomBool()});
			newGrid[i].push_back(new CELL{ left, top, right, bottom, false });
			left += squareLengthSize;
			right += squareLengthSize;
		}
		left = 0.0f;
		right = squareLengthSize;
		top += squareLengthSize;
		bottom += squareLengthSize;
	}
}

void Rules::DestroyGrid() {

	for (int i = 0; i < grid.size(); i++) {
		for (int j = 0; j < grid[i].size(); j++) {
			delete grid[i][j];
		}
	}

	for (int i = 0; i < newGrid.size(); i++) {
		for (int j = 0; j < newGrid[i].size(); j++) {
			delete newGrid[i][j];
		}
	}
}

bool Rules::GetRandomBool() {
	return static_cast<bool>(rand() % 2);
}

int Rules::NormalCell(int i, int j) {

	int sum = 0;

	sum += static_cast<int>(grid[i - 1][j]->isAlive); // Cell directly above

	sum += static_cast<int>(grid[i - 1][j + 1]->isAlive); // Cell top right

	sum += static_cast<int>(grid[i][j + 1]->isAlive); // Cell to the right

	sum += static_cast<int>(grid[i + 1][j + 1]->isAlive); // Cell bottom right

	sum += static_cast<int>(grid[i + 1][j]->isAlive); // Cell directly below

	sum += static_cast<int>(grid[i + 1][j - 1]->isAlive); // Cell bottom left

	sum += static_cast<int>(grid[i][j - 1]->isAlive); // Cell to the left

	sum += static_cast<int>(grid[i - 1][j - 1]->isAlive); // Cell top left

	return sum;
}

int Rules::TopLeftCorner(int i, int j) {

	int sum = 0;

	sum += static_cast<int>(grid[i][j + 1]->isAlive); // Cell to the right

	sum += static_cast<int>(grid[i + 1][j + 1]->isAlive); // Cell to the bottom right

	sum += static_cast<int>(grid[i + 1][j]->isAlive); // Cell directly below

	return sum;
}

int Rules::TopRightCorner(int i, int j) {

	int sum = 0;

	sum += static_cast<int>(grid[i][j - 1]->isAlive); // Cell to the left 

	sum += static_cast<int>(grid[i + 1][j - 1]->isAlive); // Cell to the bottom left

	sum += static_cast<int>(grid[i + 1][j]->isAlive); // Cell directly below

	return sum;
}

int Rules::TopRow(int i, int j) {

	int sum = 0;

	sum += static_cast<int>(grid[i][j + 1]->isAlive); // Cell to the right 

	sum += static_cast<int>(grid[i + 1][j + 1]->isAlive); // Cell to the bottom right

	sum += static_cast<int>(grid[i + 1][j]->isAlive); // Cell directly below

	sum += static_cast<int>(grid[i + 1][j - 1]->isAlive); // Cell to the bottom left

	sum += static_cast<int>(grid[i][j - 1]->isAlive); // Cell to the left

	return sum;
}

int Rules::LeftMostColumn(int i, int j) {

	int sum = 0;

	sum += static_cast<int>(grid[i - 1][j]->isAlive); // Cell directly above 

	sum += static_cast<int>(grid[i - 1][j + 1]->isAlive); // Cell top right

	sum += static_cast<int>(grid[i][j + 1]->isAlive); // Cell to the right

	sum += static_cast<int>(grid[i + 1][j + 1]->isAlive); // Cell to the bottom right

	sum += static_cast<int>(grid[i + 1][j]->isAlive); // Cell directly below

	return sum;
}

int Rules::RightMostColumn(int i, int j) {

	int sum = 0;

	sum += static_cast<int>(grid[i - 1][j]->isAlive); // Cell directly above 

	sum += static_cast<int>(grid[i - 1][j - 1]->isAlive); // Cell top left

	sum += static_cast<int>(grid[i][j - 1]->isAlive); // Cell to the left

	sum += static_cast<int>(grid[i + 1][j - 1]->isAlive); // Cell bottom left

	sum += static_cast<int>(grid[i + 1][j]->isAlive); // Cell directly below

	return sum;
}

int Rules::BottomLeftCorner(int i, int j) {

	int sum = 0;

	sum += static_cast<int>(grid[i - 1][j]->isAlive); // Cell directly above

	sum += static_cast<int>(grid[i - 1][j + 1]->isAlive); // Cell top right

	sum += static_cast<int>(grid[i][j + 1]->isAlive); // Cell to the right

	return sum;
}

int Rules::BottomRightCorner(int i, int j) {

	int sum = 0;

	sum += static_cast<int>(grid[i - 1][j]->isAlive); // Cell directly above 

	sum += static_cast<int>(grid[i - 1][j - 1]->isAlive); // Cell top left

	sum += static_cast<int>(grid[i][j - 1]->isAlive); // Cell to the left

	return sum;
}

int Rules::BottomRow(int i, int j) {

	int sum = 0;

	sum += static_cast<int>(grid[i - 1][j]->isAlive); // Cell directly above 

	sum += static_cast<int>(grid[i - 1][j + 1]->isAlive); // Cell top right

	sum += static_cast<int>(grid[i][j + 1]->isAlive); // Cell to the right

	sum += static_cast<int>(grid[i][j - 1]->isAlive); // Cell to the left

	sum += static_cast<int>(grid[i - 1][j - 1]->isAlive); // Cell top left

	return sum;
}

bool Rules::isTopLeftCorner(int i, int j)
{
	return i == 0 && j == 0;
}

bool Rules::isTopRightCorner(int i, int j)
{
	return i == 0 && j == grid[i].size() - 1;
}

bool Rules::isTopRow(int i, int j)
{
	return i == 0 && j != 0 && j != grid[i].size() - 1;
}

bool Rules::isBottomLeftCorner(int i, int j)
{
	return i == grid.size() - 1 && j == 0;
}

bool Rules::isBottomRightCorner(int i, int j)
{
	return i == grid.size() - 1 && j == grid[i].size() - 1;
}

bool Rules::isBottomRow(int i, int j)
{
	return i == grid.size() - 1 && j != 0 && j != grid[i].size() - 1;
}

bool Rules::isLeftMostColumn(int i, int j)
{
	return j == 0 && i > 0 && i < grid.size() - 1;
}

bool Rules::isRightMostColumn(int i, int j)
{
	return j == grid[i].size() - 1 && i > 0 && i < grid.size() - 1;
}

bool Rules::isNormalCell(int i, int j)
{
	return (i > 0 && i < grid.size() - 1) && (j > 0 && j < grid[i].size() - 1);
}


bool Rules::CalculateIsAlive(int n, int i, int j) {

	if (grid[i][j]->isAlive) {
		
		if (n < 2) {
			return false;
		}
		else if (n == 2 || n == 3) {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		if (n == 3) {
			return true;
		}
	}

	return false;
}

void Rules::ReCalculateGrid() {

	for (int i = 0; i < grid.size(); i++) {
		for (int j = 0; j < grid[i].size(); j++) {

			if (isNormalCell(i, j))
			{
				int neighbourSum = NormalCell(i, j);
				bool NextGenAlive = CalculateIsAlive(neighbourSum, i, j);
				newGrid[i][j]->isAlive = NextGenAlive;
			}
			else if (isLeftMostColumn(i, j))
			{
				int neighbourSum = LeftMostColumn(i, j);
				bool NextGenAlive = CalculateIsAlive(neighbourSum, i, j);
				newGrid[i][j]->isAlive = NextGenAlive;
			}
			else if (isRightMostColumn(i, j))
			{
				int neighbourSum = RightMostColumn(i, j);
				bool NextGenAlive = CalculateIsAlive(neighbourSum, i, j);
				newGrid[i][j]->isAlive = NextGenAlive;
			}
			else if (isTopLeftCorner(i, j))
			{
				int neighbourSum = TopLeftCorner(i, j);
				bool NextGenAlive = CalculateIsAlive(neighbourSum, i, j);
				newGrid[i][j]->isAlive = NextGenAlive;
			}
			else if (isTopRightCorner(i, j))
			{
				int neighbourSum = TopRightCorner(i, j);
				bool NextGenAlive = CalculateIsAlive(neighbourSum, i, j);
				newGrid[i][j]->isAlive = NextGenAlive;
			}
			else if (isTopRow(i, j))
			{
				int neighbourSum = TopRow(i, j);
				bool NextGenAlive = CalculateIsAlive(neighbourSum, i, j);
				newGrid[i][j]->isAlive = NextGenAlive;
			}
			else if (isBottomLeftCorner(i, j))
			{
				int neighbourSum = BottomLeftCorner(i, j);
				bool NextGenAlive = CalculateIsAlive(neighbourSum, i, j);
				newGrid[i][j]->isAlive = NextGenAlive;
			}
			else if (isBottomRightCorner(i, j))
			{
				int neighbourSum = BottomRightCorner(i, j);
				bool NextGenAlive = CalculateIsAlive(neighbourSum, i, j);
				newGrid[i][j]->isAlive = NextGenAlive;
			}
			else if (isBottomRow(i, j))
			{
				int neighbourSum = BottomRow(i, j);
				bool NextGenAlive = CalculateIsAlive(neighbourSum, i, j);
				newGrid[i][j]->isAlive = NextGenAlive;
			}
			else
			{
				throw;
			}
		}
	}
}

void Rules::SwapGrid() {

	std::vector<std::vector<CELL*>> temp;

	temp = grid;

	grid = newGrid;

	newGrid = temp;
}

void Rules::Update() {

	ReCalculateGrid();
	SwapGrid();
}