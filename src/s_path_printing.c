#include "../inc/s_graph.h"
#include "../inc/s_path.h"
#include "../libmx/inc/libmx.h"

static void print_path(t_path path, t_graph *map) {
    for (t_list *routes = path.routes; routes; routes = routes->next) {
        t_list *island;

        mx_printstr("========================================\n");

        mx_printstr("Path: ");
        mx_printstr(map->islands[path.start]);
        mx_printstr(" -> ");
        mx_printstr(map->islands[path.end]);
        mx_printstr("\n");

        mx_printstr("Route: ");
        for (island = (t_list *)(routes->data); island;
             island = island->next) {
            mx_printstr(map->islands[((long long)(island->data))]);
            if (island->next) mx_printstr(" -> ");
        }
        mx_printstr("\n");

        mx_printstr("Distance: ");
        island = (t_list *)(routes->data);
        if (island->next->next) {
            for (island = routes->data; island->next;
                 island = island->next) {
                static int i, j;

                i = ((int)(island->data));
                j = ((int)(island->next->data));

                mx_printint(map->bridges[i][j]);
                if (j != path.end) mx_printstr(" + ");
            }

            mx_printstr(" = ");
            mx_printint(path.lenth);
        }
        else {
            static int i, j;

            i = ((int)(island->data));
            j = ((int)(island->next->data));
            mx_printint(map->bridges[i][j]);
        }

        mx_printstr("\n");

        mx_printstr("========================================\n");
    }
}

void print_available_pathes(t_path **pathes, t_graph *map) {
    int islands_amount = map->islands_count;

    for (int i = 0; i < islands_amount; i++) {
        for (int j = 0; j < islands_amount; j++) {
            if (pathes[i][j].lenth > 0) {
                print_path(pathes[i][j], map);
            }
        }
    }
}
