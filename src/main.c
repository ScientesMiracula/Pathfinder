#include "../inc/conversions.h"
#include "../inc/pathfinder.h"
#include "../inc/s_graph.h"
#include "../inc/s_path.h"
#include "../libmx/inc/libmx.h"

static void stderr_print(const char *err_str) {
    write(2, err_str, mx_strlen(err_str));
}

static bool check_islands_amount(int islands_must_be,
                                 char *first_line) {
    int input_islands_amount = 0;

    while (*first_line) {
        input_islands_amount *= 10;
        input_islands_amount += *first_line - '0';
        first_line++;
    }

    return input_islands_amount == islands_must_be;
}

int main(int argv, char **args) {
    if (!args || argv != 2) {
        stderr_print("usage:./pathfinder [filename]\n");
        exit(0);
    }
    char **lines = map_file_to_lines_with_grammar_validation(args);

    t_graph *graph = build_graph_without_duplicates(lines);

    if (!check_islands_amount(graph->islands_count, lines[0])) {
        mx_del_strarr(&lines);
        free_graph(&graph);
        stderr_print("error: invalid number of islands\n");
        exit(0);
    }

    mx_del_strarr(&lines);

    if (graph->bridges[0][0] == -2) {
        free_graph(&graph);
        stderr_print("error: duplicate bridges\n");
        exit(0);
    }

    t_memory_cell **routes_map = calculate_all_routes(graph);

    t_path **full_pathes =
        adapt_to_pathes(routes_map, graph->islands_count);

    print_available_pathes(full_pathes, graph);

    free_pathes_arr(&full_pathes, graph->islands_count);
    free_graph(&graph);
    return 0;
}
