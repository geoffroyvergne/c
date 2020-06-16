#include <iostream>
#include <array>

int main() {
    std::array<int,3> testArray1={ 10, 20, 30 };

    for(int i=0; i<testArray1.size(); i++) {
        ++testArray1[i];
    }

    for(int elem : testArray1) {
        std::cout << elem;
    }
    std::cout << std::endl;

    std::array<int,3> testArray2={ 1, 2, 3 };

    std::sort(testArray1.begin(), testArray1.end());
    std::reverse_copy(testArray2.begin(), testArray2.end(),
        std::ostream_iterator<int>(std::cout, " - "));

    std::cout << "\n";

    std::array<std::string, 2> testArray3={ std::string("a"), "b" };

    for(const auto& s : testArray3) {
        std::cout << s << ' ';
    }
}
