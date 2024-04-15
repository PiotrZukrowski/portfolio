package the_game_of_life.simple_simulation;

import java.util.Map;
import javax.swing.*;
import java.awt.Rectangle;


public class Controller {

  public static void refreshGeneration(boolean[][] matrix, Map<String, Object> widgets) {
/**
    Force screen widget to repaint on the display.

    @param matrix The table containing pairs of cell coordinates.
    @param widgets The map object containing JComponents and cellSize.
    @param return None.
*/

    int cellSize = (int) widgets.get("cellSize");
    ((JComponent) widgets.get("screen")).repaint(new Rectangle(0, 0,
                                                               cellSize * matrix[0].length,
                                                               cellSize * matrix.length));
  }

  public static boolean[][] nextGeneration(boolean[][] matrix, Map<String, Object> widgets) {

/**
    Return a matrix containing a new generation.
    Force screen widget to repaint on the display.

    @param matrix The table containing old pairs of cell coordinates.
    @param widgets The map object containing JComponents and cellSize.
    @param return A table containing new pairs of cell coordinates.
*/

    boolean[][] matrixNew = Model.getNextGeneration(matrix);
    ((Canvas) widgets.get("screen")).matrix = matrixNew;
    refreshGeneration(matrixNew, widgets);
    return matrixNew;

  }


  public static void refreshCell(Map<String, Object>  widgets, int posRow, int posCol) {
/**
    Force screen widget to repaint on the display the given cell.

    @param widgets The map object containing JComponents and cellSize.
    @param posRow The index of the row.
    @param posCol The index of the column.
    @param return None.
*/

    int cellSize = (int) widgets.get("cellSize");
    ((JComponent) widgets.get("screen")).repaint(new Rectangle(posCol * cellSize,
                                                               posRow * cellSize,
                                                               cellSize,
                                                               cellSize));
  }

  public static boolean[][] simulate(boolean[][] matrix, Map<String, Object>  widgets, int cycles) {
/**
    Generate iteratively the given number of generations.
    Update the screen widget.
    Repaint on the display.

    @param matrix The table containing old pairs of cell coordinates.
    @param widgets The map object containing JComponents and cellSize.
    @param cycles The number of generations to simulate.
    @param return A table containing new pairs of cell coordinates.
*/

    for (int i = 0; i < cycles; i++) {
      try {
        Thread.sleep(75);
      } catch (InterruptedException e) {}
      matrix = nextGeneration(matrix, widgets);
    }

    return matrix;
  }

}
