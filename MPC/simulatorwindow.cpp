#include "simulatorwindow.h"
#include <Instruction.h>
#include "ui_simulatorwindow.h"
#include <QStringListModel>
#include <QStandardItemModel>
#include <QFlags>
#include <QTextEdit>
#include <QVector>
#include <vector>
#include <iostream>
#include <fstream>
#include <QTextStream>
#include <QFile>


using namespace std;

SimulatorWindow::SimulatorWindow(QWidget *parent, Simulator * S, CPU * cpu) :
    QMainWindow(parent),
    ui(new Ui::SimulatorWindow)
{
    this->S=S;
    this->ingy= cpu;
    finished=false;
    ascii=false;
    S->readTextFromFile("/Users/Ingy/Desktop/github/AssemblyProject/test3t");
    S->readMemoryFromFile("/Users/Ingy/Desktop/github/AssemblyProject/test3m");

    ui->setupUi(this);


    ui->DisassemblerTab->setObjectName("Code Editor");
    ui->DataSegment->setObjectName("Data Segment & Diagram");
   ui->DisassemblerTab->setEnabled(true);
   ui->disassemblerOut->setUndoRedoEnabled(true);

   // Registers
   model = new QStandardItemModel(32,2,this);
   model->setHorizontalHeaderItem(0, new QStandardItem(QString("Register")));
   model->setHorizontalHeaderItem(1, new QStandardItem(QString("Value")));
   for (int i=0; i<32; i++)
   {
       model->setVerticalHeaderItem(i,new QStandardItem(QString::number(i)));
   }
   ui->registers->setModel(model);


   this->setRegistersName();

   //DataSegment

   model2 = new QStandardItemModel(32,1,this);

   model2->setHorizontalHeaderItem(0, new QStandardItem(QString("Data Memory")));

   //model2->setVerticalHeaderItem(0, new QStandardItem(QString("Address")));

   for (int i=0; i<32; i++)
   {
       model2->setVerticalHeaderItem(i,new QStandardItem(QString::number(i)));
   }

   ui->DataSegment->setModel(model2);
   setDataContent();
   // run();
   this->Disassembler();

}

SimulatorWindow::~SimulatorWindow()
{
    delete ui;
}

void SimulatorWindow::run ()
{
    try {


        ingy->loadAndParse("/Users/Ingy/Desktop/github/MipsPipelinedSimulator/MipsPipelined/MipsPipelinedSimulator/MipsPipelinedSimulator/input4.txt");


 //       cout <<"blaaaaa";
 //       for (int i = 0; i < btb.size(); i++)
 //           cout << btb[i].branchAddress << btb[i].predictedPC << btb[i].taken << endl;

     }
     catch(const inputException & inp)
     {
        // cout << "File input error: \nIncorrect syntax at line: " <<inp.what();
        cout << "File input error: \nIncorrect syntax at line: ";
         exit(0);
     }
     catch(const invalid_argument & inp)
     {
         //cout << " " <<inp.what();
        cout <<"File input error: \nInvalid argument at line:";
         exit(0);
     }
}

void SimulatorWindow::Disassembler()
{

    vector<QString> v;
    v=ingy->textIM;

    // text edit
    QVector<QString> v0=QVector<QString>::fromStdVector(v);

    ui->disassemblerOut->clear();

    for(int i=0; i<v.size(); i++)
        ui->disassemblerOut->append(v0[i]);
    //ui->disassemblerOut->setVerticalScrollBar();
    //delete v;
}

void SimulatorWindow::setRegistersName()
{

    for (int i=0; i<32; i++)
       {
        model->setItem(i,0,new QStandardItem(QString::fromStdString(InstructionT::displayReg(i))));
        }
    // Put in table view
    ui->registers->setModel(model);
}

void SimulatorWindow::setRegistersContent()
{
    for (int i=0; i<32; i++)
       {
        model->setItem(i,1,new QStandardItem(QString::number(ingy->RegFile[i])));
        }
    // Put in table view
    ui->registers->setModel(model);
}

void SimulatorWindow::setDataContent()
{
    string s;
    if (!ascii)
        for(int i=0;i<32; i++)
            model2->setItem(i,0,new QStandardItem(QString::number(ingy->DataMem[i])));
    else
        for(int i=0;i<32; i++)
        {
            s =ingy->DataMem[i];
            model2->setItem(i,0,new QStandardItem(QString::fromStdString(s)));
        }

    ui->DataSegment->setModel(model2);

}

void SimulatorWindow::setConsoleOut()
{
//    QVector<QString> * v;
//    v=S->getConsole();

//    QString s="";
//    for(int i=0; i<v->size(); i++)
//        s+=v->at(i);
////    ui->Console->clear();
////    for(int i=0; i<v->size(); i++)
////        ui->Console->append(v->at(i));
//    ui->Console->setText(s);
}

void SimulatorWindow::on_commandLinkButton_clicked() // Next button
{
    // run 1 step
   if(ingy->getClk() <= ingy->getClkWAtFinal())
   {
       //finished=S->run1();
       ingy->test();
        ingy->incrementClk();
       this->setRegistersContent();
       this->setDataContent();

   }

}

void SimulatorWindow::on_commandLinkButton_2_clicked() //Run button
{



         //   this->Disassembler();
            do{
                ingy->test();
                cout << "RUNNING!!!!";

                ingy->incrementClk();


            } while (ingy->getClk() < ingy->getClkWAtFinal());

    this->setRegistersContent();
    this->setDataContent();
}

void SimulatorWindow::on_checkBox_toggled(bool checked)
{
    ascii =checked;
    this->setDataContent();
}

void SimulatorWindow::on_Edit_clicked()
{
    ui->disassemblerOut->setReadOnly(false);
}

void SimulatorWindow::on_Save_clicked()
{
    ui->disassemblerOut->setReadOnly(true);
    updateT();
}

void SimulatorWindow::updateT ()
{
    QString text = ui->disassemblerOut->toPlainText();

    QFile output ("/Users/Ingy/Desktop/github/MipsPipelinedSimulator/MipsPipelined/MipsPipelinedSimulator/MipsPipelinedSimulator/shit.txt");
//    std::ofstream out;
//    out.open("test.txt");
//    out<<text.QString::toStdString();
//    cout<<text.QString::toStdString();
//    out.close();
    output.open(QIODevice::WriteOnly| QIODevice::Text);
    QTextStream outStream (&output);
    outStream<<text;
    output.close();
    ingy->loadAndParse("/Users/Ingy/Desktop/github/MipsPipelinedSimulator/MipsPipelined/MipsPipelinedSimulator/MipsPipelinedSimulator/shit.txt");
}
