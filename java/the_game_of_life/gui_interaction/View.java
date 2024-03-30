package the_game_of_life.gui_interaction;
// Compile package: Java> javac the_game_of_life/gui_interaction/View.java
// Invoke application: Java> java the_game_of_life/gui_interaction/View

import java.util.Map;
import java.util.HashMap;
import java.awt.*;
import java.awt.Dimension;
import javax.swing.*;


public class View {

  public static Map<String, Object> setup(boolean[][] matrix, int cellSize) {
/**
    Return widgets of a view encapsulated in map object.

    @param matrix The table containing pairs of cell coordinates.
    @param cellSize The square edge length in pixels.
    @param return The map object containing JComponents and cellSize.
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
    if type(cell_size) is not int:
        raise TypeError(f"'cell_size' parameter must be an int, not {type(cell_size)}")
    if cell_size < 1:
        raise ValueError(f"'cell_size' parameter must be greater than zero")
*/

    Map<String, Object> view = new HashMap<String, Object>();
    view.put("cellSize", cellSize);

    JFrameTheGameOfLife jFrameTheGameOfLife = new JFrameTheGameOfLife(matrix, cellSize);
    view.put("JFrameTheGameOfLife", jFrameTheGameOfLife);

    JPanelOptions jPanelOptions = new JPanelOptions();
    view.put("jPanelOptions", jPanelOptions);
    jFrameTheGameOfLife.getContentPane().add(jPanelOptions);

    String[] options = {"Random", "Interactive"};
    view.put("options", options);
    JListOptions<String> jListOptions = new JListOptions<String>(options);
    view.put("jListOptions", jListOptions);
    jPanelOptions.add(jListOptions);

    JPanelStartPause jPanelStartPause = new JPanelStartPause();
    view.put("jPanelStartPause", jPanelStartPause);

    JButtonStartPause jButtonStartPause = new JButtonStartPause("Start");
    view.put("jButtonStartPause", jButtonStartPause);
    jFrameTheGameOfLife.getContentPane().add(jPanelStartPause);
    jPanelStartPause.add(jButtonStartPause);

    Canvas canvas = new Canvas(matrix, cellSize);
    view.put("canvas", canvas);
    jFrameTheGameOfLife.getContentPane().add(canvas);

    jListOptions.addMouseListener(new JListOptionsMouseListener(view));
    jButtonStartPause.addActionListener(new JButtonStartPauseActionListener(view));
    canvas.addMouseListener(new CanvasMouseListener(view));

    jFrameTheGameOfLife.setVisible(true);
    return view;

/*
    class JListOptionsListener implements ListSelectionListener {
      public void valueChanged(ListSelectionEvent event) {
        if (jListOptions.isEnabled() && !event.getValueIsAdjusting()) {

          String choice = (String) jListOptions.getSelectedValue();
          System.out.println("Class 'JListOptions'. Method 'valueChanged'. Variable 'option' = " + choice);

          if (choice.equals("Random")) {
            canvas.setIsEnabled(false);
            // Fill the matrix randomly using the 'model' module.
            Model.fillMatrixRandomly(canvas.matrix);
          } else if (choice.equals("Interactive")) {
            // Get a new matrix for interactive mode.
            canvas.setIsEnabled(true);
            canvas.matrix = Model.getNewMatrix(matrix.length, matrix[0].length);
          }
          // Draw the generation on the canvas.
          canvas.repaint();
          jButtonStartPause.setEnabled(true);
          jButtonStartPause.setText("Start");

        }
      }
    }

    class JListOptionsMouseListener implements MouseListener {

      public void mouseEntered(MouseEvent e) {}
      public void mouseExited(MouseEvent e) {}
      public void mousePressed(MouseEvent e) {}

      public void mouseClicked(MouseEvent event) {
        if (jListOptions.isEnabled()
            && SwingUtilities.isLeftMouseButton(event) && event.getClickCount() == 1
            && jListOptions.getSelectedIndex() != -1) {

          int index = jListOptions.locationToIndex(event.getPoint());
          String choice = options[index];
          System.out.println("Class 'JListOptions'. Method 'valueChanged'. Variable 'option' = " + choice);

          if (choice.equals("Random")) {
            canvas.setIsEnabled(false);
            // Fill the matrix randomly using the 'model' module.
            Model.fillMatrixRandomly(canvas.matrix);
          } else if (choice.equals("Interactive")) {
            // Get a new matrix for interactive mode.
            canvas.setIsEnabled(true);
            canvas.matrix = Model.getNewMatrix(canvas.matrix.length, canvas.matrix[0].length);
          }
          // Draw the generation on the canvas.
          canvas.repaint();
          jButtonStartPause.setEnabled(true);
          jButtonStartPause.setText("Start");

        }
      }

      public void mouseReleased(MouseEvent e) {}

    }
*/

  }

}

class JFrameTheGameOfLife extends JFrame {

  public JFrameTheGameOfLife(boolean[][] matrix, int cellSize) {
    this("The Game of Life", matrix, cellSize);
  }

  public JFrameTheGameOfLife(String title, boolean[][] matrix, int cellSize) {
    super(title);
    // Default settings.
    final Dimension jFrameDimension = new Dimension(matrix.length * cellSize + 16, 56 + matrix[0].length * cellSize + 39);  // Width, height. Window bar has probably height of 40.
    setSize(jFrameDimension);
    setMinimumSize(jFrameDimension);
    setResizable(false);
    setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    setLayout(new FlowLayout(FlowLayout.CENTER));
  }

}
