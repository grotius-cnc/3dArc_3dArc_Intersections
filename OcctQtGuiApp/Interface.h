#ifndef INTERFACE_H
#define INTERFACE_H

#include "QWidget"
#include "iostream"
#include "Types.h"
#include "Geom_TrimmedCurve.hxx"
#include "GC_MakeArcOfCircle.hxx"
#include "BRepBuilderAPI_MakeVertex.hxx"
#include "TopoDS_Edge.hxx"
#include "AIS_Shape.hxx"
#include "AIS_DisplayMode.hxx"
#include "BRepBuilderAPI_MakeEdge.hxx"
#include "GC_MakePlane.hxx"
#include "BRepPrimAPI_MakeSphere.hxx"
#include "BRepBuilderAPI_MakeFace.hxx"
#include "BRepBuilderAPI_MakeWire.hxx"
#include "LineLineIntersect.h"
#include "LineArcIntersect.h"
#include "ArcArcIntersect.h"
#include "SplineSplineIntersect.h"
#include "ArcCenter.h"
#include "GeneralIntersect.h"
#include "PointOnPlane.h"
#include "PointOnLine.h"
#include "SplinePoints.h"
#include <libspline/cubic_spline.h>
#include <libspline/bezier_spline.h>

//! Make conversion's easy:
#define toRadians M_PI/180.0
#define toDegrees (180.0/M_PI)

enum TYPE{
    none,
    point_1p,
    line_2p,
    triangle,
    rectangle,
    plane,
    polyline,
    polygon,
    hexagon,
    arc_cp_2p,
    arc_3p,
    circle_cp_2p,
    circle_3p,
    ellipse,
    spline,
    bezier,
    slot,
    arrow,
    sphere,
    box,
};

enum LINETYPE{
    continious,
    dashed_center,
    dashed_dot,
    dashed_even
};

struct COLOR{
    //! Range 0-255.
    unsigned int red=0, green=0, blue=0, alpha=0;
};

struct PROPERTIES{
public:
    void setLayer(int theLayer){
        myLayer=theLayer;
    }
    void setLineType(LINETYPE theType){
        myLinetype=theType;
    }
    void setLineWidth(double theLinewidht){
        myLinewidht=theLinewidht;
    }
    void setColor(double red, double green, double blue, double alpha){
        myColor.red=red;
        myColor.green=green;
        myColor.blue=blue;
        myColor.alpha=alpha;
    }
    void setColor(COLOR theColor){
        myColor=theColor;
    }
private:
    int myLayer=0;
    LINETYPE myLinetype;
    double myLinewidht=0;
    //! Color 0-255
    COLOR myColor;
};

struct VALUES{
public:
    void setPointVectorSize(size_t theSize){
        myPointVec.resize(theSize);
    }
    void setDoubleVectorSize(size_t theSize){
        myDoubleVec.resize(theSize);
    }
    void setUIntegerVectorSize(size_t theSize){
        myUIntegerVec.resize(theSize);
    }
    void clear(){
        myPointVec.clear();
        myDoubleVec.clear();
    }
    void setPointValues(int theIndex, gp_Pnt thePoint){
        myPointVec.at(theIndex)=thePoint;
    };
    void setPointValues(gp_PntVec thePoints){
        myPointVec.clear();
        myPointVec.resize(thePoints.size());
        myPointVec=thePoints;
    }
    void setDoubleValues(unsigned int theIndex, double theValue){
        myDoubleVec[theIndex]=theValue;
    }
    void setDoubleValues(std::vector<double> theValues){
        myDoubleVec=theValues;
    }
    void setUIntegerValues(std::vector<unsigned int> theValues){
        myUIntegerVec=theValues;
    }
    bool isDuplicate(gp_Pnt thePoint){
        for(unsigned int i=0; i<myPointVec.size(); i++){
            if(thePoint.Distance(myPointVec.at(i))<0.0001){
                return 1;
            }
        }
        return 0;
    }
    gp_Pnt getFirstPoint(){
        return myPointVec.at(0);
    }
    gp_Pnt getSecondPoint(){
        return myPointVec.at(1);
    }
    gp_Pnt getThirdPoint(){
        return myPointVec.at(2);
    }
    gp_PntVec getPointVec(){
        return myPointVec;
    }
    double getRadiusFrom3pArc(){
        return ArcCenter(myPointVec[0],myPointVec[1],myPointVec[2]).Arc_radius();
    }
    bool getFirstDoubleValue(double& theValue){
        if(myDoubleVec.size()>0){
            theValue=myDoubleVec[0];
            return 1;
        } else { return 0; }
    }
    bool getSecondDoubleValue(double& theValue){
        if(myDoubleVec.size()>1){
            theValue=myDoubleVec[1];
            return 1;
        } else { return 0; }
    }
    bool getThirdDoubleValue(double& theValue){
        if(myDoubleVec.size()>2){
            theValue=myDoubleVec[2];
            return 1;
        } else { return 0; }
    }
    gp_Pnt getArcCenter(){
        return ArcCenter(myPointVec[0],myPointVec[1],myPointVec[2]).Arc_cp();
    }

private:
    gp_PntVec myPointVec;
    std::vector<double> myDoubleVec;
    std::vector<unsigned int> myUIntegerVec;
};

