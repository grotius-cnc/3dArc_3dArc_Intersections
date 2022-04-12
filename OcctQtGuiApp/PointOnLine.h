#ifndef POINTONLINE_H
#define POINTONLINE_H

#include <gp_Pnt.hxx>

//! Checks if a point in 3d space is on a line in 3d space.
class PointOnLine
{
public:
    PointOnLine(gp_Pnt p0_line, gp_Pnt p1_line, gp_Pnt thePoint, double tollerance): p0(p0_line), p1(p1_line), p2(thePoint), myTol(tollerance) {};

    //! Print with debug output.
    bool isOnLine(bool debug){
        myDebug=debug;
        return isOnLine();
    };

    //! Normal.
    bool isOnLine(){

        double l0=sqrt(pow(p0.X()-p2.X(),2)+pow(p0.Y()-p2.Y(),2)+pow(p0.Z()-p2.Z(),2));
        double l1=sqrt(pow(p1.X()-p2.X(),2)+pow(p1.Y()-p2.Y(),2)+pow(p1.Z()-p2.Z(),2));
        double ltot=sqrt(pow(p1.X()-p0.X(),2)+pow(p1.Y()-p0.Y(),2)+pow(p1.Z()-p0.Z(),2));

        //! Result.
        if(ltot>((l0+l1)-myTol) && ltot<((l0+l1)+myTol)){
            if(myDebug){std::cout<<"point is on line"<<std::endl;}
            return 1;
        } else {
            if(myDebug){std::cout<<"point is not on the line"<<std::endl;}
            return 0;
        }
        return 0;
    };
private:

    gp_Pnt p0, p1, p2;
     double myTol;
    bool myDebug=0;
};

#endif // POINTONLINE_H
