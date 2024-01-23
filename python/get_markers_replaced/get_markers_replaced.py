"""
A parser replacing markers from a string.

Presentation of basic skill:
- Working with files.
- Splitting tasks into separate functions.
"""


import os.path


def get_markers_replaced(string: str, markers: list[str]):

    """
    Return a copy of the given string with markers replaced with user input.
    Assume natural language - markers correspond to whole words,
        may be prefixed by a whitespace character,
        and may be postfixed by a whitespace character or a sequence generated from ',.?!;'.
    Every whitespace character sequence is replaced with a single space.

    :param string: The data under parsing.
    :param markers: The sequence of words searched for in the string.
    :return: An updated copy of text.
    """

    if not type(string) is str:
        raise TypeError(f"'{type(string).__name__}' object is not a string")
    if not hasattr(markers, '__contains__'):
        raise TypeError(f"'{type(markers).__name__}' object does not define '__contains__' operator")

    text_new: str = ''
    words: list[str] = string.split()

    for word in words:
        stripped: str = word.rstrip(',.?!;')
        if stripped in markers:
            text_new += input(f'Provide {stripped}: ') + word[len(stripped):] + ' '
        else:
            text_new += word + ' '

    return text_new[:-1]


def parse_file(file_path: str,  markers: list[str]) -> str:

    """
    Load a text file.
    Replace markers with user input.
    Return an updated text as a copy.
    Assume natural language - markers correspond to whole words,
        may be prefixed by a whitespace character,
        and may be postfixed by a whitespace character or a sequence generated from ',.?!;'.
    Every whitespace character sequence is replaced with a single space.

    :param file_path: The location of the data under parsing.
    :param markers: The sequence of words searched for in the text.
    :return: An updated copy of the text.
    """

    if not type(file_path) is str:
        raise TypeError(f"'{type(file_path).__name__}' object is not a string")
    if not os.path.isfile(file_path):
        raise FileNotFoundError(f"{file_path} is not a valid file path")
    if not hasattr(markers, '__contains__'):
        raise TypeError(f"'{type(markers).__name__}' object does not define '__contains__' operator")

    text: str = ''

    try:
        file = open(file_path, 'r')
        for line in file:
            text += get_markers_replaced(line, markers) + '\n'
        file.close()
    except FileNotFoundError as error:
        raise FileNotFoundError(f"function 'parse_file' parameter 'file_path': {error}") from error
    except IsADirectoryError as error:
        raise IsADirectoryError(f"function 'parse_file' parameter 'file_path': {error}") from error
    except PermissionError as error:
        raise PermissionError(f"function 'parse_file' parameter 'file_path': {error}") from error
    except ValueError as error:
        raise ValueError(f"function 'parse_file' parameter 'file_path': {error}") from error

    return text


def test_sunny_day():
    # documentation written by chat gpt
    """
    Test function for a sunny day scenario of parsing a file with specified markers.

    This function tests the `parse_file` function in a sunny day scenario by providing a list of markers
    and a valid file path. It prints the markers and file path, then prints the result of parsing the file.

    Example:
    --------
    > test_sunny_day()
    sunny day
    markers = ['NOUN', 'VERB', 'ADJECTIVE']
    file_path = 'lorem.txt'
    Parsed content: {'NOUN': 12, 'VERB': 8, 'ADJECTIVE': 5}

    Notes:
    ------
    - Ensure that the parse_file function is defined before running this test.
    - This test demonstrates a sunny day scenario where the parse_file function successfully parses the file.

    Parameters:
    -----------
    - None

    Returns:
    --------
    - None

    """
    print('sunny day')

    # Providing a list of markers and a valid file path for demonstration purposes  # <- written by chat gpt
    markers: list[str] = ['NOUN', 'VERB', 'ADJECTIVE']
    print(f'{markers = }')

    file_path: str = 'lorem.txt'
    print(f'{file_path = }')

    # Parsing the file with specified markers and printing the result  # <- written by chat gpt
    print(parse_file(file_path, markers))


