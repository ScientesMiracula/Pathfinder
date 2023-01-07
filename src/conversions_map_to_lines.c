#include "../inc/conversions.h"
#include "../inc/validation.h"

static void stderr_print(const char *err) {
    write(2, err, mx_strlen(err));
}

char **map_file_to_lines_with_grammar_validation(char **args) {
    int validation_result = validate_file(args[1]);
    switch (validation_result) {
        case IS_VALID:
        default:
            break;
        case ERR_FILE_NOT_EXIST:
            stderr_print("error: file ");
            stderr_print(args[1]);
            stderr_print(" does not exist\n");
            exit(0);
            break;
    }

    char *file_str = mx_file_to_str(args[1]);
    validation_result = validate_sizes(file_str);

    switch (validation_result) {
        case IS_VALID:
            break;
        case ERR_ISLANDS_NUMBER:
            stderr_print("error: invalid number of islands\n");
            break;
        default: {
            stderr_print("error: line ");
            char *temp_ptr = mx_itoa(validation_result - ERR_LINE_N);
            stderr_print(temp_ptr);
            free(temp_ptr);
            stderr_print(" is not valid\n");
            break;
        }
    }

    if (validation_result != IS_VALID) {
        free(file_str);
        exit(0);
    }

    char **lines = mx_strsplit(file_str, '\n');

    validation_result =
        validate_grammar_and_length((const char **)lines);

    switch (validation_result) {
        case IS_VALID:
            break;
        case ERR_TOO_LARGE_ROUTE:
            stderr_print("error: sum of bridges lengths is too big\n");
            break;
        default: {
            stderr_print("error: line ");
            char *temp_ptr = mx_itoa(validation_result - ERR_LINE_N);
            stderr_print(temp_ptr);
            free(temp_ptr);
            stderr_print(" is not valid\n");
            break;
        }
    }

    if (validation_result != IS_VALID) {
        free(file_str);
        mx_del_strarr(&(lines));
        exit(0);
    }

    return lines;
}
