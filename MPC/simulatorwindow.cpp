#include "simulatorwindow.h"
//#include <Instruction.h>
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
#include <QMessageBox>


using namespace std;

SimulatorWindow::SimulatorWindow(QWidget *parent,  CPU * cpu) :
    QMainWindow(parent),
    ui(new Ui::SimulatorWindow)
{

    this->ingy= cpu;
    //finished=false;
    ascii=false;

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

   ui->PCcount->setText("");

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

   model3 = new QStandardItemModel(0,0,this);
   const QModelIndex index = model3->index(0, 0);
   model3->setData(index, Qt::AlignCenter, Qt::TextAlignmentRole);
   setDataContent();
   // run();
   this->check();
   on = on2 = false;
   this->Disassembler();


}

SimulatorWindow::~SimulatorWindow()
{
    delete ui;
}

void SimulatorWindow::check (string s)
{
//    delete model3;
//    model3 = new QStandardItemModel(0,0,this);
    model3->clear();
    QMessageBox error(this);

    try {


        ingy->loadAndParse(s);


 //       cout <<"blaaaaa";
 //       for (int i = 0; i < btb.size(); i++)
 //           cout << btb[i].branchAddress << btb[i].predictedPC << btb[i].taken << endl;

     }
     catch(const inputException & inp)
     {
        // cout << "File input error: \nIncorrect syntax at line: " <<inp.what();
       // cout << "File input error: \nIncorrect syntax at line: ";
        QString s = "File input error:\n\nIncorrect syntax at line: ";
        s.append(QString::fromStdString(inp.what()));
        QString s1= " ";
        error.critical(0,s1,s);
        error.show();

         //exit(0);
     }
     catch(const invalid_argument & inp)
     {
         //cout << " " <<inp.what();
        cout <<"File input error: \nInvalid argument at line:";
        QString s = "\nFile input error:\n\nInvalid argument at line: ";
        s.append(QString::fromStdString(inp.what()));
        error.critical(0," ",s);
        error.show();
         //exit(0);
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

void SimulatorWindow::setGraphContent()
{
    if(ingy->stages[4])
    {
        // Wb is valid
        model3->setItem(ingy->getClk()-5,ingy->getClk()-1,new QStandardItem("W"));
    }
    if(ingy->stages[3])
    {
        //M
        model3->setItem(ingy->getClk()-4,ingy->getClk()-1,new QStandardItem("M"));
    }
    if(ingy->stages[2])
    {
        // Ex
        model3->setItem(ingy->getClk()-3,ingy->getClk()-1,new QStandardItem("E"));
    }
    if(ingy->stages[1])
    {
        //Decode
        model3->setItem(ingy->getClk()-2,ingy->getClk()-1,new QStandardItem("D"));
    }
    if(ingy->stages[0])
    {
        // Fetch
        model3->setItem(ingy->getClk()-1,ingy->getClk()-1,new QStandardItem("F"));
    }
    QString s;


    if(ingy->getFinalFoo())
        on = true;

        s= oldPC;

    if(!on2)
        model3->setVerticalHeaderItem(ingy->getClk()-1,new QStandardItem(s));

    if(on) on2 =true;

     ui->graph->setModel(model3);
}

void SimulatorWindow::on_commandLinkButton_clicked() // Next button
{
    // run 1 step
   if(ingy->getClk() <= ingy->getClkWAtFinal())
   {

       ui->PCcount->setText(QString::number(ingy->getPC()));
       this->oldPC = ingy->textIM[ingy->getPC()];
       //finished=S->run1();
       ingy->test();
       this->setGraphContent();
        ingy->incrementClk();
       this->setRegistersContent();
       this->setDataContent();


   }

}


void SimulatorWindow::on_commandLinkButton_2_clicked() //Run button
{

     //   this->Disassembler();
            while (ingy->getClk() <= ingy->getClkWAtFinal())
            {
            ui->PCcount->setText(QString::number(ingy->getPC()));
                this->oldPC = ingy->textIM[ingy->getPC()];
                ingy->test();
                cout << "RUNNING!!!!";
              this->setGraphContent();
                ingy->incrementClk();


            }

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
    //ui->disassemblerOut->setReadOnly(true);
    updateT();
    ui->graph->setModel(new QStandardItemModel(0,0,this));
   this->setRegistersContent();
    on = false;
    on2=false;
    oldPC="";
}

void SimulatorWindow::updateT ()
{
    QString text = ui->disassemblerOut->toPlainText();
    text.append('\n');
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
    string s = "/Users/Ingy/Desktop/github/MipsPipelinedSimulator/MipsPipelined/MipsPipelinedSimulator/MipsPipelinedSimulator/shit.txt";
    check (s);
    //ingy->loadAndParse("/Users/Ingy/Desktop/github/MipsPipelinedSimulator/MipsPipelined/MipsPipelinedSimulator/MipsPipelinedSimulator/shit.txt");
}
