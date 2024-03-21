package the_game_of_life.simple_simulation;

import java.util.Map;
import java.util.HashMap;
import javax.swing.*;
import java.awt.Dimension;
import java.awt.event.*;
import java.awt.Graphics;
import java.awt.Color;


public class View {

  public static Map<String, Object> setup(boolean[][] matrix, int cellSize) {
/**
    Return widgets of a view encapsulated in map object.

    @param matrix The table containing pairs of cell coordinates.
    @param cellSize The square edge length in pixels.
    @param return The map object containing JComponents and cellSize.
*/

    Map<String, Object> view = new HashMap<String, Object>();
    final Dimension jFrameDimension = new Dimension(matrix.length * cellSize + 16, matrix[0].length * cellSize + 39);  // Width, height. Window bar has probably height of 40.
    final Dimension screenDimension = new Dimension(matrix.length * cellSize, matrix[0].length * cellSize);  // Width, height.
    view.put("cellSize", cellSize);

    JFrame jFrame = new JFrame();
    view.put("jFrame", jFrame);
    jFrame.setTitle("The Game of Life");
    jFrame.setSize(jFrameDimension);
    jFrame.setMinimumSize(jFrameDimension);
    jFrame.setResizable(false);
    jFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

    Canvas screen = new Canvas(matrix, cellSize);
    jFrame.getContentPane().add(screen);
    view.put("screen", screen);
    screen.setPreferredSize(screenDimension);
    jFrame.setVisible(true);
    return view;

  }

}

class Canvas extends JPanel {
/**
    Screen/grid with cells.
*/

  boolean[][] matrix;
  int cellSize;

  public Canvas(boolean[][] matrix, int cellSize) {
    this.matrix = matrix;
    this.cellSize = cellSize;
  }

  public void paintComponent(Graphics graphics) {
    super.paintComponent(graphics);
    for (int i = 0; i < matrix.length; i++) {
      for (int j = 0; j < matrix[i].length; j++) {
        if (!matrix[i][j]) {  // Cell is dead.
          graphics.setColor(Color.WHITE);
          graphics.fillRect(j * cellSize, i * cellSize, cellSize, cellSize);  // x, y, width, height.
        } else {  // Cell is alive.
          graphics.setColor(Color.BLACK);
          graphics.fillRect(j * cellSize, i * cellSize, cellSize, cellSize);  // x, y, width, height.
        }
      }
    }
  }

}
