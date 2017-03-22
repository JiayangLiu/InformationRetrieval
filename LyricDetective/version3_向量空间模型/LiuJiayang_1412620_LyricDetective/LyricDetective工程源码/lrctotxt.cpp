#include <lrctotxt.h>

#include <fstream>
#include <iostream>
#include <QMessageBox>

LRCtoTXT::LRCtoTXT()
{
}
LRCtoTXT::~LRCtoTXT()
{
}

void LRCtoTXT::readLyric(QString fileName, QString filePath)
{
    file_CurrentProccessed_lrc = fileName;
    path = filePath;
//    std::string filename_str = path.toStdString() + "/" + fileName.toStdString();

//    char file[100];
//    strcpy(file, filename_str);


    QString str_name = filePath + "/" + fileName;
    qDebug()<<"current file: "<<str_name;

    char *ch;
    QByteArray ba = str_name.toLatin1();
    ch = ba.data();
    qDebug()<<"current ch*: "<<ch;

    std::ifstream fin;
    fin.open(ch);
    if (!fin.is_open())
    {
        qDebug() << "文件读取失败! 请使用此软件包所提供的正确格式lrc文件.\n";
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
void LRCtoTXT::analysisOneLine(QString str)
{
    std::string str_string = str.toStdString();
    if (i1 < 3)
    {
        // 歌词说明 ar:演唱者 ti:歌曲名称 al:专辑名称
        getLyricHeader(str);
    }

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

    QString contentTemp = QString::fromStdString(str_string); // important

    for (int i = 0; i < p; i++)
    {
        if (lineNum == 1)
        {
            // qDebug() << "";
        }
        lyric[lineNum].startTime = QString::fromStdString(timeTemp[i]);

        if (timeTemp[i + 1] != "") // 连续的
        {
            lyric[lineNum].endTime = QString::fromStdString(timeTemp[i + 1]);
            // qDebug() << QString::fromStdString(timeTemp[i]);
        }

        if (lineNum - 1 >= 0 && i == 0) // 设置上一个的endTime
            lyric[lineNum - 1].endTime = lyric[lineNum].startTime;
        lyric[lineNum].lineNum = lineNum;
        lyric[lineNum].lyricContent = contentTemp;
        lineNum++;
    }

}
void LRCtoTXT::getLyricHeader(QString str)
{
    switch (i1) {
    case 0:
        Lheader[0] = QString::fromStdString(str.toStdString().substr(4, str.length()-5));
        break;
    case 1:
        Lheader[1] = QString::fromStdString(str.toStdString().substr(4, str.length()-5));
        break;
    case 2:
        Lheader[2] = QString::fromStdString(str.toStdString().substr(4, str.length()-5));
        break;
    defalut:
        break;
    }
}
void LRCtoTXT::printLyric()
{
    for (int i=0; i<3; i++) {
        qDebug()<<Lheader[i];
    }
    // full-text录入至./lrc/
    QString path_lrc = path + "/txt_generated/lrc/" + file_CurrentProccessed_lrc + ".lrc.txt"; // 指定文件夹路径和文件名
    QFile file_lrc(path_lrc);
    if(! file_lrc.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::warning(NULL, "Warning", "无法录入文件 " + file_CurrentProccessed_lrc + ".txt");
        return;
    } else {
        QString content;
        // 录入内容
        for(int i = 0; i < lineNum; i++)
        {
            if (lyric[i].startTime != "")
            {
                content += lyric[i].lyricContent + "\n";
            }
        }
        // 清空结构体数组 否则之后的输出文件中包含之前的内容
        memset(&lyric, 0, sizeof(OneLineLyric)*200);
        // 输出到文件
        QTextStream in(&file_lrc);
        in << content;
        file_lrc.close();
    }

    // ar录入至./ar/
    QString path_ar = path + "/txt_generated/ar/" + file_CurrentProccessed_lrc + ".ar.txt"; // 指定文件夹路径和文件名
    QFile file_ar(path_ar);
    if(! file_ar.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::warning(NULL, "Warning", "无法录入文件 " + file_CurrentProccessed_lrc + ".ar.txt");
        return;
    } else {
        QString content;
        // 录入内容
        content = Lheader[0] + "\n";
        // 输出到文件
        QTextStream in(&file_ar);
        in << content;
        file_ar.close();
    }

    // ti录入至./ti/
    QString path_ti = path + "/txt_generated/ti/" + file_CurrentProccessed_lrc + ".ti.txt"; // 指定文件夹路径和文件名
    QFile file_ti(path_ti);
    if(! file_ti.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::warning(NULL, "Warning", "无法录入文件 " + file_CurrentProccessed_lrc + ".ti.txt");
        return;
    } else {
        QString content;
        // 录入内容
        content = Lheader[1] + "\n";
        // 输出到文件
        QTextStream in(&file_ti);
        in << content;
        file_ti.close();
    }

    // al录入至./al/
    QString path_al = path + "/txt_generated/al/" + file_CurrentProccessed_lrc + ".al.txt"; // 指定文件夹路径和文件名
    QFile file_al(path_al);
    if(! file_al.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::warning(NULL, "Warning", "无法录入文件 " + file_CurrentProccessed_lrc + ".al.txt");
        return;
    } else {
        QString content;
        // 录入内容
        content = Lheader[2] + "\n";
        // 输出到文件
        QTextStream in(&file_al);
        in << content;
        file_al.close();
    }
}

// 将时间转换成毫秒
int LRCtoTXT::changeStringToInt(QString str_time)
{
    int time, min, sec, msc = 0; //分钟,秒,毫秒 转换成毫秒
    min = atof(const_cast<const char *>(str_time.toStdString().substr(0, 2).c_str()));
    sec = atof(const_cast<const char *>(str_time.toStdString().substr(3, 2).c_str()));
    if (str_time.length() > 5)
        msc = atof(const_cast<const char *>(str_time.toStdString().substr(4, 2).c_str()));
    time = min * 60 * 100 + sec * 100 + msc;
    return time;
}
