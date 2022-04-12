#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "Interface.h"

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

            //if(!oneshot){
            //! Inputs:
            //!
            gp_Pnt pa0_in{0,0,50};
            gp_Pnt pa1_in{50,55,0};
            gp_Pnt pa2_in{100,0,-50};
            gp_Pnt pb0_in{0,100,0};
            gp_Pnt pb1_in{50,55,0};
            gp_Pnt pb2_in{100,100,0};


            //! Create a pointer.
            OBJECT *Obj;

            //! Create a new object.
            Obj = new OBJECT(arc_3p,pa0_in,pa1_in,pa2_in);
            occt_viewer->show_shape(Obj->getShape(Quantity_NOC_RED,AIS_WireFrame,2,0));
            gp_Pnt CenterA=Obj->getValues().getArcCenter();
            //! CenterPoint
            Obj = new OBJECT(sphere,CenterA,2);
            occt_viewer->show_shape(Obj->getShape(Quantity_NOC_WHITE,AIS_Shaded,1,0));
            //! Surface
            Obj = new OBJECT(sphere,CenterA,CenterA.Distance(pa0_in));
            occt_viewer->show_shape(Obj->getShape(Quantity_NOC_WHITE,AIS_Shaded,1,0.95));
            Obj = new OBJECT(triangle,pa0_in,pa1_in,pa2_in);
            occt_viewer->show_shape(Obj->getShape());
            Obj = new OBJECT(plane,pa0_in,pa1_in,pa2_in);
            occt_viewer->show_shape(Obj->getShape(Quantity_NOC_GRAY,AIS_Shaded,1,0.95));


            Obj = new OBJECT(arc_3p,pb0_in,pb1_in,pb2_in);
            occt_viewer->show_shape(Obj->getShape(Quantity_NOC_BLUE,AIS_WireFrame,2,0));
            gp_Pnt CenterB=Obj->getValues().getArcCenter();
            //! CenterPoint.
            Obj = new OBJECT(sphere,CenterB,2);
            occt_viewer->show_shape(Obj->getShape(Quantity_NOC_WHITE,AIS_Shaded,1,0));
            //! Surface.
            Obj = new OBJECT(sphere,CenterB,CenterB.Distance(pb0_in));
            occt_viewer->show_shape(Obj->getShape(Quantity_NOC_WHITE,AIS_Shaded,1,0.95));
            Obj = new OBJECT(triangle,pb0_in,pb1_in,pb2_in);
            occt_viewer->show_shape(Obj->getShape());
            Obj = new OBJECT(plane,pb0_in,pb1_in,pb2_in);
            occt_viewer->show_shape(Obj->getShape(Quantity_NOC_GRAY,AIS_Shaded,1,0.95));

            //! Line CenterA to CenterB

            Obj = new OBJECT(line,CenterA,CenterB);
            occt_viewer->show_shape(Obj->getShape(Quantity_NOC_CYAN,AIS_WireFrame,2,0));


            int count=0;
            int division=50;
            gp_Pnt pa00_out,pa01_out,pa02_out, pb00_out,pb01_out,pb02_out, pa0i,pb0i;
             gp_Pnt pa10_out,pa11_out,pa12_out, pb10_out,pb11_out,pb12_out, pa1i,pb1i;
