//
//  Instruction.cpp
//  MipsPipelinedSimulator
//
//  Created by Alia Hassan  on 11/23/15.
//  Copyright (c) 2015 Alia Hassan . All rights reserved.
//

#include "InstructionT.h"
#include<iostream>
#include <QString>
using namespace std;

InstructionT::InstructionT()
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

string InstructionT::displayReg(int r)
{
    string s;
//    cout <<dec;
    switch (r)
    {

            // $zero
        case 0x00:
            s="$zero";
            break;

            // $at
        case 0x01:
            s="$at";
            break;

            // $v0-$v1
        case 0x02:
        case 0x03:
            s= "$v"+QString::number((r-2)).toStdString();
            break;

            // $a0-$a3
        case 0x04:
        case 0x05:
        case 0x06:
        case 0x07:
            s= "$a"+QString::number(int(r-4)).toStdString();
            break;

            // $t0-$t7
        case 0x08:
        case 0x09:
        case 0x0a:
        case 0x0b:
        case 0x0c:
        case 0x0d:
        case 0x0e:
        case 0x0f:
            s= "$t"+QString::number(int(r-8)).toStdString();
            break;

            //$s0-$s7
        case 0x10:
        case 0x11:
        case 0x12:
        case 0x13:
        case 0x14:
        case 0x15:
        case 0x16:
        case 0x17:
            s="$s"+QString::number(int(r-0x10)).toStdString();
            break;

            // $t8-$t9
        case 0x18:
        case 0x19:
            s="$t"+QString::number(int(r-0x18+8)).toStdString();
            break;

            // $k0-$k1
        case 0x1a:
        case 0x1b:
            s="$k"+ QString::number(int(r-0x1a)).toStdString();
            break;

            // $gp
        case 0x1c:
            s="$gp";
            break;

            // $sp
        case 0x1d:
            s="$sp";
            break;

            // $fp
        case 0x1e:
            s="$fp";
            break;

            // $ra
        case 0x1f:
            s="$ra";
            break;

    }

    return s;
}
InstructionT::InstructionT(int i, int s, int d, int t, int im):instNum(i),rs(s),rd(d),rt(t),imm(im)
{
    
}

void InstructionT::setRd(int rd)
{
    this->rd = rd;
}

void InstructionT::setRs(int rs)
{
    this->rs = rs;
}

void InstructionT::setRt(int rt)
{
    this->rt = rt;
}

void InstructionT::setInstNum(int inst)
{
    this->instNum= inst;
}

void InstructionT::setImm(int imm)
{
    this->imm = imm;
}


/*void Instruction::setOffset(int offset)
{
    this->imm = offset;
}*/

void InstructionT:: setClkAtFet (int clk)
{
    this->clkAtFet = clk;
}
void InstructionT::setClkAtDec (int clk)
{
    this->clkAtDec=clk;
}
void InstructionT:: setClkAtEx (int clk)
{
    this->clkAtEx = clk;
}
void InstructionT:: setClkAtMem (int clk)
{
    this->clkAtMem = clk;
}
void InstructionT:: setClkAtWB (int clk)
{
    this->clkAtWB = clk;
}

int InstructionT:: getInstNum ()
{
    return this->instNum;
}

int InstructionT:: getImm ()
{
    return this ->imm;
}
/*int InstructionT:: getOffset ()
{
    return this->imm;
}*/
int InstructionT:: getRs()
{
    return this->rs;
}
int InstructionT:: getRt()
{
    return this->rt;
}
int InstructionT:: getRd()
{
    return this->rd;
}
int InstructionT:: getClkAtFet ()
{
    return this->clkAtFet;
}
int InstructionT:: getClkAtDec ()
{
    return this->clkAtDec;
}
int InstructionT:: getClkAtEx ()
{
    return this->clkAtEx;
}
int InstructionT:: getClkAtMem ()
{
    return this->clkAtMem;
}
int InstructionT:: getClkAtWB()
{
    return this -> clkAtWB;
}



void InstructionT:: clear ()
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


InstructionT::InstructionT (const InstructionT & rhs)
{
    this->instNum = rhs.instNum;
    this->rs =rhs.rs;
    this->rd =rhs.rd;
    this->rt=rhs.rt;
    this->imm=rhs.imm;
    
    this->clkAtFet=rhs.clkAtFet;
    this->clkAtDec=rhs.clkAtDec;
    this->clkAtEx=rhs.clkAtEx;
    this->clkAtMem=rhs.clkAtMem;
    this->clkAtWB=rhs.clkAtWB;
}

InstructionT::~InstructionT()
{
    
}

