package the_game_of_life.gui_interaction;
// Compile package: Java> javac the_game_of_life/gui_interaction/ViewTestDrive.java
// Invoke application: Java> java the_game_of_life/gui_interaction/ViewTestDrive

import java.util.Map;
import javax.swing.*;


public class ViewTestDrive {
/**
The Game of Life.
Sunny day tests during development phase of view part of the MVC programming pattern.
*/

  final static int MAX_ROW = 100;
  final static int MAX_COL = 100;
  final static int CELL_SIZE = 5;

  public static void main(String[] args) {
/**
Run all tests.
*/
    setupTestDrive();
  }

  public static void setupTestDrive() {
/**
Present results of "View" class "setup" method.
*/
    boolean[][] matrix = Model.getNewMatrix(MAX_ROW, MAX_COL);
    Map<String, Object> widgets = View.setup(matrix, CELL_SIZE);
    // Debug: System.out.println("Class 'ViewTestDrive'. Method 'setupTestDrive'. widgets.getClass() = " + widgets.getClass());
    // Debug: System.out.println("Class 'ViewTestDrive'. Method 'setupTestDrive'. (int) widgets.get('cellSize') = " + (int) widgets.get("cellSize"));
  }

}
