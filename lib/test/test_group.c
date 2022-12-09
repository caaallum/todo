#include "../todo_group.h"
#include <check.h>
#include <stdlib.h>

START_TEST(test_group_init) {
    todo_group_t *group = todo_group_new();

    ck_assert_ptr_nonnull(group);
    ck_assert_ptr_null(group->name);
    ck_assert_int_eq(todo_group_get_total(group), 0);

    todo_group_free(group);
}
END_TEST

START_TEST(test_group_build) {
    static char name[] = "Group Name";

    todo_group_t *group = todo_group_build(name);

    ck_assert_ptr_nonnull(group);
    ck_assert_str_eq(group->name, name);
    ck_assert_int_eq(todo_group_get_total(group), 0);

    todo_group_free(group);
}
END_TEST

START_TEST(test_group_add) {
    todo_group_t *group = todo_group_new();

    todo_item_t *item  = todo_item_new();
    todo_item_t *item2 = todo_item_new();

    todo_group_add(group, item);
    ck_assert_int_eq(todo_group_get_total(group), 1);
    todo_group_add(group, item2);
    ck_assert_int_eq(todo_group_get_total(group), 2);

    ck_assert_ptr_eq(todo_group_get(group, 0), item);
    ck_assert_ptr_eq(todo_group_get(group, 1), item2);

    todo_group_free(group);
}
END_TEST

START_TEST(test_group_set) {
    todo_group_t *group = todo_group_new();

    todo_item_t *item  = todo_item_new();
    todo_item_t *item2 = todo_item_new();
    todo_item_t *item3 = todo_item_new();
    todo_item_t *item4 = todo_item_new();

    todo_group_add(group, item);
    ck_assert_int_eq(todo_group_get_total(group), 1);
    todo_group_add(group, item2);
    ck_assert_int_eq(todo_group_get_total(group), 2);
    todo_group_add(group, item3);
    ck_assert_int_eq(todo_group_get_total(group), 3);

    ck_assert_ptr_eq(todo_group_get(group, 0), item);
    ck_assert_ptr_eq(todo_group_get(group, 1), item2);
    ck_assert_ptr_eq(todo_group_get(group, 2), item3);

    todo_group_set(group, 1, item4);
    ck_assert_ptr_eq(todo_group_get(group, 1), item4);
}
END_TEST

START_TEST(test_group_delete) {
    todo_group_t *group = todo_group_new();

    todo_item_t *item  = todo_item_new();
    todo_item_t *item2 = todo_item_new();

    todo_group_add(group, item);
    todo_group_add(group, item2);

    ck_assert_int_eq(todo_group_get_total(group), 2);

    todo_group_delete(group, 0);

    ck_assert_int_eq(todo_group_get_total(group), 1);

    ck_assert_ptr_eq(todo_group_get(group, 0), item2);

    todo_group_free(group);
}
END_TEST

Suite *
group_suite(void) {
    Suite *s;
    TCase *tc_core, *tc_data;

    s = suite_create("Group");

    /* Core test case */
    tc_core = tcase_create("Core");
    tcase_add_test(tc_core, test_group_init);
    tcase_add_test(tc_core, test_group_build);

    /* Data test case */
    tc_data = tcase_create("Data");
    tcase_add_test(tc_data, test_group_add);
    tcase_add_test(tc_data, test_group_set);
    tcase_add_test(tc_data, test_group_delete);

    suite_add_tcase(s, tc_core);
    suite_add_tcase(s, tc_data);

    return s;
}

int
main(void) {
    int number_failed;
    Suite *s;
    SRunner *sr;

    s  = group_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);

    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
