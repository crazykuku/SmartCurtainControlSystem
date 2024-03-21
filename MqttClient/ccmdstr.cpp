#include "ccmdstr.h"


string& deletelchr(string &str, const int cc)
{
    auto pos=str.find_first_not_of(cc);    // 从字符串的左边查找第一个不是cc的字符的位置。

    if (pos!= 0) str.replace(0,pos,"");       // 把0-pos之间的字符串替换成空。

    return str;
}

string& deleterchr(string &str,const int cc)
{
    auto pos=str.find_last_not_of(cc);     // 从字符串的右边查找第一个不是cc的字符的位置。

    if (pos!= 0) str.erase(pos+1);            // 把pos之后的字符删掉。

    return str;
}

string& deletelrchr(string &str,const int cc)
{
    deletelchr(str,cc);
    deleterchr(str,cc);

    return str;
}

char* toupper(char *str)
{
    if (str == nullptr) return nullptr;

    char* p = str;				// 指向字符串的首地址。
    while (*p != 0)			  // 遍历字符串。
    {
        if ( (*p >= 'a') && (*p <= 'z') ) *p=*p - 32;
        p++;
    }

    return str;
}

string& toupper(string &str)
{
    for (auto &cc:str)
    {
        if ( (cc >= 'a') && (cc <= 'z') ) cc=cc - 32;
    }

    return str;
}

char* tolower(char *str)
{
    if (str == nullptr) return nullptr;

    char* p = str;				// 指向字符串的首地址。
    while (*p != 0)			  // 遍历字符串。
    {
        if ( (*p >= 'A') && (*p <= 'Z') ) *p=*p + 32;
        p++;
    }

    return str;
}

string& tolower(string &str)
{
    for (auto &cc:str)
    {
        if ( (cc >= 'A') && (cc <= 'Z') ) cc=cc + 32;
    }

    return str;
}


char* picknumber(const string &src,char *dest,const bool bsigned,const bool bdot)
{
    if (dest==nullptr) return nullptr;    // 判断空指针。

    string strtemp=picknumber(src,bsigned,bdot);
    strtemp.copy(dest,strtemp.length());
    dest[strtemp.length()]=0;    // string的copy函数不会给C风格字符串的结尾加0。

    return dest;
}

string& picknumber(const string &src,string &dest,const bool bsigned,const bool bdot)
{
    // 为了支持src和dest是同一变量的情况，定义str临时变量。
    string str;

    for (char cc:src)
    {
        // 判断是否提取符号。
        if ( (bsigned==true) && ( (cc == '+') || (cc == '-') ))
        {
            str.append(1,cc); continue;
        }

        // 判断是否提取小数点。
        if ( (bdot==true) && (cc == '.') )
        {
            str.append(1,cc); continue;
        }

        // 提取数字。
        if (isdigit(cc)) str.append(1,cc);
    }

    dest=str;

    return dest;
}

string picknumber(const string &src,const bool bsigned,const bool bdot)
{
    string dest;
    picknumber(src,dest,bsigned,bdot);
    return dest;
}

ccmdstr::ccmdstr(const string &buffer,const string &sepstr,const bool bdelspace)
{
    splittocmd(buffer,sepstr,bdelspace);
}

// 把字符串拆分到m_cmdstr容器中。
// buffer：待拆分的字符串。
// sepstr：buffer字符串中字段内容的分隔符，注意，分隔符是字符串，如","、" "、"|"、"~!~"。
// bdelspace：是否删除拆分后的字段内容前后的空格，true-删除；false-不删除，缺省不删除。
void ccmdstr::splittocmd(const string &buffer,const string &sepstr,const bool bdelspace)
{
    // 清除所有的旧数据
    m_cmdstr.clear();

    int pos=0;        // 每次从buffer中查找分隔符的起始位置。
    int pos1=0;      // 从pos的位置开始，查找下一个分隔符的位置。
    string substr;   // 存放每次拆分出来的子串。

    while ( (pos1=buffer.find(sepstr,pos)) != string::npos)   // 从pos的位置开始，查找下一个分隔符的位置。
    {
        substr=buffer.substr(pos,pos1-pos);            // 从buffer中截取子串。

        if (bdelspace == true) deletelrchr(substr);   // 删除子串前后的空格。

        m_cmdstr.push_back(std::move(substr));     // 把子串放入m_cmdstr容器中，调用string类的移动构造函数。

        pos=pos1+sepstr.length();                           // 下次从buffer中查找分隔符的起始位置后移。
    }

    // 处理最后一个字段（最后一个分隔符之后的内容）。
    substr=buffer.substr(pos);

    if (bdelspace == true) deletelrchr(substr);

    m_cmdstr.push_back(std::move(substr));

    return;
}

