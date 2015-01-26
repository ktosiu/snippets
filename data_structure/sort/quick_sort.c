#include <stdio.h>
#include <assert.h>

void swap(int* a, int* b)
{
    int temp = *a;
    *a = * b;
    *b = temp;
}

/*range [lo, hi]*/
int partition(int* a, int lo, int hi)
{
    assert(lo <= hi);

    /*Choos the pivot*/
    int pivotIndex = (lo + hi)/2;
    int pivotValue = a[pivotIndex];
    swap(&a[pivotIndex], &a[hi]);
    int storeIndex = lo;
    for(int i = lo; i < hi; i++)
    {
        if(a[i] < pivotValue)
        {
            swap(&a[i], &a[storeIndex]);
            storeIndex++;
        }
    }
    swap(&a[storeIndex], &a[hi]);
    return storeIndex;
}

void quicksort(int* a, int lo, int hi)
{
    if(lo < hi)
    {
        int p = partition(a, lo, hi);
        quicksort(a, lo, p-1);
        quicksort(a, p+1, hi);
    }
}

void print_array(int* a, int len)
{
    for(int i = 0; i < len; i++)
        printf("%d ", a[i]);
    printf("\n");
}

int main()
{
    int a[10] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};

    quicksort(a, 0, 9);
    print_array(a, 10);

    return 0;
}
