#include "pokemonwidget.h"
#include "ui_pokemonwidget.h"

PokemonWidget::PokemonWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PokemonWidget)
{
    ui->setupUi(this);
    //setWindowFlags (Qt::CustomizeWindowHint);
    setWindowIcon(QIcon(":/images/images/pokemonball.ico"));
    //初始化Socket
    clientSocket = NULL;
    onlineSocket = NULL;
    //分配空间，指定父对象
    clientSocket =new QTcpSocket(this);
    onlineSocket =new QTcpSocket(this);
    //一开始是连接8888端口的Hub
    port = 8888;

    //初始化登录窗口和注册窗口
    login = NULL;
    reg = NULL;
    mediaPlayer = new QMediaPlayer(this);
    //不能有this，不然子窗口内容会直接显示在主窗口中
    login=new loginWidget();
    reg = new registerWidget();

    connect(login,&loginWidget::login_signal,this,&PokemonWidget::login_slot);

    connect(clientSocket,&QTcpSocket::readyRead,this,&PokemonWidget::dealServerMsg);

    connect(ui->pushButtonChgName,&QPushButton::clicked,this,[this]
    {
        QString str = "changePokemonName ";
                str+=QString::number(pokemonID);
                str+=' ';
                str+=ui->tablePokemonDetail->item(0,0)->text();
        qDebug()<<str.toLocal8Bit();
        if(clientSocket->write(str.toLocal8Bit(),DEFAULT_BUFLEN)==-1)
        {
            QMessageBox::warning(this,tr("修改小精灵名称失败"),tr("服务器错误！"));
            return;
        }
        changeState(CNGPONAME);
    });

    ui->pushButtonChgPsw->setToolTip("修改密码");
    ui->pushButtonLouout->setToolTip("登出");

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
    minButton->setGeometry(wide-155,20,50,50);
    maxButton->setGeometry(wide-105,20,50,50);
    closeButton->setGeometry(wide-55,20,50,50);

    //设置鼠标移至按钮上的提示信息
    minButton->setToolTip(tr("最小化"));
    closeButton->setToolTip(tr("关闭"));
    maxButton->setToolTip(tr("最大化"));

    //设置最小化、关闭按钮的样式
    minButton->setStyleSheet("background-color:transparent;");
    closeButton->setStyleSheet("background-color:transparent;");
    maxButton->setStyleSheet("background-color:transparent;");

    connect(closeButton, &QToolButton::clicked, this, &PokemonWidget::close );
    connect(minButton, &QToolButton::clicked, this,  &PokemonWidget::showMinimized );
    connect(maxButton, &QToolButton::clicked, this,  &PokemonWidget::showMaximized );

    fightcontroller.mode=NOFIGHT;
    fightcontroller.initFight=true;


    ui->tablePokemon1->setColumnCount(1); //设置列数
    ui->tablePokemon1->setRowCount(8); //设置行数
    ui->tablePokemon1->setVerticalHeaderLabels({tr("POKEMONID"),tr("NAME"),tr("RACE"),"ATK","DFS","HP","SPEED","LV"});
    ui->tablePokemon1->verticalHeader()->setStyleSheet("QHeaderView::section{background:#666666;color:white;}");
    ui->tablePokemon1->verticalHeader()->setFont(QFont("Terminal", 10 ));
    ui->tablePokemon1->horizontalHeader()->hide();
    QFont font = ui->tablePokemon1->verticalHeader()->font(); //先获取字体
    font.setBold(true); //字体设置为粗体
    ui->tablePokemon1->verticalHeader()->setFont(font); //设置每一列的标题字体为粗体
    ui->tablePokemon1->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); //宽度自适应
    ui->tablePokemon1->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch); //高度自适应
    // 设置属性
    ui->tablePokemon1->setEditTriggers(QAbstractItemView::NoEditTriggers);//Table只读

    ui->tablePokemon2->setColumnCount(1); //设置列数
    ui->tablePokemon2->setRowCount(8); //设置行数
    ui->tablePokemon2->setVerticalHeaderLabels({tr("POKEMONID"),tr("NAME"),tr("RACE"),"ATK","DFS","HP","SPEED","LV"});
    ui->tablePokemon2->verticalHeader()->setStyleSheet("QHeaderView::section{background:#666666;color:white;}");
    ui->tablePokemon2->verticalHeader()->setFont(QFont("Terminal", 10 ));

    ui->tablePokemon2->horizontalHeader()->hide();
    font = ui->tablePokemon2->verticalHeader()->font(); //先获取字体
    font.setBold(true); //字体设置为粗体
    ui->tablePokemon2->verticalHeader()->setFont(font); //设置每一列的标题字体为粗体
    ui->tablePokemon2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); //宽度自适应
    ui->tablePokemon2->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch); //高度自适应
    // 设置属性
    ui->tablePokemon2->setEditTriggers(QAbstractItemView::NoEditTriggers);//Table只读

    //初始化给出小精灵界面的3个table
    //Table1
    ui->tableWidgetLosePokemon1->setColumnCount(1); //设置列数
    ui->tableWidgetLosePokemon1->setRowCount(8); //设置行数
    ui->tableWidgetLosePokemon1->setVerticalHeaderLabels({tr("POKEMONID"),tr("NAME"),tr("RACE"),"ATK","DFS","HP","SPEED","LV"});
    ui->tableWidgetLosePokemon1->verticalHeader()->setStyleSheet("QHeaderView::section{background:#666666;color:white;}");
    ui->tableWidgetLosePokemon1->verticalHeader()->setFont(QFont("Terminal", 10 ));

    ui->tableWidgetLosePokemon1->horizontalHeader()->hide();
    font = ui->tableWidgetLosePokemon1->verticalHeader()->font(); //先获取字体
    font.setBold(true); //字体设置为粗体
    ui->tableWidgetLosePokemon1->verticalHeader()->setFont(font); //设置每一列的标题字体为粗体
    ui->tableWidgetLosePokemon1->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); //宽度自适应
    ui->tableWidgetLosePokemon1->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch); //高度自适应
    // 设置属性
    ui->tableWidgetLosePokemon1->setEditTriggers(QAbstractItemView::NoEditTriggers);//Table只读

    //Table2
    ui->tableWidgetLosePokemon2->setColumnCount(1); //设置列数
    ui->tableWidgetLosePokemon2->setRowCount(8); //设置行数
    ui->tableWidgetLosePokemon2->setVerticalHeaderLabels({tr("POKEMONID"),tr("NAME"),tr("RACE"),"ATK","DFS","HP","SPEED","LV"});
    ui->tableWidgetLosePokemon2->horizontalHeader()->hide();
    ui->tableWidgetLosePokemon2->verticalHeader()->setStyleSheet("QHeaderView::section{background:#666666;color:white;}");
    ui->tableWidgetLosePokemon2->verticalHeader()->setFont(QFont("Terminal", 10 ));

    font = ui->tableWidgetLosePokemon2->verticalHeader()->font(); //先获取字体
    font.setBold(true); //字体设置为粗体
    ui->tableWidgetLosePokemon2->verticalHeader()->setFont(font); //设置每一列的标题字体为粗体
    ui->tableWidgetLosePokemon2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); //宽度自适应
    ui->tableWidgetLosePokemon2->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch); //高度自适应
    // 设置属性
    ui->tableWidgetLosePokemon2->setEditTriggers(QAbstractItemView::NoEditTriggers);//Table只读
    ui->tableWidgetLosePokemon2->verticalHeader()->setStyleSheet("QHeaderView::section{background:#666666;color:white;}");
    ui->tableWidgetLosePokemon2->verticalHeader()->setFont(QFont("Terminal", 10 ));

    //Table3
    ui->tableWidgetLosePokemon3->setColumnCount(1); //设置列数
    ui->tableWidgetLosePokemon3->setRowCount(8); //设置行数
    ui->tableWidgetLosePokemon3->setVerticalHeaderLabels({tr("POKEMONID"),tr("NAME"),tr("RACE"),"ATK","DFS","HP","SPEED","LV"});
    ui->tableWidgetLosePokemon3->horizontalHeader()->hide();

    ui->tableWidgetLosePokemon3->verticalHeader()->setStyleSheet("QHeaderView::section{background:#666666;color:white;}");
    ui->tableWidgetLosePokemon3->verticalHeader()->setFont(QFont("Terminal", 10 ));
    font = ui->tableWidgetLosePokemon3->verticalHeader()->font(); //先获取字体
    font.setBold(true); //字体设置为粗体
    ui->tableWidgetLosePokemon3->verticalHeader()->setFont(font); //设置每一列的标题字体为粗体
    ui->tableWidgetLosePokemon3->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); //宽度自适应
    ui->tableWidgetLosePokemon3->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch); //高度自适应
    // 设置属性
    ui->tableWidgetLosePokemon3->setEditTriggers(QAbstractItemView::NoEditTriggers);//Table只读


    // 设置BadgeTip字体
    QFont font_badge("Terminal", 12, 75);
    ui->labelBadge1Tip->setFont(font_badge);
    ui->labelBadge2Tip->setFont(font_badge);

    //跳到登录界面
    changeState(LOGIN);
}

