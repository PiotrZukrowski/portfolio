"""
The Game of Life.
An interactive presentation.

Presentation of the implementing simulation skill.

Presentation of the basic working with graphical interface skill:
- Drawing on the screen.
- Handling input from the user.
- Designing and implementing multiple graphical objects changes after single signal.
"""


import controller


if __name__ == '__main__':

    max_row: int = 100
    max_col: int = 100
    cell_size: int = 5
    cycles: int = 100

    controller.setup(max_row, max_col, cell_size)
    controller.mainloop()
