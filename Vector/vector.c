#include "vector.h"

#include <stdlib.h>


static void  vector_resize(vector_t *vec, size_t capacity)
{
  void **items = (void**)realloc(vec->items, sizeof(void *) * capacity);
  if (items) 
  {
    vec->items = items;
    vec->capacity = capacity;
  }
}

void vector_init(vector_t * vec, size_t capacity)
{
  vec->capacity = capacity;
  vec->count = 0;
  vec->items = (void**)malloc(sizeof(void *) * vec->capacity);
}

void      vector_free(vector_t *vec, void (*free_element)(void *ele))
{
  if (free_element) {
    size_t i;
    for (i = 0; i < vec->count; i++)
    {
      free_element(vec->items[i]);
    }
  }

  free(vec->items);
  vec->count = 0;
  vec->items = NULL;
}

void      vector_add(vector_t *vec, void *element)
{
  if (vec->count == vec->capacity)
    vector_resize(vec, vec->capacity + CAPACITY_INC);

  vec->items[vec->count++] = element;
}

void     *vector_get(vector_t *vec, size_t i)
{
  if (i >= vec->count) return NULL;
  return vec->items[i];
}

int       vector_set(vector_t *vec, size_t i, void *element)
{
  if (i < 0 || i >= vec->count) return -1;
  vec->items[i] = element;
  return 0;
}

int       vector_delete(vector_t *vec, size_t i)
{
  if (i < 0 || i >= vec->count) return -1;

  vec->items[i] = NULL;

  for (i = i; i < vec->count - 1; i++)
  {
    vec->items[i] = vec->items[i + 1];
    vec->items[i + 1] = NULL;
  }

  vec->count--;

  if (vec->count > 0 && vec->count == vec->capacity + (CAPACITY_INC*2))
    vector_resize(vec, vec->capacity - CAPACITY_INC);

  return 0;
}

static int def_comapre(void *element, void *ele)
{
  return element == ele?0:1;
}

int       vector_find(vector_t *vec, void *element, int(*comapre)(void *element, void *ele))
{
  size_t i;
  int(*cmp)(void *element, void *ele) = comapre;
  if (cmp == NULL) cmp = def_comapre;

  for (i = 0; i < vec->count; i++)
  {
    if (cmp(element, vec->items[i]) == 0) return (int)i;
  }
  return -1;
}


size_t    vector_size(vector_t *vec)
{
  return vec->count;
}
size_t    vector_capacity(vector_t *vec)
{
  return vec->capacity;
}
