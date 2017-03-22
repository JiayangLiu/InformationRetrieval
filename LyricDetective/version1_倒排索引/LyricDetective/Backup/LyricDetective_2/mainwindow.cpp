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
    ui->twgFileList->setSelectionBehavior(QAbstractItemView::SelectRows);  //设置选择行为时每次选择一行


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
    // 判读文件列表是否已为空 messagebox
    if(listFileName.length() != 0)
    {
        // 移除选中行
        int curRow = ui->twgFileList->currentIndex().row(); //获取选中行
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
void MainWindow::readLyric(QString fileName)
{
    std::string filename_str = fileName.toStdString();

    std::ifstream fin;
    fin.open(filename_str);
    if (!fin.is_open())
    {
        qDebug() << "文件读取失败!\n";
        // system("pause");
        // exit(0);
    }

    std::string str;
    getline(fin, str);
    while (fin)
    {
        if (str != "")
        {
            analysisOneLine(QString::fromStdString(str));
            i1 = i1 + 1;
        }
        getline(fin, str);
    }
    fin.close();
    printLyric();
}

// 分析一行 保存到结构体数组
void MainWindow::analysisOneLine(QString str)
{
    std::string str_string = str.toStdString();
    if (i1 == 0)
    {
        if (str_string[5] != '[')
        {
            qDebug() << "歌词文件格式不正规!\n";
            qDebug() << str_string[6];
        }
    }
    if (i1>0)
    {
        if (str_string[0] != '[')
        {
            qDebug() << "歌词文件格式不正规!\n";
            qDebug() << str_string[5];
        }
    }

    // 歌词说明 ti:歌曲名称 ar:演唱者 al: by: 制作单位
    getLyricHeader(str);

    int m, n, p = 0;
    std::string timeTemp[MAX_LYRCE_REPEAT_NUM]; // 保存信息
    m = str_string.find_first_of('[');
    n = str_string.find_first_of(']');
    while (m >= 0 && m <= str_string.length() && n >= 0 && n <= str_string.length() && str != "")
    {
        timeTemp[p] = str_string.substr(m + 1, n - 1);
        p++;
        str_string = str_string.substr(n + 1, str_string.length());
        m = str_string.find_first_of('[');
        n = str_string.find_first_of(']');
    }

    QString contentTemp = str;

    for (int i = 0; i < p; i++)
    {
        if (lineNum == 1)
        {
            qDebug() << "";
        }
        lyric[lineNum].startTime = QString::fromStdString(timeTemp[i]);

        if (timeTemp[i + 1] != "") // 连续的
        {
            lyric[lineNum].endTime = QString::fromStdString(timeTemp[i + 1]);
            qDebug() << QString::fromStdString(timeTemp[i]);
        }

        if (lineNum - 1 >= 0 && i == 0) // 设置上一个的endTime
            lyric[lineNum - 1].endTime = lyric[lineNum].startTime;
        lyric[lineNum].lineNum = lineNum;
        lyric[lineNum].lyricContent = contentTemp;
        lineNum++;
    }

}
void MainWindow::getLyricHeader(QString str)
{
    for (int i = 0; i < 4; i++)
    {
        if (header[i] == QString::fromStdString(str.toStdString().substr(1, 3)));
        {
            Lheader[i] = str;
        }
    }
}
void MainWindow::printLyric()
{
    qDebug() << "歌曲信息:";
    for (int i = 0; i < 4; i++)
    {
        qDebug() << Lheader[i];
    }

    for (int i = 0; i < lineNum; i++)
    {
        if (lyric[i].startTime != "")
        {
            qDebug() << "行    号:\t" << lyric[i].lineNum;
            qDebug() << "开始时间:\t" << lyric[i].startTime;
            qDebug() << "结束时间:\t" << lyric[i].endTime;
            qDebug() << "歌词内容:\t" << lyric[i].lyricContent;
        }
    }

    QString txt_FileName = "/home/jeremyliu/Desktop/LyricDetective/lrc_generated/" + file_CurrentProccessed + ".txt"; // 指定文件夹路径和文件名
    QFile file(txt_FileName);
    file.open(QIODevice::WriteOnly | QIODevice::Text );

    QString content;
    // 录入内容
    for(int i = 0; i < lineNum; i++)
    {
        if (lyric[i].startTime != "")
        {
            acontent += lyric[i].lyricContent + "\n";
        }
    }
    // 输出到文件
    QTextStream in(&file);
    in << content;
    file.close();
}

// 将时间转换成毫秒
int MainWindow::changeStringToInt(QString str_time)
{
    int time, min, sec, msc = 0; //分钟,秒,毫秒 转换成毫秒
    min = atof(const_cast<const char *>(str_time.toStdString().substr(0, 2).c_str()));
    sec = atof(const_cast<const char *>(str_time.toStdString().substr(3, 2).c_str()));
    if (str_time.length() > 5)
        msc = atof(const_cast<const char *>(str_time.toStdString().substr(4, 2).c_str()));
    time = min * 60 * 100 + sec * 100 + msc;
    return time;
}

// 将lrc转换生成txt
void MainWindow::on_btnLRCtoTXT_clicked()
{
    for (int i=0; i<listFileName.size(); i++) {
        file_CurrentProccessed = listFileName[i];
        qDebug()<<"File is being converted: "<<file_CurrentProccessed;
        readLyric(file_CurrentProccessed);
    }
}

// ----- txt->InvertedIndex -----------------------------------
// 使用刚刚转化出的txt生成倒排索引
void MainWindow::on_btnInvertedIndex_clicked()
{
    for (int i=0; i<listFileName.size(); i++) {
        file_CurrentProccessed = listFileName[i];
        qDebug()<<"InvertedIndex is being generated: "<<file_CurrentProccessed;
        index->StatWords("/home/jeremyliu/Desktop/LyricDetective/lrc_generated/" + file_CurrentProccessed + ".txt");
    }
}
