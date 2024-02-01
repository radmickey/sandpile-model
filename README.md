## Sand pile model

## Introduction 

[Sand Heap Model](https://en.wikipedia.org/wiki/Abelian_sandpile_model), a console application that allows you to save your states into a BMP image. 

The initial state and grid size are specified.

The grid size can be changed during the process

Implementation, a console application that supports the following command line arguments:

  **-l, --length** - grid length (guaranteed to fit in uint16_t)
  
  **-w, --width** - grid width (guaranteed to fit into uint16_t)
  
  **-i, --input** - tsv-file with initial data
  
  **-o, --output** - path to the directory for saving pictures
  
  **-m, --max-iter** - maximum number of model iterations
  
  **-f, --freq** - frequency at which the pictures should be saved (if 0, only the last state is saved).
  
The order of arguments does not matter


## Initial state

The initial state is specified by the grid sizes passed as program arguments and a file with the initial number of grains of sand in each cell, except for empty ones.

File format:
Each line contains information about one cell, in the form of (x-coordinates, y-coordinates, number of grains of sand) separated by a tab character. The number of grains of sand is guaranteed to fit in uint64_t. 

## Notes on the model

1. New grains of sand are added only during initialization.

2. The state of the trace generation of a cell depends only on the previous state of the mesh

3. If grains of sand fall over the grid, the size of the grid is increased by 1 in the corresponding direction.

## Program result

The program recalculates the state of the model, according to the initial data, and also saves intermediate states with a specified frequency into a picture in bmp format.

The picture for the current state is formed according to the following rules:

1. The size of the picture is equal to the size of the field

2. Each pixel corresponds to a cell of the field

3. The color of a pixel depends on the number of grains of sand in the cell: 0 - white, 1 - green, 2 - purple, 3 - yellow, > 3 - black.

The program terminates if the model has reached a stable state or the iteration number set initially.

## Input example 
1. -l=100 -w=100 -i=someName.tsv -o=./
