#include "CPU.h"
using namespace std;
#include <iostream>
#include <fstream>
#include <string>
#include "inputException.h"
#include <stdlib.h>
#include <QString>

CPU::CPU(string name):filename(name)  // constructor receives the file name
{  
	for (int i=0; i<8; i++)
			buffer1old[i]=0;
		for (int i=0; i<20; i++)
			buffer2old[i]=0;
		for (int i=0; i<18; i++)
			buffer3old[i]=0;
		for (int i=0; i<9; i++)
			buffer4old[i]=0;

	// initializing regfile
	for (int i = 0; i < 32; i++)
		RegFile[i] = 0;
	// initializing dataMem
	for (int i = 0; i < 32; i++)
		DataMem[i]  = 0;
	DataMem[6] = 35; 

	RegFile[17] = 5;
	RegFile[18] = 3;
    
    for(bool i : stages)
    {
        i=0;
    }

	finalEn = false;
	fetchEn =true;
	decodeEn = true;
	execEn = true;
	memEn = true;
	wbEn = true;
    finalfooEn = false; //so that the clock at final instruction is set only once at fetch, instead of at each stage.
	finalInst = false;
	branchFound = false;
    boolStall = false;
	clkWAtFinalInst=clkAtFinalInst=400000;

   // this->loadAndParse(this->filename);
}
void CPU::test()
{
    for(int i : stages)
    {
        i=0;
    }

    fetch();
    WriteBack();
    execute();
    MemAccess();
    Decode();

    for (int i=0; i<8; i++)
        buffer1old[i]=buffer1new[i];
    for (int i=0; i<20; i++)
        buffer2old[i]=buffer2new[i];
    for (int i=0; i<18; i++)
        buffer3old[i]=buffer3new[i];
    for (int i=0; i<9; i++)
        buffer4old[i]=buffer4new[i];

}



CPU::~CPU()
{
}

void CPU:: control (int instNum) //generates the control signals
{

	switch (instNum)
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
        RegFile[31]= buffer1old[0]+1;
		break;
	case 10:   //jr
		jumpReg= true;
		regWrite= false;
        PC =  RegFile[buffer1old[2]];
		break;
	case 11:   //jumpProcedure
		jump= true;
		regWrite= false;
            if(returnAddresses.size()<4)
         returnAddresses.push(buffer1old[0]+1);
		break;
	case 12:   //returnProcedure
		jumpReg= true;
		regWrite= false;
            if(returnAddresses.size()!=0)
            {
                PC = returnAddresses.top();
                returnAddresses.pop();
                
            }
            else
            {
                jumpReg = false;
            }
        break;
	default:
		
            ALUOp=4; //invalid
	}

	buffer2new[7] = regWrite;
	buffer2new[8] = regDest;
	buffer2new[9] = ALUSrc;
	buffer2new[10] = ALUOp;
	buffer2new[11] = branch;
	buffer2new[12] = memRead;
	buffer2new[13] = memWrite;
	buffer2new[14] = memToReg;
	buffer2new[15] = jump;
	buffer2new[16] = jumpReg;
	buffer2new[17] = buffer1old[7];
	buffer2new[18]= buffer1old[2];//rs
	buffer2new[19]=buffer1old[3];  //rt
}


void CPU::fetch()
{
   if( boolStall)
   {
        stages[0]=0;
       boolStall=false;
   }
    
       if(fetchEn == false)
       {
           stages[0]=0;
           return;
       }
    
	
	// control signals initialization
	regWrite= true;
	regDest= true;
	ALUSrc= false;    //control signal (0: read from reg, 1: imm)
	branch= false;   //control signal 
	memRead= false;   //control signal 
	memWrite= false;   //control signal 
	memToReg= false;  //control signal 
	jump= false;    //control signal 
	jumpReg= false; 


		IM[PC].setClkAtFet(clk);
	buffer1new[0] = PC;
	buffer1new[1] = IM[PC].getInstNum(); 
	buffer1new[2] = IM[PC].getRs();
	buffer1new[3] = IM[PC].getRt();
	buffer1new[4] = IM[PC].getRd();
	buffer1new[5] = IM[PC].getImm();
	buffer1new[6] = IM[PC].getClkAtFet();
    buffer1new[7] = branchFound; 

    if(PC== (IM.size()-1))//final instruction
    {
        finalInst=true;
        
        if(!finalfooEn){
            clkAtFinalInst = clk;
            finalfooEn=true;
        }
        if(IM[PC].getInstNum() != 6) return;
    }
    


	if (IM[PC].getInstNum() == 6)    // branch instruction
	{
		branch = true; 
		buffer2new[11] = buffer2old[11] = true;
		buffer2old[10] = 1;    // aluop for ble
		if (Found(PC))   // if branch instruction found in btb
		{
			if (branchTaken(PC))  // taken = true in btb
				PC = Predicted(PC);
			//else
				// PC++ noraml execution??????????????
		}
		else  // not found in btb
		{
			InsertInBtb(PC,PC+1+IM[PC].getImm());
			// PC++ normal execution  ????????????
		}
	}




	programCounter(); // (imm,jump, branch,fetchEn)


        stages[0]=validFetch();

}

