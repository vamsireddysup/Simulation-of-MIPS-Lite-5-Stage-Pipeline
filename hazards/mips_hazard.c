//mips_hazard.c - Hazard detection and report statistics for MIPS_Lite Simulator
//Implemented : Moulya Raju Machohalli Thimmaraju


//headers files
#include<stdio.h>		//std I/O for functions like printf, scanf etc
#include<stdlib.h>
#include "mips_core.h"		//declared core structures like instn mem, registers, etc
#include "mips_hazards.h"	//header file conatining function calls for hazard checker and stall installtion

//checking and injecting stalls for RAW(Read After Write True Dependency) Hazard

//function for stall injection
void stalls_inj(){
	if (flag1 == 0) return;  //there's no instrn to process so can return
	
	uint32_t curr_inst = dyn_instn_list[flag1];
	int curr_op = opcode(curr_inst);		//opcode 
	int curr_rs = rs(curr_inst);			//source reg
	int curr_rd = rd(curr_inst);			//destination reg
	
//macros for accessing previous instns
#define prev_inst(n) (dyn_instn_list[flag1 - (n)])
#define prev_op(n) (opcode(prev_inst(n)))
#define prev_rd(n) (rd(prev_inst(n)))
#define prev_rt(n) (rt(prev_inst(n)))

//checks 1 instruction back
if(flag1 >= 1){
	int pop = prev_op(1);		//opcode of previous inst
	int prd = prev_rd(1);		//destn and secondary reg to compare with curr_sources
	int prt = prev_rt(1);
	
	if(((prd == curr_rs) || (prd == curr_rd) || (prt == curr_rs) || (prt == curr_rd) && ((curr_op <= op_sub) || (curr_op  >= op_or && currOp <= op_xori) || curr_op == op_stw || curr_op == op_beq))
	{
		if (pop == OP_LDW || pop == OP_STW) {
                frwdstalls++;
            }
            stalls += 2;
            rawhazdect[Flag1] = -1;
            return;
        }
    }

	    // 2-instructions back
    if (flag1 >= 2) {
        int prd2 = prev_rd(2);
        if (prd2 == curr_rs || prd2 == curr_rd) {
            stalls += 1;
            rawhazdect[flag1] = -2;
            return;
        }
    }

    #undef prev_inst
    #undef prev_op
    #undef prev_rd
    #undef prev_rt
}

//Hazard checker at Top-Level - checks and estimates brac=nch penalties
void hazardshcecker() {
    if (flag1 == 0) return;
    if (flag1 >= 1 && branchflag[flag1-1]) {
        penalties += 2;
        flag2dict[flag1] = -1;
        return;
    }
    if (flag1 >= 2 && branchflag[flag1-2]) {
        stallsinjection();
        return;
    }
    stallsinjection();
}

// Report Statistics logout
void display() {
    printf("||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("                     Simulation Report\n");
    printf("||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    int totalinstrn = arithmeticinstrn + logicalinstrn + memoryinstrn + countmeminstrn;
    printf("  Total instructions       : %d\n", totalinstrn);
    printf("  Arithmetic             : %d\n", arithmeticinstrn);
    printf("  Logical                : %d\n", logicalinstrn);
    printf("  Memory (LD/ST)         : %d\n", memoryinstrn);
    printf("  Control (branches,jr)  : %d\n", countmeminstrn);
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("  Final Program Counter  : 0x%08X\n", ProgramCounter);
    printf("----------------------------------------------------------------------\n");
    printf("  Registers updated:\n");
    

