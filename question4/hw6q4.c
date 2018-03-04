#include <stdio.h>

struct point {
    int x;
    int y;
};

int main()
{
    int a, b, c, i, x;
    struct point arr[11];

    printf("ax^2 + bx + c\n\nEnter a value for a: ");
    scanf("%d", &a);
    printf("Enter a value for b: ");
    scanf("%d", &b);
    printf("Enter a value for c: ");
    scanf("%d", &c);
    printf("\n");

    for (i = 0, x = -5; x <= 5; ++x, ++i)
    {
        arr[i].x = x;
        arr[i].y = (a * x * x) + (b * x) + c;
        printf("Point %d   (%d, %d)\n", i + 1, arr[i].x, arr[i].y);
    }

    return 0;
}
