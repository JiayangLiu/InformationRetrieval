#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QFile>
#include <QFileDialog>
#include <QDebug>
#include <fstream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initial();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initial()
{
    // 设置状态栏的显示内容
    ui->statusBar->addWidget(new QLabel("                                 LyricDetective by JeremyLiu"));
    // 添加状态栏时间
    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timerUpdate()));
    timer->start(1000);
    labelTimer = new QLabel();
    ui->statusBar->addPermanentWidget(labelTimer);

    // TableWidget部分
    ui->twgFileList->setColumnCount(1);
    ui->twgFileList->setRowCount(0);
    QStringList headers;
    headers << "文件名";
    ui->twgFileList->setHorizontalHeaderLabels(headers);
    ui->twgFileList->horizontalHeader()->setStretchLastSection(true);
    ui->twgFileList->setSelectionBehavior(QAbstractItemView::SelectRows);  // 设置选择行为时每次选择一行
}

// 状态栏时间显示
void MainWindow::timerUpdate()
{
    // 获取系统现在的时间
    QDateTime time = QDateTime::currentDateTime();
    // 设置显示格式
    QString str = time.toString("                                 yyyy-MM-dd hh:mm:ss                                 ");
    labelTimer->setText(str);
}

// 消息响应：关于LyricDetective
void MainWindow::on_actionAbout_LyricDetective_triggered()
{
    // 弹出对话框
    QMessageBox msgBox(QMessageBox::NoIcon, "About LyricDetective", "Developed by JeremyLiu.");
    msgBox.setIconPixmap(QPixmap("icon.png"));
    msgBox.exec();
}

// 添加lrc文件
void MainWindow::on_btnAddFile_clicked()
{
    QString file_full = "";
    QString file_name = "";
    QString file_path = "";
    QString file_suffix = "";

    QFileInfo fileinfo;

    file_full = QFileDialog::getOpenFileName(this, "add file", ".", "lrcfile(*.lrc)"); // 打开文件限定在lrc格式

    fileinfo = QFileInfo(file_full);
    // 文件名
    file_name = fileinfo.fileName();
    // 文件后缀
    file_suffix = fileinfo.suffix();
    // 绝对路径
    file_path = fileinfo.absolutePath();

    qDebug()<<"File name is: "<<file_name;

    listFileName.append(file_name);

    // TableWidget全部删除
    int iLen = ui->twgFileList->rowCount();
    for(int i=0;i<iLen;i++)
    {
        ui->twgFileList->removeRow(0);
    }

    // 重新将信息显示在TableWidget中
    for(int i = 0; i < listFileName.length(); i++)
    {
        ui->twgFileList->setRowCount(i+1);
        QString content;
        content = listFileName[i];
        ui->twgFileList->setItem(i, 0, new QTableWidgetItem(content));
    }
}

void MainWindow::on_actionAdd_lrc_triggered()
{
    on_btnAddFile_clicked();
}

// 移除lrc文件
void MainWindow::on_btnRemoveFile_clicked()
{
    // 判读文件列表是否已为空 (后期加messagebox)
    if(listFileName.length() != 0)
    {
        // 移除选中行
        int curRow = ui->twgFileList->currentIndex().row(); // 获取选中行
        ui->twgFileList->removeRow(curRow);
        listFileName.remove(curRow);

        // 重新将信息显示在TableWidget中
        for(int i = 0; i < listFileName.length(); i++)
        {
            ui->twgFileList->setRowCount(i+1);
            QString content;
            content = listFileName[i];
            ui->twgFileList->setItem(i, 0, new QTableWidgetItem(content));
        }
    } else {
        QMessageBox::about(NULL, "Warning", "File list is already empty.");
    }
}

// 清空lrc文件
void MainWindow::on_btnClearList_clicked()
{
    listFileName.clear();
    // TableWidget全部删除
    int iLen = ui->twgFileList->rowCount();
    for(int i=0;i<iLen;i++)
    {
        ui->twgFileList->removeRow(0);
    }
}

// ----- lrc->txt -----------------------------------
// 将lrc转换生成txt
void MainWindow::on_btnLRCtoTXT_clicked()
{
    for (int i=0; i<listFileName.size(); i++) {
        file_CurrentProccessed = listFileName[i];
        qDebug()<<"File is being converted: "<<file_CurrentProccessed;
        totxt=new LRCtoTXT();
        totxt->readLyric(file_CurrentProccessed);
    }
}

// ----- txt->InvertedIndex -----------------------------------
// 使用刚刚转化出的txt生成倒排索引
void MainWindow::on_btnInvertedIndex_clicked()
{
    for (int i=0; i<listFileName.size(); i++) {
        file_CurrentProccessed = listFileName[i];
        qDebug()<<"InvertedIndex is being generated: "<<file_CurrentProccessed;
        std::string file_ToBeInverted = "/home/jeremyliu/Desktop/LyricDetective/txt_generated/" + file_CurrentProccessed.toStdString() + ".txt";
        index->StatWords(file_ToBeInverted.data()); // 将string转换为char*
    }
}
