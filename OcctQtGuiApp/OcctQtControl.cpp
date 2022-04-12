#include "OcctQtControl.h"
#include "ui_OcctQtControl.h"
#include "Interface.h"

OcctQtControl::OcctQtControl(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OcctQtControl)
{
    ui->setupUi(this);

    setMouseTracking(true);
    lbl_x= ui->label_val_mouse_x;
    lbl_y= ui->label_val_mouse_y;
    lbl_z= ui->label_val_mouse_z;

    btn_zoom_top=ui->toolButton_zoom_top;
    btn_zoom_bottom=ui->toolButton_zoom_bottom;
    btn_zoom_front=ui->toolButton_zoom_fromt;
    btn_zoom_back=ui->toolButton_zoom_back;
    btn_zoom_left=ui->toolButton_zoom_left;
    btn_zoom_right=ui->toolButton_zoom_right;
    btn_zoom_extends=ui->toolButton_zoom_extends;
    btn_zoom_plus=ui->toolButton_zoom_plus;
    btn_zoom_min=ui->toolButton_zoom_min;
    btn_zoom_3d=ui->toolButton_zoom_3d;
}

OcctQtControl::~OcctQtControl()
{
    delete ui;
}

void OcctQtControl::on_pushButton_line_pressed()
{

}

void OcctQtControl::on_pushButton_circle_pressed()
{

}

void OcctQtControl::on_pushButton_arc_arc_pressed()
{

}






























