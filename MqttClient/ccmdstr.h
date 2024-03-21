#ifndef CCMDSTR_H
#define CCMDSTR_H

#include <string.h>
#include <vector>
#include <iostream>
#include <qjsonvalue.h>

using namespace std;


string& deletelchr(string &str, const int cc=' ');
string& deleterchr(string &str,const int cc=' ');
string& deletelrchr(string &str,const int cc=' ');
char*     picknumber(const string &src,char *dest,const bool bsigned=false,const bool bdot=false);
string& picknumber(const string &src,string &dest,const bool bsigned=false,const bool bdot=false);
string    picknumber(const string &src,const bool bsigned=false,const bool bdot=false);

// 把字符串中的小写字母转换成大写，忽略不是字母的字符。
// str：待转换的字符串。
char*     toupper(char *str);
string& toupper(string &str);

// 把字符串中的大写字母转换成小写，忽略不是字母的字符。
// str：待转换的字符串。
char*     tolower(char *str);
string& tolower(string &str);



class ccmdstr
{
private:
    vector<string> m_cmdstr;  // 存放拆分后的字段内容。

    ccmdstr(const ccmdstr &) = delete;                      // 禁用拷贝构造函数。
    ccmdstr &operator=(const ccmdstr &) = delete;  // 禁用赋值函数。
public:
    ccmdstr();
    ccmdstr(const string &buffer,const string &sepstr,const bool bdelspace=false);

        const string& operator[](int ii) const     // 重载[]运算符，可以像访问数组一样访问m_cmdstr成员。
        {
            return m_cmdstr[ii];
        }

        // 把字符串拆分到m_cmdstr容器中。
        // buffer：待拆分的字符串。
        // sepstr：buffer中采用的分隔符，注意，sepstr参数的数据类型不是字符，是字符串，如","、" "、"|"、"~!~"。
        // bdelspace：拆分后是否删除字段内容前后的空格，true-删除；false-不删除，缺省不删除。
        void splittocmd(const string &buffer,const string &sepstr,const bool bdelspace=false);

        // 获取拆分后字段的个数，即m_cmdstr容器的大小。
        int size() const { return m_cmdstr.size(); }
        int cmdcount() const { return m_cmdstr.size(); }      // 兼容以前的项目。

        // 从m_cmdstr容器获取字段内容。
        // ii：字段的顺序号，类似数组的下标，从0开始。
        // value：传入变量的地址，用于存放字段内容。
        // 返回值：true-成功；如果ii的取值超出了m_cmdstr容器的大小，返回失败。
        bool getvalue(const int ii,string &value,const int ilen=0) const;      // C++风格字符串。视频中没有第三个参数，加上第三个参数更好。
        bool getvalue(const int ii,char *value,const int ilen=0) const;          // C风格字符串，ilen缺省值为0-全部长度。
        bool getvalue(const int ii,int  &value) const;                                    // int整数。
        bool getvalue(const int ii,unsigned int &value) const;                     // unsigned int整数。
        bool getvalue(const int ii,long &value) const;                                  // long整数。
        bool getvalue(const int ii,unsigned long &value) const;                  // unsigned long整数。
        bool getvalue(const int ii,double &value) const;                              // 双精度double。
        bool getvalue(const int ii,float &value) const;                                  // 单精度float。
        bool getvalue(const int ii,bool &value) const;                                  // bool型。

        ~ccmdstr(); // 析构函数。
};

#endif // CCMDSTR_H
