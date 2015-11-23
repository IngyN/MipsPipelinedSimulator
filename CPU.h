#ifndef CPU_h
#define CPU_h
#include "Instruction.h"   // to be added 


class CPU
{
public: 

	CPU(string);    // class constructor receives the file name containing assembly code to be parsed
	~CPU(); 
	void control (); //generates the control signals, it receives the instruction number
	// Fetch function
	// Decode function
	void execute ();

private:
string filename; 
vector <Instruction> IM; // instruction memory of type Instruction(class)
const int RegFile_Size = 16;  // size of register file
const int DataMem_Size;      //**** 
int RegFile[RegFile_Size];             // Declaring an array for Register File 
int DataMem[DataMem_Size];          // Declaring an array for Data Memory 
int buffer1[2]; // IF/ID
int buffer2[5]; // ID/EX
int buffer3[5]; // EX/Mem
int buffer4[3]; // MEM/WB
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

// Decode parameters:
// inputs to the register file
	int ReadReg1;      // Read register 1 (Rs)
	int ReadReg2;      // Read register 2 (Rt)
	int WrReg;        // Write register (Rd or Rt) - passed from final buffer 
	int WrData;       // Write data 
	// output stored in buffer2 (next PC, ReadData1, ReadData2, imm, rd)
	int ReadData1;    // Read data 1 (RegFile[Rs])
	int ReadData2;    // Read data 2 (RegFile[Rt])
	int RD;       // current rd 

// Add parameters needed for fetch/decode/execute
int zeroflag=0; //it's an integer to passed through the buffer 
int ALUResult;

};
#endif