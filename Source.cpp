#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Node
{
    char* data;
    struct Node* next;
} Node;

int Hashify(char* str, unsigned int table_size)
{
    if (!str)
        return -1;
    size_t hash_sum = 0;
    int len = strlen(str);
    for (int i = 0; i < len; i++)
        hash_sum += str[i];
    return hash_sum % table_size;
}


int Find(Node** table, unsigned int table_size, char* str)
{
    Node* cur = table[Hashify(str, table_size)];
    while (cur)
    {
        if (!strcmp(cur->data, str))
            return 1;
        cur = cur->next;
    }
    return 0;
}


void Add(Node** table, unsigned int table_size, char* str)
{
    if (Find(table, table_size, str))
        return;
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = (char*)malloc(strlen(str) + 1);
    if (!new_node) return;
    unsigned int id = Hashify(str, table_size);
    strcpy(new_node->data, str);
    new_node->next = table[id];
    table[id] = new_node;
}


void del(Node** table, unsigned int table_size, char* to_del)
{
    if (!Find(table, table_size, to_del))
        return;
    unsigned int id = Hashify(to_del, table_size);
    Node* target_node = table[id];
    while (strcmp(target_node->data, to_del))
        target_node = target_node->next;
    if (!strcmp(target_node->data, table[id]->data))
    {
        if (table[id]->next)
            table[id] = table[id]->next;
        else
            table[id] = NULL;
        free(target_node->data);
        free(target_node);
    }
    else
    {
        Node* cur = table[id];
        while (cur->next != target_node)
        {
            cur = cur->next;
        }
        cur->next = target_node->next;
        free(target_node->data);
        free(target_node);
    }
}


int main()
{
    const unsigned int size = 909091;
    Node** table = (Node**)malloc(sizeof(Node) * size);
    if (!table)
        return -1;
    for (int i = 0; i < size; i++)
        table[i] = NULL;
    char req;
    char key[100];
    while (scanf("%c", &req) > 0)
    {
        switch (req)
        {
        case 'a':
            scanf("%s", &key);
            Add(table, size, key);
            break;
        case 'r':
            scanf("%s", &key);
            del(table, size, key);
            break;
        case 'f':
            scanf("%s", &key);
            if (Find(table, size, key))
                printf("%s", "yes\n");
            else
                printf("%s", "no\n");
        }
    }
    return 0;
}