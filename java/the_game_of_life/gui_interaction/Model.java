package the_game_of_life.gui_interaction;
// Compile package: Java> javac the_game_of_life/gui_interaction/Model.java
// Invoke application: Java> java the_game_of_life/gui_interaction/Model

import java.util.Random;


public class Model {
/**
The Game of Life.
The model part of the MVC programming pattern.
*/

  public static boolean[][] getNewMatrix(int maxRow, int maxCol) {
/**
    Return a fresh matrix of the given size.

    * @param maxRow The Y-axis capacity.
    * @param maxCol The X-axis capacity.
    * @return A table containing pairs of cell coordinates.
*/

/*
    if type(max_row) is not int:
        raise TypeError(f"'max_row' parameter must be an int, not {type(max_row)}")
    if type(max_col) is not int:
        raise TypeError(f"'max_row' parameter must be an int, not {type(max_col)}")
    if max_row < 1:
        raise ValueError(f"'max_row' parameter must be greater than zero")
    if max_col < 1:
        raise ValueError(f"'max_col' parameter must be greater than zero")
*/

    boolean[][] matrix = new boolean[maxRow][maxCol];
    return matrix;
  }

  public static void fillMatrixRandomly(boolean[][] matrix) {
/**
    Assign random values to matrix cells.
    In-place (i.e. the matrix itself is modified).

    * @param matrix The table containing pairs of cell coordinates.
    * @param return Null.
*/

/*
    if type(matrix) is not list:
        raise TypeError(f"'matrix' parameter must be a list, not {type(matrix)}")
    for i in range(len(matrix)):
        if type(matrix[i]) is not list:
            raise TypeError(f"'matrix[{i}]' parameter must be a list, not {type(matrix[i])}")
*/

    Random random = new Random();
    for (int i = 0; i < matrix.length; i++) {
      for (int j = 0; j < matrix[0].length; j++) {
        matrix[i][j] = random.nextBoolean();
      }
    }

  }

  public static boolean[][] getNextGeneration(boolean[][] matrix) {
/**
    Return a new matrix with a next generation based on the given old matrix.

    * @param matrix The table containing old pairs of cell coordinates.
    * @param return A table containing new pairs of cell coordinates.
*/

/*
    if type(matrix) is not list:
        raise TypeError(f"'matrix' parameter must be a list, not {type(matrix)}")
    for i in range(len(matrix)):
        if type(matrix[i]) is not list:
            raise TypeError(f"'matrix[{i}]' parameter must be a list, not {type(matrix[i])}")
        for j in range(len(matrix[i])):
            if type(matrix[i][j]) is not bool:
                raise TypeError(f"'matrix[{i}][{j}]' parameter must be a bool, not {type(matrix[i])}")
*/

    boolean[][] matrixNew = new boolean[matrix.length][];
    for (int i = 0; i < matrix.length; i++) {
      matrixNew[i] = matrix[i].clone();
    }

    for (int i = 0; i < matrix.length; i++) {
      for (int j = 0; j < matrix[i].length; j++) {
        updateCell(matrix, matrixNew, i, j);
      }
    }
    return matrixNew;

  }

