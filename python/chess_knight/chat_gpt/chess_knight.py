# refactored and enhanced by chat gpt, based on programmer input and guidance
"""
Chess Knight Module

This module provides classes to simulate the movement of a knight on a chessboard.
It includes a Chessboard class representing the chessboard and a Knight class for the knight's movements.

Classes:
- Chessboard: Represents a chessboard for the knight puzzle.
- Knight: Represents a knight chess piece and its movement on a chessboard.

Usage:
1. Create a Chessboard instance.
2. Create a Knight instance on the chessboard.
3. Retrieve the knight's movement sequence using the get_solution method.

Example:
```python
chessboard = Chessboard()
knight = Knight(chessboard)
solution = knight.get_solution()
if solution:
    for row in solution:
        print(row)
else:
    print("No solution found.")
"""

import unittest

class Chessboard:
    """
    Chessboard class represents a chessboard for the knight puzzle.

    Attributes:
    - size (int): The size of the chessboard.
    - board (list[list[bool | int]]): 2D list representing the chessboard.
    - movements (tuple): Tuple of possible single movements for the knight.
    """

    def __init__(self, size: int = 8):
        """
        Initialize a chessboard with the given size.

        Args:
        - size (int): The size of the chessboard.
        """
        if not isinstance(size, int) or size <= 0:
            raise ValueError("Chessboard size must be a positive integer.")

        self.size = size
        self.board: list[list[bool | int]] = [[False] * size for _ in range(size)]  # Initialize the chessboard
        # ^ type annotation was manually added after chat gpt due to pycharm check failure
        self.movements = ((-2, 1), (-1, 2), (1, 2), (2, 1), (2, -1), (1, -2), (-1, -2), (-2, -1))

    def is_valid_move(self, row: int, col: int) -> bool:
        """
        Check if the given square on the chessboard is available for the knight.

        Args:
        - row (int): Row index of the square.
        - col (int): Column index of the square.

        Returns:
        - bool: True if the square is available, False otherwise.
        """
        if not (isinstance(row, int) and isinstance(col, int)):
            raise ValueError("Row and column must be integers.")

        return 0 <= row < self.size and 0 <= col < self.size and not self.board[row][col]

class Knight:
    """
    Knight class represents a knight chess piece and its movement on a chessboard.

    Attributes:
    - chessboard (Chessboard): The chessboard on which the knight moves.
    - current_position (tuple[int, int]): Current position of the knight on the chessboard.
    - steps (int): Number of steps the knight has taken.
    - solution (list[list[int]] | None): The knight's movement sequence on the chessboard.
    """

    def __init__(self, chessboard: Chessboard, starting_position: tuple[int, int] = (0, 0)):
        """
        Initialize a knight on the given chessboard.

        Args:
        - chessboard (Chessboard): The chessboard on which the knight moves.
        - starting_position (tuple[int, int]): Starting position of the knight.
        """
        if not isinstance(chessboard, Chessboard):
            raise ValueError("Invalid chessboard instance provided.")

        if not isinstance(starting_position, tuple) or len(starting_position) != 2:
            raise ValueError("Starting position must be a tuple of two integers.")

        row, col = starting_position

        if not (isinstance(row, int) and isinstance(col, int)):
            raise ValueError("Row and column must be integers.")

        if not (0 <= row < chessboard.size and 0 <= col < chessboard.size):
            raise ValueError("Starting position is outside the valid range of the chessboard.")

        self.chessboard = chessboard
        self.current_position = starting_position
        self.steps = 0
        self.solution = self.solve()

    def solve(self) -> list[list[int]] | None:
        """
        Find the knight's movement sequence to fill the entire chessboard.

        Returns:
        - list[list[int]] | None: The knight's movement sequence or None if no solution is found.
        """
        result = self._recursive_solve(self.current_position[0], self.current_position[1])
        return result

    def _recursive_solve(self, row: int, col: int) -> list[list[int]] | None:
        """
        Recursively search for a solution starting from the given position.

        Args:
        - row (int): Row index of the current position.
        - col (int): Column index of the current position.

        Returns:
        - list[list[int]] | None: The knight's movement sequence or None if no solution is found.
        """
        if not isinstance(row, int) or not isinstance(col, int):
            raise ValueError("Row and column must be integers.")

        if self.steps == self.chessboard.size ** 2:
            return [row[:] for row in self.chessboard.board]

        if self.chessboard.is_valid_move(row, col):
            self.steps += 1
            self.chessboard.board[row][col] = self.steps
        else:
            return None

        for movement in self.chessboard.movements:
            result = self._recursive_solve(row + movement[0], col + movement[1])
            if result:
                return result

        self.steps -= 1
        self.chessboard.board[row][col] = False
        return None

    def get_solution(self) -> list[list[int]] | None:
        """
        Get the solution of the knight's movement sequence on the chessboard.

        Returns:
        - list[list[int]] | None: The knight's movement sequence or None if no solution is found.
        """
        return self.solution

