"""
The Game of Life.
The controller part of the MVC programming pattern.
"""


import model


def clear_screen(widgets: dict, update_view: bool = True) -> None:

    """
    Clear the screen data model. Draw on the display.

    :param widgets: The dictionary containing tkinter objects.
    :param update_view: The flag can be set to update also the display.
    :return: None.
    """

    if type(widgets) is not dict:
        raise TypeError(f"'widgets' parameter must be a dict, not {type(widgets)}")

    widgets['screen'].delete('all')
    if update_view:
        widgets['root'].update()


def draw_generation(matrix: list[list[bool]], widgets: dict, update_view: bool = True) -> None:

    """
    Draw the current data model from the matrix on the screen view object from the widgets. Draw on the display.

    :param matrix: The table containing pairs of cell coordinates.
    :param widgets: The dictionary containing tkinter objects.
    :param update_view: The flag can be set to update also the display.
    :return: None.
    """

    if type(matrix) is not list:
        raise TypeError(f"'matrix' parameter must be a list, not {type(matrix)}")
    if type(widgets) is not dict:
        raise TypeError(f"'widgets' parameter must be a dict, not {type(widgets)}")

    for i in range(len(matrix)):
        for j in range(len(matrix[i])):
            if matrix[i][j]:
                draw_cell(widgets, i, j, update_view=False)
    if update_view:
        widgets['root'].update()


def next_generation(matrix: list[list[bool]], widgets: dict) -> list[list[bool]]:

    """
    Return a matrix containing a new generation. Draw on the display.

    :param matrix: The table containing old pairs of cell coordinates.
    :param widgets: The dictionary containing tkinter objects.
    :return: A table containing new pairs of cell coordinates.
    """

    if type(matrix) is not list:
        raise TypeError(f"'matrix' parameter must be a list, not {type(matrix)}")
    if type(widgets) is not dict:
        raise TypeError(f"'widgets' parameter must be a dict, not {type(widgets)}")

    clear_screen(widgets, update_view=False)
    matrix: list[list[bool]] = model.get_next_generation(matrix)
    draw_generation(matrix, widgets)
    return matrix


def draw_cell(widgets: dict, pos_row, pos_col, color_filling='black', color_outline='grey', update_view: bool = True) -> None:

    """
    Draw the square in the given position. Draw on the display.

    :param widgets: The dictionary containing tkinter objects.
    :param pos_row: The index of the row.
    :param pos_col: The index of the column.
    :param color_filling: The color of the cell center.
    :param color_outline: The color of the cell border.
    :param update_view: The flag can be set to update also the display.
    :return: None.
    """

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
    if pos_row > widgets['screen'].winfo_reqheight():
        raise ValueError(f"'pos_row' parameter must be lower than list Y-axis")
    if pos_col > widgets['screen'].winfo_reqwidth():
        raise ValueError(f"'pos_col' parameter must be lower than list X-axis")

    cell_size: int = widgets['cell_size']
    widgets['screen'].create_rectangle(pos_col * cell_size,
                                       pos_row * cell_size,
                                       pos_col * cell_size + cell_size,
                                       pos_row * cell_size + cell_size,
                                       fill=color_filling,
                                       outline=color_outline)
    if update_view:
        widgets['root'].update()


def simulate(matrix: list[list[bool]], widgets: dict, cycles: int) -> list[list[bool]]:

    """
    Generate iteratively the given number of generations. Update the data model. Draw on the display.

    :param matrix: The table containing old pairs of cell coordinates.
    :param widgets: The dictionary containing tkinter objects.
    :param cycles: The number of generations to simulate.
    :return: A table containing new pairs of cell coordinates.
    """

    if type(matrix) is not list:
        raise TypeError(f"'matrix' parameter must be a list, not {type(matrix)}")
    if type(widgets) is not dict:
        raise TypeError(f"'widgets' parameter must be a dict, not {type(widgets)}")
    if type(cycles) is not int:
        raise TypeError(f"'cycles' parameter must be an int, not {type(cycles)}")
    if cycles < 1:
        raise ValueError(f"'cycles' parameter must be greater than zero")

    for i in range(cycles):
        matrix: list[list[bool]] = next_generation(matrix, widgets)

    return matrix
