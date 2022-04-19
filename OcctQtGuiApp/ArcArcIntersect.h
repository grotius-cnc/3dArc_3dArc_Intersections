#ifndef ARCARCINTERSECT_H
#define ARCARCINTERSECT_H

#include "Types.h"
#include <PointOnPlane.h>
#include <LineSphereIntersect.h>
#include <ArcCenter.h>
#include "GeomInt_IntSS.hxx"
#include "GC_MakePlane.hxx"

//! This class is designed to intersect 3d_arc with 3d_arc.
//!
//! The class includes 2 stratagies to find the 3d arc-arc intersections.
//!
//! 1. When arc planes are in the same surface we calculate a conventional 2d arc-arc intersection.
//!
//! 2. When arc planes are not in the same surface we use a few steps to get the intersections.
//!         1. From the 3d arc points, we create planes.
//!         2. We do a plane-plane intersection wich gives us a line.
//!         3. We do a line-sphere intersection for each arc.
//!         4. The duplicate points of item 3 are the arc-intersections.
//!
class ArcArcIntersect
{
public:
    ArcArcIntersect(gp_Pnt arcA_p0, gp_Pnt arcA_p1, gp_Pnt arcA_p2, gp_Pnt arcB_p0, gp_Pnt arcB_p1, gp_Pnt arcB_p2)
        : pa0(arcA_p0), pa1(arcA_p1), pa2(arcA_p2), pb0(arcB_p0), pb1(arcB_p1), pb2(arcB_p2) {
    }

    //! Standard 0.001, Used by plane and point calculations.
    void setTollerance(double tollerance){
        myTol=tollerance;
    }

    bool getIntersections(gp_PntVec &pvec, bool debug){

        //! We have plane0 & plane1. We want a plane-plane intersect using GeomInt_IntSS.
        Handle(Geom_Plane) GeomPlaneA=GC_MakePlane(pa0,pa1,pa2);
        Handle(Geom_Plane) GeomPlaneB=GC_MakePlane(pb0,pb1,pb2);

        //! Check planes.
        bool p0=PointOnPlane(pa0,pa1,pa2,pb0).IsOnPlane(debug);
        bool p1=PointOnPlane(pa0,pa1,pa2,pb1).IsOnPlane(debug);
        bool p2=PointOnPlane(pa0,pa1,pa2,pb2).IsOnPlane(debug);

        //! 2d approach. In this case the 2 planes are in the same surface. Then the 3d approach will not work. Changing to 2d approach and return results.
        if(p0==1 && p1==1 && p2==1){
            if(debug){
                std::cout<<"Arc plane's are in the same surface, 2d approach."<<std::endl;
            }
            getIntersections2D(pvec, debug);
            return 1;
        }

        //! 3d approach.
        //! Intersect 2 planes. Result is a line.
        GeomInt_IntSS intersect(GeomPlaneA,GeomPlaneB,myTol,1,0,0);
        if(intersect.IsDone()){
            if(intersect.NbLines()>0){
                if(debug){
                    std::cout<<"intersect is done, nr of points: "<<intersect.NbPoints()<<" nr of lines: "<<intersect.NbLines()<<std::endl;
                }

                //! Mention the output starts at 1. This is the intersection line of 2 planes.
                Handle(Geom_Curve) aline= intersect.Line(1);

                //! Get random points for this line.
                gp_Pnt a=aline->Value(-500);
                gp_Pnt b=aline->Value(500);

                //! Line-Sphere intersect on ArcA.
                gp_PntVec pvecA;
                LineSphereIntersect(a,b,pa0,pa1,pa2).getIntersections(pvecA,debug);

                //! Line-Sphere intersect on ArcB.
                gp_PntVec pvecB;
                LineSphereIntersect(a,b,pb0,pb1,pb2).getIntersections(pvecB,debug);

                //! Used for debug.
                std::setprecision(3);

                //! Store only the duplicates. The duplicates are the shared intersection points of the arc's.
                for(unsigned int i=0; i<pvecA.size(); i++){
                    for(unsigned int j=0; j<pvecB.size(); j++){
                        if(pvecA[i].Distance(pvecB[j])<myTol){
                            pvec.push_back(pvecA[i]);
                            if(debug){
                                std::cout<<std::fixed<<"Intersection at x:"<<pvecA[i].X()<<" y:"<<pvecA[i].Y()<<" z:"<<pvecA[i].Z()<<std::endl;
                            }
                        }
                    }
                }
                return 1;
            }
        }
        return 0;
    }

private:
    gp_Pnt pa0, pa1, pa2, pb0, pb1, pb2;
    double myTol=0.001;
    gp_Pnt myCenter0, myCenter1;

    //! Determine the points where 2 circles in a common plane intersect.
    //! - http://paulbourke.net/geometry/circlesphere/tvoght.c
    bool getIntersections2D(gp_PntVec &pvec, bool debug)
    {
        myCenter0=ArcCenter(pa0,pa1,pa2).Arc_cp(debug);
        myCenter1=ArcCenter(pb0,pb1,pb2).Arc_cp(debug);

        //! Arc0.
        double x0=myCenter0.X();
        double y0=myCenter0.Y();
        double z0=myCenter0.Z();

        //! Arc1.
        double x1=myCenter1.X();
        double y1=myCenter1.Y();
        double z1=myCenter1.Z();

        //! Radius.
        double r0=myCenter0.Distance(pa0);
        double r1=myCenter1.Distance(pb0);

        double a, dx, dy, d, h, rx, ry;
        double x2, y2;

        //! dx and dy are the vertical and horizontal distances between
        //! the circle centers.
        dx = x1 - x0;
        dy = y1 - y0;

        //! Determine the straight-line distance between the centers.
        //! d = sqrt((dy*dy) + (dx*dx));
        d = hypot(dx,dy); //! Suggested by Keith Briggs

        //! Check for solvability.
        if (d > (r0 + r1))
        {
            //! no solution. circles do not intersect.
            return 0;
        }
        if (d < fabs(r0 - r1))
        {
            //! no solution. one circle is contained in the other
            return 0;
        }

        //! 'point 2' is the point where the line through the circle
        //! intersection points crosses the line between the circle
        //! centers.

        //! Determine the distance from point 0 to point 2.
        a = ((r0*r0) - (r1*r1) + (d*d)) / (2.0 * d) ;

        //! Determine the coordinates of point 2.
        x2 = x0 + (dx * a/d);
        y2 = y0 + (dy * a/d);

        //! Determine the distance from point 2 to either of the
        //! intersection points.
        h = sqrt((r0*r0) - (a*a));

        //! Now determine the offsets of the intersection points from
        //! point 2.
        //!
        rx = -dy * (h/d);
        ry = dx * (h/d);

        //! Determine the absolute intersection points.
        gp_Pnt ia{ x2+rx , y2+ry, z0};
        gp_Pnt ib{ x2-rx , y2-ry, z1};

        //! Store only one solution if points are duplicates.
        if(ia.Distance(ib)<myTol){
             pvec.push_back(ia);
        } else {
            pvec.push_back(ia);
            pvec.push_back(ib);
        }
        return 1;
    }
};

#endif // ARCARCINTERSECT_H













