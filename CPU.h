#ifndef CPU_h
#define CPU_h
#include "Instruction.h"   // to be added 
#include <string>
#include <vector>
#include<stack>
#define RegFile_Size 32 // size of register file
#define DataMem_Size 32 // Declaring an array for Data Memory
using namespace std;

class CPU
{
public: 

	CPU(string);    // class constructor receives the file name containing assembly code to be parsed
	~CPU(); 
	int nametoNum(string  & name, bool cut = true);
	void control(int); //generates the control signals, it receives the instruction number
	void fetch();
	void Decode();      // uses buffer1 as input and stores output in buffer2
	void execute ();
	void MemAccess(); 
	void WriteBack(); 
	void flush(); 
	bool Found(int);   // returns true if branch address is found in BTB
	int Predicted(int);  
	void DeleteEntry(int);   // prediction state = false
	void InsertInBtb(int,int);   // inserts record in btb

private:

	/*struct buffer1
	{
	int pc;
	Instruction inst;
	};
	struct buffer2
	{
	int pc;
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
	int rs;
	int rt;
	int imm;
	int RD;
	};
	struct buffer3
	{
	int pc;
	int zeroflag;
	int ALUresult;
	int rt;
	int RD;
	bool regDest;
	bool branch;   //control signal 
	bool memRead;   //control signal 
	bool memWrite;   //control signal 
	bool memToReg;  //control signal 
	bool jump;    //control signal 
	bool jumpReg; //control signal
	int imm;
	};
	struct buffer4
	{
	int MemReadData; 
	int ALUresult;
	int RD;
	bool memWrite;   //control signal 
	bool memToReg;  //control signal 
	};*/
	string filename; 
	vector <Instruction> IM; // instruction memory of type Instruction(class)

	int PC;//program counter
	int clk;
	bool rst;
	int RegFile[RegFile_Size];             // Declaring an array for Register File 
	int DataMem[DataMem_Size];          // Declaring an array for Data Memory 
	int buffer1old[8]; // IF/ID    
	int buffer2old[18]; // ID/EX   
	int buffer3old[18]; // EX/Mem 
	int buffer4old[9]; // MEM/WB
	int buffer1new[8];  // 
	int buffer2new[18]; // ID/EX  
	int buffer3new[18]; // EX/Mem
	int buffer4new[9]; // MEM/WB
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

	int clkAtFinalInst;
    int clkWAtFinalInst;
	bool finalInst;
	bool fetchEn;
	bool finalfooEn;
	bool finalEn;
	bool decodeEn;
	bool execEn;
	bool memEn;
	bool wbEn;
    bool branchFound;
	int wbData;

	struct BTB
	{int branchAddress; 
	int predictedPC;
	bool taken; 
	};
	vector<BTB> btb;
	stack<int> returnAddresses; 
	//private function
	void programCounter();
	void test(); 
};
#endif