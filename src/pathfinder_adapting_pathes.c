#include "../inc/pathfinder.h"

static void *get_parent_data(int i, t_list *parents) {
    for (; i > 0; i--) {
        parents = parents->next;
    }
    return parents->data;
}

static int *get_routes_amount_arr(t_memory_cell *island_line,
                                  int islands_count) {
    int *routes_amount = malloc(sizeof(int) * islands_count);

    for (int i = 0; i < islands_count; i++) {
        routes_amount[i] = -1;

        static t_list *route;

        route = island_line[i].parents;
        while (route) {
            routes_amount[i]++;
            route = route->next;
        }
    }

    return routes_amount;
}

static t_list *build_path(t_memory_cell *island_map,
                          int *routes_lenthes,
                          long long root,
                          long long goal) {
    t_list *path = NULL;

    if (island_map[goal].traveled_lenth < 1) {
        return NULL;
    }

    while (goal != root) {
        mx_push_front(&path, (void *)goal);
        goal = (long long)(get_parent_data(routes_lenthes[goal],
                                           island_map[goal].parents));
        routes_lenthes[(int)(path->data)]--;
    }
    mx_push_front(&path, (void *)root);

    return path;
}

static t_list *build_pathes_list(t_memory_cell *island_map,
                                 int root,
                                 int goal,
                                 int islands_count) {
    if (root == goal) {
        return NULL;
    }

    static int *routes_lenthes;
    t_list *path = NULL;

    routes_lenthes = get_routes_amount_arr(island_map, islands_count);

    while (routes_lenthes[goal] >= 0) {
        static t_list *new_path;

        new_path = build_path(island_map, routes_lenthes, root, goal);
        mx_push_front(&(path), new_path);
    }

    free(routes_lenthes);
    return path;
}

static void clear_list(t_list *list) {
    while (list) {
        static t_list *buffer;

        buffer = list;
        list = list->next;
        free(buffer);
    }
}

static void free_calculatings(t_memory_cell **routes_map,
                              int islands_count) {
    for (int i = 0; i < islands_count; i++) {
        for (int j = 0; j < islands_count; j++) {
            clear_list(routes_map[i][j].parents);
        }
        free(routes_map[i]);
    }
    free(routes_map);
}

t_path **adapt_to_pathes(t_memory_cell **routes_map,
                         int islands_count) {
    t_path **pathes = malloc(sizeof(t_path *) * islands_count);

    for (int i = 0; i < islands_count; i++) {
        pathes[i] = malloc(sizeof(t_path) * islands_count);
        for (int j = 0; j < islands_count; j++) {
            pathes[i][j].lenth = -1;
            pathes[i][j].start = -1;
            pathes[i][j].end = -1;
            pathes[i][j].routes = NULL;
        }
    }

    for (int i = 0; i < islands_count; i++) {
        for (int j = i + 1; j < islands_count; j++) {
            pathes[i][j].lenth = routes_map[i][j].traveled_lenth;
            pathes[i][j].start = i;
            pathes[i][j].end = j;
            pathes[i][j].routes =
                build_pathes_list(routes_map[i], i, j, islands_count);
        }
    }
    free_calculatings(routes_map, islands_count);
    return pathes;
}