void CPU::Decode()
{
	  
    if(decodeEn == false)
    {
        stages[1]=0;
        return;
    }
    
    RD=0;
    // if R-format
    if (buffer1old[1] == 1 || buffer1old[1] == 3 || buffer1old[1] == 8)  // ADD/XOR/SLT
        RD = buffer1old[4];
    else // if I-format
        if (buffer1old[1] == 2 || buffer1old[1] == 4)   // ADDI/LW
            RD = buffer1old[3];
    
     
    control(buffer1old[1]);

   if (buffer2new[12] && ((buffer2new[19]==buffer1old[2]) || (buffer2new[19]==buffer1old[3]))) //memRead AND(rt==rs or rt==rt )  //load hazard
	{
		stall();
        
        boolStall = true;
	    		
	} 

    
    buffer2new[0] = buffer1old[0];//PC
    buffer2new[1] = RegFile[buffer1old[2]];  // rs
    buffer2new[2] = RegFile[buffer1old[3]];   // rt
    buffer2new[3] = buffer1old[5];    // imm
    buffer2new[4] = RD;
    buffer2new[5] = buffer1old[6];   // clkAtFetch
    buffer2new[6] = clk;
   

        stages[1]=validDecode();


    if(finalfooEn && (jumpReg || jump) )
    {
        finalfooEn = false;
    }
    
    if(jumpReg) // JR or RP
    {		    // imm
        flushFetch();
    }

    if(jump) // JAL or JP
    {		   // imm
        PC = buffer1old[5];
        flushFetch();
    }
    

    if(!( jump==true || branch == true || jumpReg) && clkAtFinalInst==buffer1old[6])
    {
        
        decodeEn=false;
        stages[0]=0;
        finalEn=true;
        
    }
//    if(( jump==true || branch == true ||jumpReg)&& clkAtFinalInst==buffer1old[6])
//    {
//        finalfooEn=false;
//    }
//    else if (clkAtFinalInst==buffer1old[6]) finalfooEn= false;
    //else if(!finalEn)
    //{
    //	execEn = false;
    //}
    

    
}

