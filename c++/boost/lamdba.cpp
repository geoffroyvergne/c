/*
g++ lamdba.cpp -o bin/lambda
echo 1 2 3 | bin/lambda
*/


#include <boost/lambda/lambda.hpp>
#include <iostream>
#include <algorithm>

int main() {
    using namespace boost::lambda;
    typedef std::istream_iterator<int> in;

    std::for_each(
        in(std::cin), in(), std::cout << (_1 * 3) << " ");
}