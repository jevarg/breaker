#include "particle_list.h"
#include "utils.h"

particle_list_node_t *particle_list_init()
{
    particle_list_node_t *node = calloc(1, sizeof(particle_list_node_t));
    if (node == NULL)
    {
        print_error("Could not init particle list");
        return NULL;
    }

    return node;
}

void particle_list_destroy(particle_list_node_t *node)
{
    if (node == NULL)
    {
        return;
    }

    free(node);
}

void particle_list_add(particle_list_node_t *root_node, particle_t *particle)
{
    if (root_node == NULL)
    {
        printf("Null root node\n");
        return;
    }

    if (root_node->particle == NULL)
    {
        root_node->particle = particle;
        return;
    }

    particle_list_node_t *parent = root_node;
    while (parent->next != NULL)
    {
        parent = parent->next;
    }

    particle_list_node_t *new_node = particle_list_init();
    new_node->particle = particle;
    new_node->prev = parent;

    parent->next = new_node;
}

void particle_list_remove(particle_list_node_t *node)
{
    if (node->next != NULL)
    {
        if (node->prev != NULL)
        {
            node->prev->next = node->next;
        }
        else
        {
            node->next->prev = NULL;
        }

        node->next->prev = node->prev;
    }
    else if (node->prev != NULL)
    {
        node->prev->next = NULL;
    }

    particle_list_destroy(node);
}

void particle_list_find_and_remove(particle_list_node_t *root_node, particle_t *particle)
{
    particle_list_node_t *node = root_node;
    while (node != NULL)
    {
        if (node->particle != particle)
        {
            continue;
        }

        particle_list_remove(node);
        break;
    }
}

