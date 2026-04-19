#ifndef __PILE_H__
#define __PILE_H__

#include <stdbool.h>
#include "coord.h"

typedef coord Element;
typedef struct _noeud {
  Element data;// La donnée stockée
  struct _noeud *suiv; // Un pointeur vers la boîte d'en dessous
} noeud;

// On change ca en pointeur
typedef struct _pile {
  noeud *haut_pile; // Pointeur vers le hautt de la pile
} Stack;

// Les fonctions restent les mêmes
void stack_init(Stack *stack);
bool stack_empty(Stack *stack);
Element stack_pop(Stack *stack);
void stack_push(Stack *stack, Element e);
void free_stack(Stack *stack);

#endif