//loop:


            ArcArcIntersect(pa0_in,pa1_in,pa2_in,pb0_in,pb1_in,pb2_in).getCloserArcs(
                        pa00_out,pa01_out,pa02_out,    //! New arc A0.
                        pa10_out,pa11_out,pa12_out,
                        pb00_out,pb01_out,pb02_out,    //! New arc B.
                        pb10_out,pb11_out,pb12_out,
                        pa0i,pb0i,                    //! Closest points.
                         pa1i,pb1i,                    //! Closest points.
                        division);                  //! Resolution to split up a arc in segments.

            //! Above output can give duplicate points. Therefore check for duplicates.

            //! Draw the above result.
            Obj = new OBJECT(arc_3p,pa00_out,pa01_out,pa02_out);
            occt_viewer->show_shape(Obj->getShape(Quantity_NOC_AZURE3,AIS_WireFrame,5,0));
            Obj = new OBJECT(arc_3p,pa10_out,pa11_out,pa12_out);
            occt_viewer->show_shape(Obj->getShape(Quantity_NOC_AZURE3,AIS_WireFrame,5,0));

            Obj = new OBJECT(arc_3p,pb00_out,pb01_out,pb02_out);
            occt_viewer->show_shape(Obj->getShape(Quantity_NOC_AZURE3,AIS_WireFrame,5,0));
            Obj = new OBJECT(arc_3p,pb10_out,pb11_out,pb12_out);
            occt_viewer->show_shape(Obj->getShape(Quantity_NOC_AZURE3,AIS_WireFrame,5,0));

            //! Draw intersetions.
            Obj = new OBJECT(sphere,pa0i,1);
            occt_viewer->show_shape(Obj->getShape(Quantity_NOC_GREEN,AIS_Shaded,1,0));
            Obj = new OBJECT(sphere,pa1i,1);
            occt_viewer->show_shape(Obj->getShape(Quantity_NOC_GREEN,AIS_Shaded,1,0));

            Obj = new OBJECT(sphere,pb0i,1);
            occt_viewer->show_shape(Obj->getShape(Quantity_NOC_RED,AIS_Shaded,1,0));
            Obj = new OBJECT(sphere,pb1i,1);
            occt_viewer->show_shape(Obj->getShape(Quantity_NOC_RED,AIS_Shaded,1,0));


            double dist=pa0i.Distance(pb0i);
            std::cout<<"distance pai-pbi: "<<dist<<std::endl;
//            if(dist>0.006){
//                pa0_in=pa0_out;
//                pa1_in=pa1_out;
//                pa2_in=pa2_out;

//                pb0_in=pb0_out;
//                pb1_in=pb1_out;
//                pb2_in=pb2_out;
//                count++;
//                if(count<3){
//                    std::cout<<"count:"<<count<<std::endl;
//                    goto loop;
//                } else {
//                    std::cout<<"out of scope"<<std::endl;
//                }
//            } else {
//                std::cout<<"intersection is ok"<<std::endl;
//            }

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


//            int count=0;
//            loop:

//            ArcArcIntersect(pa0_in,pa1_in,pa2_in,pb0_in,pb1_in,pb2_in).getCloserArcs(
//                        pa0_out,pa1_out,pa2_out,    //! New arc A.
//                        pb0_out,pb1_out,pb2_out,    //! New arc B.
//                        pai,pbi,                    //! Closest points.
//                        division);                  //! Resolution to split up a arc in segments.


//            //! Draw the above result.
//            Obj = new OBJECT(arc_3p,pa0_out,pa1_out,pa2_out);
//            occt_viewer->show_shape(Obj->getShape(Quantity_NOC_AZURE3,AIS_WireFrame,5,0));

//            Obj = new OBJECT(arc_3p,pb0_out,pb1_out,pb2_out);
//            occt_viewer->show_shape(Obj->getShape(Quantity_NOC_AZURE3,AIS_WireFrame,5,0));

//            //! Draw intersetions.
//            Obj = new OBJECT(sphere,pai,1);
//            occt_viewer->show_shape(Obj->getShape(Quantity_NOC_AZURE4,AIS_Shaded,1,0));

//            Obj = new OBJECT(sphere,pbi,1);
//            occt_viewer->show_shape(Obj->getShape(Quantity_NOC_AZURE4,AIS_Shaded,1,0));


//            double dist=pai.Distance(pbi);
//            std::cout<<"distance pai-pbi: "<<dist<<std::endl;
//            if(dist>0.006){
//                pa0_in=pa0_out;
//                pa1_in=pa1_out;
//                pa2_in=pa2_out;

//                pb0_in=pb0_out;
//                pb1_in=pb1_out;
//                pb2_in=pb2_out;
//                count++;
//                if(count<3){
//                    std::cout<<"count:"<<count<<std::endl;
//                    goto loop;
//                } else {
//                    std::cout<<"out of scope"<<std::endl;
//                }
//            } else {
//                std::cout<<"intersection is ok"<<std::endl;
//            }
















