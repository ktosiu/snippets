# Naive algorithm which is O(n^2)
def integers_sum(S, x):
    for i in range(0, len(S)):
        for j in range(i+1, len(S)):
            if S[i] + S[j] == x:
                return True
    return False

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

# A better algorithm
# 1. Sort S. O(n*lgn)
# 2. For each item i in S, use binary_search to find (x-i) in S. O(n*lgn)
def better_algo(S, x):
    S.sort()
    for item in S:
        return binary_search(S, 0, len(S)-1, x-item) != -1

S = [1,2,3,4,5,6,7]
print integers_sum(S, 5)
print integers_sum(S, 8)

print better_algo(S, 5)
print better_algo(S, 50)
