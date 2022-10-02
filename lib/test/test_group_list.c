#include <stdlib.h>
#include <check.h>
#include "../todo_group_list.h"

START_TEST(test_group_list_init) {
    ptodo_group_list_t group_list = todo_group_list_new();

    ck_assert_ptr_nonnull(group_list);
    ck_assert_int_eq(todo_group_list_get_total(group_list), 0);

    todo_group_list_free(group_list);
}
END_TEST

START_TEST(test_group_list_add) {
    ptodo_group_list_t group_list = todo_group_list_new();

    ptodo_group_t group = todo_group_new();
    ptodo_group_t group1 = todo_group_new();
    ptodo_group_t group2 = todo_group_new();

    todo_group_list_add(group_list, group);
    ck_assert_int_eq(todo_group_list_get_total(group_list), 1);
    
    todo_group_list_add(group_list, group1);
    ck_assert_int_eq(todo_group_list_get_total(group_list), 2);

    todo_group_list_add(group_list, group2);
    ck_assert_int_eq(todo_group_list_get_total(group_list), 3);

    todo_group_list_free(group_list);
}
END_TEST

START_TEST(test_group_list_get) {
    ptodo_group_list_t group_list = todo_group_list_new();

    ptodo_group_t group = todo_group_new();
    ptodo_group_t group1 = todo_group_new();

    todo_group_list_add(group_list, group);
    todo_group_list_add(group_list, group1);

    ck_assert_ptr_eq(todo_group_list_get(group_list, 0), group);
    ck_assert_ptr_eq(todo_group_list_get(group_list, 1), group1);

    todo_group_list_free(group_list);
}
END_TEST

START_TEST(test_group_list_set) {
    ptodo_group_list_t group_list = todo_group_list_new();

    ptodo_group_t group = todo_group_new();
    ptodo_group_t group1 = todo_group_new();
    ptodo_group_t group2 = todo_group_new();
    ptodo_group_t group3 = todo_group_new();

    todo_group_list_add(group_list, group);
    todo_group_list_add(group_list, group1);
    todo_group_list_add(group_list, group2);

    ck_assert_ptr_eq(todo_group_list_get(group_list, 0), group);
    ck_assert_ptr_eq(todo_group_list_get(group_list, 1), group1);
    ck_assert_ptr_eq(todo_group_list_get(group_list, 2), group2);

    todo_group_list_set(group_list, 1, group3);

    ck_assert_ptr_eq(todo_group_list_get(group_list, 1), group3);

    todo_group_list_free(group_list);
}
END_TEST

START_TEST(test_group_list_delete) {
    ptodo_group_list_t group_list = todo_group_list_new();

    ptodo_group_t group = todo_group_new();
    ptodo_group_t group1 = todo_group_new();
    ptodo_group_t group2 = todo_group_new();

    todo_group_list_add(group_list, group);
    todo_group_list_add(group_list, group1);
    todo_group_list_add(group_list, group2);

    ck_assert_ptr_eq(todo_group_list_get(group_list, 0), group);
    ck_assert_ptr_eq(todo_group_list_get(group_list, 1), group1);
    ck_assert_ptr_eq(todo_group_list_get(group_list, 2), group2);

    todo_group_list_delete(group_list, 1);

    ck_assert_ptr_eq(todo_group_list_get(group_list, 0), group);
    ck_assert_ptr_eq(todo_group_list_get(group_list, 1), group2);

    todo_group_list_free(group_list);
}
END_TEST

Suite *group_list_suite(void) {
    Suite *s;
    TCase *tc_core, *tc_data;

    s = suite_create("Group List");

    /* Core test case */
    tc_core = tcase_create("Core");
    tcase_add_test(tc_core, test_group_list_init);

    /* Data test case */
    tc_data = tcase_create("Data");
    tcase_add_test(tc_data, test_group_list_add);
    tcase_add_test(tc_data, test_group_list_get);
    tcase_add_test(tc_data, test_group_list_set);
    tcase_add_test(tc_data, test_group_list_delete);

    suite_add_tcase(s, tc_core);
    suite_add_tcase(s, tc_data);

    return s;
}

int main(void) {
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = group_list_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_VERBOSE);
    number_failed = srunner_ntests_failed(sr);

    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}