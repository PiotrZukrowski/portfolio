

def bubble_sort(iterable, reverted=False):

    if not hasattr(iterable, '__iter__'):
        raise TypeError(f"'{type(iterable).__name__}' object is not iterable")
    if not hasattr(iterable, '__len__'):
        raise TypeError(f"'{type(iterable).__name__}' object has not '__len__' operator defined")
    if not reverted and not hasattr(iterable, '__gt__'):
        raise TypeError(f"'{type(iterable).__name__}' object has not '__gt__' operator defined")
    if not reverted and not hasattr(iterable, '__lt__'):
        raise TypeError(f"'{type(iterable).__name__}' object has not '__lt__' operator defined")

    length = len(iterable)
    for i in range(length - 1):
        is_ongoing = False
        for j in range(length - 1 - i):
            if iterable[j] > iterable[j+1] if not reverted else iterable[j] < iterable[j+1]:
                iterable[j], iterable[j+1] = iterable[j+1], iterable[j]
                is_ongoing = True
        if not is_ongoing:
            break
    return iterable


if __name__ == '__main__':
    a = [0, 2, 1, 3]
    print(f'{a}')
    print(f'{bubble_sort(a) = }')
    print(f'{bubble_sort(a, reverted=True) = }')
