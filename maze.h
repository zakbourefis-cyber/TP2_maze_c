#ifndef LABYRINTHE_H
#define LABYRINTHE_H

#include <stdbool.h>
#include "coord.h"

typedef struct __neighboors
{
  bool north;
  bool south;
  bool east;
  bool west;
} neighboors;

// Structure représentant une seule case du labyrinthe.
typedef struct __cell
{
  struct __cell *north; // Pointeur vers la case au dessus  (ou NULL).
  struct __cell *south; // Pointeur vers la case au dessous (ou NULL).
  struct __cell *east;  // Pointeur vers la case à droite   (ou NULL).
  struct __cell *west;  // Pointeur vers la case à gauche   (ou NULL).
  char tag[2];          // Caractères à afficher dans la cellule.
  int x;                // Position de la cellule sur l'axe des X.
  int y;                // Position de la cellule sur l'axe des Y.
} cell;

// Structure représentant un labyrinthe rectangulaire.
typedef struct __maze
{
  int width;    // Largeur globale du labyrinthe.
  int height;   // Hauteur globale du labyrinthe.
  cell **cells; // La matrice des cases (ou cellules).
  cell *origin; // Pointeur vers la cellule d'entrée.
  cell *target; // Pointeur vers la cellule de sortie.
} maze;

typedef struct __node
{
  int x;
  int y;
  struct __node *next;
} node;

typedef struct __edge
{
  node *source;
  node *target;
  int weight;
} edge;

// Fonction d'initialisation d'un labyrinthe rectangulaire.
void init_maze(maze *m, int width, int height);

// Libération de la mémoire pour un labyrinthe.
void free_maze(maze *m);

// Affiche un labyrinthe.
void print_maze(maze *m);

// Teste si la cellule à la position donnée est l'entrée.
int is_origin(maze *m, coord coord);

// Teste si la cellule à la position donnée est la sortie.
int is_target(maze *m, coord coord);

// Renvoie les cases voisines, dans lesquelles il est possible de se déplacer.
neighboors list_neighboors(maze *m, coord coord);

// Change le label de la case donnée (2 caractères maximum).
void set_tag(maze *m, coord coord, const char *c);

#endif // LABYRINTHE_H
