//
//  IFormat.cpp
//  AssemblyProject
//
//  Created by Ingy on 3/24/15.
//  Copyright (c) 2015 Ingy. All rights reserved.
//

#include "IFormat.h" 
#include <iostream>
#include <iomanip>
#include <QString>

using namespace std;

void IFormat::decode ()
{
    opcode = word >> 26;
    
    imm = word & 0x0000ffff;
    rt    = (word>>16) & 0x0000001f;
    rs    = (word>>21) & 0x0000001f;
    signedImm 	= (imm & 0x8000) ? (0xFFFF0000 | imm): imm;	// sign extending the immediate field
    
    //addi, addiu, andi, ori, xori, lw, sw, sb, lb, lh, sh, beq, bne, slti, lui
}
string IFormat::display ()
{
    string s;
    switch(opcode)
    {
        case 0x08:
            s= "\taddi\t"+displayReg(rt)+","+displayReg(rs)+", "+QString::number(signedImm).toStdString()+"\n";
            
            break;
            
        case 0x09:
            s= "\taddiu\t"+displayReg(rt)+","+displayReg(rs)+", "+QString::number(signedImm).toStdString()+"\n";
            
            break;
        
        case 0x0c:
//            cout << "\tANDI\t";
            s= "\tandi\t"+displayReg(rt)+","+displayReg(rs)+", "+QString::number(signedImm).toStdString()+"\n";
            
            break;
            
        case 0x0d:
//            cout << "\tORI\t\t";
            s= "\tori\t"+displayReg(rt)+","+displayReg(rs)+", "+QString::number(signedImm).toStdString()+"\n";
            
            break;
            
        case 0x0e:
//            cout << "\tXORI\t";
            s= "\txori\t"+displayReg(rt)+","+displayReg(rs)+", "+QString::number(signedImm).toStdString()+"\n";
            
            break;
            
        case 0x23://LW
            
//            cout << "\tLW\t\t";
//            displayReg(rt);
//            cout<< ","<< hex <<signedImm;
//            cout<< "(";
//            displayReg(rs);
//            cout <<")"<<endl;
            s= "\tlw\t"+displayReg(rt)+","+QString::number(signedImm).toStdString()+"("+displayReg(rs)+")"+"\n";

            break;
            
        case 0x2b://SW
//            cout << "\tSW\t\t";
            s= "\tsw\t"+displayReg(rt)+","+QString::number(signedImm).toStdString()+"("+displayReg(rs)+")"+"\n";
            break;
            
        case 0x20://LB
//            cout << "\tLB\t\t";
            s= "\tlb\t"+displayReg(rt)+","+QString::number(signedImm).toStdString()+"("+displayReg(rs)+")"+"\n";
            
            break;
            
        case 0x28://SB
//            cout << "\tSB\t\t";
            s= "\tsb\t"+displayReg(rt)+","+QString::number(signedImm).toStdString()+"("+displayReg(rs)+")"+"\n";
            
            break;
            
        case 0x21://LH
//            cout << "\tLH\t\t";
            s= "\tlh\t"+displayReg(rt)+","+QString::number(signedImm).toStdString()+"("+displayReg(rs)+")"+"\n";
            
            break;
            
        case 0x29://SH
//            cout << "\tSH\t\t";
            s= "\tsh\t"+displayReg(rt)+","+QString::number(signedImm).toStdString()+"("+displayReg(rs)+")"+"\n";
            
            break;
            
        case 0x04:
//            cout << "\tBEQ\t\t";
//            displayReg(rs);
//            cout<< ",";
//            displayReg(rt);
//            cout<< ", 0x"<< hex <<signedImm<<endl;
            s= "\tbeq\t"+displayReg(rs)+","+displayReg(rt)+", "+QString::number(signedImm).toStdString()+"\n";
            break;
            
        case 0x05:
//            cout << "\tBNE\t\t";
//            displayReg(rs);
//            cout<< ",";
//            displayReg(rt);
//            cout<< ", "<<dec<<signedImm<<endl;
            s= "\tbne\t"+displayReg(rs)+","+displayReg(rt)+", "+QString::number(signedImm).toStdString()+"\n";
            break;
            
        case 0x0a:
//            cout << "\tSLTI\t";
//            displayReg(rt);
//            cout<< ",";
//            displayReg(rs);
//            cout<< ","<< hex << signedImm<<endl;
            s= "\tslti\t"+displayReg(rt)+","+displayReg(rs)+", "+QString::number(signedImm).toStdString()+"\n";
            break;
            
        case 0x0f:
//            cout << "\tLUI\t\t";
//            displayReg(rt);
//            cout<< ","<< hex << signedImm<<endl;
            s= "\tlui\t"+displayReg(rt)+","+QString::number(signedImm).toStdString()+"\n";
            break;
            
        default:
            s= "\tUnkown I-Format Instruction\n";
            
    }
    return s;
}

