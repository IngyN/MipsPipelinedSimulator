//
//  Instruction.cpp
//  MipsPipelinedSimulator
//
//  Created by Alia Hassan  on 11/23/15.
//  Copyright (c) 2015 Alia Hassan . All rights reserved.
//

#include "Instruction.h"

Instruction::Instruction()
{
      instNum = 0;
      rs =0;
      rd =0;
      rt=0;
      imm=0;
    
      clkAtFet=0;
      clkAtDec=0;
      clkAtEx=0;
      clkAtMem=0;
      clkAtWB=0;
}

Instruction::Instruction(int i, int s, int d, int t, int im):instNum(i),rs(s),rd(d),rt(t),imm(im)
{
    
}

void Instruction::setRd(int rd)
{
    this->rd = rd;
}

void Instruction::setRs(int rs)
{
    this->rs = rs;
}

void Instruction::setRt(int rt)
{
    this->rt = rt;
}

void Instruction::setInstNum(int inst)
{
    this->instNum= inst;
}

void Instruction::setImm(int imm)
{
    this->imm = imm;
}

void Instruction::setOffset(int offset)
{
    this->imm = offset;
}

void Instruction:: clear ()
{
    instNum = 0;
    rs =0;
    rd =0;
    rt=0;
    imm=0;
    
    clkAtFet=0;
    clkAtDec=0;
    clkAtEx=0;
    clkAtMem=0;
    clkAtWB=0;
}


Instruction::Instruction (const Instruction &)
{
    this->instNum = instNum;
    this->rs =rs;
    this->rd =rd;
    this->rt=rt;
    this->imm=imm;
    
    this->clkAtFet=clkAtFet;
    this->clkAtDec=clkAtDec;
    this->clkAtEx=clkAtEx;
    this->clkAtMem=clkAtMem;
    this->clkAtWB=clkAtWB;
}

Instruction::~Instruction()
{
    
}

