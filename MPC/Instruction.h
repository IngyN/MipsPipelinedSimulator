//
//  Instruction.h
//  AssemblyProject
//
//  Created by Ingy on 3/24/15.
//  Copyright (c) 2015 Ingy. All rights reserved.
//

#ifndef __AssemblyProject__Instruction__
#define __AssemblyProject__Instruction__
#include <bitset>
#include <QString>


using namespace std;

class RFormat;
class JFormat;
class IFormat;

class Instruction
{
public:
    Instruction ();
    ~Instruction();
    
    void setWord(unsigned int);
    static void displayAll();
    
    virtual void decode ()=0;
    virtual string display ()=0;
    virtual bool execute ()=0;
    static string displayReg(char);
    
    bool isRFormat();
    bool isJFormat();
    bool isIFormat();

    virtual unsigned short returnFunction()=0;
    
    static void select(Instruction * &, unsigned char, unsigned int);
    
    static unsigned int pc;
    // Registers
    // 32 registers of size 32 bits (4bytes).
    static int registers [32];
    
    static unsigned char memory[8*1024];	// This array represents the data memory available
    // only 8KB of data memory
    // Starts from address 0x10010000
    
protected:
    
   unsigned int word;
   unsigned char opcode;
    
};

#endif /* defined(__AssemblyProject__Instruction__) */
