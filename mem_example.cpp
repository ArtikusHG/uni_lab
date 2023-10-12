// include libraries for i/o
#include <stdlib.h>
#include <iostream>

// declare structure that contains two fields a and b
struct TwoInts
{
    int a;
    int b;
};

// another structure with array and num pointer
struct StructWithArray
{
    int arr[4];
    int* someNumber;
};

// main function
int main()
{
    // instance of structure TwoInts
    TwoInts i2 = { };
    i2.a = 5;
    i2.b = 7;
    // output a and b to console
    std::cout << i2.a << std::endl;
    std::cout << i2.b << std::endl;
    
    // two instances of structure StructWithArray, set the first array element
    StructWithArray s = { };
    s.arr[0] = 10;

    StructWithArray s1 = { };
    s1.arr[0] = 15;
    
    // the same but with a pointer
    StructWithArray* sPointer = &s;
    sPointer->arr[0] = 20;

    // output elements and change their values
    std::cout << s.arr[0] << std::endl;
    s.arr[0] = 25;
    std::cout << s.arr[0] << std::endl;
    // the same with a pointer
    sPointer->arr[0] = 30;
    std::cout << s.arr[0] << std::endl;

    sPointer = &s1;
    sPointer->arr[0] = 35;
    std::cout << s.arr[0] << std::endl;
    std::cout << s1.arr[0] << std::endl;

    // array of StructWithArray
    StructWithArray structArray[2] = { };
    // set fourth array number of first struct to 77
    structArray[0].arr[3] = 77;
    // the same using pointers
    structArray[1].someNumber = &structArray[0].arr[3];

    sPointer = &s;
    // using sPointer, assign new pointer to 4th element
    int* pointer = &sPointer->arr[3];
    s.arr[3] = 72;
    // output pointer
    std::cout << *pointer;

    // assign all 0es to this struct in memory
    StructWithArray memory;
    memset(&memory, 0, sizeof(StructWithArray));
    return 0;
}

