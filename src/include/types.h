#ifndef __GRIT_LANG_TYPES_H
#define __GRIT_LANG_TYPES_H

#include <cstddef>

struct Position {
  size_t cursor;
  size_t row;
  size_t linebeg;

  Position() { cursor = row = linebeg = 0; }
};

#endif
