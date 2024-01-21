"""
A parser replacing markers from a string.
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


if __name__ == '__main__':

    # sunny day
    markers: list[str] = ['NOUN', 'VERB', 'ADJECTIVE']
    print(f'{markers = }')
    file_path: str = 'lorem.txt'
    print(f'{file_path = }')
    print(parse_file(file_path, markers))

    # rainy day
    file_path_b: str = '../lorem.txt'
    print(f'{file_path_b = }')
    try:
        print(parse_file(file_path_b, markers))  # rainy day scenario, wrong file_path
    except Exception as error:
        print(f'{error = }')
    file_path_c: int = 0
    print(f'{file_path_c = }')
    try:
        print(parse_file(file_path_c, markers))  # rainy day scenario, file_path wrong type
    except Exception as error:
        print(f'{error = }')
    markers_d = object()
    print(f'{markers_d = }')
    try:
        print(parse_file(file_path, markers_d))  # rainy day scenario, marks wrong type
    except Exception as error:
        print(f'{error = }')
