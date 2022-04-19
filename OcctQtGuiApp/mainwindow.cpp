#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "Interface.h"
#include "PointOnArc.h"
#include "ArcPoints.h"
#include "Types.h"

//! Creator : Skynet Cyberdyne.
//! Date    : 01-2021.
//!
//! The occt_viewer widget has it's own opengl interface, separated from qt opengl to
//! avoid opengl entanglement.
//!
//! This widget has several implementation examples:
//!
//! 1. Xyz mouse coordinates mapped to the occt environment.
//! 2. Transparant qt widget overlay.
//! 3. Viewports, 3d, top, bottom, left, right, front, back.
//! 4. Zoom to fit, zoom +, zoom -
//! 5. Create a shape and set tranceparancy level.
//! 6. Show shapes as wireframe or as shaded object.
//! 7. Show or hide 3d navigation box.
//! 8. Show or hide triedron.
//! 9. Show shape in orthographic or perspective mode.
//! 10. Show or hide shape boundary lines.
//! 11. Print the actual opencascade performance.. // OcctQtViwer::show_specs;
//!
//! This example could be entirely be brought into one upper widget if you want to do so.
//!
//! 1.0 aMainWindow
//!     2.O OcctQt upper widget -> QWidget
//!         2.1 OcctQtcontrols  -> Qt opengl
//!         2.2 OcctQtViewer    -> Occt opengl
//!         2.3 Tranceparancy

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //! Add the occt_viewer widget.
    QGridLayout *layout=new QGridLayout(occt_viewer);
    //! Add the occt_control widget.
    layout->addWidget(occt_controls,0,0,Qt::AlignCenter);
    ui->gridLayout->addWidget(occt_viewer);

    const QColor color= ui->centralwidget->palette().color(QPalette::ColorRole::Window);
    occt_viewer->set_backgroundcolor(color.red(),color.green(),color.blue());

    connect(timer, &QTimer::timeout, this, &MainWindow::mainloop);
    timer->start(50);
}

//! Destructor.
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionwireframe_triggered()
{
    occt_viewer->show_as_wireframe();
}

void MainWindow::on_actionshaded_triggered()
{
    occt_viewer->show_as_shaded();
}

void MainWindow::on_actionboundary_show_triggered()
{
    occt_viewer->show_boundary();
}

void MainWindow::on_actionboundary_hide_triggered()
{
    occt_viewer->hide_boundary();
}

void MainWindow::on_actionorthographic_triggered()
{
    occt_viewer->set_orthographic();
}

void MainWindow::on_actionperspective_triggered()
{
    occt_viewer->set_perspective();
}

void MainWindow::on_actioncube_hide_triggered()
{
    occt_viewer->hide_cube();
}

void MainWindow::on_actioncube_show_triggered()
{
    occt_viewer->show_cube();
}

void MainWindow::on_actiontriedron_hide_triggered()
{
    occt_viewer->hide_triedron();
}

void MainWindow::on_actiontriedron_show_triggered()
{
    occt_viewer->show_triedron();
}

void MainWindow::on_actiontranceparancy_dialog_triggered()
{
    transparancy->show();
}

#include "ElCLib/ElCLib.hxx"
#include "GeomAPI_IntCS.hxx"
#include "GeomInt_IntSS.hxx"
#include "Geom_Curve.hxx"
#include "Geom_Surface.hxx"
#include "TopoDS_Face.hxx"
#include "BRepBuilderAPI_MakeFace.hxx"
#include "gp_Cylinder.hxx"
#include "BRepAdaptor_HSurface.hxx"
#include "GC_MakeLine.hxx"
#include <BRepPrimAPI_MakeSphere.hxx>

bool oneshot=0;

void MainWindow::mainloop(){

    //! Opencascade callback thread.
    //! This thread can be used to process occt localtransformations etc.
    if(!occt_viewer->View().IsNull()){

        occt_controls->lbl_x->setText(QString::number(occt_viewer->aMousePnt.X(),'f',3));
        occt_controls->lbl_y->setText(QString::number(occt_viewer->aMousePnt.Y(),'f',3));
        occt_controls->lbl_z->setText(QString::number(occt_viewer->aMousePnt.X(),'f',3));

        if(occt_controls->btn_zoom_extends->isDown()==true){
            occt_viewer->View()->FitAll(0.01,Standard_True);
        }
        if(occt_controls->btn_zoom_plus->isDown()==true){
            occt_viewer->UpdateZoom(1);
            occt_viewer->update();


            //! Inputs:
            gp_Pnt p0{50,50,0};
            gp_Pnt p1{0,0,0};
            gp_Pnt p2{50,-50,0};
            gp_Pnt p{0,0,0};

            OBJECT *aSpline = new OBJECT(spline,{p0,p1,p2});
            occt_viewer->show_shape(aSpline->getShape(Quantity_NOC_ALICEBLUE,AIS_Shaded,1,0.8));


        }
        if(occt_controls->btn_zoom_min->isDown()==true){
            occt_viewer->UpdateZoom(-1);
            occt_viewer->update();
        }
        if(occt_controls->btn_zoom_front->isDown()==true){
            occt_viewer->View()->SetProj(V3d_Yneg);
            occt_viewer->View()->FitAll(0.01,Standard_True);
        }
        if(occt_controls->btn_zoom_back->isDown()==true){
            occt_viewer->View()->SetProj(V3d_Ypos);
            occt_viewer->View()->FitAll(0.01,Standard_True);
        }
        if(occt_controls->btn_zoom_left->isDown()==true){
            occt_viewer->View()->SetProj(V3d_Xneg);
            occt_viewer->View()->FitAll(0.01,Standard_True);
        }
        if(occt_controls->btn_zoom_right->isDown()==true){
            occt_viewer->View()->SetProj(V3d_Xpos);
            occt_viewer->View()->FitAll(0.01,Standard_True);
        }
        if(occt_controls->btn_zoom_top->isDown()==true){
            occt_viewer->View()->SetProj(V3d_Zpos);
            occt_viewer->View()->FitAll(0.01,Standard_True);
        }
        if(occt_controls->btn_zoom_bottom->isDown()==true){
            occt_viewer->View()->SetProj(V3d_Zneg);
            occt_viewer->View()->FitAll(0.01,Standard_True);
        }
        if(occt_controls->btn_zoom_3d->isDown()==true){
            occt_viewer->View()->SetProj(V3d_TypeOfOrientation_Zup_AxoRight);
            occt_viewer->View()->FitAll(0.01,Standard_True);
        }
        if(transparancy->isVisible()){
            occt_viewer->set_tranceparancy(0.01*transparancy->value);
            //! This is done here, otherwise it will not do a live update.
            occt_viewer->View()->Redraw();
            occt_viewer->update();
        }
        if(!oneshot){
            occt_viewer->View()->SetProj(V3d_TypeOfOrientation_Zup_AxoRight);
            double value=0.01*Tranceparancy().value;
            occt_viewer->set_tranceparancy(value);
            occt_viewer->View()->FitAll(0.01,Standard_True);
            occt_viewer->View()->Redraw();
            oneshot=1;
        }
    }
}


