//! OBJECT is a general class that directs program flow.
class OBJECT{
public:

    OBJECT(){
        myType=none;
        setTypeValueModel();
    }

    OBJECT(TYPE theType){
        myType=theType;
        setTypeValueModel();
    }

    OBJECT(TYPE theType ,gp_Pnt P0){
        myType=theType;
        setTypeValueModel();
        myValues.setPointValues({P0});
    }

    //! Sphere.
    //!     P0=theCenterPoint
    //!     D0=theRadius
    OBJECT(TYPE theType, gp_Pnt P0, double D0){
        myType=theType;
        setTypeValueModel();
        myValues.setPointValues(0,P0);
        myValues.setDoubleValues(0,D0);
    }

    //! Box.
    //!     P0=theOrigin
    //!     D0=theWidth
    //!     D1=theDepth
    //!     D2=theHeight
    OBJECT(TYPE theType, gp_Pnt P0, double D0, double D1, double d2){
        myType=theType;
        setTypeValueModel();
        myValues.setPointValues({P0});
    }

    //! Line
    //!     P0=theStartPoint
    //!     P1=theEndPoint
    //! Sphere
    //!     P0=theCenterPoint
    //!     P1=theSurfacePoint
    //! Rectangle, Slot
    //!     P0=theLowerLeftPoint
    //!     P1=theUpperRightPoint
    OBJECT(TYPE theType, gp_Pnt theFirstPoint, gp_Pnt theSecondPoint){
        myType=theType;
        if(theType==TYPE::line_2p){
            myPointVec.reserve(2);
            myPointVec.push_back(theFirstPoint);
            myPointVec.push_back(theSecondPoint);
        }
        if(theType==TYPE::sphere){
            myPointVec.reserve(2);
            myPointVec.push_back(theFirstPoint);
            myPointVec.push_back(theSecondPoint);
            myRadius=theFirstPoint.Distance(theSecondPoint);
        }
    }

    //! Arc_3p, Circle_3p, Circle_2p_cp
    //!     P0=theStartPoint
    //!     P1=theWayPoint
    //!     P2=theEndPoint
    //! Triangle
    //!     P0=theEdgeA
    //!     P1=theEdgeB
    //!     P2=theEdgeC
    //! Ellipse
    //!     P0=theCenter
    //!     P1=theXaxisEndPoint
    //!     P2=theYaxisEndPoint
    //! Plane
    //!     P0=thePlanePointA
    //!     P1=thePlanePointB
    //!     P2=thePlanePointC
    OBJECT(TYPE theType, gp_Pnt P0, gp_Pnt P1, gp_Pnt P2){
        myType=theType;
        setTypeValueModel();
        myValues.setPointValues({P0,P1,P2});
    }

    //! Bezier
    //!     P0=theFirstPoint
    //!     P1=theSecondPoint
    //!     P2=theThirdtPoint
    //!     P3=theFourthPoint
    OBJECT(TYPE theType, gp_Pnt P0, gp_Pnt P1, gp_Pnt P2, gp_Pnt P3){
        myType=theType;
        setTypeValueModel();
        myValues.setPointValues({P0,P1,P2,P3});
    }

    //! Hexagon, Polygon
    //!     P0=theCenterpoint
    //!     P1=theCircumfencePoint
    //!     UI0=theIntSides
    OBJECT(TYPE theType, gp_Pnt P0, gp_Pnt P1, unsigned int UI0){
        myType=theType;
        setTypeValueModel();
        myValues.setPointValues({P0,P1});
        myValues.setUIntegerValues({UI0});
    }

