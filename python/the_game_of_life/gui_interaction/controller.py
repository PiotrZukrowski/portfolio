"""
The Game of Life.
The controller part of the MVC programming pattern.
"""


import sys
import model
import view
import tkinter


matrix: list[list[bool]] = []  # The model object - a table containing pairs of cell coordinates
widgets: dict = {}  # The view object - a dictionary of widgets
interval: int = 10  # The time between display updates.


def setup(max_row: int, max_col: int, cell_size: int) -> tuple[list[list[bool]], dict]:

    """
    Create a model object and view object.

    :param max_row: The Y-axis capacity.
    :param max_col: The X-axis capacity.
    :param cell_size: The square edge length in pixels.
    :return: A tuple with:
     - a table containing pairs of cell coordinates
     - a dictionary of widgets
    """

    if type(max_row) is not int:
        raise TypeError(f"'max_row' parameter must be an int, not {type(max_row)}'")
    if type(max_col) is not int:
        raise TypeError(f"'max_row' parameter must be an int, not {type(max_col)}'")
    if max_row < 1:
        raise ValueError(f"'max_row' parameter must be greater than zero")
    if max_col < 1:
        raise ValueError(f"'max_col' parameter must be greater than zero")
    if type(cell_size) is not int:
        raise TypeError(f"'cell_size' parameter must be an int, not {type(cell_size)}")
    if cell_size < 1:
        raise ValueError(f"'cell_size' parameter must be greater than zero")
    if 'matrix' not in globals():
        raise NameError(f"'matrix' name is not defined")
    if 'widgets' not in globals():
        raise NameError(f"'widgets' name is not defined")

    global matrix, widgets

    if type(matrix) is not list:
        raise TypeError(f"'matrix' parameter must be a list, not {type(matrix)}")
    if type(widgets) is not dict:
        raise TypeError(f"'widgets' parameter must be a dict, not {type(widgets)}")
    if 'model' not in sys.modules:
        raise NameError(f"'model' name is not defined")
    if 'view' not in sys.modules:
        raise NameError(f"'view' name is not defined")
    if 'tkinter' not in sys.modules:
        raise NameError(f"'tkinter' name is not defined")

    matrix = model.get_new_matrix(max_row, max_col)
    widgets = view.setup(matrix, cell_size)

    widgets['menu'] = tkinter.OptionMenu(widgets['root'],
                                         widgets['choice'],
                                         *widgets['options'],
                                         command=menu_handler)
    widgets['menu'].config(width=20)
    widgets['menu'].grid(row=0, column=0, padx=20)

    return matrix, widgets


def mainloop() -> None:

    """
    Run the main loop of view.

    :return: None
    """

    if 'view' not in sys.modules:
        raise NameError(f"'view' name is not defined")

    view.mainloop()


def clear_screen(widgets: dict, update_view: bool = True) -> None:

    """
    Clear the screen data model.
    Draw on the display.

    :param widgets: The dictionary containing tkinter objects.
    :param update_view: The flag can be set to update also the display.
    :return: None.
    """

    if type(widgets) is not dict:
        raise TypeError(f"'widgets' parameter must be a dict, not {type(widgets)}")
    if 'tkinter' not in sys.modules:
        raise NameError(f"'tkinter' name is not defined")
    if 'screen' not in widgets:
        raise KeyError(f"'widgets' dictionary must have 'screen' key")
    if type(widgets['screen']) is not tkinter.Canvas:
        raise TypeError(f"'widgets['screen']' object must be a tkinter.Canvas, not {type(widgets['screen'])}")
    if 'root' not in widgets:
        raise KeyError(f"'widgets' dictionary must have 'root' key")
    if type(widgets['root']) is not tkinter.Tk:
        raise TypeError(f"'widgets['root']' object must be a tkinter.Tk, not {type(widgets['root'])}")

    widgets['screen'].delete('all')
    if update_view:
        widgets['root'].update()


def draw_generation(matrix: list[list[bool]], widgets: dict, update_view: bool = True) -> None:

    """
    Draw the current data model from the matrix on the screen view object from the widgets.
    Draw on the display.

    :param matrix: The table containing pairs of cell coordinates.
    :param widgets: The dictionary containing tkinter objects.
    :param update_view: The flag can be set to update also the display.
    :return: None.
    """

    if type(matrix) is not list:
        raise TypeError(f"'matrix' parameter must be a list, not {type(matrix)}")
    for i in range(len(matrix)):
        if type(matrix[i]) is not list:
            raise TypeError(f"'matrix[{i}]' parameter must be a list, not {type(matrix[i])}")
        for j in range(len(matrix[i])):
            if type(matrix[i][j]) is not bool:
                raise TypeError(f"'matrix[{i}][{j}]' parameter must be a bool, not {type(matrix[i])}")
    if type(widgets) is not dict:
        raise TypeError(f"'widgets' parameter must be a dict, not {type(widgets)}")
    if 'root' not in widgets:
        raise KeyError(f"'widgets' dictionary must have 'root' key")
    if type(widgets['root']) is not tkinter.Tk:
        raise TypeError(f"'widgets['root']' object must be a tkinter.Tk, not {type(widgets['root'])}")

    for i in range(len(matrix)):
        for j in range(len(matrix[i])):
            if matrix[i][j]:
                draw_cell(widgets, i, j, update_view=False)
    if update_view:
        widgets['root'].update()


