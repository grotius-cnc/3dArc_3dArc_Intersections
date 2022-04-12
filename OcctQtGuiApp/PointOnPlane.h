#ifndef POINTONPLANE_H
#define POINTONPLANE_H

#include "iostream"
#include "gp_Pnt.hxx"

class PointOnPlane
{
public:
    //! 3D Plane points             : p1,p2,p3.
    //! Point to check on plane     : pi.
    PointOnPlane(gp_Pnt _p1, gp_Pnt _p2, gp_Pnt _p3, gp_Pnt _pi) : p1(_p1), p2(_p2), p3(_p3), pi(_pi)  {}

    //! Function to find equation of plane.
    //! https://www.geeksforgeeks.org/program-to-check-whether-4-points-in-a-3-d-plane-are-coplanar/
    bool IsOnPlane(bool debug){
        double a1 = p2.X() - p1.X();
        double b1 = p2.Y() - p1.Y();
        double c1 = p2.Z() - p1.Z();
        double a2 = p3.X() - p1.X();
        double b2 = p3.Y() - p1.Y();
        double c2 = p3.Z() - p1.Z();
        double a = b1 * c2 - b2 * c1 ;
        double b = a2 * c1 - a1 * c2 ;
        double c = a1 * b2 - b1 * a2 ;
        double d = (- a * p1.X() - b * p1.Y() - c * p1.Z()) ;

        //! equation of plane is: a*x + b*y + c*z = 0 #

        //! checking if the 4th point satisfies
        //! the above equation
        if(a * pi.X() + b * pi.Y() + c * pi.Z() + d ==0){
            if(debug){std::cout<<"Coplanar (on plane)"<<std::endl;}
            return true;
        } else {
            if(debug){std::cout<<"Non Coplanar (not on plane)"<<std::endl;}
            return false;
        }
    }
private:
    gp_Pnt p1,p2,p3,pi;
};

#endif // POINTONPLANE_H
