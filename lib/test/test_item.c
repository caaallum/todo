#include "../todo_item.h"
#include <check.h>
#include <stdlib.h>

START_TEST(test_item_init) {
    todo_item_t *item = todo_item_new();

    ck_assert_ptr_nonnull(item);
    ck_assert_ptr_null(item->name);
    ck_assert_ptr_null(item->description);
    ck_assert_ptr_null(item->notes);

    ck_assert_uint_eq(item->due, 0);
    ck_assert_uint_eq(item->created, 0);

    todo_item_free(item);
}
END_TEST

START_TEST(test_item_build) {
    static char name[]           = "Item Name";
    static char description[]    = "Item Description";
    static char notes[]          = "Item Notes";
    static unsigned long due     = 1;
    static unsigned long created = 2;

    todo_item_t *item = todo_item_build(name, description, notes, due, created);

    ck_assert_ptr_nonnull(item);
    ck_assert_str_eq(item->name, name);
    ck_assert_str_eq(item->description, description);
    ck_assert_str_eq(item->notes, notes);
    ck_assert_uint_eq(item->due, due);
    ck_assert_uint_eq(item->created, created);

    todo_item_free(item);
}
END_TEST

START_TEST(test_item_set_name) {
    static char name[] = "Item name";

    todo_item_t *item = todo_item_new();

    todo_item_set_name(item, name);

    ck_assert_str_eq(item->name, name);

    todo_item_free(item);
}
END_TEST

START_TEST(test_item_set_description) {
    static char description[] = "Item description";

    todo_item_t *item = todo_item_new();

    todo_item_set_description(item, description);

    ck_assert_str_eq(item->description, description);

    todo_item_free(item);
}
END_TEST

START_TEST(test_item_set_notes) {
    static char notes[] = "Item notes";

    todo_item_t *item = todo_item_new();

    todo_item_set_notes(item, notes);

    ck_assert_str_eq(item->notes, notes);

    todo_item_free(item);
}
END_TEST

START_TEST(test_item_set_due) {
    static unsigned long due = 123456;

    todo_item_t *item = todo_item_new();

    item->due = due;

    ck_assert_uint_eq(item->due, due);

    todo_item_free(item);
}
END_TEST

START_TEST(test_item_set_created) {
    static unsigned long created = 123456;

    todo_item_t *item = todo_item_new();

    item->created = created;

    ck_assert_uint_eq(item->created, created);

    todo_item_free(item);
}

Suite *
item_suite(void) {
    Suite *s;
    TCase *tc_core, *tc_data;

    s = suite_create("Item");

    /* Core test case */
    tc_core = tcase_create("Core");
    tcase_add_test(tc_core, test_item_init);
    tcase_add_test(tc_core, test_item_build);

    /* Data test case */
    tc_data = tcase_create("Data");
    tcase_add_test(tc_data, test_item_set_name);
    tcase_add_test(tc_data, test_item_set_description);
    tcase_add_test(tc_data, test_item_set_notes);
    tcase_add_test(tc_data, test_item_set_due);
    tcase_add_test(tc_data, test_item_set_created);

    suite_add_tcase(s, tc_core);
    suite_add_tcase(s, tc_data);

    return s;
}

int
main(void) {
    int number_failed;
    Suite *s;
    SRunner *sr;

    s  = item_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);

    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
