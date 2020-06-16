#include <iostream>

class Rectangle {
    int width, height;

    public:
        Rectangle();
        Rectangle(int a,int b) {
            width = a;
            height = b;
        }
        //void setValues(int,int);
        int area() {
            return width * height;
        }
};

Rectangle::Rectangle() {
    width = 5;
    height = 5;
}

/*void Rectangle::setValues(int x, int y) {
    width = x;
    height = y;
}*/

int main() {
    /*Rectangle rectangleA, rectangleB;
    rectangleA.setValues(3, 4);
    rectangleB.setValues(5, 6);*/

    Rectangle rectangleA(3, 4);
    Rectangle rectangleB(4, 5);

    std::cout << "area A : " << rectangleA.area() << std::endl;
    std::cout << "area B : " << rectangleB.area() << std::endl;

    return EXIT_SUCCESS;
}