#include "search.h"
#include "villes1/town.h"

#ifndef srcPath
#define srcPath "."
#endif
// The path and name of the town file
string townFile = srcPath "/villes1/villes.txt";

int main()
{   ////////// Part 1: tests with type Point2D<int> ////////

    srand((unsigned int) time(0));

    vector<Point2D<int> > V;
    for(int i=0; i<10; i++)
        V.push_back(Point2D<int>(rand()%100, rand()%100, 1));

        //2: stocking and displaying Point2D<int>

    QuadNode<Point2D<int> >* Q = MakeTree2D(V, Point_2D(0,0), Point_2D(100,100));
    //display(Q);

        //3,4: nearest points, nearest point

    vector<Point2D<int> > W;
    W.push_back(Point2D<int>(0,0,0)); // init W[0] to stock nearest point if best == true
    square S(Point_2D(0,0), Point_2D(100,100));
    float r = 50;
    bool best = true;
    int counter = 0;

    neighbors(Q, Point2D<int>(50,50,1),r,W,S,best, counter);
    //cout<< W[0].x() <<" ; "<< W[0].y() << endl;

    delete Q;

    ////////// Part 2: working with type Point2D<Town> ////////

    vector<Town> T;
    float xmin, ymin, xmax, ymax;
    int N = Town::read_file(townFile,T,xmin,ymin,xmax,ymax); // loads townFile
    cout<<N<<endl;
    cout<<"TL: ("<<xmin<<","<<ymin<<")"<<" BR: ("<<xmax<<","<<ymax<<")"<<endl; // TopLeft, BottomRight

    vector<Point2D<Town> > C;
    for(int i=0; i<N; i++){
        C.push_back(Point2D<Town>(T[i].x(), T[i].y(), T[i])); // Lambert 93 coordinates + Town
    }

        //5,6: loading towns in a QuadTree, returning nbTrees

    float dim = max(xmax,ymax);
    QuadNode<Point2D<Town> >* QTTown = MakeTree2D(C,Point_2D(0,0), Point_2D(dim,dim));
    cout<<"leaves: "<<QTTown->nbLeaves()<<endl;
    cout<<"nodes: "<<QTTown->nbNodes()<<endl;
    cout<<"trees: "<<QTTown->nbTrees()<<endl;

        //7: Paris' nearest town

    Town Ponts("Paris", 48.866667, 2.333333);
    vector<Point2D<Town> > search;
    search.push_back(Point2D<Town>(Ponts.x(), Ponts.y(), Ponts)); // init search[0] to stock nearest town
    square Perimeter(Point_2D(0,0), Point_2D(dim,dim));
    r = 10;
    counter = 0;

    neighbors(QTTown, Point2D<Town>(Ponts.x(),Ponts.y(),Ponts), r, search, Perimeter, best, counter);
    cout<< "nearest town:" << ((search[0]).info()).name() <<endl;
    cout<< counter <<endl;

        //8: average time

    vector<Point2D<Town> > Random; // will stock 1000 random towns
    int j;
    for(int i=0; i<1000; i++){
        j = rand()%N;
        Random.push_back(C[j]);
    }

    clock_t t1 = clock();
    for(int i=0; i<1000; i++){
        r = 10;
        neighbors(QTTown,Random[i],r,search,Perimeter,best,counter);
    }
    clock_t t2 = clock();
    cout<<"quadtree: t = "<<(float)(t2-t1)/CLOCKS_PER_SEC<<" seconds"<<endl; // tests time with QuadTree


    t1 = clock();
    for(int i=0; i<1000; i++){
        r = 10;
        for(int k=0; k<N; k++){
            if(Random[i].dist2(C[k])<=r){
                r = Random[i].dist2(C[k]);
                search[0] = C[k];
            }
        }
    }
    t2 = clock();
    cout<<"vector : t = "<<(float)(t2-t1)/CLOCKS_PER_SEC<<" seconds"<<endl; // tests time with vector


    delete QTTown;
    return 0;
}
