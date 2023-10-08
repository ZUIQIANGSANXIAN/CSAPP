#include"./cpu/cpu.h"
#include"./cpu/mmu.h"
#include"./memory/dram.h"
#include"./memory/instruction.h"
#include"./disk/elf.h"

cpu_reg_t cpu;
int main()
{
    printf("begin\n");
    //step1:初始化指令的操作函数
    init_handler_tbale();

    //step2:初始化寄存器
    cpu.rax=0x12340000;
    cpu.rbx=0x0;
    cpu.rcx=0x555555557df8;
    cpu.rdx=0xabcd;
    cpu.rsi=0x7fffffffe588;
    cpu.rdi=0x1;
    cpu.rbp=0x7fffffffe470;
    cpu.rsp=0x7fffffffe450;
    cpu.rip=(uint64_t)&pragma[9];
    //printf("init_register sucessful!\n");


    //step3:初始化heap
    write64bits(va2pa(0x7fffffffe470),0x01);        // rbp
    write64bits(va2pa(0x7fffffffe468),0x0);
    write64bits(va2pa(0x7fffffffe460),0x0000abcd);
    write64bits(va2pa(0x7fffffffe458),0x12340000);
    write64bits(va2pa(0x7fffffffe450),0x0);        // rsp
    //printf("init_heap sucessful!\n");
    print_register();
    print_stack();

    // step4:运行指令
    for(int i=0;i<13;i++)
    {
        instruction_cycle();
        print_register();
        print_stack();
    }

    int match=1;
    // step5：匹配寄存器状态
    match=match&&(cpu.rax== 0x1234abcd);
    match=match&&(cpu.rbx== 0x0 );
    match=match&&(cpu.rcx== 0x555555557df8);
    match=match&&(cpu.rdx== 0x12340000);
    match=match&&(cpu.rdi== 0xabcd  );
    match=match&&(cpu.rsi== 0x12340000);
    match=match&&(cpu.rbp== 0x7fffffffe470);
    match=match&&(cpu.rsp== 0x7fffffffe450);

    if(match==1)
    {
        printf("register match!\n");
    }
    else
    {
        printf("register not match!\n");
    }


    // step6：匹配栈状态
    match=match&&(read64bits(va2pa(0x7fffffffe470))==0x01);
    match=match&&(read64bits(va2pa(0x7fffffffe468))==0x1234abcd);
    match=match&&(read64bits(va2pa(0x7fffffffe460))==0x0000abcd);
    match=match&&(read64bits(va2pa(0x7fffffffe458))==0x12340000);
    match=match&&(read64bits(va2pa(0x7fffffffe450))==0x0);

    if(match==1)
    {
        printf("MM match!\n");
    }
    else
    {
        printf("MM not match!\n");
    }

    return 0;
};