    //! Spline, Polyline, Bezier
    //!     PVEC=thePointVec
    //! This input model is compatible with Line, Arc_3p and more.
    OBJECT(TYPE theType, gp_PntVec thePvec){
        myType=theType;
        if(theType==TYPE::spline){
            myPointVec.reserve(thePvec.size());
            myPointVec=thePvec;
            SplinePoints(thePvec).getLowerLevelPoints(myPointVecGl);
        }
    }


    virtual ~OBJECT(){}

    void setDebug(bool state){
        myDebug=state;
    }
    void setType(TYPE theType){
        myType=theType;
        setTypeValueModel();
    };
    TYPE getType(){
        return myType;
    }
    void setProperties(PROPERTIES properties){
        myProperties=properties;
    };
    void setColor(COLOR theColor){
        myProperties.setColor(theColor);
    }
    //! Range 0-255
    void setColor(unsigned int red, unsigned int green, unsigned int blue, unsigned int alpha){
        myProperties.setColor(red,green,blue,alpha);
    }
    void setLineType(LINETYPE theLinetype){
        myProperties.setLineType(theLinetype);
    }
    void setLineWidht(double theLineWidth){
        myProperties.setLineWidth(theLineWidth);
    }
    void setLayer(int theLayer){
        myProperties.setLayer(theLayer);
    }

    PROPERTIES getProperties(){
        return myProperties;
    }
    //! setPoints{0,{0,0,0}}
    void setPoints(unsigned int theIndex, gp_Pnt thePoint){
        myValues.setPointValues(theIndex,thePoint);
    };
    //! setPoints{{0,0,0},{0,0,0}}
    void setPoints(gp_PntVec thePoints){
        myValues.setPointValues(thePoints);
    };

    VALUES getValues(){
        return myValues;
    }
    void matchType(OBJECT theRefObject){
        myType=theRefObject.myType;
    };
    void matchProperties(OBJECT theRefObject){
        myProperties=theRefObject.myProperties;
    };
    void matchValues(OBJECT theRefObject){
        myValues=theRefObject.myValues;
    };
    void matchEverything(OBJECT theRefObject){
        myType=theRefObject.myType;
        myProperties=theRefObject.myProperties;
        myValues=theRefObject.myValues;
    };

    //! With debug.
    bool getIntersections(OBJECT theRefObject, gp_PntVec &pvec, bool debug){

        //! Line-line 3d intersection
        if(myType==TYPE::line_2p && theRefObject.myType==TYPE::line_2p){
            bool result=LineLineIntersect(
                        this->getValues().getFirstPoint(),
                        this->getValues().getSecondPoint(),
                        theRefObject.getValues().getFirstPoint(),
                        theRefObject.getValues().getSecondPoint()).getIntersections(pvec,debug);
            return result;
        };

        //! Arc-line 3d intersection and visa-versa
        if(myType==TYPE::line_2p && theRefObject.myType==TYPE::arc_3p){
            bool result=LineArcIntersect(
                        myValues.getFirstPoint(),
                        myValues.getSecondPoint(),
                        theRefObject.getValues().getFirstPoint(),
                        theRefObject.getValues().getSecondPoint(),
                        theRefObject.getValues().getThirdPoint()).getIntersections(pvec,debug);
            return result;
        };
        if(myType==TYPE::arc_3p && theRefObject.myType==TYPE::line_2p){
            bool result=LineArcIntersect(
                        theRefObject.getValues().getFirstPoint(),
                        theRefObject.getValues().getSecondPoint(),
                        myValues.getFirstPoint(),
                        myValues.getSecondPoint(),
                        myValues.getThirdPoint()).getIntersections(pvec,debug);

            return result;
        };

        //! Arc-arc 3d intersection
        if(myType==TYPE::arc_3p && theRefObject.myType==TYPE::arc_3p){
            bool result=ArcArcIntersect(myValues.getFirstPoint(),
                                        myValues.getSecondPoint(),
                                        myValues.getThirdPoint(),
                                        theRefObject.getValues().getFirstPoint(),
                                        theRefObject.getValues().getSecondPoint(),
                                        theRefObject.getValues().getThirdPoint()).getIntersections(pvec, debug);
            return result;
        }

        //! Spline-spline intersetions. Includes self intersections.
        if(myType==TYPE::spline && theRefObject.myType==TYPE::spline){
            bool result=SplineSplineIntersect(this->myPointVecGl,theRefObject.myPointVecGl).getIntersections(pvec, debug);
            return result;
        }



        return 0;
    };

    //! Get the opencascade shape to display like :
    //! myContext->Display(==> TheShape,AIS_WireFrame,-1,Standard_False);
    //! myContext->Redisplay(==> theShape,Standard_True);
    //!       aShape->SetColor(Quantity_NOC_ANTIQUEWHITE);

