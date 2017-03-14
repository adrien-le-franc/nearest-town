#include "tools.h"
#include<cassert>

square::square(){}
square::square(Point_2D A, Point_2D B){
    TL = A;
    BR = B;
}

void square::next_square(int X){
    if(X==NE){
        BR = Point_2D((TL.x()+BR.x())/2, (TL.y()+BR.y())/2);
    }
    else if(X==NW){
        TL = Point_2D((TL.x()+BR.x())/2, TL.y());
        BR = Point_2D(BR.x(), (TL.y()+BR.y())/2) ;
    }
    else if(X==SW)
        TL = Point_2D((TL.x()+BR.x())/2, (TL.y()+BR.y())/2);
    else if(X==SE){
        TL = Point_2D(TL.x(), (TL.y()+BR.y())/2);
        BR = Point_2D((TL.x()+BR.x())/2, BR.y());
    }
    else{
        cout<< "error: undefined x" <<endl;
        exit(1);
    }
}

void square::previous_square(int X){
    int L = BR.x()-TL.x();
    if(X==NE){
        BR = Point_2D(BR.x()+L, BR.y()+L);
    }
    else if(X==NW){
        TL = Point_2D(TL.x()-L, TL.y());
        BR = Point_2D(BR.x(), BR.y()+L) ;
    }
    else if(X==SW)
        TL = Point_2D(TL.x()-L, TL.y()-L);
    else if(X==SE){
        TL = Point_2D(TL.x(), TL.y()-L);
        BR = Point_2D(BR.x()+L, BR.y());
    }
    else{
        cout<< "error: undefined x" <<endl;
        exit(1);
    }
}

int square::subsquare(Point_2D X) const{
    float Ix = (TL.x()+BR.x())/2;
    float Iy = (TL.y()+BR.y())/2; // I middle of square defined by TL and BR

    if(X.x()>=Ix && X.y()>=Iy)
        return SW;
    if(X.x()>=Ix && X.y()<Iy)
        return NW;
    if(X.x()<Ix && X.y()>=Iy)
        return SE;
    if(X.x()<Ix && X.y()<Iy)
        return NE;
    else{
        cout<< "error: X not in square" <<endl;
        exit(1);
    }
}

bool square::intersects_disk(const Point_2D &P, float r) const{
    Point_2D ND(P.x(), P.y()-r);
    Point_2D SD(P.x(), P.y()+r);
    Point_2D ED(P.x()-r, P.y());
    Point_2D WD(P.x()+r, P.y()); // N,S,E,W of disk

    if((ED.x()<=BR.x() && WD.x()>=TL.x()) && (ND.y()<=BR.y() && SD.y()>=TL.y())) // test on intersection of intervals ie 1D projections
        return true;
    return false;
}
