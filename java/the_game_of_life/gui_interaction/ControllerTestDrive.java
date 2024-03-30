package the_game_of_life.gui_interaction;
// Compile package: Java> javac the_game_of_life/gui_interaction/ControllerTestDrive.java
// Invoke application: Java> java the_game_of_life/gui_interaction/ControllerTestDrive

import java.util.Map;


public class ControllerTestDrive {
/**
The Game of Life.
Sunny day tests during development phase of controller part of the MVC programming pattern.
*/

  final static int MAX_ROW = 100;
  final static int MAX_COL = 100;
  final static int CELL_SIZE = 5;

  public static void main(String[] args) {
/**
Run all tests.
*/
    refreshCellTestDrive();

    try {
      Thread.sleep(2000);
    } catch (InterruptedException e) {}
    refreshGenerationTestDrive();

    try {
      Thread.sleep(2000);
    } catch (InterruptedException e) {}
    nextGenerationTestDrive();

  }

  public static void refreshCellTestDrive() {
/**
Present results of "Controller" class "refreshCell" method.
*/
    boolean[][] matrix = Model.getNewMatrix(MAX_ROW, MAX_COL);
    matrix[0][0] = true;  // Top-left.
    matrix[(int) MAX_ROW / 2][(int) MAX_COL / 2] = true;  // Middle.
    matrix[MAX_ROW - 1][MAX_COL - 1] = true;  // Bottom-right.
    Map<String, Object>  widgets = View.setup(matrix, CELL_SIZE);

    try {
      Thread.sleep(2000);
    } catch (InterruptedException e) {}
    System.out.println("I'm after sleep 2s.");
    // Disable cells.
    matrix[0][0] = false;  // Top-left. // Is it still possible, as canvas has reference copy as private?
    matrix[(int) MAX_ROW / 2][(int) MAX_COL / 2] = false;  // Middle.
    matrix[MAX_ROW - 1][MAX_COL - 1] = false;  // Bottom-right.
    Controller.refreshCell(widgets, 0, 0);
    Controller.refreshCell(widgets, (int) MAX_ROW / 2, (int) MAX_COL / 2);
    Controller.refreshCell(widgets, MAX_ROW - 1, MAX_COL - 1);

  }

  public static void refreshGenerationTestDrive() {
/**
Present results of "Controller" class "refreshGeneration" method.
*/
    boolean[][] matrix = Model.getNewMatrix(MAX_ROW, MAX_COL);
    matrix[0][MAX_COL - 1] = true;  // Top-right.
    matrix[(int) MAX_ROW / 2][MAX_COL - 1] = true;  // Middle-right.
    matrix[MAX_ROW - 1][0] = true;  // Bottom-left.
    Map<String, Object>  widgets = View.setup(matrix, CELL_SIZE);

    try {
      Thread.sleep(2000);
    } catch (InterruptedException e) {}
    System.out.println("I'm after sleep 2s.");
    // Disable cells.
    matrix[0][MAX_COL - 1] = false;  // Top-right.
    matrix[(int) MAX_ROW / 2][MAX_COL - 1] = false;  // Middle-right.
    matrix[MAX_ROW - 1][0] = false;  // Bottom-left.
    Controller.refreshGeneration(widgets);

  }

  public static void nextGenerationTestDrive() {
/**
Present results of "Controller" class "nextGeneration" method.
*/
    boolean[][] matrix = Model.getNewMatrix(MAX_ROW, MAX_COL);
    Model.fillMatrixRandomly(matrix);
    Map<String, Object>  widgets = View.setup(matrix, CELL_SIZE);

    try {
      Thread.sleep(2000);
    } catch (InterruptedException e) {}
    System.out.println("I'm after sleep 2s.");
    Controller.nextGeneration(widgets);

  }

}
