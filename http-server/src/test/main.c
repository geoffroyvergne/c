#include <stdio.h>
#include <CUnit/Basic.h>
#include <unit-tests.h>

void basicTest1(void) {
  CU_ASSERT(2+2 == 4);
}

void basicTest2(void) {
  CU_ASSERT(1+1 == 2);
}

int init_suite1(void){ return 0; }

int clean_suite1(void){ return 0; }

int main(int argc, char **argv) {

  CU_pSuite pSuite = NULL;

  /* initialize the CUnit test registry */
  if (CUE_SUCCESS != CU_initialize_registry())
    return CU_get_error();

   /* add a suite to the registry */
   pSuite = CU_add_suite("Suite_1", init_suite1, clean_suite1);
   if (NULL == pSuite) {
      CU_cleanup_registry();
      return CU_get_error();
   }

   /* add the tests to the suite */
   /* NOTE - ORDER IS IMPORTANT - MUST TEST fread() AFTER fprintf() */
   if (
      (NULL == CU_add_test(pSuite, "test of basicTest1()", basicTest1)) ||
      (NULL == CU_add_test(pSuite, "test of basicTest2()", basicTest2)) ||
      (NULL == CU_add_test(pSuite, "test of basicHttpTest1()", basicHttpTest1)) ||
      (NULL == CU_add_test(pSuite, "test of basicHttpTest2()", basicHttpTest2))
      )
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

  /* Run all tests using the CUnit Basic interface */
  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  CU_cleanup_registry();
  return CU_get_error();
}
