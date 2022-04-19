#ifndef GENERALINTERSECT_H
#define GENERALINTERSECT_H

#include "Types.h"
#include <ArcPoints.h>
#include <LineArcIntersect.h>
#include <ArcCenter.h>

//! To be coded.
//!
//!
class GeneralIntersect
{
public:
    GeneralIntersect(gp_Pnt arcA_p0, gp_Pnt arcA_p1, gp_Pnt arcA_p2, gp_Pnt arcB_p0, gp_Pnt arcB_p1, gp_Pnt arcB_p2)
        : pa0(arcA_p0), pa1(arcA_p1), pa2(arcA_p2), pb0(arcB_p0), pb1(arcB_p1), pb2(arcB_p2) { }

private:
    gp_Pnt pa0, pa1, pa2, pb0, pb1, pb2;
};

#endif // GENERALINTERSECT_H



/*

            OBJECT *OA = new OBJECT(arc_3p,{{0,0,0},{50,50,0},{100,0,0}});
            occt_viewer->show_shape(OA->getShape());

            OBJECT *OB = new OBJECT(arc_3p,{{50,0,-50},{40,50,0},{50,100,-50}});
            occt_viewer->show_shape(OB->getShape());


            gp_PntVec A = ArcPoints({0,0,0},{50,50,0},{100,0,0}).getPoints(5,1);
            gp_PntVec B = ArcPoints({50,0,-50},{40,50,0},{50,100,-50}).getPoints(5,1);

            //! Draw lines for first array.
            for(unsigned int i=0; i<A.size()-1; i++){
                TopoDS_Edge aEdge = BRepBuilderAPI_MakeEdge(A[i],A[i+1]);
                Handle(AIS_Shape) aShape=new AIS_Shape(aEdge);
                aShape->SetDisplayMode(AIS_Shaded);
                occt_viewer->show_shape(aShape);
            }
            //! Draw lines for second array.
            for(unsigned int i=0; i<B.size()-1; i++){
                TopoDS_Edge aEdge = BRepBuilderAPI_MakeEdge(B[i],B[i+1]);
                Handle(AIS_Shape) aShape=new AIS_Shape(aEdge);
                aShape->SetDisplayMode(AIS_Shaded);
                occt_viewer->show_shape(aShape);
            }


            std::pair<gp_Pnt,gp_Pnt> pair;
            gp_Pnt pa,pb;
            unsigned int i1,j1;
            double result=INFINITY;
            double lenght=INFINITY;
            double U1,U2,U3,U4;
            for(unsigned int i=0; i<A.size()-1; i++){
                for(unsigned int j=0; j<B.size()-1; j++){
                    bool ok= LineLineIntersect(A[i],A[i+1],B[j],B[j+1]).getClosestLenght(result,pair);
                    if(result<lenght && ok){
                        lenght=result;
                        i1=i;
                        j1=j;
                        pa=pair.first;
                        pb=pair.second;

                        //! What are the circleparameters?
                        U1=ArcPoints({0,0,0},{50,50,0},{100,0,0}).getCirlcleParameterFromPoint(A[i]);
                        U2=ArcPoints({0,0,0},{50,50,0},{100,0,0}).getCirlcleParameterFromPoint(A[i+1]);

                        U3=ArcPoints({50,0,-50},{40,50,0},{50,100,-50}).getCirlcleParameterFromPoint(B[j]);
                        U4=ArcPoints({50,0,-50},{40,50,0},{50,100,-50}).getCirlcleParameterFromPoint(B[j+1]);
                    }
                }
            }
            std::cout<<"intersection at i: "<<i1<<" j: "<<j1<<" lenght: "<<lenght<<std::endl;

            //! Calculate new midpoint for the section.
            double U12=(U1+U2)/2;
            double U34=(U3+U4)/2;
            gp_Pnt P12=ArcPoints({0,0,0},{50,50,0},{100,0,0}).getPointFromCircleParameter(A[i1],A[i1+1],U12);
            gp_Pnt P34=ArcPoints({50,0,-50},{40,50,0},{50,100,-50}).getPointFromCircleParameter(B[j1],B[j1+1],U34);

            //! Draw midpoints.
            TopoDS_Shape aSphere = BRepPrimAPI_MakeSphere(P12,1).Shape();
            Handle(AIS_Shape) aShape=new AIS_Shape(aSphere);
            aShape->SetDisplayMode(AIS_Shaded);
            aShape->SetColor(Quantity_NOC_BLUE);
            occt_viewer->show_shape(aShape);

            aSphere = BRepPrimAPI_MakeSphere(P34,1).Shape();
            aShape=new AIS_Shape(aSphere);
            aShape->SetColor(Quantity_NOC_BLUE);
            aShape->SetDisplayMode(AIS_Shaded);
            occt_viewer->show_shape(aShape);
            */











