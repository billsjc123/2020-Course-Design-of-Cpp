#ifndef STRFUNCTION_H
#define STRFUNCTION_H

#pragma once
#include <string>
#include <vector>
#include <QString>
#include <QDebug>
#include <QTextCodec>
using namespace std;

class strFunction
{
public:
    vector<string> split_str(const string &str, char ch);
    QString GetCorrectUnicode(const QByteArray &ba);
    bool isValidUsername(QString username);
    bool isValidPassword(QString password);
};


#endif // STRFUNCTION_H
