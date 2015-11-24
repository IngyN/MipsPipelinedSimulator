#ifndef CPU_h
#define CPU_h
#include "Instruction.h"   // to be added 
#include <string>
#include <vector>
#define RegFile_Size 32 // size of register file
#define DataMem_Size 100 // Declaring an array for Data Memory
using namespace std;

class CPU
{
public: 

	CPU(string);    // class constructor receives the file name containing assembly code to be parsed
	~CPU(); 
	void control(int); //generates the control signals, it receives the instruction number
    void fetch();
    void Decode();      // uses buffer1 as input and stores output in buffer2
	void execute ();
    int nametoNum(string  & name, bool cut = true);
	void MemAccess(); 

private:
    static int PC;//program counter
    static int clk;
    static bool rst;
    
string filename; 
vector <Instruction> IM; // instruction memory of type Instruction(class)
int RegFile[RegFile_Size];             // Declaring an array for Register File 
int DataMem[DataMem_Size];          // Declaring an array for Data Memory 
int buffer1[11]; // IF/ID
/*
buffer1[0] = pc
buffer1[1] = inst.num
buffer1[2] = inst.rs
buffer1[3] = inst.rt
buffer1[4] = inst.rd
buffer1[5] = inst.imm
buffer1[6] = inst.clkAtFetch
buffer1[7] = inst.clkAtdec
buffer1[8] = inst.clkAtEx
buffer1[9] = inst.clkAtMem
buffer1[10] = inst.clkAtWB
*/ 
int buffer2[17]; // ID/EX
int buffer3[13]; // EX/Mem
int buffer4[3]; // MEM/WB
bool regWrite;   //control signal 
bool regDest;    //control signal (1 for rd, 0 for rt)
bool ALUSrc;    //control signal (0: read from reg, 1: imm)
int ALUOp;    //control signal 
bool branch;   //control signal 
bool memRead;   //control signal 
bool memWrite;   //control signal 
bool memToReg;  //control signal 
bool jump;    //control signal 
bool jumpReg; //control signal

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
    int zeroflag; //it's an integer to passed through the buffer
    int ALUResult;
    bool fetchEn;
    //private function
    void programCounter();

};
#endif