void PokemonWidget::initStyles()
{
    //加载样式表
    QFile file(":/qss/qss/psblack.css");
    if (file.open(QFile::ReadOnly)) {
        QString qss = QLatin1String(file.readAll());
        QString paletteColor = qss.mid(20, 7);
        qApp->setPalette(QPalette(QColor(paletteColor)));
        qApp->setStyleSheet(qss);
        file.close();
    }
}

PokemonWidget::~PokemonWidget()
{
    delete login;
    delete reg;
    delete clientSocket;
    delete ui;
}

void PokemonWidget::paintEvent(QPaintEvent *)
{
    //设置背景图片
    QPainter p(this);
    p.drawPixmap(0,0,width(),height(),QPixmap(":/images/images/login_bg2.jpg"));
}

void PokemonWidget::changeState(State state)
{
    QString sendStr;
    this->state=state;
    switch (state) {
    case MAIN:
        ui->stackedWidget->setCurrentIndex(1);
        ui->pushButtonPoList->setDisabled(false);
        ui->pushButtonUserList->setDisabled(false);
        ui->pushButtonLouout->setDisabled(false);
        ui->pushButtonChgPsw->setDisabled(false);
        break;
    case LOGIN:
        ui->stackedWidget->setCurrentIndex(0);
        break;
    case USERLIST:
        ui->stackedWidget->setCurrentIndex(3);
        break;
    case POKEMONLIST:
        ui->stackedWidget->setCurrentIndex(4);
        break;
    case CNGPSW:
        ui->stackedWidget->setCurrentIndex(2);
        break;
    case POKEMONINFO:
        ui->stackedWidget->setCurrentIndex(5);
        break;
    case FIGHT:
        ui->stackedWidget->setCurrentIndex(6);
        sendStr = "battle ";
        sendStr += QString::number(fightcontroller.myPokemonid)+' '+QString::number(fightcontroller.opponentPokemonid);
        if(clientSocket->write(sendStr.toLocal8Bit(),DEFAULT_BUFLEN)==-1)
        {
            QMessageBox::warning(this,tr("战斗失败"),tr("服务器错误！"));
            break;
        }
        qDebug()<<"初始化战斗成功";
        break;
    case LOSEPOKEMON:
        ui->stackedWidget->setCurrentIndex(7);
        break;
    default:
        break;
    }
}

