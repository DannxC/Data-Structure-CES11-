#include <stdio.h>

int main()
{
    int i, x, y;
    scanf("%d%d", &x, &y);
    for (i = 1; i <= x; i++)
        printf("Hello World!\n");
    for (i = 1; i <= y; i++)
        printf("Olá Mundo!\n");
    return 0;
}