# Merge procedure to merge A[p, q] and A[q+1, r]
def merge(A, p, q, r):
    L, R = [], []
    for i in range(p, q+1):
        L.append(A[i])
    for i in range(q+1, r+1):
        R.append(A[i])

    i, j = 0, 0
    k = p
    while i < len(L) and j < len(R):
        if L[i] < R[j]:
            A[k] = L[i]
            i = i + 1
            k = k + 1
        else:
            A[k] = R[j]
            j = j + 1
            k = k + 1

    while i < len(L):
        A[k] = L[i]
        i = i + 1
        k = k + 1

    while j < len(R):
        A[k] = R[j]
        j = j + 1
        k = k + 1

def merge_sort(A, p, r):
    if p < r:
        q = (p + r) / 2
        merge_sort(A, p, q)
        merge_sort(A, q+1, r)
        merge(A, p, q, r)

# Test
data = [1, 3, 5, 7, 9, 2, 4, 6, 8, 10]
merge_sort(data, 0, len(data) - 1)
print data
