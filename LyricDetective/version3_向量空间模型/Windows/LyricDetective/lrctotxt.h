#ifndef LRCTOTXT_H
#define LRCTOTXT_H

#include <QString>
#include <string>
#include <QDebug>
#include <QFile>

class LRCtoTXT
{
public:
    LRCtoTXT();
    ~LRCtoTXT();

    void readLyric(QString fileName, QString filePath);
    void analysisOneLine(QString str);
    void printLyric();
    void getLyricHeader(QString str);
    int changeStringToInt(QString str_time);
    int i1 = 0;
    void timeSort();

    const int MAX_LYRIC_LINE_NUM = 200;
    const int MAX_LYRCE_REPEAT_NUM = 10;
    QString header[3] = { "ar:", "ti:", "al:"};
    int lineNum = 0;
    QString Lheader[3]; // 存放三种header信息
    QString a;
    QString file_CurrentProccessed_lrc;
    QString path;


    struct OneLineLyric
    {
        int lineNum;
        QString startTime;
        QString endTime;
        QString lyricContent;
    } lyric[200];
    // } lyric[MAX_LYRIC_LINE_NUM]; // 动态分配最好


};

#endif // LRCTOTXT_H
