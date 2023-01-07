#include "../inc/conversions.h"
#include "../libmx/inc/libmx.h"

static int get_islands_count(char **islands) {
    int count = 0;

    for (; *islands; islands++) {
        count++;
    }

    return count;
}

static void move_ptr_to_symbol(char **ptr_to_ptr, char symbol) {
    while (**ptr_to_ptr != symbol && **ptr_to_ptr != '\0') {
        (*ptr_to_ptr)++;
    }
}

static int index_in_array(char *word, char **array) {
    int index = 0;

    for (char **island = array; *island != NULL; island++, index++) {
        if (mx_strcmp(*island, word) == 0) {
            return index;
        }
    }
    return -1;
}

static void push_back_to_array(char *word, char ***ptr_to_array) {
    int array_size = 0;

    for (char **array = *ptr_to_array; *array != NULL; array++) {
        array_size++;
    }

    char **old_array = *ptr_to_array;
    char **save_old = old_array;
    int save_array_size = array_size;

    *ptr_to_array = malloc(sizeof(char *) * (array_size + 2));

    for (char **new_ptr = *ptr_to_array; array_size > 0;
         array_size--, new_ptr++) {
        *new_ptr = *old_array;
        old_array++;
    }

    free(save_old);

    (*ptr_to_array)[save_array_size] = mx_strdup(word);
    (*ptr_to_array)[save_array_size + 1] = NULL;
}

static void examine_island(char *word_start,
                           char breakpoint,
                           char ***islands_ptr) {
    char *word_end;
    int word_index;

    word_end = word_start + mx_get_char_index(word_start, breakpoint);
    *word_end = '\0';

    word_index = index_in_array(word_start, *islands_ptr);

    if (word_index == -1) {
        push_back_to_array(word_start, islands_ptr);
    }

    *word_end = breakpoint;
}

static char **make_islands_collection(char **lines) {
    char **islands;

    islands = malloc(sizeof(char *) * 1);
    islands[0] = NULL;

    for (char **line = (lines + 1); *line != NULL; line++) {
        static char *head;
        head = *line;

        examine_island(head, '-', &islands);

        move_ptr_to_symbol(&head, '-');
        head++;

        examine_island(head, ',', &islands);
    }

    return islands;
}

static int get_island_index(char *word_start,
                            char breakpoint,
                            char **islands) {
    char *word_end;
    int word_index;

    word_end = word_start + mx_get_char_index(word_start, breakpoint);

    *word_end = '\0';

    word_index = index_in_array(word_start, islands);

    *word_end = breakpoint;

    return word_index;
}

static int **make_bridges_matrix(char **lines, char **islands) {
    int **bridges;
    int islands_size = get_islands_count(islands);

    bridges = malloc(sizeof(int *) * (islands_size));

    for (int i = 0; i < islands_size; i++) {
        bridges[i] = malloc(islands_size * sizeof(int));
        for (int j = 0; j < islands_size; j++) {
            bridges[i][j] = -1;
        }
    }

    for (char **line = (lines + 1); *line != NULL; line++) {
        static int left_i, right_i;
        static char *head;

        head = *line;

        left_i = get_island_index(head, '-', islands);

        move_ptr_to_symbol(&head, '-');
        head++;

        right_i = get_island_index(head, ',', islands);

        if (left_i == right_i || bridges[left_i][right_i] != -1) {
            bridges[0][0] = -2;
            return bridges;
        }
        else {
            int bridge_lenth = 0;

            move_ptr_to_symbol(&head, ',');
            head++;

            while (*(head) != '\0') {
                bridge_lenth *= 10;
                bridge_lenth += *head - '0';
                head++;
            }

            bridges[left_i][right_i] = bridge_lenth;
            bridges[right_i][left_i] = bridge_lenth;
        }
    }
    return bridges;
}

t_graph *build_graph_without_duplicates(char **lines) {
    t_graph *map = malloc(sizeof(t_graph));

    map->islands = make_islands_collection(lines);
    map->islands_count = get_islands_count(map->islands);
    map->bridges = make_bridges_matrix(lines, map->islands);

    return map;
}
