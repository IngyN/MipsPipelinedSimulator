//
//  RFormat.h
//  AssemblyProject
//
//  Created by Ingy on 3/24/15.
//  Copyright (c) 2015 Ingy. All rights reserved.
//

#ifndef __AssemblyProject__RFormat__
#define __AssemblyProject__RFormat__
#include "Instruction.h"

class RFormat: public Instruction
{
public:
    void decode ();
    string display();
    bool execute ();

    unsigned short returnFunction();

private:
    
    unsigned short rd, rs, rt, func, shamt, imm;
};

#endif /* defined(__AssemblyProject__RFormat__) */
