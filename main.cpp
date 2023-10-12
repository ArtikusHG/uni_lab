#include <stdio.h>

int main() {
    int i;
    i = 69;
    int number = 72;
    i = 69 + 72;
    int array[3] = {0, 0, 0};
    int *iPointer = &i;
    number = *iPointer;
    *iPointer = 15;
    iPointer = &array[0];
    iPointer += 2;
    array[0] = 5;
    *iPointer = 6;
    return 0;
}

