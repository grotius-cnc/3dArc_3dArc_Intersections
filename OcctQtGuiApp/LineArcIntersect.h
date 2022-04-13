#ifndef LINEARCINTERSECT_H
#define LINEARCINTERSECT_H

#include "Interface.h"
#include "ArcCenter.h"
#include "PointOnPlane.h"
#include "PointOnLine.h"

class LineArcIntersect
{
public:
    //! Given a 2p_line & 3p_arc in 3d.
    //! This function is like intersecting a line with a sphere, after that it checks if solution is on arc plane.
    //! This line-sphere intersect implementation is inherit to raytracing computergraphics.
    LineArcIntersect(gp_Pnt line_p0, gp_Pnt line_p1, gp_Pnt arc_p0, gp_Pnt arc_p1, gp_Pnt arc_p2) :
        p0(line_p0), p1(line_p1), parc0(arc_p0), parc1(arc_p1), parc2(arc_p2) {

        cp=ArcCenter(parc0,parc1,parc2).Arc_cp();
        myRadius=parc0.Distance(cp);
    }

    //! Return intersections.
    bool getIntersections(std::vector<gp_Pnt> &pvec, bool debug)
    {
        double cx = cp.X();
        double cy = cp.Y();
        double cz = cp.Z();

        double px = p0.X();
        double py = p0.Y();
        double pz = p0.Z();

        double vx = p1.X() - px;
        double vy = p1.Y() - py;
        double vz = p1.Z() - pz;

        double A = vx * vx + vy * vy + vz * vz;
        double B = 2.0 * (px * vx + py * vy + pz * vz - vx * cx - vy * cy - vz * cz);
        double C = px * px - 2 * px * cx + cx * cx + py * py - 2 * py * cy + cy * cy +
                pz * pz - 2 * pz * cz + cz * cz - myRadius * myRadius;

        // discriminant
        double D = B * B - 4 * A * C;

        double t1 = (-B - Sqrt(D)) / (2.0 * A);

        gp_Pnt solution1;
        solution1.SetX(p0.X() * (1 - t1) + t1 * p1.X());
        solution1.SetY(p0.Y() * (1 - t1) + t1 * p1.Y());
        solution1.SetZ(p0.Z() * (1 - t1) + t1 * p1.Z());

        double t2 = (-B + Sqrt(D)) / (2.0 * A);
        gp_Pnt solution2;
        solution2.SetX(p0.X() * (1 - t2) + t2 * p1.X());
        solution2.SetY(p0.Y() * (1 - t2) + t2 * p1.Y());
        solution2.SetZ(p0.Z() * (1 - t2) + t2 * p1.Z());

        if (D < 0 || t1 > 1 || t2 >1)
        {
            if(debug){
                std::cout<<"no intersections found in general."<<std::endl;
            }
            return 0;
        }
        else if (D == 0)
        {
            //! Check if intersection is on the arc-plane.
//            bool on_plane=PointOnPlane(parc0,parc1,parc2,solution1).IsOnPlane(debug);
//            if(on_plane){
//                bool on_line=PointOnLine(p0,p1,solution1,0.01).isOnLine();
//                if(on_line){
//                    pvec.push_back(solution1);
//                    if(debug){
//                        std::cout<<"intersection solution 1."<<std::endl;
//                    }

//                }
//            }
            pvec.push_back(solution1);
            return 1;
        }
        else
        {
            //! Check if intersection of first solution is on the arc-plane.
//            bool on_planeA=PointOnPlane(parc0,parc1,parc2,solution1).IsOnPlane(debug);
//            if(on_planeA){
//                bool on_lineA=PointOnLine(p0,p1,solution1,0.01).isOnLine();
//                if(on_lineA){
//                    pvec.push_back(solution1);
//                    if(debug){
//                        std::cout<<"intersection found solution 1."<<std::endl;
//                    }
//                }
//            }
//            //! Check if intersection of second solution is on the arc-plane.
//            bool on_planeB=PointOnPlane(parc0,parc1,parc2,solution2).IsOnPlane(debug);
//            if(on_planeB){

//                bool on_lineB=PointOnLine(p0,p1,solution2,0.01).isOnLine();
//                if(on_lineB){
//                    pvec.push_back(solution2);
//                    if(debug){
//                        std::cout<<"intersection found solution 2."<<std::endl;
//                    }
//                }
//            }
            pvec.push_back(solution1);
            pvec.push_back(solution2);
            return 1;
        }
        return 0;
    };
private:
    gp_Pnt p0, p1, cp, parc0, parc1, parc2;
    double myRadius;
};

#endif // LINEARCINTERSECT_H

























