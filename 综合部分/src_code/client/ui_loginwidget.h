/********************************************************************************
** Form generated from reading UI file 'loginwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINWIDGET_H
#define UI_LOGINWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_loginWidget
{
public:
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QGridLayout *gridLayout_2;
    QLineEdit *lineEditUsername;
    QLabel *labelPassword;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *buttonLogin;
    QPushButton *buttonBack;
    QHBoxLayout *horizontalLayout_2;
    QLabel *labelUsername;
    QLineEdit *lineEditPassword;

    void setupUi(QWidget *loginWidget)
    {
        if (loginWidget->objectName().isEmpty())
            loginWidget->setObjectName(QStringLiteral("loginWidget"));
        loginWidget->resize(535, 402);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(loginWidget->sizePolicy().hasHeightForWidth());
        loginWidget->setSizePolicy(sizePolicy);
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        loginWidget->setFont(font);
        loginWidget->setWindowOpacity(1);
        loginWidget->setStyleSheet(QStringLiteral(""));
        layoutWidget = new QWidget(loginWidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(50, 40, 431, 321));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        lineEditUsername = new QLineEdit(layoutWidget);
        lineEditUsername->setObjectName(QStringLiteral("lineEditUsername"));
        lineEditUsername->setMinimumSize(QSize(0, 50));
        QFont font1;
        font1.setFamily(QStringLiteral("Terminal"));
        font1.setPointSize(12);
        font1.setBold(true);
        font1.setWeight(75);
        lineEditUsername->setFont(font1);
        lineEditUsername->setStyleSheet(QLatin1String("color:white;\n"
"background-color: rgb(102, 102, 102);"));

        gridLayout_2->addWidget(lineEditUsername, 0, 1, 1, 1);

        labelPassword = new QLabel(layoutWidget);
        labelPassword->setObjectName(QStringLiteral("labelPassword"));
        QFont font2;
        font2.setFamily(QStringLiteral("Terminal"));
        font2.setPointSize(12);
        font2.setBold(true);
        font2.setItalic(false);
        font2.setUnderline(false);
        font2.setWeight(75);
        labelPassword->setFont(font2);
        labelPassword->setStyleSheet(QStringLiteral("color:white;"));

        gridLayout_2->addWidget(labelPassword, 0, 0, 1, 1);


        gridLayout->addLayout(gridLayout_2, 0, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        buttonLogin = new QPushButton(layoutWidget);
        buttonLogin->setObjectName(QStringLiteral("buttonLogin"));
        buttonLogin->setMinimumSize(QSize(0, 60));
        QFont font3;
        font3.setFamily(QStringLiteral("Terminal"));
        font3.setPointSize(12);
        font3.setBold(true);
        font3.setItalic(false);
        font3.setWeight(75);
        buttonLogin->setFont(font3);
        buttonLogin->setStyleSheet(QLatin1String("QPushButton#buttonLogin\n"
"{\n"
"border-radius:5px;\n"
"color:white\n"
"}\n"
"QPushButton#buttonLogin:hover\n"
"{\n"
"background-color:#666666;\n"
"border-radius:5px;\n"
"color:white;\n"
"}\n"
"QPushButton#buttonLogin:hover:pressed\n"
"{\n"
"background-color:rgb(85,170,255); \n"
"border:2px solid #3C80B1;\n"
"border-radius:5px;\n"
"color:white;\n"
"}"));

        horizontalLayout_3->addWidget(buttonLogin);

        buttonBack = new QPushButton(layoutWidget);
        buttonBack->setObjectName(QStringLiteral("buttonBack"));
        buttonBack->setMinimumSize(QSize(0, 60));
        buttonBack->setFont(font3);
        buttonBack->setStyleSheet(QLatin1String("\n"
"QPushButton#buttonBack\n"
"{\n"
"border-radius:5px;\n"
"color:white\n"
"}\n"
"QPushButton#buttonBack:hover\n"
"{\n"
"background-color:#666666;\n"
"border-radius:5px;\n"
"color:white;\n"
"}\n"
"QPushButton#buttonBack:hover:pressed\n"
"{\n"
"background-color:rgb(85,170,255); \n"
"border:2px solid #3C80B1;\n"
"border-radius:5px;\n"
"color:white;\n"
"}"));

        horizontalLayout_3->addWidget(buttonBack);


        gridLayout->addLayout(horizontalLayout_3, 2, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        labelUsername = new QLabel(layoutWidget);
        labelUsername->setObjectName(QStringLiteral("labelUsername"));
        labelUsername->setFont(font2);
        labelUsername->setStyleSheet(QLatin1String("color:white;\n"
""));

        horizontalLayout_2->addWidget(labelUsername);

        lineEditPassword = new QLineEdit(layoutWidget);
        lineEditPassword->setObjectName(QStringLiteral("lineEditPassword"));
        lineEditPassword->setMinimumSize(QSize(0, 50));
        QFont font4;
        font4.setPointSize(12);
        lineEditPassword->setFont(font4);
        lineEditPassword->setStyleSheet(QLatin1String("background-color: rgb(102, 102, 102);\n"
"color:white;"));
        lineEditPassword->setEchoMode(QLineEdit::Password);

        horizontalLayout_2->addWidget(lineEditPassword);


        gridLayout->addLayout(horizontalLayout_2, 1, 0, 1, 1);


        retranslateUi(loginWidget);

        QMetaObject::connectSlotsByName(loginWidget);
    } // setupUi

    void retranslateUi(QWidget *loginWidget)
    {
        loginWidget->setWindowTitle(QApplication::translate("loginWidget", "\345\256\240\347\211\251\345\260\217\347\262\276\347\201\265\345\257\271\346\210\230\347\263\273\347\273\237\347\231\273\345\275\225\347\225\214\351\235\242", Q_NULLPTR));
        lineEditUsername->setText(QApplication::translate("loginWidget", "billsjc123", Q_NULLPTR));
        labelPassword->setText(QApplication::translate("loginWidget", "USERNAME:", Q_NULLPTR));
        buttonLogin->setText(QApplication::translate("loginWidget", "LOG IN", Q_NULLPTR));
        buttonBack->setText(QApplication::translate("loginWidget", "BACK", Q_NULLPTR));
        labelUsername->setText(QApplication::translate("loginWidget", "PASSWORD:", Q_NULLPTR));
        lineEditPassword->setText(QApplication::translate("loginWidget", "123456", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class loginWidget: public Ui_loginWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINWIDGET_H