void PokemonWidget::dealServerMsg()
{
    QString msg = QString::fromLocal8Bit(clientSocket->read(DEFAULT_BUFLEN));
    string str = msg.toStdString();

    int cntPokemon,cnt15;
    switch (state) {
    case LOSEPOKEMON:
        if(str == "服务器数据库错误")
        {
            qDebug()<<"服务器数据库错误";
            QMessageBox::warning(this,tr("给出小精灵失败"),tr("服务器数据库错误"));
            changeState(MAIN);
        }
        else
        {
            auto pokemons = msg.split('\n');
            QTableWidget* table;
            QLabel* label;
            int pokemons_size = pokemons.size();
            ui->pushButtonLosePokemon1->setDisabled(true);
            ui->pushButtonLosePokemon2->setDisabled(true);
            ui->pushButtonLosePokemon3->setDisabled(true);

            for (int i=0;i<pokemons_size-1;i++) {
                if(i==0)
                {
                    table = ui->tableWidgetLosePokemon1;
                    label = ui->labelLosePokemon1;
                    ui->pushButtonLosePokemon1->setDisabled(false);
                }
                else if(i==1)
                {
                    label = ui->labelLosePokemon2;
                    table = ui->tableWidgetLosePokemon2;
                    ui->pushButtonLosePokemon2->setDisabled(false);
                }
                else if(i==2)
                {
                    label = ui->labelLosePokemon3;
                    table = ui->tableWidgetLosePokemon3;
                    ui->pushButtonLosePokemon3->setDisabled(false);
                }
                auto detail = pokemons[i].split(' ');

                setPokemonImg(label,detail[2]);
                QTableWidgetItem* t ;

                for (int j=0;j<8;j++) {
                    t= new QTableWidgetItem(detail[j]);
                    t->setFlags(t->flags()^Qt::ItemIsEnabled);
                    table->setItem(j,0,t);
                }
            }
        }
        break;
    case FIGHT:
        if(str == "服务器数据库错误")
        {
            qDebug()<<"服务器数据库错误";
            QMessageBox::warning(this,tr("战斗失败"),tr("服务器数据库错误"));
            changeState(MAIN);
            fightcontroller.mode=NOFIGHT;
            fightcontroller.initFight=true;
        }
        else
        {
            //开始对战！
            ui->pushButtonBackFromBattle->setDisabled(true);
            qDebug()<<msg;
            //infos[0]--对战信息 infos[1]--pokemon1 infos[2]--pokemon2

            auto infos = msg.split('\n');

            //先处理对战信息
            auto detail = infos[0].split(' ');
            int battleround = detail[0].toInt();

            //初始化战斗
            if(battleround==2)
            {
                detail = infos[1].split(' ');
                int battlehp=detail[5].toInt(),maxhp=detail[8].toInt();
                // 添加图片
                setPokemonImg(ui->labelPokemon1,detail[2]);

                QTableWidgetItem* t;
                for (int i=0;i<8;i++) {
                    if(i==5)
                        t = new QTableWidgetItem(detail[i]+'/'+detail[8]);
                    else
                        t = new QTableWidgetItem(detail[i]);
                    t->setFlags(t->flags()^Qt::ItemIsEnabled);
                    ui->tablePokemon1->setItem(i,0,t);
                }

                ui->progressBarPokemon1->setMaximum(maxhp);
                ui->progressBarPokemon1->setValue(battlehp);
                //处理pokemon2的数据
                detail = infos[2].split(' ');
                battlehp=detail[5].toInt(),maxhp=detail[8].toInt();
                // 添加图片
                setPokemonImg(ui->labelPokemon2,detail[2]);

                for (int i=0;i<8;i++) {
                    if(i==5)
                        t = new QTableWidgetItem(detail[i]+'/'+detail[8]);
                    else
                        t = new QTableWidgetItem(detail[i]);
                    t->setFlags(t->flags()^Qt::ItemIsEnabled);
                    ui->tablePokemon2->setItem(i,0,t);
                }

                ui->progressBarPokemon2->setMaximum(maxhp);
                ui->progressBarPokemon2->setValue(battlehp);
                QString attacker_name,opponent_name;
                attacker_name = ui->tablePokemon1->item(1,0)->text();
                opponent_name = ui->tablePokemon2->item(1,0)->text();
                ui->textBrowserFightInfo->append("------------战斗开始！-----------\n");
                ui->textBrowserFightInfo->append(tr((attacker_name+" vs "+opponent_name+"!\n\n").toStdString().c_str()));
                QString str = "continue";
                if(clientSocket->write(str.toLocal8Bit(),DEFAULT_BUFLEN)==-1)
                {
                    QMessageBox::warning(this,tr("战斗失败"),tr("服务器错误！"));
                    return;
                }
            }
            else if(battleround==3)
            {
                ui->textBrowserFightInfo->append("\n\n------------战斗结束！-----------\n");
                detail = infos[1].split(' ');
                if(detail[0]=='1')
                    ui->textBrowserFightInfo->append("获胜者是: "+ui->tablePokemon1->item(1,0)->text()+"!\n");
                else
                    ui->textBrowserFightInfo->append("获胜者是: "+ui->tablePokemon2->item(1,0)->text()+"!\n");
                ui->textBrowserFightInfo->append(ui->tablePokemon1->item(1,0)->text()+"获得经验值: "+detail[1]+"!\n");
                ui->textBrowserFightInfo->append(ui->tablePokemon2->item(1,0)->text()+"获得经验值: "+detail[2]+"!\n");
                QString str = "end";
                if(clientSocket->write(str.toLocal8Bit(),DEFAULT_BUFLEN)==-1)
                {
                    QMessageBox::warning(this,tr("战斗失败"),tr("服务器错误！"));
                    return;
                }

                ui->pushButtonBackFromBattle->setDisabled(false);

                 // 决斗模式，进行结算
                if(fightcontroller.mode==DUELMODE)
                {
                    // 获胜，获得该小精灵
                    if(detail[0]=='1')
                    {
                        changePokemonMaster(ui->tablePokemon2->item(0,0)->text().toInt(),playerID);
                        QMessageBox::information(this,tr("战斗胜利！"),tr("战斗胜利，和新伙伴打个招呼吧！(*^_^*)"));
                        getPokemonList(playerID);
                        ui->textBrowserFightInfo->clear();
                    }
                    // 失败，从自己的小精灵中由系统选择三个，玩家挑一个送出
                    else
                    {
                        QMessageBox::information(this,tr("战斗失败！"),tr("和你的某一只小精灵说再见吧/(ㄒoㄒ)/~~"));
                        QString str = "losePokemon";
                        if(clientSocket->write(str.toLocal8Bit(),DEFAULT_BUFLEN)==-1)
                        {
                            QMessageBox::warning(this,tr("给出小精灵失败"),tr("服务器错误！"));
                            return;
                        }
                        changeState(LOSEPOKEMON);
                        ui->textBrowserFightInfo->clear();

                    }
                }
                else
                {
                    if(detail[0]=='1')
                        QMessageBox::information(this,tr("战斗胜利！"),tr("矮油，不错喔~"));
                    else
                        QMessageBox::information(this,tr("战斗失败！"),tr("胜败乃兵家常事，大侠请从头来过！"));
                }

            }
            else
            {
                QString skillname = detail[1];
                bool dodge = detail[2].toInt(),critical_strike = detail[3].toInt();

                // 根据infos[0]输出信息
                QString attacker_name,opponent_name;
                if(battleround==0)
                {
                    //pokemon1 攻击 pokemon2
                    attacker_name = ui->tablePokemon1->item(1,0)->text();
                    opponent_name = ui->tablePokemon2->item(1,0)->text();

                }
                else
                {
                    attacker_name = ui->tablePokemon2->item(1,0)->text();
                    opponent_name = ui->tablePokemon1->item(1,0)->text();
                }
                ui->textBrowserFightInfo->append(tr((attacker_name+"使出了"+skillname+"!\n").toStdString().c_str()));
                if(dodge)
                {
                    ui->textBrowserFightInfo->append(tr((opponent_name+"居然闪开了!\n").toStdString().c_str()));
                    QString str = "continue";
                    if(clientSocket->write(str.toLocal8Bit(),DEFAULT_BUFLEN)==-1)
                    {
                        QMessageBox::warning(this,tr("战斗失败"),tr("服务器错误！"));
                        return;
                    }
                    break;
                }
                if(critical_strike)
                {
                    ui->textBrowserFightInfo->append(tr((attacker_name+"打出了暴击！！！\n").toStdString().c_str()));
                }

                //保存上一回合结束小精灵数值
                QString attacker_atk,attacker_dfs,attacker_hp,attacker_speed;
                QString opponent_atk,opponent_dfs,opponent_hp,opponent_speed;
                QString attacker_atk_p,attacker_dfs_p,attacker_hp_p,attacker_speed_p;
                QString opponent_atk_p,opponent_dfs_p,opponent_hp_p,opponent_speed_p;
                if(battleround==0)
                {
                    attacker_atk=ui->tablePokemon1->item(3,0)->text();
                    attacker_dfs=ui->tablePokemon1->item(4,0)->text();
                    attacker_hp=ui->tablePokemon1->item(5,0)->text().split('/')[0];
                    attacker_speed=ui->tablePokemon1->item(6,0)->text();
                    opponent_atk=ui->tablePokemon2->item(3,0)->text();
                    opponent_dfs=ui->tablePokemon2->item(4,0)->text();
                    opponent_hp=ui->tablePokemon2->item(5,0)->text().split('/')[0];
                    opponent_speed=ui->tablePokemon2->item(6,0)->text();
                }
                else
                {
                    attacker_atk=ui->tablePokemon2->item(3,0)->text();
                    attacker_dfs=ui->tablePokemon2->item(4,0)->text();
                    attacker_hp=ui->tablePokemon2->item(5,0)->text().split('/')[0];
                    attacker_speed=ui->tablePokemon2->item(6,0)->text();
                    opponent_atk=ui->tablePokemon1->item(3,0)->text();
                    opponent_dfs=ui->tablePokemon1->item(4,0)->text();
                    opponent_hp=ui->tablePokemon1->item(5,0)->text().split('/')[0];
                    opponent_speed=ui->tablePokemon1->item(6,0)->text();
                }

                //当前回合结束小精灵数值
                detail = infos[1].split(' ');
                attacker_atk_p = detail[3];
                attacker_dfs_p = detail[4];
                attacker_hp_p = detail[5];
                attacker_speed_p = detail[6];
                detail = infos[2].split(' ');
                opponent_atk_p = detail[3];
                opponent_dfs_p = detail[4];
                opponent_hp_p = detail[5];
                opponent_speed_p = detail[6];

                //处理pokemon1的数据
                if(battleround==0)
                    detail = infos[1].split(' ');
                else
                    detail = infos[2].split(' ');
                int battlehp=detail[5].toInt(),maxhp=detail[8].toInt();
                // 添加图片
                setPokemonImg(ui->labelPokemon1,detail[2]);

                QTableWidgetItem* t;
                for (int i=0;i<8;i++) {
                    if(i==5)
                        t = new QTableWidgetItem(detail[i]+'/'+detail[8]);
                    else
                        t = new QTableWidgetItem(detail[i]);
                    t->setFlags(t->flags()^Qt::ItemIsEnabled);
                    ui->tablePokemon1->setItem(i,0,t);
                }
                ui->progressBarPokemon1->setMaximum(maxhp);
                ui->progressBarPokemon1->setValue(battlehp);
                //处理pokemon2的数据
                if(battleround==0)
                    detail = infos[2].split(' ');
                else
                    detail = infos[1].split(' ');
                battlehp=detail[5].toInt(),maxhp=detail[8].toInt();
                // 添加图片
                setPokemonImg(ui->labelPokemon2,detail[2]);

                for (int i=0;i<8;i++) {
                    if(i==5)
                        t = new QTableWidgetItem(detail[i]+'/'+detail[8]);
                    else
                        t = new QTableWidgetItem(detail[i]);
                    t->setFlags(t->flags()^Qt::ItemIsEnabled);
                    ui->tablePokemon2->setItem(i,0,t);
                }
                ui->progressBarPokemon2->setMaximum(maxhp);
                ui->progressBarPokemon2->setValue(battlehp);

                //在textbrowser上添加信息

                //处理数值变化
                if(opponent_hp!=opponent_hp_p)
                {
                    ui->textBrowserFightInfo->append(tr((opponent_name+"的HP从"+opponent_hp+"变为"+opponent_hp_p+"\n").toStdString().c_str()));
                }
                if(opponent_atk!=opponent_atk_p)
                {
                    ui->textBrowserFightInfo->append(tr((opponent_name+"的ATK从"+opponent_atk+"变为"+opponent_atk_p+"\n").toStdString().c_str()));
                }
                if(opponent_dfs!=opponent_dfs_p)
                {
                    ui->textBrowserFightInfo->append(tr((opponent_name+"的DFS从"+opponent_dfs+"变为"+opponent_dfs_p+"\n").toStdString().c_str()));
                }
                if(opponent_speed!=opponent_speed_p)
                {
                    ui->textBrowserFightInfo->append(tr((opponent_name+"的SPEED从"+opponent_speed+"变为"+opponent_speed_p+"\n").toStdString().c_str()));
                }
                if(attacker_hp!=attacker_hp_p)
                {
                    ui->textBrowserFightInfo->append(tr((attacker_name+"的HP从"+attacker_hp+"变为"+attacker_hp_p+"\n").toStdString().c_str()));
                }
                if(attacker_atk!=attacker_atk_p)
                {
                    ui->textBrowserFightInfo->append(tr((attacker_name+"的ATK从"+attacker_atk+"变为"+attacker_atk_p+"\n").toStdString().c_str()));
                }
                if(attacker_dfs!=attacker_dfs_p)
                {
                    ui->textBrowserFightInfo->append(tr((attacker_name+"的DFS从"+attacker_dfs+"变为"+attacker_dfs_p+"\n").toStdString().c_str()));
                }
                if(attacker_speed!=attacker_speed_p)
                {
                    ui->textBrowserFightInfo->append(tr((attacker_name+"的SPEED从"+attacker_speed+"变为"+attacker_speed_p+"\n").toStdString().c_str()));
                }
                QString str = "continue";
                if(clientSocket->write(str.toLocal8Bit(),DEFAULT_BUFLEN)==-1)
                {
                    QMessageBox::warning(this,tr("战斗失败"),tr("服务器错误！"));
                    return;
                }
            }


        }
        break;
    case CNGPONAME:
        if(str == "Accept.\n")
        {
            qDebug()<<"修改名字成功";
            QMessageBox::information(this,tr("修改名字成功"),tr("修改名字成功！"));
        }
        else if(str == "服务器数据库错误")
        {
            qDebug()<<"服务器数据库错误";
            QMessageBox::warning(this,tr("修改名字失败"),tr("服务器数据库错误"));
        }
        changeState(POKEMONINFO);
        break;
    case CNGPSW:
        ui->pushButtonCngPswAdmit->setDisabled(false);
        if(str == "Accept.\n")
        {
            qDebug()<<"修改密码成功";
            ui->lineEditNewPsw->clear();
            ui->lineEditNewPsw2->clear();
            ui->lineEditOldPsw->clear();
            QMessageBox::information(this,tr("修改密码成功"),tr("修改密码成功！"));
            changeState(MAIN);
        }
        else if(str == "Wrong original password")
        {
            qDebug()<<"原密码错误";
            ui->lineEditNewPsw->clear();
            ui->lineEditNewPsw2->clear();
            ui->lineEditOldPsw->clear();
            QMessageBox::warning(this,tr("修改密码失败"),tr("原密码错误"));
        }
        else if(str == "服务器数据库错误")
        {
            qDebug()<<"服务器数据库错误";
            ui->lineEditNewPsw->clear();
            ui->lineEditNewPsw2->clear();
            ui->lineEditOldPsw->clear();
            QMessageBox::warning(this,tr("修改密码失败"),tr("服务器数据库错误"));
        }
        break;
    case USERLIST:
        ui->pushButtonUserList->setDisabled(false);
        if(str == "服务器数据库错误")
        {
            qDebug()<<"服务器数据库错误";
            QMessageBox::warning(this,tr("查看用户列表失败"),tr("服务器数据库错误"));
            changeState(MAIN);
        }
        else
        {
            qDebug()<<msg;
            auto players = msg.split('\n');

            // 设置格式
            ui->tableUserList->setWindowTitle(tr("用户列表"));
            ui->tableUserList->setColumnCount(4); //设置列数
            ui->tableUserList->setHorizontalHeaderLabels({tr("PLAYERID"), tr("USERNAME"),tr("STATUS"),tr("OPERATION")});
            ui->tableUserList->setRowCount(players.size()); //设置行数

            ui->tableUserList->verticalHeader()->hide();
            ui->tableUserList->horizontalHeader()->setStyleSheet("QHeaderView::section{background:#666666;color:white;}");
            ui->tableUserList->horizontalHeader()->setFont(QFont("Terminal", 10 ));
            QFont font = ui->tableUserList->horizontalHeader()->font(); //先获取字体
            font.setBold(true); //字体设置为粗体
            ui->tableUserList->horizontalHeader()->setFont(font); //设置每一列的标题字体为粗体
            ui->tableUserList->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); //宽度自适应

            // 设置属性
            ui->tableUserList->setEditTriggers(QAbstractItemView::NoEditTriggers);//Table只读

            // 添加表项
            int tableRowIndex = 0;
            // 添加一个系统用户
            QTableWidgetItem* t = new QTableWidgetItem("0");
            t->setFlags(t->flags()^Qt::ItemIsEnabled);
            ui->tableUserList->setItem(tableRowIndex,0,t);
            // username
            t = new QTableWidgetItem(tr("系统"));
            t->setFlags(t->flags()^Qt::ItemIsEnabled);
            ui->tableUserList->setItem(tableRowIndex,1,t);
            // always online
            t = new QTableWidgetItem(tr("在线"));
            t->setFlags(t->flags()^Qt::ItemIsEnabled);
            ui->tableUserList->setItem(tableRowIndex,2,t);
            // btn
            QPushButton* button = new QPushButton(tr("查看小精灵"),this);
            ui->tableUserList->setCellWidget(tableRowIndex,3,button);

            connect(button,&QPushButton::clicked,this,
                    [this]
                    {
                        showBadge=false;
                        getPokemonList(0);
                    });
            ++tableRowIndex;
            for (int i=0;i<players.size()-1;i++) {
                auto detail = players[i].split(' ');
                // detail[0]--id detail[1]--username detail[2]--online
                // id
                t = new QTableWidgetItem(detail[0]);
                t->setFlags(t->flags()^Qt::ItemIsEnabled);
                ui->tableUserList->setItem(tableRowIndex,0,t);
                // username
                t = new QTableWidgetItem(detail[1]);
                t->setFlags(t->flags()^Qt::ItemIsEnabled);
                ui->tableUserList->setItem(tableRowIndex,1,t);
                // online
                if(detail[2].toInt()==0)
                    t = new QTableWidgetItem(tr("离线"));
                else
                    t = new QTableWidgetItem(tr("在线"));
                t->setFlags(t->flags()^Qt::ItemIsEnabled);
                ui->tableUserList->setItem(tableRowIndex,2,t);
                // btn
                QPushButton* button = new QPushButton(tr("查看小精灵"),this);
                ui->tableUserList->setCellWidget(tableRowIndex,3,button);

                connect(button,&QPushButton::clicked,this,
                        [this,detail]
                        {
                            showBadge=true;
                            int playerID = detail[0].toInt();
                            getPokemonList(playerID);
                        });
                ++tableRowIndex;
            }
            changeState(USERLIST);
        }
        break;
    case POKEMONLIST:
        ui->pushButtonUserList->setDisabled(false);
        if(str == "服务器数据库错误")
        {
            qDebug()<<"服务器数据库错误";
            QMessageBox::warning(this,tr("查看用户列表失败"),tr("服务器数据库错误"));
            changeState(MAIN);
        }
        else if(str == "无效的PlayerID")
        {
            qDebug()<<"无效的PlayerID";
            QMessageBox::warning(this,tr("查看用户列表失败"),tr("该用户不存在"));
            changeState(MAIN);
        }
        else
        {         
            qDebug()<<msg;
            auto pokemons = msg.split('\n');

            // 设置格式
            ui->tablePokemonList->setWindowTitle(tr("小精灵列表"));
            ui->tablePokemonList->setColumnCount(7); //设置列数
            ui->tablePokemonList->setHorizontalHeaderLabels({tr("POKEMONID"), tr("PLAYERID"),tr("NAME"),tr("RACE"),"LV",tr("DETAIL"),tr("GO")});
            ui->tablePokemonList->setRowCount(pokemons.size()-2); //设置行数
            ui->tablePokemonList->horizontalHeader()->setStyleSheet("QHeaderView::section{background:#666666;color:white;}");
            ui->tablePokemonList->horizontalHeader()->setFont(QFont("Terminal", 10 ));

            ui->tablePokemonList->verticalHeader()->hide();
            QFont font = ui->tablePokemonList->horizontalHeader()->font(); //先获取字体
            font.setBold(true); //字体设置为粗体
            ui->tablePokemonList->horizontalHeader()->setFont(font); //设置每一列的标题字体为粗体
            ui->tablePokemonList->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); //宽度自适应
            ui->tablePokemonList->horizontalHeader()->setSectionResizeMode(1,QHeaderView::ResizeToContents);
            ui->tablePokemonList->horizontalHeader()->setSectionResizeMode(0,QHeaderView::ResizeToContents);
            ui->tablePokemonList->horizontalHeader()->setSectionResizeMode(4,QHeaderView::ResizeToContents);
            ui->tablePokemonList->horizontalHeader()->setSectionResizeMode(5,QHeaderView::ResizeToContents);
            ui->tablePokemonList->horizontalHeader()->setSectionResizeMode(6,QHeaderView::ResizeToContents);

            // 设置属性
            ui->tablePokemonList->setEditTriggers(QAbstractItemView::NoEditTriggers);//Table只读
            // 胜率
            double win_round,total_round;
            if(showBadge)
            {
                auto detail = pokemons[0].split(' ');
                win_round=detail[0].toInt();
                total_round=detail[1].toInt();
                double win_rate;
                if(total_round==0)
                    win_rate=0;
                else
                    win_rate = win_round/total_round;
                //将胜率那一栏设置为显示
                ui->labelWinRate->show();
                ui->labelWinRound->show();
                ui->labelTotalRound->show();
                ui->labelWinRound->setText("WIN ROUND:"+detail[0]);
                ui->labelTotalRound->setText("TOTAL ROUND:"+detail[1]);
                ui->labelWinRate->setText("WINNING RATE:"+QString::number(win_rate*100,'f',2)+'%');
            }
            else
            {
                //将胜率那一栏设置为不显示
                ui->labelWinRate->hide();
                ui->labelWinRound->hide();
                ui->labelTotalRound->hide();
            }
            // 徽章计数
            cntPokemon=0,cnt15=0;
            // 添加表项
            int tableRowIndex = 0;
            for (int i=1;i<pokemons.size()-1;i++) {

                auto detail = pokemons[i].split(' ');
                cntPokemon++;
                if(detail[5].toInt()>15)
                    cnt15++;
                QTableWidgetItem* t ;

                QString race = detail[3];
                if(race=="2")
                {
                    race="Onix";
                }
                else if(race=="1")
                {
                    race="Snorlax";
                }
                else if(race=="3")
                {
                    race="Pidgey";
                }
                else if(race=="0")
                {
                    race="Primeape";
                }
                detail[3]=race;

                for (int i=0;i<6;i++) {
                    t= new QTableWidgetItem(detail[i]);
                    t->setFlags(t->flags()^Qt::ItemIsEnabled);
                    ui->tablePokemonList->setItem(tableRowIndex,i,t);
                }

                QPushButton* button1 = new QPushButton(tr("详细信息"),this);
                button1->setFont(QFont("Terminal",7));
                button1->setStyleSheet("color:white");
                ui->tablePokemonList->setCellWidget(tableRowIndex,5,button1);

                connect(button1,&QPushButton::clicked,this,
                        [this,detail]
                        {
                            int pokemonID = detail[0].toInt();
                            getPokemonInfo(pokemonID);
                        });
                QPushButton* button2;
                if(fightcontroller.mode!=NOFIGHT)
                {
                    if(detail[1].toInt()==playerID)
                        button2 = new QPushButton(tr("就决定是你了！"),this);
                    else
                        button2 = new QPushButton(tr("和我决斗吧！"),this);

                }
                else
                    button2 = new QPushButton(tr("无对战"),this);
                button2->setFont(QFont("Terminal",7));
                button2->setStyleSheet("color:white");
                ui->tablePokemonList->setCellWidget(tableRowIndex,6,button2);
                if(fightcontroller.mode==NOFIGHT)
                    button2->setDisabled(true);
                connect(button2,&QPushButton::clicked,this,
                        [this,detail]
                        {
                            //选择自己的小精灵
                            if(detail[1].toInt()==playerID)
                            {
                                fightcontroller.myPokemonid=detail[0].toInt();
                                QMessageBox::information(this,tr("小精灵已选定"),tr("您的出战小精灵已准备完毕，接下来请选择您的对手！"));
                                //升级赛可以和任意小精灵对战
                                if(fightcontroller.mode==LEVELUPMODE)
                                    getPokemonList(8888);
                                //决斗赛只能和系统的小精灵对战
                                else
                                    getPokemonList(0);
                            }
                            //选择对手的小精灵
                            else
                            {
                                fightcontroller.opponentPokemonid=detail[0].toInt();
                                QMessageBox::information(this,tr("小精灵已选定"),tr("您的对手已选择完成，战斗开始！"));
                                changeState(FIGHT);
                            }

                        });
                ++tableRowIndex;
            }

            // 展示徽章和胜率
            // 宠物个数徽章（金银铜）30-金 20-银 10-铜 无
            // 高级宠物徽章（金银铜）15-金 10-银 5-铜 无
            if(showBadge)
            {

                if(cntPokemon<10)
                {
                    ui->labelBadge1->setPixmap(QPixmap(":/images/images/badge1_no.png"));
                    ui->labelBadge1->setToolTip(tr("宠物个数小于10，无法获得徽章"));
                }
                else if(cntPokemon <20)
                {
                    ui->labelBadge1->setPixmap(QPixmap(":/images/images/badge1_choppery.png"));
                    ui->labelBadge1->setToolTip(tr("宠物个数大于等于10，获得宠物个数徽章(铜)"));
                }
                else if(cntPokemon <30)
                {
                    ui->labelBadge1->setPixmap(QPixmap(":/images/images/badge1_sliver.png"));
                    ui->labelBadge1->setToolTip(tr("宠物个数大于等于20，获得宠物个数徽章(银)"));
                }
                else
                {
                    ui->labelBadge1->setPixmap(QPixmap(":/images/images/badge1_gold.png"));
                    ui->labelBadge1->setToolTip(tr("宠物个数大于等于30，获得宠物个数徽章(金)"));
                }
                if(cnt15<5)
                {
                    ui->labelBadge2->setPixmap(QPixmap(":/images/images/badge2_no.png"));
                    ui->labelBadge2->setToolTip(tr("满级宠物个数小于5，无法获得高级宠物徽章"));
                }
                else if(cnt15 <10)
                {
                    ui->labelBadge2->setPixmap(QPixmap(":/images/images/badge2_choppery.png"));
                    ui->labelBadge2->setToolTip(tr("满级宠物个数大于等于5，获得高级宠物徽章(铜)"));
                }
                else if(cnt15 <15)
                {
                    ui->labelBadge2->setPixmap(QPixmap(":/images/images/badge2_sliver.png"));
                    ui->labelBadge2->setToolTip(tr("满级宠物个数大于等于10，获得高级宠物徽章(银)"));
                }
                else
                {
                    ui->labelBadge2->setPixmap(QPixmap(":/images/images/badge2_gold.png"));
                    ui->labelBadge2->setToolTip(tr("满级宠物个数大于等于15，获得高级宠物徽章(金)"));
                }
                ui->labelBadge1->setScaledContents(true);
                ui->labelBadge1->show();
                ui->labelBadge2->setScaledContents(true);
                ui->labelBadge2->show();
            }
            showBadge=false;
            changeState(POKEMONLIST);
        }
        break;
    case POKEMONINFO:
        qDebug()<<msg;
        if(str == "服务器数据库错误")
        {
            qDebug()<<"服务器数据库错误";
            QMessageBox::warning(this,tr("查看小精灵信息失败"),tr("服务器数据库错误"));
            changeState(MAIN);
        }
        else if(str == "无效的PokemonID")
        {
            qDebug()<<"无效的PokemonID";
            QMessageBox::warning(this,tr("查看小精灵信息失败"),tr("该小精灵不存在"));
            changeState(MAIN);
        }
        else
        {
            qDebug()<<msg;
            auto detail = msg.split(' ');
            // 判断是否是自己的Pokemon
            // detail[8]--userid
            bool myPokemon = detail[8].toInt()==playerID?true:false;
            // 设置格式
            ui->tablePokemonDetail->setWindowTitle(tr("小精灵详细信息"));
            ui->tablePokemonDetail->setColumnCount(1); //设置列数
            ui->tablePokemonDetail->setRowCount(8); //设置行数
            ui->tablePokemonDetail->setVerticalHeaderLabels({"NAME","RACE","ATK","DFS","HP","SPEED","LV","EP"});
            ui->tablePokemonDetail->verticalHeader()->setStyleSheet("QHeaderView::section{background:#666666;}");
            ui->tablePokemonDetail->verticalHeader()->setFont(QFont("Terminal", 10 ));
            ui->tablePokemonDetail->horizontalHeader()->hide();
            QFont font = ui->tablePokemonDetail->verticalHeader()->font(); //先获取字体
            font.setBold(true); //字体设置为粗体
            ui->tablePokemonDetail->verticalHeader()->setFont(font); //设置每一列的标题字体为粗体
            ui->tablePokemonDetail->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); //宽度自适应
            ui->tablePokemonDetail->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch); //高度自适应
            ui->tablePokemonDetail->resize(400,500);

            // 设置属性
            ui->tablePokemonDetail->setEditTriggers(QAbstractItemView::DoubleClicked);//Table只读
            // 添加图片
            setPokemonImg(ui->labelImg,detail[1]);
            // 添加表项
            QTableWidgetItem* t;
            // 修改名字
            t = new QTableWidgetItem(detail[0]);
            // 是自己的Pokemon才能修改名字
            if(myPokemon)
            {
                t->setToolTip(tr("双击以更改精灵名称"));
            }
            else
            {
                t->setFlags(t->flags() ^ Qt::ItemIsEnabled);
                t->setBackgroundColor(QColor("#eff0f1"));
            }
            t->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
            ui->tablePokemonDetail->setItem(0,0,t);

            for (int i=1;i<detail.size()-1;i++) {
                t = new QTableWidgetItem(detail[i]);
                t->setFlags(t->flags()^Qt::ItemIsEnabled);
                t->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                ui->tablePokemonDetail->setItem(i,0,t);
            }
        }
        break;
    default:
        break;
    }
}

