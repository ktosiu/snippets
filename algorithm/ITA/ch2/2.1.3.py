def linear_search(A, v):
    for i in range(0, len(A)):
        if A[i] == v:
            return i
    return -1

data = [1,2,3,4,5]
print linear_search(data, 4)
print linear_search(data, 9)
