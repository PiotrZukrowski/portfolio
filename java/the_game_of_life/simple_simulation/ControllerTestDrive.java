package the_game_of_life.simple_simulation;

import java.util.Map;


public class ControllerTestDrive {

  final static int MAX_ROW = 100;
  final static int MAX_COL = 100;
  final static int CELL_SIZE = 5;
  final static int NUM_OF_CYCLES = 100;

  public static void main(String[] args) {

    refreshCellTestDrive();

    try {
      Thread.sleep(2000);
    } catch (InterruptedException e) {}
    refreshGenerationTestDrive();

    try {
      Thread.sleep(2000);
    } catch (InterruptedException e) {}
    nextGenerationTestDrive();

    try {
      Thread.sleep(2000);
    } catch (InterruptedException e) {}
    simulateTestDrive();

  }

  public static void refreshCellTestDrive() {

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
    matrix[0][0] = false;  // Top-left.
    matrix[(int) MAX_ROW / 2][(int) MAX_COL / 2] = false;  // Middle.
    matrix[MAX_ROW - 1][MAX_COL - 1] = false;  // Bottom-right.
    Controller.refreshCell(widgets, 0, 0);
    Controller.refreshCell(widgets, (int) MAX_ROW / 2, (int) MAX_COL / 2);
    Controller.refreshCell(widgets, MAX_ROW - 1, MAX_COL - 1);

  }

  public static void refreshGenerationTestDrive() {

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
    Controller.refreshGeneration(matrix, widgets);

  }

  public static void nextGenerationTestDrive() {

    boolean[][] matrix = Model.getNewMatrix(MAX_ROW, MAX_COL);
    Model.fillMatrixRandomly(matrix);
    Map<String, Object>  widgets = View.setup(matrix, CELL_SIZE);

    try {
      Thread.sleep(2000);
    } catch (InterruptedException e) {}
    System.out.println("I'm after sleep 2s.");
    Controller.nextGeneration(matrix, widgets);

  }

  public static void simulateTestDrive() {
    boolean[][] matrix = Model.getNewMatrix(MAX_ROW, MAX_COL);
    Model.fillMatrixRandomly(matrix);
    Map<String, Object>  widgets = View.setup(matrix, CELL_SIZE);
    Controller.simulate(matrix, widgets, NUM_OF_CYCLES);
  }

}
