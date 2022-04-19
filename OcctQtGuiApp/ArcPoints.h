#ifndef ARCPOINTS_H
#define ARCPOINTS_H

#include <gp_Pnt.hxx>
#include <gp_Ax2.hxx>
#include <vector>
#include <algorithm>
#include <ArcCenter.h>
#include <PointOnPlane.h>
#include "Types.h"
#include "Geom_TrimmedCurve.hxx"
#include "GC_MakeArcOfCircle.hxx"
#include "gce_MakeCirc.hxx"

//! Just for info. Not used in this class.
#include "ElCLib/ElCLib.hxx"

//! Make conversion's easy:
#define toRadians M_PI/180.0
#define toDegrees (180.0/M_PI)

//! This class has reverse engeneered code at some points with the help off the <ElCLib.hxx> class.
//! The function creates 3d arc points along the 3d arc curve.
//! This can be helpfull to calculate arc intersections with other primitives in other class.
class ArcPoints
{
public:
    ArcPoints(gp_Pnt arc_p0, gp_Pnt arc_p1, gp_Pnt arc_p2) : p0(arc_p0), p1(arc_p1), p2(arc_p2) {
        myCenter=ArcCenter(p0,p1,p2).Arc_cp();
        myRadius=ArcCenter(p0,p1,p2).Arc_radius();
        myArcOfCircle = GC_MakeArcOfCircle(p0,p1,p2);
        myUstart=myArcOfCircle->FirstParameter();
        myUend=myArcOfCircle->LastParameter();
        gce_MakeCirc gce_circle(p0,p1,p2);
        myGpCircle=(gce_circle.Value());
    }

    //! Get arc center.
    gp_Pnt getCenter(){
        return myCenter;
    }

    //! Get arc radius.
    double getRadius(){
        return myRadius;
    }

    //! Divide a arc into equal divided points lying on the arc circumfence.
    gp_PntVec getPoints(unsigned int division, bool debug){

        //! For debug.
        std::setprecision(3);

        double increment= (myUend-myUstart)/division;
        gp_PntVec pvec;
        for(double i=myUstart; i<=myUend; i+=increment){
            gp_Pnt p;
            myArcOfCircle->D0(i,p);
            pvec.push_back(p);
            if(debug){
                std::cout<<std::fixed<<"Point i:"<<i<<" x:"<<p.X()<<" y:"<<p.Y()<<" z:"<<p.Z()<<std::endl;
            }
        }
        return pvec;
    }

    //! If a arc intersection is done, the intersection points are not ordered from Ustart to Uend.
    //! We need to do sort this, to be able to create new sub arc's when the basic arc curve is trimmed into pieces.
    bool sortIntersections(gp_PntVec &theIntersections, std::vector<double> &Uvec, bool debug){
        //! A Vector that holds the retrieved U value of the intersection point and the point itself.

        //! Fill in the data.
        for(unsigned int i=0; i<theIntersections.size(); i++){
              double U=ElCLib().Parameter(myGpCircle,theIntersections[i]);
              Uvec.push_back(U);
              if(debug){
                    std::cout<<"Uvec in, non sorted :"<<i<<" U value:"<<U<<std::endl;
              }
        }

        //! Sort the vector for U. Sorting from lowest U to higher U value. Where U is the circleparameter.
        std::sort(Uvec.begin(),Uvec.end());

        //! Clear vector to be refilled again with sorted values.
        theIntersections.clear();

        //! Sorted result conversed to points again.
        for(unsigned int i=0; i<Uvec.size(); i++){
            if(debug){
                std::cout<<"Uvec sorted :"<<i<<" U value:"<<Uvec[i]<<std::endl;
            }
            gp_Pnt p;
            myArcOfCircle->D0(Uvec[i],p);
            theIntersections.push_back(p);
        }
        return 1;
    }

    //! This functions creates sub arc's between sorted intersection points.
    //! The main arc shape then can be deleted after trim operation is finished.
    //! Also the point clicked nearest to one of the sub arc's, this arc will also be deleted to create the trim.
    bool getNewArcPointsFromSortedIntersections(gp_PntVec theSortedIntersections, std::vector<double> theSortedUvec,
                                                //! Returns a vector of : arc start, arc waypoint, arc endpoint.
                                                std::vector<gp_PntVec> &arcpointVec){

        //! Create midpoint for arc startpoint to first intersectionpoint to create a sub arc.
        double UwayPoint=(theSortedUvec[0]-myUstart)/2;
        gp_Pnt theWayPoint;
        myArcOfCircle->D0(UwayPoint,theWayPoint);

        //! The first sub arc is born.
        gp_PntVec A;
        A.push_back(p0);
        A.push_back(theWayPoint);
        A.push_back(theSortedIntersections[0]);
        arcpointVec.push_back(A);

        //! The in between sub arc's.
        for(unsigned int i=0; i<theSortedIntersections.size()-1; i++){
            double UwayPoint=theSortedUvec[i]+ (theSortedUvec[i+1]-theSortedUvec[i])/2;
            gp_Pnt theWayPoint;
            myArcOfCircle->D0(UwayPoint,theWayPoint);

            gp_PntVec B;
            B.push_back(theSortedIntersections[i]);
            B.push_back(theWayPoint);
            B.push_back(theSortedIntersections[i+1]);

            arcpointVec.push_back(B);
        }

        //! The last sub arc.
        double UwayPoint1=theSortedUvec.back() + (myUend-theSortedUvec.back())/2;
        gp_Pnt theWayPoint1;
        myArcOfCircle->D0(UwayPoint1,theWayPoint1);

        //! The first sub arc is born.
        gp_PntVec C;
        C.push_back(theSortedIntersections.back());
        C.push_back(theWayPoint1);
        C.push_back(p2);
        arcpointVec.push_back(C);
        return 1;
    }

    //! Determine if a thePoint is on the 3d arc segment.
    bool isPointOnArc(gp_Pnt thePoint, bool debug){

        //! Check if radius of thePoint is ok.
        if(thePoint.Distance(myCenter)>myRadius-myTol && thePoint.Distance(myCenter)<myRadius+myTol ){
            if(debug){
                std::cout<<"Radius is ok."<<std::endl;
            }
        } else {
            if(debug){
                std::cout<<"Radius is not ok."<<std::endl;
            }
            return 0;
        }

        //! Check if thePoint is on the arc plane.
        if(PointOnPlane(p0,p1,p2,thePoint).IsOnPlane(0)){
            if(debug){
                std::cout<<"The point is on plane."<<std::endl;
            }
        } else {
            if(debug){
                std::cout<<"The point is not on plane."<<std::endl;
            }
            return 0;
        }

        //! Check if point is on the arc. Gce_MakeCirc has more functions then GC_MakeArcOfCircle to pass in a Point and get back a circle U value.

        double Upoint=ElCLib().Parameter(myGpCircle,thePoint);
        std::cout<<"elparam:"<<Upoint<<std::endl;

        if(Upoint>=myUstart && Upoint<=myUend){
            if(debug){
                std::cout<<"The point is on arc circumfence."<<std::endl;
            }
            return 1;
        }
        if(debug){
            std::cout<<"The point is not on arc cirumfence."<<std::endl;
        }
        return 0;
    }

private:
    gp_Pnt p0,p1,p2;
    double myRadius=0;
    gp_Pnt myCenter;
    double myTol=0.001;
    double myUstart, myUend;
    Handle(Geom_TrimmedCurve) myArcOfCircle;
    gp_Circ myGpCircle;
};

#endif // ARCPOINTS_H