void CPU:: execute()
{
    int firstoperand;
    if(execEn == false)
    {
        stages[2] = 0;
        return;
    }

    ALUResult = 0; // initialize to zero so that when it doesn't compute something it doesn't resturn previous result
    zeroflag=0;
    int secoperand;  //imm or data from reg


    //FORWARDING
    if (buffer3old[5] &&  !buffer2old[12] && buffer3old[4]==buffer2old[18] && buffer3old[4]!=0) //RegWrite AND rd=rs
        firstoperand= buffer3old[2];				//ALUResult directly from buffer
    else
        if (buffer4old[3]  &&(buffer4old[2]== buffer2old[18]) && (buffer4old[2]!=0) &&
            !(buffer3old[5] && buffer3old[4]!=0 && (buffer3old[4]==buffer2old[18])))
                                                                //RegWrite AND rd=rs AND !(regwrite & rd==rs)
             firstoperand= wbData;
        else
            firstoperand= buffer2old[1];

    if (buffer2old[9])   // addi or lw or sw
        secoperand = buffer2old[3];

    else
    if (buffer3old[5] &&  !buffer2old[12] && buffer3old[4]==buffer2old[19] && buffer3old[4]!=0) //RegWrite AND                  rd=rt
        secoperand= buffer3old[2]; //ALUResult directly from buffer
    else
        if ((buffer4old[3] && (buffer4old[2]== buffer2old[19]) && buffer4old[2]!=0 ) &&
            !(buffer3old[5] && (buffer3old[4]!=0) && (buffer3old[4]==buffer2old[19])))
                 //RegWrite AND    rd=rt   AND !(regwrite & rd=rt)
                 secoperand= wbData;
        else
    {
        //if (buffer2old[9]) //addi or lw or sw, the sec operand is the immediate
            //secoperand = buffer2old[3];
        //else
            secoperand= buffer2old[2];
    }
    switch (buffer2old[10])   // aluOp
    {
    case 0:   //add

        ALUResult = firstoperand+secoperand;
        break;
    case 1:   //sub
        ALUResult= firstoperand-secoperand;
        if (firstoperand && ALUResult<=0)  //ble
            zeroflag=1;
        break;
    case 2:   //xor
        ALUResult= firstoperand^secoperand;
        break;
    case 3:   //slt
        if (firstoperand<secoperand)
            ALUResult= 1;
        else
            ALUResult=0;
        break;
    default:
        ALUResult=-1;
    }

    // If its a branch instruction
    if (buffer2old[11] && zeroflag)    // branch is taken
    {
        if (!branchTaken(buffer2old[0]))  // if taken = false
        {
            assignTaken(buffer2old[0],1); // taken = true
            PC = Predicted(buffer2old[0]);
            // remove previous fetched instructions  ???????
            flushThree();
        }
    }
    else
    if (buffer2old[11] && !zeroflag)   // branch not taken
    {
        if (branchTaken(buffer2old[0]))  // if taken = true
        {
            assignTaken(buffer2old[0],0);  // taken = false
            // PC++ normal pc increment
            flushThree();
            // remove previous fetched instructions  ???????
        }
    }


    //input to the Exec/Mem buffer
    buffer3new[0]= buffer2old[0];  // pc
    buffer3new[1]= zeroflag;
    buffer3new[2]= ALUResult;
    buffer3new[3]= buffer2old[2];  // rt
    buffer3new[4]= buffer2old[4];  // rd
    buffer3new[5]= buffer2old[7];  // regwrite
    buffer3new[6]= buffer2old[8];   // regdest
    buffer3new[7]= buffer2old[11];   // branch
    buffer3new[8]= buffer2old[12];   // memread
    buffer3new[9]= buffer2old[13];   // memwrite
    buffer3new[10]= buffer2old[14];  // memtoreg
    buffer3new[11]= buffer2old[15];   // jump
    buffer3new[12]= buffer2old[16]; //jumpreg
    buffer3new[13] = clk;
    buffer3new[14]= buffer2old[3]; //imm
    buffer3new[15]= buffer2old[5]; // Clk at fetch
    buffer3new[16]= buffer2old[6]; // clk at Dec
    buffer3new[17] = buffer2old[17];     // branchFound

        stages[2]=validExecute();


    if(clkAtFinalInst==buffer2old[5]&& finalfooEn)
    {
        execEn=false;
    }


}

void CPU::MemAccess()
{   
    if(memEn == false)
    {
        stages[3] = 0;
        return;
    }
    
    int MemReadData=0;  // output of data memory
                        // int PC;
       
    if (buffer3old[9])    // memwrite
        DataMem[buffer3old[2]] = buffer3old[3];      // Datamem[ALUresult]
    
    if (buffer3old[10])  // memread
        MemReadData = DataMem[buffer3old[2]];
    
    buffer4new[0] = MemReadData;
    buffer4new[1] = buffer3old[2]; //alu
    buffer4new[2] = buffer3old[4];   // rd
    buffer4new[3] = buffer3old[5];   // regwrite
    buffer4new[4] = buffer3old[10];  // memtoreg
    buffer4new[5] = clk;         // clkAtmemAccess
    buffer4new[6] = buffer3old[13]; // clk at exec
    buffer4new[7] = buffer3old[15]; //clk at F
    buffer4new[8] = buffer3old[16]; // clk at D
    

        stages[3]=validMemory();

    if(clkAtFinalInst==buffer3old[15]&& finalfooEn)
    {
        memEn=false;
    }
    
}

void CPU:: WriteBack()
{
    if(wbEn == false)
    {
        stages[4] = 0;
        return;
    }

     
   // int wbData;
    if (buffer4old[4])  // memtoreg
        wbData = buffer4old[0];
    else
        wbData = buffer4old[1];
    if (buffer4old[3] && buffer4old[2]!=0) // regwrite
        RegFile[buffer4old[2]] = wbData;
    

        stages[4]=validWb();


    if(finalEn ==true && clkAtFinalInst == buffer4old[7])
    {
        execEn = false;
        wbEn=false;
        clkWAtFinalInst=clk;
    }
}

//private functions

