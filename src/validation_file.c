#include "../inc/validation.h"

int validate_file(const char *file_path) {
    int file_d = open(file_path, O_RDONLY);

    if (file_d < 0) {
        return ERR_FILE_NOT_EXIST;
    }

    char buffer;
    if (!read(file_d, &buffer, 1)) return ERR_FILE_IS_EMPTY;

    close(file_d);

    return IS_VALID;
}
