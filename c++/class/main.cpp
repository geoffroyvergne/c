#include <iostream>
#include "Point.hpp"

int main() {
    Point A, B, C;
    double d;

    A.setX(3);
    A.setY(5);

    B.setX(2);
    B.setY(6);

    C.setX(7);
    C.setY(9);

    C = A.middle(B);
    d = A.distance(B);

    std::cout << "X value : " << C.getX() << std::endl;
    std::cout << "Y value : " << C.getY() << std::endl;
    std::cout << "Distance AB : " << d << std::endl;

    return EXIT_SUCCESS;
}
