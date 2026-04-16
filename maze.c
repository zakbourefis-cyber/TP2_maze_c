#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include "maze.h"

node *set_find(node *n)
{
	if (n->next == NULL)
		return n;
	n->next = set_find(n->next);
	return n->next;
}

void set_union(node *n1, node *n2)
{
	node *r1 = set_find(n1);
	node *r2 = set_find(n2);
	r1->next = r2;
}

int compare_edge(const void *e1, const void *e2)
{
	return ((edge *)e1)->weight - ((edge *)e2)->weight;
}

void initialize_cells(maze *m, int w, int h)
{
	for (int x = 0; x < w; ++x)
	{
		for (int y = 0; y < h; ++y)
		{
			m->cells[x][y].north = NULL;
			m->cells[x][y].south = NULL;
			m->cells[x][y].east = NULL;
			m->cells[x][y].west = NULL;
			m->cells[x][y].tag[0] = ' ';
			m->cells[x][y].tag[1] = ' ';
			m->cells[x][y].x = x;
			m->cells[x][y].y = y;
		}
	}
}

void set_origin_and_target(maze *m, int w, int h)
{
	m->origin = &m->cells[0][0];
	m->origin->tag[1] = '@';
	m->target = &m->cells[w - 1][h - 1];
	m->target->tag[1] = '$';
}

void create_edges(node *ns, edge *es, int w, int h)
{
	for (int x = 0; x < w - 1; ++x)
	{
		for (int y = 0; y < h; ++y)
		{
			es[(w - 1) * y + x].source = &ns[w * y + x];
			es[(w - 1) * y + x].target = &ns[w * y + x + 1];
			es[(w - 1) * y + x].weight = rand();
		}
	}
	for (int x = 0; x < w; ++x)
	{
		for (int y = 0; y < h - 1; ++y)
		{
			es[(w - 1) * h + w * y + x].source = &ns[w * y + x];
			es[(w - 1) * h + w * y + x].target = &ns[w * (y + 1) + x];
			es[(w - 1) * h + w * y + x].weight = rand();
		}
	}
}

void connect_cells(maze *m, edge *es, int nb_edges)
{
	for (int i = 0; i < nb_edges; ++i)
	{
		if (set_find(es[i].source) != set_find(es[i].target))
		{
			set_union(es[i].source, es[i].target);
			if (es[i].source->x == es[i].target->x)
			{
				m->cells[es[i].source->x][es[i].source->y].south =
					&m->cells[es[i].source->x][es[i].source->y + 1];
				m->cells[es[i].source->x][es[i].source->y + 1].north =
					&m->cells[es[i].source->x][es[i].source->y];
			}
			else
			{
				m->cells[es[i].source->x][es[i].source->y].east =
					&m->cells[es[i].source->x + 1][es[i].source->y];
				m->cells[es[i].source->x + 1][es[i].source->y].west =
					&m->cells[es[i].source->x][es[i].source->y];
			}
		}
	}
}

void init_maze(maze *m, int w, int h)
{
	node *ns;
	edge *es;
	int nb_edges;
	struct timeval tm;

	m->width = w;
	m->height = h;

	m->cells = (cell **)malloc(w * sizeof(cell *));
	for (int i = 0; i < w; i++)
		m->cells[i] = (cell *)malloc(h * sizeof(cell));

	initialize_cells(m, w, h);
	set_origin_and_target(m, w, h);

	gettimeofday(&tm, NULL);
	srand(tm.tv_usec);

	ns = (node *)malloc(w * h * sizeof(node));
	for (int x = 0; x < w; ++x)
		for (int y = 0; y < h; ++y)
			ns[w * y + x] = (node){.x = x, .y = y, .next = NULL};

	nb_edges = (w - 1) * h + (h - 1) * w;
	es = (edge *)malloc(nb_edges * sizeof(edge));
	create_edges(ns, es, w, h);
	qsort(es, nb_edges, sizeof(edge), compare_edge);
	connect_cells(m, es, nb_edges);

	free(ns);
	free(es);
}

void free_maze(maze *m)
{
	for (int i = 0; i < m->width; i++)
		free(m->cells[i]);
	free(m->cells);
}

int is_origin(maze *m, coord coord)
{
	int x = coord.x;
	int y = coord.y;
	return &m->cells[x][y] == m->origin;
}

int is_target(maze *m, coord coord)
{
	int x = coord.x;
	int y = coord.y;
	return &m->cells[x][y] == m->target;
}

neighboors list_neighboors(maze *m, coord coord)
{
	int x = coord.x;
	int y = coord.y;
	cell c = m->cells[x][y];
	neighboors d;
	d.north = c.north != NULL;
	d.south = c.south != NULL;
	d.east = c.east != NULL;
	d.west = c.west != NULL;
	return d;
}

void set_tag(maze *m, coord coord, const char *c)
{
	int x = coord.x;
	int y = coord.y;
	size_t len = strlen(c);
	if (len == 0)
	{
		m->cells[x][y].tag[0] = ' ';
		m->cells[x][y].tag[1] = ' ';
	}
	if (len == 1)
	{
		m->cells[x][y].tag[0] = ' ';
		m->cells[x][y].tag[1] = c[0];
	}
	if (len == 2)
	{
		m->cells[x][y].tag[0] = c[0];
		m->cells[x][y].tag[1] = c[1];
	}
}
