//
//  Instruction.cpp
//  AssemblyProject
//
//  Created by Ingy on 3/24/15.
//  Copyright (c) 2015 Ingy. All rights reserved.
//

#include "Instruction.h"
#include <iostream>
# include "RFormat.h"
# include "JFormat.h"
#include "IFormat.h"
#include <QString>

using namespace std;

unsigned int Instruction:: pc=0;

int Instruction::registers [32]={0};

unsigned char Instruction:: memory[8*1024]={0};

Instruction::Instruction()
{
    
    // Initialize stack pointer at last location in memory
    registers[0x1d]=4*2048+0x10010000; // 8KB/4= 2KB= 2*2ˆ10
    
}

Instruction::~Instruction()
{
    
}

void Instruction ::select(Instruction * & p, unsigned char opcode, unsigned int w)
{
    if(opcode ==0)
    {
        // R format
        p =  new RFormat;
        p->setWord(w);
    }
    else if(opcode==2 || opcode==3)
    {
        // J-Format (J & Jal)
        p = new JFormat;
        p->setWord(w);
    }
    
    else if( 16!=opcode && 17!=opcode &&18!=opcode && 19!=opcode)
    {
        // I-Format
        p =new IFormat;
        p->setWord(w);
    }
    
    else
    {
        // The opcode is not known
        cout << "\tOpcode: " << dec << opcode << " - Unkown Instruction" << endl;
    }
}

void Instruction::setWord(unsigned int w)
{
    word=w;
    opcode=w>>26;
}

bool  Instruction::isRFormat()
{
    return (opcode==0);
}

bool Instruction:: isJFormat()
{
    return (opcode==2 || opcode==3);
}
bool Instruction::isIFormat()
{
    return (16!=opcode && 17!=opcode &&18!=opcode && 19!=opcode && opcode!=2 && opcode !=3 && opcode != 0);
}

string Instruction::displayReg(char r)
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

void Instruction::displayAll()
{
    cout <<endl;
    for(int i=0; i<32; i++)
    {
        displayReg(char(i));
        cout <<"\t"<< registers[i]<<endl;
    }
    cout <<endl;
}
