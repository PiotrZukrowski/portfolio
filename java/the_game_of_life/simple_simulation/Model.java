package the_game_of_life.simple_simulation;

import java.util.Random;


public class Model {

  public static boolean[][] getNewMatrix(int maxRow, int maxCol) {
/**
    Return a fresh matrix of the given size.

    * @param maxRow The Y-axis capacity.
    * @param maxCol The X-axis capacity.
    * @return A table containing pairs of cell coordinates.
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
