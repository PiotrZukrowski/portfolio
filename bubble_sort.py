

def bubble_sort(iterable, reverted=False):
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
