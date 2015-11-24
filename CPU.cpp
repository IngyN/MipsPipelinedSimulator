#include "CPU.h"
using namespace std;
#include <iostream>
#include <fstream>

CPU::CPU(string name)    // constructor receives the file name 
{
	filename = name;
    ifstream in;
    in.open(name.c_str());
    Instruction temp;
    string instName, reg1, reg2, reg3, offset, imm;
    
    while (!in.eof())
    {
        in>>instName;
        
        if(instName == "ADD")
        {
            in>>reg1>>reg2>>reg3;
            temp.setRd(nametoNum(reg1));
            temp.setRt(nametoNum(reg3, 0));
            temp.setRs(nametoNum(reg2));
            temp.setInstNum(1);
            
        } else if(instName == "ADDI")
        {
            in>>reg1>>reg2>>imm;
            temp.setImm(nametoNum(reg3,0));
            temp.setRs(nametoNum(reg2));
            temp.setRt(nametoNum(reg1));
            
            temp.setInstNum(2);
            
        } else if(instName == "XOR")
        {
            in>>reg1>>reg2>>reg3;
            temp.setRd(nametoNum(reg1));
            temp.setRt(nametoNum(reg3,0));
            temp.setRs(nametoNum(reg2));
            temp.setInstNum(3);
            
        } else if(instName == "LW")
        {
            in>> reg1;
            getline(in, offset, '(');
            getline(in, reg2, ')');
            
            temp.setRt(nametoNum(reg1));
            temp.setOffset(stoi(offset));
            temp.setRs(nametoNum(reg2,0));
            temp.setInstNum(4);
            
        } else if(instName == "SW")
        {
            in>> reg1;
            getline(in, offset, '(');
            getline(in, reg2, ')');
            
            temp.setRt(nametoNum(reg1));
            temp.setOffset(stoi(offset));
            temp.setRs(nametoNum(reg2,0));
            temp.setInstNum(5);
            
        } else if(instName == "BLE")
        {
            in>>reg1>>reg2>>offset;
            
            temp.setRs(nametoNum(reg1));
            temp.setRt(nametoNum(reg2));
            temp.setOffset(stoi(offset));
            temp.setInstNum(6);
        } else if(instName == "J")
        {
            in>>imm;
            
            temp.setImm(stoi(imm));
            temp.setInstNum(7);
            
        } else if(instName == "SLT")
        {
            in>>reg1>>reg2>>reg3;
            temp.setRd(nametoNum(reg1));
            temp.setRt(nametoNum(reg3, 0));
            temp.setRs(nametoNum(reg2));
            temp.setInstNum(8);
        } else if(instName == "JAL")
        {
            in >>imm;
            temp.setImm(stoi(imm));
            temp.setInstNum(9);
        } else if(instName == "JR")
        {
            in >>reg1;
            temp.setRs(nametoNum(reg1,0));
            temp.setInstNum(10);
        } else if(instName == "JP")
        {
            in >> imm;
            temp.setImm(stoi(imm));
            temp.setInstNum(11);
        } else if(instName == "RP")
        {
            temp.setInstNum(12);
        } else {
            //NOP
            temp.setInstNum(0);
        }
        
        IM.push_back(temp);
        temp.clear();
                  
    }
    
    
    in.close();
    
}

int nametoNum(string  & name, bool cut = true)
{
    if(cut){
    string::iterator iter = name.end();
    name.erase(iter);
    }
    
    if(name == "$zero")
    {
        return 0;
    } else if(name == "$at")
    {
        return 1;
    } else if(name == "$v0")
    {
        return 2;
    } else if(name == "$v1")
    {
        return 3;
    } else if(name == "$a0")
    {
        return 4;
    } else if(name == "$a1")
    {
        return 5;
    } else if(name == "$a2")
    {
        return 6;
    } else if(name == "$a3")
    {
        return 7;
    } else if(name == "$t0")
    {
        return 8;
    } else if(name == "$t1")
    {
        return 9;
    } else if(name == "$t2")
    {
        return 10;
    } else if(name == "$t3")
    {
        return 11;
    } else if(name == "$t4")
    {
        return 12;
    } else if(name == "$t5")
    {
        return 13;
    } else if(name == "$t6")
    {
        return 14;
    }else if(name == "$t7")
    {
        return 15;
    } else if(name == "$s0")
    {
        return 16;
    } else if(name == "$s1")
    {
        return 17;
    } else if(name == "$s2")
    {
        return 18;
    } else if(name == "$s3")
    {
        return 19;
    } else if(name == "$s4")
    {
        return 20;
    } else if(name == "$s5")
    {
        return 21;
    } else if(name == "$s6")
    {
        return 22;
    } else if(name == "$s7")
    {
        return 23;
    } else if(name == "$t8")
    {
        return 24;
    } else if(name == "$t9")
    {
        return 25;
    } else if(name == "$k0")
    {
        return 26;
    } else if(name == "$k1")
    {
        return 27;
    } else if(name == "$gp")
    {
        return 28;
    } else if(name == "$sp")
    {
        return 29;
    } else if(name == "$fp")
    {
        return 30;
    } else if(name == "$ra")
    {
        return 31;
    }
    else return -1;
}

