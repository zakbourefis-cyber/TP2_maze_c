#include <stdlib.h>
#include "stack.h"

void stack_init(Stack *p)
{
  p->taille = 0; 
}

bool stack_empty(Stack *p)
{
  return (p->taille == 0);
}

void stack_push(Stack *p, Element e)
{
  if (p->taille < PILEMAX) {
    p->elements[p->taille] = e;
    p->taille++;
  }
}

Element stack_pop(Stack *p)
{
  if (!stack_empty(p)) {
    p -> taille --;
    return p -> elements [p -> taille];
  }
  
  return 0;
}