void CPU::programCounter()
{
	
	/*  if( rst == true){
	PC = 0;
	clk = 0;
	}*/    // initialized in constructor
	if(fetchEn)
	{
		if(!jump)        
			PC++;     // normal increment

		//cout << "PC in fetch " << PC << endl;
		/*else 
		
		
	if(jump==1)     //branch instruction  
		{
		if(branch == true)
		PC = (PC+1) + buffer2[3];    // imm
		else
		PC = PC+1;// no branch, so pc increments as normal
		} */ 

		/* else if (jump==3)//JAL
		{
		RegFile[31] = PC+1;
		PC = buffer2[3];
		}
		else if (jump==4)//JR{
		//  PC = RegFile[rs]; /// HEYYYYY !!! MEEN RS DAH 

		else if (jump==5)//JumpProced
		{
		returnAddresses.push(PC+1);
		PC = buffer2[3];
		}
		else if (jump==6)//ReturnProced
		{
		PC = returnAddresses.top();
		returnAddresses.pop();
		}*/
	}
	/*else if( stall)
	{
		PC--; //Stall fetching the next instruction	
	}*/

}

void CPU::flush()
{
	for (int i=0; i<8; i++)
	{
	//		buffer1old[i]=0;
			buffer1new[i]=0;
	}
		for (int i=0; i<20; i++)
		{
			buffer2old[i]=0;
		//	buffer2new[i]=0;
		}
		for (int i=0; i<18; i++)
		{
			buffer3old[i]=0;
		//	buffer3new[i]=0;
		}
		for (int i=0; i<9; i++)
		{
			buffer4old[i]=0;
		 //buffer4new[i]=0;
		}

//        for (int i=1; i<4; i++)
//        {
//            stages[i]= 0;
//        }

}

void CPU::flushThree()
{
    for (int i=0; i<8; i++) // buffer 1
    {
        buffer1old[i]=0;
        buffer1new[i]=0;
    }
    for (int i=0; i<20; i++)  // buffer 2
    {
        buffer2old[i]=0;
        buffer2new[i]=0;
    }

    stages[0]=stages[1] = 0;

   /* for (int i=0; i<18; i++)
    {
        buffer3old[i]=0;
        buffer3new[i]=0;
    }*/
    
}

void CPU::flushFetch()
{
    for (int i=0; i<7; i++)
    {
        buffer1old[i]=0;
    }
    stages[0] = 0;
}

