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
    for i in range(len(matrix)):
        if type(matrix[i]) is not list:
            raise TypeError(f"'matrix[{i}]' parameter must be a list, not {type(matrix[i])}")
        for j in range(len(matrix[i])):
            if type(matrix[i][j]) is not bool:
                raise TypeError(f"'matrix[{i}][{j}]' parameter must be a bool, not {type(matrix[i])}")
    if type(cell_size) is not int:
        raise TypeError(f"'cell_size' parameter must be an int, not {type(cell_size)}")
    if cell_size < 1:
        raise ValueError(f"'cell_size' parameter must be greater than zero")

    view = dict()
    view['cell_size'] = cell_size

    view['root'] = tkinter.Tk()
    view['root'].title('The Game of Life')
    view['root'].resizable(False, False)

    view['screen'] = tkinter.Canvas(view['root'],
                                    height=len(matrix) * cell_size,
                                    width=len(matrix[0]) * cell_size,
                                    borderwidth=0,
                                    highlightthickness=0,
                                    bg='white')
    view['screen'].grid(row=1, columnspan=2, padx=20, pady=20)

    view['options'] = ['random', 'interactive']
    view['choice'] = tkinter.StringVar(view['root'])
    view['choice'].set('not selected')
    view['menu'] = tkinter.OptionMenu(view['root'],
                                      view['choice'],
                                      # 'not selected',
                                      *view['options'])
    view['menu'].config(width=20)
    view['menu'].grid(row=0, column=0, padx=20)

    view['start'] = tkinter.Button(view['root'], text='Start', width=12)
    view['start'].grid(row=0, column=1, sticky='W', padx=20, pady=20)
    view['start'].configure(state='disabled')

    view['root'].update()
    return view


def mainloop():
    tkinter.mainloop()
