/*
author:sanxian
time:2023/10/5
*/

#ifndef gurd_mmu
#define gurd_mmu


#include "memory/dram.h"
#include"stdint.h"
uint64_t va2pa(uint64_t paddr); //vaddr->paddr

#endif