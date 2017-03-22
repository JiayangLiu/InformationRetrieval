#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QTimer>
#include <QDateTime>

#include <lrctotxt.h>
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
    LRCtoTXT *totxt; // 建立LRCtoTXT类的对象
    QString file_CurrentProccessed;

    // ----- txt->InvertedIndex --------------------------------------
    InvertedIndex *index; // 建立InvertedIndex类的对象
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
