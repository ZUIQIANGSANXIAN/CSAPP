/*
author:sanxian
time:2023/10/5
*/
#include<stdlib.h>
#include<stdint.h>

// operator
typedef enum OP
{
    MOV,
    PUSH,
    CALL
}op_t;

// operand
/*
操作数的三种类型：
立即数(immediate)
寄存器(register)
内存引用(M[addr]) addr->Imm(rb,ri,s)
*/
typedef enum OD_TYPE
{
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
    uint64_t scal;
    uint64_t reg1;
    uint64_t reg2;
}od_t;

// instrucation
typedef struct INST_STRUCT
{
    op_t op;
    od_t src;
    od_t dst;
}ins_t;
