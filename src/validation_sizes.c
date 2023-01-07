#include "../inc/validation.h"

static int validate_first_number(const char *file_str) {
    const char *file_ptr = file_str;

    while (*(file_ptr++) != '\n') {
        if (!mx_isdigit(*file_ptr)) {
            if (*file_ptr == '\n') {
                break;
            }
            else {
                return ERR_LINE_N + 1;
            }
        }
    }

    return IS_VALID;
}

int validate_sizes(const char *str) {
    int validation_result = validate_first_number(str);

    if (validation_result != IS_VALID) {
        return validation_result;
    }

    return IS_VALID;
}