bool ccmdstr::getvalue(const int ii,string &value,const int ilen) const
{
    if (ii>=m_cmdstr.size()) return false;

    // 从xml中截取数据项的内容。
    // 视频中是以下代码：
    // value=m_cmdstr[ii];
    // 改为：
    int itmplen=m_cmdstr[ii].length();
    if ( (ilen>0) && (ilen<itmplen) ) itmplen=ilen;
    value=m_cmdstr[ii].substr(0,itmplen);

    return true;
}

bool ccmdstr::getvalue(const int ii,char *value,const int len) const
{
    if ( (ii>=m_cmdstr.size()) || (value==nullptr) ) return false;

    if (len>0) memset(value,0,len+1);   // 调用者必须保证value的空间足够，否则这里会内存溢出。

    if ( (m_cmdstr[ii].length()<=(unsigned int)len) || (len==0) )
    {
        m_cmdstr[ii].copy(value,m_cmdstr[ii].length());
        value[m_cmdstr[ii].length()]=0;    // string的copy函数不会给C风格字符串的结尾加0。
    }
    else
    {
        m_cmdstr[ii].copy(value,len);
        value[len]=0;
    }

    return true;
}

bool ccmdstr::getvalue(const int ii,int &value) const
{
    if (ii>=m_cmdstr.size()) return false;

    try
    {
        value = stoi(picknumber(m_cmdstr[ii],true));  // stoi有异常，需要处理异常。
    }
    catch(const std::exception& e)
    {
        return false;
    }

    return true;
}

bool ccmdstr::getvalue(const int ii,unsigned int &value) const
{
    if (ii >= m_cmdstr.size()) return false;

    try
    {
       value = stoi(picknumber(m_cmdstr[ii]));  // stoi有异常，需要处理异常。不提取符号 + -
    }
    catch(const std::exception& e)
    {
        return false;
    }

    return true;
}

bool ccmdstr::getvalue(const int ii,long &value) const
{
    if (ii>=m_cmdstr.size()) return false;

    try
    {
        value = stol(picknumber(m_cmdstr[ii],true));  // stol有异常，需要处理异常。
    }
    catch(const std::exception& e)
    {
        return false;
    }

    return true;
}

bool ccmdstr::getvalue(const int ii,unsigned long &value) const
{
    if (ii>=m_cmdstr.size()) return false;

    try
    {
        value = stoul(picknumber(m_cmdstr[ii]));  // stoul有异常，需要处理异常。不提取符号 + -
    }
    catch(const std::exception& e)
    {
        return false;
    }

    return true;
}

bool ccmdstr::getvalue(const int ii,double &value) const
{
    if (ii>=m_cmdstr.size()) return false;

    try
    {
        value = stod(picknumber(m_cmdstr[ii],true,true));  // stod有异常，需要处理异常。提取符号和小数点。
    }
    catch(const std::exception& e)
    {
        return false;
    }

    return true;
}

bool ccmdstr::getvalue(const int ii,float &value) const
{
    if (ii>=m_cmdstr.size()) return false;

    try
    {
        value = stof(picknumber(m_cmdstr[ii],true,true));  // stof有异常，需要处理异常。提取符号和小数点。
    }
    catch(const std::exception& e)
    {
        return false;
    }

    return true;
}

bool ccmdstr::getvalue(const int ii,bool &value) const
{
    if (ii>=m_cmdstr.size()) return false;

    string str=m_cmdstr[ii];
    toupper(str);     // 转换为大写来判断。

    if (str=="TRUE") value=true;
    else value=false;

    return true;
}

ccmdstr::~ccmdstr()
{
    m_cmdstr.clear();
}

ostream& operator<<(ostream& out, const ccmdstr& cmdstr)
{
    for (int ii=0;ii<cmdstr.size();ii++)
        out << "[" << ii << "]=" << cmdstr[ii] << endl;

    return out;
}