    //! The default constructor returns standard values.
    Handle(AIS_Shape) getShape(){
        Handle(AIS_Shape) aShape=getShape(Quantity_NOC_BLACK,AIS_Shaded,1,0);
        return aShape;
    }
    //! The customized constructor returns a shape with specifik properties.
    //! For theTranceparancy 0.0-1.0
    Handle(AIS_Shape) getShape(Quantity_Color theColor, AIS_DisplayMode theDisplayMode, double theWidth, double theTranceparancy){
        //! Failsafe.
        if(theWidth==0){
            theWidth=1;
        }

        if(myType==TYPE::point_1p){
            TopoDS_Vertex aVertex = BRepBuilderAPI_MakeVertex(myValues.getFirstPoint());
            Handle(AIS_Shape) aShape=new AIS_Shape(aVertex);
            aShape->SetWidth(theWidth);
            aShape->SetDisplayMode(theDisplayMode);
            aShape->SetColor(theColor);
            aShape->SetTransparency(theTranceparancy);
            return aShape;
        }
        if(myType==TYPE::line_2p){
            TopoDS_Edge aEdge = BRepBuilderAPI_MakeEdge(myValues.getFirstPoint(),myValues.getSecondPoint());
            Handle(AIS_Shape) aShape=new AIS_Shape(aEdge);
            aShape->SetWidth(theWidth);
            aShape->SetDisplayMode(theDisplayMode);
            aShape->SetColor(theColor);
            aShape->SetTransparency(theTranceparancy);
            return aShape;
        }
        if(myType==TYPE::triangle){
            BRepBuilderAPI_MakeWire aWire;
            aWire.Add(BRepBuilderAPI_MakeEdge(myValues.getFirstPoint(),myValues.getSecondPoint()));
            aWire.Add(BRepBuilderAPI_MakeEdge(myValues.getSecondPoint(),myValues.getThirdPoint()));
            aWire.Add(BRepBuilderAPI_MakeEdge(myValues.getFirstPoint(),myValues.getThirdPoint()));

            Handle(AIS_Shape) aShape=new AIS_Shape(aWire);
            aShape->SetWidth(theWidth);
            aShape->SetDisplayMode(theDisplayMode);
            aShape->SetColor(theColor);
            aShape->SetTransparency(theTranceparancy);
            return aShape;
        }
        if(myType==TYPE::arc_3p){
            //! Check if arc points are not colineair. If the arc is a line, opencascade gives error.
            bool onLine=PointOnLine(myValues.getFirstPoint(),myValues.getSecondPoint(),myValues.getThirdPoint(),0.0001).isOnLine();
            if(onLine){
                std::cout<<"opencascade error, arc points are colineair. Arc seems a line.";
                return nullptr;
            } else {
                Handle(Geom_TrimmedCurve) aArcOfCircle = GC_MakeArcOfCircle(myValues.getFirstPoint(),
                                                                            myValues.getSecondPoint(),
                                                                            myValues.getThirdPoint());
                std::cout<<"Construction Firstparamter: "<<aArcOfCircle->FirstParameter()<<
                           " x:"<<aArcOfCircle->StartPoint().X()<<" y:"<<aArcOfCircle->StartPoint().Y()<< " z:"<<aArcOfCircle->StartPoint().Z()<<std::endl;

                std::cout<<"Construction Lastparamter: "<<aArcOfCircle->LastParameter()<<
                             " x:"<<aArcOfCircle->EndPoint().X()<<" y:"<<aArcOfCircle->EndPoint().Y()<< " z:"<<aArcOfCircle->EndPoint().Z()<<std::endl;


                TopoDS_Edge aEdge = BRepBuilderAPI_MakeEdge(aArcOfCircle);
                Handle(AIS_Shape) aShape=new AIS_Shape(aEdge);
                aShape->SetWidth(theWidth);
                aShape->SetDisplayMode(theDisplayMode);
                aShape->SetColor(theColor);
                aShape->SetTransparency(theTranceparancy);
                return aShape;
            }
        }
        if(myType==TYPE::sphere){
            double theValue;
            myValues.getFirstDoubleValue(theValue);
            TopoDS_Shape aSphere;

            if(theValue>0){
                aSphere = BRepPrimAPI_MakeSphere(myValues.getFirstPoint(),theValue).Shape();

            } else if (myValues.getFirstPoint().Distance(myValues.getSecondPoint())>0){
                theValue=myValues.getFirstPoint().Distance(myValues.getSecondPoint());
                myValues.setDoubleValues(0,theValue);
                aSphere = BRepPrimAPI_MakeSphere(myValues.getFirstPoint(),theValue).Shape();

            } else {
                //! Nothing can be created.
                return nullptr;
            }

            Handle(AIS_Shape) aShape=new AIS_Shape(aSphere);
            aShape->SetWidth(theWidth);
            aShape->SetDisplayMode(theDisplayMode);
            aShape->SetColor(theColor);
            aShape->SetTransparency(theTranceparancy);
            return aShape;
        }
        if(myType==TYPE::plane){
            //! Create a plane from 3 points.
            Handle(Geom_Plane) GeomPlane=GC_MakePlane(myValues.getFirstPoint(),myValues.getSecondPoint(),myValues.getThirdPoint());

            gp_Pln thePlane;
            thePlane.SetPosition(GeomPlane->Position());

            TopoDS_Shape aPlane= BRepBuilderAPI_MakeFace(thePlane, -200.0, 200.0, -200.0, 200.0);
            Handle(AIS_Shape) aShape=new AIS_Shape(aPlane);
            aShape->SetWidth(theWidth);
            aShape->SetDisplayMode(theDisplayMode);
            aShape->SetColor(theColor);
            aShape->SetTransparency(theTranceparancy);
            return aShape;
        }
        if(myType==TYPE::spline){
            //! Create a linewire.
            BRepBuilderAPI_MakeWire aWire;
            TopoDS_Edge edge;
            gp_Pnt p1=myPointVecGl[0], p2={0,0,0};
            for(unsigned int i=1; i<myPointVecGl.size(); i++){
                //! A system to avoid duplicates.
                p2=myPointVecGl.at(i);
                if(p1.X()!=p2.X() || p1.Y()!=p2.Y() || p1.Z()!=p2.Z()){
                    edge = BRepBuilderAPI_MakeEdge(p1,p2);
                    aWire.Add(edge);
                    p1=p2;
                } else {
                    std::cout<<"Avoiding duplicate points from spline input."<<std::endl;
                }
            }
            Handle(AIS_Shape) aShape=new AIS_Shape(aWire);
            aShape->SetWidth(theWidth);
            aShape->SetDisplayMode(theDisplayMode);
            aShape->SetColor(theColor);
            aShape->SetTransparency(theTranceparancy);
            return aShape;
        }

        return nullptr;
    };

private:
    bool myDebug;
    TYPE myType;
    PROPERTIES myProperties;
    VALUES myValues;
    gp_PntVec myPointVec;
    //! Store points at opengl level.
    gp_PntVec myPointVecGl;
    double myRadius;

