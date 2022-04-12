#ifndef LINELINEINTERSECT_H
#define LINELINEINTERSECT_H

#include "gp_Pnt.hxx"
#include <vector>
#include "Types.h"

class LineLineIntersect
{
public:
    //! Line A: p1,p2   Line B: p2,p3
    LineLineIntersect(gp_Pnt _p0, gp_Pnt _p1, gp_Pnt _p2, gp_Pnt _p3) : p0(_p0), p1(_p1), p2(_p2), p3(_p3)  {}

    //! Gives you the lenght of the closest path between the 2 compared lines.
    bool getClosestLenght(double &lenght, std::pair<gp_Pnt,gp_Pnt> &pair){
        gp_Pnt p13,p43,p21;
        const double EPS=0.0001;
        double d1343,d4321,d1321,d4343,d2121;
        double numer,denom;

        p13.SetX(p0.X() - p2.X());
        p13.SetY(p0.Y() - p2.Y());
        p13.SetZ(p0.Z() - p2.Z());
        p43.SetX(p3.X() - p2.X());
        p43.SetY(p3.Y() - p2.Y());
        p43.SetZ(p3.Z() - p2.Z());
        if (abs(p43.X()) < EPS && abs(p43.Y()) < EPS && abs(p43.Z()) < EPS)
            return(false);
        p21.SetX(p1.X() - p0.X());
        p21.SetY(p1.Y() - p0.Y());
        p21.SetZ(p1.Z() - p0.Z());
        if (abs(p21.X()) < EPS && abs(p21.Y()) < EPS && abs(p21.Z()) < EPS)
            return(false);

        d1343 = p13.X() * p43.X() + p13.Y() * p43.Y() + p13.Z() * p43.Z();
        d4321 = p43.X() * p21.X() + p43.Y() * p21.Y() + p43.Z() * p21.Z();
        d1321 = p13.X() * p21.X() + p13.Y() * p21.Y() + p13.Z() * p21.Z();
        d4343 = p43.X() * p43.X() + p43.Y() * p43.Y() + p43.Z() * p43.Z();
        d2121 = p21.X() * p21.X() + p21.Y() * p21.Y() + p21.Z() * p21.Z();

        denom = d2121 * d4343 - d4321 * d4321;
        if (abs(denom) < EPS)
            return(false);
        numer = d1343 * d4321 - d1321 * d4343;

        double mua = numer / denom;
        double mub = (d1343 + d4321 * (mua)) / d4343;

        pa.SetX(p0.X() + mua * p21.X());
        pa.SetY(p0.Y() + mua * p21.Y());
        pa.SetZ(p0.Z() + mua * p21.Z());
        pb.SetX(p2.X() + mub * p43.X());
        pb.SetY(p2.Y() + mub * p43.Y());
        pb.SetZ(p2.Z() + mub * p43.Z());

        //! Check if pa is on line p1-p2.
        double l1=sqrt(pow(p0.X()-pa.X(),2)+pow(p0.Y()-pa.Y(),2)+pow(p0.Z()-pa.Z(),2));
        double l2=sqrt(pow(p1.X()-pa.X(),2)+pow(p1.Y()-pa.Y(),2)+pow(p1.Z()-pa.Z(),2));
        double l3=sqrt(pow(p1.X()-p0.X(),2)+pow(p1.Y()-p0.Y(),2)+pow(p1.Z()-p0.Z(),2));
        if(l3==l1+l2){
            std::cout<<"pa is on the line p1-p2"<<std::endl;
        }

        //! Check if pb is on line p3-p4.
        double l4=sqrt(pow(p2.X()-pb.X(),2)+pow(p2.Y()-pb.Y(),2)+pow(p2.Z()-pb.Z(),2));
        double l5=sqrt(pow(p3.X()-pb.X(),2)+pow(p3.Y()-pb.Y(),2)+pow(p3.Z()-pb.Z(),2));
        double l6=sqrt(pow(p3.X()-p2.X(),2)+pow(p3.Y()-p2.Y(),2)+pow(p3.Z()-p2.Z(),2));
        if(l6==l4+l5){
            std::cout<<"pb is on the line p3-p4"<<std::endl;
        }

        //! Result.
        if(l3>(l1+l2)-EPS && l3<(l1+l2)+EPS && l6>(l4+l5)-EPS && l6<(l4+l5)+EPS){
            std::cout<<"pa.x:"<<pa.X()<<" pa.y:"<<pa.Y()<<" pa.z:"<<pa.Z()<<std::endl;
            std::cout<<"pb.x:"<<pb.X()<<" pb.y:"<<pb.Y()<<" pb.z:"<<pb.Z()<<std::endl;

            //! Shortest imaginairy line lenght between line p1p2 & line p3p4.
            lenght=sqrt(pow(pb.X()-pa.X(),2)+pow(pb.Y()-pa.Y(),2)+pow(pb.Z()-pa.Z(),2));
            std::setprecision(3);
            std::cout<<std::fixed<<"pa-pb lenght:"<<lenght<<std::endl;

            pair.first=pa;
            pair.second=pb;

            return true;
        }
        return false;
    }

private:
    gp_Pnt p0,p1,p2,p3,pa,pb;
};

#endif // LINELINEINTERSECT_H
















