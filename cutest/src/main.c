#include <stdio.h>
#include "CuTest.h"

void TestBasic(CuTest *tc) {
    CuAssertIntEquals(tc, 2+2, 4);
}

CuSuite* TestBasicSuite() {
    CuSuite* suite = CuSuiteNew();
    SUITE_ADD_TEST(suite, TestBasic);
    return suite;
}

void RunAllTests(void) {
    CuString *output = CuStringNew();
    CuSuite* suite = CuSuiteNew();
    
    CuSuiteAddSuite(suite, TestBasicSuite());

    CuSuiteRun(suite);
    CuSuiteSummary(suite, output);
    CuSuiteDetails(suite, output);
    printf("%s\n", output->buffer);
}

int main(int argc, char **argv) {
    printf("cutest\n");

    RunAllTests();

    return 0;
}
