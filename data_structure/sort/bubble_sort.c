#include <stdio.h>

void bubble_sort(int* array, int len)
{
    int swapped = 0;
    do {
        swapped = 0;
        for(int i = 1; i < len; i++)
        {
            if(array[i-1] > array[i])
            {
                int temp = array[i];
                array[i] = array[i-1];
                array[i-1] = temp;
                swapped = 1;
            }
        }
    }
    while(swapped);
}

int main()
{
    int a[10] = {4, 5, 2, 1, 15, 6, 90, 33, 22, 55};
    bubble_sort(a, 10);
    for(int i = 0; i < 10; i++)
    {
        printf("%d ", a[i]);
    }
    printf("\n");
    return 0;
}
