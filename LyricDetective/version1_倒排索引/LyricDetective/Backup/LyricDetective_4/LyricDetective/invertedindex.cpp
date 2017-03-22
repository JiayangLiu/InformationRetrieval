#include <invertedindex.h>

#include <QFile>
#include <QTextStream>

InvertedIndex::InvertedIndex()
{
}
InvertedIndex::~InvertedIndex()
{
    result_index_.clear();
}

int InvertedIndex::StatWords(const char* file_name) // file_name is a pointer to const char
{
    FILE *fp;
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

    const char* needle=" \n\t";
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
    std::string word_str = word;
    std::string file_name_str = file_name;

    std::map<std::string, std::map<std::string, int>>::iterator it;
    it = result_index_.find(word_str);

    if(it == result_index_.end()) // not found
    {
        std::map<std::string, int> file_word_count;
        file_word_count.insert(std::pair<std::string, int>(file_name_str,1));
        result_index_[word_str] = file_word_count;
    }
    else
    {
        std::map<std::string, int> file_word_count = result_index_[word_str];
        file_word_count[file_name_str] ++ ;
        result_index_[word_str] = file_word_count;
    }

    SaveResultToTXT(result_index_);
}

// (后期加messagebox)
void InvertedIndex::SaveResultToTXT(std::map<std::string, std::map<std::string, int>> result_index_)
{
//    QString txt_FileName = "/home/jeremyliu/Desktop/LyricDetective/txt_generated/result.txt"; // 指定文件夹路径和文件名
//    QFile file(txt_FileName);
//    file.open(QIODevice::WriteOnly | QIODevice::Text);

//    QString content;
    // 录入内容
//    for(int i = 0; i < lineNum; i++)
//    {
//        if (lyric[i].startTime != "")
//        {
//            content += lyric[i].lyricContent + "\n";
//        }
//    }

    // 清空Ma[ 否则之后的输出文件中包含之前的内容

    // 输出到文件 (后期加messagebox)
//    QTextStream in(&file);
//    in << content;
//    file.close();
}

