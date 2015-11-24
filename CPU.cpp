#include "CPU.h"
using namespace std;
#include <iostream>
#include <fstream>

CPU::CPU(string name)    // constructor receives the file name 
{
	filename = name;
    ifstream in;
    in.open(name.c_str());
    
    string instName, reg1, reg2, reg3, offset, imm;
    while (!in.eof())
    {
        in>>instName;
        
        if(instName == "ADD")
        {
            in>>reg1>>reg2>>reg3;
            
        } else if(instName == "ADDI")
        {
            
        } else if(instName == "XOR")
        {
            
        } else if(instName == "LW")
        {
            
        } else if(instName == "SW")
        {
            
        } else if(instName == "BLE")
        {
            
        } else if(instName == "J")
        {
            
        } else if(instName == "SLT")
        {
            
        } else if(instName == "JAL")
        {
            
        } else if(instName == "JR")
        {
            
        } else if(instName == "JP")
        {
            
        } else if(instName == "RP")
        {
            
        } else {
            //NOP
        }
            
                  
    }
    
    
    in.close();
    
}

CPU::~CPU()
{
}

void CPU:: control () //generates the control signals
{	
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

void CPU:: execute()
{
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

//test