void PokemonWidget::changePokemonMaster(int targetpokemonID,int targetplayerID){
    qDebug()<<"玩家"<< targetplayerID<<"成为小精灵"<<targetpokemonID<<"的新主人！";
    QString str = "changePokemonMaster "+QString::number(targetpokemonID)+" "+QString::number(targetplayerID);
    if(clientSocket->write(str.toLocal8Bit(),DEFAULT_BUFLEN)==-1)
    {
        QMessageBox::warning(this,tr("小精灵变更主人失败"),tr("服务器错误！"));
        return;
    }
}

void PokemonWidget::getPokemonList(int playerID)
{
    qDebug()<<"查看玩家"<< playerID<<"的小精灵信息";
    QString str = "getPokemonList "+QString::number(playerID);
    ui->pushButtonPoList->setDisabled(true);
    if(clientSocket->write(str.toLocal8Bit(),DEFAULT_BUFLEN)==-1)
    {
        ui->pushButtonPoList->setDisabled(false);
        QMessageBox::warning(this,tr("查看小精灵列表失败"),tr("服务器错误！"));
        return;
    }
    changeState(POKEMONLIST);
}

void PokemonWidget::getPokemonInfo(int pokemonID)
{
    this->pokemonID=pokemonID;
    qDebug()<<"查看小精灵"<< pokemonID<<"的小精灵信息";
    changeState(POKEMONINFO);
    QString str = "getPokemonInfo "+QString::number(pokemonID);
    if(clientSocket->write(str.toLocal8Bit(),DEFAULT_BUFLEN)==-1)
    {
        QMessageBox::warning(this,tr("查看小精灵信息失败"),tr("服务器错误！"));
        return;
    }

}

