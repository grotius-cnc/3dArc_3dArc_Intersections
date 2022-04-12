#ifndef OCCTQTCONTROL_H
#define OCCTQTCONTROL_H

#include <QDialog>
#include <QLabel>
#include <QToolButton>
#include <QSlider>

namespace Ui {
class OcctQtControl;
}

class OcctQtControl : public QDialog
{
    Q_OBJECT

public:
    explicit OcctQtControl(QWidget *parent = nullptr);
    ~OcctQtControl();

    QLabel *lbl_x,*lbl_y,*lbl_z;
    QToolButton *btn_zoom_top, *btn_zoom_bottom, *btn_zoom_front, *btn_zoom_back, *btn_zoom_left, *btn_zoom_right, *btn_zoom_extends, *btn_zoom_plus, *btn_zoom_min, *btn_zoom_3d;

private slots:
    void on_pushButton_circle_pressed();

    void on_pushButton_line_pressed();

    void on_pushButton_arc_arc_pressed();

private:
    Ui::OcctQtControl *ui;
};

#endif // OCCTQTCONTROL_H
