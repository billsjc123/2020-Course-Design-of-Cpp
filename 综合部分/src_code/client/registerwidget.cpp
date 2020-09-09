#include "registerwidget.h"
#include "ui_registerwidget.h"

registerWidget::registerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::registerWidget)
{
    ui->setupUi(this);
    //初始化Socket
    clientSocket = NULL;

    //分配空间，指定父对象
    clientSocket =new QTcpSocket(this);

    connect(clientSocket,&QTcpSocket::readyRead,this,&registerWidget::dealRegMsg);

    //构建最小化、最大化、关闭按钮
    QToolButton *minButton = new QToolButton(this);
    QToolButton *closeButton= new QToolButton(this);
    QToolButton *maxButton= new QToolButton(this);

    //设置最小化、关闭按钮图标
    minButton->setIcon(QPixmap(":/images/images/最小化.png"));
    closeButton->setIcon(QPixmap(":/images/images/关闭.png"));
    maxButton->setIcon(QPixmap(":/images/images/最大化.png"));

    setWindowFlag(Qt::FramelessWindowHint);

    int wide = width();

    //设置最小化、关闭按钮在界面的位置
    minButton->setGeometry(wide-115,20,30,30);
    maxButton->setGeometry(wide-85,20,30,30);
    closeButton->setGeometry(wide-55,20,30,30);


    //设置鼠标移至按钮上的提示信息
    minButton->setToolTip(tr("最小化"));
    closeButton->setToolTip(tr("关闭"));
    maxButton->setToolTip(tr("最大化"));

    //设置最小化、关闭按钮的样式
    minButton->setStyleSheet("background-color:transparent;");
    closeButton->setStyleSheet("background-color:transparent;");
    maxButton->setStyleSheet("background-color:transparent;");

    connect(closeButton, &QToolButton::clicked, this, &registerWidget::close );
    connect(minButton, &QToolButton::clicked, this,  &registerWidget::showMinimized );
    connect(maxButton, &QToolButton::clicked, this,  &registerWidget::showMaximized );
}

registerWidget::~registerWidget()
{
    delete ui;
}

void registerWidget::paintEvent(QPaintEvent *)
{
    //设置背景图片
    QPainter p(this);
    //p.drawPixmap(0,0,width(),height(),QPixmap(":/images/images/login_widget_bg.jpg"));
    p.drawPixmap(0,0,width(),height(),QPixmap(":/images/images/login3.png"));
}

void registerWidget::on_pushButtonBack_clicked()
{
    this->hide();
    ui->lineEditUsename->clear();
    ui->lineEditPassword->clear();
    ui->lineEditPassword_2->clear();
    clientSocket->disconnectFromHost();

}

void registerWidget::on_pushButtonReg_clicked()
{
    clientSocket->connectToHost("127.0.0.1",8888);

    QString username = ui->lineEditUsename->text();
    QString psw = ui->lineEditPassword->text();
    QString psw2 = ui->lineEditPassword_2->text();
    if(!strfunc.isValidPassword(psw))
    {
        QMessageBox::warning(this,tr("注册失败"),tr("密码只能包含英文字母、数字和下划线"));
        qDebug()<<"Invalid password!";
        ui->lineEditPassword->clear();
        ui->lineEditPassword_2->clear();
        return;
    }
    if(!strfunc.isValidUsername(username))
    {
        QMessageBox::warning(this,tr("注册失败"),tr("用户名只能包含英文字母、数字和下划线"));
        qDebug()<<"Invalid username!";
        ui->lineEditUsename->clear();
        ui->lineEditPassword->clear();
        ui->lineEditPassword_2->clear();
        return;
    }
    if(psw!=psw2)
    {
        ui->labelWarning->setText("两次密码不一致！请重新输入！");
        ui->lineEditPassword->clear();
        ui->lineEditPassword_2->clear();
        return;
    }

    QString sendStr = "logon "+username+" "+psw;
    qDebug()<<sendStr;
    // 避免重复提交
    ui->pushButtonReg->setDisabled(true);

    if(clientSocket->write(sendStr.toLocal8Bit(),DEFAULT_BUFLEN)==-1)
    {
        QMessageBox::warning(this,tr("注册失败"),tr("服务器错误！"));
        ui->pushButtonReg->setDisabled(false);
        return;
    }
}

void registerWidget::dealRegMsg()
{
    auto msg = clientSocket->read(DEFAULT_BUFLEN);

    // endpoint的端口号，返回给主窗口
    //对于使用toInt(a,10)将QString 类型的a转换成10进制数时，a只能有0-9的字符组成，如果含有其他字符，会输出为0
    if(QString(msg)!="Accept!\n")
    {

        QString str = QString(msg).fromLocal8Bit(msg);
        //qDebug()<<str.fromLocal8Bit(msg);
        QMessageBox::warning(this,tr("注册失败"),tr(str.toStdString().c_str()));
    }
    else
    {
        ui->labelWarning->setText("注册成功");
        QMessageBox::information(this,tr("注册成功"),tr("注册成功"));
        this->close();
        ui->lineEditUsename->clear();
        ui->lineEditPassword->clear();
        ui->lineEditPassword_2->clear();
        clientSocket->disconnectFromHost();
    }
    ui->pushButtonReg->setDisabled(false);
}

void registerWidget::mousePressEvent(QMouseEvent *e)
{
    last=e->globalPos();
}
void registerWidget::mouseMoveEvent(QMouseEvent *e)
{
    int dx = e->globalX() - last.x();
        int dy = e->globalY() - last.y();
        last = e->globalPos();
        move(x()+dx, y()+dy);
}
void registerWidget::mouseReleaseEvent(QMouseEvent *e)
{
    int dx = e->globalX() - last.x();
    int dy = e->globalY() - last.y();
    move(x()+dx, y()+dy);
}
