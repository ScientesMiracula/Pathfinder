#ifndef PATHFINDER
#define PATHFINDER

#include "../libmx/inc/libmx.h"
#include "s_graph.h"
#include "s_path.h"

typedef struct s_memory_cell {
    int traveled_lenth;
    t_list *parents;
} t_memory_cell;

t_memory_cell **calculate_all_routes(t_graph *graph);
t_path **adapt_to_pathes(t_memory_cell **routes_map, int);

#endif  // !PATHFINDER
