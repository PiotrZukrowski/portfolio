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


if __name__ == '__main__':

    # sunny day
    a = 'kajak'
    print(f'{a = }')
    print(f'{get_is_palindrome(a) = }')  # sunny day scenario
    help(__name__)

    # rainy day
    b = 'kaja'
    print(f'{b = }')
    print(f'{get_is_palindrome(b) = }')  # rainy day scenario, even number of elements
    c = 'kaj'
    print(f'{c = }')
    print(f'{get_is_palindrome(c) = }')  # rainy day scenario, odd number of elements

    # sunny day . special
    d = 'k'
    print(f'{d = }')
    print(f'{get_is_palindrome(d) = }')  # sunny day scenario, one letter
    e = [0, 1, 0]
    print(f'{e = }' )
    print(f'{get_is_palindrome(e) = }')  # sunny day scenario, non-string input

    # rainy day . special
    f = object()
    print(f'{f = }')
    try:
        print(f'{get_is_palindrome(f) = }')  # rainy day scenario, wrong type
    except TypeError as error:
        print(f'{error = }')
