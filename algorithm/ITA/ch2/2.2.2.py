# Selection sort
def selection_sort(A):
    for i in range(0, len(A)):
        k = i
        for j in range(i, len(A)):
            if A[j] < A[k]:
                k = j
        A[i], A[k] = A[k], A[i]

data = [1, 8, 3, 6, 5, 4, 7, 2, 9]
selection_sort(data)
print data
