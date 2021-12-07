# Data Structures projects

Some the projects I made through Data structures, from second and third semester on Computer Science course of UEL. (State University of Londrina).

On every project, it is ***strictly prohibited*** declaring structs on headers files.

 ## First project
  Given a file .geo containing data for rectangles, and functions from a .qry file, the goal is to execute predetermined functions from the .qry file and show modifications each function does to the rectangles in a SVG and a text file.
  
  Important to notice that the rectangles ***must*** be stored in a double linked list.
  
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


![project1-2](https://user-images.githubusercontent.com/65873681/145121677-c0884bcc-2b55-412e-b452-372ba7e37e29.png)

Example of a tp and a bbi function execution

## Second project
  Same format of first project, however, now circles will be added too.
  
  The plot of this project is to consider the rectangles as buildings, and circles as people on a colony of "New Grimesland". There will be some radioactive meteors falling in the village with radiation level varying between [0, 25] mSv. Each side of the rectangles will produce a shadow that blocks 20% of the meteor radiation.
  
  ![radiation](https://user-images.githubusercontent.com/65873681/145122040-dcae2187-9f30-4f0c-a286-8955265773ae.png)
  ![bombs](https://user-images.githubusercontent.com/65873681/145122075-a0a07c2e-f4f7-4c04-82a0-23129cd14cce.png)


  
  Important to notice that rectangles and circles ***must*** be stored in K-Dimensional trees, shadows can be stored either on K-D or BS trees. Also, whenever is possible only search in promising sub-trees.
  
  *In total there are 6 functions:* 
  
  - DPI: Remove every rectangle that the point passed as an argument to the function is inner.
  - DR: Remove every rectangle that is inside a rectangle whose ID is passed to this function. 
  - FG: Given a point and a radius, every circle that is inside the FG circle, needs to find and run to the closest building, to shelter itself against the meteors. Also, in the SVG file the circles running to the closest building **should** be animated using *animateMotion*.
  - IM: Meteor with radiation *s* mSv impacted *point (x,y)*. Calculate the exposition class of every circle in the village, change its color to the designed class. The level of radiation each circle has is accumulative, if the person dies (radiation level > 8000), put a black fill and a cross on the circle.
  - T30: 30 minutes passed, circles with imminent death, dies.
  - NVE: Calculate the level of radiation of the given *point (x,y)*. For this, is important to consider every meteor that IM created (and fell in the village), every single shadow that every meteor created for this function.

  #### *Concepts used:*
  - Information hiding.
  - Double Linked Lists.
  - Binary Trees.
  - Space partitioning using K-Dimensional Trees (in this case, using 2-D Trees).
  - Optimizing search on Trees.
  - Sorting data based on given criteria using qsort from *<stdlib.h>*.
  - Basic animation on SVG.
  - Introduction to basic Computational Geometry.

![project2](https://user-images.githubusercontent.com/65873681/145121899-ae892ba2-bea4-480d-9940-da6b5a78eb95.png)

Example of a fg function (animated with <animatemotion>)

## Third project
 Same format of the previous two projects, with .geo files and .qry. However, on this project we're doing a city map, using information of buildings, people and locations.
 
 Every building has a ZIP code, face, and number.
 
 Every person has a SSN (social security number), a name, a surname, sex and birth date.
 
 Also, the locations can be rented.
 
 The plot is to build a system to manipulate the map of a city and some relatable info. The map of a city is composed by a rectangle set representing the buildings.
 The number of a house or store is the distance of the front of the place to a anchor point.
 
 Also, the buildings ***must*** be stored on lists of buildings with the same x coordinate. Then this list is stored inside a node of the AVL tree.
 
 All persons and locations ***must*** be stored on hash tables.
 
 (P.S - I also stored the buildings on hash tables using the ZIP code to optimize search).
 
 ![project3](https://user-images.githubusercontent.com/65873681/145122300-6c4301d6-d854-494a-9ba2-d4e4ad89bc4f.png)
 ![p3](https://user-images.githubusercontent.com/65873681/145122686-99d3e7c7-9909-4eb0-aa28-9b38a8e1eb7d.png)

 *In total there are 13 functions:* 
 
  - del: Given a ZIP code, remove all the persons living here, as well the locations available.
  - m?: List all the persons that lives on the given ZIP code.
  - dm?: Show all the person data given the specific SSN.
  - mud: The person with given SSN number move to another place (given new ZIP code, number, face).
  - oloc: Add a new location offer to the given ZIP code.
  - oloc?: Show all available locations inside a given rectangle.
  - loc: The person with given SSN number rent location identified with given ID.
  - loc?: Show the situation of a specific location (given ID).
  - dloc: The person living on location (with given ID) end the contract, the location offer is removed.
  - hom: Show the info of all men inside a given rectangle.
  - mul: Show the info of all woman inside a given rectangle.
  - dmpt: Generate the .dot file with the current state of the AVL tree.
  - catac: Remove buildings, persons, and locations offers inside given rectagle.
  
  #### *Concepts used:*
  - Information hiding.
  - Double Linked Lists.
  - AVL Trees.
  - Hash Tables.
  - Computational Geometry.
  - Optimizing search on Trees.
