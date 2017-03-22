#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QTimer>
#include <QDateTime>
#include <string>

#include <invertedindex.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    void initial();

    QLabel *labelTimer; // 显示当前时间的Label
    QVector<QString> listFileName; // 列表存储显示文件名

    // ----- lrc->txt --------------------------------------
    void readLyric(QString fileName);
    void analysisOneLine(QString str);
    void printLyric();
    void getLyricHeader(QString str);
    int  changeStringToInt(QString str_time);
    int i1 = 0;
    void timeSort();

    const int MAX_LYRIC_LINE_NUM = 200;
    const int MAX_LYRCE_REPEAT_NUM = 10;
    QString header[4] = { "ai:", "ar:", "al:", "by:" };
    int lineNum = 0;
    QString Lheader[4];
    QString a;

    struct OneLineLyric
    {
        int lineNum;
        QString startTime;
        QString endTime;
        QString lyricContent;
    } lyric[200];
    // } lyric[MAX_LYRIC_LINE_NUM]; //动态分配最好

    QString file_CurrentProccessed;

    // ----- txt->InvertedIndex --------------------------------------
    InvertedIndex *index;
    // ---------------------------------------------------------------


private slots:
    void timerUpdate();

    void on_actionAbout_LyricDetective_triggered();
    void on_btnAddFile_clicked();
    void on_btnRemoveFile_clicked();
    void on_btnClearList_clicked();

    void on_btnLRCtoTXT_clicked();
    void on_actionAdd_lrc_triggered();
    void on_btnInvertedIndex_clicked();
};

#endif // MAINWINDOW_H
