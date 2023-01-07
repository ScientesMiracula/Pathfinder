#ifndef VALIDATION
#define VALIDATION

#include "../libmx/inc/libmx.h"

#define INT_MAX (2147483647)

#define IS_VALID (0)
#define ERR_FILE_NOT_EXIST (-1)
#define ERR_FILE_IS_EMPTY (-2)
#define ERR_ISLANDS_NUMBER (-3)
#define ERR_DUPLICATE (-4)
#define ERR_TOO_LARGE_ROUTE (-5)
#define ERR_LINE_N (1)

int validate_file(const char *file_path);
int validate_sizes(const char *str);
int validate_grammar_and_length(const char **lines);

#endif  // !VALIDATION
