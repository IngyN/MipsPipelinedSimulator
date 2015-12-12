#ifndef CPU_h
#define CPU_h
#include "InstructionT.h"   // to be added
#include <string>
#include <QString>
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
    void fetch();
	void Decode();      // uses buffer1 as input and stores output in buffer2
	void execute ();
	void MemAccess(); 
	void WriteBack();
	int nametoNum(string name, bool cut = true);
    void loadAndParse(string name = "");
    void test();
    void reset ();
    int getClk();
    void incrementClk();
    int getClkWAtFinal();
    int getPC();
    bool validFetch();
    bool validDecode();
    bool validExecute();
    bool validMemory();
    bool validWb();
    bool getFinalFoo();

    
    //variables
    vector <InstructionT> IM; // instruction memory of type Instruction(class)
    vector<QString> textIM;
    int RegFile[RegFile_Size];             // Declaring an array for Register File
    int DataMem[DataMem_Size];          // Declaring an array for Data Memory
    bool stages [5];
    
private:

    bool Found(int);   // returns true if branch address is found in BTB
    int Predicted(int);
    void InsertInBtb(int,int);   // inserts record in btb
    void flushFetch();
    void flushThree();
    void stall();
    bool branchTaken(int);   // returns true if taken = true in btb
    void assignTaken(int,int);  // true/false depending on zeroflag
    void flush();
   
    
    
    void control(int); //generates the control signals, it receives the ins truction number

	string filename; 
	

	int PC;//program counter
	int clk;
	bool rst;
	
	int buffer1old[8]; // IF/ID    
	int buffer2old[20]; // ID/EX   
	int buffer3old[18]; // EX/Mem 
	int buffer4old[9]; // MEM/WB
	int buffer1new[8];  // 
	int buffer2new[20]; // ID/EX  
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
    
    bool boolStall;

	struct BTB
	{int branchAddress; 
	int predictedPC;
	bool taken; 
	};
	vector<BTB> btb;
	stack<int> returnAddresses; 
	//private function
	void programCounter();
	
};
#endif
