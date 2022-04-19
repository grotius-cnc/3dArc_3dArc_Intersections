#ifndef SPLINEPOINTS_H
#define SPLINEPOINTS_H

#include "Types.h"
#include "libspline/cubic_spline.h"

class SplinePoints{
public:
    //! Insert the spline waypoints.
    SplinePoints(gp_PntVec theWayPointVec): myWayPointVec(theWayPointVec){}

    //! Returns points to draw the Opengl linestrip for a spline.
    bool getLowerLevelPoints(gp_PntVec &thePvec){

        if(myWayPointVec.size()<3){
            return 0;
        }

        std::vector<Vector3d> path;
        for(unsigned int i=0; i<myWayPointVec.size(); i++){
            path.push_back(Vector3d(myWayPointVec.at(i).X(),
                                    myWayPointVec.at(i).Y(),
                                    myWayPointVec.at(i).Z()));
        }
        CubicSpline c_spline(path,mySegmentsAPoint);
        c_spline.BuildSpline(path);
        std::vector<double> c_pathx(c_spline.GetPositionProfile().size());
        std::vector<double> c_pathy(c_spline.GetPositionProfile().size());
        std::vector<double> c_pathz(c_spline.GetPositionProfile().size());

        //! Get profile data for position, speed, acceleration, and curvature
        std::vector<double> ti(c_spline.GetPositionProfile().size());
        for(unsigned int i=0;i<c_pathx.size();++i)
        {
            c_pathx[i] = c_spline.GetPositionProfile()[i].x();
            c_pathy[i] = c_spline.GetPositionProfile()[i].y();
            c_pathz[i] = c_spline.GetPositionProfile()[i].z();
            thePvec.push_back({c_pathx[i],c_pathy[i],c_pathz[i]});
        }
        return 1;
    }

private:
    gp_PntVec myWayPointVec;
    int mySegmentsAPoint=20;
};

#endif // SPLINEPOINTS_H
