//
//  Instruction.h
//  MipsPipelinedSimulator
//
//  Created by Alia Hassan  on 11/23/15.
//  Copyright (c) 2015 Alia Hassan . All rights reserved.
//

#ifndef __MipsPipelinedSimulator__Instruction__
#define __MipsPipelinedSimulator__Instruction__

class Instruction
{
public:
    Instruction(int i, int s, int d, int t, int imm);//constructor
    //Instruction (const Instruction &);//copy constructor
    ~Instruction();//destructor
    
    
    
private:
    int instNum;
    int rs;
    int rd;
    int rt;
    int imm;
    
    int clkAtFet;
    int clkAtDec;
    int clkAtEx;
    int clkAtMem;
    int clkAtWB;
    
    
    
};

#endif /* defined(__Temp__Instruction__) */
