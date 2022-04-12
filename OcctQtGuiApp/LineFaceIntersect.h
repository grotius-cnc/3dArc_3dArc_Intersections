#ifndef LINEFACEINTERSECT_H
#define LINEFACEINTERSECT_H

/*
#include "ElCLib/ElCLib.hxx"
#include "GeomAPI_IntCS.hxx"
#include "Geom_Curve.hxx"
#include "Geom_Surface.hxx"
#include "TopoDS_Face.hxx"
#include "BRepBuilderAPI_MakeFace.hxx"
#include "gp_Cylinder.hxx"
#include "BRepAdaptor_HSurface.hxx"
#include "GC_MakeLine.hxx"

//! Create a line, GC_ has different curve's.
gp_Pnt depart(-200,0,0);
gp_Dir direction(200,0,0);
GC_MakeLine mkLine(depart, direction);

//! Create the raw material cube surface.
gp_Cylinder cil(gp::XOY(),100);
TopoDS_Face cylinder_face = BRepBuilderAPI_MakeFace(cil);

//! Do a line-face intersection.
BRepAdaptor_Surface surface(cylinder_face);
const GeomAdaptor_Surface& geomAdapSurf = surface.Surface();
const Handle(Geom_Surface)& geomSurf = geomAdapSurf.Surface();

GeomAPI_IntCS inCS;
inCS.Perform(mkLine.Value(),geomSurf);

if (inCS.IsDone()){
    if (inCS.NbPoints() == 0){
        std::cout<<"no intersections."<<std::endl;
    } else {
        for(int i=1; i<inCS.NbPoints()+1; i++){
            gp_Pnt p = inCS.Point(i);
            std::cout<<"Px:"<<p.X()<< " Py:" << p.Y() << " Pz:" << p.Z() <<std::endl;
        }
    }
};

Output :
Px:100.000000 Py:0.000000 Pz:0.000000
Px:-100.000000 Py:0.000000 Pz:0.000000

https://dev.opencascade.org/content/line-face-intersection
https://github.com/grotius-cnc/hal-core/blob/main/src/hal/components/matrix/cpp_interface/libocct/draw_primitives.cpp Line 592
*/

#endif // LINEFACEINTERSECT_H
