#ifndef _ARGUMENTS
#define _ARGUMENTS

#include <argp.h>

struct arguments {
        char *args[1];
        int version;
        int help;
};

static struct argp_option options[] = {
        {"version", 'v', 0, 0, "Print lsmd version"},
        {0}
};

static char args_doc[] = "FILE";

static char doc[] = "lsmd -- A program for printing the duration of media files.\v";

static error_t parse_opt (int key, char *arg, struct argp_state *state) {
        struct arguments *arguments = state->input;

        switch (key)
        {
        case 'v':
                arguments->version = 1;
                break;
        case ARGP_KEY_ARG:
                if (state->arg_num >= 2)
                {
                        argp_usage(state);
                }
                arguments->args[state->arg_num] = arg;
                break;
        case ARGP_KEY_END:
                break;
        default:
                return ARGP_ERR_UNKNOWN;
        }
        return 0;
}

static struct argp argp = {options, parse_opt, args_doc, doc};

#endif
