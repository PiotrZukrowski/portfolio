"""
The Game of Life.
A presentation of an example.
"""


import model
import view
import controller


if __name__ == '__main__':

    max_row: int = 100
    max_col: int = 100
    cell_size: int = 5
    cycles: int = 100

    matrix: list[list[bool]] = model.get_new_matrix(max_row, max_col)
    model.fill_matrix_randomly(matrix)
    widgets: dict = view.setup(matrix, cell_size)
    controller.draw_generation(matrix, widgets)
    controller.simulate(matrix, widgets, cycles)
    view.mainloop()
