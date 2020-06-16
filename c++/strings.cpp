#include <iostream>
#include <string>

using namespace std;

#define TESTVALUE "test"

void displayText(string& text);

int main() {

    cout << "Hello World! " << endl;
    string testString;
    testString = "Test String! ";
    cout << testString << TESTVALUE << endl;

    for(char c : testString) {
        cout << "[" << c << "]";
    }
    cout << endl;

    displayText(testString);

    return EXIT_SUCCESS;
}

void displayText(string& text) {
    cout << "displayText : " << text << endl;
}
