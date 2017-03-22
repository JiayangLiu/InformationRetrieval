/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionAdd_lrc;
    QAction *actionAbout_LyricDetective;
    QWidget *centralWidget;
    QLabel *labelIcon;
    QGroupBox *groupBox;
    QPushButton *btnAddFile;
    QPushButton *btnRemoveFile;
    QPushButton *btnClearList;
    QTableWidget *twgFileList;
    QPushButton *btnLRCtoTXT;
    QPushButton *btnInvertedIndex;
    QMenuBar *menuBar;
    QMenu *menuDocument;
    QMenu *menuHelp;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(674, 364);
        actionAdd_lrc = new QAction(MainWindow);
        actionAdd_lrc->setObjectName(QStringLiteral("actionAdd_lrc"));
        actionAbout_LyricDetective = new QAction(MainWindow);
        actionAbout_LyricDetective->setObjectName(QStringLiteral("actionAbout_LyricDetective"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        labelIcon = new QLabel(centralWidget);
        labelIcon->setObjectName(QStringLiteral("labelIcon"));
        labelIcon->setGeometry(QRect(460, 90, 101, 111));
        labelIcon->setPixmap(QPixmap(QString::fromUtf8(":/resources/picture/icon.png")));
        labelIcon->setScaledContents(true);
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(20, 10, 381, 281));
        btnAddFile = new QPushButton(groupBox);
        btnAddFile->setObjectName(QStringLiteral("btnAddFile"));
        btnAddFile->setGeometry(QRect(280, 50, 80, 22));
        btnRemoveFile = new QPushButton(groupBox);
        btnRemoveFile->setObjectName(QStringLiteral("btnRemoveFile"));
        btnRemoveFile->setGeometry(QRect(280, 120, 80, 22));
        btnClearList = new QPushButton(groupBox);
        btnClearList->setObjectName(QStringLiteral("btnClearList"));
        btnClearList->setGeometry(QRect(280, 190, 80, 22));
        twgFileList = new QTableWidget(groupBox);
        twgFileList->setObjectName(QStringLiteral("twgFileList"));
        twgFileList->setGeometry(QRect(20, 30, 241, 201));
        btnLRCtoTXT = new QPushButton(groupBox);
        btnLRCtoTXT->setObjectName(QStringLiteral("btnLRCtoTXT"));
        btnLRCtoTXT->setGeometry(QRect(30, 250, 101, 22));
        btnInvertedIndex = new QPushButton(groupBox);
        btnInvertedIndex->setObjectName(QStringLiteral("btnInvertedIndex"));
        btnInvertedIndex->setGeometry(QRect(150, 250, 101, 22));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 674, 19));
        menuDocument = new QMenu(menuBar);
        menuDocument->setObjectName(QStringLiteral("menuDocument"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuDocument->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuDocument->addAction(actionAdd_lrc);
        menuHelp->addAction(actionAbout_LyricDetective);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionAdd_lrc->setText(QApplication::translate("MainWindow", "Add lrc", 0));
        actionAbout_LyricDetective->setText(QApplication::translate("MainWindow", "About LyricDetective", 0));
        labelIcon->setText(QString());
        groupBox->setTitle(QApplication::translate("MainWindow", "lrc List", 0));
        btnAddFile->setText(QApplication::translate("MainWindow", "Add", 0));
        btnRemoveFile->setText(QApplication::translate("MainWindow", "Remove", 0));
        btnClearList->setText(QApplication::translate("MainWindow", "Clear", 0));
        btnLRCtoTXT->setText(QApplication::translate("MainWindow", "lrc->txt", 0));
        btnInvertedIndex->setText(QApplication::translate("MainWindow", "InvertedIndex", 0));
        menuDocument->setTitle(QApplication::translate("MainWindow", "&File", 0));
        menuHelp->setTitle(QApplication::translate("MainWindow", "&Help", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
