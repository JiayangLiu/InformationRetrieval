#ifndef INVERTEDINDEX_H
#define INVERTEDINDEX_H

#include <QMap>

class InvertedIndex
{
public:
    InvertedIndex();
    ~InvertedIndex();

    int StatWords(const char* file_name);
    std::map<std::string, std::map<std::string,int>> result_index(){return result_index_;}
    int MAXLINE = 200;


private:
    // 存放倒排索引结果，key是单词，value也是map，该map的key是文件名，value是该单词在该文件中出现的次数
    std::map<std::string, std::map<std::string,int>> result_index_;

    int ParseWordsByLine(char* str_line, const char* file_name);
    void InsertWordToMap(char* word, const char* file_name);

    void SaveResultToTXT(std::map<std::string, std::map<std::string,int>> result_index_);
};

#endif // INVERTEDINDEX_H
