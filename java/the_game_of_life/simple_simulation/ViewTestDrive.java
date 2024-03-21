package the_game_of_life.simple_simulation;

import java.util.Map;
import javax.swing.*;


public class ViewTestDrive {

  final static int maxRow = 100;
  final static int maxCol = 100;
  static boolean[][] matrix = Model.getNewMatrix(maxRow, maxCol);
  final static int cellSize = 5;

  public static void main(String[] args) {
    setupTestDrive();
  }

  public static void setupTestDrive() {
    Map<String, Object> widgets = View.setup(matrix, cellSize);
    System.out.println("Class 'ViewTestDrive'. Method 'setupTestDrive'. widgets.getClass() = " + widgets.getClass());
    System.out.println("Class 'ViewTestDrive'. Method 'setupTestDrive'. (int) widgets.get('cellSize') = " + (int) widgets.get("cellSize"));
  }

}
