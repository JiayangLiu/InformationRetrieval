#ifndef VECTORSPACEMODEL_H
#define VECTORSPACEMODEL_H

#include <QString>
#include <QMap>

class VectorSpaceModel
{
public:
    VectorSpaceModel();
    ~VectorSpaceModel();

    QVector<double> calculateScore(QString searchContent, int N, QVector<QString> list_file, std::map<std::string, std::map<std::string,int> > mapOutter, QString ranking_mode);

private:


};

#endif // VECTORSPACEMODEL_H