def progress() -> None:

    """
    Progress infinitely through generations.
    Update the data model.
    Draw on the display.
    Stop depending on the state of the start button.

    :return: None.
    """

    if 'matrix' not in globals():
        raise NameError(f"'matrix' name is not defined")
    if 'widgets' not in globals():
        raise NameError(f"'widgets' name is not defined")

    global matrix, widgets, interval

    if type(matrix) is not list:
        raise TypeError(f"'matrix' parameter must be a list, not {type(matrix)}")
    if type(widgets) is not dict:
        raise TypeError(f"'widgets' parameter must be a dict, not {type(widgets)}")
    if 'start' not in widgets:
        raise KeyError(f"'widgets' dictionary must have 'start' key")
    if type(widgets['start']) is not tkinter.Button:
        raise TypeError(f"'widgets['start']' object must be a tkinter.Button, not {type(widgets['start'])}")
    if 'root' not in widgets:
        raise KeyError(f"'widgets' dictionary must have 'root' key")
    if type(widgets['root']) is not tkinter.Tk:
        raise TypeError(f"'widgets['root']' object must be a tkinter.Tk, not {type(widgets['root'])}")
    if 'model' not in sys.modules:
        raise NameError(f"'model' name is not defined")

    if widgets['start'].cget('text') == 'Pause':
        clear_screen(widgets, update_view=False)
        matrix = model.get_next_generation(matrix)
        draw_generation(matrix, widgets)
        widgets['root'].after(interval, progress)


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
    if 'screen' not in widgets:
        raise KeyError(f"'widgets' dictionary must have 'screen' key")
    if type(widgets['screen']) is not tkinter.Canvas:
        raise TypeError(f"'widgets['screen']' object must be a tkinter.Canvas, not {type(widgets['screen'])}")
    if pos_row > widgets['screen'].winfo_reqheight():
        raise ValueError(f"'pos_row' parameter must be lower than list Y-axis")
    if pos_col > widgets['screen'].winfo_reqwidth():
        raise ValueError(f"'pos_col' parameter must be lower than list X-axis")
    if 'cell_size' not in widgets:
        raise KeyError(f"'widgets' dictionary must have 'cell_size' key")
    if type(widgets['cell_size']) is not int:
        raise TypeError(f"'widgets['cell_size']' object must be an int, not {type(widgets['cell_size'])}")
    if 'root' not in widgets:
        raise KeyError(f"'widgets' dictionary must have 'root' key")
    if type(widgets['root']) is not tkinter.Tk:
        raise TypeError(f"'widgets['root']' object must be a tkinter.Tk, not {type(widgets['root'])}")

    cell_size: int = widgets['cell_size']
    widgets['screen'].create_rectangle(pos_col * cell_size,
                                       pos_row * cell_size,
                                       pos_col * cell_size + cell_size,
                                       pos_row * cell_size + cell_size,
                                       fill=color_filling,
                                       outline=color_outline)
    if update_view:
        widgets['root'].update()


