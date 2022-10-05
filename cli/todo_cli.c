#include <glib.h>
#include "../config.h"
#include <stdio.h>

int main(int argc, char **argv) {
    static gboolean display_version = FALSE;
    static gchar *command = NULL;
    GError *error = NULL;
    GOptionContext *option_context;
    static GOptionEntry entries[] = {
        { "version", 'V', 0, G_OPTION_ARG_NONE, &display_version,
          "Display version information", NULL },
        { "command", 0, 0, G_OPTION_ARG_NONE, &command,
          "Command to run", NULL },

        { NULL, 0, 0, 0, NULL, NULL, NULL }
    };

    option_context = g_option_context_new(NULL);
    g_option_context_add_main_entries(option_context, entries, NULL);

    if (!g_option_context_parse(option_context, &argc, &argv, &error)) {
        g_print("%s\n\n", error->message);
        return EXIT_SUCCESS;
    }
    g_option_context_free(option_context);

    if (display_version) {
        printf("todo_cli %s\n", VERSION);
        return EXIT_SUCCESS;
    }

    return 0;
}
