package the_game_of_life.gui_interaction;
// Compile package: Java> javac the_game_of_life/gui_interaction/Controller.java
// Invoke application: Java> java the_game_of_life/gui_interaction/Controller

import java.util.Map;
import java.awt.*;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Rectangle;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.event.*;


public class Controller {

  public static void refreshGeneration(Map<String, Object> widgets) {
/**
    Force canvas widget to repaint on the display.

    @param widgets The map object containing JComponents and cellSize.
    @param return Null.
*/

/*
    if type(matrix) is not list:
        raise TypeError(f"'matrix' parameter must be a list, not {type(matrix)}")
    if type(widgets) is not dict:
        raise TypeError(f"'widgets' parameter must be a dict, not {type(widgets)}")
*/

    ((Canvas) widgets.get("canvas")).repaint();

  }

  public static boolean[][] nextGeneration(Map<String, Object> widgets) {

/**
    Return a matrix containing a new generation.
    Force canvas widget to repaint on the display.

    @param matrix The table containing old pairs of cell coordinates.
    @param widgets The map object containing JComponents and cellSize.
    @param return A table containing new pairs of cell coordinates.
*/

/*
    if type(matrix) is not list:
        raise TypeError(f"'matrix' parameter must be a list, not {type(matrix)}")
    if type(widgets) is not dict:
        raise TypeError(f"'widgets' parameter must be a dict, not {type(widgets)}")
*/

    Canvas canvas = (Canvas) widgets.get("canvas");
    boolean[][] matrixNew = Model.getNextGeneration(canvas.getMatrix());
    canvas.setMatrix(matrixNew);
    refreshGeneration(widgets);
    return matrixNew;

  }

  public static void refreshCell(Map<String, Object>  widgets, int posRow, int posCol) {
/**
    Force canvas widget to repaint on the display the given cell.

    @param widgets The map object containing JComponents and cellSize.
    @param posRow The index of the row.
    @param posCol The index of the column.
    @param return Null.
*/

/*
    if type(widgets) is not dict:
        raise TypeError(f"'widgets' parameter must be a dict, not {type(widgets)}")
    if type(pos_row) is not int:
        raise TypeError(f"'pos_row' parameter must be an int, not {type(pos_row)}")
    if type(pos_col) is not int:
        raise TypeError(f"'pos_col' parameter must be an int, not {type(pos_col)}")
    if pos_row < 0:
        raise ValueError(f"'pos_row' parameter must be a non-negative integer")
    if pos_col < 0:
        raise ValueError(f"'pos_col' parameter must be a non-negative integer")
    if pos_row > widgets['canvas'].winfo_reqheight():
        raise ValueError(f"'pos_row' parameter must be lower than list Y-axis")
    if pos_col > widgets['canvas'].winfo_reqwidth():
        raise ValueError(f"'pos_col' parameter must be lower than list X-axis")
*/

    int cellSize = (int) widgets.get("cellSize");
    ((Canvas) widgets.get("canvas")).repaint(new Rectangle(posCol * cellSize, posRow * cellSize, cellSize, cellSize));

  }

  public static void simulate(Map<String, Object> widgets) {
/**
Progress infinitely through generations.
Update the data model.
Draw on the display.
Stop depending on the state of the start button.
*/
    new Simulate(widgets).execute();
  }

}

class Simulate extends SwingWorker<Void,int[]> {
/**
Progress infinitely through generations.
Update the data model.
Draw on the display.
Stop depending on the state of the start button.
*/

  private int delay = 75;
  private Map<String, Object> widgets;
  private JButtonStartPause jButtonStartPause;
  private Canvas canvas;

  public Simulate(Map<String, Object> widgets) {
    // System.out.println("Class 'Simulate'. Method 'Simulate()'.");
    this.widgets = widgets;
    jButtonStartPause = (JButtonStartPause) widgets.get("jButtonStartPause");
    canvas = (Canvas) widgets.get("canvas");
  }

  public Simulate(Map<String, Object> widgets, int delay) {
    this(widgets);

    if (delay < 1) {
      throw new IllegalArgumentException("'delay' argument in 'Simulate' class must be a positive number.");
    }
    this.delay = delay;

  }

  public Void doInBackground() {
    while (jButtonStartPause.getText().equals("Pause")) {
      canvas.nextGeneration();
      try {
        Thread.sleep(delay);
      } catch (InterruptedException e) {}
    }

    return null;
  }

}

class JPanelOptions extends JPanel {
/**
The Game of Life dedicated abstraction level for options JPanel.
*/

  public JPanelOptions() {
    super();
    // Default settings.
    setLayout(new FlowLayout(FlowLayout.CENTER));
  }
}

class JListOptions<E> extends JList<E> {
/**
The Game of Life dedicated abstraction level for options list JList.
*/