void PokemonWidget::login_slot(int endpointport,int playerid)
{
    port = endpointport;
    clientSocket->connectToHost("127.0.0.1",endpointport);
    playerID=playerid;
    // 成功登录，成功连接endpoint
    // 跳转到主界面
    ui->stackedWidget->setCurrentIndex(1);
    changeState(MAIN);
}

void PokemonWidget::on_buttonLogin_clicked()
{
    login->show();
}

void PokemonWidget::on_buttonRegister_clicked()
{
    reg->show();
}

void PokemonWidget::on_buttonQuit_clicked()
{
    this->close();
}

void PokemonWidget::on_pushButtonLouout_clicked()
{
    QString sendStr = "logout";

    if(clientSocket->write(sendStr.toLocal8Bit(),DEFAULT_BUFLEN)==-1)
    {
        QMessageBox::warning(this,tr("登出失败"),tr("服务器错误！"));
        return;
    }
    QMessageBox::information(this,tr("登出成功"),tr("登出成功"));
    qDebug()<<"登出成功";
    clientSocket->disconnectFromHost();
    changeState(LOGIN);
}

void PokemonWidget::on_pushButtonChgPsw_clicked()
{
    changeState(CNGPSW);
}

void PokemonWidget::on_pushButtonCngPswBack_clicked()
{
    ui->lineEditNewPsw->clear();
    ui->lineEditNewPsw2->clear();
    ui->lineEditOldPsw->clear();
    ui->pushButtonCngPswAdmit->setDisabled(false);
    changeState(MAIN);
}

