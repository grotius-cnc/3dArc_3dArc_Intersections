#ifndef SPLINESPLINEINTERSECT_H
#define SPLINESPLINEARCINTERSECT_H

#include "Types.h"
#include "LineLineIntersect.h"

template<typename T>
bool aForLoop(T a, T b, T &rpvec){
    uint i,j;
    for(i=0; i<a.size()-1; i++){
        for(j=0; j<b.size()-1; j++){
            gp_PntVec ipvec;
            bool ok=LineLineIntersect(a[i],a[i+1],b[j],b[j+1]).getIntersections(ipvec,0);
            if(ipvec.size()>0){
                rpvec.push_back(ipvec[0]);
            }
        }
    }
    if(rpvec.size()<1){
        return 0;
    }
    return 1;
};

class SplineSplineIntersect
{
public:

    SplineSplineIntersect(gp_PntVec pvecSplineA, gp_PntVec pvecSplineB) :
        pveca(pvecSplineA), pvecb(pvecSplineB) { }

    //! Return intersections.
    bool getIntersections(gp_PntVec &pvec, bool debug){

        gp_PntVec rpvec;
        aForLoop<gp_PntVec>(pveca,pvecb,rpvec);

    };

private:
    gp_PntVec pveca,pvecb;
};

#endif // LINEARCINTERSECT_H

























