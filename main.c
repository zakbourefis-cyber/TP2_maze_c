#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>

#include "maze.h"
#include "coord.h"
#include "stack.h"
#include "structure.h"

void solve(maze *m)
{
  (void)m; // Supprimez cette ligne !
  // Exo 3
}

void usage(const char *name)
{
  fprintf(stderr, "Usage : %s w h\n", name);
  fprintf(stderr, "Affiche un labyrinthe de dimension w x h\n");
  fprintf(stderr, "Options :\n");
  fprintf(stderr, " w : largeur du labyrinthe\n");
  fprintf(stderr, " h : hauteur du labyrinthe\n");
}

int main(int argc, char **argv)
{
  maze m;
  int w = (argc > 1 ? atoi(argv[1]) : 10);
  int h = (argc > 2 ? atoi(argv[2]) : 10);

  if (w < 0 || h < 0 || w * h < 2)
  {
    usage(argv[0]);
    exit(EXIT_FAILURE);
  }

  init_maze(&m, w, h);
  coord c;
  c.x = 3;
  c.y = 1;
  if (is_target(&m,c))
  {
    printf("Vous êtes arrivés à la sortie !\n");
  }
  mark_neighboors(&m, c);
  set_tag(&m, c, "x");
  print_maze(&m);
  free_maze(&m);

  return 0;
}

void mark_neighboors(maze* m, coord c) {
    set_tag(m, c, "x");
    neighboors v = list_neighboors(m, c);
    coord voisin;
    if (v.north == true) { 
        voisin.x = c.x;
        voisin.y = c.y - 1; 
        set_tag(m, voisin, "o");
    }
    if (v.south == true) { 
        voisin.x = c.x;
        voisin.y = c.y + 1; 
        set_tag(m, voisin, "o");
    }
    if (v.west == true) { 
        voisin.x = c.x - 1;
        voisin.y = c.y; 
        set_tag(m, voisin, "o");
    }
    if (v.east == true) { 
        voisin.x = c.x + 1;
        voisin.y = c.y; 
        set_tag(m, voisin, "o");
    }
}