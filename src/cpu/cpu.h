/*
author:sanxian
time:2023/10/5
*/
#ifndef gurd_cpu
#define gurd_cpu

#include<stdlib.h>
#include<stdint.h>

typedef struct 
{
    // rax寄存器
    union 
    {
        uint64_t rax;
        uint32_t eax;
        uint16_t ax;

        struct 
        {
            uint8_t al;
            uint8_t ah;
        };
    };
    
    uint64_t rbx;
    uint64_t rcx;
    uint64_t rdx;
    uint64_t rsi;
    uint64_t rdi;
    uint64_t rbp;
    uint64_t rsp;
    uint64_t rip;

}cpu_reg_t;
extern cpu_reg_t cpu;


#endif