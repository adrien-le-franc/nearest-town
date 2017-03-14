# nearest-town
this code is a basic program which purpose was to get familiar with quad-tree structure to stock cities' coordinates 
to perform efficient nearest neighbour research given a query French city. It was designed for my algorithm class at Ecole des Ponts

->"villes1" and "quadtree" contain tools that were provided and had to be completed / adapted to match the project. 
->tools.h computes a data structure to build a quadtree and stock 2D points and information from a database
->search.h computes nearest point research in the quadtree
->main.cpp exposes results, Part2.Q7 launches the research to find Paris' nearest neighbour

about the data base:

The file villes.txt contains the approximate coordinates (lattitudes
and longitudes in decimal degrees) of towns in Metropolitan France.
Note that, due to approximation, a few towns have identical coordinates.

This file has been derived from data available at web site
http://www.galichon.com/codesgeo/, which itself has been composed
from data available at INSEE and other organisms.

Please make sure that you read the warning at
http://www.galichon.com/codesgeo/avertissement.php
