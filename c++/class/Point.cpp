#include <iostream>
#include <cmath>
#include "Point.hpp"

Point::Point() {
    x = 0;
    y = 0;
}

Point::Point(double x, double y) {
    this->x = x;
    this->y = y;
}

void Point::setX(double x) {
    this->x = x;
}

double Point::getX() {
    return x;
}

void Point::setY(double y) {
    this->y = y;
}

double Point::getY() {
    return y;
}

double Point::distance(const Point &P) {
    double dx,dy;
    dx = x - P.x;
    dy = y - P.y;

    return sqrt(dx*dx + dy*dy);
}

Point Point::middle(const Point &P) {
    Point M;
    M.x = (P.x+x) / 2;
    M.y = (P.y+y) / 2;

    return M;
}

void Point::display() {
    std::cout << "X value : " << x << std::endl;
    std::cout << "Y value : " << y << std::endl;
}
