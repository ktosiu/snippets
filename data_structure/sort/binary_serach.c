#include <stdio.h>
#include <assert.h>

int binary_search(int* a, int key, int begin, int end)
{
    assert(a != 0);
    if(end < begin)
        return -1;

    int mid = (begin + end)/2;
    if(key < a[mid])
    {
        return binary_search(a, key,begin, mid-1);
    }
    else if(key > a[mid])
    {
        return binary_search(a, key, mid+1, end);
    }
    else
    {
        return mid;
    }
}

int binary_search_iter(int* a, int key, int begin, int end)
{
    while(begin <= end)
    {
        int mid = (begin + end)/2;
        if(key == a[mid])
            return mid;
        else if(key < a[mid])
        {
            end = mid - 1;
        }
        else
        {
            begin = mid + 1;
        }
    }

    return -1;
}

int main()
{
    int a[10] = {1,2,3,4,5,6,7,8,9,10};

    int i = binary_search(a, 5, 0, 9);
    printf("%d\n", i);

    i = binary_search_iter(a, 5, 0, 9);
    printf("%d\n", i);
    return 0;
}
