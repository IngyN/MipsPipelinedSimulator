#ifndef CPU_h
#define CPU_h
#include "Instruction.h"   // to be added 


class CPU
{
public: 

	CPU(string);    // class constructor receives the file name containing assembly code to be parsed
	~CPU(); 
	void control (int); //generates the control signals, it receives the instruction number
	// Fetch function
	// Decode function
	// Execute function

private:
string filename; 
vector <Instruction> IM; // instruction memory of type Instruction(class)
const int RF_Size = 16;  // size of register file
const int DM_Size;      //**** 
int RF[RF_Size];             // Declaring an array for Register File 
int DM[DM_Size];          // Declaring an array for Data Memory 
int instNumber; //instruction number
bool regWrite= true;   //control signal 
bool regDest= true;    //control signal (1 for rd, 0 for rt)
bool ALUSrc= false;    //control signal (0: read from reg, 1: imm)
int ALUOp;    //control signal 
bool branch= false;   //control signal 
bool memRead= false;   //control signal 
bool memWrite= false;   //control signal 
bool memToReg= false;  //control signal 
bool jump= false;    //control signal 
bool jumpReg= false; //control signal
// Add parameters needed for fetch/decode/execute

};
#endif