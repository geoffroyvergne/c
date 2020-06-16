#include <iostream>

using namespace std;

template <class T>
T sum(T a, T b) {
    T result;
    result = a+b;
    return result;
}

int main() {
    int result = sum<int>(2, 6);
    cout << "Result : " << result << endl;

    return EXIT_SUCCESS;
}