int CPU:: nametoNum(string name, bool cut)
{
    if(cut){
        string::iterator iter = name.end()-1;
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
    else
    {
        QString imm= QString::number(IM.size()+1);
        throw inputException(imm.QString::toStdString());

    };
}

bool CPU::Found(int address)
{
    for (int i = 0; i < btb.size(); i++)
        if (btb[i].branchAddress == address)
            return true;
    return false;
}

int CPU::Predicted(int pc)
{
    for (int i = 0; i < btb.size(); i++)
        if (btb[i].branchAddress == pc)
            return btb[i].predictedPC;
    return 0;
}

void CPU :: InsertInBtb(int address,int predicted)  // inserts record in btb
{
    BTB temp;
    temp.branchAddress = address;
    temp.predictedPC = predicted;
    temp.taken = false;   // assume initially not taken
    btb.push_back(temp); 
}

void CPU :: stall()
{
	flush();
	PC--;
}

bool CPU:: branchTaken(int pc)
{
	for (int i = 0; i < btb.size(); i++) 
		if (btb[i].branchAddress == pc && (btb[i].taken))
			return true;
	return false; 

}

void CPU :: assignTaken(int pc, int n)
{
	for (int i = 0; i < btb.size(); i++)
		if (btb[i].branchAddress == pc)
			if (n == 1)
				btb[i].taken = true; 
			else if( n == 0) 
				btb[i].taken = false; 
}

int CPU::getClk()
{
    return clk;
}

void CPU::incrementClk()
{
    clk++;
}

int CPU::getClkWAtFinal()
{
    return clkWAtFinalInst;
}

void CPU::reset()
{
    btb.clear();
    for (int i=0; i<8; i++)
            buffer1old[i]=buffer1new[i]=0;
        for (int i=0; i<20; i++)
            buffer2old[i]=buffer2new[i]=0;
        for (int i=0; i<18; i++)
            buffer3old[i]= buffer3new[i]=0;
        for (int i=0; i<9; i++)
            buffer4old[i]= buffer4new[i]=0;

    // initializing regfile
    for (int i = 0; i < 32; i++)
        RegFile[i] = 0;
    // initializing dataMem
    for (int i = 0; i < 32; i++)
        DataMem[i]  = 0;
    DataMem[6] = 35;

    RegFile[17] = 5;
    RegFile[18] = 3;


    for(bool &i : stages)
        i=0;
    finalEn = false;
    fetchEn =true;
    decodeEn = true;
    execEn = true;
    memEn = true;
    wbEn = true;
    finalfooEn = false; //so that the clock at final instruction is set only once at fetch, instead of at each stage.
    finalInst = false;
    branchFound = false;
    boolStall = false;
    clkWAtFinalInst=clkAtFinalInst=400000;
}

void CPU::loadAndParse(string name)
{
    reset();
    IM.clear();
    textIM.clear();
    ifstream in;
    if(name=="")
        in.open(filename.c_str());
    else in.open(name.c_str());
    bool fail = in.fail();

    if(fail)
        throw inputException("Unable to open file, please check file path");
    InstructionT temp;
    string instName, reg1, reg2, reg3;
            QString imm;
    string tempText;
    PC = 0;
    clk = 1;
    
    while (!in.eof())
    {
        
         instName="NOP";
         reg1="0"; reg2="0"; reg3="0";

        imm="";
        tempText ="";

        in>>instName;
        
        /*     for (char &i : instName)
         {
         toupper(instName[i]);
         }  */
        for(int i=0; i<instName.size();i++)
            instName[i]=toupper(instName[i]);
        try {
            if(instName == "ADD")
            {
                
                in>>reg1>>reg2>>reg3;
                temp.setRd(nametoNum(reg1));
                temp.setRt(nametoNum(reg3, 0));
                temp.setRs(nametoNum(reg2));
                temp.setInstNum(1);
                
                tempText = instName + " " + reg1 + " " +reg2 + " " +reg3;
                
            } else if(instName == "ADDI")
            {
                string tempS;


                in>>reg1>>reg2>>tempS;
                imm=QString::fromStdString(tempS);
                if(imm.QString::toInt()==0)
                {
                    if(imm=="0")
                        temp.setImm(imm.QString::toInt());
                    else
                    {
                        imm = QString::number(IM.size()+1);
                        throw invalid_argument(imm.QString::toStdString());
                    }
                }
                temp.setImm(imm.QString::toInt());
                temp.setRs(nametoNum(reg2));
                temp.setRt(nametoNum(reg1));

                tempText = instName + " " + reg1 + " " +reg2 + " " +imm.QString::toStdString();
                
                temp.setInstNum(2);
                
            } else if(instName == "XOR")
            {
                in>>reg1>>reg2>>reg3;
                temp.setRd(nametoNum(reg1));
                temp.setRt(nametoNum(reg3,0));
                temp.setRs(nametoNum(reg2));
                temp.setInstNum(3);
                
                tempText = instName + " " + reg1 + " " +reg2 + " " +reg3;
                
            } else if(instName == "LW")
            {
                string tempS;
                in>> reg1;
                getline(in, tempS, '(');
                getline(in, reg2, ')');

                imm=QString::fromStdString(tempS);

                if(imm.QString::toInt()==0)
                {
                    if(imm=="0")
                        temp.setImm(imm.QString::toInt());
                    else
                    {
                        imm = QString::number(IM.size()+1);
                        throw invalid_argument(imm.QString::toStdString());
                    }
                }
                temp.setImm(imm.QString::toInt());
                temp.setRt(nametoNum(reg1));
                temp.setRs(nametoNum(reg2,0));
                temp.setInstNum(4);
                
                tempText = instName + " " + reg1 + " " +imm.QString::toStdString() + "(" +reg2 + ")";
                
            } else if(instName == "SW")
            {
                string tempS;
                in>> reg1;
                getline(in, tempS, '(');
                getline(in, reg2, ')');
                
                temp.setRt(nametoNum(reg1));
                imm=QString::fromStdString(tempS);
                if(imm.QString::toInt()==0)
                {
                    if(imm=="0")
                        temp.setImm(imm.QString::toInt());
                    else
                    {
                        imm = QString::number(IM.size()+1);
                        throw invalid_argument(imm.QString::toStdString());
                    }
                }
                temp.setRs(nametoNum(reg2,0));
                temp.setInstNum(5);
                temp.setImm(imm.QString::toInt());
                tempText = instName + " " + reg1 + " " +imm.QString::toStdString() + "(" +reg2 + ")";
                
            } else if(instName == "BLE")
            {
                string tempS;
                in>>reg1>>reg2>>tempS;
                imm=QString::fromStdString(tempS);
                if(imm.QString::toInt()==0)
                {
                    if(imm=="0")
                        temp.setImm(imm.QString::toInt());
                    else
                    {
                        imm = QString::number(IM.size()+1);
                        throw invalid_argument(imm.QString::toStdString());
                    }
                }
                temp.setRs(nametoNum(reg1));
                temp.setRt(nametoNum(reg2));
                temp.setInstNum(6);
                temp.setImm(imm.QString::toInt());
                tempText = instName + " " + reg1 + " " +reg2 + " " +imm.QString::toStdString();
                
            } else if(instName == "J")
            {
                string tempS;
                in>>tempS;
                imm=QString::fromStdString(tempS);
                if(imm.QString::toInt()==0)
                {
                    if(imm=="0")
                        temp.setImm(imm.QString::toInt());
                    else
                    {
                        imm = QString::number(IM.size()+1);
                        throw invalid_argument(imm.QString::toStdString());
                    }
                }
                temp.setInstNum(7);
                temp.setImm(imm.QString::toInt());
                tempText = instName + " " + imm.QString::toStdString();
                
            } else if(instName == "SLT")
            {
                in>>reg1>>reg2>>reg3;
                temp.setRd(nametoNum(reg1));
                temp.setRt(nametoNum(reg3, 0));
                temp.setRs(nametoNum(reg2));
                temp.setInstNum(8);
                
                tempText = instName + " " + reg1 + " " +reg2 + " " +reg3;
                
            } else if(instName == "JAL")
            {
                string tempS;
                in >>tempS;
                imm=QString::fromStdString(tempS);
                if(imm.QString::toInt()==0)
                {
                    if(imm=="0")
                        temp.setImm(imm.QString::toInt());
                    else
                    {
                        imm = QString::number(IM.size()+1);
                        throw invalid_argument(imm.QString::toStdString());
                    }
                }
                temp.setInstNum(9);
                temp.setImm(imm.QString::toInt());
                tempText = instName + " " + imm.QString::toStdString();
                
            } else if(instName == "JR")
            {
                in >>reg1;
                temp.setRs(nametoNum(reg1,0));
                temp.setInstNum(10);
                
                tempText = instName + " " + reg1;
            } else if(instName == "JP")
            {
                string tempS;
                in >>tempS;
                imm=QString::fromStdString(tempS);
                if(imm.QString::toInt()==0)
                {
                    if(imm=="0")
                        temp.setImm(imm.QString::toInt());
                    else
                    {
                        imm = QString::number(IM.size()+1);
                        throw invalid_argument(imm.QString::toStdString());
                    }
                }
                temp.setInstNum(11);
                temp.setImm(imm.QString::toInt());
                tempText = instName + " " + imm.QString::toStdString();
                
            } else if(instName == "RP")
            {
                temp.setInstNum(12);
                
                tempText = instName;
            } else {
                //NOP
                string shit;
                getline(in,shit);
                if(instName.find("NOP")!=-1)
                {
                    temp.setInstNum(0);
                    tempText = instName;
                }
                
                else
                {
                    imm = QString::number(IM.size()+1);
                    string s = "Incorrrect syntax at line:";
                    s+= imm.QString::toStdString();
                    throw inputException(s);
                }
            }
        }
        catch(const invalid_argument & m)
        {
            imm = QString::number(IM.size()+1);
            throw invalid_argument(imm.QString::toStdString());
        }
        
        
        
        IM.push_back(temp);
        textIM.push_back(QString::fromStdString(tempText));
        
        /*	cout << temp.getInstNum();
         cout << temp.getRs();
         cout << temp.getRt();
         
         */
        temp.clear();
        tempText.clear();
    }
    //}
    IM.pop_back();
    textIM.pop_back();
    in.close();
}

bool CPU::validFetch ()
{

        return (buffer1new[1]!=0 && fetchEn); // IM[PC].getInstNum() && fetchEn
}

bool CPU::validDecode ()
{

        return (buffer2new[10]!=4 && decodeEn);
}

bool CPU::validExecute()
{
    return (buffer3new[2]!=-1  && execEn);
}

bool CPU::validMemory()
{

    return( (buffer3old[9] ||buffer4new[4])&& memEn);

}

bool CPU::validWb()
{
    return(wbEn && ((buffer4old[4]||buffer4old[3]) )); // (memtoreg|| regwrite) && finalfooEn
}

int CPU::getPC()
{
    return PC;
}

bool CPU::getFinalFoo()
{
    return finalfooEn;
}
