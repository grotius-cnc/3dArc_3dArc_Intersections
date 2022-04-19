# 3dArc_3dArc_Intersections
A general algoritme to find 3d intersections. Works also for parallel arc planes.

![screen09](https://user-images.githubusercontent.com/44880102/163284016-65e4f16a-6af8-4b97-afb3-6fe645ae4bac.jpg)

            //! Arc A
            gp_Pnt pa0_in{0,0,0};
            gp_Pnt pa1_in{50,50,0};
            gp_Pnt pa2_in{100,0,0};
            OBJECT *ArcA = new OBJECT(arc_3p,pa0_in,pa1_in,pa2_in);
            
            //! Arc B
            gp_Pnt pb0_in{0,100,0};
            gp_Pnt pb1_in{50,50,0};
            gp_Pnt pb2_in{100,100,0};
            OBJECT *ArcB = new OBJECT(arc_3p,pb0_in,pb1_in,pb2_in);
       
            gp_PntVec pvec;
            ArcA->getIntersections(*ArcB,pvec,1);

            for(unsigned int i=0; i<pvec.size(); i++){
                //! Intersections:
                pvec[i]
            }
            
- Some additional functions in this repository :
         
LineSphereIntersect, LineLineIntersect, ArcArcIntersect, ArcCenter, ArcPoints, PointOnArc, PointOnLine, PointOnPlane        

- Not finished :

GeneralIntersect, SplineSplineIntersect.
          

Opencascade library :
https://github.com/grotius-cnc/occt-samples-qopenglwidget/releases/download/1.1/opencascade.tar.gz
