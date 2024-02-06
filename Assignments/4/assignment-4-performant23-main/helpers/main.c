#include <stdio.h>
#include <stdlib.h>
#include "helpers.h"

int main(int argc, char* argv[])
{
    if(argc != 2) 
    {
        printf("Usage: %s <size>\n", argv[0]);
        exit(1);
    }
    int num = atoi(argv[1]);
    printf("Num: %d, Prime:%d\n", num, getPrime_fromFile(num));
}
