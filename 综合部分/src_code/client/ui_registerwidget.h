/********************************************************************************
** Form generated from reading UI file 'registerwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTERWIDGET_H
#define UI_REGISTERWIDGET_H

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
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_registerWidget
{
public:
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_2;
    QLabel *labelUsername;
    QLabel *labelPassword;
    QLabel *labelPassword_2;
    QVBoxLayout *verticalLayout;
    QLineEdit *lineEditUsename;
    QLineEdit *lineEditPassword;
    QLineEdit *lineEditPassword_2;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *pushButtonReg;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButtonBack;
    QLabel *labelWarning;

    void setupUi(QWidget *registerWidget)
    {
        if (registerWidget->objectName().isEmpty())
            registerWidget->setObjectName(QStringLiteral("registerWidget"));
        registerWidget->resize(625, 414);
        QFont font;
        font.setFamily(QString::fromUtf8("\345\271\274\345\234\206"));
        registerWidget->setFont(font);
        layoutWidget = new QWidget(registerWidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(30, 20, 552, 381));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        labelUsername = new QLabel(layoutWidget);
        labelUsername->setObjectName(QStringLiteral("labelUsername"));
        QFont font1;
        font1.setFamily(QStringLiteral("Terminal"));
        font1.setPointSize(12);
        font1.setBold(true);
        font1.setWeight(75);
        labelUsername->setFont(font1);
        labelUsername->setStyleSheet(QLatin1String("color:white;\n"
""));

        verticalLayout_2->addWidget(labelUsername);

        labelPassword = new QLabel(layoutWidget);
        labelPassword->setObjectName(QStringLiteral("labelPassword"));
        labelPassword->setFont(font1);
        labelPassword->setStyleSheet(QLatin1String("color:white;\n"
""));

        verticalLayout_2->addWidget(labelPassword);

        labelPassword_2 = new QLabel(layoutWidget);
        labelPassword_2->setObjectName(QStringLiteral("labelPassword_2"));
        labelPassword_2->setFont(font1);
        labelPassword_2->setStyleSheet(QLatin1String("color:white;\n"
""));

        verticalLayout_2->addWidget(labelPassword_2);


        horizontalLayout->addLayout(verticalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(15);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        lineEditUsename = new QLineEdit(layoutWidget);
        lineEditUsename->setObjectName(QStringLiteral("lineEditUsename"));
        lineEditUsename->setMinimumSize(QSize(0, 30));
        lineEditUsename->setFont(font1);
        lineEditUsename->setStyleSheet(QLatin1String("color:white;\n"
"background-color:#666666"));
        lineEditUsename->setMaxLength(30);
        lineEditUsename->setEchoMode(QLineEdit::Normal);

        verticalLayout->addWidget(lineEditUsename);

        lineEditPassword = new QLineEdit(layoutWidget);
        lineEditPassword->setObjectName(QStringLiteral("lineEditPassword"));
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lineEditPassword->sizePolicy().hasHeightForWidth());
        lineEditPassword->setSizePolicy(sizePolicy);
        lineEditPassword->setMinimumSize(QSize(0, 30));
        lineEditPassword->setStyleSheet(QLatin1String("color:white;\n"
"background-color:#666666"));
        lineEditPassword->setMaxLength(30);
        lineEditPassword->setEchoMode(QLineEdit::Password);

        verticalLayout->addWidget(lineEditPassword);

        lineEditPassword_2 = new QLineEdit(layoutWidget);
        lineEditPassword_2->setObjectName(QStringLiteral("lineEditPassword_2"));
        lineEditPassword_2->setMinimumSize(QSize(0, 30));
        lineEditPassword_2->setStyleSheet(QLatin1String("color:white;\n"
"background-color:#666666"));
        lineEditPassword_2->setMaxLength(30);
        lineEditPassword_2->setEchoMode(QLineEdit::Password);

        verticalLayout->addWidget(lineEditPassword_2);


        horizontalLayout->addLayout(verticalLayout);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        pushButtonReg = new QPushButton(layoutWidget);
        pushButtonReg->setObjectName(QStringLiteral("pushButtonReg"));
        pushButtonReg->setMinimumSize(QSize(200, 60));
        pushButtonReg->setFont(font1);
        pushButtonReg->setStyleSheet(QLatin1String("QPushButton#pushButtonReg\n"
"{\n"
"\n"
"border-radius:5px;\n"
"color:white\n"
"}\n"
"QPushButton#pushButtonReg:hover\n"
"{\n"
"background-color:#666666;\n"
"border-radius:5px;\n"
"color:white;\n"
"}\n"
"QPushButton#pushbuttonReg:hover:pressed\n"
"{\n"
"background-color:rgb(85,170,255); \n"
"border:2px solid #3C80B1;\n"
"border-radius:5px;\n"
"color:white;\n"
"}"));

        horizontalLayout_3->addWidget(pushButtonReg);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        pushButtonBack = new QPushButton(layoutWidget);
        pushButtonBack->setObjectName(QStringLiteral("pushButtonBack"));
        pushButtonBack->setMinimumSize(QSize(200, 60));
        pushButtonBack->setFont(font1);
        pushButtonBack->setStyleSheet(QLatin1String("QPushButton#pushButtonBack\n"
"{\n"
"\n"
"border-radius:5px;\n"
"color:white\n"
"}\n"
"QPushButton#pushButtonBack:hover\n"
"{\n"
"background-color:#666666;\n"
"border-radius:5px;\n"
"color:white;\n"
"}\n"
"QPushButton#pushbuttonBack:hover:pressed\n"
"{\n"
"background-color:rgb(85,170,255); \n"
"border:2px solid #3C80B1;\n"
"border-radius:5px;\n"
"color:white;\n"
"}"));

        horizontalLayout_3->addWidget(pushButtonBack);


        gridLayout->addLayout(horizontalLayout_3, 2, 0, 1, 1);

        labelWarning = new QLabel(layoutWidget);
        labelWarning->setObjectName(QStringLiteral("labelWarning"));
        labelWarning->setMaximumSize(QSize(16777215, 40));
        QFont font2;
        font2.setFamily(QStringLiteral("Terminal"));
        font2.setPointSize(10);
        font2.setBold(true);
        font2.setWeight(75);
        labelWarning->setFont(font2);
        labelWarning->setStyleSheet(QLatin1String("color:white;\n"
""));
        labelWarning->setTextFormat(Qt::AutoText);

        gridLayout->addWidget(labelWarning, 1, 0, 1, 1);


        retranslateUi(registerWidget);

        QMetaObject::connectSlotsByName(registerWidget);
    } // setupUi

    void retranslateUi(QWidget *registerWidget)
    {
        registerWidget->setWindowTitle(QApplication::translate("registerWidget", "\346\263\250\345\206\214\347\225\214\351\235\242", Q_NULLPTR));
        labelUsername->setText(QApplication::translate("registerWidget", "USERNAME:", Q_NULLPTR));
        labelPassword->setText(QApplication::translate("registerWidget", "PASSWORD:", Q_NULLPTR));
        labelPassword_2->setText(QApplication::translate("registerWidget", "PASSWORD AGAIN:", Q_NULLPTR));
        lineEditUsename->setText(QApplication::translate("registerWidget", "billsjc123", Q_NULLPTR));
        lineEditPassword->setText(QApplication::translate("registerWidget", "1", Q_NULLPTR));
        lineEditPassword_2->setText(QApplication::translate("registerWidget", "1", Q_NULLPTR));
        pushButtonReg->setText(QApplication::translate("registerWidget", "OK", Q_NULLPTR));
        pushButtonBack->setText(QApplication::translate("registerWidget", "BACK", Q_NULLPTR));
        labelWarning->setText(QApplication::translate("registerWidget", "PLEASE ENTER PASSWORD AND USERNAME!~~~///(^v^)\\~~~", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class registerWidget: public Ui_registerWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTERWIDGET_H
