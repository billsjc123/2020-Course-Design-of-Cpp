#pragma execution_character_set("utf-8")
#ifndef REGISTERWIDGET_H
#define REGISTERWIDGET_H

#include <QWidget>
#include <QDebug>
#include <QMessageBox>
#include <QTcpSocket>
#include <QHostAddress>
#include <QTextCodec>
#include <QPainter>
#include <QToolButton>
#include <QMouseEvent>
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
    void paintEvent(QPaintEvent *);

    strFunction strfunc;
signals:
    void logon_signal(QString username,QString password);
private slots:
    void on_pushButtonBack_clicked();
    void on_pushButtonReg_clicked();
private:
    QPoint last;
    //Ui::registerWidget *ui;
    QTcpSocket *clientSocket;
protected:
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
};

#endif // REGISTERWIDGET_H
