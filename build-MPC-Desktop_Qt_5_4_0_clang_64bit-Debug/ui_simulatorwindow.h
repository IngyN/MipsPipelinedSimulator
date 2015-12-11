/********************************************************************************
** Form generated from reading UI file 'simulatorwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIMULATORWINDOW_H
#define UI_SIMULATORWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QCommandLinkButton>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SimulatorWindow
{
public:
    QAction *actionOpen;
    QWidget *centralwidget;
    QTabWidget *tabs;
    QWidget *DisassemblerTab;
    QTextEdit *disassemblerOut;
    QPushButton *Save;
    QPushButton *Edit;
    QWidget *Data;
    QTableView *DataSegment;
    QTextEdit *Console;
    QCheckBox *checkBox;
    QTableView *registers;
    QCommandLinkButton *commandLinkButton;
    QCommandLinkButton *commandLinkButton_2;
    QLabel *label;
    QMenuBar *menubar;
    QMenu *menuFile;
    QStatusBar *File;

    void setupUi(QMainWindow *SimulatorWindow)
    {
        if (SimulatorWindow->objectName().isEmpty())
            SimulatorWindow->setObjectName(QStringLiteral("SimulatorWindow"));
        SimulatorWindow->resize(917, 618);
        actionOpen = new QAction(SimulatorWindow);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        centralwidget = new QWidget(SimulatorWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        tabs = new QTabWidget(centralwidget);
        tabs->setObjectName(QStringLiteral("tabs"));
        tabs->setGeometry(QRect(20, 20, 691, 551));
        QFont font;
        font.setFamily(QStringLiteral("Courier"));
        tabs->setFont(font);
        DisassemblerTab = new QWidget();
        DisassemblerTab->setObjectName(QStringLiteral("DisassemblerTab"));
        disassemblerOut = new QTextEdit(DisassemblerTab);
        disassemblerOut->setObjectName(QStringLiteral("disassemblerOut"));
        disassemblerOut->setGeometry(QRect(10, 0, 671, 481));
        QFont font1;
        font1.setFamily(QStringLiteral("Courier New"));
        disassemblerOut->setFont(font1);
        disassemblerOut->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        disassemblerOut->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        disassemblerOut->setUndoRedoEnabled(false);
        disassemblerOut->setTextInteractionFlags(Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);
        Save = new QPushButton(DisassemblerTab);
        Save->setObjectName(QStringLiteral("Save"));
        Save->setGeometry(QRect(590, 480, 81, 32));
        QPalette palette;
        QBrush brush(QColor(59, 139, 250, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush);
        Save->setPalette(palette);
        Edit = new QPushButton(DisassemblerTab);
        Edit->setObjectName(QStringLiteral("Edit"));
        Edit->setGeometry(QRect(520, 480, 71, 32));
        tabs->addTab(DisassemblerTab, QString());
        Data = new QWidget();
        Data->setObjectName(QStringLiteral("Data"));
        DataSegment = new QTableView(Data);
        DataSegment->setObjectName(QStringLiteral("DataSegment"));
        DataSegment->setGeometry(QRect(10, 30, 151, 481));
        DataSegment->setEditTriggers(QAbstractItemView::NoEditTriggers);
        DataSegment->horizontalHeader()->setDefaultSectionSize(120);
        DataSegment->horizontalHeader()->setHighlightSections(true);
        DataSegment->horizontalHeader()->setMinimumSectionSize(4);
        DataSegment->verticalHeader()->setDefaultSectionSize(32);
        Console = new QTextEdit(Data);
        Console->setObjectName(QStringLiteral("Console"));
        Console->setGeometry(QRect(180, 30, 491, 481));
        Console->setUndoRedoEnabled(false);
        Console->setReadOnly(true);
        checkBox = new QCheckBox(Data);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        checkBox->setGeometry(QRect(10, 0, 61, 20));
        tabs->addTab(Data, QString());
        registers = new QTableView(centralwidget);
        registers->setObjectName(QStringLiteral("registers"));
        registers->setGeometry(QRect(720, 50, 181, 481));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(registers->sizePolicy().hasHeightForWidth());
        registers->setSizePolicy(sizePolicy);
        QFont font2;
        font2.setPointSize(11);
        registers->setFont(font2);
        registers->setLineWidth(1);
        registers->setSizeAdjustPolicy(QAbstractScrollArea::AdjustIgnored);
        registers->setEditTriggers(QAbstractItemView::NoEditTriggers);
        registers->setProperty("showDropIndicator", QVariant(false));
        registers->setDragDropOverwriteMode(false);
        registers->setSelectionMode(QAbstractItemView::SingleSelection);
        registers->horizontalHeader()->setDefaultSectionSize(80);
        commandLinkButton = new QCommandLinkButton(centralwidget);
        commandLinkButton->setObjectName(QStringLiteral("commandLinkButton"));
        commandLinkButton->setGeometry(QRect(730, 20, 61, 31));
        commandLinkButton->setFont(font1);
        commandLinkButton_2 = new QCommandLinkButton(centralwidget);
        commandLinkButton_2->setObjectName(QStringLiteral("commandLinkButton_2"));
        commandLinkButton_2->setGeometry(QRect(830, 20, 71, 31));
        commandLinkButton_2->setFont(font1);
        label = new QLabel(centralwidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(730, 540, 59, 16));
        SimulatorWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(SimulatorWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 917, 22));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        SimulatorWindow->setMenuBar(menubar);
        File = new QStatusBar(SimulatorWindow);
        File->setObjectName(QStringLiteral("File"));
        SimulatorWindow->setStatusBar(File);

        menubar->addAction(menuFile->menuAction());
        menuFile->addAction(actionOpen);

        retranslateUi(SimulatorWindow);

        tabs->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(SimulatorWindow);
    } // setupUi

    void retranslateUi(QMainWindow *SimulatorWindow)
    {
        SimulatorWindow->setWindowTitle(QApplication::translate("SimulatorWindow", "Simulator", 0));
        actionOpen->setText(QApplication::translate("SimulatorWindow", "Open", 0));
        Save->setText(QApplication::translate("SimulatorWindow", "Save", 0));
        Edit->setText(QApplication::translate("SimulatorWindow", "Edit", 0));
        tabs->setTabText(tabs->indexOf(DisassemblerTab), QApplication::translate("SimulatorWindow", "Code Editor", 0));
#ifndef QT_NO_ACCESSIBILITY
        Data->setAccessibleName(QString());
#endif // QT_NO_ACCESSIBILITY
        checkBox->setText(QApplication::translate("SimulatorWindow", "ASCII", 0));
        tabs->setTabText(tabs->indexOf(Data), QApplication::translate("SimulatorWindow", "Data Segment and Diagram", 0));
        commandLinkButton->setText(QApplication::translate("SimulatorWindow", "Next", 0));
        commandLinkButton_2->setText(QApplication::translate("SimulatorWindow", "Run", 0));
        label->setText(QApplication::translate("SimulatorWindow", "PC", 0));
        menuFile->setTitle(QApplication::translate("SimulatorWindow", "File", 0));
    } // retranslateUi

};

namespace Ui {
    class SimulatorWindow: public Ui_SimulatorWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIMULATORWINDOW_H
