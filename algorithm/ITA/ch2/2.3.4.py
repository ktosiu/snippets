# Recursive version of insertion sort
def insertion_sort(A, n):
    if n <= 0:
        return
    insertion_sort(A, n-1)
    key = A[n]
    i = n-1
    while i >= 0 and A[i] > key:
        A[i+1] = A[i]
        i = i - 1
    A[i+1] = key

data = [9, 8, 7, 6, 5, 4, 3, 2, 1]
insertion_sort(data, len(data)-1)
print data
