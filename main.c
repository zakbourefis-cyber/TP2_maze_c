#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>

#include "maze.h"
#include "coord.h"
#include "stack.h"
#include "structure.h"

// Fonction récursive qui regarde les chemins
bool solve_rec(maze *m, coord c, Stack *p) {
    coord prev = {-1, -1}; // test
    
    // On regarde la case précédente 
    if (!stack_empty(p)) {
        prev = stack_pop(p);
        stack_push(p, prev);
    }
    
    // On regarde la case actuelle
    stack_push(p, c);
    
    // On regarde si on a gagner 
    if (is_target(m, c)) {
        return true; 
    }
    
    // on regarde ou on va
    neighboors n = list_neighboors(m, c);
    coord next;
    
    // nord
    if (n.north) {
        next = (coord){c.x, c.y - 1};
        if (!equal(next, prev)) {
            if (solve_rec(m, next, p) == true) {
                return true;
            }
        }
    }
    
    // sud
    if (n.south) {
        next = (coord){c.x, c.y + 1};
        // on vérifie qu'on ne vient pas juste de cette case
        if (!equal(next, prev)) {
            // si on va vers la sortie on renvoie true
            if (solve_rec(m, next, p) == true) {
                return true;
            }
        }
    }

    // est
    if (n.east) {
        next = (coord){c.x + 1, c.y};
        if (!equal(next, prev)) {
            if (solve_rec(m, next, p) == true) {
                return true;
            }
        }
    }

    // ouest
    if (n.west) {
        next = (coord){c.x - 1, c.y};
        if (!equal(next, prev)) {
            if (solve_rec(m, next, p) == true) {
                return true;
            }
        }
    }
    
    // si ca marche pas on retire la case de la pile
    stack_pop(p);
    return false;
}

// Permet de lancer le solveur
void solve(maze *m) {
    Stack p;
    stack_init(&p);
    
    coord depart = {0, 0}; // on va au départ
    
    // On regarde
    if (solve_rec(m, depart, &p) == true) {
        
        // on remplace alors le chemin par des "." (exerci )
        while (!stack_empty(&p)) {
            coord chemin = stack_pop(&p);
            set_tag(m, chemin, ".");
        }
    }
    free_stack(&p); // On oublie pas de free
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
  } // COmme vu en cours 

  init_maze(&m, w, h);
  solve(&m);
  print_maze(&m);
  free_maze(&m);
  return 0;
}

void mark_neighboors(maze* m, coord c) {
  // permet de marquer le joueur
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