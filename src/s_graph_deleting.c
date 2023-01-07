#include <stdlib.h>

#include "../inc/s_graph.h"

void free_graph(t_graph **ptr_to_graph) {
    t_graph *graph = *ptr_to_graph;
    int islands_amount = graph->islands_count;

    *ptr_to_graph = (void *)0;

    for (char **island = graph->islands; *island; island++) {
        free(*island);
    }
    free(graph->islands);

    for (int **island_bridges = graph->bridges; islands_amount > 0;
         islands_amount--, island_bridges++) {
        free(*island_bridges);
    }
    free(graph->bridges);
    free(graph);
}
