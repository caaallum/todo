#include "str.h"
#include <check.h>
#include <stdlib.h>

START_TEST(test_set_string) {
    static char src[] = "Test string";
    char *dest;

    todo_set_string(&dest, src);

    ck_assert_str_eq(dest, src);

    free(dest);
}
END_TEST

START_TEST(test_asprintf) {
    char *out;

    asprintf(&out, "hello %s", "world");

    ck_assert_str_eq(out, "hello world");

    free(out);
}
END_TEST

Suite *
str_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("Item");

  /* Core test case */
  tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_set_string);
  tcase_add_test(tc_core, test_asprintf);

  suite_add_tcase(s, tc_core);

  return s;
}

int
main(void) {
  int number_failed;
  Suite *s;
  SRunner *sr;

  s  = str_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);

  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}