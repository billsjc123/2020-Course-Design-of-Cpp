/********************************************************************************
** Form generated from reading UI file 'pokemonwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_POKEMONWIDGET_H
#define UI_POKEMONWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PokemonWidget
{
public:
    QStackedWidget *stackedWidget;
    QWidget *LoginPage;
    QWidget *layoutWidget;
    QVBoxLayout *LoginLayout;
    QPushButton *buttonLogin;
    QSpacerItem *verticalSpacer;
    QPushButton *buttonRegister;
    QSpacerItem *verticalSpacer_2;
    QPushButton *buttonQuit;
    QWidget *MainPage;
    QWidget *layoutWidget1;
    QVBoxLayout *MainLayout;
    QSpacerItem *verticalSpacer_3;
    QPushButton *pushButtonLevelUp;
    QSpacerItem *verticalSpacer_6;
    QPushButton *pushButtonDuel;
    QSpacerItem *verticalSpacer_7;
    QPushButton *pushButtonUserList;
    QSpacerItem *verticalSpacer_4;
    QPushButton *pushButtonPoList;
    QSpacerItem *verticalSpacer_5;
    QPushButton *pushButtonChgPsw;
    QPushButton *pushButtonLouout;
    QWidget *cngPswPage;
    QWidget *layoutWidget2;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *labelNewPsw2;
    QSpacerItem *horizontalSpacer_4;
    QLineEdit *lineEditNewPsw2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *labelNewPsw;
    QSpacerItem *horizontalSpacer_3;
    QLineEdit *lineEditNewPsw;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *pushButtonCngPswAdmit;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButtonCngPswBack;
    QHBoxLayout *horizontalLayout_3;
    QLabel *labelOldPsw;
    QSpacerItem *horizontalSpacer_2;
    QLineEdit *lineEditOldPsw;
    QWidget *UserListpage;
    QTableWidget *tableUserList;
    QPushButton *pushButtonUserListBack;
    QWidget *PokemonListPage;
    QPushButton *pushButtonPoListBack;
    QLabel *labelBadge1;
    QLabel *labelBadge2;
    QLabel *labelBadge2Tip;
    QLabel *labelBadge1Tip;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *winroundLayout;
    QLabel *labelWinRound;
    QLabel *labelTotalRound;
    QLabel *labelWinRate;
    QTableWidget *tablePokemonList;
    QWidget *PokemonInfoPage;
    QTableWidget *tablePokemonDetail;
    QLabel *labelImg;
    QWidget *layoutWidget3;
    QVBoxLayout *verticalLayout_2;
    QPushButton *pushButtonChgName;
    QPushButton *pushButtonPoInfoBack;
    QWidget *LevelUpFightPage;
    QTextBrowser *textBrowserFightInfo;
    QLabel *labelPokemon1;
    QTableWidget *tablePokemon1;
    QTableWidget *tablePokemon2;
    QLabel *labelPokemon2;
    QProgressBar *progressBarPokemon1;
    QProgressBar *progressBarPokemon2;
    QPushButton *pushButtonBackFromBattle;
    QWidget *LosePokemonPage;
    QLabel *labelLosePokemon3;
    QLabel *labelLosePokemon1;
    QLabel *labelLosePokemon2;
    QPushButton *pushButtonLosePokemon2;
    QPushButton *pushButtonLosePokemon3;
    QPushButton *pushButtonLosePokemon1;
    QWidget *layoutWidget4;
    QHBoxLayout *horizontalLayout_5;
    QTableWidget *tableWidgetLosePokemon1;
    QSpacerItem *horizontalSpacer_5;
    QTableWidget *tableWidgetLosePokemon2;
    QSpacerItem *horizontalSpacer_6;
    QTableWidget *tableWidgetLosePokemon3;

    void setupUi(QWidget *PokemonWidget)
    {
        if (PokemonWidget->objectName().isEmpty())
            PokemonWidget->setObjectName(QStringLiteral("PokemonWidget"));
        PokemonWidget->resize(1226, 755);
        QFont font;
        font.setFamily(QStringLiteral("Terminal"));
        font.setBold(true);
        font.setWeight(75);
        PokemonWidget->setFont(font);
        stackedWidget = new QStackedWidget(PokemonWidget);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        stackedWidget->setGeometry(QRect(-20, 0, 1251, 781));
        stackedWidget->setStyleSheet(QStringLiteral(""));
        LoginPage = new QWidget();
        LoginPage->setObjectName(QStringLiteral("LoginPage"));
        layoutWidget = new QWidget(LoginPage);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(800, 270, 321, 341));
        LoginLayout = new QVBoxLayout(layoutWidget);
        LoginLayout->setObjectName(QStringLiteral("LoginLayout"));
        LoginLayout->setContentsMargins(0, 0, 0, 0);
        buttonLogin = new QPushButton(layoutWidget);
        buttonLogin->setObjectName(QStringLiteral("buttonLogin"));
        buttonLogin->setMinimumSize(QSize(0, 80));
        QFont font1;
        font1.setFamily(QStringLiteral("Terminal"));
        font1.setPointSize(30);
        font1.setBold(true);
        font1.setWeight(75);
        buttonLogin->setFont(font1);
        buttonLogin->setStyleSheet(QLatin1String("\n"
"QPushButton#buttonLogin\n"
"{  \n"
"	border-radius:5px;\n"
"	color:white\n"
"} \n"
"QPushButton#buttonLogin:hover\n"
"{ background-color:#666666;\n"
"\n"
"border-radius:5px;\n"
"color:white;\n"
"}\n"
"QPushButton#buttonLogin:hover:pressed\n"
"{\n"
"background-color:rgb(85,170,255); \n"
"border:2px solid #3C80B1;\n"
"border-radius:5px;\n"
"color:white;\n"
"}\n"
""));

        LoginLayout->addWidget(buttonLogin);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        LoginLayout->addItem(verticalSpacer);

        buttonRegister = new QPushButton(layoutWidget);
        buttonRegister->setObjectName(QStringLiteral("buttonRegister"));
        buttonRegister->setMinimumSize(QSize(0, 80));
        QFont font2;
        font2.setFamily(QStringLiteral("Terminal"));
        font2.setPointSize(19);
        font2.setBold(true);
        font2.setWeight(75);
        buttonRegister->setFont(font2);
        buttonRegister->setStyleSheet(QLatin1String("QPushButton#buttonRegister\n"
"{  \n"
"\n"
"\n"
"	border-radius:5px;\n"
"	color:white\n"
"} \n"
"QPushButton#buttonRegister:hover\n"
"{\n"
" background-color:#666666;\n"
"\n"
"border-radius:5px;\n"
"color:white;\n"
"}\n"
"QPushButton#buttonRegister:hover:pressed\n"
"{\n"
"background-color:rgb(85,170,255); \n"
"border:2px solid #3C80B1;\n"
"border-radius:5px;\n"
"color:white;\n"
"}"));

        LoginLayout->addWidget(buttonRegister);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        LoginLayout->addItem(verticalSpacer_2);

        buttonQuit = new QPushButton(layoutWidget);
        buttonQuit->setObjectName(QStringLiteral("buttonQuit"));
        buttonQuit->setMinimumSize(QSize(0, 80));
        buttonQuit->setFont(font2);
        buttonQuit->setStyleSheet(QLatin1String("QPushButton#buttonQuit\n"
"{  \n"
"	border-radius:5px;\n"
"	color:white\n"
"} \n"
"QPushButton#buttonQuit:hover\n"
"{\n"
"background-color:#666666;\n"
"\n"
"border-radius:5px;\n"
"color:white;\n"
"}\n"
"QPushButton#buttonQuit:hover:pressed\n"
"{\n"
"background-color:rgb(85,170,255); \n"
"border:2px solid #3C80B1;\n"
"border-radius:5px;\n"
"color:white;\n"
"}"));

        LoginLayout->addWidget(buttonQuit);

        stackedWidget->addWidget(LoginPage);
        MainPage = new QWidget();
        MainPage->setObjectName(QStringLiteral("MainPage"));
        layoutWidget1 = new QWidget(MainPage);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(750, 130, 341, 542));
        MainLayout = new QVBoxLayout(layoutWidget1);
        MainLayout->setObjectName(QStringLiteral("MainLayout"));
        MainLayout->setContentsMargins(0, 0, 0, 0);
        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        MainLayout->addItem(verticalSpacer_3);

        pushButtonLevelUp = new QPushButton(layoutWidget1);
        pushButtonLevelUp->setObjectName(QStringLiteral("pushButtonLevelUp"));
        pushButtonLevelUp->setMinimumSize(QSize(0, 80));
        QFont font3;
        font3.setFamily(QStringLiteral("Terminal"));
        font3.setPointSize(12);
        font3.setBold(true);
        font3.setWeight(75);
        pushButtonLevelUp->setFont(font3);
        pushButtonLevelUp->setStyleSheet(QLatin1String("QPushButton#pushButtonLevelUp\n"
"{\n"
"    color:white;\n"
"\n"
"    border-radius:5px;\n"
"}\n"
" \n"
"QPushButton#pushButtonLevelUp:hover\n"
"{\n"
"    color:white;\n"
"    background-color:#666666;\n"
"}\n"
" \n"
"QPushButton#pushButtonLevelUp:pressed\n"
"{\n"
"    color:white;\n"
"    background-color:rgb(14 , 135 , 228);\n"
"    padding-left:3px;\n"
"    padding-top:3px;\n"
"}\n"
""));

        MainLayout->addWidget(pushButtonLevelUp);

        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        MainLayout->addItem(verticalSpacer_6);

        pushButtonDuel = new QPushButton(layoutWidget1);
        pushButtonDuel->setObjectName(QStringLiteral("pushButtonDuel"));
        pushButtonDuel->setMinimumSize(QSize(0, 80));
        QFont font4;
        font4.setFamily(QStringLiteral("Terminal"));
        font4.setPointSize(15);
        font4.setBold(true);
        font4.setWeight(75);
        pushButtonDuel->setFont(font4);
        pushButtonDuel->setStyleSheet(QLatin1String("QPushButton#pushButtonDuel\n"
"{\n"
"    color:white;\n"
"\n"
"    border-radius:5px;\n"
"}\n"
" \n"
"QPushButton#pushButtonDuel:hover\n"
"{\n"
"	background-color:#666666;\n"
"    color:white;\n"
"    \n"
"}\n"
" \n"
"QPushButton#pushButtonDuel:pressed\n"
"{\n"
"    color:white;\n"
"    background-color:rgb(14 , 135 , 228);\n"
"    padding-left:3px;\n"
"    padding-top:3px;\n"
"}\n"
""));

        MainLayout->addWidget(pushButtonDuel);

        verticalSpacer_7 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        MainLayout->addItem(verticalSpacer_7);

        pushButtonUserList = new QPushButton(layoutWidget1);
        pushButtonUserList->setObjectName(QStringLiteral("pushButtonUserList"));
        pushButtonUserList->setMinimumSize(QSize(0, 80));
        pushButtonUserList->setFont(font3);
        pushButtonUserList->setStyleSheet(QLatin1String("QPushButton#pushButtonUserList\n"
"{\n"
"    color:white;\n"
"\n"
"    border-radius:5px;\n"
"}\n"
" \n"
"QPushButton#pushButtonUserList:hover\n"
"{\n"
"    color:white;\n"
"     background-color:#666666;\n"
"}\n"
" \n"
"QPushButton#pushButtonUserList:pressed\n"
"{\n"
"    color:white;\n"
"    background-color:rgb(14 , 135 , 228);\n"
"    padding-left:3px;\n"
"    padding-top:3px;\n"
"}\n"
""));

        MainLayout->addWidget(pushButtonUserList);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        MainLayout->addItem(verticalSpacer_4);

        pushButtonPoList = new QPushButton(layoutWidget1);
        pushButtonPoList->setObjectName(QStringLiteral("pushButtonPoList"));
        pushButtonPoList->setMinimumSize(QSize(0, 80));
        pushButtonPoList->setFont(font3);
        pushButtonPoList->setStyleSheet(QLatin1String("QPushButton#pushButtonPoList\n"
"{\n"
"    color:white;\n"
"\n"
"    border-radius:5px;\n"
"}\n"
" \n"
"QPushButton#pushButtonPoList:hover\n"
"{\n"
"    color:white;\n"
"    background-color:#666666;\n"
"}\n"
" \n"
"QPushButton#pushButtonPoList:pressed\n"
"{\n"
"    color:white;\n"
"    background-color:rgb(14 , 135 , 228);\n"
"    padding-left:3px;\n"
"    padding-top:3px;\n"
"}\n"
""));

        MainLayout->addWidget(pushButtonPoList);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        MainLayout->addItem(verticalSpacer_5);

        pushButtonChgPsw = new QPushButton(MainPage);
        pushButtonChgPsw->setObjectName(QStringLiteral("pushButtonChgPsw"));
        pushButtonChgPsw->setGeometry(QRect(1090, 200, 90, 90));
        pushButtonChgPsw->setMinimumSize(QSize(0, 80));
        pushButtonChgPsw->setFont(font3);
        pushButtonChgPsw->setMouseTracking(false);
        pushButtonChgPsw->setContextMenuPolicy(Qt::DefaultContextMenu);
        pushButtonChgPsw->setAutoFillBackground(false);
        pushButtonChgPsw->setStyleSheet(QString::fromUtf8("QPushButton#pushButtonChgPsw\n"
"{\n"
"	border-image: url(:/images/images/\344\277\256\346\224\271\345\257\206\347\240\201.png);\n"
"}\n"
" \n"
"QPushButton#pushButtonChgPsw:hover\n"
"{\n"
"	border-image: url(:/images/images/\344\277\256\346\224\271\345\257\206\347\240\2012.png);\n"
"    color:white;\n"
"};\n"
" \n"
"QPushButton#pushButtonChgPsw:pressed\n"
"{\n"
"    color:white;\n"
"    background-color:rgb(14 , 135 , 228);\n"
"    padding-left:3px;\n"
"    padding-top:3px;\n"
"}\n"
""));
        pushButtonChgPsw->setAutoDefault(true);
        pushButtonLouout = new QPushButton(MainPage);
        pushButtonLouout->setObjectName(QStringLiteral("pushButtonLouout"));
        pushButtonLouout->setGeometry(QRect(1080, 460, 101, 101));
        pushButtonLouout->setMinimumSize(QSize(0, 80));
        pushButtonLouout->setFont(font3);
        pushButtonLouout->setStyleSheet(QString::fromUtf8("\n"
"QPushButton#pushButtonLouout\n"
"{\n"
"border-image: url(:/images/images/\347\231\273\345\207\272.png);\n"
"    color:white;\n"
"    border-radius:5px;\n"
"}\n"
" \n"
"QPushButton#pushButtonLouout:hover\n"
"{\n"
"border-image: url(:/images/images/\347\231\273\345\207\2722.png);\n"
"    color:white;\n"
"}\n"
" \n"
"QPushButton#pushButtonLouout:pressed\n"
"{\n"
"    color:white;\n"
"    background-color:rgb(14 , 135 , 228);\n"
"    padding-left:3px;\n"
"    padding-top:3px;\n"
"}\n"
""));
        stackedWidget->addWidget(MainPage);
        cngPswPage = new QWidget();
        cngPswPage->setObjectName(QStringLiteral("cngPswPage"));
        cngPswPage->setFont(font3);
        cngPswPage->setStyleSheet(QStringLiteral("background-color: rgb(102, 102, 102);"));
        layoutWidget2 = new QWidget(cngPswPage);
        layoutWidget2->setObjectName(QStringLiteral("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(430, 170, 506, 431));
        gridLayout = new QGridLayout(layoutWidget2);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        labelNewPsw2 = new QLabel(layoutWidget2);
        labelNewPsw2->setObjectName(QStringLiteral("labelNewPsw2"));
        QFont font5;
        font5.setFamily(QStringLiteral("Terminal"));
        font5.setPointSize(15);
        font5.setBold(false);
        font5.setItalic(false);
        font5.setWeight(9);
        labelNewPsw2->setFont(font5);
        labelNewPsw2->setStyleSheet(QLatin1String("QLabel#labelNewPsw2\n"
"{\n"
"font: 75 15pt Terminal;                        \n"
"border-radius: 4px;                                                \n"
"color:white;                              \n"
"}\n"
""));

        horizontalLayout->addWidget(labelNewPsw2);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);

        lineEditNewPsw2 = new QLineEdit(layoutWidget2);
        lineEditNewPsw2->setObjectName(QStringLiteral("lineEditNewPsw2"));
        lineEditNewPsw2->setMinimumSize(QSize(250, 30));
        lineEditNewPsw2->setStyleSheet(QStringLiteral("color:white;"));
        lineEditNewPsw2->setEchoMode(QLineEdit::Password);

        horizontalLayout->addWidget(lineEditNewPsw2);


        gridLayout->addLayout(horizontalLayout, 2, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        labelNewPsw = new QLabel(layoutWidget2);
        labelNewPsw->setObjectName(QStringLiteral("labelNewPsw"));
        QFont font6;
        font6.setFamily(QStringLiteral("Terminal"));
        font6.setPointSize(22);
        font6.setBold(false);
        font6.setItalic(false);
        font6.setWeight(12);
        labelNewPsw->setFont(font6);
        labelNewPsw->setStyleSheet(QLatin1String("QLabel#labelNewPsw\n"
"{\n"
"color:white;\n"
"font: 100 22pt Terminal;                        \n"
"border-radius: 4px;                                             \n"
"                             \n"
"}"));

        horizontalLayout_2->addWidget(labelNewPsw);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        lineEditNewPsw = new QLineEdit(layoutWidget2);
        lineEditNewPsw->setObjectName(QStringLiteral("lineEditNewPsw"));
        lineEditNewPsw->setMinimumSize(QSize(250, 30));
        lineEditNewPsw->setStyleSheet(QStringLiteral("color:white;"));
        lineEditNewPsw->setEchoMode(QLineEdit::Password);

        horizontalLayout_2->addWidget(lineEditNewPsw);


        gridLayout->addLayout(horizontalLayout_2, 1, 0, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        pushButtonCngPswAdmit = new QPushButton(layoutWidget2);
        pushButtonCngPswAdmit->setObjectName(QStringLiteral("pushButtonCngPswAdmit"));
        pushButtonCngPswAdmit->setMinimumSize(QSize(200, 60));
        pushButtonCngPswAdmit->setFont(font3);
        pushButtonCngPswAdmit->setStyleSheet(QLatin1String("QPushButton#pushButtonCngPswAdmit\n"
"{\n"
"    color:white;\n"
"    background-color:rgb(102,102,102);\n"
"    border-radius:5px;\n"
"}\n"
" \n"
"QPushButton#pushButtonCngPswAdmit:hover\n"
"{\n"
"    color:white;\n"
"    background-color:rgb(138,138,138);\n"
"}\n"
" \n"
"QPushButton#pushButtonCngPswAdmit:pressed\n"
"{\n"
"    color:white;\n"
"    background-color:rgb(14 , 135 , 228);\n"
"    padding-left:3px;\n"
"    padding-top:3px;\n"
"}\n"
""));

        horizontalLayout_4->addWidget(pushButtonCngPswAdmit);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);

        pushButtonCngPswBack = new QPushButton(layoutWidget2);
        pushButtonCngPswBack->setObjectName(QStringLiteral("pushButtonCngPswBack"));
        pushButtonCngPswBack->setMinimumSize(QSize(200, 60));
        pushButtonCngPswBack->setFont(font3);
        pushButtonCngPswBack->setStyleSheet(QLatin1String("QPushButton#pushButtonCngPswBack\n"
"{\n"
"    color:white;\n"
"    background-color:rgb(102,102,102);\n"
"    border-radius:5px;\n"
"}\n"
" \n"
"QPushButton#pushButtonCngPswBack:hover\n"
"{\n"
"    color:white;\n"
"    background-color:rgb(138,138,138);\n"
"}\n"
" \n"
"QPushButton#pushButtonCngPswBack:pressed\n"
"{\n"
"    color:white;\n"
"    background-color:rgb(14 , 135 , 228);\n"
"    padding-left:3px;\n"
"    padding-top:3px;\n"
"}\n"
""));

        horizontalLayout_4->addWidget(pushButtonCngPswBack);


        gridLayout->addLayout(horizontalLayout_4, 3, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        labelOldPsw = new QLabel(layoutWidget2);
        labelOldPsw->setObjectName(QStringLiteral("labelOldPsw"));
        QFont font7;
        font7.setFamily(QStringLiteral("Terminal"));
        font7.setPointSize(12);
        font7.setBold(false);
        font7.setItalic(false);
        font7.setWeight(9);
        labelOldPsw->setFont(font7);
        labelOldPsw->setStyleSheet(QLatin1String("QLabel#labelOldPsw\n"
"{\n"
"color:white;\n"
"font: 75 12pt Terminal;                        \n"
"border-radius: 4px;                                                                    \n"
"}"));

        horizontalLayout_3->addWidget(labelOldPsw);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);

        lineEditOldPsw = new QLineEdit(layoutWidget2);
        lineEditOldPsw->setObjectName(QStringLiteral("lineEditOldPsw"));
        lineEditOldPsw->setMinimumSize(QSize(250, 30));
        lineEditOldPsw->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
        lineEditOldPsw->setEchoMode(QLineEdit::Password);

        horizontalLayout_3->addWidget(lineEditOldPsw);


        gridLayout->addLayout(horizontalLayout_3, 0, 0, 1, 1);

        stackedWidget->addWidget(cngPswPage);
        UserListpage = new QWidget();
        UserListpage->setObjectName(QStringLiteral("UserListpage"));
        tableUserList = new QTableWidget(UserListpage);
        tableUserList->setObjectName(QStringLiteral("tableUserList"));
        tableUserList->setGeometry(QRect(110, 59, 681, 651));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tableUserList->sizePolicy().hasHeightForWidth());
        tableUserList->setSizePolicy(sizePolicy);
        tableUserList->setFont(font3);
        tableUserList->setStyleSheet(QLatin1String("background-color: rgb(102, 102, 102);\n"
"color:white;\n"
"QTabWidget[lightblue = \"true\"] QTabBar::tab{ \n"
"	background-color: rgb(102, 102, 102);   	\n"
"	border-top:1px solid rgb(249,249,249);\n"
"	border-top-left-radius: 4px;\n"
"    border-top-right-radius: 4px;\n"
"	max-height:20px;\n"
"	min-height:20px;\n"
"	min-width:95px;\n"
"	font-family:Terminal;\n"
"	color:rgb(255,255,255);\n"
"	font-size:13px;\n"
"	padding:0px 0px 0px 0px;\n"
"	border-image:url();\n"
"	margin: 0px;\n"
"	padding-bottom:15px;\n"
"}\n"
"\n"
"QTabWidget[lightblue = \"true\"] QTabBar::tab:selected{\n"
"	border-left:1px solid rgb(192,215,250);\n"
"	border-right:1px solid rgb(192,215,250);\n"
"	border-top:1px solid rgb(192,215,250);\n"
"	color:rgb(50,50,50);\n"
"	background-color:rgb(249,249,249);\n"
"	font-size:13px;\n"
"	border-image:url();\n"
"	margin: 0px;\n"
"}\n"
"\n"
"QTabWidget[lightblue = \"true\"]::pane { \n"
" border-top: 1px solid rgb(192,215,250);\n"
" position: absolute;\n"
" top: -1px;\n"
"}"));
        tableUserList->setColumnCount(0);
        pushButtonUserListBack = new QPushButton(UserListpage);
        pushButtonUserListBack->setObjectName(QStringLiteral("pushButtonUserListBack"));
        pushButtonUserListBack->setGeometry(QRect(900, 630, 201, 81));
        pushButtonUserListBack->setFont(font3);
        pushButtonUserListBack->setStyleSheet(QLatin1String("QPushButton#pushButtonUserListBack\n"
"{\n"
"    color:white;\n"
"    border-radius:6px;\n"
"}\n"
" \n"
"QPushButton#pushButtonUserListBack:hover\n"
"{\n"
"    color:white;\n"
"    background-color:#666666;\n"
"	border-radius:6px;\n"
"}\n"
" \n"
"QPushButton#pushButtonUserListBack:pressed\n"
"{\n"
"    color:white;\n"
"    background-color:rgb(14 , 135 , 228);\n"
"    padding-left:3px;\n"
"    padding-top:3px;\n"
"}\n"
""));
        stackedWidget->addWidget(UserListpage);
        PokemonListPage = new QWidget();
        PokemonListPage->setObjectName(QStringLiteral("PokemonListPage"));
        pushButtonPoListBack = new QPushButton(PokemonListPage);
        pushButtonPoListBack->setObjectName(QStringLiteral("pushButtonPoListBack"));
        pushButtonPoListBack->setGeometry(QRect(890, 610, 251, 91));
        pushButtonPoListBack->setFont(font3);
        pushButtonPoListBack->setStyleSheet(QLatin1String("QPushButton#pushButtonPoListBack\n"
"{  \n"
"	border-radius:5px;\n"
"	color:white\n"
"} \n"
"QPushButton#pushButtonPoListBack:hover\n"
"{\n"
"	background-color:#666666;\n"
"	border-radius:5px;\n"
"	color:white;\n"
"}\n"
"QPushButton#pushButtonPoListBack:hover:pressed\n"
"{\n"
"	background-color:rgb(85,170,255); \n"
"	border:2px solid #3C80B1;\n"
"	border-radius:5px;\n"
"	color:white;\n"
"}\n"
""));
        labelBadge1 = new QLabel(PokemonListPage);
        labelBadge1->setObjectName(QStringLiteral("labelBadge1"));
        labelBadge1->setGeometry(QRect(950, 120, 150, 150));
        labelBadge1->setPixmap(QPixmap(QString::fromUtf8(":/images/images/badge1_no.png")));
        labelBadge1->setScaledContents(true);
        labelBadge2 = new QLabel(PokemonListPage);
        labelBadge2->setObjectName(QStringLiteral("labelBadge2"));
        labelBadge2->setGeometry(QRect(950, 380, 150, 150));
        labelBadge2->setPixmap(QPixmap(QString::fromUtf8(":/images/images/badge2_no.png")));
        labelBadge2->setScaledContents(true);
        labelBadge2Tip = new QLabel(PokemonListPage);
        labelBadge2Tip->setObjectName(QStringLiteral("labelBadge2Tip"));
        labelBadge2Tip->setGeometry(QRect(880, 310, 191, 41));
        labelBadge2Tip->setFocusPolicy(Qt::StrongFocus);
        labelBadge2Tip->setStyleSheet(QLatin1String("QLabel#labelBadge2Tip\n"
"{\n"
"font: 25 12pt Terminal;                        \n"
"border-radius: 4px;                                                  \n"
"color:white;              \n"
"}"));
        labelBadge1Tip = new QLabel(PokemonListPage);
        labelBadge1Tip->setObjectName(QStringLiteral("labelBadge1Tip"));
        labelBadge1Tip->setGeometry(QRect(880, 50, 141, 41));
        QFont font8;
        font8.setFamily(QStringLiteral("Terminal"));
        font8.setPointSize(12);
        font8.setBold(false);
        font8.setItalic(false);
        font8.setWeight(3);
        labelBadge1Tip->setFont(font8);
        labelBadge1Tip->setFocusPolicy(Qt::StrongFocus);
        labelBadge1Tip->setStyleSheet(QLatin1String("QLabel#labelBadge1Tip\n"
"{\n"
"color:white;\n"
"font: 25 12pt Terminal;                        \n"
"border-radius: 4px;                                            \n"
"                              \n"
"}"));
        widget = new QWidget(PokemonListPage);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(90, 70, 771, 631));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setSpacing(2);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        winroundLayout = new QHBoxLayout();
        winroundLayout->setSpacing(0);
        winroundLayout->setObjectName(QStringLiteral("winroundLayout"));
        labelWinRound = new QLabel(widget);
        labelWinRound->setObjectName(QStringLiteral("labelWinRound"));
        labelWinRound->setMinimumSize(QSize(0, 50));
        labelWinRound->setStyleSheet(QLatin1String("QLabel#labelWinRound\n"
"{\n"
"font: 75 12pt Terminal;                        \n"
"border-radius: 4px;                                   \n"
"color:white;\n"
"}"));

        winroundLayout->addWidget(labelWinRound);

        labelTotalRound = new QLabel(widget);
        labelTotalRound->setObjectName(QStringLiteral("labelTotalRound"));
        labelTotalRound->setMinimumSize(QSize(0, 50));
        labelTotalRound->setFont(font7);
        labelTotalRound->setStyleSheet(QLatin1String("QLabel#labelTotalRound\n"
"{\n"
"font: 75 12pt Terminal;                        \n"
"border-radius: 4px;                                            \n"
"color:white;                              \n"
"}"));

        winroundLayout->addWidget(labelTotalRound);

        labelWinRate = new QLabel(widget);
        labelWinRate->setObjectName(QStringLiteral("labelWinRate"));
        labelWinRate->setMinimumSize(QSize(0, 50));
        labelWinRate->setStyleSheet(QLatin1String("QLabel#labelWinRate\n"
"{\n"
"font: 75 12pt Terminal;                        \n"
"border-radius: 4px;                                            \n"
"color:white;              \n"
"}"));

        winroundLayout->addWidget(labelWinRate);


        verticalLayout->addLayout(winroundLayout);

        tablePokemonList = new QTableWidget(widget);
        tablePokemonList->setObjectName(QStringLiteral("tablePokemonList"));
        tablePokemonList->setFont(font3);
        tablePokemonList->setStyleSheet(QLatin1String("color:white;\n"
"background-color:#666666"));

        verticalLayout->addWidget(tablePokemonList);

        stackedWidget->addWidget(PokemonListPage);
        PokemonInfoPage = new QWidget();
        PokemonInfoPage->setObjectName(QStringLiteral("PokemonInfoPage"));
        tablePokemonDetail = new QTableWidget(PokemonInfoPage);
        tablePokemonDetail->setObjectName(QStringLiteral("tablePokemonDetail"));
        tablePokemonDetail->setGeometry(QRect(130, 70, 522, 611));
        tablePokemonDetail->setMinimumSize(QSize(521, 611));
        tablePokemonDetail->setFont(font3);
        tablePokemonDetail->setStyleSheet(QLatin1String("background-color: rgb(102, 102, 102);\n"
"color:white;"));
        labelImg = new QLabel(PokemonInfoPage);
        labelImg->setObjectName(QStringLiteral("labelImg"));
        labelImg->setGeometry(QRect(700, 70, 411, 381));
        layoutWidget3 = new QWidget(PokemonInfoPage);
        layoutWidget3->setObjectName(QStringLiteral("layoutWidget3"));
        layoutWidget3->setGeometry(QRect(750, 360, 311, 401));
        verticalLayout_2 = new QVBoxLayout(layoutWidget3);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        pushButtonChgName = new QPushButton(layoutWidget3);
        pushButtonChgName->setObjectName(QStringLiteral("pushButtonChgName"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pushButtonChgName->sizePolicy().hasHeightForWidth());
        pushButtonChgName->setSizePolicy(sizePolicy1);
        pushButtonChgName->setMinimumSize(QSize(200, 80));
        pushButtonChgName->setFont(font3);
        pushButtonChgName->setStyleSheet(QLatin1String("QPushButton#pushButtonChgName\n"
"{  \n"
"	border-radius:5px;\n"
"	color:white\n"
"} \n"
"QPushButton#pushButtonChgName:hover\n"
"{\n"
"	background-color:#666666;\n"
"	border-radius:5px;\n"
"	color:white;\n"
"}\n"
"QPushButton#pushButtonChgName:hover:pressed\n"
"{\n"
"	background-color:rgb(85,170,255); \n"
"	border:2px solid #3C80B1;\n"
"	border-radius:5px;\n"
"	color:white;\n"
"}\n"
""));

        verticalLayout_2->addWidget(pushButtonChgName);

        pushButtonPoInfoBack = new QPushButton(layoutWidget3);
        pushButtonPoInfoBack->setObjectName(QStringLiteral("pushButtonPoInfoBack"));
        sizePolicy1.setHeightForWidth(pushButtonPoInfoBack->sizePolicy().hasHeightForWidth());
        pushButtonPoInfoBack->setSizePolicy(sizePolicy1);
        pushButtonPoInfoBack->setMinimumSize(QSize(200, 80));
        pushButtonPoInfoBack->setFont(font3);
        pushButtonPoInfoBack->setStyleSheet(QLatin1String("QPushButton#pushButtonPoInfoBack\n"
"{  \n"
"	border-radius:5px;\n"
"	color:white\n"
"} \n"
"QPushButton#pushButtonPoInfoBack:hover\n"
"{\n"
"	background-color:#666666;\n"
"	border-radius:5px;\n"
"	color:white;\n"
"}\n"
"QPushButton#pushButtonPoInfoBack:hover:pressed\n"
"{\n"
"	background-color:rgb(85,170,255); \n"
"	border:2px solid #3C80B1;\n"
"	border-radius:5px;\n"
"	color:white;\n"
"}\n"
""));

        verticalLayout_2->addWidget(pushButtonPoInfoBack);

        stackedWidget->addWidget(PokemonInfoPage);
        LevelUpFightPage = new QWidget();
        LevelUpFightPage->setObjectName(QStringLiteral("LevelUpFightPage"));
        textBrowserFightInfo = new QTextBrowser(LevelUpFightPage);
        textBrowserFightInfo->setObjectName(QStringLiteral("textBrowserFightInfo"));
        textBrowserFightInfo->setGeometry(QRect(440, 190, 391, 481));
        textBrowserFightInfo->setFont(font3);
        textBrowserFightInfo->setStyleSheet(QLatin1String("background-color:#666666;\n"
"color:white;"));
        labelPokemon1 = new QLabel(LevelUpFightPage);
        labelPokemon1->setObjectName(QStringLiteral("labelPokemon1"));
        labelPokemon1->setGeometry(QRect(120, 80, 221, 211));
        tablePokemon1 = new QTableWidget(LevelUpFightPage);
        tablePokemon1->setObjectName(QStringLiteral("tablePokemon1"));
        tablePokemon1->setGeometry(QRect(90, 340, 271, 331));
        tablePokemon1->setFont(font3);
        tablePokemon1->setStyleSheet(QLatin1String("background-color:#666666;\n"
"color:white;"));
        tablePokemon2 = new QTableWidget(LevelUpFightPage);
        tablePokemon2->setObjectName(QStringLiteral("tablePokemon2"));
        tablePokemon2->setGeometry(QRect(890, 340, 271, 331));
        tablePokemon2->setFont(font3);
        tablePokemon2->setStyleSheet(QLatin1String("color:white;\n"
"background-color:#666666;"));
        labelPokemon2 = new QLabel(LevelUpFightPage);
        labelPokemon2->setObjectName(QStringLiteral("labelPokemon2"));
        labelPokemon2->setGeometry(QRect(910, 80, 221, 211));
        progressBarPokemon1 = new QProgressBar(LevelUpFightPage);
        progressBarPokemon1->setObjectName(QStringLiteral("progressBarPokemon1"));
        progressBarPokemon1->setGeometry(QRect(70, 310, 331, 21));
        progressBarPokemon1->setFont(font3);
        progressBarPokemon1->setStyleSheet(QStringLiteral("color:white;"));
        progressBarPokemon1->setMaximum(100);
        progressBarPokemon1->setValue(1);
        progressBarPokemon1->setOrientation(Qt::Horizontal);
        progressBarPokemon2 = new QProgressBar(LevelUpFightPage);
        progressBarPokemon2->setObjectName(QStringLiteral("progressBarPokemon2"));
        progressBarPokemon2->setGeometry(QRect(870, 310, 331, 21));
        progressBarPokemon2->setFont(font3);
        progressBarPokemon2->setStyleSheet(QStringLiteral("color:white;"));
        progressBarPokemon2->setValue(24);
        pushButtonBackFromBattle = new QPushButton(LevelUpFightPage);
        pushButtonBackFromBattle->setObjectName(QStringLiteral("pushButtonBackFromBattle"));
        pushButtonBackFromBattle->setGeometry(QRect(440, 70, 391, 101));
        pushButtonBackFromBattle->setFont(font3);
        pushButtonBackFromBattle->setStyleSheet(QLatin1String("QPushButton#pushButtonBackFromBattle\n"
"{  \n"
"	border-radius:5px;\n"
"	color:white\n"
"} \n"
"QPushButton#pushButtonBackFromBattle:hover\n"
"{\n"
"	background-color:#666666;\n"
"	border-radius:5px;\n"
"	color:white;\n"
"}\n"
"QPushButton#pushButtonBackFromBattle:hover:pressed\n"
"{\n"
"	background-color:rgb(85,170,255); \n"
"	border:2px solid #3C80B1;\n"
"	border-radius:5px;\n"
"	color:white;\n"
"}\n"
""));
        stackedWidget->addWidget(LevelUpFightPage);
        LosePokemonPage = new QWidget();
        LosePokemonPage->setObjectName(QStringLiteral("LosePokemonPage"));
        labelLosePokemon3 = new QLabel(LosePokemonPage);
        labelLosePokemon3->setObjectName(QStringLiteral("labelLosePokemon3"));
        labelLosePokemon3->setGeometry(QRect(960, 20, 200, 200));
        labelLosePokemon1 = new QLabel(LosePokemonPage);
        labelLosePokemon1->setObjectName(QStringLiteral("labelLosePokemon1"));
        labelLosePokemon1->setGeometry(QRect(140, 20, 200, 200));
        labelLosePokemon2 = new QLabel(LosePokemonPage);
        labelLosePokemon2->setObjectName(QStringLiteral("labelLosePokemon2"));
        labelLosePokemon2->setGeometry(QRect(550, 20, 200, 200));
        pushButtonLosePokemon2 = new QPushButton(LosePokemonPage);
        pushButtonLosePokemon2->setObjectName(QStringLiteral("pushButtonLosePokemon2"));
        pushButtonLosePokemon2->setGeometry(QRect(520, 670, 261, 71));
        pushButtonLosePokemon2->setFont(font3);
        pushButtonLosePokemon2->setStyleSheet(QLatin1String("QPushButton#pushButtonLosePokemon2\n"
"{  \n"
"	border-radius:5px;\n"
"	color:white\n"
"} \n"
"QPushButton#pushButtonLosePokemon2:hover\n"
"{\n"
"	background-color:#666666;\n"
"	border-radius:5px;\n"
"	color:white;\n"
"}\n"
"QPushButton#pushButtonLosePokemon2:hover:pressed\n"
"{\n"
"	background-color:rgb(85,170,255); \n"
"	border:2px solid #3C80B1;\n"
"	border-radius:5px;\n"
"	color:white;\n"
"}\n"
""));
        pushButtonLosePokemon3 = new QPushButton(LosePokemonPage);
        pushButtonLosePokemon3->setObjectName(QStringLiteral("pushButtonLosePokemon3"));
        pushButtonLosePokemon3->setGeometry(QRect(930, 670, 261, 71));
        pushButtonLosePokemon3->setFont(font3);
        pushButtonLosePokemon3->setStyleSheet(QLatin1String("QPushButton#pushButtonLosePokemon3\n"
"{  \n"
"	border-radius:5px;\n"
"	color:white\n"
"} \n"
"QPushButton#pushButtonLosePokemon3:hover\n"
"{\n"
"	background-color:#666666;\n"
"	border-radius:5px;\n"
"	color:white;\n"
"}\n"
"QPushButton#pushButtonLosePokemon3:hover:pressed\n"
"{\n"
"	background-color:rgb(85,170,255); \n"
"	border:2px solid #3C80B1;\n"
"	border-radius:5px;\n"
"	color:white;\n"
"}\n"
""));
        pushButtonLosePokemon1 = new QPushButton(LosePokemonPage);
        pushButtonLosePokemon1->setObjectName(QStringLiteral("pushButtonLosePokemon1"));
        pushButtonLosePokemon1->setGeometry(QRect(110, 670, 261, 71));
        pushButtonLosePokemon1->setFont(font3);
        pushButtonLosePokemon1->setStyleSheet(QLatin1String("QPushButton#pushButtonLosePokemon1\n"
"{  \n"
"	border-radius:5px;\n"
"	color:white\n"
"} \n"
"QPushButton#pushButtonLosePokemon1:hover\n"
"{\n"
"	background-color:#666666;\n"
"	border-radius:5px;\n"
"	color:white;\n"
"}\n"
"QPushButton#pushButtonLosePokemon1:hover:pressed\n"
"{\n"
"	background-color:rgb(85,170,255); \n"
"	border:2px solid #3C80B1;\n"
"	border-radius:5px;\n"
"	color:white;\n"
"}\n"
""));
        layoutWidget4 = new QWidget(LosePokemonPage);
        layoutWidget4->setObjectName(QStringLiteral("layoutWidget4"));
        layoutWidget4->setGeometry(QRect(110, 220, 1081, 441));
        horizontalLayout_5 = new QHBoxLayout(layoutWidget4);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        tableWidgetLosePokemon1 = new QTableWidget(layoutWidget4);
        tableWidgetLosePokemon1->setObjectName(QStringLiteral("tableWidgetLosePokemon1"));
        tableWidgetLosePokemon1->setFont(font3);
        tableWidgetLosePokemon1->setStyleSheet(QLatin1String("color:white;\n"
"background-color:#666666;"));

        horizontalLayout_5->addWidget(tableWidgetLosePokemon1);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_5);

        tableWidgetLosePokemon2 = new QTableWidget(layoutWidget4);
        tableWidgetLosePokemon2->setObjectName(QStringLiteral("tableWidgetLosePokemon2"));
        tableWidgetLosePokemon2->setFont(font3);
        tableWidgetLosePokemon2->setStyleSheet(QLatin1String("color:white;\n"
"background-color:#666666;"));

        horizontalLayout_5->addWidget(tableWidgetLosePokemon2);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_6);

        tableWidgetLosePokemon3 = new QTableWidget(layoutWidget4);
        tableWidgetLosePokemon3->setObjectName(QStringLiteral("tableWidgetLosePokemon3"));
        tableWidgetLosePokemon3->setFont(font3);
        tableWidgetLosePokemon3->setStyleSheet(QLatin1String("color:white;\n"
"background-color:#666666;"));

        horizontalLayout_5->addWidget(tableWidgetLosePokemon3);

        stackedWidget->addWidget(LosePokemonPage);

        retranslateUi(PokemonWidget);

        stackedWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(PokemonWidget);
    } // setupUi

    void retranslateUi(QWidget *PokemonWidget)
    {
        PokemonWidget->setWindowTitle(QApplication::translate("PokemonWidget", "\345\256\240\347\211\251\345\260\217\347\262\276\347\201\265\345\257\271\346\210\230\347\263\273\347\273\237", Q_NULLPTR));
        buttonLogin->setText(QApplication::translate("PokemonWidget", "LOG IN", Q_NULLPTR));
        buttonRegister->setText(QApplication::translate("PokemonWidget", "REGISTER", Q_NULLPTR));
        buttonQuit->setText(QApplication::translate("PokemonWidget", "QUIT", Q_NULLPTR));
        pushButtonLevelUp->setText(QApplication::translate("PokemonWidget", "LEVELUP MODE", Q_NULLPTR));
        pushButtonDuel->setText(QApplication::translate("PokemonWidget", "DUEL MODE", Q_NULLPTR));
        pushButtonUserList->setText(QApplication::translate("PokemonWidget", "USER LIST", Q_NULLPTR));
        pushButtonPoList->setText(QApplication::translate("PokemonWidget", "POKEMON LIST", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        pushButtonChgPsw->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        pushButtonChgPsw->setText(QString());
        pushButtonLouout->setText(QString());
        labelNewPsw2->setText(QApplication::translate("PokemonWidget", "PLEASE ENTER AGAIN:", Q_NULLPTR));
        labelNewPsw->setText(QApplication::translate("PokemonWidget", "NEW PASSWORD:", Q_NULLPTR));
        pushButtonCngPswAdmit->setText(QApplication::translate("PokemonWidget", "CHANGE PASSWORD", Q_NULLPTR));
        pushButtonCngPswBack->setText(QApplication::translate("PokemonWidget", "BACK", Q_NULLPTR));
        labelOldPsw->setText(QApplication::translate("PokemonWidget", "OLD PASSWORD:", Q_NULLPTR));
        pushButtonUserListBack->setText(QApplication::translate("PokemonWidget", "BACK", Q_NULLPTR));
        pushButtonPoListBack->setText(QApplication::translate("PokemonWidget", "\350\277\224\345\233\236", Q_NULLPTR));
        labelBadge1->setText(QString());
        labelBadge2->setText(QString());
#ifndef QT_NO_TOOLTIP
        labelBadge2Tip->setToolTip(QApplication::translate("PokemonWidget", "\344\273\243\350\241\250\344\275\24015\347\272\247\347\232\204\345\256\240\347\211\251\344\270\252\346\225\260", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        labelBadge2Tip->setText(QApplication::translate("PokemonWidget", "HIGH-LEVEL BADGET:", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        labelBadge1Tip->setToolTip(QApplication::translate("PokemonWidget", "\344\273\243\350\241\250\344\275\240\346\213\245\346\234\211\347\232\204\345\260\217\347\262\276\347\201\265\346\225\260\351\207\217", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        labelBadge1Tip->setText(QApplication::translate("PokemonWidget", "NUMBER BADGET:", Q_NULLPTR));
        labelWinRound->setText(QString());
        labelTotalRound->setText(QString());
        labelWinRate->setText(QString());
        labelImg->setText(QString());
        pushButtonChgName->setText(QApplication::translate("PokemonWidget", "CHANGE NAME", Q_NULLPTR));
        pushButtonPoInfoBack->setText(QApplication::translate("PokemonWidget", "BACK", Q_NULLPTR));
        labelPokemon1->setText(QApplication::translate("PokemonWidget", "TextLabel", Q_NULLPTR));
        labelPokemon2->setText(QApplication::translate("PokemonWidget", "TextLabel", Q_NULLPTR));
        progressBarPokemon1->setFormat(QApplication::translate("PokemonWidget", "%v/%m", Q_NULLPTR));
        progressBarPokemon2->setFormat(QApplication::translate("PokemonWidget", "%v/%m", Q_NULLPTR));
        pushButtonBackFromBattle->setText(QApplication::translate("PokemonWidget", "BACK TO MENU", Q_NULLPTR));
        labelLosePokemon3->setText(QString());
        labelLosePokemon1->setText(QString());
        labelLosePokemon2->setText(QString());
        pushButtonLosePokemon2->setText(QApplication::translate("PokemonWidget", "SAY BYEBYE~~", Q_NULLPTR));
        pushButtonLosePokemon3->setText(QApplication::translate("PokemonWidget", "SAY \345\206\215\350\247\201~~", Q_NULLPTR));
        pushButtonLosePokemon1->setText(QApplication::translate("PokemonWidget", "SAY GOODBYE~~", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class PokemonWidget: public Ui_PokemonWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_POKEMONWIDGET_H
