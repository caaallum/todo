#include "group.h"
#include "db.h"
#include <check.h>
#include <stdlib.h>

START_TEST(test_group_init) {
    group_t *group = group_new();

    ck_assert_ptr_nonnull(group);

    ck_assert_int_eq(group->id, 0);
    ck_assert_ptr_null(group->name);
    ck_assert_ptr_nonnull(group->items);

    group_free(group);
}
END_TEST

Suite *
group_suite(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("Group");

    /* Core test case */
    tc_core = tcase_create("Core");
    tcase_add_test(tc_core, test_group_init);

    suite_add_tcase(s, tc_core);

    return s;
}

int
main(void) {
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = group_suite();
    sr = srunner_create(s);
    todo_db_init(":memory:");

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);

    todo_db_shutdown();

    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
