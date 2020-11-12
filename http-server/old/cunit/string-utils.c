#include <stdio.h>
#include <stdlib.h>
#include <CUnit/Basic.h>
#include <string-utils.h>

void testStringUtils(void) {
  CU_ASSERT(2+2 == 4);
  CU_ASSERT(1+1 == 2);

  char testString1[] = "testToLowerCase";
  char *testValue1 = toLowerCase(testString1);
    
  CU_ASSERT(strcmp(testValue1, "testtolowercase") == 0);

  char testString2[] = "testToUpperCase";
  char *testValue2 = toUpperCase(testString2);
    
  CU_ASSERT(strcmp(testValue2, "TESTTOUPPERCASE") == 0);

  char testString3[] = " testTrim ";
  char *testValue3 = trim(testString3);

  CU_ASSERT(strcmp(testValue3, "testTrim") == 0);
}
