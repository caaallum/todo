#include "../todo_group_list.h"
#include <check.h>
#include <stdio.h>
#include <stdlib.h>

const char *xml =
        "<group_list>"
        "<group>"
        "<name>Group 1</name>"
        "<items>"
        "<item>"
        "<name>Group 1 Item 1</name>"
        "<description>Group 1 Item 1 description</description>"
        "<notes>Group 1 Item 1 Notes</notes>"
        "<due>1</due>"
        "<created>2</created>"
        "</item>"
        "<item>"
        "<name>Group 1 Item 2</name>"
        "<description>Group 1 Item 2 description</description>"
        "<notes>Group 1 Item 2 Notes</notes>"
        "<due>2</due>"
        "<created>1</created>"
        "</item>"
        "</items>"
        "</group>"
        "<group>"
        "<name>Group 2</name>"
        "<items>"
        "<item>"
        "<name>Group 2 Item 1</name>"
        "<description>Group 2 Item 1 description</description>"
        "<notes>Group 2 Item 1 Notes</notes>"
        "<due>3</due>"
        "<created>4</created>"
        "</item>"
        "</items>"
        "</group>"
        "</group_list>";

START_TEST(test_load_all) {
    todo_group_list_t *group_list = todo_group_list_load_all(xml);
    ck_assert_ptr_nonnull(group_list);

    size_t total = todo_group_list_get_total(group_list);

    ck_assert_int_eq(total, 2);

    /* Check group1 in parsed group list */
    todo_group_t *group1 = todo_group_list_get(group_list, 0);
    ck_assert_ptr_nonnull(group1);

    ck_assert_str_eq(group1->name, "Group 1");
    ck_assert_int_eq(todo_group_get_total(group1), 2);

    todo_item_t *group1_item1 = todo_group_get(group1, 0);
    ck_assert_ptr_nonnull(group1_item1);

    ck_assert_str_eq(group1_item1->name, "Group 1 Item 1");
    ck_assert_str_eq(group1_item1->description, "Group 1 Item 1 description");
    ck_assert_str_eq(group1_item1->notes, "Group 1 Item 1 Notes");
    ck_assert_int_eq(group1_item1->due, 1);
    ck_assert_int_eq(group1_item1->created, 2);

    todo_item_t *group1_item2 = todo_group_get(group1, 1);
    ck_assert_ptr_nonnull(group1_item2);

    ck_assert_str_eq(group1_item2->name, "Group 1 Item 2");
    ck_assert_str_eq(group1_item2->description, "Group 1 Item 2 description");
    ck_assert_str_eq(group1_item2->notes, "Group 1 Item 2 Notes");
    ck_assert_int_eq(group1_item2->due, 2);
    ck_assert_int_eq(group1_item2->created, 1);

    /* Check group2 in parsed group list */
    todo_group_t *group2 = todo_group_list_get(group_list, 1);
    ck_assert_ptr_nonnull(group2);

    ck_assert_str_eq(group2->name, "Group 2");

    ck_assert_int_eq(todo_group_get_total(group2), 1);

    todo_item_t *group2_item1 = todo_group_get(group2, 0);
    ck_assert_ptr_nonnull(group2_item1);

    ck_assert_str_eq(group2_item1->name, "Group 2 Item 1");
    ck_assert_str_eq(group2_item1->description, "Group 2 Item 1 description");
    ck_assert_str_eq(group2_item1->notes, "Group 2 Item 1 Notes");
    ck_assert_int_eq(group2_item1->due, 3);
    ck_assert_int_eq(group2_item1->created, 4);

    todo_group_list_free(group_list);
}
END_TEST

Suite *
load_suite(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("Load");

    /* Core test case */
    tc_core = tcase_create("Core");
    tcase_add_test(tc_core, test_load_all);

    suite_add_tcase(s, tc_core);

    return s;
}

int
main(void) {
    int number_failed;
    Suite *s;
    SRunner *sr;

    s  = load_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);

    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
