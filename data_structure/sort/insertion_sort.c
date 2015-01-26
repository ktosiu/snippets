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

void insertion_sort(int* a, int len) {
    for(int i = 1; i < len; i++) {
        int j = i;
        while(j > 0 && a[j-1] > a[j]) {
            swap(&a[j-1], &a[j]);
            j--;
        }
    }
}

void insertion_sort2(int* a, int len) {
    for(int i = 0; i < len; i++) {
        int x = a[i];
        int j = i;
        while(j > 0 && a[j-1] > x) {
            a[j] = a[j-1];
            j--;
        }
        a[j] = x;
    }
}

int main() {
    int a[10] = {10,9,8,7,6,5,4,3,2,1};
    insertion_sort(a, 10);
    print_array(a, 10);
    return 0;
}
