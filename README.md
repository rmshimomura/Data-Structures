# Data Structures projects

Some the projects I made through Data structures, from second and third semester on Computer Science course of UEL. (State University of Londrina).

On every project, it is ***strictly prohibited*** declaring structs on headers files.

 ## Project 1
  Given a file .geo containing data for rectangles, and functions from a .qry file, the goal is to execute predetermined functions from the .qry file and show modifications each function does to the rectangles in a SVG and a text file. Important to notice that the rectangles ***must*** be stored in a double linked list.
  
  *In total there are 8 functions:*
  
  - TP: On the final SVG, only the rectangles that intercepts any other should appear, and fill color must be changed every pair formed.
  - TPR: Similar to TP, but only consider rectangles with intersections within a rectangle passed as an argument to the function.
  - DPI: Remove every rectangle that the point passed as an argument to the function is inner.
  - DR: Remove every rectangle that is inside a rectangle whose ID is passed to this function. 
  - BBI: Draw a bounding box containing all the rectangles that the point passed to this function is inner.
  - BBID: Analogous to BBI, but select all the rectangles that are inner to the rectangle whose ID is passed to this function.
  - IID: Report data from the passed ID and k elements before (*k* < 0) or after (*k* > 0) this rectangle. 
  - DIID: Similar to IID, but remove the rectangles (excluding the passed ID rectangle). 

#### *Concepts used:*
  - Information hiding.
  - Double Linked Lists.
  - Static Lists.
  - Introduction to SVG.
  - Introduction to using Cartesian plane with C language.

## Project-2:
  Same format of first project, however, now circles will be added too. The plot of this project is to consider the rectangles as buildings, and circles as people on a colony of "New Grimesland". There will be some radioactive meteors falling in the village with radiation level varying between [0, 25] mSv. Each side of the rectangles will produce a shadow that blocks 20% of the meteor radiation. Important to notice that rectangles and circles ***must*** be stored in K-Dimensional trees, shadows can be stored either on K-D or BS trees. Also, whenever is possible only search in promising sub-trees.
  
  *In total there are 6 functions:* 
  
  - DPI: Remove every rectangle that the point passed as an argument to the function is inner.
  - DR: Remove every rectangle that is inside a rectangle whose ID is passed to this function. 
  - FG: Given a point and a radius, every circle that is inside the FG circle, needs to find and run to the closest building, to shelter itself against the meteors. Also, in the SVG file the circles running to the closest building **should** be animated using *animateMotion*.
  - IM: Meteor with radiation *s* mSv impacted *point (x,y)*. Calculate the exposition class of every circle in the village, change its color to the designed class. The level of radiation each circle has is accumulative, if the person dies (radiation level > 8000), put a black fill and a cross on the circle.
  - T30: 30 minutes passed, circles with imminent death, dies.
  - NVE: Calculate the level of radiation of the given *point (x,y)*. For this, is important to consider every meteor that IM created (and fall in the village), every single shadow that every meteor created for this function.
  
  
  
#### *Concepts used:*
  - Information hiding.
  - Double Linked Lists.
  - Binary Trees.
  - Space partitioning using K-Dimensional Trees (in this case, using 2-D Trees).
  - Optimizing search on Trees.
  - Sorting data based on given criteria using qsort from *<stdlib.h>*.
  - Basic animation on SVG.
  - Introduction to basic Computational Geometry.
