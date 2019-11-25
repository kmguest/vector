/*
* @km 2019-11-23
* vector.h
*/
#include <stddef.h>

#ifndef __VECTOR_H__
#define __VECTOR_H__

#ifdef __cplusplus
extern "C" {
#endif

#define CAPACITY_INC (128)

  typedef struct _vector_s {
    size_t    capacity;
    void    **items;
    size_t    count;
  } vector_t;

  void      vector_init(vector_t *vector, size_t capacity);
  void      vector_free(vector_t *vector, void(*free_element)(void *ele));
  void      vector_add(vector_t *vector, void *element);
  void     *vector_get(vector_t *vector, size_t i);
  int       vector_set(vector_t *vector, size_t i, void *element);
  int       vector_delete(vector_t *vector, size_t i);
  int       vector_find(vector_t *vector, void *element, int(*comapre)(void *element, void *ele));
  size_t    vector_size(vector_t *vector);
  size_t    vector_capacity(vector_t *vector);

#ifdef __cplusplus
}
#endif

#endif //__VECTOR_H__
