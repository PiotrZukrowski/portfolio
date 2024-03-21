package the_game_of_life.simple_simulation;

import java.util.Map;


public class TheGameOfLife {

  final static int MAX_ROW = 100;
  final static int MAX_COL = 100;
  final static int CELL_SIZE = 5;
  final static int NUM_OF_CYCLES = 100;

  public static void main(String[] args) {
    boolean[][] matrix = Model.getNewMatrix(MAX_ROW, MAX_COL);
    Model.fillMatrixRandomly(matrix);
    Map<String, Object>  widgets = View.setup(matrix, CELL_SIZE);
    Controller.simulate(matrix, widgets, NUM_OF_CYCLES);
  }
}
