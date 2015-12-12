#ifndef SIMULATORWINDOW_H
#define SIMULATORWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
//#include<Simulator.h>
#include <CPU.h>
#include <inputException.h>

namespace Ui {
class SimulatorWindow;
}

class SimulatorWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SimulatorWindow(QWidget *parent = 0,  CPU * cpu=NULL);
    void Disassembler();
    void setRegistersName();
    void setRegistersContent();
    void check(string s = "");
    void setDataContent();
    void setGraphContent();
    void updateT();
    ~SimulatorWindow();

private slots:
    void on_commandLinkButton_clicked();
    void on_commandLinkButton_2_clicked();

    void on_checkBox_toggled(bool checked);

    void on_Edit_clicked();

    void on_Save_clicked();


private:
    Ui::SimulatorWindow *ui;
    bool ascii;
    bool on;
    bool on2;
    bool canRun;
    QString oldPC;
    QStandardItemModel * model;
    QStandardItemModel * model2;
    QStandardItemModel * model3;
    CPU * ingy;
};

#endif // SIMULATORWINDOW_H
