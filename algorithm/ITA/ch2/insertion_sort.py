def insertion_sort(A):
    n = len(A)
    for i in range(1, n):
        key = A[i]
        j = i - 1
        while j >= 0 and A[j] > key:
            A[j+1] = A[j]
            j = j - 1
        A[j+1] = key

unsorted_data = [3, 4, 1, 6, 9, 2, 7]
insertion_sort(unsorted_data)
print unsorted_data

data = []
insertion_sort(data)
print data
