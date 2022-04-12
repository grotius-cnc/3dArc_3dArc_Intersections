/********************************************************************************
** Form generated from reading UI file 'OcctQtControls.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OCCTQTCONTROLS_H
#define UI_OCCTQTCONTROLS_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OcctQtControls
{
public:
    QGridLayout *gridLayout_4;
    QGridLayout *gridLayout_2;
    QLabel *label_mouse_z;
    QLabel *label_val_mouse_z;
    QLabel *label_mouse_y;
    QLabel *label_val_mouse_y;
    QLabel *label_val_mouse_x;
    QLabel *label_mouse_x;
    QSpacerItem *horizontalSpacer_2;
    QGridLayout *gridLayout;
    QToolButton *toolButton_zoom_3d;
    QSpacerItem *horizontalSpacer;
    QToolButton *toolButton_zoom_min;
    QToolButton *toolButton_zoom_plus;
    QToolButton *toolButton_zoom_bottom;
    QToolButton *toolButton_zoom_fromt;
    QToolButton *toolButton_zoom_right;
    QToolButton *toolButton_zoom_extends;
    QToolButton *toolButton_zoom_back;
    QToolButton *toolButton_zoom_top;
    QToolButton *toolButton_zoom_left;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *OcctQtControls)
    {
        if (OcctQtControls->objectName().isEmpty())
            OcctQtControls->setObjectName(QString::fromUtf8("OcctQtControls"));
        OcctQtControls->resize(405, 297);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(OcctQtControls->sizePolicy().hasHeightForWidth());
        OcctQtControls->setSizePolicy(sizePolicy);
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(13, 17, 23, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush1);
        QBrush brush2(QColor(19, 25, 34, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Light, brush2);
        QBrush brush3(QColor(16, 21, 28, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Midlight, brush3);
        QBrush brush4(QColor(6, 8, 11, 255));
        brush4.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Dark, brush4);
        QBrush brush5(QColor(9, 11, 15, 255));
        brush5.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        palette.setBrush(QPalette::Active, QPalette::BrightText, brush);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        QBrush brush6(QColor(0, 0, 0, 255));
        brush6.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Base, brush6);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette.setBrush(QPalette::Active, QPalette::Shadow, brush6);
        palette.setBrush(QPalette::Active, QPalette::AlternateBase, brush4);
        QBrush brush7(QColor(255, 255, 220, 255));
        brush7.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::ToolTipBase, brush7);
        palette.setBrush(QPalette::Active, QPalette::ToolTipText, brush6);
        QBrush brush8(QColor(255, 255, 255, 128));
        brush8.setStyle(Qt::SolidPattern);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Active, QPalette::PlaceholderText, brush8);
#endif
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Light, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::Midlight, brush3);
        palette.setBrush(QPalette::Inactive, QPalette::Dark, brush4);
        palette.setBrush(QPalette::Inactive, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::BrightText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush6);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Shadow, brush6);
        palette.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush4);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush7);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush6);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush8);
#endif
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Light, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Midlight, brush3);
        palette.setBrush(QPalette::Disabled, QPalette::Dark, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::BrightText, brush);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Shadow, brush6);
        palette.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush7);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush6);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush8);
#endif
        OcctQtControls->setPalette(palette);
        OcctQtControls->setMouseTracking(false);
        gridLayout_4 = new QGridLayout(OcctQtControls);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_mouse_z = new QLabel(OcctQtControls);
        label_mouse_z->setObjectName(QString::fromUtf8("label_mouse_z"));
        QFont font;
        font.setBold(false);
        font.setWeight(50);
        label_mouse_z->setFont(font);
        label_mouse_z->setFrameShape(QFrame::Panel);
        label_mouse_z->setFrameShadow(QFrame::Sunken);
        label_mouse_z->setLineWidth(1);
        label_mouse_z->setMidLineWidth(0);

        gridLayout_2->addWidget(label_mouse_z, 2, 4, 1, 1);

        label_val_mouse_z = new QLabel(OcctQtControls);
        label_val_mouse_z->setObjectName(QString::fromUtf8("label_val_mouse_z"));
        label_val_mouse_z->setMinimumSize(QSize(0, 0));
        label_val_mouse_z->setFont(font);
        label_val_mouse_z->setFrameShape(QFrame::Panel);
        label_val_mouse_z->setFrameShadow(QFrame::Sunken);
        label_val_mouse_z->setLineWidth(1);
        label_val_mouse_z->setMidLineWidth(0);

        gridLayout_2->addWidget(label_val_mouse_z, 2, 5, 1, 1);

        label_mouse_y = new QLabel(OcctQtControls);
        label_mouse_y->setObjectName(QString::fromUtf8("label_mouse_y"));
        label_mouse_y->setFont(font);
        label_mouse_y->setAutoFillBackground(false);
        label_mouse_y->setStyleSheet(QString::fromUtf8(""));
        label_mouse_y->setFrameShape(QFrame::Panel);
        label_mouse_y->setFrameShadow(QFrame::Sunken);
        label_mouse_y->setLineWidth(1);
        label_mouse_y->setMidLineWidth(0);

        gridLayout_2->addWidget(label_mouse_y, 1, 4, 1, 1);

        label_val_mouse_y = new QLabel(OcctQtControls);
        label_val_mouse_y->setObjectName(QString::fromUtf8("label_val_mouse_y"));
        label_val_mouse_y->setMinimumSize(QSize(0, 0));
        label_val_mouse_y->setFont(font);
        label_val_mouse_y->setAutoFillBackground(false);
        label_val_mouse_y->setStyleSheet(QString::fromUtf8(""));
        label_val_mouse_y->setFrameShape(QFrame::Panel);
        label_val_mouse_y->setFrameShadow(QFrame::Sunken);
        label_val_mouse_y->setLineWidth(1);
        label_val_mouse_y->setMidLineWidth(0);

        gridLayout_2->addWidget(label_val_mouse_y, 1, 5, 1, 1);

        label_val_mouse_x = new QLabel(OcctQtControls);
        label_val_mouse_x->setObjectName(QString::fromUtf8("label_val_mouse_x"));
        sizePolicy.setHeightForWidth(label_val_mouse_x->sizePolicy().hasHeightForWidth());
        label_val_mouse_x->setSizePolicy(sizePolicy);
        label_val_mouse_x->setMinimumSize(QSize(75, 0));
        label_val_mouse_x->setFont(font);
        label_val_mouse_x->setAutoFillBackground(false);
        label_val_mouse_x->setStyleSheet(QString::fromUtf8(""));
        label_val_mouse_x->setFrameShape(QFrame::Panel);
        label_val_mouse_x->setFrameShadow(QFrame::Sunken);
        label_val_mouse_x->setLineWidth(1);
        label_val_mouse_x->setMidLineWidth(0);

        gridLayout_2->addWidget(label_val_mouse_x, 0, 5, 1, 1);

        label_mouse_x = new QLabel(OcctQtControls);
        label_mouse_x->setObjectName(QString::fromUtf8("label_mouse_x"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_mouse_x->sizePolicy().hasHeightForWidth());
        label_mouse_x->setSizePolicy(sizePolicy1);
        label_mouse_x->setFont(font);
        label_mouse_x->setAutoFillBackground(false);
        label_mouse_x->setStyleSheet(QString::fromUtf8(""));
        label_mouse_x->setFrameShape(QFrame::Panel);
        label_mouse_x->setFrameShadow(QFrame::Sunken);
        label_mouse_x->setLineWidth(1);
        label_mouse_x->setMidLineWidth(0);

        gridLayout_2->addWidget(label_mouse_x, 0, 4, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_2, 1, 0, 1, 1);


        gridLayout_4->addLayout(gridLayout_2, 4, 1, 1, 1);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        toolButton_zoom_3d = new QToolButton(OcctQtControls);
        toolButton_zoom_3d->setObjectName(QString::fromUtf8("toolButton_zoom_3d"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/view-iso.svg"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_zoom_3d->setIcon(icon);
        toolButton_zoom_3d->setCheckable(false);
        toolButton_zoom_3d->setChecked(false);
        toolButton_zoom_3d->setAutoRepeat(false);
        toolButton_zoom_3d->setAutoExclusive(false);
        toolButton_zoom_3d->setAutoRepeatDelay(300);
        toolButton_zoom_3d->setAutoRepeatInterval(100);

        gridLayout->addWidget(toolButton_zoom_3d, 0, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(2000, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 0, 1, 1);

        toolButton_zoom_min = new QToolButton(OcctQtControls);
        toolButton_zoom_min->setObjectName(QString::fromUtf8("toolButton_zoom_min"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/zoom_min.svg"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_zoom_min->setIcon(icon1);

        gridLayout->addWidget(toolButton_zoom_min, 0, 10, 1, 1);

        toolButton_zoom_plus = new QToolButton(OcctQtControls);
        toolButton_zoom_plus->setObjectName(QString::fromUtf8("toolButton_zoom_plus"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/zoom_plus.svg"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_zoom_plus->setIcon(icon2);

        gridLayout->addWidget(toolButton_zoom_plus, 0, 9, 1, 1);

        toolButton_zoom_bottom = new QToolButton(OcctQtControls);
        toolButton_zoom_bottom->setObjectName(QString::fromUtf8("toolButton_zoom_bottom"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/view-bottom.svg"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_zoom_bottom->setIcon(icon3);

        gridLayout->addWidget(toolButton_zoom_bottom, 0, 3, 1, 1);

        toolButton_zoom_fromt = new QToolButton(OcctQtControls);
        toolButton_zoom_fromt->setObjectName(QString::fromUtf8("toolButton_zoom_fromt"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/view-front.svg"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_zoom_fromt->setIcon(icon4);

        gridLayout->addWidget(toolButton_zoom_fromt, 0, 4, 1, 1);

        toolButton_zoom_right = new QToolButton(OcctQtControls);
        toolButton_zoom_right->setObjectName(QString::fromUtf8("toolButton_zoom_right"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/view-right.svg"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_zoom_right->setIcon(icon5);

        gridLayout->addWidget(toolButton_zoom_right, 0, 6, 1, 1);

        toolButton_zoom_extends = new QToolButton(OcctQtControls);
        toolButton_zoom_extends->setObjectName(QString::fromUtf8("toolButton_zoom_extends"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/zoom_extend.svg"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_zoom_extends->setIcon(icon6);

        gridLayout->addWidget(toolButton_zoom_extends, 0, 8, 1, 1);

        toolButton_zoom_back = new QToolButton(OcctQtControls);
        toolButton_zoom_back->setObjectName(QString::fromUtf8("toolButton_zoom_back"));
        toolButton_zoom_back->setAutoFillBackground(true);
        toolButton_zoom_back->setStyleSheet(QString::fromUtf8(""));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/view-back.svg"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_zoom_back->setIcon(icon7);

        gridLayout->addWidget(toolButton_zoom_back, 0, 2, 1, 1);

        toolButton_zoom_top = new QToolButton(OcctQtControls);
        toolButton_zoom_top->setObjectName(QString::fromUtf8("toolButton_zoom_top"));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/view-top.svg"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_zoom_top->setIcon(icon8);

        gridLayout->addWidget(toolButton_zoom_top, 0, 7, 1, 1);

        toolButton_zoom_left = new QToolButton(OcctQtControls);
        toolButton_zoom_left->setObjectName(QString::fromUtf8("toolButton_zoom_left"));
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/view-left.svg"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_zoom_left->setIcon(icon9);

        gridLayout->addWidget(toolButton_zoom_left, 0, 5, 1, 1);


        gridLayout_4->addLayout(gridLayout, 0, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 2000, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_4->addItem(verticalSpacer, 2, 1, 1, 1);


        retranslateUi(OcctQtControls);

        QMetaObject::connectSlotsByName(OcctQtControls);
    } // setupUi

    void retranslateUi(QWidget *OcctQtControls)
    {
        OcctQtControls->setWindowTitle(QCoreApplication::translate("OcctQtControls", "Form", nullptr));
        label_mouse_z->setText(QCoreApplication::translate("OcctQtControls", "Z", nullptr));
        label_val_mouse_z->setText(QCoreApplication::translate("OcctQtControls", "0.000", nullptr));
        label_mouse_y->setText(QCoreApplication::translate("OcctQtControls", "Y", nullptr));
        label_val_mouse_y->setText(QCoreApplication::translate("OcctQtControls", "0.000", nullptr));
        label_val_mouse_x->setText(QCoreApplication::translate("OcctQtControls", "0.000", nullptr));
        label_mouse_x->setText(QCoreApplication::translate("OcctQtControls", "X", nullptr));
        toolButton_zoom_3d->setText(QCoreApplication::translate("OcctQtControls", "...", nullptr));
        toolButton_zoom_min->setText(QCoreApplication::translate("OcctQtControls", "...", nullptr));
        toolButton_zoom_plus->setText(QCoreApplication::translate("OcctQtControls", "...", nullptr));
        toolButton_zoom_bottom->setText(QCoreApplication::translate("OcctQtControls", "...", nullptr));
        toolButton_zoom_fromt->setText(QCoreApplication::translate("OcctQtControls", "...", nullptr));
        toolButton_zoom_right->setText(QCoreApplication::translate("OcctQtControls", "...", nullptr));
        toolButton_zoom_extends->setText(QCoreApplication::translate("OcctQtControls", "...", nullptr));
        toolButton_zoom_back->setText(QCoreApplication::translate("OcctQtControls", "...", nullptr));
        toolButton_zoom_top->setText(QCoreApplication::translate("OcctQtControls", "...", nullptr));
        toolButton_zoom_left->setText(QCoreApplication::translate("OcctQtControls", "...", nullptr));
    } // retranslateUi

};

namespace Ui {
    class OcctQtControls: public Ui_OcctQtControls {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OCCTQTCONTROLS_H
