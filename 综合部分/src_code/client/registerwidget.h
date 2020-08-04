#pragma execution_character_set("utf-8")
#ifndef REGISTERWIDGET_H
#define REGISTERWIDGET_H

#include <QWidget>
#include <QSqlDatabase>
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>
#include <QVariantList>
#include <QDir>
#include <QTcpSocket>
#include <QHostAddress>
#include <QTextCodec>

#include "strfunction.h"


#define DEFAULT_BUFLEN 1024

namespace Ui {
class registerWidget;
}

class registerWidget : public QWidget
{
    Q_OBJECT

public:
    Ui::registerWidget *ui;
    void dealRegMsg();
    explicit registerWidget(QWidget *parent = nullptr);
    ~registerWidget();

    strFunction strfunc;
signals:
    void logon_signal(QString username,QString password);
private slots:
    void on_pushButtonBack_clicked();
    void on_pushButtonReg_clicked();
private:
    //Ui::registerWidget *ui;
    QTcpSocket *clientSocket;
};

#endif // REGISTERWIDGET_H
