#include "../inc/s_path.h"
#include "../libmx/inc/libmx.h"

static void clear_list(t_list *list, void (*free_data)(void *)) {
    while (list) {
        static t_list *buffer;

        free_data(list->data);

        buffer = list;
        list = list->next;
        free(buffer);
    }
}

static void free_list_inside(void *data) {
    t_list* list = data;
    while (list) {
        static t_list *buffer;

        buffer = list;
        list = list->next;
        free(buffer);
    }
}

void free_pathes_arr(t_path ***ptr_to_arr, int arr_size) {
    t_path **arr = *ptr_to_arr;

    *ptr_to_arr = (void *)0;
    for (int i = 0; i < arr_size; i++) {
        for (int j = 0; j < arr_size; j++) {
            clear_list(arr[i][j].routes, free_list_inside);
        }
        free(arr[i]);
    }
    free(arr);
}
