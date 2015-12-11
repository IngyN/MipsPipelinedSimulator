//
//  JFormat.h
//  AssemblyProject
//
//  Created by Ingy on 3/24/15.
//  Copyright (c) 2015 Ingy. All rights reserved.
//

#ifndef __AssemblyProject__JFormat__
#define __AssemblyProject__JFormat__

#include "Instruction.h"

class JFormat: public Instruction
{
public:
    JFormat();
    ~JFormat();
    
    void decode ();

    string display ();
    bool execute ();
    unsigned short returnFunction();
    
private:
    
    unsigned int targetAddress;
    
};

#endif /* defined(__AssemblyProject__JFormat__) */
