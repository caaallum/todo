#include "db.h"
#include <check.h>
#include <stdlib.h>

START_TEST(test_db_init) {
    int rc = todo_db_init(":memory:");

    ck_assert_int_eq(rc, SQLITE_OK);

    todo_db_shutdown();
}
END_TEST

Suite *
db_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("Item");

  /* Core test case */
  tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_db_init);

  suite_add_tcase(s, tc_core);

  return s;
}

int
main(void) {
  int number_failed;
  Suite *s;
  SRunner *sr;

  s  = db_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);

  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}