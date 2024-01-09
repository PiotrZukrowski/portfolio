"""
Sorting function based on bubble sort algorithm.
"""

def bubble_sort(iterable, reverted: bool = False):

    """
    Sort iterable in-place (i.e. the list itself is modified), stable (i.e. the
        order of two equal elements is maintained) and return sorted.

    :param iterable: Data
    :param reverted: Indicate descending order
    :return: Sorted iterable
    """

    if not hasattr(iterable, '__iter__'):
        raise TypeError(f"'{type(iterable).__name__}' object is not iterable")
    if not hasattr(iterable, '__len__'):
        raise TypeError(f"'{type(iterable).__name__}' object does not define '__len__' operator")
    if not reverted and not hasattr(iterable, '__gt__'):
        raise TypeError(f"'{type(iterable).__name__}' object does not define '__gt__' operator")
    if reverted and not hasattr(iterable, '__lt__'):
        raise TypeError(f"'{type(iterable).__name__}' object does not define '__lt__' operator")

    length: int = len(iterable)
    for i in range(length - 1):
        is_ongoing: bool = False
        for j in range(length - 1 - i):
            if iterable[j] > iterable[j+1] if not reverted else iterable[j] < iterable[j+1]:
                iterable[j], iterable[j+1] = iterable[j+1], iterable[j]
                is_ongoing: bool = True
        if not is_ongoing:
            break
    return iterable


if __name__ == '__main__':
    a: list = [0, 2, 1, 3]
    print(f'{a}')
    print(f'{bubble_sort(a) = }')
    print(f'{bubble_sort(a, reverted=True) = }')
    help(__name__)
