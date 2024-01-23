"""
The Bubble Sort Algorithm.

A sorting function based on the bubble sort algorithm.

Presentation of working with algorithms on basic level
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


if __name__ == '__main__':
    a: list = [0, 2, 1, 3]
    print(f'{a = }')
    print(f'{bubble_sort(a) = }')
    print(f'{bubble_sort(a, reverse=True) = }')
    help(__name__)

    # rainy day . special
    b = object()
    print(f'{b = }')
    try:
        print(f'{bubble_sort(b) = }')  # rainy day scenario, wrong type
    except TypeError as error:
        print(f'{error = }')
