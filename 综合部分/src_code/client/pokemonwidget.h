#pragma execution_character_set("utf-8")
#ifndef POKEMONWIDGET_H
#define POKEMONWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QLabel>
#include <QDir>
#include <QTcpSocket>
#include <qhostaddress.h>
#include <QTextCodec>
#include <QTableWidget>
#include <iostream>
#include <QMediaPlaylist>
#include <QMediaPlayer>



// 需要用到的一些字符串工具函数
#include "strfunction.h"

// 子窗口
#include "loginwidget.h"
#include "registerwidget.h"


#define DEFAULT_BUFLEN 1024

enum State{MAIN,LOGIN,POKEMONLIST,USERLIST,LOGOUT,CNGPSW,POKEMONINFO,CNGPONAME,FIGHT,LOSEPOKEMON};
enum FightState{NOFIGHT,LEVELUPMODE,DUELMODE};
struct FightController
{
    int myPokemonid;
    int opponentPokemonid;
    FightState mode;
    bool initFight;
};

QT_BEGIN_NAMESPACE
namespace Ui { class PokemonWidget; }
QT_END_NAMESPACE

class PokemonWidget : public QWidget
{
    Q_OBJECT

public:
    void changeState(State s);
    void dealServerMsg();
    PokemonWidget(QWidget *parent = nullptr);
    ~PokemonWidget();

    void getPokemonList(int playerID);
    void getPokemonInfo(int pokemonID);
    void changePokemonMaster(int pokemonID,int playerID);

    void setPokemonImg(QLabel* imgLabel,QString &race);

    void initStyles();

    strFunction strfunc;
protected:
    void paintEvent(QPaintEvent *);

private slots:
    void on_buttonLogin_clicked();

    void on_buttonRegister_clicked();

    void on_buttonQuit_clicked();

    void login_slot(int,int);

    void on_pushButtonChgPsw_clicked();

    void on_pushButtonLouout_clicked();

    void on_pushButtonCngPswAdmit_clicked();

    void on_pushButtonCngPswBack_clicked();

    void on_pushButtonUserList_clicked();

    void on_pushButtonUserListBack_clicked();

    void on_pushButtonPoList_clicked();

    void on_pushButtonPoListBack_clicked();

    void on_pushButtonPoInfoBack_clicked();

    void on_pushButtonLevelUp_clicked();


    void on_pushButtonBackFromBattle_clicked();

    void on_pushButtonDuel_clicked();

    void on_pushButtonLosePokemon1_clicked();
    void on_pushButtonLosePokemon2_clicked();
    void on_pushButtonLosePokemon3_clicked();

private:
    Ui::PokemonWidget *ui;
    loginWidget *login;
    registerWidget *reg;

    QSqlQuery query;
    QSqlDatabase db;
    QTcpSocket *clientSocket; //通信套接字

    QMediaPlayer *mediaPlayer;

    State state;
    int port;
    int playerID;
    int pokemonID; //present Pokemon

    bool showBadge; //只有展示玩家信息才展示徽章和胜率


    FightController fightcontroller;
};
#endif // POKEMONWIDGET_H
