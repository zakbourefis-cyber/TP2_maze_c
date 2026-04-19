#ifndef __PILE_H__
#define __PILE_H__

#include <stdio.h>
#include <stdbool.h>
#include "coord.h"

#define PILEMAX 100

typedef coord Element;

typedef struct _stack
{
  Element elements[PILEMAX];
  int taille;
} Stack;

/**
 * Configuration :
 *
 *   0                     n           PILEMAX-1
 *   |                     |             |
 *   V                     V             V
 *  ---------------------------------------
 *  |*|*|*|*|*|*|*|*|*|*|*| | | | | | | | |
 *  ---------------------------------------
 *
 */

void stack_init(Stack *stack);

bool stack_empty(Stack *stack);

Element stack_pop(Stack *stack);

void stack_push(Stack *stack, Element e);

#endif