def test_rainy_day_wrong_path():
    # documentation written by chat gpt
    """
    Test function for a rainy day scenario with an incorrect file path.

    This function tests the `parse_file` function in a rainy day scenario by providing a list of markers
    and an incorrect file path. It prints the markers and file path, then catches the FileNotFoundError
    that is expected to be raised, and prints the error message.

    Example:
    --------
    > test_rainy_day_wrong_path()
    rainy day - wrong file_path
    markers = ['NOUN', 'VERB', 'ADJECTIVE']
    file_path = '../lorem.txt'
    error = FileNotFoundError("[Errno 2] No such file or directory: '../lorem.txt'")

    Notes:
    ------
    - Ensure that the parse_file function is defined before running this test.
    - This test demonstrates a rainy day scenario where the parse_file function raises a FileNotFoundError
      due to providing an incorrect file path.

    Parameters:
    -----------
    - None

    Returns:
    --------
    - None

    """
    print('rainy day - wrong file_path')

    # Providing a list of markers and an incorrect file path for demonstration purposes  # <- written by chat gpt
    markers: list[str] = ['NOUN', 'VERB', 'ADJECTIVE']
    print(f'{markers = }')

    file_path: str = '../lorem.txt'
    print(f'{file_path = }')

    try:
        # Attempting to parse the file with specified markers and catching the expected FileNotFoundError  # <- written by chat gpt
        print(parse_file(file_path, markers))
    except FileNotFoundError as error:
        # Catching and printing the expected FileNotFoundError  # <- written by chat gpt
        print(f'{error = }')


def test_rainy_day_path_wrong_type():
    # documentation written by chat gpt
    """
    Test function for a rainy day scenario with an incorrect file path type.

    This function tests the `parse_file` function in a rainy day scenario by providing a list of markers
    and an incorrect file path type. It prints the markers and file path, then catches the TypeError
    that is expected to be raised, and prints the error message.

    Example:
    --------
    > test_rainy_day_path_wrong_type()
    rainy day - file_path wrong type
    markers = ['NOUN', 'VERB', 'ADJECTIVE']
    file_path = 0
    error = TypeError("file_path must be a string representing the file path.")

    Notes:
    ------
    - Ensure that the parse_file function is defined before running this test.
    - This test demonstrates a rainy day scenario where the parse_file function raises a TypeError
      due to providing an incorrect type for the file path.

    Parameters:
    -----------
    - None

    Returns:
    --------
    - None

    """
    print('rainy day - file_path wrong type')

    # Providing a list of markers and an incorrect file path type for demonstration purposes  # <- written by chat gpt
    markers: list[str] = ['NOUN', 'VERB', 'ADJECTIVE']
    print(f'{markers = }')

    file_path: int = 0
    print(f'{file_path = }')

    try:
        # Attempting to parse the file with specified markers and catching the expected TypeError  # <- written by chat gpt
        print(parse_file(file_path, markers))
    except TypeError as error:
        # Catching and printing the expected TypeError  # <- written by chat gpt
        print(f'{error = }')


def test_rainy_day_markers_wrong_type():
    # documentation written by chat gpt
    """
    Test function for a rainy day scenario with incorrect markers type.

    This function tests the `parse_file` function in a rainy day scenario by providing incorrect markers type.
    It prints the markers and file path, then catches the TypeError that is expected to be raised, and prints the error message.

    Example:
    --------
    > test_rainy_day_markers_wrong_type()
    rainy day - markers wrong type
    markers = <object object at 0x...>
    file_path = 'lorem.txt'
    error = TypeError("markers must be a list of strings representing part-of-speech tags.")

    Notes:
    ------
    - Ensure that the parse_file function is defined before running this test.
    - This test demonstrates a rainy day scenario where the parse_file function raises a TypeError
      due to providing an incorrect type for the markers.

    Parameters:
    -----------
    - None

    Returns:
    --------
    - None

    """
    print('rainy day - markers wrong type')

    # Providing incorrect markers type (object) for demonstration purposes  # <- written by chat gpt
    markers = object()
    print(f'{markers = }')

    file_path: str = 'lorem.txt'
    print(f'{file_path = }')

    try:
        # Attempting to parse the file with specified markers and catching the expected TypeError  # <- written by chat gpt
        print(parse_file(file_path, markers))
    except TypeError as error:
        # Catching and printing the expected TypeError  # <- written by chat gpt
        print(f'{error = }')


if __name__ == '__main__':

    test_sunny_day(); print()

    test_rainy_day_wrong_path(); print()
    test_rainy_day_path_wrong_type(); print()
    test_rainy_day_markers_wrong_type()
