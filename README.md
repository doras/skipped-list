# skipped-list
[![License](https://img.shields.io/badge/Licence-MIT-blue.svg)](./LICENSE)   
C implementation of randomly skipped list

## Usage
Can use skipped-list with a header file [skipped_list.h](./skipped_list.h) and a function definition file [skipped_list.c](./skipped_list.c).

If you include [skipped_list.h](./skipped_list.h), can use struct `Skip_node` and various functions.
```c
#include "skipped_list.h"

void func() {
    Skip_node* header = make_empty_skipped_list(3);
    // insert, delete, find
    delete_skipped_list(header);
}
```

## Sample
In [sample](./sample) and [main.c](./main.c), sample for using skipped-list exists.

Insert 1 to 5, then print in skipped-list with 4 max level.
```
header(4)
1(2)
2(3)
3(0)
4(3)
5(2)
tail(4)
```
Integer in parenthesis is level of each node.