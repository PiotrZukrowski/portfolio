"""
A palindrome checker.

Presentation of basic skills:
- Understanding and implementing recursion.
- Accepting parameter based on methods instead of strict type.
- Recognizing requirements for an input data verification.
"""


def get_is_palindrome(sequence) -> bool:

    """
    Return whether the sequence is a palindrome.
    The implementation uses a recursion.

    :param sequence: The data under examination. It must implement methods:
        - __len__()
        - __getitem__()
    :return: An indicator whether the sequence is a palindrome.
    """

    if not hasattr(sequence, '__len__'):
        raise TypeError(f"'{type(sequence).__name__}' object has no length")
    if not hasattr(sequence, '__getitem__'):
        raise TypeError(f"'{type(sequence).__name__}' object is not a sequence")

    if len(sequence) == 0:
        return True
    elif sequence[0] == sequence[-1]:  # potential palindrome
        return get_is_palindrome(sequence[1:-1])  # keep checking
    else:
        return False


def test_sunny_day():
    # documentation written by chat gpt
    """
    Test function for a sunny day scenario with a palindrome string.

    This function tests the `get_is_palindrome` function with a palindrome string.
    It prints the original string and the result of the palindrome check.

    Example:
    --------
    > test_sunny_day()
    sunny day
    s = 'kajak'
    get_is_palindrome(s) = True

    Notes:
    ------
    - Ensure that the get_is_palindrome function is defined before running this test.
    - This test demonstrates a sunny day scenario where the input string is a palindrome.

    Parameters:
    -----------
    - None

    Returns:
    --------
    - None

    """
    print('sunny day')

    # Providing a palindrome string for demonstration purposes  # <- written by chat gpt
    s = 'kajak'
    print(f'{s = }')

    # Checking if the string is a palindrome using the get_is_palindrome function  # <- written by chat gpt
    print(f'{get_is_palindrome(s) = }')


def test_sunny_day_one_letter():
    # documentation written by chat gpt
    """
    Test function for a sunny day scenario with a one-letter string.

    This function tests the `get_is_palindrome` function with a one-letter string.
    It prints the original string and the result of the palindrome check.

    Example:
    --------
    > test_sunny_day_one_letter()
    sunny day - one letter
    s = 'k'
    get_is_palindrome(s) = True

    Notes:
    ------
    - Ensure that the get_is_palindrome function is defined before running this test.
    - This test demonstrates a sunny day scenario where the input string consists of only one letter.

    Parameters:
    -----------
    - None

    Returns:
    --------
    - None

    """
    print('sunny day - one letter')

    # Providing a one-letter string for demonstration purposes  # <- written by chat gpt
    s = 'k'
    print(f'{s = }')

    # Checking if the string is a palindrome using the get_is_palindrome function  # <- written by chat gpt
    print(f'{get_is_palindrome(s) = }')


def test_sunny_day_diff_type():
    # documentation written by chat gpt
    """
    Test function for a sunny day scenario with a non-string input.

    This function tests the `get_is_palindrome` function with a non-string input.
    It prints the original input and the result of the palindrome check.

    Example:
    --------
    > test_sunny_day_diff_type()
    sunny day - non-string input
    l = [0, 1, 0]
    get_is_palindrome(l) = True

    Notes:
    ------
    - Ensure that the get_is_palindrome function is defined before running this test.
    - This test demonstrates a sunny day scenario where the input is a non-string iterable (list).

    Parameters:
    -----------
    - None

    Returns:
    --------
    - None

    """
    print('sunny day - non-string input')

    # Providing a non-string iterable (list) for demonstration purposes  # <- written by chat gpt
    l = [0, 1, 0]
    print(f'{l = }')

    # Checking if the input is a palindrome using the get_is_palindrome function  # <- written by chat gpt
    print(f'{get_is_palindrome(l) = }')


def test_documentation():
    # documentation written by chat gpt
    """
    Test function for printing module documentation using the help function.

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


def test_rainy_day_even():
    # documentation written by chat gpt
    """
    Test function for a rainy day scenario with a string of even length.

    This function tests the `get_is_palindrome` function with a string of even length.
    It prints the original string and the result of the palindrome check.

    Example:
    --------
    > test_rainy_day_even()
    rainy day - even number of elements
    s = 'kaja'
    get_is_palindrome(s) = False

    Notes:
    ------
    - Ensure that the get_is_palindrome function is defined before running this test.
    - This test demonstrates a rainy day scenario where the input string has an even number of elements.

    Parameters:
    -----------
    - None

    Returns:
    --------
    - None

    """
    print('rainy day - even number of elements')

    # Providing a string of even length for demonstration purposes  # <- written by chat gpt
    s = 'kaja'
    print(f'{s = }')

    # Checking if the string is a palindrome using the get_is_palindrome function  # <- written by chat gpt
    print(f'{get_is_palindrome(s) = }')


def test_rainy_day_odd():
    # documentation written by chat gpt
    """
    Test function for a rainy day scenario with a string of odd length.

    This function tests the `get_is_palindrome` function with a string of odd length.
    It prints the original string and the result of the palindrome check.

    Example:
    --------
    > test_rainy_day_odd()
    rainy day - odd number of elements
    s = 'kaj'
    get_is_palindrome(s) = False

    Notes:
    ------
    - Ensure that the get_is_palindrome function is defined before running this test.
    - This test demonstrates a rainy day scenario where the input string has an odd number of elements.

    Parameters:
    -----------
    - None

    Returns:
    --------
    - None

    """
    print('rainy day - odd number of elements')

    # Providing a string of odd length for demonstration purposes  # <- written by chat gpt
    s = 'kaj'
    print(f'{s = }')

    # Checking if the string is a palindrome using the get_is_palindrome function  # <- written by chat gpt
    print(f'{get_is_palindrome(s) = }')


def test_rainy_wrong_type():
    # documentation written by chat gpt
    """
    Test function for a rainy day scenario with an input of incorrect type.

    This function tests the `get_is_palindrome` function with an input of incorrect type.
    It prints the original input and catches the TypeError that is expected to be raised,
    then prints the error message.

    Example:
    --------
    > test_rainy_wrong_type()
    rainy day - odd number of elements
    o = <object object at 0x...>
    error = TypeError("Input must be a string or an iterable of characters.")

    Notes:
    ------
    - Ensure that the get_is_palindrome function is defined before running this test.
    - This test demonstrates a rainy day scenario where the input is of incorrect type.

    Parameters:
    -----------
    - None

    Returns:
    --------
    - None

    """
    print('rainy day - odd number of elements')

    # Providing an object for demonstration purposes  # <- written by chat gpt
    o = object()
    print(f'{o = }')

    try:
        # Attempting to check if the object is a palindrome using the get_is_palindrome function  # <- written by chat gpt
        print(f'{get_is_palindrome(o) = }')
    except TypeError as error:
        # Catching and printing the expected TypeError  # <- written by chat gpt
        print(f'{error = }')


if __name__ == '__main__':

    test_sunny_day(); print()
    test_sunny_day_one_letter(); print()
    test_sunny_day_diff_type(); print()
    test_documentation(); print()

    test_rainy_day_even(); print()
    test_rainy_day_odd(); print()
    test_rainy_wrong_type()
