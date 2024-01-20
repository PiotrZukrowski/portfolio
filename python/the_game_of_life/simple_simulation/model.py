"""
The Game of Life.
The model part of the MVC programming pattern.
"""


import random


def get_new_matrix(max_row: int, max_col: int) -> list[list[bool]]:

    """
    Return a fresh matrix of the given size.

    :param max_row: The Y-axis capacity.
    :param max_col: The X-axis capacity.
    :return: A table containing pairs of cell coordinates.
    """

    if type(max_row) is not int:
        raise TypeError(f"'max_row' parameter must be an int, not {type(max_row)}'")
    if type(max_col) is not int:
        raise TypeError(f"'max_row' parameter must be an int, not {type(max_col)}'")
    if max_row < 1:
        raise ValueError(f"'max_row' parameter must be greater than zero")
    if max_col < 1:
        raise ValueError(f"'max_col' parameter must be greater than zero")

    matrix: list[list[bool]] = []
    for _ in range(max_row):
        matrix.append([False] * max_col)
    return matrix


def fill_matrix_randomly(matrix: list[list[bool]]) -> None:

    """
    Assign random values to matrix cells.
    In-place (i.e. the matrix itself is modified).

    :param matrix: The table containing pairs of cell coordinates.
    :return: None.
    """

    if type(matrix) is not list:
        raise TypeError(f"'matrix' parameter must be a list, not {type(matrix)}'")

    for i in range(len(matrix)):
        for j in range(len(matrix[i])):
            matrix[i][j]: bool = random.choice((False, True))


def get_next_generation(matrix: list[list[bool]]) -> list[list[bool]]:

    """
    Return a new matrix with a next generation based on the given old matrix.

    :param matrix: The table containing old pairs of cell coordinates.
    :return: A table containing new pairs of cell coordinates.
    """

    if type(matrix) is not list:
        raise TypeError(f"'matrix' parameter must be a list, not {type(matrix)}'")

    matrix_new: list[list[bool]] = []
    for i in range(len(matrix)):
        matrix_new.append(matrix[i].copy())

    for i in range(len(matrix)):
        for j in range(len(matrix[i])):
            update_cell(matrix, matrix_new, i, j)
    return matrix_new


def update_cell(matrix_old: list[list[bool]],
                matrix_new: list[list[bool]],
                pos_row: int,
                pos_col: int) -> None:

    """
    Assign a value to the given cell, based on neighbours values.
    In-place (i.e. the matrix itself is modified).

    :param matrix_old: The table containing old pairs of cell coordinates.
    :param matrix_new: The table containing new pairs of cell coordinates.
    :param pos_row: The index of the row.
    :param pos_col: The index of the column.
    :return: None.
    """

    if type(matrix_old) is not list:
        raise TypeError(f"'matrix_old' parameter must be a list, not {type(matrix_old)}")
    if type(matrix_new) is not list:
        raise TypeError(f"'matrix_new' parameter must be a list, not {type(matrix_new)}")
    if type(pos_row) is not int:
        raise TypeError(f"'pos_row' parameter must be an int, not {type(pos_row)}")
    if type(pos_col) is not int:
        raise TypeError(f"'pos_col' parameter must be an int, not {type(pos_col)}")
    if pos_row < 0:
        raise ValueError(f"'pos_row' parameter must be a non-negative integer")
    if pos_col < 0:
        raise ValueError(f"'pos_col' parameter must be a non-negative integer")
    if pos_row > len(matrix_new) + 1:
        raise ValueError(f"'pos_row' parameter must be lower than list Y-axis")
    if pos_col > len(matrix_new[0]) + 1:
        raise ValueError(f"'pos_col' parameter must be lower than list X-axis")

    old_value: bool = matrix_old[pos_row][pos_col]
    counter: int = get_neighbours_counter(matrix_old, pos_row, pos_col)
    if not old_value and counter == 3:
        matrix_new[pos_row][pos_col]: bool = True
    elif old_value:
        if counter < 2:
            matrix_new[pos_row][pos_col]: bool = False
        # elif counter == 2 or counter == 3:  # value is already True, update is not needed
        if counter > 3:
            matrix_new[pos_row][pos_col]: bool = False


def get_neighbours_counter(matrix: list[list[bool]], pos_row, pos_col) -> int:

    """
    Return a number of neighbours to the given cell.
    Assume the torus shape.

    :param matrix: The table containing pairs of cell coordinates.
    :param pos_row: Index of the row.
    :param pos_col: Index of the column.
    :return: A number of neighbours.
    """

    if type(matrix) is not list:
        raise TypeError(f"'matrix' parameter must be a list, not {type(matrix)}")
    if type(pos_row) is not int:
        raise TypeError(f"'pos_row' parameter must be an int, not {type(pos_row)}")
    if type(pos_col) is not int:
        raise TypeError(f"'pos_col' parameter must be an int, not {type(pos_col)}")
    if pos_row < 0:
        raise ValueError(f"'pos_row' parameter must be a non-negative integer")
    if pos_col < 0:
        raise ValueError(f"'pos_col' parameter must be a non-negative integer")
    if pos_row > len(matrix) + 1:
        raise ValueError(f"'pos_row' parameter must be lower than list Y-axis")
    if pos_col > len(matrix[0]) + 1:
        raise ValueError(f"'pos_col' parameter must be lower than list X-axis")

    row_len: int = len(matrix)
    col_len: int = len(matrix[pos_row])

    return sum([matrix[pos_row - 1][pos_col - 1],
                matrix[pos_row - 1][pos_col],
                matrix[pos_row - 1][(pos_col + 1) % col_len],
                matrix[pos_row][pos_col - 1],
                matrix[pos_row][(pos_col + 1) % col_len],
                matrix[(pos_row + 1) % row_len][pos_col - 1],
                matrix[(pos_row + 1) % row_len][pos_col],
                matrix[(pos_row + 1) % row_len][(pos_col + 1) % col_len]])


def test():

    # sunny day
    max_row: int = 100
    print(f'{max_row = }')
    max_col: int = 100
    print(f'{max_col = }')
    matrix: list[list[bool]] = get_new_matrix(max_row, max_col)
    print(f'{matrix = }')

    # proceed with randomize
    print('fill_matrix_randomly(matrix)'); fill_matrix_randomly(matrix)
    print(f'{matrix = }')

    # proceed with nex generation
    print('matrix: list[list[bool]] = get_next_generation(matrix)'); matrix: list[list[bool]] = get_next_generation(matrix)
    print(f'{matrix = }')


if __name__ == '__main__':
    test()