def screen_handler(event) -> None:

    # documentation made by the chat gpt, based on the body of the function, slightly modified
    """
    Event handler function for the screen object.

    Parameters:
    - event: Tkinter event object representing the occurrence of an event, such as a mouse click.

    Global Variables:
    - matrix: A 2D list representing the state of cells on the screen.
    - widgets: A dictionary containing configuration parameters, including 'cell_size'.

    Returns:
    None

    Description:
    This function is designed to handle events, particularly mouse clicks on a screen. It updates the state
    of the matrix based on the position of the mouse click. If the cell at the clicked position is currently
    'alive', it toggles it to 'dead', and vice versa. It then updates the graphical representation of the cell
    on the screen by calling the 'draw_cell' function.

    Note:
    - The function assumes that the 'draw_cell' function is defined and available in the code.
    - The 'matrix' is assumed to be a global variable representing the state of cells on the screen.
    - The 'widgets' dictionary is assumed to be a global variable containing configuration parameters.

    Example Usage:
    ```
    root.bind("<Button-1>", screen_handler)
    ```
    This binds the function to a left mouse button click event on the Tkinter window.
    """

    if 'matrix' not in globals():
        raise NameError(f"'matrix' name is not defined")
    if 'widgets' not in globals():
        raise NameError(f"'widgets' name is not defined")

    global matrix, widgets

    if type(matrix) is not list:
        raise TypeError(f"'matrix' parameter must be a list, not {type(matrix)}")
    for i in range(len(matrix)):
        if type(matrix[i]) is not list:
            raise TypeError(f"'matrix[{i}]' parameter must be a list, not {type(matrix[i])}")
    if type(widgets) is not dict:
        raise TypeError(f"'widgets' parameter must be a dict, not {type(widgets)}")
    if 'cell_size' not in widgets:
        raise KeyError(f"'widgets' dictionary must have 'cell_size' key")
    if type(widgets['cell_size']) is not int:
        raise TypeError(f"'widgets['cell_size']' object must be an int, not {type(widgets['cell_size'])}")
    if widgets['cell_size'] < 1:
        raise ValueError(f"'widget['cell_size']' must be a positive integer")

    pos_row: int = int(event.y / widgets['cell_size'])
    pos_col: int = int(event.x / widgets['cell_size'])

    # if pos_row < 0:  # already satisfied
    #     raise ValueError(f"'pos_row' parameter must be a non-negative integer")
    # if pos_col < 0:  # already satisfied
    #     raise ValueError(f"'pos_col' parameter must be a non-negative integer")
    if pos_row > len(matrix) + 1:
        raise ValueError(f"'pos_row' parameter must be lower than list Y-axis")
    if type(matrix[pos_row]) is not list:
        raise TypeError(f"'matrix[{pos_row}]' parameter must be a list, not {type(matrix[pos_row])}")
    if pos_col > len(matrix[pos_row]) + 1:
        raise ValueError(f"'pos_col' parameter must be lower than list X-axis")
    if type(matrix[pos_row][pos_col]) is not bool:
        raise TypeError(f"'matrix[{pos_row}][{pos_col}]' parameter must be a bool, not {type(matrix[pos_col])}")

    if matrix[pos_row][pos_col]:
        matrix[pos_row][pos_col] = False
        draw_cell(widgets, pos_row, pos_col, color_filling='white', color_outline='white')
    else:
        matrix[pos_row][pos_col] = True
        draw_cell(widgets, pos_row, pos_col)


def menu_handler(event) -> None:

    # documentation made by the chat gpt, based on the body of the function, slightly modified
    """
    Event handler function for menu-related events for the screen object.

    Parameters:
    - event: Tkinter event object representing the occurrence of a menu-related event.

    Global Variables:
    - matrix: A 2D list representing the state of cells on the screen.
    - widgets: A dictionary containing configuration parameters, including 'choice', 'screen', and 'start'.

    Returns:
    None

    Description:
    This function is designed to handle events related to menu choices. It updates the screen and configurations
    based on the selected menu choice. The function interacts with the 'model' module, which is assumed to provide
    certain functionalities like filling the matrix randomly and getting a new matrix.

    Menu Choices:
    - 'random': Fills the matrix randomly and sets up the screen for starting the simulation.
    - 'interactive': Prepares the screen for interactive mode by binding mouse click events.

    Note:
    - The 'model' module is assumed to be imported and available in the code.
    - The 'screen_handler' and 'start_handler' functions are assumed to be defined and available.

    Example Usage:
    ```
    # Assuming 'widgets' is a dictionary containing configuration parameters.
    # Binding the function to a menu choice event in a Tkinter application.
    widgets['menu'].bind('<MenuChoice>', menu_handler)
    ```
    """

    if 'matrix' not in globals():
        raise NameError(f"'matrix' name is not defined")
    if 'widgets' not in globals():
        raise NameError(f"'widgets' name is not defined")

    global matrix, widgets

    if type(matrix) is not list:
        raise TypeError(f"'matrix' parameter must be a list, not {type(matrix)}")
    if type(widgets) is not dict:
        raise TypeError(f"'widgets' parameter must be a dict, not {type(widgets)}")
    if 'choice' not in widgets:
        raise KeyError(f"'widgets' dictionary must have 'choice' key")
    if type(widgets['choice']) is not tkinter.StringVar:
        raise TypeError(f"'widgets['choice']' object must be a tkinter.StringVar, not {type(widgets['choice'])}")
    if 'screen' not in widgets:
        raise KeyError(f"'widgets' dictionary must have 'screen' key")
    if type(widgets['screen']) is not tkinter.Canvas:
        raise TypeError(f"'widgets['screen']' object must be a tkinter.Canvas, not {type(widgets['screen'])}")
    if 'model' not in sys.modules:
        raise NameError(f"'model' name is not defined")
    if 'start' not in widgets:
        raise KeyError(f"'widgets' dictionary must have 'start' key")
    if type(widgets['start']) is not tkinter.Button:
        raise TypeError(f"'widgets['start']' object must be a tkinter.Button, not {type(widgets['start'])}")

    choice = widgets['choice'].get()

    # Clear the screen before processing the menu choice  # <- from chat gpt
    clear_screen(widgets)

    if choice == 'random':
        widgets['screen'].unbind('<Button-1>')
        # Fill the matrix randomly using the 'model' module  # <- from chat gpt
        model.fill_matrix_randomly(matrix)
        # Draw the initial generation on the screen  # <- from chat gpt
        draw_generation(matrix, widgets)
        widgets['start'].bind('<Button-1>', start_handler)
        widgets['start'].configure(text='Start')
        widgets['start'].configure(state='active')
    elif choice == 'interactive':
        # Get a new matrix for interactive mode  # <- from chat gpt
        matrix = model.get_new_matrix(len(matrix), len(matrix[0]))
        widgets['screen'].bind('<Button-1>', screen_handler)
        widgets['start'].bind('<Button-1>', start_handler)
        widgets['start'].configure(text='Start')
        widgets['start'].configure(state='active')
    else:
        raise ValueError(f"'widgets['choice']' value must be 'random' or 'interactive', not {widgets['choice']}")


