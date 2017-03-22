#ifndef INVERTEDINDEX_H
#define INVERTEDINDEX_H

#include <QMap>

class InvertedIndex
{
public:
    InvertedIndex();
    ~InvertedIndex();

    int StatWords(const char* file_name,  QString file_CurrentProccessed, QString curr_mode);
    std::map<std::string, std::map<std::string,int>> result_index_lrc(){return result_index_lrc_;}
    std::map<std::string, std::map<std::string,int>> result_index_ar(){return result_index_ar_;}
    std::map<std::string, std::map<std::string,int>> result_index_ti(){return result_index_ti_;}
    std::map<std::string, std::map<std::string,int>> result_index_al(){return result_index_al_;}
    int MAXLINE = 200;
    void SaveResultToTXT(QString curr_mode, QString filePath);
    QString path;

private:
    // 存放倒排索引结果，key是单词，value也是map，该map的key是文件名，value是该单词在该文件中出现的次数
    std::map<std::string, std::map<std::string,int>> result_index_lrc_;
    std::map<std::string, int> file_word_count_lrc_;
    std::map<std::string, std::map<std::string,int>> result_index_ar_;
    std::map<std::string, int> file_word_count_ar_;
    std::map<std::string, std::map<std::string,int>> result_index_ti_;
    std::map<std::string, int> file_word_count_ti_;
    std::map<std::string, std::map<std::string,int>> result_index_al_;
    std::map<std::string, int> file_word_count_al_;

    QString file_CurrentProccessed_incerted;

    int ParseWordsByLine(char* str_line, const char* file_name);
    void InsertWordToMap(char* word, const char* file_name);

    QString mode;

};

#endif // INVERTEDINDEX_H
