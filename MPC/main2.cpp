#include <iostream>
#include "CPU.h"
#include "inputException.h"
#include <stdexcept>
using namespace std;

//int main ()
//{
    //SEBA
	/*try {
        CPU one ("C:/Users/Seba/Documents/330_Project/MipsPipelinedSimulator/MipsPipelinedSimulator/input2.txt");
    }
    catch(const inputException & inp)
    {
        cout << "File input error: \nIncorrect syntax at line: " <<inp.what();
        exit(0);
   }
    catch(const invalid_argument & inp)
    {
        cout << "File input error: \nInvalid argument at line: " <<inp.what();
    }*/

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
       
       ingy.loadAndParse();
       do{
           ingy.test();
           
           ingy.incrementClk();
       } while (ingy.getClk() < ingy.getClkWAtFinal());
       
//       cout <<"blaaaaa";
//       for (int i = 0; i < btb.size(); i++)
//           cout << btb[i].branchAddress << btb[i].predictedPC << btb[i].taken << endl;

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


    
    
    //CPU one ("C:/Users/NesmaBadr/Desktop/Fall 2015/CS 330/330project/input.txt");
	//CPU one ("C:/Users/Seba/Documents/330_Project/MipsPipelinedSimulator/MipsPipelinedSimulator/input2.txt");
    //CPU alia ("/Users/Alia/Desktop/MipsPipelinedSimulator/MipsPipelinedSimulator/input4.txt");
   // CPU ingy ("input2.txt");


    
//	system ("Pause");
//	return 0;
//}
