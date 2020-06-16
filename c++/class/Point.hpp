#ifndef POINT_H
#define POINT_H

class Point {
    private:
        double x,y;

    public:
        Point();
        Point(double x, double y);
        
        void setX(double x);
        double getX();

        void setY(double y);
        double getY();

        double distance(const Point &P);
        Point middle(const Point &P);

        //void set();
        void display();
};

#endif
