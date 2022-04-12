#ifndef ARCPOINTS_H
#define ARCPOINTS_H

#include <gp_Pnt.hxx>
#include <gp_Ax2.hxx>
#include <vector>
#include <ArcCenter.h>
#include "Types.h"

//! Just for info. Not used in this class.
#include "ElCLib/ElCLib.hxx"

//! This class has reverse engeneered code at some points with the help off the <ElCLib.hxx> class.
//! The function creates 3d arc points along the 3d arc curve.
//! This can be helpfull to calculate arc intersections with other primitives in other class.
class ArcPoints
{
public:
    ArcPoints(gp_Pnt arc_p0, gp_Pnt arc_p1, gp_Pnt arc_p2) : p0(arc_p0), p1(arc_p1), p2(arc_p2) {
        myCenter=ArcCenter(p0,p1,p2).Arc_cp();
        myRadius=ArcCenter(p0,p1,p2).Arc_radius();
    }

    //! Get arc center.
    gp_Pnt getCenter(){
        return myCenter;
    }

    //! Get arc radius.
    double getRadius(){
        return myRadius;
    }

    //! Borrowed from <ElCLib.hxx>
    double getCircleParameter(gp_Ax2 Pos, gp_Pnt P)
    {
        gp_Vec aVec(Pos.Location(), P);
        if (aVec.SquareMagnitude() < gp::Resolution())
            // coinciding points -> infinite number of parameters
            return 0.0;

        gp_Dir dir = Pos.Direction();
        // Project vector on circle's plane
        gp_XYZ aVProj = dir.XYZ().CrossCrossed(aVec.XYZ(), dir.XYZ());

        if (aVProj.SquareModulus() < gp::Resolution())
            return 0.0;

        // Angle between X direction and projected vector
        double Teta = (Pos.XDirection()).AngleWithRef(aVProj, dir);

        if(Teta < -1.e-16){
            Teta += M_PI+M_PI;
        } else if (Teta < 0){
            Teta = 0;
        }
        return Teta;
    }

    //! Get 3d arc orientation.
    gp_Ax2 getOrientation(){
        double x1,y1,z1,x2,y2,z2,x3,y3,z3;
        p0.Coord(x1,y1,z1);
        p1.Coord(x2,y2,z2);
        p2.Coord(x3,y3,z3);
        gp_Dir Dir1(x2-x1,y2-y1,z2-z1);
        gp_Dir Dir2(x3-x2,y3-y2,z3-z2);
        gp_Dir Dir3 = Dir1.Crossed(Dir2);

        gp_Ax2 ArcPosition(myCenter,Dir3,Dir1);
        return ArcPosition;
    }

    //! The same as getCircleparameter, this one already includes getOrientation.
    double getCirlcleParameterFromPoint(gp_Pnt thePoint){
        return getCircleParameter(getOrientation(),thePoint);
    }

    gp_Pnt getPointFromCircleParameter(gp_Pnt a, gp_Pnt b, double Uinput){
        //! Max circle value is endpoint.
        //gp_Circ C(ArcPos,radius);
        double U_start = getCircleParameter(getOrientation(),a);
        double U_end = getCircleParameter(getOrientation(),b);

        //! When cirlce end < start add a full circle.
        if(U_end<U_start){
            U_end+=2*M_PI;
        }

        gp_XYZ XDir = getOrientation().XDirection().XYZ();
        gp_XYZ YDir = getOrientation().YDirection().XYZ();
        gp_XYZ PLoc = getOrientation().Location  ().XYZ();
        double A1 = myRadius * cos(Uinput);
        double A2 = myRadius * sin(Uinput);

        gp_Pnt result;
        result.SetX(A1 * XDir.X() + A2 * YDir.X() + PLoc.X());
        result.SetY(A1 * XDir.Y() + A2 * YDir.Y() + PLoc.Y());
        result.SetZ(A1 * XDir.Z() + A2 * YDir.Z() + PLoc.Z());

        return result;
    }

    //! The division is the resolution, a division of 50, gives back 51 points.
    //! Get 3d arc points along the curve, given a 3p_arc.
    std::vector<gp_Pnt> getPoints(unsigned int division, bool debug){

        //! Point storage container.
        std::vector<gp_Pnt> pvec;

        //! Max circle value is endpoint.
        //gp_Circ C(ArcPos,radius);
        double U_start = getCircleParameter(getOrientation(),p0);   if(debug){std::cout<<"U_start:"<<U_start<<std::endl;}
        double U_end = getCircleParameter(getOrientation(),p2);     if(debug){std::cout<<"U_endt:"<<U_end<<std::endl;}

        //! When cirlce end < start add a full circle.
        if(U_end<U_start){
            U_end+=2*M_PI;
        }

        double increment= (U_end-U_start)/division;

        for(double i=U_start; i<U_end; i+=increment){

            gp_XYZ XDir = getOrientation().XDirection().XYZ();
            gp_XYZ YDir = getOrientation().YDirection().XYZ();
            gp_XYZ PLoc = getOrientation().Location  ().XYZ();
            double A1 = myRadius * cos(i);
            double A2 = myRadius * sin(i);

            gp_Pnt result;
            result.SetX(A1 * XDir.X() + A2 * YDir.X() + PLoc.X());
            result.SetY(A1 * XDir.Y() + A2 * YDir.Y() + PLoc.Y());
            result.SetZ(A1 * XDir.Z() + A2 * YDir.Z() + PLoc.Z());
            pvec.push_back(result);
            if(debug){
                std::cout<<"p.x:"<<result.X()<<" p.y:"<<result.Y()<<" p.z:"<<result.Z()<<std::endl;
            }
        }

        //! Last point.
        gp_XYZ XDir = getOrientation().XDirection().XYZ();
        gp_XYZ YDir = getOrientation().YDirection().XYZ();
        gp_XYZ PLoc = getOrientation().Location  ().XYZ();
        double A1 = myRadius * cos(U_end);
        double A2 = myRadius * sin(U_end);

        gp_Pnt result;
        result.SetX(A1 * XDir.X() + A2 * YDir.X() + PLoc.X());
        result.SetY(A1 * XDir.Y() + A2 * YDir.Y() + PLoc.Y());
        result.SetZ(A1 * XDir.Z() + A2 * YDir.Z() + PLoc.Z());
        pvec.push_back(result);
        if(debug){
            std::cout<<"p.x:"<<result.X()<<" p.y:"<<result.Y()<<" p.z:"<<result.Z()<<std::endl;
        }

        return pvec;
    }

private:
    gp_Pnt p0,p1,p2;
    double myRadius=0;
    gp_Pnt myCenter;
};

#endif // ARCPOINTS_H
