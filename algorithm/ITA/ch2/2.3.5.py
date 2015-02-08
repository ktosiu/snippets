# Binary search. if not found return -1
def binary_search(A, p, q, v):
    if p > q:
        return -1

    mid = (p + q) /2
    if A[mid] < v:
        return binary_search(A, mid+1, q, v)
    elif A[mid] > v:
        return binary_search(A, p, mid-1, v)
    else:
       return mid

# The iterative version of binary search algorithm
def binary_search_iterative(A, p, q, v):
    while(p <= q):
        mid = (p + q)/2
        if A[mid] < v:
            p = mid + 1
        elif A[mid] > v:
            q = mid - 1
        else:
            return mid
    return -1

sorted = [1,2,3,4,5,6,7,8,9]
print binary_search(sorted, 0, len(sorted)-1, 5)
print binary_search(sorted, 0, len(sorted)-1, 10)

print binary_search_iterative(sorted, 0, len(sorted)-1, 5)
print binary_search_iterative(sorted, 0, len(sorted)-1, 10)
