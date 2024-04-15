package the_game_of_life.gui_interaction;

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
