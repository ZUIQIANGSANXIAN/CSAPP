/*
author:sanxian
time:2023/10/6
*/
#include"../disk/elf.h"
#include"../cpu/cpu.h"

ins_t pragma[13]=
{
    //1 add() 
    {
        push_reg,
        {REG,0,0,(uint64_t*)&cpu.rbp,NULL},
        {EMPTY,0,0,NULL,NULL},
        "push   \%rbp"
    },
    //2
    {
        mov_reg_reg,
        {REG,0,0,(uint64_t*)&cpu.rsp,NULL},
        {REG,0,0,(uint64_t*)&cpu.rbp,NULL},
        "mov    \%rsp,\%rbp"
    },
    //3
    {
        mov_reg_mem,
        {REG,0,0,(uint64_t*)&cpu.rdi,NULL},
        {MM_IMM_REG,-0x8,0,(uint64_t*)&cpu.rbp,NULL},
        "mov    \%rdi,-0x8(\%rbp)"
    },
    //4
    {
        mov_reg_mem,
        {REG,0,0,(uint64_t*)&cpu.rsi,NULL},
        {MM_IMM_REG,-0x10,0,(uint64_t*)&cpu.rbp,NULL},
        "mov    \%rsi,-0x10(\%rbp)"
    },
    //5
    {
        mov_mem_reg,
        {MM_IMM_REG,-0x8,0,(uint64_t*)&cpu.rbp,NULL},
        {REG,0,0,(uint64_t*)&cpu.rdx,NULL},
        "mov    -0x8(\%rbp),\%rdx"
    },
    //6
    {
        mov_mem_reg,
        {MM_IMM_REG,-0x10,0,(uint64_t*)&cpu.rbp,NULL},
        {REG,0,0,(uint64_t*)&cpu.rax,NULL},
        "mov    -0x10(\%rbp),\%rax"
    },
    //7
    {
        add_reg_reg,
        {REG,0,0,(uint64_t*)&cpu.rdx,NULL},
        {REG,0,0,(uint64_t*)&cpu.rax,NULL},
        "add    \%rdx,\%rax"
    },
    // 8
    {
        pop_reg,
        {REG,0,0,(uint64_t*)&cpu.rbp,NULL},
        {EMPTY,0,0,NULL,NULL},
        "pop    \%rbp"
    },
    // 9
    {
        ret,
        {EMPTY,0,0,NULL,NULL},
        {EMPTY,0,0,NULL,NULL},
        "ret"
    },
    // 10 main()
    {
        mov_reg_reg,
        {REG,0,0,(uint64_t*)&cpu.rdx,NULL},
        {REG,0,0,(uint64_t*)&cpu.rsi,NULL},
        "mov    \%rdx,\%rsi"
    },
    // 11
    {
        mov_reg_reg,
        {REG,0,0,(uint64_t*)&cpu.rax,NULL},
        {REG,0,0,(uint64_t*)&cpu.rdi,NULL},
        "mov    \%rax,\%rdi"
    },
    // 12
    {
        call,
        {IMM,(uint64_t)&pragma[0],0,NULL,NULL},
        {EMPTY,0,0,NULL,NULL},
        "call   0x555555555129 <add>"
    },
    // 13
    {
        mov_reg_mem,
        {REG,0,0,(uint64_t*)&cpu.rax,NULL},
        {MM_IMM_REG,-0X8,0,(uint64_t*)&cpu.rbp,NULL},
        "mov    \%rax,-0x8(\%rbp)"
    }
};



