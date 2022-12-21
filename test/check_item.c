#include "item.h"
#include "db.h"
#include <check.h>
#include <stdlib.h>
#include <stdio.h>

START_TEST(test_item_init) {
    item_t *item = todo_item_new();

    ck_assert_ptr_nonnull(item);

    ck_assert_ptr_null(item->name);
    ck_assert_ptr_null(item->description);
    ck_assert_ptr_null(item->notes);
    ck_assert_int_eq(item->due, 0);
    ck_assert_int_eq(item->created, 0);
    ck_assert_int_eq(item->group_id, 0);

    todo_item_free(item);
}
END_TEST

START_TEST(test_item_build) {
    item_t *item = todo_item_build("Name", "Description", "Notes", 123456789, 987654321);

    ck_assert_ptr_nonnull(item);

    ck_assert_str_eq(item->name, "Name");
    ck_assert_str_eq(item->description, "Description");
    ck_assert_str_eq(item->notes, "Notes");
    ck_assert_int_eq(item->due, 123456789);
    ck_assert_int_eq(item->created, 987654321);
    ck_assert_int_eq(item->group_id, 0);

    todo_item_free(item);
}
END_TEST

START_TEST(test_item_save) {
    item_t *item = todo_item_build("Name", "Description", "Notes", 123456789, 987654321);

    todo_item_save(item);

    todo_item_free(item);
}
END_TEST

START_TEST(test_item_load) {
    item_t *item1 = todo_item_build("Name1", "Description1", "Notes1", 123456789, 987654321);
    item_t *item2 = todo_item_build("Name2", "Description2", "Notes2", 987654321, 123456789);
    todo_item_save(item1);
    todo_item_save(item2);

    item_list_t *items = todo_item_load();

    ck_assert_int_eq(items->items[0]->id, item1->id);
    ck_assert_str_eq(items->items[0]->name, item1->name);
    ck_assert_str_eq(items->items[0]->description, item1->description);
    ck_assert_str_eq(items->items[0]->notes, item1->notes);
    ck_assert_int_eq(items->items[0]->due, item1->due);
    ck_assert_int_eq(items->items[0]->created, item1->created);
    ck_assert_int_eq(items->items[0]->group_id, item1->group_id);

    ck_assert_int_eq(items->items[1]->id, item2->id);
    ck_assert_str_eq(items->items[1]->name, item2->name);
    ck_assert_str_eq(items->items[1]->description, item2->description);
    ck_assert_str_eq(items->items[1]->notes, item2->notes);
    ck_assert_int_eq(items->items[1]->due, item2->due);
    ck_assert_int_eq(items->items[1]->created, item2->created);
    ck_assert_int_eq(items->items[1]->group_id, item2->group_id);

    item_list_free_all(items);
}
END_TEST

START_TEST(test_item_load_one) {
    item_t *item1 = todo_item_build("Name1", "Description1", "Notes1", 123456789, 987654321);
    item_t *item2 = todo_item_build("Name2", "Description2", "Notes2", 987654321, 123456789);
    todo_item_save(item1);
    todo_item_save(item2);

    item_t *item1_loaded = todo_item_load_one(1);
    item_t *item2_loaded = todo_item_load_one(2);

    ck_assert_int_eq(item1_loaded->id, item1->id);
    ck_assert_str_eq(item1_loaded->name, item1->name);
    ck_assert_str_eq(item1_loaded->description, item1->description);
    ck_assert_str_eq(item1_loaded->notes, item1->notes);
    ck_assert_int_eq(item1_loaded->due, item1->due);
    ck_assert_int_eq(item1_loaded->created, item1->created);
    ck_assert_int_eq(item1_loaded->group_id, item1->group_id);

    ck_assert_int_eq(item2_loaded->id, item2->id);
    ck_assert_str_eq(item2_loaded->name, item2->name);
    ck_assert_str_eq(item2_loaded->description, item2->description);
    ck_assert_str_eq(item2_loaded->notes, item2->notes);
    ck_assert_int_eq(item2_loaded->due, item2->due);
    ck_assert_int_eq(item2_loaded->created, item2->created);
    ck_assert_int_eq(item2_loaded->group_id, item2->group_id);

    todo_item_free(item1);
    todo_item_free(item2);
    todo_item_free(item1_loaded);
    todo_item_free(item2_loaded);
}
END_TEST

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
    tcase_add_test(tc_data, test_item_save);
    tcase_add_test(tc_data, test_item_load);
    tcase_add_test(tc_data, test_item_load_one);

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
    todo_db_init(":memory:");

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);

    todo_db_shutdown();

    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}