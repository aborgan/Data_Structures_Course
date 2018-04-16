#include <stdio.h>// print, write
#include <stddef.h> // NULL
#include <stdlib.h> // malloc, free


typedef struct node
{
    int data;
    struct node *next;
}node;

node* create_node(int data)
{
    node *n;
    n = malloc(sizeof(node));
    n->data = data;
    return n;
}

void delete_node(node *n)
{
    //free data if data is malloced (ie string)
    free(n);
}

void print_node(node *n)
{
    printf("%d", n->data);
}

// --- LIST --- //
typedef struct linked_list
{
    node* head;
    node* tail;
}linked_list;

linked_list create_linked_list()
{
   linked_list l;
   l.head = NULL;
   l.tail = NULL;
   return l;
}

void add_node(linked_list *l, int data)
{
    node *n = create_node(data);
    if (l->head == NULL)
    {
        l->head = n;
        l->tail = l->head;
    }
    else
    {
        l->tail->next = n;
        l->tail = l->tail->next;
        l->tail->next = NULL;
    }
}

void print_list(linked_list l)
{
    node* temp = l.head;
    do
    {
        print_node(temp);
        printf(", ");
        temp = temp->next;
    }while(temp != NULL);
    printf("\n");
}

void delete_list(linked_list * l)
{
    node* temp = l->head;
    node* next_temp = temp->next;
    do
    {
        next_temp = temp->next;
        delete_node(temp);
        temp = next_temp;
    }while(temp != NULL);
}

void save_node(node *n, FILE *fp)
{
    fwrite(&(n->data), sizeof(n->data), 1, fp);
}

// --- FILE --- //
void save_linked_list(FILE *fp, linked_list *l)
{
    node* temp = l->head;
    do
    {
        save_node(temp, fp);
        temp = temp->next;
    }while(temp != NULL);
}

void read_linked_list(FILE *fp, linked_list *l)
{
    int input;
    node* n = create_node(0);
    while (fread(&input, sizeof(n->data), 1, fp) == 1)
    {
        add_node(l, input);
    }
    delete_node(n);
}

int main()
{
    FILE *fp;

    struct linked_list l = create_linked_list();

    int input;
    fp = fopen("listdata.bin", "rb");
    read_linked_list(fp, &l);

    printf("Enter an integer or press q to quit and print\n");

    while (scanf("%d", &input) > 0)
    {
        add_node(&l, input);
        printf("Enter another integer or press q to quit and print\n");

    }
    print_list(l);

    // --- SAVE --- //
    fp = fopen("listdata.bin", "wb");
    save_linked_list(fp, &l);
    fclose(fp);

    delete_list(&l);

    return 0;
}
