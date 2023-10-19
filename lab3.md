# Задание 1: Функции и линкер

## Пример 1

Создаю файл ```main.cpp``` со следующим содержимым:

```c++
#include <stdio.h>

int hello(int input);

int main() {
	int test = hello(103);
	printf("%d", test);
	return 0;
}
```

Пытаюсь скомпилировать командой ```clang++ main.cpp```, получаю следующую ошибку:

```
in function `main':
main.cpp:(.text+0x15): undefined reference to `hello(int)'
clang-16: error: linker command failed with exit code 1 (use -v to see invocation)
```

Это означает, что функция хоть и объявлена, и компиляция проходит успешно, однако линкер выдает ошибку, потому что функция не декларирована, у нее нет тела. Получается что ```main``` ссылается на несуществующий фрагмент программы.

Добавляю функции тело:

```c++
int hello(int input) {
    return input;
}
```

После этого компиляция проходит успешно, программа выводит ```103```.

## Пример 2 (с 2 файлами)

Создаю в добавок к первому файлу ```main.cpp``` новый файл ```f.cpp```. В результате имею:

### main.cpp

```c++
#include <stdio.h>

int hello(int input);

int main() {
	int test = hello(103);
	printf("%d", test);
	return 0;
}
```

### f.cpp

```c++
int hello(int input);
```

Компилирую командой ```clang++ main.cpp f.cpp```, получаю похожую ошибку:

```
in function `main':
main.cpp:(.text+0x15): undefined reference to `hello(int)'
clang-16: error: linker command failed with exit code 1 (use -v to see invocation)
```

Хоть мы и объявили функцию в двух файлах, у нее все еще нет тела, и линкеру все еще не на что сослаться. Определим функции тело в файле ```f.cpp```:

```c++
int hello(int input) {
    return input;
}
```

После этого компиляция проходит успешно и программа опять же выводит ```103```. Это происходит потому, что несмотря на то, что ```hello``` объявлена в отдельном файле, результатом является единая программа, и ошибки нет.

### Пример со ```static```

Добавляю к определению ```hello``` в ```f.cpp``` ключевое слово ```static```.

```f.cpp```

```c++
static int hello(int input) {
    return input;
}
```

В результате опять получаю ошибку как в прошлых пунктах:

```
in function `main':
main.cpp:(.text+0x15): undefined reference to `hello(int)'
clang-16: error: linker command failed with exit code 1 (use -v to see invocation)
```

Добавляю ```static``` в объявление ```hello``` в ```main.cpp```, в итоге получаю:

```c++
#include <stdio.h>

static int hello(int input);

int main() {
	int test = hello(103);
	printf("%d", test);
	return 0;
}
```

Получаю ту же ошибку при компиляции обоих файлов, но еще и warning:

```
warning: function 'hello' has internal linkage but is not defined [-Wundefined-internal]
static int hello(int input);
in function `main':
main.cpp:(.text+0x15): undefined reference to `hello(int)'
clang-16: error: linker command failed with exit code 1 (use -v to see invocation)
```

В переводе на человеческий язык, если функция ```static```, то она может быть вызвана только в том файле, в котором она была объявлена. Если добавить определение функции с телом в ```main.cpp```, то компиляция пройдет успешно:

```c++
#include <stdio.h>

static int hello(int input) {
  return input;
}

int main() {
	int test = hello(103);
	printf("%d", test);
	return 0;
}
```

При условии, что мы оставим в ```f.cpp``` функцию ```hello```, то в финальный результат будут включены две версии функции ```hello```. Современные компиляторы это оптимизируют и уберут ту, которая не используется (в файле ```f.cpp``` функция ```hello``` ни разу не вызывается).

# Задание 2

## ```stack_2.cpp```

```c++
#include <stdlib.h>
#include <iostream>

//  Создаем функцию которая возвращает указатель на int
int *stackMemory1()
{
    int a = 1;
    return &a;
}
// То же, но с другим int
int *stackMemory2()
{
    int b = 2;
    return &b;
}

int main()
{
    int *b = stackMemory1(); // получаем указатель на int a из stackMemory1
    int a1 = *b; // получаем из него число
    int *c = stackMemory2(); // то же самое со stackMemory2 и переменной int b из этой функции
    int a2 = *c;
    int a3 = *b; // a3 будет иметь то же значение что и a1, потому что они указывают на одну и ту же переменную

    std::cout << a1 << std::endl;                                // prints 1
    std::cout << a2 << std::endl;                                // prints 2
    std::cout << a3 << std::endl;                                // prints 2
    std::cout << ((std::byte *)b - (std::byte *)c) << std::endl; // prints 0, pointers are equal

    return 0;
}
```

## ```stack_1.cpp```

```c++
#include <iostream>

// void - это функция, которая ничего не возвращает...
void stackMemory()
{
    int a = 0;
    std::cout << "a: " << a << std::endl;
    a += 1;
}

int main()
{
    // ...поэтому здесь всегда выводится 0
    stackMemory(); // prints 0
    stackMemory(); // prints 0
    stackMemory(); // prints 0
    return 0;
}
```

Для того, чтобы сделать второй пример эквивалентным первому, нужно не возвращать указатель на переменную ```int a``` - тогда она будет удалена из стэка сразу поле завершения функции.
