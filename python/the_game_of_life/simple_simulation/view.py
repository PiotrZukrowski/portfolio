"""
The Game of Life.
The view part of the MVC programming pattern.
"""


import tkinter


def setup(matrix: list[list[bool]], cell_size: int) -> dict:

    """
    Return widgets of a view encapsulated in dictionary.

    :param matrix: The table containing pairs of cell coordinates.
    :param cell_size: The square edge length in pixels.
    :return: A dictionary of widgets.
    """

    if type(matrix) is not list:
        raise TypeError(f"'matrix' parameter must be a list, not {type(matrix)}")
    if type(cell_size) is not int:
        raise TypeError(f"'cell_size' parameter must be an int, not {type(cell_size)}")
    if cell_size < 1:
        raise ValueError(f"'cell_size' parameter must be greater than zero")

    view = dict()
    view['cell_size'] = cell_size

    view['root'] = tkinter.Tk()
    view['root'].title('The game of Life')

    view['screen'] = tkinter.Canvas(view['root'],
                                    height=len(matrix) * cell_size,
                                    width=len(matrix[0]) * cell_size,
                                    borderwidth=0,
                                    highlightthickness=0,
                                    bg='white')
    view['screen'].grid(row=1, columnspan=2, padx=20, pady=20)
    # view['screen'].bind('<Button-1>', screen_handler)

    # view['choice'] = tkinter.StringVar(view['root'])
    # view['choice'].set('')
    # view['menu'] = tkinter.OptionMenu(view['root'],
    #                                   view['start_button'],
    #                                   'random',
    #                                   'interactive',
    #                                   command=menu_handler)
    # view['menu'].config(width=20)
    # view['menu'].grid(row=0, column=0, padx=20)
    #
    # view['start_button'] = tkinter.Button(view['root'], text='Start', width=12)
    # view['start_button'].grid(row=0, column=1, sticky='W', padx=20, pady=20)
    # view['start_button'].bind('<Button-1>', start_button_handler)

    view['root'].update()

    return view


def mainloop():
    tkinter.mainloop()
