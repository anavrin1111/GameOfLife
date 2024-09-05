# Conway's Game of Life

## Description

The game of life is a cellular automation zero player game devised by John Conway in 1970.
Each cell is governed by the following rules which dictate the cells survival in the next 
generation.

1. Any live cell with fewer than two live neighbours dies, as if by underpopulation.
2. Any live cell with two or three live neighbours lives on to the next generation.
3. Any live cell with more than three live neighbours dies, as if by overpopulation.
4. Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.

More information can be found [here](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life).

## Usage

In Visual Studio, add d2d1.lib to the following. Ensure all configurations is selected.

```
Project -> <Project Name> properties -> Linker -> Input -> Additional Dependencies
```

Then build the solution or select `Debug -> Start Without -> Debugging`.

## About

This is my first project teaching myself C++ and Windows DirectX. There are improvements to be 
made in the structure of the application and the code quality which will be taken in future projects.