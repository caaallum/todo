#include <stdlib.h>
#include <check.h>
#include "../todo_group_list.h"

const char *xml = \
"<group_list>" \
    "<group>"
        "<name>Group 1</name>" \
        "<items>" \
            "<item>" \
                "<name>Group 1 Item 1</name>" \
                "<description>Group 1 Item 1 description</description>" \
                "<notes>Group 1 Item 1 Notes</notes>" \
                "<due>1</due>" \
                "<created>2</created>" \
            "</item>" \
            "<item>" \
                "<name>Group 1 Item 2</name>" \
                "<description>Group 1 Item 2 description</description>" \
                "<notes>Group 1 Item 2 Notes</notes>" \
                "<due>2</due>" \
                "<created>1</created>" \
            "</item>" \
        "</items>" \
    "</group>" \
    "<group>" \
        "<name>Group 2</name>" \
        "<items>" \
            "<item>" \
                "<name>Group 2 Item 1</name>" \
                "<description>Group 2 Item 1 description</description>" \
                "<notes>Group 2 Item 1 Notes</notes>" \
                "<due>3</due>" \
                "<created>4</created>" \
            "</item>" \
        "</items>" \
    "</group>" \
"</group_list>";

START_TEST(test_load_all) {
    ptodo_group_list_t group_list = todo_group_list_load_all(xml);
    ck_assert_ptr_nonnull(group_list);
    
    size_t total = todo_group_list_get_total(group_list);

    ck_assert_int_eq(total, 2);

    for (size_t i = 0; i < total; i++) {
        ptodo_group_t group = todo_group_list_get(group_list, i);
    
        ck_assert_ptr_nonnull(group);

        const char *name = todo_group_get_name(group);

        switch (i) {
            case 0:
                ck_assert_str_eq(name, "Group 1");
                break;
            case 1:
                ck_assert_str_eq(name, "Group 2");
                break;
        }
    }

}
END_TEST

Suite *load_suite(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("Load");

    /* Core test case */
    tc_core = tcase_create("Core");
    tcase_add_test(tc_core, test_load_all);

    suite_add_tcase(s, tc_core);

    return s;
}

int main(void) {
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = load_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);

    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
