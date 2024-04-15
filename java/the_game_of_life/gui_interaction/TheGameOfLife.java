package the_game_of_life.gui_interaction;

import java.util.Map;


public class TheGameOfLife {
/**
The Game of Life.
An interactive presentation.

Presentation of the implementing simulation skill.

Presentation of the basic working with graphical interface skill:
- Drawing on the screen.
- Handling input from the user.
- Designing and implementing multiple graphical objects changes after single signal.
*/

  final static int MAX_ROW = 100;
  final static int MAX_COL = 100;
  final static int CELL_SIZE = 5;

  public static void main(String[] args) {
    boolean[][] matrix = Model.getNewMatrix(MAX_ROW, MAX_COL);
    Map<String, Object>  widgets = View.setup(matrix, CELL_SIZE);
  }
}
