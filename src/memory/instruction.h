/*
author:sanxian
time:2023/10/5
*/
#ifndef gurd_instruction
#define gurd_instruction

#include<stdlib.h>
#include<stdint.h>
#include<stdio.h>

#define NUM_OPTYPE 8

// operator
typedef enum OP
{
   mov_reg_reg,
   mov_reg_mem,
   mov_mem_reg,
   push_reg,
   pop_reg,
   call,
   ret,
   add_reg_reg
}op_t;

// operand
typedef enum OD_TYPE
{
    EMPTY,
    IMM,
    REG,
    MM_IMM,
    MM_REG,
    MM_IMM_REG,
    MM_REG1_REG2,
    MM_IMM_REG1_REG2,
    MM_REG2_SCAL,
    MM_IMM_REG2_SCAL,
    MM_REG1_REG2_SCAL,
    MM_IMM_REG1_REG2_SCAL
}od_type_t;

typedef struct OD
{
    // 操作数类型
    od_type_t type;
    int64_t imm;
    int64_t scal;
    uint64_t *reg1;
    uint64_t *reg2;
}od_t;

// instrucation
typedef struct INST_STRUCT
{
    op_t op;
    od_t src;
    od_t dst;
    char code[100];
}ins_t;


// decode
uint64_t decode_od(od_t od);

// 指令操作对应的回调函数
typedef void (*handler_t)(uint64_t src,uint64_t dst);
extern handler_t handler_table[NUM_OPTYPE];

void init_handler_tbale();
void mov_reg_reg_handler(uint64_t src,uint64_t dst);
void mov_reg_mem_handler(uint64_t src,uint64_t dst);
void mov_mem_reg_handler(uint64_t src,uint64_t dst);
void push_reg_handler(uint64_t src,uint64_t dst);
void pop_reg_handler(uint64_t src,uint64_t dst);
void call_handler(uint64_t src,uint64_t dst);
void ret_handler(uint64_t src,uint64_t dst);
void add_reg_reg_handler(uint64_t src,uint64_t dst);


void instruction_cycle();
#endif