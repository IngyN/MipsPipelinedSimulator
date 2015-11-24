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
    Instruction();
    Instruction(int i, int s, int d, int t, int imm);//constructor
    Instruction (const Instruction &);//copy constructor
    ~Instruction();//destructor
    
    // setters
    void setRd(int rd);
    void setRs (int rs);
    void setRt (int rt);
    void setInstNum(int inst);
    void setImm(int imm);
    void setOffset(int offset);
    void setClkAtFet (int);
    void setClkAtDec (int);
    void setClkAtEx (int);
    void setClkAtMem (int);
    void setClkAtWB (int);
    
    // getters
    int getInstNum ();
    int getImm ();
    int getOffset ();
    int getRs();
    int getRt();
    int getRd();
    
    //clear everything
    void clear ();
    
    
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
