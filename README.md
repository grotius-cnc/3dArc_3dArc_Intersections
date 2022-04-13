# 3dArc_3dArc_Intersections
A general algoritme to find 3d intersections.
Why general?
 
 - This algo can be modified or expanded to include 3d-intersections with other primitive types.
 
# Who is the creator of this algoritme?
Cyberdyne Skynet.

# When using this algoritme?
If you look at cad program's, and want to do more with 3d geometry, it can be handy if the sketcher
of the app can do a 3d trim or extend for different objects.

# Is there a mathematical formule for intersecting two 3d_arc's?
I don't know if there is one. Please open a issue and paste the info if you know if one excists.

# How fast is this algoritme?
The iteration to get a <0.001 accuracy is fast enough for a cadcam program.

# How does the algoritme work?
Step 1.

    Both arc's are divided by points. For example 50 points for each arc. 
Step 2.
    
    The algorimte then does a "line-line" intersection for each part of the segmented arc and looks for the closest distance.
    For example, the closest result found could be like : `for Arc A at i=5. for Arc B at j=8`. 
    
    The line-line info : http://www.paulbourke.net/geometry/pointlineplane/ => The shortest line between two lines in 3D
    In this repository the header : ~/LineLineIntersect.h

Step 3.

    When the closest distance is found for i & j, it know's wich chunk of the arc this is. But this is not optimal yet.
    In this chunk a new arc is created and divided into another 50 points again. and step 2 is repeated again.
    
    The arc division is done by the header : ~/ArcPoints.h 

# How can it see 1 or 2 intersections for arc-arc?
The algo is done 2 times. The second time the arc input points are reversed and will give the other intersection points.
If the output gives duplicate points, you know only one intersection is possible.

# What should i use for input values?
This algo can have different input values, wich result in different results.
From my perspective if you draw a circle with opengl, a division of 50 gives a nice circle output. A division of 10 is way to low.

# How can i check the accuracy?
The algo gives a std::pair of 2 intersections points for each intersection. 
If both std::pair points are the same, you have 100% accuracy.

# Is the algo already failsafe?
No it isn't. It just for info.

# Could the 3d_arc -> 3d_arc intersecting be done in another way?
I don't know, but in some picture's below you will see the 2 arc planes. 
These arc planes intersect along a line, like : http://etc.usf.edu/clipart/42100/42108/planelines_42108.tif
The intersection point should be on that line somewhere. So that is one part. 
Then a line->sphere intersection could be done. This algo is also to be found in this repository at : ~/LineArcIntersect.h

# To mention.
I am trying to create something modular for cad. Something that can morph into something else. Something that can intersect's something else, etc.
Included in mainwindow:

    //! Create a new arc object on the fly.
    OBJECT *Obj = new OBJECT(arc_3p,p0,p1,p2);
    occt_viewer->show_shape(Obj->getShape(Quantity_NOC_RED,AIS_WireFrame,2,0));
    
    //! Create a new spline object on the fly.
    Obj = new OBJECT(spline,pvec);
    occt_viewer->show_shape(Obj->getShape(Quantity_NOC_RED,AIS_WireFrame,2,0));

# Pictures
3d arc's intersecting at 2 points:
![3darc_3darc_intersection](https://user-images.githubusercontent.com/44880102/163068922-fc20fa84-8651-41c1-b919-2a21f9a91e09.jpg)

3d arc's intersecting only at 1 point. 
![3darc_3darc_intersection_1](https://user-images.githubusercontent.com/44880102/163068929-1c3f261b-4bde-4553-9129-c50c02f96427.jpg)

3d arc's intersecting only at 1 point. Sphere's and Plane's are clearly visible.
![screen02](https://user-images.githubusercontent.com/44880102/163072009-25321f5e-78bd-4066-8f9c-caeb48a0f2ea.jpg)

3d arc's endpoint intersection:
![screen03](https://user-images.githubusercontent.com/44880102/163073467-b68c9e99-20cd-4567-b81a-a8f70d3ea371.jpg)

When 3d arc intersections are out of scope:

      The std::pair green+red is not at the same location. This means, no intersection.
![screen04](https://user-images.githubusercontent.com/44880102/163073598-db8c6a70-c398-4cbd-b30b-eb81e3c7c12a.jpg)



