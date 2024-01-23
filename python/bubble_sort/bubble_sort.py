"""
The Bubble Sort Algorithm.

A sorting function based on the bubble sort algorithm.

Presentation of working with algorithms on basic level:
- Understanding abstraction.
- Implementing architecture.
- Optimizing performance.

Presentation of basic skills:
- Accepting parameter based on methods instead of strict type.
- Recognizing additional options of high value for users.
- Recognizing requirements for an input data verification.
"""


def bubble_sort(iterable, reverse: bool = False):

    """
    Sort the iterable in-place (i.e. the list itself is modified).
    Stable (i.e. the order of two equal elements is maintained).
    Return a sorted iterable.

    :param iterable: The data to be sorted.
    :param reverse: The flag can be set to sort in descending order.
    :return: A sorted iterable.
    """

    if not hasattr(iterable, '__len__'):
        raise TypeError(f"'{type(iterable).__name__}' object does not define '__len__' operator")
    if not hasattr(iterable, '__getitem__'):
        raise TypeError(f"'{type(iterable).__name__}' object does not define '__getitem__' operator")
    if not reverse and not hasattr(iterable, '__gt__'):
        raise TypeError(f"'{type(iterable).__name__}' object does not define '__gt__' operator")
    if reverse and not hasattr(iterable, '__lt__'):
        raise TypeError(f"'{type(iterable).__name__}' object does not define '__lt__' operator")

    length: int = len(iterable)
    for i in range(length - 1):
        is_ongoing: bool = False
        for j in range(length - 1 - i):
            if iterable[j] > iterable[j+1] if not reverse else iterable[j] < iterable[j+1]:
                iterable[j], iterable[j+1] = iterable[j+1], iterable[j]
                is_ongoing: bool = True
        if not is_ongoing:
            break
    return iterable


def test_sunny_day_ascending():
    # documentation written by chat gpt
    """
    Test function for a sunny day scenario with ascending order using the bubble sort algorithm.

    This function creates a list of integers in random order, prints the original list,
    applies the bubble sort algorithm to sort the list in ascending order, and then prints the sorted list.

    Example:
    --------
    > test_sunny_day_ascending()
    sunny day - ascending
    l = [0, 2, 1, 3]
    bubble_sort(l) = [0, 1, 2, 3]
    l = [0, 1, 2, 3]

    Notes:
    ------
    - Ensure that the bubble_sort function is defined before running this test.
    - The bubble_sort function is expected to sort the list in ascending order in-place.

    Parameters:
    -----------
    - None

    Returns:
    --------
    - None

    """
    print('sunny day - ascending')

    # Creating a list of integers in random order  # <- written by chat gpt
    l = [0, 2, 1, 3]

    # Printing the original list
    print(f'{l = }')

    # Sorting the list in ascending order using the bubble sort algorithm  # <- written by chat gpt
    print(f'{bubble_sort(l) = }')

    # Printing the sorted list  # <- written by chat gpt
    print(f'{l = }')


def test_sunny_day_descending():
    # documentation written by chat gpt
    """
    Test function for a sunny day scenario with descending order using the bubble sort algorithm.

    This function creates a list of integers in random order, prints the original list,
    applies the bubble sort algorithm to sort the list in descending order, and then prints the sorted list.

    Example:
    --------
    > test_sunny_day_descending()
    sunny day - descending
    l = [0, 2, 1, 3]
    bubble_sort(l, reverse=True) = [3, 2, 1, 0]
    l = [3, 2, 1, 0]

    Notes:
    ------
    - Ensure that the bubble_sort function is defined before running this test.
    - The bubble_sort function is expected to sort the list in descending order in-place when the reverse parameter is set to True.

    Parameters:
    -----------
    - None

    Returns:
    --------
    - None

    """
    print('sunny day - descending')

    # Creating a list of integers in random order  # <- written by chat gpt
    l = [0, 2, 1, 3]

    # Printing the original list  # <- written by chat gpt
    print(f'{l = }')

    # Sorting the list in descending order using the bubble sort algorithm  # <- written by chat gpt
    print(f'{bubble_sort(l, reverse=True) = }')

    # Printing the sorted list  # <- written by chat gpt
    print(f'{l = }')


def test_documentation():
    # documentation written by chat gpt
    """
    Test function for printing documentation using the help function.

    This function prints the documentation for the current module (denoted by __name__)
    using the help function. It serves as a demonstration for accessing module-level documentation.

    Example:
    --------
    > test_documentation()
    print documentation
    Help on module __main__:

    ...

    Notes:
    ------
    - The help function is a built-in Python function that provides interactive help on modules, classes, functions, etc.
    - The specific content of the help output will vary based on the module's documentation.

    Parameters:
    -----------
    - None

    Returns:
    --------
    - None

    """
    print('print documentation')
    help(__name__)


def test_rainy_day_insufficient_argument():
    # documentation written by chat gpt
    """
    Test function for a rainy day scenario with insufficient arguments provided to bubble_sort.

    This function attempts to use the bubble_sort function with an insufficient argument (not a list),
    catches the TypeError that is expected to be raised, and prints the error message.

    Example:
    --------
    > test_rainy_day_insufficient_argument()
    rainy day - insufficient argument
    o = <object object at 0x...>
    TypeError('bubble_sort() missing 1 required positional argument: 'l'')

    Notes:
    ------
    - Ensure that the bubble_sort function is defined before running this test.
    - This test demonstrates a rainy day scenario where the bubble_sort function is not provided with a valid list argument.

    Parameters:
    -----------
    - None

    Returns:
    --------
    - None

    """
    print('rainy day - insufficient argument')

    # Creating an object for demonstration purposes  # <- written by chat gpt
    o = object()
    print(f'{o = }')

    try:
        # Attempting to use bubble_sort with an insufficient argument (not a list)  # <- written by chat gpt
        print(f'{bubble_sort(o) = }')  # rainy day scenario, wrong type
    except TypeError as error:
        # Catching and printing the expected TypeError  # <- written by chat gpt
        print(f'{error = }')


if __name__ == '__main__':

    test_sunny_day_ascending(); print()
    test_sunny_day_descending(); print()
    test_documentation(); print()

    test_rainy_day_insufficient_argument()