  public JListOptions(E[] list) {
    super(list);
    // Default settings.
    setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
  }
}

class JListOptionsListener implements ListSelectionListener {
/**
The Game of Life dedicated abstraction level for options listener.
*/

  private Map<String, Object> widgets;
  private JListOptions jListOptions;
  private Canvas canvas;
  private JButtonStartPause jButtonStartPause;

  public JListOptionsListener(Map<String, Object> widgets) {
    this.widgets = widgets;
    jListOptions = (JListOptions) widgets.get("jListOptions");
    canvas = (Canvas) widgets.get("canvas");
    jButtonStartPause = (JButtonStartPause) widgets.get("jButtonStartPause");
  }

  public void valueChanged(ListSelectionEvent event) {
    if (jListOptions.isEnabled() && !event.getValueIsAdjusting()) {

      String choice = (String) jListOptions.getSelectedValue();
      // Debug: System.out.println("Class 'JListOptions'. Method 'valueChanged'. Variable 'option' = " + choice);

      if (choice.equals("Random")) {
        canvas.setIsEnabled(false);
        // Fill the matrix randomly using the 'model' module.
        canvas.fillMatrixRandomly();
      } else if (choice.equals("Interactive")) {
        canvas.setIsEnabled(true);
        // Get a new matrix for interactive mode.
        canvas.clearMatrix();
      }

      // Draw the generation on the canvas.
      canvas.repaint();
      jButtonStartPause.setEnabled(true);
      jButtonStartPause.setText("Start");

    }

  }
}

class JListOptionsMouseListener implements MouseListener {
/**
The Game of Life dedicated abstraction level for options listener.
*/

  private Map<String, Object> widgets;
  private JListOptions jListOptions;
  private String[] options;  // It might need mutable wrapper class to handle external changing.
  private Canvas canvas;
  private JButtonStartPause jButtonStartPause;

  public JListOptionsMouseListener(Map<String, Object> widgets) {
    this.widgets = widgets;
    jListOptions = (JListOptions) widgets.get("jListOptions");
    options = (String[]) widgets.get("options");
    canvas = (Canvas) widgets.get("canvas");
    jButtonStartPause = (JButtonStartPause) widgets.get("jButtonStartPause");
  }

  public void mouseEntered(MouseEvent e) {}
  public void mouseExited(MouseEvent e) {}
  public void mousePressed(MouseEvent e) {}

  public void mouseClicked(MouseEvent event) {
    if (jListOptions.isEnabled()
        && SwingUtilities.isLeftMouseButton(event) && event.getClickCount() == 1
        && jListOptions.getSelectedIndex() != -1) {

      int index = jListOptions.locationToIndex(event.getPoint());
      String choice = options[index];
      // Debug: System.out.println("Class 'JListOptions'. Method 'valueChanged'. Variable 'option' = " + choice);

      if (choice.equals("Random")) {
        canvas.setIsEnabled(false);
        // Fill the matrix randomly using the 'model' module.
        canvas.fillMatrixRandomly();
      } else if (choice.equals("Interactive")) {
        canvas.setIsEnabled(true);
        // Get a new matrix for interactive mode.
        canvas.clearMatrix();
      }

      // Draw the generation on the canvas.
      canvas.repaint();
      jButtonStartPause.setEnabled(true);
      jButtonStartPause.setText("Start");

    }
  }

  public void mouseReleased(MouseEvent e) {}

}

class JPanelStartPause extends JPanel {
/**
The Game of Life dedicated abstraction level for start-pause button JPanel.
*/
  public JPanelStartPause() {
    super();
    // Default settings.
    setLayout(new FlowLayout(FlowLayout.CENTER));
  }
}

class JButtonStartPause extends JButton {
  public JButtonStartPause(String text) {
    super(text);
    // Default settings.
    setEnabled(false);
  }
}

class JButtonStartPauseActionListener implements ActionListener {
/**
The Game of Life dedicated abstraction level for start-pause button listener.
*/

  private Map<String, Object> widgets;
  private JListOptions jListOptions;
  private JButtonStartPause jButtonStartPause;
  private Canvas canvas;

  public JButtonStartPauseActionListener(Map<String, Object> widgets) {
    this.widgets = widgets;
    jListOptions = (JListOptions) widgets.get("jListOptions");
    jButtonStartPause = (JButtonStartPause) widgets.get("jButtonStartPause");
    canvas = (Canvas) widgets.get("canvas");
  }

