#pragma execution_character_set("utf-8")

#include "changepasswordwdg.h"
#include "ui_changepasswordwdg.h"

changepasswordWdg::changepasswordWdg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::changepasswordWdg)
{
    ui->setupUi(this);
    //初始化Socket
    this->clientSocket = NULL;

    //分配空间，指定父对象
    clientSocket =new QTcpSocket(this);

    connect(clientSocket,&QTcpSocket::readyRead,this,&changepasswordWdg::dealCngMsg);
}

changepasswordWdg::~changepasswordWdg()
{
    clientSocket->disconnectFromHost();
    delete clientSocket;
    delete ui;
}

void changepasswordWdg::dealCngMsg()
{
    auto msg = clientSocket->read(DEFAULT_BUFLEN);

    // endpoint的端口号，返回给主窗口
    //对于使用toInt(a,10)将QString 类型的a转换成10进制数时，a只能有0-9的字符组成，如果含有其他字符，会输出为0
    QString str= QString(msg).fromLocal8Bit(msg);
    if(str!="Accept.\n")
    {
        QMessageBox::warning(this,tr("修改密码失败"),str.toStdString().c_str());
    }
    else
    {
        QMessageBox::information(this,tr("修改密码成功"),tr("登录成功"));
    }
    ui->pushButtonAdmit->setDisabled(false);
}

void changepasswordWdg::on_pushButtonBack_clicked()
{
    this->hide();
    ui->lineEditNewPsw->clear();
    ui->lineEditOldPsw->clear();
    ui->lineEditNewPsw2->clear();
    ui->pushButtonAdmit->setDisabled(false);
}

void changepasswordWdg::on_pushButtonAdmit_clicked()
{
    QString oldpsw = ui->lineEditOldPsw->text();
    QString newpsw = ui->lineEditNewPsw->text();
    QString newpsw2 = ui->lineEditNewPsw2->text();

    if(newpsw!=newpsw2)
    {
        QMessageBox::warning(this,tr("修改密码失败"),tr("两次输入密码不一致!"));
        ui->lineEditNewPsw->clear();
        ui->lineEditNewPsw2->clear();
        return;
    }
    if(!isValidPassword(oldpsw)||!isValidPassword(newpsw))
    {
        QMessageBox::warning(this,tr("修改密码失败"),tr("密码只能包含数字、英文字母和下划线!"));
        ui->lineEditNewPsw->clear();
        ui->lineEditNewPsw2->clear();
        ui->lineEditOldPsw->clear();
        return;
    }

    emit cngPsw_signal(oldpsw,newpsw);

//    clientSocket->connectToHost("127.0.0.1",port);
//    //避免重复提交
    ui->pushButtonAdmit->setDisabled(true);

//    QString sendStr = "changePassword "+QString::number(playerID)+" "+oldpsw+ " "+newpsw;
//    if(clientSocket->write(sendStr.toLocal8Bit(),DEFAULT_BUFLEN)==-1)
//    {
//        QMessageBox::warning(this,tr("修改密码失败"),tr("服务器错误！"));
//        ui->pushButtonAdmit->setDisabled(false);
//        return;
//    }
}

bool changepasswordWdg::isValidPassword(QString password)
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
