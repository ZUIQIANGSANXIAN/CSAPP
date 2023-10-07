#include"memory/dram.h"
#include"cpu/mmu.h"
#include"cpu/cpu.h"
#include<stdio.h>

#define SRAM_CACHE_SETTING 0
uint64_t read64bits(uint64_t paddr)
{
    if(SRAM_CACHE_SETTING==1)
    {
        return 0x0;
    }

    uint64_t var=0x0;
    var+=((uint64_t)MM[paddr+0]<<0);
    var+=((uint64_t)MM[paddr+1]<<8);
    var+=((uint64_t)MM[paddr+2]<<16);
    var+=((uint64_t)MM[paddr+3]<<24);
    var+=((uint64_t)MM[paddr+4]<<32);
    var+=((uint64_t)MM[paddr+5]<<40);
    var+=((uint64_t)MM[paddr+6]<<48);
    var+=((uint64_t)MM[paddr+7]<<56);

    return var;
}

void print_register()
{
    printf("rax= %16lx\trbx= %16lx\trcx= %16lx\trdx= %16lx\n",
            cpu.rax,cpu.rbx,cpu.rcx,cpu.rdx);
            
    printf("rsi= %16lx\trdi= %16lx\trbp= %16lx\trsp= %16lx\n",
            cpu.rsi,cpu.rdi,cpu.rbp,cpu.rsp);
    printf("rip= \n",cpu.rsi);
}

void print_stack()
{
    int n=10;

    uint64_t *high=(uint64_t*)(&MM[va2pa(cpu.rsp)]);

    high=&high[n];

    uint64_t rsp_start=cpu.rsp+n*8;

    for(int i=0;i<2*n;++i)
    {
        uint64_t *ptr=(uint64_t*)(high-i);
        printf("0x%16lx:%16lx",rsp_start,*ptr);
        
        if(i==n)
        {
            printf("<=rsp");
        }

        rsp_start=rsp_start-8;
        printf("\n");
    }
}

void write64bits(uint64_t paddr,uint64_t data)
{
    if(SRAM_CACHE_SETTING==1)
    {
        return;
    }
    MM[paddr+0]=(data>>0)&0xff;
    MM[paddr+1]=(data>>8)&0xff;
    MM[paddr+2]=(data>>16)&0xff;
    MM[paddr+3]=(data>>24)&0xff;
    MM[paddr+4]=(data>>32)&0xff;
    MM[paddr+5]=(data>>40)&0xff;
    MM[paddr+6]=(data>>48)&0xff;
    MM[paddr+7]=(data>>56)&0xff;

}