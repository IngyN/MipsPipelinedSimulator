 //
//  Simulator.cpp
//  AssemblyProject
//
//  Created by Ingy on 3/24/15.
//  Copyright (c) 2015 Ingy. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "Simulator.h"
#include <cmath>
#include <QString>
#include <string>


using namespace std;

Simulator::Simulator()
{
    Instruction::pc=-1;
}

Simulator::~Simulator()
{
    
}

bool Simulator::readTextFromFile(string source)
{
    unsigned int instWord=0;
    
    Instruction * p=NULL;
    ifstream inFile;
    string inFileName = "";
    
//    bool flag =true;
    
//    if(source=="")
//    {
//        // Get the binary filename from the user
//        cout << "Enter the binary filename (e.g. sample1.bin): "<<endl;
//        cin >> inFileName;
        
//        // Open the binary file to start reading the instructions
//        inFile.open(inFileName.c_str(), ios::in | ios::binary);
////        flag=!(!inFile.read((char *)&instWord, 4))
        
//    }
//    else

        inFile.open(source.c_str(), ios::in | ios::binary);

    
    long long maxSize= (pow(2.0, 26)*3)/4;
    
    // If the file is open (this will evaluate to false if the file could not be found)
    if(inFile.is_open())
    {
        // Start reading and decoding the instructions.
        while(textSegment.size()<maxSize)
        {
            // Read 4 bytes (an instruction) from the file
            if(!inFile.read((char *)&instWord, 4))
                break; // If 4 bytes cannot be read from the file (i.e. end of file has been reached), break the loop.
            
            Instruction::select(p, instWord>>26, instWord);
            
            textSegment.push_back(p);
        }
        inFile.close();
    }
    
    else // The input file cannot be opened
    {
        cout << "\nCannot access input file" << endl;
        return false;
    }

    return true;
}
bool Simulator::readMemoryFromFile(string source)
{
    bool flag =true;
    
    // read from file and store in memory
    char temp[4]={0};
    int index=0;
    
    ifstream inFile;
    
//    if(source=="")
//    {
//        cout << "Would you like to enter a memory file?"<<endl;
//        char c;
//        cin >> c;
//        c=toupper(c);
        
//        if(c=='Y')
//        {
//            cout << "\nMemory file path: "<<endl;
//            cin >>source;
//        }
        
//        else
//            cout <<"No memory file"<<endl;
//    }
    
    if(source!="")
    {
        inFile.open(source.c_str(), ios::in | ios::binary);
        
        
        long long maxSize= 2048;
        
        // If the file is open (this will evaluate to false if the file could not be found)
        if(inFile.is_open())
        {
            // Start reading and decoding the instructions.
            while(textSegment.size()<maxSize && !inFile.eof())
            {
                // Read 4 bytes (an instruction) from the file
                for(int i=0; i<4; i++)
                    if(inFile.read(&temp[i], 1))
                    {
                        Instruction::memory[index++]=temp[i];
                    }
                
                // If 4 bytes cannot be read from the file (i.e. end of file has been reached), break the loop.
            }
        }
        
        else // The input file cannot be opened
        {
            cout << "Cannot access input file" << endl;
            flag=false;
        }
        inFile.close();
    }
    
    return flag;
}

void Simulator::run()
{
    
    bool finished =false;
    
    do
    {
        Instruction::pc++;
        finished=textSegment[Instruction::pc]->execute();

    }while (!finished && Instruction::pc<textSegment.size()-1);
    
}

QVector<QString> * Simulator::getConsole()
{
    return &(consoleText);
}


void Simulator::executeSyscall()
{

    string s;
    switch (Instruction::registers[2])//$v0
{
    case 1://Print an integer
        consoleText.push_back(QString::number(Instruction::registers[4]));
        break;

    case 11://Print a character
        consoleText.push_back(QChar(Instruction::registers[4]));
        break;

    case 4://Print a string
    {
        bool nullFound= false;

        for(int i = Instruction::registers[4]-0x10010000;nullFound==false;i++)
        {
                if(Instruction::memory[i]=='\0')
                    nullFound= true;
                else
                    s=s+char(Instruction::memory[i]);
        }
        consoleText.push_back(QString::fromStdString(s));
        break;
    }
}
}

bool Simulator::run1()
{
    bool finished =false;
    Instruction::pc++;
    if (textSegment[Instruction::pc]->isRFormat() && textSegment[Instruction::pc]->returnFunction()==0x0c)
    {
        executeSyscall();
    }
    finished=textSegment[Instruction::pc]->execute();
    return finished;
}

vector<QString> * Simulator::disassembler()
{
    vector <QString> * v= new vector<QString>;
    cout<<"pc"<<Instruction::pc<<endl;

    do
    {
        Instruction::pc++;
        textSegment [Instruction::pc] ->decode();
        v->push_back(QString::fromStdString(textSegment [Instruction::pc] ->display()));

    }while (Instruction::pc<textSegment.size()-1);

    Instruction::pc =-1;

    return v;
}

int Simulator:: getTextSize()
{
    return textSegment.size();
}

