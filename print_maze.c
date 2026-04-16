#include <stdio.h>
#include <stdbool.h>

#include "maze.h"
#include "print_maze.h"

void print_maze(maze *m)
{
    print_top_border(m);

    // Print the maze line by line
    for (int y = 0; y < m->height; y++)
    {
        // Print cell content
        printf("│");
        for (int x = 0; x < m->width; x++)
        {
            print_cell_contents(m, x, y);
        }
        printf("\n");

        // Print the border line
        if (y == m->height - 1)
        {
            print_bottom_border(m, y);
        }
        else
        {
            print_intermediate_border(m, y);
        }
        printf("\n");
    }
}

void print_top_border(maze *m)
{
    printf("┌");
    for (int x = 0; x < m->width - 1; ++x)
    {
        printf("──%s", (m->cells[x][0].east == NULL ? "┬" : "─"));
    }
    printf("──┐\n");
}

void print_cell_contents(maze *m, int x, int y)
{
    printf("%c%c", m->cells[x][y].tag[0], m->cells[x][y].tag[1]);
    printf("%s", (m->cells[x][y].east == NULL ? "│" : " "));
}

void print_bottom_border(maze *m, int y)
{
    printf("└");
    for (int x = 0; x < m->width - 1; ++x)
    {
        printf("──%s", (m->cells[x][y].east == NULL ? "┴" : "─"));
    }
    printf("──┘");
}

const char *get_border_symbol(bool has_south, bool has_east, bool has_south_next, bool has_east_next)
{
    if (has_south)
    {
        if (has_south_next)
        {
            if (has_east)
            {
                return has_east_next ? "   " : "  ╷";
            }
            else
            {
                return has_east_next ? "  ╵" : "  │";
            }
        }
        else
        {
            if (has_east)
            {
                return has_east_next ? "  ╶" : "  ┌";
            }
            else
            {
                return has_east_next ? "  └" : "  ├";
            }
        }
    }
    else
    {
        if (has_south_next)
        {
            if (has_east)
            {
                return has_east_next ? "──╴" : "──┐";
            }
            else
            {
                return has_east_next ? "──┘" : "──┤";
            }
        }
        else
        {
            if (has_east)
            {
                return has_east_next ? "───" : "──┬";
            }
            else
            {
                return has_east_next ? "──┴" : "──┼";
            }
        }
    }
}

void print_intermediate_border(maze *m, int y)
{
    printf("%s", (m->cells[0][y].south == NULL ? "├" : "│"));
    for (int x = 0; x < m->width - 1; ++x)
    {
        bool has_south = m->cells[x][y].south != NULL;
        bool has_east = m->cells[x][y].east != NULL;
        bool has_south_next = m->cells[x + 1][y].south != NULL;
        bool has_east_next = m->cells[x][y + 1].east != NULL;

        const char *symbol = get_border_symbol(has_south, has_east, has_south_next, has_east_next);
        printf("%s", symbol);
    }
    printf("%s", (m->cells[m->width - 1][y].south == NULL ? "──┤" : "  │"));
}
