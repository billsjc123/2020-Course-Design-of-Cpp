#pragma execution_character_set("utf-8")
#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QPixmap>
#include <QDebug>
#include <QMessageBox>
#include <QDir>
#include <QTcpSocket>
#include <QHostAddress>
#include <QToolButton>
#include <QMouseEvent>


// 需要用到的字符串工具函数
#include "strfunction.h"

#define DEFAULT_BUFLEN 1024

namespace Ui {
class loginWidget;
}

class loginWidget : public QWidget
{
    Q_OBJECT

public:
    Ui::loginWidget *ui;
    void dealLoginMsg();
    explicit loginWidget(QWidget *parent = nullptr);
    ~loginWidget();
    void paintEvent(QPaintEvent *event);

    strFunction strfunc;
protected:
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

private slots:
    void on_buttonBack_clicked();

    void on_buttonLogin_clicked();
signals:
    void login_signal(int,int);
private:
    QPoint last;
    int port;
    QTcpSocket *clientSocket;
};

#endif // LOGINWIDGET_H
