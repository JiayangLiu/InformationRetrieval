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

    ui->twgRankList->setColumnCount(2);
    ui->twgRankList->setRowCount(0);
    QStringList headers_rank;
    headers_rank << "搜索排名" << "得分";
    ui->twgRankList->setHorizontalHeaderLabels(headers_rank);
    ui->twgRankList->horizontalHeader()->setStretchLastSection(true);
    ui->twgRankList->setSelectionBehavior(QAbstractItemView::SelectRows);

    N = 0;

    ui->cbbRankMode->addItem(QWidget::tr("---Ranking By---"));
    ui->cbbRankMode->addItem(QWidget::tr("full-text"));
    ui->cbbRankMode->addItem(QWidget::tr("artist"));
    ui->cbbRankMode->addItem(QWidget::tr("title"));
    ui->cbbRankMode->addItem(QWidget::tr("album"));

    Dialog *d = new Dialog;
    d->setWindowTitle("Welcome");
    d->setWindowFlags( Qt::FramelessWindowHint | Qt::Tool | Qt::WindowStaysOnTopHint);
    d->show();
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
    QMessageBox msgBox(QMessageBox::NoIcon, "About LyricDetective", "Developed by JeremyLiu.    ");
    msgBox.setIconPixmap(QPixmap("icon.png"));
    msgBox.exec();
}

// 添加lrc文件
void MainWindow::on_btnAddFile_clicked()
{
    QString file_full = "";
    QString file_name = "";
    // QString file_path = "";
    QString file_suffix = "";

    QFileInfo fileinfo;

    file_full = QFileDialog::getOpenFileName(this, "add file", ".", "lrcfile(*.lrc)"); // 打开文件限定在lrc格式

    fileinfo = QFileInfo(file_full);
    // 文件名
    file_name = fileinfo.fileName();
    // 文件后缀
    file_suffix = fileinfo.suffix();
    // 绝对路径
    path = fileinfo.absolutePath();

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

    N++;
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
    QString name_output;
    for (int i=0; i<listFileName.size(); i++) {
        file_CurrentProccessed = listFileName[i];
        qDebug()<<"File is being converted: "<<file_CurrentProccessed;
        totxt = new LRCtoTXT();
        totxt->readLyric(file_CurrentProccessed, path);

        name_output += listFileName[i] + "\n";
    }

    QMessageBox::about(NULL, "Success", "已成功将:\n" + name_output + "转化为txt文件并储存");
}

// ----- txt->InvertedIndex -----------------------------------
// 使用刚刚转化出的txt生成倒排索引
void MainWindow::on_btnInvertedIndex_clicked()
{
    index = new InvertedIndex();
    for (int i=0; i<listFileName.size(); i++) {
        file_CurrentProccessed = listFileName[i];
        qDebug()<<"InvertedIndex is being generated: "<<file_CurrentProccessed;

        std::string file_ToBeInverted_lrc = path.toStdString() + "/txt_generated/lrc/" + file_CurrentProccessed.toStdString() + ".lrc.txt";
        index->StatWords(file_ToBeInverted_lrc.data(), file_CurrentProccessed, "lrc"); // 将string转换为char*
        std::string file_ToBeInverted_ar = path.toStdString() + "/txt_generated/ar/" + file_CurrentProccessed.toStdString() + ".ar.txt";
        index->StatWords(file_ToBeInverted_ar.data(), file_CurrentProccessed, "ar");
        std::string file_ToBeInverted_ti = path.toStdString() + "/txt_generated/ti/" + file_CurrentProccessed.toStdString() + ".ti.txt";
        index->StatWords(file_ToBeInverted_ti.data(), file_CurrentProccessed, "ti");
        std::string file_ToBeInverted_al = path.toStdString() + "/txt_generated/al/" + file_CurrentProccessed.toStdString() + ".al.txt";
        index->StatWords(file_ToBeInverted_al.data(), file_CurrentProccessed, "al");
    }
    index->SaveResultToTXT("lrc", path);
    index->SaveResultToTXT("ar", path);
    index->SaveResultToTXT("ti", path);
    index->SaveResultToTXT("al", path);
}

// ----- Search & VSM -----------------------------------------
// 点击Search按钮
void MainWindow::on_btnSearch_clicked()
{
    QString searchContent = ui->letSearch->text();
    // qDebug()<<"1";

    if (searchContent=="") {
        QMessageBox::about(NULL, "Warning", "    请输入查询内容     ");
    } else if (ui->cbbRankMode->currentText()=="---Ranking By---") {
        QMessageBox::about(NULL, "Warning", "    请选择排序方式     ");
    } else if (ui->cbbRankMode->currentText()=="full-text") {
        mapOutter = index->result_index_lrc();
        Scores = VSM->calculateScore(searchContent, N, listFileName, mapOutter, "full-text");
        showRank();
    } else if (ui->cbbRankMode->currentText()=="artist") {
        mapOutter = index->result_index_ar();
        Scores = VSM->calculateScore(searchContent, N, listFileName, mapOutter, "artist");
        showRank();
    } else if (ui->cbbRankMode->currentText()=="title") {
        mapOutter = index->result_index_ti();
        Scores = VSM->calculateScore(searchContent, N, listFileName, mapOutter, "title");
        showRank();
    } else if (ui->cbbRankMode->currentText()=="album") {
        mapOutter = index->result_index_al();
        Scores = VSM->calculateScore(searchContent, N, listFileName, mapOutter, "album");
        showRank();
    }
}

void MainWindow::showRank()
{
    // 维护一张追踪文件位置随Scores排序变动的索引表
    QVector<int> list_index(listFileName.length());
    for (int i=0; i<list_index.length(); i++)
    {
        list_index[i] = i;
    }

    // 冒泡排序
    double temp_Scores;
    double temp_index;
    for (int i=0; i<Scores.length(); i++)
    {
        qDebug() << "Final output: " << Scores[i]; // WTF?????
        for (int j=Scores.length()-1; j>i; j--)
        {
            if (Scores[j] > Scores[j-1])
            {
                temp_Scores = Scores[j-1];
                Scores[j-1] = Scores[j];
                Scores[j] = temp_Scores;

                temp_index = list_index[j-1];
                list_index[j-1] = list_index[j];
                list_index[j] = temp_index;
            }
        }
    }

    // 向TableWidget中输出rank结果
    for(int i=0; i<list_index.length(); i++)
    {
        ui->twgRankList->setRowCount(i+1);
        QString content;
        content = listFileName.at(list_index[i]);
        QString score = QString("%1").arg(Scores[i]); // float->QString
        ui->twgRankList->setItem(i, 0, new QTableWidgetItem(content));
        ui->twgRankList->setItem(i, 1, new QTableWidgetItem(score));
    }
}
