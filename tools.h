#pragma once
#include "quadtree/quadtree.h"
#include "villes1/point2d.h"
#include<vector>
#include<cassert>
#include<iostream>
#include<ctime>

using namespace std;

class square{
public:
    Point_2D TL; //TopLeft
    Point_2D BR; //BottomRight

    square();
    square(Point_2D A, Point_2D B);
    void next_square(int X);
    void previous_square(int X);
    int subsquare(Point_2D X) const;
    bool intersects_disk(const Point_2D& P, float r) const;
};

template <typename T>
QuadNode<Point2D<T> >* MakeTree2D(const vector<Point2D<T> >& V, Point_2D TopLeft, Point_2D BottomRight){
    assert(TopLeft.x()<BottomRight.x() && TopLeft.y()<BottomRight.y()); // makes sure the square is defined
    assert(BottomRight.x()-TopLeft.x() == BottomRight.y()-TopLeft.y()); // makes sure the square is a square

    QuadNode<Point2D<T> >* QT = new QuadNode<Point2D<T> >(); // init: empty QuadNode
    QuadTree<Point2D<T> >* rqt = QT; // pointing at running QuadTree
    square S;
    Point2D<T>* transitory;

    for(typename vector<Point2D<T> >::const_iterator it=V.begin(); it!=V.end(); it++){

        S.TL = TopLeft; S.BR = BottomRight;
        int X = S.subsquare(*it);

        while(true){                   // moving down the nodes
            if(rqt->son(X)==nullptr)
                break;
            if(rqt->son(X)->isLeaf()) // can be tested after being sure that son(X) is not nullptr
                break;
            rqt = rqt->son(X);
            S.next_square(X);
            X = S.subsquare(*it);
        }

        if(rqt->son(X)==nullptr){
            rqt->son(X) = new QuadLeaf<Point2D<T> >(*it);
            rqt = QT;
            continue;
        }
        if((rqt->son(X))->isLeaf()){
            if(*it==rqt->son(X)->value()) // ignores a point if it is already in tree
                continue;
            transitory = &(rqt->son(X))->value(); // stocks value in the Leaf before changing to a Node
            rqt->son(X) = new QuadNode<Point2D<T> >();
            rqt = rqt->son(X);
            S.next_square(X);
            X = S.subsquare(*it);
            while(true){                               // subdivise square untill both points are in separated squares
                if(X!=S.subsquare(*transitory))
                    break;
                rqt->son(X) = new QuadNode<Point2D<T> >();
                rqt = rqt->son(X);
                S.next_square(X);
                X = S.subsquare(*it);
            }
            rqt->son(X) = new QuadLeaf<Point2D<T> >(*it);
            rqt->son(S.subsquare(*transitory)) = new QuadLeaf<Point2D<T> >(*transitory);
            rqt = QT;
        }
    }
    return QT;
}
