//
//  Instruction.cpp
//  MipsPipelinedSimulator
//
//  Created by Alia Hassan  on 11/23/15.
//  Copyright (c) 2015 Alia Hassan . All rights reserved.
//

#include "Instruction.h"

Instruction::Instruction(int i, int s, int d, int t, int im):instNum(i),rs(s),rd(d),rt(t),imm(im)
{
    
}

//Instruction::Instruction (const Instruction &)
//{
//
//}

Instruction::~Instruction()
{
    
}

