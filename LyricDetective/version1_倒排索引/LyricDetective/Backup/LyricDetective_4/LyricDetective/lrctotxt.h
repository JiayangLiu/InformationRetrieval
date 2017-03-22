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

    void readLyric(QString fileName);
    void analysisOneLine(QString str);
    void printLyric();
    void getLyricHeader(QString str);
    int changeStringToInt(QString str_time);
    int i1 = 0;
    void timeSort();

    const int MAX_LYRIC_LINE_NUM = 200;
    const int MAX_LYRCE_REPEAT_NUM = 10;
    QString header[4] = { "ai:", "ar:", "al:", "by:" };
    int lineNum = 0;
    QString Lheader[4];
    QString a;
    QString file_CurrentProccess;


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
