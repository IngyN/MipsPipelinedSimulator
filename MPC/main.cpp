//#include "mainwindow.h"
#include <QApplication>
//#include "Simulator.h"
#include <CPU.h>
#include <iostream>
#include <simulatorwindow.h>
using namespace std;
int main(int argc, char *argv[])
{
//    if(argc>3)
//    {
//        cout <<"Error: too many arguments"<<endl;
//    }
//    else if(argc==3)
//    {
//        // name and textFile and Memory
//        Simulator S;
//        if (S.readTextFromFile(argv[1]))
//        {
//            if(S.readMemoryFromFile(argv[2]))
//                S.run();
//        }

//    }
//    else if(argc==2)
//    {
//        // name and textFile
//        Simulator S;
//        std::string s="";
//        if(S.readTextFromFile(argv[1]))
//        {
//            S.readMemoryFromFile(s);
//            S.run();
//        }


//    }
//    else if (argc==1)
//    {
//        cout << "Error: too few arguments"<<endl;
//        string s="";
//        Simulator S;

//        if(S.readTextFromFile(s))
//        {
//            S.readMemoryFromFile(s);
//            S.run();
//        }
//        else
//        {
//            cout <<"\n\nError invalid file\n"<<endl;
//        }

//    }
    QApplication a(argc, argv);
    CPU * cpu = new CPU("/Users/Ingy/Desktop/github/MipsPipelinedSimulator/MipsPipelined/MipsPipelinedSimulator/MipsPipelinedSimulator/input2.txt");
    SimulatorWindow w(NULL, cpu);
    w.show();

    return a.exec();
}
