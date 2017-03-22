#include <invertedindex.h>

#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QMessageBox>

InvertedIndex::InvertedIndex()
{
}
InvertedIndex::~InvertedIndex()
{
    result_index_lrc_.clear();
    result_index_ar_.clear();
    result_index_ti_.clear();
    result_index_al_.clear();
}

int InvertedIndex::StatWords(const char* file_name, QString file_CurrentProccessed, QString curr_mode) // file_name is a pointer to const char
{
    mode = curr_mode;

    FILE *fp;
    file_CurrentProccessed_incerted = file_CurrentProccessed;
    if((fp = fopen(file_name,"r")) == NULL)
    {
        // printf("cannot open %s", file_name);
        return -1;
    }

    char str_line[MAXLINE];
    while(fgets(str_line, MAXLINE, fp) != NULL) // fgets(字符数组名，n，文件指针):从fp所指的文件中读出MAXLINE-1个字符送入字符数组str_line中
    {
        int len = strlen(str_line);
        str_line[len-1] = '\0';  /*去掉换行符*/
        ParseWordsByLine(str_line,file_name);
    }
    fclose(fp);
    return 0;
}

int InvertedIndex::ParseWordsByLine(char* str_line,const char* file_name)
{
    if(strlen(str_line) == 0)
    {
        return -1;
    }

    const char* needle=" \n\t\r,?\"";
    /*char *strtok(char *s, const char *delim):strtok在s中查找包含在delim中的字符并用NULL(‘\0’)来替换，直到找遍整个字符串。
    返回值：从s开头开始的一个个被分割的串。当没有被分割的串时则返回NULL。*/
    char* word = strtok(str_line, needle); // str_line为要分解的字符串，needle为分隔符字符串
    while(word != NULL)
    {
        InsertWordToMap(word,file_name);
        word = strtok(NULL, needle);
    }
    return 0;
}

void InvertedIndex::InsertWordToMap(char* word, const char* file_name)
{
    if(strlen(word) == 0)
    {
        return;
    }

    if (mode == "lrc") {
        std::string word_str = word;
        std::string file_name_str = file_CurrentProccessed_incerted.toStdString();

        std::map<std::string, std::map<std::string, int> >::iterator it;
        it = result_index_lrc_.find(word_str);

        if(it == result_index_lrc_.end())
        {
            file_word_count_lrc_.insert(std::pair<std::string, int>(file_name_str,1));
            result_index_lrc_[word_str] = file_word_count_lrc_;
        }
        else
        {
            file_word_count_lrc_ = result_index_lrc_[word_str];
            file_word_count_lrc_[file_name_str] ++ ;
            result_index_lrc_[word_str] = file_word_count_lrc_;
        }
    } else if (mode == "ar") {
        std::string word_str = word;
        std::string file_name_str = file_CurrentProccessed_incerted.toStdString();

        std::map<std::string, std::map<std::string, int> >::iterator it;
        it = result_index_ar_.find(word_str);

        if(it == result_index_ar_.end())
        {
            file_word_count_ar_.insert(std::pair<std::string, int>(file_name_str,1));
            result_index_ar_[word_str] = file_word_count_ar_;
        }
        else
        {
            file_word_count_ar_ = result_index_ar_[word_str];
            file_word_count_ar_[file_name_str] ++ ;
            result_index_ar_[word_str] = file_word_count_ar_;
        }
    } else if (mode == "ti") {
        std::string word_str = word;
        std::string file_name_str = file_CurrentProccessed_incerted.toStdString();

        std::map<std::string, std::map<std::string, int> >::iterator it;
        it = result_index_ti_.find(word_str);

        if(it == result_index_ti_.end())
        {
            file_word_count_ti_.insert(std::pair<std::string, int>(file_name_str,1));
            result_index_ti_[word_str] = file_word_count_ti_;
        }
        else
        {
            file_word_count_ti_ = result_index_ti_[word_str];
            file_word_count_ti_[file_name_str] ++ ;
            result_index_ti_[word_str] = file_word_count_ti_;
        }
    } else if (mode == "al") {
        std::string word_str = word;
        std::string file_name_str = file_CurrentProccessed_incerted.toStdString();

        std::map<std::string, std::map<std::string, int> >::iterator it;
        it = result_index_al_.find(word_str);

        if(it == result_index_al_.end())
        {
            file_word_count_al_.insert(std::pair<std::string, int>(file_name_str,1));
            result_index_al_[word_str] = file_word_count_al_;
        }
        else
        {
            file_word_count_al_ = result_index_al_[word_str];
            file_word_count_al_[file_name_str] ++ ;
            result_index_al_[word_str] = file_word_count_al_;
        }
    }
}

