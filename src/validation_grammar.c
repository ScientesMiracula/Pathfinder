#include "../inc/validation.h"

static void skip_alphabetic_symbols(const char **ptr_to_start) {
    while (mx_isalpha(**ptr_to_start)) {
        (*(ptr_to_start))++;
    }
}

static void skip_digits(const char **ptr_to_start) {
    while (mx_isdigit(**ptr_to_start)) {
        (*(ptr_to_start))++;
    }
}

static int validate_bridge(const char *line) {
    char expectated_punctuation = '-';

    skip_alphabetic_symbols(&line);
    if (*line != expectated_punctuation) {
        return ERR_LINE_N;
    }
    line++;

    expectated_punctuation = ',';
    skip_alphabetic_symbols(&line);
    if (*line != expectated_punctuation) {
        return ERR_LINE_N;
    }
    line++;

    expectated_punctuation = '\0';
    skip_digits(&line);
    if (*line != expectated_punctuation) {
        return ERR_LINE_N;
    }
    return IS_VALID;
}

static int get_bridge_length(const char *line) {
    while (*line != ',') {
        line++;
    }
    line++;

    long long length = 0;
    while (mx_isdigit(*line)) {
        length *= 10;
        length += (*line) - '0';
        line++;
    }
    if (length < 0 || length / INT_MAX != 0) {
        return INT_MAX;
    }
    else {
        return length;
    }
}

int validate_grammar_and_length(const char **lines) {
    int validation_result;
    int line_n = 2;
    long long full_bridges_lengths = 0;

    for (const char **line = (lines + 1); *line != NULL;
         line++, line_n++) {
        validation_result = validate_bridge(*line);
        switch (validation_result) {
            case ERR_LINE_N:
                return ERR_LINE_N + line_n;
                break;

            case IS_VALID:
                break;
        }
        full_bridges_lengths += get_bridge_length(*line);
        if (full_bridges_lengths > INT_MAX) {
            return ERR_TOO_LARGE_ROUTE;
        }
    }

    return IS_VALID;
}
