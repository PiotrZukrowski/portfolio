package the_game_of_life.simple_simulation;

public class ModelTestDrive {

  static int maxRow = 3;
  static int maxCol = 4;

  public static void main(String[] args) {
    getNewMatrixTestDrive(maxRow, maxCol);
    fillMatrixRandomlyTestDrive();
    getNextGenerationTestDrive();
    updateCellTestDrive();
    getNeighboursCounterTestDrive();
  }

  public static void getNewMatrixTestDrive(int maxRow, int maxCol) {

    boolean[][] matrix = Model.getNewMatrix(maxRow, maxCol);
    System.out.println("Class 'ModelTestDrive'. Method 'getNewMatrixTestDrive'. matrix.length = " + matrix.length);
    System.out.println("Class 'ModelTestDrive'. Method 'getNewMatrixTestDrive'. matrix[0].length = " + matrix[0].length);

    for (int i = 0; i < maxRow; i++) {
      for (int j = 0; j < maxCol; j++) {
        System.out.println("Class 'ModelTestDrive'. Method 'getNewMatrixTestDrive'. matrix[i][j] = " + matrix[i][j]);
      }
    }

  }

  public static void fillMatrixRandomlyTestDrive() {
    boolean[][] matrix = Model.getNewMatrix(maxRow, maxCol);
    Model.fillMatrixRandomly(matrix);
    for (int i = 0; i < maxRow; i++) {
      for (int j = 0; j < maxCol; j++) {
        System.out.println("Class 'ModelTestDrive'. Method 'fillMatrixRandomlyTestDrive'. matrix[i][j] = " + matrix[i][j]);
      }
    }
  }

  public static void getNextGenerationTestDrive() {

    boolean[][] matrix = Model.getNewMatrix(maxRow, maxCol);

    Model.fillMatrixRandomly(matrix);
    for (int i = 0; i < maxRow; i++) {
      for (int j = 0; j < maxCol; j++) {
        System.out.println("Class 'ModelTestDrive'. Method 'getNextGenerationTestDrive'. original matrix[i][j] = " + matrix[i][j]);
      }
    }

    matrix = Model.getNextGeneration(matrix);
    for (int i = 0; i < maxRow; i++) {
      for (int j = 0; j < maxCol; j++) {
        System.out.println("Class 'ModelTestDrive'. Method 'getNextGenerationTestDrive'. next matrix[i][j] = " + matrix[i][j]);
      }
    }

  }

  public static void updateCellTestDrive() {

    boolean[][] matrix = Model.getNewMatrix(maxRow, maxCol);

    Model.fillMatrixRandomly(matrix);
    for (int i = 0; i < maxRow; i++) {
      for (int j = 0; j < maxCol; j++) {
        System.out.println("Class 'ModelTestDrive'. Method 'updateCellTestDrive'. original matrix[i][j] = " + matrix[i][j]);
      }
    }

    boolean[][] matrixNew = Model.getNextGeneration(matrix);

    for (int i = 0; i < maxRow; i++) {
      for (int j = 0; j < maxCol; j++) {
        Model.updateCell(matrix, matrixNew, i, j);
        System.out.println("Class 'ModelTestDrive'. Method 'updateCellTestDrive'. next matrixNew[i][j] = " + matrixNew[i][j]);
      }
    }

  }

  public static void getNeighboursCounterTestDrive() {

    boolean[][] matrix = Model.getNewMatrix(maxRow, maxCol);

    Model.fillMatrixRandomly(matrix);
    for (int i = 0; i < maxRow; i++) {
      for (int j = 0; j < maxCol; j++) {
        System.out.println("Class 'ModelTestDrive'. Method 'getNeighboursCounter'. original matrix[i][j] = " + matrix[i][j]);
      }
    }

    for (int i = 0; i < maxRow; i++) {
      for (int j = 0; j < maxCol; j++) {
        System.out.println("Class 'ModelTestDrive'. Method 'getNeighboursCounter'. Model.getNeighboursCounter(matrix, i, j) = " + Model.getNeighboursCounter(matrix, i, j));
      }
    }

  }

}
