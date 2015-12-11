//
//  IFormat.h
//  AssemblyProject
//
//  Created by Ingy on 3/24/15.
//  Copyright (c) 2015 Ingy. All rights reserved.
//

#ifndef __AssemblyProject__IFormat__
#define __AssemblyProject__IFormat__

#include "Instruction.h"

class IFormat: public Instruction
{
public:
    
    void decode ();
    string display ();
    bool execute ();
    unsigned short returnFunction();
    
private:
    unsigned int rs, rt;
    int imm;
    int signedImm, address;
    
};

#endif /* defined(__AssemblyProject__IFormat__) */
