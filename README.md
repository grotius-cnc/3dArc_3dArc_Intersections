# 3dArc_3dArc_Intersections
A general algoritme to find 3d intersections.

# Who invented this algoritme?
Cyberdyne Skynet.

# How fast is this algoritme?
The iteration to get a <0.001 accuracy is fast enough for a cadcam program.

# How does the algoritme work?
Step 1.
Both arc's are divided by points. For example 50 points for each arc. 
Step 2.
The algorimte then does a "line-line" intersection for each part of the segmented arc and looks for the closest distance.
For example, the closest result found could be like : `for Arc A at i=5. for Arc B at j=8`. 
Step 3.
When the closest distance is found for i & j, it know's wich chunk of the arc this is. But this is not optimal yet.
In this chunk a new arc is created and divided into another 50 points again. and step 2 is repeated again.

# How can it see 1 or 2 intersections for arc-arc?
The algo is done 2 times. The second time the arc input points are reversed and will give the other intersection points.
If the output gives duplicate points, you know only one intersection is possible.

# What should i use for input values?
This algo can have different input values, wich result in different results.
From my perspective if you draw a circle with opengl, a division of 50 gives a nice circle output. A division of 10 is way to low.

# How can i check the accuracy?
The algo gives a std::pair of 2 intersections points for each intersection. 
If both std::pair points are the same, you have 100% accuracy.

![3darc_3darc_intersection](https://user-images.githubusercontent.com/44880102/163068922-fc20fa84-8651-41c1-b919-2a21f9a91e09.jpg)

![3darc_3darc_intersection_1](https://user-images.githubusercontent.com/44880102/163068929-1c3f261b-4bde-4553-9129-c50c02f96427.jpg)
