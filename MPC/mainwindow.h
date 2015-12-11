#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <Simulator.h>
#include <simulatorwindow.h>
using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0, Simulator * S=NULL);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_checkBox_toggled(bool checked);


private:
    Ui::MainWindow *ui;
    Simulator * S;
};

#endif // MAINWINDOW_H
