/*
author:sanxian
time:2023/10/6
*/
#ifndef gurd_dram
#define gurd_dram


#include<stdlib.h>
#include<stdint.h>

#define MM_LEN 1000
// 设置的内存大小
extern uint8_t MM[MM_LEN];

// 读写

uint64_t read64bits(uint64_t paddr);
void write64bits(uint64_t paddr,uint64_t data);

void print_register();
void print_stack();

#endif