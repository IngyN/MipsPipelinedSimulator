#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <Simulator.h>
#include <QMessageBox>
#include <iostream>
#include <simulatorwindow.h>

SimulatorWindow * w0=NULL;

MainWindow::MainWindow(QWidget *parent, Simulator * S) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->S=S;

    ui->setupUi(this);

    ui->memoryFile->setVisible(false);
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
//        string s="";
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
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QMessageBox error(this);

    QString textSource=ui->textFile->text();

    // check file validity
    bool textOpened=S->readTextFromFile(textSource.toStdString());
    bool memOpened=true;

    //std::cout <<"Shit"<<textOpened<<endl;

    // If they entered a memory file path
    if(ui->checkBox->isChecked())
    {
        QString memorySource= ui->memoryFile->text();
        memOpened=S->readMemoryFromFile(memorySource.toStdString());

    }

    if(!textOpened)
    {
        // Error dialog cannot access text Segment file
        error.critical(0,"Input error","Cannot access Text Segment file");
        error.show();

    }

    if(!memOpened)
    {
        cout << "Mem";
        // Error dialog cannot access memory file
        error.critical(0,"Input error","Cannot access memory file");
        error.show();

    }

    if(textOpened && memOpened)
    {
        // call disassembler.
//        SimulatorWindow w0 (this, S);
//        w0.show();
        if(!w0) {w0 = new SimulatorWindow(this, S);}

          if(w0)

          {

            w0->show();

            this->hide();

          }
    }


}

void MainWindow::on_checkBox_toggled(bool checked)
{
    ui->memoryFile->setHidden(!checked);
}


