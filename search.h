#pragma once
#include"tools.h"

template <typename T>
void neighbors(QuadTree<Point2D<T> >* Q, const Point2D<T> &P, float &r, vector<Point2D<T> >& V, square S, const bool& best, int& counter){
    for(int i=0; i<4; i++){
        if(Q->son(i)==nullptr)
            continue;
        if(Q->son(i)->isLeaf()){
            if(P.dist2(Q->son(i)->value())<=r*r){
                    if(Q->son(i)->value()==P){  // excludes the town itself from the search
                        continue;
                    }
                    if(best){                              // if searching nearest town
                        r = P.dist(Q->son(i)->value());
                        V[0] = Q->son(i)->value();
                    }
                    else                                  // if searching nearest towns
                        V.push_back(Q->son(i)->value());
                }
        }
        else{
            counter++;          // counts number of nodes encountered
            S.next_square(i);
            if(S.intersects_disk(P,r))
                neighbors(Q->son(i),P,r,V,S,best,counter);
            S.previous_square(i);    // previous square corresponding to the node whose children are being inspected in the loop
        }
    }
}


