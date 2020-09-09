#pragma execution_character_set("utf-8")
#include "loginwidget.h"
#include "ui_loginwidget.h"

loginWidget::loginWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::loginWidget)
{
    ui->setupUi(this);

    //初始化Socket
    clientSocket = NULL;

    //分配空间，指定父对象
    clientSocket =new QTcpSocket(this);

    connect(clientSocket,&QTcpSocket::readyRead,this,&loginWidget::dealLoginMsg);

    //自定义最小化、关闭等按钮
    int wide = width();//获取界面的宽度

    //隐藏标题栏
    this->setWindowFlag(Qt::FramelessWindowHint);

    //构建最小化、最大化、关闭按钮
    QToolButton *minButton = new QToolButton(this);
    QToolButton *closeButton= new QToolButton(this);
    QToolButton *maxButton= new QToolButton(this);

    //设置最小化、关闭按钮图标
    minButton->setIcon(QPixmap(":/images/images/最小化.png"));
    closeButton->setIcon(QPixmap(":/images/images/关闭.png"));
    maxButton->setIcon(QPixmap(":/images/images/最大化.png"));

    //设置最小化、关闭按钮在界面的位置
    minButton->setGeometry(wide-115,30,30,30);
    maxButton->setGeometry(wide-85,30,30,30);
    closeButton->setGeometry(wide-55,30,30,30);


    //设置鼠标移至按钮上的提示信息
    minButton->setToolTip(tr("最小化"));
    closeButton->setToolTip(tr("关闭"));
    maxButton->setToolTip(tr("最大化"));

    //设置最小化、关闭按钮的样式
    minButton->setStyleSheet("background-color:transparent;");
    closeButton->setStyleSheet("background-color:transparent;");
    maxButton->setStyleSheet("background-color:transparent;");

    connect(closeButton, &QToolButton::clicked, this, &loginWidget::close );
    connect(minButton, &QToolButton::clicked, this,  &loginWidget::showMinimized );
    connect(maxButton, &QToolButton::clicked, this,  &loginWidget::showMaximized );

}

loginWidget::~loginWidget()
{
    delete clientSocket;
    delete ui;
}

void loginWidget::paintEvent(QPaintEvent *)
{
    //设置背景图片
    QPainter p(this);
    //p.drawPixmap(0,0,width(),height(),QPixmap(":/images/images/login_widget_bg.jpg"));
    p.drawPixmap(0,0,width(),height(),QPixmap(":/images/images/login3.png"));
}

void loginWidget::on_buttonBack_clicked()
{
    clientSocket->disconnectFromHost();

    this->hide();
    ui->lineEditPassword->clear();
    ui->lineEditUsername->clear();
    ui->buttonLogin->setDisabled(false);
}

void loginWidget::on_buttonLogin_clicked()
{
    QString username = ui->lineEditUsername->text();
    QString password = ui->lineEditPassword->text();
    if(!strfunc.isValidPassword(password))
    {
        QMessageBox::warning(this,tr("登录失败"),tr("密码只能包含英文字母、数字和下划线"));
        qDebug()<<"Invalid password!";
        ui->lineEditPassword->clear();
        return;
    }
    if(!strfunc.isValidUsername(username))
    {
        QMessageBox::warning(this,tr("登录失败"),tr("用户名只能包含英文字母、数字和下划线"));
        qDebug()<<"Invalid username!";
        ui->lineEditUsername->clear();
        return;
    }
    clientSocket->connectToHost("127.0.0.1",8888);

    QString sendStr = "login "+username+" "+password;
    qDebug()<<sendStr;
    // 避免重复提交
    ui->buttonLogin->setDisabled(true);

    if(clientSocket->write(sendStr.toLocal8Bit(),DEFAULT_BUFLEN)==-1)
    {
        QMessageBox::warning(this,tr("登录失败"),tr("服务器错误！"));
        ui->buttonLogin->setDisabled(false);
        return;
    }
}

void loginWidget::dealLoginMsg()
{
    auto msg = clientSocket->read(DEFAULT_BUFLEN);
    string str =QString(msg).fromLocal8Bit(msg).toStdString();
    vector<string> strs = strfunc.split_str(str,' ');
    // endpoint的端口号，返回给主窗口
    //对于使用toInt(a,10)将QString 类型的a转换成10进制数时，a只能有0-9的字符组成，如果含有其他字符，会输出为0
    //对于stoi函数，如果正确则返回int，不正确则会抛出异常
    //因此需要try catch来解决
    try {
        int port = stoi(strs[0]);
    } catch (std::invalid_argument) {
        //不是数字的情况
        QString qstr = QString(msg).fromLocal8Bit(msg);
        QMessageBox::warning(this,tr("登录失败"),qstr.toStdString().c_str());
        ui->buttonLogin->setDisabled(false);
        ui->lineEditPassword->clear();
        return;
    }
    int port = stoi(strs[0]);
    int id = stoi(strs[1]);
    QMessageBox::information(this,tr("登录成功"),tr("登录成功"));
    emit login_signal(port,id);
    this->hide();
    ui->lineEditPassword->clear();
    ui->buttonLogin->setDisabled(false);
    clientSocket->disconnectFromHost();

}

void loginWidget::mousePressEvent(QMouseEvent *e)
{
    last=e->globalPos();
}
void loginWidget::mouseMoveEvent(QMouseEvent *e)
{
    int dx = e->globalX() - last.x();
        int dy = e->globalY() - last.y();
        last = e->globalPos();
        move(x()+dx, y()+dy);
}
void loginWidget::mouseReleaseEvent(QMouseEvent *e)
{
    int dx = e->globalX() - last.x();
    int dy = e->globalY() - last.y();
    move(x()+dx, y()+dy);
}

