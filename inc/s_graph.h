#ifndef GRAPH
#define GRAPH

typedef struct s_graph {
    int islands_count;
    char **islands;
    int **bridges;
} t_graph;

void free_graph(t_graph **ptr_to_graph);

#endif  // !GRAPH
