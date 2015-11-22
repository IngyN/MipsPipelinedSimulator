#include "CPU.h"
using namespace std;
#include <iostream>

CPU::CPU(string name)    // constructor receives the file name 
{
	filename = name; 
}

CPU::~CPU()
{
}

void control (int instNum) //generates the control signals, receives the instruction number
{	
	switch (instNum)
		case 1:   //add
			ALUOp=0;
			break;
		case 2:   //addi
			ALUOp=0;
			regDest= false;
			ALUSrc= true;
			break;
		case 3:   //xor
			ALUOp=2;
			break;
		case 4:  //lw
			regDest= false;
			ALUSrc= true;
			ALUOp=0;
			memRead= true;
			memToReg= true;
			break;
		case 5:   //sw
			regWrite= false;
			ALUSrc= true;
			ALUOp=0;
			memWrite= true;
			break;
		case 6:   //ble
			regWrite= false;
			ALUOp=1; //subtract
			branch= true;
			break;
		case 7:   //j
			jump= true;
			regWrite= false;
			break;
		case 8:   //slt
			ALUOp= 3;
			break;
		case 9:   //jal   
			jump= true;
			break;
		case 10:   //jr
			jumpReg= true;
			regWrite= false;
			break;
		case 11:   //jumpProcedure
			jump= true;
			regWrite= false;
			break;
		case 12:   //returnProcedure
			jumpReg= true;
			regWrite= false;
			break;


}