#include"memory/instruction.h"
#include"cpu/cpu.h"
#include"cpu/mmu.h"
#include"memory/dram.h"

static uint64_t decode_od(od_t od)
{
    if(od.type==IMM)
    {
        return *(uint64_t *)&od.imm;
    }
    else if(od.type==REG)
    {
        return (uint64_t)*od.reg1;
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



void init_handler_tbale();
void mov_reg_reg_handler(uint64_t src,uint64_t dst)
{
    *(uint64_t *)dst=*(uint64_t *)src;
    cpu.rip=cpu.rip+sizeof(ins_t);
}
void add_reg_reg_handler(uint64_t src,uint64_t dst)
{
    *(uint64_t *)dst=*(uint64_t *)src+ *(uint64_t *)dst;
    cpu.rip=cpu.rip+sizeof(ins_t);
}
void call_handler(uint64_t src,uint64_t dst)
{
    
}


