#include <stdio.h>

void print_array(int* a, int len) {
    for(int i = 0; i < len;i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void selection_sort(int* a, int len) {
    for(int i = 0; i < len - 1; i++) {
        int index_min = i;
        for(int j = i + 1; j < len; j++) {
            if(a[j] < a[index_min]) {
                index_min = j;
            }
        }
        swap(&a[index_min], &a[i]);
    }
}

int main() {
    int a[10] = {10,9,8,7,6,5,4,3,2,1};
    selection_sort(a, 10);
    print_array(a, 10);
    return 0;
}
