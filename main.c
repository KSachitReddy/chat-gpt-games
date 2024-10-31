#include <stdio.h>
int main()
{
    int a, b, c;

    printf("Enter values for a and b: ");
    scanf("%d %d", &a, &b);

    c = a + b;

    if (c % 2 == 0)
    {
        printf("Android\n");
    }
    else
    {
        printf("iPhone\n");
    }

    return 0;
}
