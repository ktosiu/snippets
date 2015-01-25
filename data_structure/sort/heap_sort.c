#include <stdio.h>

void make_heap(int* a, int len);

/*Adjust the range[begin, end], assume the only the top violates the heap constriant*/
void heap_adjust(int* a, int begin, int end);

void heap_sort(int* a, int len);

void print_array(int* a, int begin, int end);

int main() {
    int a[10] = {10,9,8,7,6,5,4,3,2,1};
    print_array(a, 0, 10);
    heap_sort(a, 10);
    print_array(a, 0, 10);
    return 0;
}

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heap_sort(int* a, int len) {
    make_heap(a, len);
    int end = len - 1;
    while(end > 0) {
        swap(&a[end], &a[0]);
        end--;
        heap_adjust(a, 0, end);
    }
}

/*lchild = parent*2+1, rchild = parent*2+2. */
void heap_adjust(int* a, int begin, int end) {
    int root = begin;

    while(root*2 + 1 <= end) {
        int child = root*2 + 1;
        int parent = root;

        if(a[parent] < a[child])
            parent = child;

        if(child+1 <= end && a[parent] < a[child+1]) {
            parent = child + 1;
        }

        if(parent == root) {
            return;
        }
        else {
            swap(&a[root], &a[parent]);
            root = parent;
        }
    }
}

void make_heap(int* a, int len) {
    int start = (len - 2) / 2;
    while(start >= 0) {
        heap_adjust(a, start, len-1);
        start--;
    }
}

/*[begin, end)*/
void print_array(int* a, int begin, int end) {
    for(int i = begin; i != end; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}
