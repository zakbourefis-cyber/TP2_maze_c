#include <stdlib.h>
#include "stack.h"

void stack_init(Stack *p)
{
  p->haut_pile = NULL; // pile vide donc pas de haut
}

bool stack_empty(Stack *p)
{
  return (p->haut_pile == NULL);
}

void stack_push(Stack *p, Element e)
{
  //On fait un nouveau noeud
  noeud *nouveau_noeud = (noeud *)malloc(sizeof(noeud));
  if (nouveau_noeud != NULL) {
    nouveau_noeud->data = e;
    nouveau_noeud->suiv = p->haut_pile;
    p->haut_pile = nouveau_noeud;
  }
}

Element stack_pop(Stack *p)
{
  if (!stack_empty(p)) {
    noeud *temp = p->haut_pile;
    Element e = temp->data;
    p->haut_pile = temp->suiv;
    free(temp);
    return e;
  }
  
  return (coord){0, 0};
}

void free_stack(Stack *p)
{
  // On dépile tout jusqu'à ce que la pile soit vide
  while (!stack_empty(p)) {
    stack_pop(p);
  }
}