def start_handler(event) -> None:

    # documentation made by the chat gpt, based on the body of the function, slightly modified
    """
    Event handler function for starting or pausing a simulation.

    Parameters:
    - event: Tkinter event object representing the occurrence of a start button click event.

    Global Variables:
    - matrix: A 2D list representing the state of cells on the screen.
    - widgets: A dictionary containing configuration parameters, including 'menu', 'screen', 'start', and 'choice'.

    Returns:
    None

    Description:
    This function is designed to handle events related to starting or pausing a simulation. It toggles between
    starting and pausing the simulation based on the current state of the start button. During the simulation,
    it disables the menu and screen interaction as well.

    Note:
    - The 'progress' function is assumed to be defined and available in the code.
    - The 'screen_handler' function is assumed to be defined and available.

    Example Usage:
    ```
    # Assuming 'widgets' is a dictionary containing configuration parameters.
    # Binding the function to a start button click event in a Tkinter application.
    widgets['start'].bind('<Button-1>', start_handler)
    ```
    """

    if 'matrix' not in globals():
        raise NameError(f"'matrix' name is not defined")
    if 'widgets' not in globals():
        raise NameError(f"'widgets' name is not defined")

    global matrix, widgets

    if type(matrix) is not list:
        raise TypeError(f"'matrix' parameter must be a list, not {type(matrix)}")
    if type(widgets) is not dict:
        raise TypeError(f"'widgets' parameter must be a dict, not {type(widgets)}")
    if 'start' not in widgets:
        raise KeyError(f"'widgets' dictionary must have 'start' key")
    if type(widgets['start']) is not tkinter.Button:
        raise TypeError(f"'widgets['start']' object must be a tkinter.Button, not {type(widgets['start'])}")
    if 'menu' not in widgets:
        raise KeyError(f"'widgets' dictionary must have 'menu' key")
    if type(widgets['menu']) is not tkinter.OptionMenu:
        raise TypeError(f"'widgets['menu']' object must be a tkinter.OptionMenu, not {type(widgets['menu'])}")
    if 'screen' not in widgets:
        raise KeyError(f"'widgets' dictionary must have 'screen' key")
    if type(widgets['screen']) is not tkinter.Canvas:
        raise TypeError(f"'widgets['screen']' object must be a tkinter.Canvas, not {type(widgets['screen'])}")
    if 'choice' not in widgets:
        raise KeyError(f"'widgets' dictionary must have 'choice' key")
    if type(widgets['choice']) is not tkinter.StringVar:
        raise TypeError(f"'widgets['choice']' object must be a tkinter.StringVar, not {type(widgets['choice'])}")

    if widgets['start'].cget('text') == 'Start':
        # Disable the menu and unbind the screen events during the simulation  # <- from chat gpt
        widgets['menu'].configure(state='disabled')
        widgets['screen'].unbind('<Button-1>')
        widgets['start'].configure(text='Pause')
        # Start the simulation  # <- from chat gpt
        progress()
    elif widgets['start'].cget('text') == 'Pause':
        # Enable the menu and bind screen events if in interactive mode  # <- from chat gpt
        widgets['menu'].configure(state='active')
        if widgets['choice'].get() == 'interactive':
            widgets['screen'].bind('<Button-1>', screen_handler)
        widgets['start'].configure(text='Start')
