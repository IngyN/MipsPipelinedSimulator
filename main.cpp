#include <iostream>
#include "CPU.h"
#include "Instruction.h"
#include "inputException.h"
using namespace std;

int main ()
{
    //SEBA
//    try {
//        CPU one ("C:/Users/Seba/Documents/330_Project/MipsPipelinedSimulator/MipsPipelinedSimulator/input2.txt");
//    }
//    catch(const inputException & inp)
//    {
//        cout << "File input error: \nIncorrect syntax at line: " <<inp.what();
//        exit(0);
//    }
//    
//    
//    //NESMA
//    try {
//        CPU one ("C:/Users/NesmaBadr/Desktop/Fall 2015/CS 330/330project/input.txt");
//    }
//    catch(const inputException & inp)
//    {
//        cout << "File input error: \nIncorrect syntax at line: " <<inp.what();
//        exit(0);
//    }
    
    //INGY
    try {
        CPU ingy ("input4.txt");
    }
    catch(const inputException & inp)
    {
        cout << "File input error: \nIncorrect syntax at line: " <<inp.what();
        exit(0);
    }
    catch(const invalid_argument & inp)
    {
        cout << "File input error: \nInvalid argument at line: " <<inp.what();
    }
    
    
	system ("Pause"); 
	return 0;
}