//
//  Simulator.h
//  AssemblyProject
//
//  Created by Ingy on 3/24/15.
//  Copyright (c) 2015 Ingy. All rights reserved.
//

#ifndef __AssemblyProject__Simulator__
#define __AssemblyProject__Simulator__

#include "IFormat.h"
#include "JFormat.h"
#include "RFormat.h"
#include <bitset>
#include <vector>
#include <QString>
#include <QVector>

using namespace std;

class Simulator
{
public:
    Simulator();
    ~Simulator();
    
    void run();
    bool run1();
    
    int getTextSize();
    QVector<QString> * getConsole();

    bool readTextFromFile(string);
    bool readMemoryFromFile(string);
    vector<QString> * disassembler();
    void executeSyscall();
    
private:
    // Text segment
    
    vector<Instruction *> textSegment; // starting address: 0x 0400 0000
    QVector <QString> consoleText;
};

#endif /* defined(__AssemblyProject__Simulator__) */