def presentation() -> None:
    """
    Display a presentation of the chessboard and the knight's movement sequence.
    """
    print('Presentation:')
    chessboard = Chessboard()
    knight = Knight(chessboard)
    solution = knight.get_solution()
    if solution:
        for row in solution:
            print(row)
    else:
        print("No solution found.")

class KnightTest(unittest.TestCase):
    """
    Unit tests for the Knight class.
    """
    model_solution = [[1, 38, 55, 34, 3, 36, 19, 22],
                      [54, 47, 2, 37, 20, 23, 4, 17],
                      [39, 56, 33, 46, 35, 18, 21, 10],
                      [48, 53, 40, 57, 24, 11, 16, 5],
                      [59, 32, 45, 52, 41, 26, 9, 12],
                      [44, 49, 58, 25, 62, 15, 6, 27],
                      [31, 60, 51, 42, 29, 8, 13, 64],
                      [50, 43, 30, 61, 14, 63, 28, 7]]

    def test_sunny_day(self):
        """
        Test the knight's movement on a standard chessboard.
        """
        chessboard = Chessboard()
        knight = Knight(chessboard)
        solution = knight.get_solution()
        self.assertEqual(solution, KnightTest.model_solution)

    def test_start_pos_unavailable(self):
        """
        Test when the starting position of the knight is permanently unavailable.
        """
        chessboard = Chessboard()
        chessboard.is_valid_move = lambda a, b: False  # Inject permanent unavailability
        knight = Knight(chessboard)
        self.assertIsNone(knight.get_solution())

    def test_recursion_none(self):
        """
        Test when there is no recursive solution available.
        """
        chessboard = Chessboard()
        chessboard.size = 2
        chessboard.board = [[False]]
        knight = Knight(chessboard)
        self.assertIsNone(knight.get_solution())

    def test_invalid_chessboard_size(self):
        """
        Test when attempting to create a chessboard with an invalid size.
        """
        with self.assertRaises(ValueError):
            chessboard = Chessboard(size=-1)

    def test_invalid_starting_position_type(self):
        """
        Test when attempting to create a knight with an invalid starting position type.
        """
        chessboard = Chessboard()
        with self.assertRaises(ValueError):
            knight = Knight(chessboard, starting_position="invalid")

    def test_invalid_starting_position_length(self):
        """
        Test when attempting to create a knight with an invalid starting position length.
        """
        chessboard = Chessboard()
        with self.assertRaises(ValueError):
            knight = Knight(chessboard, starting_position=(1, 2, 3))

    def test_starting_position_outside_chessboard(self):
        """
        Test when attempting to create a knight with a starting position outside the chessboard.
        """
        chessboard = Chessboard()
        with self.assertRaises(ValueError):
            knight = Knight(chessboard, starting_position=(10, 5))

if __name__ == '__main__':
    presentation()
    print()
    unittest.main()
