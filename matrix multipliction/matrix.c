#include <stdio.h>

int main()
{

    char *filename = "m1.txt";
    FILE *fp = fopen(filename, "r");

    if (fp == NULL)
    {
        printf("The document can't open %s", filename);
        return 1;
    }

    const unsigned MAX_LENGTH = 256;
    char buffer[MAX_LENGTH];

    while (fgets(buffer, MAX_LENGTH, fp))
    {
        printf("%s", buffer);
    }

    fclose(fp);

    return 0;
}