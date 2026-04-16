#ifndef __COORD_H__
#define __COORD_H__

#include <stdbool.h>

typedef struct __coord
{
  int x;
  int y;
} coord;

bool equal( coord A, coord B );

#endif

