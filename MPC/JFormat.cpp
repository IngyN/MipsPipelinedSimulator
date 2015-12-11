//
//  JFormat.cpp
//  AssemblyProject
//
//  Created by Ingy on 3/24/15.
//  Copyright (c) 2015 Ingy. All rights reserved.
//

#include "JFormat.h"
#include <iostream>
#include <cmath>
#include <iomanip>
#include <QString>
using namespace std;

JFormat::JFormat()
{
    
}

JFormat::~JFormat()
{
    
}

void JFormat::decode ()
{
    //j, jal
    
    // get target Address
    
    // mask opcode in the word
    targetAddress = this->Instruction::word & 0x03ffffff;
    
    // shift left 2 bits (add 00 at the end)
    targetAddress <<= 2;
    

}

string JFormat::display()
{
    string s;
    switch (opcode) {
        case 0x02:
            // j
            s="\tj\t"+QString::number(targetAddress).toStdString()+"\n";
            break;
            
        case 0x03:
            // jal
            s="\tjal\t"+QString::number(targetAddress).toStdString()+"\n";
            break;
            
        default:
            s="\nUnknown J-Format instruction\n";
            break;
    }
    return s;
}

bool JFormat::execute()
{
    switch (opcode) {
        case 0x02:
            // j
            if((pc+targetAddress)<(192*(pow(2.0,26))+(pow(2.0,12)))&&(pc+targetAddress)>0 )
            {
                // mask to keep 4 most significant bits
                int temp = pc & 0xf0000000;
                
                targetAddress=targetAddress|temp;
                pc=targetAddress-0x00400000; // Starting address of Text segment
                pc/=4;
                pc--;
            }
            break;
            
        case 0x03:
            // jal
            if((pc+targetAddress)<(192*pow(2.0,26)+pow(2.0,12))&&(pc+targetAddress)>0 )
            {
                // mask to keep 4 most significant bits
                int temp = pc & 0xf000;
                
                targetAddress|=temp;
                
                registers[31]=pc*4+0x00400000+4; //Starting address of text segment.
                pc=targetAddress-0x00400000;
                pc/=4;
                pc--;
            }
            break;
            
        default:
            cout << "\nUnknown J-Format instruction"<<endl;
            break;
    }
    
    return false;

}

unsigned short JFormat::returnFunction()
{
   unsigned short s=0;
   return s;
}
