#include <vectorspacemodel.h>

#include <QMessageBox>
#include <QDebug>
#include <math.h>

VectorSpaceModel::VectorSpaceModel()
{
}
VectorSpaceModel::~VectorSpaceModel()
{
}

QVector<double> VectorSpaceModel::calculateScore(QString searchContent, int N, QVector<QString> list_file, std::map<std::string, std::map<std::string,int> > mapOutter, QString ranking_mode)
{
    QStringList term_list = searchContent.split(" ");
    QVector<double> Scores(N);
    QVector<double> Length(N);
    QVector<int> count(term_list.length()); // 存放各词项在查询中出现次数
    QVector<QString> term_distinct;

    // 生成无重复的term列表并维护存放各词项在查询中出现次数的列表
    for (int i=0; i<term_list.length(); i++)
    {
        bool distinct = true;
        for (int j=0; j<term_distinct.length(); j++)
        {
            if (term_distinct.at(j)==term_list.at(i))
            {
                distinct = false;
            }
        }
        if (distinct)
        {
            term_distinct.append(term_list.at(i));
            count[term_distinct.indexOf(term_list.at(i))] = 1;
        } else {
            count[term_distinct.indexOf(term_list.at(i))] ++;
        }
    }

    qDebug()<<"去重后的字符串为:";
    for (int i=0; i<term_distinct.length(); i++)
    {
        qDebug()<<term_distinct[i];
    }

    QString term_CurrProcess;
    std::map<std::string, int>::iterator iter_inner;

    for (int t=0; t<term_distinct.length(); t++) {
        term_CurrProcess = term_distinct.at(t);
        qDebug()<<"term_CurrProcess: "<<term_distinct.at(t);

        std::map<std::string, int> mapInner = mapOutter[term_CurrProcess.toStdString()];
        int d;

        for (iter_inner = mapInner.begin(); iter_inner != mapInner.end(); ++iter_inner)
        {

            d = list_file.indexOf(QString::fromStdString(iter_inner->first));
            double N_double = (double)N + 0.0001; // 避免log(int)返回int使得乘数被约为0
            double size_double = (double)mapInner.size() + 0.0001;

            Scores[d] += (1+log(iter_inner->second)) * pow((N_double/size_double),2) * (1+log(count.at(term_distinct.indexOf(term_CurrProcess))));
        }
    }

    // 计算Length
    std::map<std::string, std::map<std::string, int> >::iterator iter_outer_length;
    std::map<std::string, int>::iterator iter_inner_length;
    int d;
    for (iter_outer_length = mapOutter.begin(); iter_outer_length != mapOutter.end(); ++iter_outer_length) {
        std::map<std::string, int> mapInner = mapOutter[iter_outer_length->first];
        for (iter_inner_length = mapInner.begin(); iter_inner_length != mapInner.end(); ++iter_inner_length) {
            for (int i=0; i<list_file.length(); i++) {
                if (list_file.at(i) == QString::fromStdString(iter_inner_length->first)) {
                    d = list_file.indexOf(QString::fromStdString(iter_inner_length->first));
                    Length[d] += pow(iter_inner_length->second, 2);
                }
            }
        }
    }

    for (int i=0; i<Scores.length(); i++)
    {
        qDebug()<<"Lyric:   "<<list_file[i];
        qDebug()<<"Scores:  "<<Scores[i];
        qDebug()<<"Length:  "<<Length[i];
        Scores[i] = Scores[i] / sqrt(Length[i]);
        qDebug()<<Scores[i];
    }

    return Scores;
}