void InvertedIndex::SaveResultToTXT(QString curr_mode, QString filePath)
{
    mode = curr_mode;
    path = filePath;
    if (mode == "lrc") {
        QString txt_FileName = path + "/txt_generated/InvertedIndex/result_lrc.txt"; // 指定文件夹路径和文件名
        QFile file(txt_FileName);

        // 遍历输出map 录入内容
        std::map<std::string, std::map<std::string, int> >::iterator iter_outer;
        std::map<std::string, int>::iterator iter_inner;

        QString content = "";

        for (iter_outer = result_index_lrc_.begin(); iter_outer != result_index_lrc_.end(); ++iter_outer) {
            std::map<std::string, int> inner_map = result_index_lrc_[iter_outer->first];
            content += QString::fromStdString(iter_outer->first) + "\t\t:\t";
            for (iter_inner = inner_map.begin(); iter_inner != inner_map.end(); ++iter_inner) {
                content += "[" + QString::fromStdString(iter_inner->first)  + ", " + QString::number(iter_inner->second,10) + "]   ";
            }
            content += '\n';
        }

        if(! file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QMessageBox::warning(NULL, "Warning", "无法录入文件 result.txt      ");
            return;
        } else {
            // 输出到文件
            QTextStream in(&file);
            in << content;
            file.close();

            QMessageBox::about(NULL, "Success", "成功录入文件 result.txt      ");
        }
    } else if (mode == "ar") {
        QString txt_FileName = path + "/txt_generated/InvertedIndex/result_ar.txt"; // 指定文件夹路径和文件名
        QFile file(txt_FileName);
        // 遍历输出map 录入内容
        std::map<std::string, std::map<std::string, int> >::iterator iter_outer;
        std::map<std::string, int>::iterator iter_inner;
        QString content = "";
        for (iter_outer = result_index_ar_.begin(); iter_outer != result_index_ar_.end(); ++iter_outer) {
            std::map<std::string, int> inner_map = result_index_ar_[iter_outer->first];
            content += QString::fromStdString(iter_outer->first) + "\t\t:\t";
            for (iter_inner = inner_map.begin(); iter_inner != inner_map.end(); ++iter_inner) {
                content += "[" + QString::fromStdString(iter_inner->first)  + ", " + QString::number(iter_inner->second,10) + "]   ";
            }
            content += '\n';
        }
        if(! file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            return;
        } else {
            // 输出到文件
            QTextStream in(&file);
            in << content;
            file.close();
        }
    } else if (mode == "ti") {
        QString txt_FileName = path + "/txt_generated/InvertedIndex/result_ti.txt"; // 指定文件夹路径和文件名
        QFile file(txt_FileName);
        // 遍历输出map 录入内容
        std::map<std::string, std::map<std::string, int> >::iterator iter_outer;
        std::map<std::string, int>::iterator iter_inner;
        QString content = "";
        for (iter_outer = result_index_ti_.begin(); iter_outer != result_index_ti_.end(); ++iter_outer) {
            std::map<std::string, int> inner_map = result_index_ti_[iter_outer->first];
            content += QString::fromStdString(iter_outer->first) + "\t\t:\t";
            for (iter_inner = inner_map.begin(); iter_inner != inner_map.end(); ++iter_inner) {
                content += "[" + QString::fromStdString(iter_inner->first)  + ", " + QString::number(iter_inner->second,10) + "]   ";
            }
            content += '\n';
        }
        if(! file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            return;
        } else {
            // 输出到文件
            QTextStream in(&file);
            in << content;
            file.close();
        }
    } else if (mode == "al") {
        QString txt_FileName = path + "/txt_generated/InvertedIndex/result_al.txt"; // 指定文件夹路径和文件名
        QFile file(txt_FileName);
        // 遍历输出map 录入内容
        std::map<std::string, std::map<std::string, int> >::iterator iter_outer;
        std::map<std::string, int>::iterator iter_inner;
        QString content = "";
        for (iter_outer = result_index_al_.begin(); iter_outer != result_index_al_.end(); ++iter_outer) {
            std::map<std::string, int> inner_map = result_index_al_[iter_outer->first];
            content += QString::fromStdString(iter_outer->first) + "\t\t:\t";
            for (iter_inner = inner_map.begin(); iter_inner != inner_map.end(); ++iter_inner) {
                content += "[" + QString::fromStdString(iter_inner->first)  + ", " + QString::number(iter_inner->second,10) + "]   ";
            }
            content += '\n';
        }

        if(! file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            return;
        } else {
            // 输出到文件
            QTextStream in(&file);
            in << content;
            file.close();
        }
    }
}
