//mips_hazard.c - Hazard detection and report statistics for MIPS_Lite Simulator
//Implemented : Moulya Raju Machohalli Thimmaraju


//headers files
#include<stdio.h>		//std I/O for functions like printf, scanf etc
#include<stdlib.h>
#include "mips_core.h"		//declared core structures like instn mem, registers, etc
#include "mips_hazards.h"	//header file conatining function calls for hazard checker and stall installtion

//checking and injecting stalls for RAW(Read After Write True Dependency) Hazard

//function for stall injection : 	Compares current instruction with past 2 to detect conflicts.
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



