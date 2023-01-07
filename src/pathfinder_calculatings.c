#include "../inc/pathfinder.h"
#include "../inc/s_graph.h"

static void trawel_to(t_memory_cell **routes_map,
                      int root,
                      long long current,
                      t_graph *graph) {
    int islands_count = graph->islands_count;

    for (long long j = 0; j < islands_count; j++) {
        if (graph->bridges[current][j] != -1) {
            static int with_new_island;
            static int old_lenth;

            old_lenth = routes_map[root][j].traveled_lenth;
            with_new_island = routes_map[root][current].traveled_lenth +
                              graph->bridges[current][j];

            if (old_lenth == -1 || with_new_island <= old_lenth) {
                bool equal_lenth;

                equal_lenth = (with_new_island == old_lenth);

                if (!equal_lenth) {
                    routes_map[root][j].traveled_lenth =
                        with_new_island;
                    while (routes_map[root][j].parents) {
                        mx_pop_front(&(routes_map[root][j].parents));
                    }
                }

                mx_push_back(&(routes_map[root][j].parents),
                             (void *)current);

                trawel_to(routes_map, root, j, graph);
            }
        }
    }
}

t_memory_cell **calculate_all_routes(t_graph *graph) {
    int islands_count = graph->islands_count;
    t_memory_cell **routes_map =
        malloc(sizeof(t_memory_cell *) * islands_count);

    for (int i = 0; i < islands_count; i++) {
        routes_map[i] = malloc(sizeof(t_memory_cell) * islands_count);
        for (int j = 0; j < islands_count; j++) {
            if (i == j) {
                routes_map[i][j].traveled_lenth = 0;
            }
            else {
                routes_map[i][j].traveled_lenth = -1;
            }
            routes_map[i][j].parents = NULL;
        }
        trawel_to(routes_map, i, i, graph);
    }

    return routes_map;
}
