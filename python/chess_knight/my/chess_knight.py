"""
Chess Knight.
Description option 1: Application filling the chessboard with the knight piece movement sequence, so the whole board is filled.
Description option 2: Application finding steps sequence of the knight chess piece to fill the whole chessboard.
"""
# considered future enhancements
# - configurable attributes at instance initialization
# - configurable square board of any (positive) size
# - configurable rectangle board of any (positive) NxM size
# - configurable regular shape board with any number of dimensions of any sizes
# - configurable irregular shape board, where in each cross-section, the plane may have a different dimension
# - configurable possible single movements, but still in "jumping" convention (step is blocked only by target square availability, not by path availability)
# - configurable starting position
# - configurable starting board (already filled with unavailable squares)
# - configurable attributes at any time (with above configurations finding solution can be "resumed" from any starting state)


import unittest


class Knight:

    __size: int = 8  # chess board size
    # tuple of possible single movements
    __movements = ((-2, 1), (-1, 2), (1, 2), (2, 1), (2, -1), (1, -2), (-1, -2), (-2, -1))
    __starting_position: tuple[int, int] = (0, 0)

    def __init__(self):
        self.__board: list[list[bool | int]] = []  # square marked as free (value False) or with step number
        self.__step: int = 0  # number of steps made so far
        for row_index in range(self.__size):
            self.__board.append(self.__size * [False])
        self.__solution: list[list[int]] | None = self.__solve(self.__starting_position[0],
                                                               self.__starting_position[1])

    def get_solution(self) -> list[list[int]] | None:
        return self.__solution

    def __solve(self, current_row: int, current_col: int) -> list[list[int]] | None:
        """
        Given current state of the chessboard and the knight piece position,
        return final solution or None.
        """

        result: list[list[int]] | None = None

        # check if step can be made into given position
        if self.__get_is_available(current_row, current_col):  # square on chess board is available
            # make a step
            self.__step += 1
            self.__board[current_row][current_col]: int = self.__step
        else:  # square on chess board is unavailable -> leave immediately
            return None
        # final solution is found -> recursion stop condition -> leave immediately
        if self.__step == self.__size ** 2:
            board: list[list[int]] = []
            for row_index in range(self.__size):
                board.append(self.__board[row_index].copy())
            return board

        # current position was available to make a step and final solution is not found yet
        for movement in self.__movements:
            # recursive research for overall solution
            result: list[list[int]] | None = self.__solve(current_row + movement[0], current_col + movement[1])
            if result is not None:  # final solution is found -> leave for loop
                break
        if result is not None:  # recursive research succeeded -> leave recursive instance
            return result
        else:  # recursive research failed -> undo current step
            self.__step -= 1
            self.__board[current_row][current_col]: bool = False
            return None

    def __get_is_available(self, pos_row: int, pos_col: int) -> bool:
        """
        Return whether the given square on the chessboard is available.
        """
        return 0 <= pos_row < self.__size and 0 <= pos_col < self.__size \
            and self.__board[pos_row][pos_col] is False


def presentation() -> None:
    print('presentation:')
    knight: Knight = Knight(); print(f'define: knight: Knight = Knight()')
    solution: list[list[int]] = knight.get_solution()
    print('solution:')
    for row in solution:
        print(row)


class KnightTest(unittest.TestCase):

    __model_solution: list[list[int]] = [[1, 38, 55, 34, 3, 36, 19, 22],
                                         [54, 47, 2, 37, 20, 23, 4, 17],
                                         [39, 56, 33, 46, 35, 18, 21, 10],
                                         [48, 53, 40, 57, 24, 11, 16, 5],
                                         [59, 32, 45, 52, 41, 26, 9, 12],
                                         [44, 49, 58, 25, 62, 15, 6, 27],
                                         [31, 60, 51, 42, 29, 8, 13, 64],
                                         [50, 43, 30, 61, 14, 63, 28, 7]]

    def test_sunny_day(self):
        knight: Knight = Knight()
        solution: list[list[int]] = knight.get_solution()
        self.assertEqual(solution, KnightTest.__model_solution)

    def test_start_pos_unavailable(self):
        knight: Knight = Knight()
        knight._Knight__get_is_available = lambda a, b: None  # inject permanent unavailability
        # force re-evaluation of private attribute via private method
        knight._Knight__solution: None = knight._Knight__solve(knight._Knight__starting_position[0],
                                                               knight._Knight__starting_position[1])
        solution: None = knight.get_solution()
        self.assertEqual(solution, None)

    def test_recursion_none(self):
        knight: Knight = Knight()
        # knight piece specific implementation
        knight._Knight__size: int = 2  # inject illusion of more available squares
        knight._Knight__board: list[list[int]] = [[False]]  # inject chessboard without recursive solution
        # force re-evaluation of private attribute via private method
        knight._Knight__solution: None = knight._Knight__solve(knight._Knight__starting_position[0],
                                                               knight._Knight__starting_position[1])
        solution: None = knight.get_solution()
        self.assertEqual(solution, None)


if __name__ == '__main__':
    presentation()
    print()
    unittest.main()
