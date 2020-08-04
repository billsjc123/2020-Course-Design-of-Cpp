#include "strfunction.h"

vector<string> strFunction::split_str(const string &str, char ch)
{
    vector<string> result;
    string newstr;
    for (auto c : str)
    {
        if (c != ch)
        {
            newstr += c;
        }
        else
        {
            result.push_back(newstr);
            newstr = "";
        }
    }
    result.push_back(newstr);
    return result;
}

QString strFunction::GetCorrectUnicode(const QByteArray &ba)
{
    QTextCodec::ConverterState state;
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QString text = codec->toUnicode(ba.constData(), ba.size(), &state);
    if (state.invalidChars > 0)
    {
        text = QTextCodec::codecForName("GBK")->toUnicode(ba);
    }
    else
    {
        text = ba;
    }
    return text;
}

bool strFunction::isValidPassword(QString password)
{
    int size = password.size();
    for (int i=0;i<size;i++) {
        if((password[i]>='0'&&password[i]<='9')||(password[i]<='z')||(password[i]>='A'&&password[i]<='Z'))
        {
            continue;
        }
        else if(password[i]=='-'||password[i]=='_')
        {
            continue;
        }
        else
        {
            return false;
        }
    }
    return true;
}

bool strFunction::isValidUsername(QString username)
{
    int size = username.size();
    for (int i=0;i<size;i++) {
        if((username[i]>='0'&&username[i]<='9')||(username[i]>='a'&&username[i]<='z')||(username[i]>='A'&&username[i]<='Z'))
        {
            continue;
        }
        else if(username[i]=='-'||username[i]=='_')
        {
            continue;
        }
        else
        {
            return false;
        }
    }
    return true;
}
