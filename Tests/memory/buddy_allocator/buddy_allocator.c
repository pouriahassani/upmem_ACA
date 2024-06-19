#include <alloc.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <defs.h>
int main() {
  int i;
  int *data;
  buddy_init(4096);
  data = buddy_alloc(1);
  data[0] = me();
  printf("\nI have allocated an int in the heap and the value of my allocated data is %d",data[0]);
}