#include <stdio.h>
void to_binary(unsigned long n);

int main(void)
{
    unsigned long number;
    printf("Enter an integer (q to exit): \n");
    while(scanf("%lu",&number) == 1 )
    {
        printf("Binary equivalent: ");
        to_binary(number);
        putchar('\n');
        printf("Enter an integer (q to exit): \n");
    }
    printf("Done.\n");
}

void to_binary(unsigned long n )
{
    int r;

    r = n%2;
    if(n >= 2)
        to_binary(n/2);
    putchar(r == 0 ? '0' : '1');

    return;
}