  public void actionPerformed(ActionEvent e) {
    if (jButtonStartPause.getText().equals("Start")) {
      // Debug: System.out.println("Class 'JButtonStartPause'. Method 'actionPerformed'. 'if (this.getText.equals(`Start`)) {'.");
      // Disable the menu and unbind the screen events during the simulation.
      jListOptions.setEnabled(false);
      canvas.setIsEnabled(false);
      jButtonStartPause.setText("Pause");
      // Start the simulation.
      Controller.simulate(widgets);
    } else if (jButtonStartPause.getText().equals("Pause")) {
      // Debug: System.out.println("Class 'JButtonStartPause'. Method 'actionPerformed'. 'if (this.getText.equals(`Pause`)) {'.");
      // Enable the menu and bind screen events if in interactive mode.
      jListOptions.setEnabled(true);
      if (jListOptions.getSelectedValue().equals("Interactive")) {
        canvas.setIsEnabled(true);
      }
      jButtonStartPause.setText("Start");
    }
  }
}

class Canvas extends JPanel {
/**
Canvas/grid with cells.
*/

  private boolean[][] matrix;
  private int cellSize;
  private boolean isEnabled = false;

  public Canvas(boolean[][] matrix, int cellSize) {

    if (cellSize < 1) {throw new IllegalArgumentException("'cellSize' argument in 'Canvas' class must be a positive number.");}

    this.matrix = matrix;
    this.cellSize = cellSize;
    // Default settings.
    final Dimension canvasDimension = new Dimension(matrix.length * cellSize, matrix[0].length * cellSize);  // Width, height.
    setPreferredSize(canvasDimension);
  }

  public boolean[][] getMatrix() {return matrix;}

  public void setMatrix(boolean[][] matrix) {this.matrix = matrix;}

  public void clearMatrix() {matrix = Model.getNewMatrix(matrix.length, matrix[0].length);}

  public void fillMatrixRandomly() {Model.fillMatrixRandomly(matrix);}

  public boolean[][] nextGeneration() {
    boolean[][] matrixNew = Model.getNextGeneration(matrix);
    setMatrix(matrixNew);
    repaint();
    return matrixNew;
  }

  public boolean getMatrixCellValue(int posRow, int posCol) {return matrix[posRow][posCol];}
    /* if (posRow < 1) {
      throw new IllegalArgumentException("'cellSize' argument in 'Canvas' class must be a positive number.");
    } */

  public void setMatrixCellValue(int posRow, int posCol, boolean value) {matrix[posRow][posCol] = value;}
    /* if (posRow < 1) {
      throw new IllegalArgumentException("'cellSize' argument in 'Canvas' class must be a positive number.");
    } */

  public void setIsEnabled(boolean isEnabled) {this.isEnabled = isEnabled;}

  public boolean getIsEnabled() {return isEnabled;}

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

class CanvasMouseListener implements MouseListener {
/**
The Game of Life dedicated abstraction level for canvas listener.
*/

  private Map<String, Object> widgets;
  private int cellSize;
  private Canvas canvas;

  public CanvasMouseListener(Map<String, Object> widgets) {
    this.widgets = widgets;
    cellSize = (int) widgets.get("cellSize");
    canvas = (Canvas) widgets.get("canvas");
  }

  public void mouseEntered(MouseEvent e) {}
  public void mouseExited(MouseEvent e) {}
  public void mousePressed(MouseEvent e) {}

  public void mouseClicked(MouseEvent event) {
    if (canvas.getIsEnabled()) {

      int posRow = (int) (event.getPoint().y / cellSize);
      // Debug: System.out.println("Class 'Canvas'. Method 'mouseClicked'. posRow = " + posRow);
      int posCol = (int) (event.getPoint().x / cellSize);
      // Debug: System.out.println("Class 'Canvas'. Method 'mouseClicked'. posCol = " + posCol);

/*
    // if pos_row < 0:  # already satisfied
    //     raise ValueError(f"'pos_row' parameter must be a non-negative integer")
    // if pos_col < 0:  # already satisfied
    //     raise ValueError(f"'pos_col' parameter must be a non-negative integer")
    if pos_row > len(matrix) + 1:
        raise ValueError(f"'pos_row' parameter must be lower than list Y-axis")
    if type(matrix[pos_row]) is not list:
        raise TypeError(f"'matrix[{pos_row}]' parameter must be a list, not {type(matrix[pos_row])}")
    if pos_col > len(matrix[pos_row]) + 1:
        raise ValueError(f"'pos_col' parameter must be lower than list X-axis")
    if type(matrix[pos_row][pos_col]) is not bool:
        raise TypeError(f"'matrix[{pos_row}][{pos_col}]' parameter must be a bool, not {type(matrix[pos_col])}")
*/

      if (canvas.getMatrixCellValue(posRow, posCol)) {
        canvas.setMatrixCellValue(posRow, posCol, false);
      } else {
        canvas.setMatrixCellValue(posRow, posCol, true);
      }
      canvas.repaint();
      // Debug: System.out.println("Class 'Canvas'. Method 'mouseClicked'. After update: matrix[posRow][posCol] = " + matrix[posRow][posCol]);

    }
  }

  public void mouseReleased(MouseEvent e) {}
}
