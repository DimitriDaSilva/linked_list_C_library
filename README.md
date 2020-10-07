This repo is a simple c library of functions to use linked lists in your own projects

/* CREATION FUNCTIONS */
node *create_node(int number);

/* LOOKUP FUNCTIONS */
node *find_node(node *head, int number);

/* INSERTION FUNCTIONS */
void insert_node_at_beginning(node **head, node *node_to_insert);
void insert_node_at_end(node **head, node *node_to_insert);
void insert_node_after_another(node *node_to_insert_after, node *node_to_insert);

/* DELETION FUNCTIONS */
void delete_first_node(node **head);
void delete_last_node(node *head);
void delete_node(node *head, node *node_to_delete);
void delete_list(node **head);

/* PRINTING FUNCTIONS */
void print_list(node *head);

/* ANALYSIS FUNCTIONS */
int count_nodes(node *head);
int count_if_nodes(node *head, int value, int (*op)(int, int));
int sum_nodes(node *head);
int sum_if_nodes(node *head, int value, int (*op)(int, int));
float average_nodes(node *head);
float average_if_nodes(node *head, int value, int (*op)(int, int));
int equal(int a, int b);
int greater_than_or_equal(int a, int b);
int greater_than(int a, int b);
int less_than_or_equal(int a, int b);
int less_than(int a, int b);

/* ORDERING FUNCTIONS */
void sort_list(node **headRef, int (*op)(int, int));
node *merge_sort(node *a, node *b, int (*op)(int, int));
void split_list(node *head, node **first_half, node **second_half);
int ascending(int a, int b);
int descending(int a, int b);

void reverse_list(node **head);

