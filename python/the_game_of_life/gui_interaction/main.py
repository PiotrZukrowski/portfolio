"""
The Game of Life.
A presentation of an example.
"""


import controller


if __name__ == '__main__':

    max_row: int = 100
    max_col: int = 100
    cell_size: int = 5
    cycles: int = 100

    controller.setup(max_row, max_col, cell_size)
    controller.mainloop()
