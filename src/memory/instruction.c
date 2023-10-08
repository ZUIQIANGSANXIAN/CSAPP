#include"../memory/instruction.h"
#include"../cpu/cpu.h"
#include"../cpu/mmu.h"
#include"../memory/dram.h"

handler_t handler_table[NUM_OPTYPE];

uint64_t decode_od(od_t od)
{
    if(od.type==IMM)
    {
        return *(uint64_t *)&od.imm;
    }
    else if(od.type==REG)
    {
        return (uint64_t)od.reg1;       // 为什么不返回值
    }
    else
    {
       // MM=imm+r1+r2*s
       uint64_t vaddr=0x0;

       if(od.type==MM_IMM)
       {
        vaddr=od.imm;     // 类型转换
       }
       else if(od.type==MM_REG)
       {
        vaddr=*(od.reg1);
       }
       else if(od.type==MM_IMM_REG)
       {
        vaddr=od.imm+*(od.reg1);
       }
       else if(od.type==MM_REG1_REG2)
       {
        vaddr=*(od.reg1)+*(od.reg2);
       }
       else if(od.type==MM_IMM_REG1_REG2)
       {
        vaddr=od.imm+*(od.reg1)+*(od.reg2);
       }
       else if(od.type==MM_REG2_SCAL)
       {
        vaddr=*(od.reg2)*od.scal;
       }
       else if(od.type==MM_IMM_REG2_SCAL)
       {
        vaddr=od.imm+*(od.reg2)*od.scal;
       }
       else if(od.type==MM_REG1_REG2_SCAL)
       {
        vaddr=od.imm+*(od.reg1)+*(od.reg2)*od.scal;
       }
       
       return vaddr;
    }
    return 0x0;
}

void mov_reg_reg_handler(uint64_t src,uint64_t dst)
{
    *(uint64_t *)dst=*(uint64_t *)src;
    cpu.rip=cpu.rip+sizeof(ins_t);
}
void mov_reg_mem_handler(uint64_t src,uint64_t dst)
{
    write64bits(va2pa(dst),*(uint64_t *)src);
    cpu.rip=cpu.rip+sizeof(ins_t);
}
void mov_mem_reg_handler(uint64_t src,uint64_t dst)
{
    uint64_t tmp=read64bits(va2pa(src));
    *(uint64_t*)dst=tmp;
    cpu.rip=cpu.rip+sizeof(ins_t);
}
void push_reg_handler(uint64_t src,uint64_t dst)
{
    cpu.rsp=cpu.rsp-8;
    write64bits(va2pa(cpu.rsp),*(uint64_t*)src);
    cpu.rip=cpu.rip+sizeof(ins_t);
}
void pop_reg_handler(uint64_t src,uint64_t dst)
{
    *(uint64_t*)src=read64bits(va2pa(cpu.rsp));
    cpu.rsp=cpu.rsp+8;
    cpu.rip=cpu.rip+sizeof(ins_t);
}
void add_reg_reg_handler(uint64_t src,uint64_t dst)
{
    *(uint64_t *)dst=*(uint64_t *)src+ *(uint64_t *)dst;
    cpu.rip=cpu.rip+sizeof(ins_t);
}
void call_handler(uint64_t src,uint64_t dst)
{
    //rsp下移
    cpu.rsp=cpu.rsp-8;
    //保存返回地址
    write64bits(va2pa(cpu.rsp),cpu.rip+sizeof(ins_t));
    // 跳转
    cpu.rip=src;
}
void ret_handler(uint64_t src,uint64_t dst)
{
    //保存返回地址
    cpu.rip=read64bits(va2pa(cpu.rsp));
     //rsp上移
    cpu.rsp=cpu.rsp+8;
}

void init_handler_tbale()
{
    handler_table[mov_reg_reg]=&mov_reg_reg_handler;
    handler_table[mov_reg_mem]=&mov_reg_mem_handler;
    handler_table[mov_mem_reg]=&mov_mem_reg_handler;
    handler_table[push_reg]=&push_reg_handler;
    handler_table[pop_reg]=&pop_reg_handler;
    handler_table[call]=&call_handler;
    handler_table[ret]=&ret_handler;
    handler_table[add_reg_reg]=&add_reg_reg_handler;
    
}

void instruction_cycle()
{
    ins_t *ins=(ins_t *)cpu.rip;


    // operand
    /*
    imm:imm
    reg:value
    mm:paddr
    */
    uint64_t src=decode_od(ins->src);
    uint64_t dst=decode_od(ins->dst);

    // operator
    handler_t handle=handler_table[ins->op];

    //run
    handle(src,dst);

    printf("   %s\n",ins->code);

    return;
}


