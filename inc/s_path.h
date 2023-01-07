#ifndef PATH
#define PATH

#include "../inc/s_graph.h"
#include "../libmx/inc/libmx.h"

typedef struct s_path {
    int lenth;
    int start;
    int end;
    t_list *routes;
} t_path;

void free_pathes_arr(t_path ***ptr_to_arr, int arr_size);
void print_available_pathes(t_path **pathes, t_graph *map);

#endif  // !PATH
