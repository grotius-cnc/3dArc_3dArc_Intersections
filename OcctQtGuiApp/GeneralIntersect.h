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
        : pa0(arcA_p0), pa1(arcA_p1), pa2(arcA_p2), pb0(arcB_p0), pb1(arcB_p1), pb2(arcB_p2) {

        //! First arc circleparameters.
        U1=ArcPoints(pa0,pa1,pa2).getCirlcleParameterFromPoint(pa0);
        U2=ArcPoints(pa0,pa1,pa2).getCirlcleParameterFromPoint(pa2);

        //! Second arc circleparameters.
        U3=ArcPoints(pb0,pb1,pb2).getCirlcleParameterFromPoint(pb0);
        U4=ArcPoints(pb0,pb1,pb2).getCirlcleParameterFromPoint(pb2);

        //! Check if circle's are out of reach to hit each other.
        gp_Pnt CenterArcA=ArcPoints(pa0,pa1,pa2).getCenter();
        double RadiusArcA=arcA_p0.Distance(CenterArcA);
        gp_Pnt CenterArcB=ArcPoints(pb0,pb1,pb2).getCenter();
        double RadiusArcB=arcB_p0.Distance(CenterArcB);

        double CenterDistAB=CenterArcA.Distance(CenterArcB);

        if(CenterDistAB-(RadiusArcA+RadiusArcB)>0){
            std::cout<<"No intersections possible, arc's are out off reach."<<std::endl;
        }
        if(CenterDistAB==0){
            std::cout<<"No intersections possible, arc's are centered at same position."<<std::endl;
        }
    }

    //! Returns closer arc's from original arc's, nearer to the intersection point.
    //! A arc can intersect multiple times.
    int getCloserArcs(gp_Pnt &arcA0_p0, gp_Pnt  &arcA0_p1, gp_Pnt &arcA0_p2,
                      gp_Pnt &arcA1_p0, gp_Pnt  &arcA1_p1, gp_Pnt &arcA1_p2,
                      gp_Pnt &arcB0_p0, gp_Pnt  &arcB0_p1, gp_Pnt &arcB0_p2,
                      gp_Pnt &arcB1_p0, gp_Pnt  &arcB1_p1, gp_Pnt &arcB1_p2,
                      gp_Pnt &arcA0_intersection, gp_Pnt &arcB0_intersection,
                      gp_Pnt &arcA1_intersection, gp_Pnt &arcB1_intersection,
                      unsigned int division){

        std::vector<gp_Pnt> A = ArcPoints(pa0,pa1,pa2).getPoints(division,0);
        std::vector<gp_Pnt> B = ArcPoints(pb0,pb1,pb2).getPoints(division,0);


        std::pair<gp_Pnt,gp_Pnt> pair;
        unsigned int i1,j1;
        double max=999999999999999;
        double lenght;
        double U1,U2,U3,U4, U12,U34;

        //! Forward sweep.
        for(unsigned int i=0; i<A.size()-1; i++){
            for(unsigned int j=0; j<B.size()-1; j++){
                bool ok= LineLineIntersect(A[i],A[i+1],B[j],B[j+1]).getClosestLenght(lenght,pair);
                if(lenght<max && ok){
                    max=lenght;
                    i1=i;
                    j1=j;
                    arcA0_intersection=pair.first;
                    arcB0_intersection=pair.second;

                    //! What are the circleparameters?
                    U1=ArcPoints(pa0,pa1,pa2).getCirlcleParameterFromPoint(A[i]);
                    U2=ArcPoints(pa0,pa1,pa2).getCirlcleParameterFromPoint(A[i+1]);

                    U3=ArcPoints(pb0,pb1,pb2).getCirlcleParameterFromPoint(B[j]);
                    U4=ArcPoints(pb0,pb1,pb2).getCirlcleParameterFromPoint(B[j+1]);
                }
            }
        }

        std::cout<<"intersection at i: "<<i1<<" j: "<<j1<<" lenght intersection A to B: "<<lenght<<std::endl;
        std::setprecision(3);
        std::cout<<std::fixed<<"intersection A x:"<<pair.first.X()<<" y:"<<pair.first.Y()<<" z:"<<pair.first.Z()<<std::endl;
        std::cout<<std::fixed<<"intersection B x:"<<pair.second.X()<<" y:"<<pair.second.Y()<<" z:"<<pair.second.Z()<<std::endl;

        //! Calculate new midpoint for the arc section.
        U12=(U1+U2)/2;
        U34=(U3+U4)/2;
        arcA0_p1=ArcPoints(pa0,pa1,pa2).getPointFromCircleParameter(A[i1],A[i1+1],U12);
        arcB0_p1=ArcPoints(pb0,pb1,pb2).getPointFromCircleParameter(B[j1],B[j1+1],U34);

        arcA0_p0=A[i1];
        arcA0_p2=A[i1+1];

        arcB0_p0=B[j1];
        arcB0_p2=B[j1+1];

        //! Reverse arcs.
        A = ArcPoints(pa2,pa1,pa0).getPoints(division,0);
        B = ArcPoints(pb2,pb1,pb0).getPoints(division,0);

        //! Reset max.
         max=999999999999999;
        //! Backward sweep.
         for(unsigned int i=0; i<A.size()-1; i++){
             for(unsigned int j=0; j<B.size()-1; j++){
                bool ok= LineLineIntersect(A[i],A[i+1],B[j],B[j+1]).getClosestLenght(lenght,pair);
                if(lenght<max && ok){
                    max=lenght;
                    i1=i;
                    j1=j;
                    arcA1_intersection=pair.first;
                    arcB1_intersection=pair.second;

                    //! What are the circleparameters?
                    U1=ArcPoints(pa0,pa1,pa2).getCirlcleParameterFromPoint(A[i]);
                    U2=ArcPoints(pa0,pa1,pa2).getCirlcleParameterFromPoint(A[i+1]);

                    U3=ArcPoints(pb0,pb1,pb2).getCirlcleParameterFromPoint(B[j]);
                    U4=ArcPoints(pb0,pb1,pb2).getCirlcleParameterFromPoint(B[j+1]);
                }
            }
        }

        std::cout<<"BACKWARD SWEEP"<<std::endl;
        std::cout<<"intersection at i: "<<i1<<" j: "<<j1<<" lenght intersection A to B: "<<lenght<<std::endl;
        std::setprecision(3);
        std::cout<<std::fixed<<"intersection A x:"<<pair.first.X()<<" y:"<<pair.first.Y()<<" z:"<<pair.first.Z()<<std::endl;
        std::cout<<std::fixed<<"intersection B x:"<<pair.second.X()<<" y:"<<pair.second.Y()<<" z:"<<pair.second.Z()<<std::endl;

        //! Calculate new midpoint for the arc section.
        U12=(U1+U2)/2;
        U34=(U3+U4)/2;
        arcA1_p1=ArcPoints(pa0,pa1,pa2).getPointFromCircleParameter(A[i1],A[i1+1],U12);
        arcB1_p1=ArcPoints(pb0,pb1,pb2).getPointFromCircleParameter(B[j1],B[j1+1],U34);

        arcA1_p0=A[i1];
        arcA1_p2=A[i1+1];

        arcB1_p0=B[j1];
        arcB1_p2=B[j1+1];





        return 1;

    }

private:
    gp_Pnt pa0, pa1, pa2, pb0, pb1, pb2;
    double U1,U2,U3,U4;
};

#endif // GENERALINTERSECT_H



/*

            OBJECT *OA = new OBJECT(arc_3p,{{0,0,0},{50,50,0},{100,0,0}});
            occt_viewer->show_shape(OA->getShape());

            OBJECT *OB = new OBJECT(arc_3p,{{50,0,-50},{40,50,0},{50,100,-50}});
            occt_viewer->show_shape(OB->getShape());


            std::vector<gp_Pnt> A = ArcPoints({0,0,0},{50,50,0},{100,0,0}).getPoints(5,1);
            std::vector<gp_Pnt> B = ArcPoints({50,0,-50},{40,50,0},{50,100,-50}).getPoints(5,1);

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