bool IFormat::execute ()
{

    switch (opcode)
    {
        case 0x08://ADDI
           
            if(!((registers[rs]& 0x80000000)^(signedImm & 0x80000000))){
                // Same sign
                int temp=registers[rs] + signedImm;
                
                if(((temp&0x80000000)^(registers[rs]&0x80000000)))
                {
                    // sign of result != sign of operands => overflow!
                    cout <<"OVERFLOW"<<endl;
                }
                else
                    registers[rt]=temp;
            }
            else{
                // no overflow (signs are different)
                registers[rt]=registers[rs] + signedImm;
            }
            
            break;
            
        case 0x09://ADDIU
            registers[rt]=registers[rs] + signedImm;
            
            break;
            
        case 0x0c://ANDI
            registers[rt]=registers[rs] & imm;
            break;
            
        case 0x0d://ORI
            registers[rt]=registers[rs] | imm;
            
            break;
            
        case 0x0e:// xor
            registers[rt]=registers[rs] ^ imm;
            
            break;
            
            //REMEMBER THE MEMORY ACCESS PROBLEM
            
        case 0x23://LW
            
            registers[rt]= (memory[registers[rs] +signedImm - 0x10010000+(3)]);
            for(int i=1; i<4;i++)
            {
                registers[rt]= registers[rt]<<(8) | (memory[registers[rs] +signedImm - 0x10010000+(3-i)]);
            }
            
            
            break;
            
        case 0x2b://SW
            
            for(int i=0; i<4;i++)
            {
                memory[registers[rs] - 0x10010000+signedImm+i]=(unsigned(registers[rt])>>(8*i))& 0x000000ff;
                
            }

            
            break;
            
        case 0x20://LB
            registers[rt]= memory[registers[rs] +signedImm - 0x10010000];
            
            break;
            
        case 0x28://SB
            memory[registers[rs] +signedImm - 0x10010000] = registers[rt];
            
            break;
            
        case 0x21://LH
            
            registers[rt] = memory[registers[rs] +signedImm - 0x10010000+1];
            registers[rt] = registers[rt]<<8 | memory[registers[rs] +signedImm - 0x10010000];
            
            break;
            
        case 0x29://SH

            memory[registers[rs] +signedImm - 0x10010000] = registers[rt] & 0x000000ff;
            memory[registers[rs] +signedImm - 0x10010000+1 ]= unsigned(registers[rt])>>8 & 0x000000ff ;
            
            break;
            
        case 0x04://BEQ

            if(registers[rt]==registers[rs])
                pc=pc+signedImm;
           
            break;
            
        case 0x05: // BNE
            if(registers[rt]!=registers[rs])
                pc=pc+signedImm;
            
            break;
            
        case 0x0a: //SLTI
            if(registers[rs]<signedImm)
                registers[rt]=1;
            else
                registers[rt]=0;
            
            break;
            
        case 0x0f://LUI
            int temp=0;
            temp=imm<<16;
            registers[rt]=temp;

            break;
            
            
    }
    
    //for now
    return false;
}

unsigned short IFormat::returnFunction()
{
   unsigned short s=0;
   return s;
}













