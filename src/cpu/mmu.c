#include"cpu/mmu.h"
#include<stdint.h>

uint64_t va2pa(uint64_t paddr)
{
    return (paddr%MM_LEN);
}
