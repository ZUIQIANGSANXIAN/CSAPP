	#include<stdlib.h>
#include<stdint.h>

uint64_t add(uint64_t x,uint64_t y)
{
    return x+y;
}

int main()
{
    uint64_t x=0x0011;
    uint64_t y=0x1100;
    uint64_t z=add(x,y);
    return 0;
}