void PokemonWidget::on_pushButtonCngPswAdmit_clicked()
{
    if(ui->lineEditNewPsw->text()!=ui->lineEditNewPsw2->text())
    {
        QMessageBox::warning(this, tr("修改密码错误"), tr("两次输入密码格式不一样"));
        ui->lineEditNewPsw->clear();
        ui->lineEditNewPsw2->clear();
        return;
    }
    if (!strfunc.isValidPassword(ui->lineEditOldPsw->text()))
    {
        QMessageBox::warning(this, tr("错误"), tr("旧密码格式错误"));
        ui->lineEditOldPsw->clear();
    }
    else if (!strfunc.isValidPassword(ui->lineEditNewPsw->text()))
    {
        QMessageBox::warning(this, tr("错误"), tr("新密码格式错误"));
        ui->lineEditNewPsw->clear();
        ui->lineEditNewPsw2->clear();
    }
    else
    {
        QString str = "changePassword ";
        str += QString::number(playerID);
        str += ' ';
        str += ui->lineEditOldPsw->text();
        str += ' ';
        str += ui->lineEditNewPsw->text();
        ui->pushButtonCngPswAdmit->setDisabled(true);
        if(clientSocket->write(str.toLocal8Bit(),DEFAULT_BUFLEN)==-1)
        {
            QMessageBox::warning(this,tr("修改密码失败"),tr("服务器错误！"));
            ui->pushButtonCngPswAdmit->setDisabled(false);
            return;
        }
    }
}

