#include <stdio.h>

int main()
{
    int a = 0;
    printf("int a = %d\n", a);
    a = a | 4;
    printf("a = a | 4\na = %d\n", a);
    printf("a & 4: %d\n", a & 4);
    printf("a == 4: %d\n", a == 4);
    printf("a & 4 == 4: %d\n", a & 4 == 4);
    printf("a & 4 == 4 & 4: %d\n", a & 4 == (4 & 4));
    return 0;
}