  public static void updateCell(boolean[][] matrixOld, boolean[][] matrixNew, int posRow, int posCol) {
/**
    Assign a value to the given cell, based on neighbours values.
    In-place (i.e. the matrix itself is modified).

    * @param matrixOld The table containing old pairs of cell coordinates.
    * @param matrixNew The table containing new pairs of cell coordinates.
    * @param posRow The index of the row.
    * @param posCol The index of the column.
    * @param return None.
*/

/*
    if type(matrix_old) is not list:
        raise TypeError(f"'matrix_old' parameter must be a list, not {type(matrix_old)}")
    if type(matrix_new) is not list:
        raise TypeError(f"'matrix_new' parameter must be a list, not {type(matrix_new)}")
    if type(pos_row) is not int:
        raise TypeError(f"'pos_row' parameter must be an int, not {type(pos_row)}")
    if type(pos_col) is not int:
        raise TypeError(f"'pos_col' parameter must be an int, not {type(pos_col)}")
    if pos_row < 0:
        raise ValueError(f"'pos_row' parameter must be a non-negative integer")
    if pos_col < 0:
        raise ValueError(f"'pos_col' parameter must be a non-negative integer")
    if pos_row > len(matrix_new) + 1:
        raise ValueError(f"'pos_row' parameter must be lower than list Y-axis")
    if pos_col > len(matrix_new[pos_row]) + 1:
        raise ValueError(f"'pos_col' parameter must be lower than list X-axis")
    if type(matrix_old[pos_row]) is not list:
        raise TypeError(f"'matrix_old[{pos_row}]' parameter must be a list, not {type(matrix_old[pos_row])}")
    if type(matrix_old[pos_row][pos_col]) is not bool:
        raise TypeError(f"'matrix_old[{pos_row}][{pos_col}]' parameter must be a bool, not {type(matrix_old[pos_col])}")
    if type(matrix_new[pos_row]) is not list:
        raise TypeError(f"'matrix_new[{pos_row}]' parameter must be a list, not {type(matrix_new[pos_row])}")
    if type(matrix_new[pos_row][pos_col]) is not bool:
        raise TypeError(f"'matrix_new[{pos_row}][{pos_col}]' parameter must be a bool, not {type(matrix_new[pos_col])}")
*/

    boolean oldValue = matrixOld[posRow][posCol];
    int counter = getNeighboursCounter(matrixOld, posRow, posCol);

    if (!oldValue && counter == 3) {
      matrixNew[posRow][posCol] = true;
    } else if (oldValue) {
      if (counter < 2) {
        matrixNew[posRow][posCol] = false;
        // } else if (counter == 2 || counter == 3) {  // value is already True, update is not needed
      } else if (counter > 3) {
        matrixNew[posRow][posCol] = false;
      }
    }

  }

  public static int getNeighboursCounter(boolean[][] matrix, int posRow, int posCol) {
/**
    Return a number of neighbours to the given cell.
    Assume the torus shape.

    * @param matrix The table containing pairs of cell coordinates.
    * @param posRow Index of the row.
    * @param posCol Index of the column.
    * @param return A number of neighbours.
*/

/*
    if type(matrix) is not list:
        raise TypeError(f"'matrix' parameter must be a list, not {type(matrix)}")
    if type(pos_row) is not int:
        raise TypeError(f"'pos_row' parameter must be an int, not {type(pos_row)}")
    if type(pos_col) is not int:
        raise TypeError(f"'pos_col' parameter must be an int, not {type(pos_col)}")
    if pos_row < 0:
        raise ValueError(f"'pos_row' parameter must be a non-negative integer")
    if pos_col < 0:
        raise ValueError(f"'pos_col' parameter must be a non-negative integer")
    if pos_row > len(matrix) + 1:
        raise ValueError(f"'pos_row' parameter must be lower than list Y-axis")
    if pos_col > len(matrix[0]) + 1:
        raise ValueError(f"'pos_col' parameter must be lower than list X-axis")
    if type(matrix[pos_row]) is not list:
        raise TypeError(f"'matrix[{pos_row}]' parameter must be a list, not {type(matrix[pos_row])}")
    if type(matrix[pos_row][pos_col]) is not bool:
        raise TypeError(f"'matrix[{pos_row}][{pos_col}]' parameter must be a bool, not {type(matrix[pos_col])}")
*/

    int rowLen = matrix.length;
    int colLen = matrix[posRow].length;

    boolean[] points = new boolean[]{matrix[(posRow - 1 + rowLen) % rowLen][(posCol - 1 + colLen) % colLen],
                matrix[(posRow - 1 + rowLen) % rowLen][posCol],
                matrix[(posRow - 1 + rowLen) % rowLen][(posCol + 1) % colLen],
                matrix[posRow][(posCol - 1 + colLen) % colLen],
                matrix[posRow][(posCol + 1) % colLen],
                matrix[(posRow + 1) % rowLen][(posCol - 1 + colLen) % colLen],
                matrix[(posRow + 1) % rowLen][posCol],
                matrix[(posRow + 1) % rowLen][(posCol + 1) % colLen]};
    int counter = 0;
    for (boolean point : points) {
      counter += point ? 1 : 0;
    }

    return counter;

  }

}