void PokemonWidget::on_pushButtonUserList_clicked()
{
    QString str = "getUserList";
    ui->pushButtonUserList->setDisabled(true);
    if(clientSocket->write(str.toLocal8Bit(),DEFAULT_BUFLEN)==-1)
    {
        ui->pushButtonUserList->setDisabled(false);
        QMessageBox::warning(this,tr("查看用户列表失败"),tr("服务器错误！"));
        return;
    }
    changeState(USERLIST);
}

void PokemonWidget::on_pushButtonUserListBack_clicked()
{
    if(fightcontroller.mode!=NOFIGHT)
    {
        fightcontroller.mode=NOFIGHT;
    }
    ui->pushButtonUserList->setDisabled(false);
    changeState(MAIN);
    ui->tableUserList->clear();
}

void PokemonWidget::on_pushButtonPoList_clicked()
{
    showBadge=true;
    getPokemonList(playerID);
    changeState(POKEMONLIST);
}

void PokemonWidget::on_pushButtonPoListBack_clicked()
{
    ui->pushButtonPoList->setDisabled(false);
    changeState(MAIN);
    ui->tablePokemonList->clear();
    fightcontroller.mode=NOFIGHT;
}

void PokemonWidget::on_pushButtonPoInfoBack_clicked()
{
    //changeState(POKEMONLIST);
    ui->pushButtonPoList->click();
    ui->pushButtonPoList->setDisabled(false);
}

