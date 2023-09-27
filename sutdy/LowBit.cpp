#include<stdlib.h>
#include<stdio.h>



int main()
{
    int a = 0x7fffffff;
    printf("%.d\n", (~a)+1);
    return 0;
}