CPU::~CPU()
{
}

void CPU:: control () //generates the control signals
{
    regWrite= true;
    regDest= true;
	ALUSrc= false;    //control signal (0: read from reg, 1: imm)
    branch= false;   //control signal 
    memRead= false;   //control signal 
    memWrite= false;   //control signal 
    memToReg= false;  //control signal 
    jump= false;    //control signal 
    jumpReg= false; 
	switch (Inst.num)
	{	case 1:   //add
			ALUOp=0;
			break;
		case 2:   //addi
			ALUOp=0;
			regDest= false;
			ALUSrc= true;
			break;
		case 3:   //xor
			ALUOp=2;
			break;
		case 4:  //lw
			regDest= false;
			ALUSrc= true;
			ALUOp=0;
			memRead= true;
			memToReg= true;
			break;
		case 5:   //sw
			regWrite= false;
			ALUSrc= true;
			ALUOp=0;
			memWrite= true;
			break;
		case 6:   //ble
			regWrite= false;
			ALUOp=1; //subtract
			branch= true;
			break;
		case 7:   //j
			jump= true;
			regWrite= false;
			break;
		case 8:   //slt
			ALUOp= 3;
			break;
		case 9:   //jal   
			jump= true;
			break;
		case 10:   //jr
			jumpReg= true;
			regWrite= false;
			break;
		case 11:   //jumpProcedure
			jump= true;
			regWrite= false;
			break;
		case 12:   //returnProcedure
			jumpReg= true;
			regWrite= false;
			break;
		default:
			ALUOp=4; //invalid 
	}
}


void CPU::fetch()
{
    programCounter(/*imm  jumpCtrl, branchEn, fetchEn*/);
    IM[PC].clkAtFet = clk;
    buffer1[0] = IM[PC];
    
}

void CPU:: execute()
{  zeroflag=0;
	int secoperand;  //imm or data from reg
	if (Inst.num == 2 || Inst.num == 4 || Inst.num==5 ) //addi or lw or sw, the sec operand is the immediate
		secoperand= buffer2[3];
	else 
		secoperand= buffer2[2];
	switch (ALUOp)
	{
	case 0:   //add  
		ALUResult= buffer2[1]+secoperand;  
		break;
	case 1:   //sub
		ALUResult= buffer2[1]-secoperand;
		if (Inst.num==6 && ALUResult<=0)  //ble
			zeroflag=1;
		break;
	case 2:   //xor
		ALUResult= buffer2[1]^secoperand;
		break;
	case 3:   //slt
		if (buffer2[1]<secoperand)
			ALUResult= 1;
		else 
			ALUResult=0;
		break;
	default:
		ALUResult=-1;
	}
	//input to the Exec/Mem buffer
	buffer3[0]= buffer2[0]; 
	buffer3[1]= zeroflag;
	buffer3[2]= ALUResult;
	buffer3[3]= buffer2[2];
	buffer3[4]= buffer2[4];
}
void CPU::Decode() 
{  
	Instruction Inst = buffer1[1]; 
	// Assuming all parameters of instruction (Rs,Rt,Rd,Imm are initialized to -1)
	ReadReg1 = Inst.rs;      // rs
	ReadReg2 = Inst.rt;      // rt
	ReadData1 = RegFile[ReadReg1];
	ReadData2 = RegFile[ReadReg2];

	// if R-format
	if (Inst.num == 1 | Inst.num == 3 | Inst.num == 8)  // ADD/XOR/SLT
		RD = Inst.rd;
	else // if I-format
		if (Inst.num == 2 | Inst.num == 4)   // ADDI/LW
			RD = Inst.rt;
		else
			if (Inst.num == 9) //JAL
				// RD = index of rs

	buffer2[0] = buffer1[0];
	buffer2[1] = ReadData1;
	buffer2[2] = ReadData2; 
	buffer2[3] =  Inst.imm;
	buffer2[4] = RD; 
}

//private functions

void CPU::programCounter()
{
    if( rst == true)
        PC = 0;
    else if(fetchEn ==true)
    {
        if(jump ==0)//Normal PC increment
            PC = PC+1;
        else if(jump==1)//branch instruction
        {
            if(branch == true)
                PC = (PC+1) + Inst.imm;
            else
                PC = PC+1;// no branch, so pc increments as normal
        }
        
        else if(jump == 2)//Jump
            PC = Inst.imm;
        else if (jump==3)//JAL
        {
            ra = PC+1;
            PC = Inst.imm;
        }
        else if (jump==4)//JR
            //PC = ra;
        
        else if (jump==5)//JumpProced
        {
            returnAddresses.push(PC+1);
            PC = Inst.imm;
        }
        else if (jump==6)//ReturnProced
        {
            PC = returnAddresses.top();
            returnAddresses.pop();
        }
    }
    else if(fetchEn == false )
    {
        //Stall fetching the next instruction
    }
    
    
}

//test