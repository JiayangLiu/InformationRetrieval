#include <lrctotxt.h>

#include <fstream>
#include <QMessageBox>

LRCtoTXT::LRCtoTXT()
{
}
LRCtoTXT::~LRCtoTXT()
{
}

void LRCtoTXT::readLyric(QString fileName)
{
    file_CurrentProccessed_lrc = fileName;
    std::string filename_str = "/home/jeremyliu/Desktop/LyricDetective/lrc_suitable/" + fileName.toStdString();

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
void LRCtoTXT::analysisOneLine(QString str)
{
    std::string str_string = str.toStdString();
    if (i1 == 0)
    {
        if (str_string[5] != '[')
        {
            // qDebug() << "歌词文件格式不正规!\n";
            // qDebug() << str_string[6];
        }
    }
    if (i1>0)
    {
        if (str_string[0] != '[')
        {
            // qDebug() << "歌词文件格式不正规!\n";
            // qDebug() << str_string[5];
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
    for (int i = 0; i < 4; i++)
    {
        if (header[i] == QString::fromStdString(str.toStdString().substr(1, 3)));
        {
            Lheader[i] = str;
        }
    }
}
void LRCtoTXT::printLyric()
{
    // qDebug() << "歌曲信息:";
    for (int i = 0; i < 4; i++)
    {
        // qDebug() << Lheader[i];
    }

    for (int i = 0; i < lineNum; i++)
    {
        if (lyric[i].startTime != "")
        {
            // qDebug() << "行    号:\t" << lyric[i].lineNum;
            // qDebug() << "开始时间:\t" << lyric[i].startTime;
            // qDebug() << "结束时间:\t" << lyric[i].endTime;
            // qDebug() << "歌词内容:\t" << lyric[i].lyricContent;
        }
    }

    QString txt_FileName = "/home/jeremyliu/Desktop/LyricDetective/txt_generated/" + file_CurrentProccessed_lrc + ".txt"; // 指定文件夹路径和文件名
    QFile file(txt_FileName);

    if(! file.open(QIODevice::WriteOnly | QIODevice::Text))
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

        // 输出到文件 (后期加messagebox)
        QTextStream in(&file);
        in << content;
        file.close();
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