void PokemonWidget::on_pushButtonLevelUp_clicked()
{
    showBadge=false;
    fightcontroller.mode=LEVELUPMODE;
    getPokemonList(playerID);
}

void PokemonWidget::on_pushButtonBackFromBattle_clicked()
{
    changeState(MAIN);
    ui->textBrowserFightInfo->clear();
}

void PokemonWidget::on_pushButtonDuel_clicked()
{
    showBadge=false;
    fightcontroller.mode=DUELMODE;
    getPokemonList(playerID);
}

void PokemonWidget::setPokemonImg(QLabel* imgLabel,QString &race)
{
    if(race=="2")
    {
        race="Onix";
        imgLabel->setPixmap(QPixmap(":/images/images/Onix.png"));
    }
    else if(race=="1")
    {
        race="Snorlax";
        imgLabel->setPixmap(QPixmap(":/images/images/Snorlax.png"));
    }
    else if(race=="3")
    {
        race="Pidgey";
        imgLabel->setPixmap(QPixmap(":/images/images/Pidgey.png"));
    }
    else if(race=="0")
    {
        race="Primeape";
        imgLabel->setPixmap(QPixmap(":/images/images/Primeape.png"));
    }
    imgLabel->setScaledContents(true);
    imgLabel->show();
}

void PokemonWidget::on_pushButtonLosePokemon1_clicked()
{
    changePokemonMaster(ui->tableWidgetLosePokemon1->item(0,0)->text().toInt(),0);
    QMessageBox::information(this,tr("小精灵已给出"),tr("您的小精灵被系统夺走啦，你可以通过对决战将其赢回来！"));
    changeState(MAIN);
    ui->tableWidgetLosePokemon1->clear();
    ui->tableWidgetLosePokemon2->clear();
    ui->tableWidgetLosePokemon3->clear();
    ui->labelLosePokemon1->clear();
    ui->labelLosePokemon2->clear();
    ui->labelLosePokemon3->clear();
}

void PokemonWidget::on_pushButtonLosePokemon2_clicked()
{
    changePokemonMaster(ui->tableWidgetLosePokemon2->item(0,0)->text().toInt(),0);
    QMessageBox::information(this,tr("小精灵已给出"),tr("您的小精灵被系统夺走啦，你可以通过对决战将其赢回来！"));
    changeState(MAIN);
    ui->tableWidgetLosePokemon1->clear();
    ui->tableWidgetLosePokemon2->clear();
    ui->tableWidgetLosePokemon3->clear();
    ui->labelLosePokemon1->clear();
    ui->labelLosePokemon2->clear();
    ui->labelLosePokemon3->clear();
}

void PokemonWidget::on_pushButtonLosePokemon3_clicked()
{
    changePokemonMaster(ui->tableWidgetLosePokemon3->item(0,0)->text().toInt(),0);
    QMessageBox::information(this,tr("小精灵已给出"),tr("您的小精灵被系统夺走啦，你可以通过对决战将其赢回来！"));
    changeState(MAIN);
    ui->tableWidgetLosePokemon1->clear();
    ui->tableWidgetLosePokemon2->clear();
    ui->tableWidgetLosePokemon3->clear();
    ui->labelLosePokemon1->clear();
    ui->labelLosePokemon2->clear();
    ui->labelLosePokemon3->clear();
}

void PokemonWidget::mousePressEvent(QMouseEvent *e)
{
    last=e->globalPos();
}
void PokemonWidget::mouseMoveEvent(QMouseEvent *e)
{
    int dx = e->globalX() - last.x();
        int dy = e->globalY() - last.y();
        last = e->globalPos();
        move(x()+dx, y()+dy);
}
void PokemonWidget::mouseReleaseEvent(QMouseEvent *e)
{
    int dx = e->globalX() - last.x();
    int dy = e->globalY() - last.y();
    move(x()+dx, y()+dy);
}

