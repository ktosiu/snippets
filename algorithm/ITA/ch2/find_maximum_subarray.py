# The simple brute force algorithm to find the maximum subarray
def naive_algorithm(A):
    (l, h, max_sum) = (0, 0, 0)
    for i in range(0, len(A)):
        for j in range(i+1, len(A)):
            sum = 0
            for k in range(i, j+1):
                sum += A[k]
            if sum > max_sum:
                (l, h, max_sum) = (i, j, sum)

    return (l, h, max_sum)

# Divid and conquer version
def find_max_crossing_subarray(A, low, mid, high):
    left_sum = A[low]
    sum = 0
    max_left = low
    for i in range(mid, low-1, -1):
        sum += A[i]
        if sum > left_sum:
            left_sum = sum
            max_left = i

    right_sum = A[high]
    sum = 0
    max_right = mid
    for i in range(mid+1, high+1):
        sum += A[i]
        if sum > right_sum:
            right_sum = sum
            max_right = i

    return (max_left, max_right, left_sum + right_sum)

def find_maximum_subarray(A, low, high):
    if high == low:
        return (low, high, A[low])
    else:
        mid = (low + high)/2
        (left_low, left_high, left_sum) = find_maximum_subarray(A, low, mid)
        (right_low, right_high, right_sum) = find_maximum_subarray(A, mid+1, high)
        (cross_low, cross_high, cross_sum) = find_max_crossing_subarray(A, low, mid, high)
        if left_sum >= right_sum and left_sum >= cross_sum:
            return (left_low, left_high, left_sum)
        elif right_sum >= left_sum and right_sum >= cross_sum:
            return (right_low, right_high, right_sum)
        else:
            return (cross_low, cross_high, cross_sum)

data = [13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7]
print naive_algorithm(data)

print find_maximum_subarray(data, 0, len(data) - 1)