    void setTypeValueModel(){
        if(myType==TYPE::none){
            myValues.setPointVectorSize(0);
        };
        if(myType==TYPE::point_1p){
            myValues.setPointVectorSize(1);
        };
        if(myType==TYPE::line_2p){
            myValues.setPointVectorSize(2);
        };
        if(myType==TYPE::plane){
            myValues.setPointVectorSize(3);
        };
        if(myType==TYPE::triangle){
            myValues.setPointVectorSize(3);
            myValues.setDoubleVectorSize(1);    //! Area.
        };
        if(myType==TYPE::arc_3p){
            myValues.setPointVectorSize(3);
            myValues.setDoubleVectorSize(1);    //! Radius.
        };
        if(myType==TYPE::circle_3p){
            myValues.setPointVectorSize(3);
            myValues.setDoubleVectorSize(1);    //! Radius.
        };
        if(myType==TYPE::rectangle){
            myValues.setPointVectorSize(4);
            myValues.setDoubleVectorSize(1);    //! Area.
        };
        if(myType==TYPE::sphere){
            myValues.setPointVectorSize(2);     //! Center, PointOnSurface
            myValues.setDoubleVectorSize(1);    //! Radius.
        };
        if(myType==TYPE::hexagon){
            myValues.setPointVectorSize(2);
            myValues.setUIntegerVectorSize(1);  //! Sides.
        };
        if(myType==TYPE::box){
            myValues.setPointVectorSize(1);     //! Origin.
            myValues.setDoubleVectorSize(3);    //! Widht,Depth,Height.
        };
        if(myType==TYPE::bezier){
            myValues.setPointVectorSize(4);
        };
        if(myType==TYPE::spline){
            myValues.setPointVectorSize(0);
        };
    };
};

#endif // INTERFACE_H





















