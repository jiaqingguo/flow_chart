/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "graphics_view.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    graphics_view *graphicsView;
    QMenuBar *menubar;
    QStatusBar *statusbar;
    QDockWidget *dockWidget;
    QWidget *dockWidgetContents;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QPushButton *btn_rect;
    QPushButton *btn_round_rect;
    QPushButton *btn_round;
    QPushButton *btn_line;
    QPushButton *btn_diamond;
    QPushButton *pushButton_6;
    QPushButton *pushButton_7;
    QPushButton *pushButton_8;
    QSpacerItem *verticalSpacer;
    QSpacerItem *verticalSpacer_3;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        graphicsView = new graphics_view(centralwidget);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));

        horizontalLayout->addWidget(graphicsView);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);
        dockWidget = new QDockWidget(MainWindow);
        dockWidget->setObjectName(QString::fromUtf8("dockWidget"));
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QString::fromUtf8("dockWidgetContents"));
        verticalLayout = new QVBoxLayout(dockWidgetContents);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        groupBox = new QGroupBox(dockWidgetContents);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy);
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        btn_rect = new QPushButton(groupBox);
        btn_rect->setObjectName(QString::fromUtf8("btn_rect"));
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(btn_rect->sizePolicy().hasHeightForWidth());
        btn_rect->setSizePolicy(sizePolicy1);
        btn_rect->setMinimumSize(QSize(45, 45));
        btn_rect->setMaximumSize(QSize(45, 45));
        btn_rect->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(btn_rect, 0, 0, 1, 1);

        btn_round_rect = new QPushButton(groupBox);
        btn_round_rect->setObjectName(QString::fromUtf8("btn_round_rect"));
        sizePolicy1.setHeightForWidth(btn_round_rect->sizePolicy().hasHeightForWidth());
        btn_round_rect->setSizePolicy(sizePolicy1);
        btn_round_rect->setMinimumSize(QSize(45, 45));
        btn_round_rect->setMaximumSize(QSize(45, 45));
        btn_round_rect->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(btn_round_rect, 0, 1, 1, 1);

        btn_round = new QPushButton(groupBox);
        btn_round->setObjectName(QString::fromUtf8("btn_round"));
        sizePolicy1.setHeightForWidth(btn_round->sizePolicy().hasHeightForWidth());
        btn_round->setSizePolicy(sizePolicy1);
        btn_round->setMinimumSize(QSize(45, 45));
        btn_round->setMaximumSize(QSize(45, 45));
        btn_round->setStyleSheet(QString::fromUtf8("background-image: url(:/img/Round.png);"));

        gridLayout->addWidget(btn_round, 1, 0, 1, 1);

        btn_line = new QPushButton(groupBox);
        btn_line->setObjectName(QString::fromUtf8("btn_line"));
        sizePolicy1.setHeightForWidth(btn_line->sizePolicy().hasHeightForWidth());
        btn_line->setSizePolicy(sizePolicy1);
        btn_line->setMinimumSize(QSize(45, 45));
        btn_line->setMaximumSize(QSize(45, 45));
        btn_line->setStyleSheet(QString::fromUtf8("background-image: url(qrc:/image/arrow0.png);"));

        gridLayout->addWidget(btn_line, 1, 1, 1, 1);

        btn_diamond = new QPushButton(groupBox);
        btn_diamond->setObjectName(QString::fromUtf8("btn_diamond"));
        sizePolicy1.setHeightForWidth(btn_diamond->sizePolicy().hasHeightForWidth());
        btn_diamond->setSizePolicy(sizePolicy1);
        btn_diamond->setMinimumSize(QSize(45, 45));
        btn_diamond->setMaximumSize(QSize(45, 45));
        btn_diamond->setStyleSheet(QString::fromUtf8("border-image: url(:/img/diamond.png);"));

        gridLayout->addWidget(btn_diamond, 2, 0, 1, 1);

        pushButton_6 = new QPushButton(groupBox);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));
        sizePolicy1.setHeightForWidth(pushButton_6->sizePolicy().hasHeightForWidth());
        pushButton_6->setSizePolicy(sizePolicy1);
        pushButton_6->setMinimumSize(QSize(45, 45));
        pushButton_6->setMaximumSize(QSize(45, 45));

        gridLayout->addWidget(pushButton_6, 2, 1, 1, 1);

        pushButton_7 = new QPushButton(groupBox);
        pushButton_7->setObjectName(QString::fromUtf8("pushButton_7"));
        sizePolicy1.setHeightForWidth(pushButton_7->sizePolicy().hasHeightForWidth());
        pushButton_7->setSizePolicy(sizePolicy1);
        pushButton_7->setMinimumSize(QSize(45, 45));
        pushButton_7->setMaximumSize(QSize(45, 45));

        gridLayout->addWidget(pushButton_7, 3, 0, 1, 1);

        pushButton_8 = new QPushButton(groupBox);
        pushButton_8->setObjectName(QString::fromUtf8("pushButton_8"));
        sizePolicy1.setHeightForWidth(pushButton_8->sizePolicy().hasHeightForWidth());
        pushButton_8->setSizePolicy(sizePolicy1);
        pushButton_8->setMinimumSize(QSize(45, 45));
        pushButton_8->setMaximumSize(QSize(45, 45));

        gridLayout->addWidget(pushButton_8, 3, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 4, 0, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_3, 4, 1, 1, 1);


        verticalLayout->addWidget(groupBox);

        groupBox_2 = new QGroupBox(dockWidgetContents);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        verticalLayout_2 = new QVBoxLayout(groupBox_2);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);


        verticalLayout->addWidget(groupBox_2);

        dockWidget->setWidget(dockWidgetContents);
        MainWindow->addDockWidget(Qt::LeftDockWidgetArea, dockWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        dockWidget->setWindowTitle(QCoreApplication::translate("MainWindow", "\346\265\201\347\250\213\350\217\234\345\215\225-\345\240\206\346\240\210\347\252\227\345\217\243", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "\346\265\201\347\250\213\345\233\276\345\205\203", nullptr));
        btn_rect->setText(QCoreApplication::translate("MainWindow", "rect", nullptr));
        btn_round_rect->setText(QCoreApplication::translate("MainWindow", "R_rect", nullptr));
        btn_round->setText(QCoreApplication::translate("MainWindow", "\345\234\206\345\275\242", nullptr));
        btn_line->setText(QCoreApplication::translate("MainWindow", "line", nullptr));
        btn_diamond->setText(QCoreApplication::translate("MainWindow", "\350\217\261\345\275\242", nullptr));
        pushButton_6->setText(QString());
        pushButton_7->setText(QString());
        pushButton_8->setText(QString());
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "\345\205\266\344\273\226", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
