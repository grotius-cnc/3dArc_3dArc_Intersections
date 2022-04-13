#ifndef POINTONARC_H
#define POINTONARC_H

#include <gp_Pnt.hxx>
#include <ArcCenter.h>
#include <gp_Ax2.hxx>

//! Checks if a point in 3d space is on a arc in 3d space.
class PointOnArc
{
public:
    PointOnArc(gp_Pnt p0_arc, gp_Pnt p1_arc, gp_Pnt p2_arc, gp_Pnt thePoint, double tollerance): p0(p0_arc), p1(p1_arc), p2(p2_arc), pi(thePoint), myTol(tollerance) {
        myCenter=ArcCenter(p0,p1,p2).Arc_cp(0);
        myRadius=myCenter.Distance(p0);
    };

    //! Print with debug output.
    bool isOnArc(bool debug){
        myDebug=debug;
        return isOnArc();
    };

    //! Normal.
    bool isOnArc(){

        double U=getCirlcleParameterFromPoint(pi);  std::cout<<"U:"<<U<<std::endl;
        double U0=getCirlcleParameterFromPoint(p0); std::cout<<"U0:"<<U0<<std::endl;
        double U1=getCirlcleParameterFromPoint(p1); std::cout<<"U1:"<<U1<<std::endl;
        double U2=getCirlcleParameterFromPoint(p2); std::cout<<"U2:"<<U2<<std::endl;

        if(U1>U0 && U2>U1 && U>=U0 && U<=U2){
            return 1;
        }
        if(U1<U0 && U2<U1 && U<=U0 && U>=U2){
            return 1;
        }

            return 0;

    };
private:

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

    gp_Pnt getPointFromCircleParameter(gp_Pnt arcStart, gp_Pnt arcEnd, double Uinput){
        //! Max circle value is endpoint.
        //gp_Circ C(ArcPos,radius);
        double U_start = getCircleParameter(getOrientation(),arcStart);
        double U_end = getCircleParameter(getOrientation(),arcEnd);

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

    gp_Pnt p0, p1, p2, pi, myCenter;
    double myTol, myRadius;
    bool myDebug=0;
};

#endif // POINTONARC_H
