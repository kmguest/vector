#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Vector/vector.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace VectorUnitTest
{		
	TEST_CLASS(VectorUnitTest$INT)
	{
	public:

    vector_t vector;
    int   CAPACITY = 128;
		
		TEST_METHOD(create_vector)
		{
      vector_init(&vector, CAPACITY);
      int size = vector_size(&vector);
      Assert::AreEqual(0, size);
      int capacity = vector_capacity(&vector);
      Assert::AreEqual(CAPACITY, capacity);
      vector_free(&vector, NULL);
      size = vector_size(&vector);
      Assert::AreEqual(0, size);
      capacity = vector_capacity(&vector);
      Assert::AreEqual(CAPACITY, capacity);
		}

    TEST_METHOD(add$int$ele_vector)
    {
      vector_init(&vector, CAPACITY);
      int ele1 = 1;
      vector_add(&vector, &ele1);
      int ele2 = 2;
      vector_add(&vector, &ele2);
      int size = vector_size(&vector);
      Assert::AreEqual(2, size);
      vector_free(&vector, NULL);
      size = vector_size(&vector);
      Assert::AreEqual(0, size);
    }

    TEST_METHOD(add$int$ele$inc$capacity_vector)
    {
      vector_init(&vector, 2);
      int eles[] = {1,2,3,4,5,6,7,8};
      vector_add(&vector, &eles[0]);
      vector_add(&vector, &eles[1]);
      int capacity = vector_capacity(&vector);
      Assert::AreEqual(2, capacity);
      vector_add(&vector, &eles[2]);
      capacity = vector_capacity(&vector);
      Assert::AreEqual(2 + CAPACITY_INC, capacity);
      vector_add(&vector, &eles[3]);
      vector_free(&vector, NULL);
    }

    TEST_METHOD(get$int$ele_vector)
    {
      vector_init(&vector, CAPACITY);
      int ele1 = 1;
      vector_add(&vector, &ele1);
      int ele2 = 2;
      vector_add(&vector, &ele2);
      int size = vector_size(&vector);
      int *ele = (int *)vector_get(&vector, 0);
      Assert::AreEqual(1, *ele);
      ele = (int *)vector_get(&vector, 1);
      Assert::AreEqual(2, *ele);
      ele = (int *)vector_get(&vector, 2);
      Assert::AreEqual(true, ele==NULL);
      vector_free(&vector, NULL);
    }

    TEST_METHOD(delete$ini$ele_vector)
    {
      vector_init(&vector, CAPACITY);
      int eles[] = { 1,2,3,4,5,6,7,8 };
      for (int i=0;i<sizeof(eles)/sizeof(int);i++)
        vector_add(&vector, &eles[i]);
      Assert::AreEqual(8, (int) vector_size(&vector));

      int *ele = (int*)vector_get(&vector, 2);
      Assert::AreEqual(true, ele!=NULL);
      Assert::AreEqual(3, *ele);

      Assert::AreEqual(0,vector_delete(&vector, 1));
      Assert::AreEqual(7, (int)vector_size(&vector));

      ele = (int*)vector_get(&vector, 1);
      Assert::AreEqual(true, ele != NULL);
      Assert::AreEqual(3, *ele);

      ele = (int*)vector_get(&vector, 2);
      Assert::AreEqual(true, ele != NULL);
      Assert::AreEqual(4, *ele);

      Assert::AreEqual(-1, vector_delete(&vector, 10));

      vector_free(&vector, NULL);
    }

    static int _int_cmp(void *e1, void *e2)
    {
      return *((int*)e1) - *((int*)e2);
    }

    TEST_METHOD(find$ini$ele_vector)
    {
      vector_init(&vector, CAPACITY);
      int eles[] = { 1,2,3,4,5,6,7,8 };
      for (int i = 0; i < sizeof(eles) / sizeof(int); i++)
        vector_add(&vector, &eles[i]);
      Assert::AreEqual(8, (int)vector_size(&vector));

      int *ele = (int*)vector_get(&vector, 2);
      Assert::AreEqual(true, ele != NULL);
      Assert::AreEqual(3, *ele);

      int look_for = 2;
      Assert::AreEqual(-1, vector_find(&vector, &look_for, NULL)); //fail default comparator compare pointers
      Assert::AreEqual( 2, vector_find(&vector, ele, NULL));       //success

      Assert::AreEqual( 1, vector_find(&vector, &look_for, _int_cmp));
      look_for = 20;
      Assert::AreEqual(-1, vector_find(&vector, &look_for, _int_cmp));

      vector_free(&vector, NULL);
    }

    static void _free_int(void *ele)
    {
      free(ele);
    }

    TEST_METHOD(auto$free$ele_vector)
    {
#define ESize  5
      int *eles[ESize] = { NULL, };
      vector_init(&vector, CAPACITY);
      for (int i = 0; i < ESize; i++)
      {
        eles[i] = (int*)malloc(sizeof(int));
        *eles[i] = i+1;
        vector_add(&vector, eles[i]);
      }

      for (int i = 0; i < ESize; i++)
      {
        int *e = (int*)vector_get(&vector, i);
        Assert::AreEqual(true, e != NULL);
        Assert::AreEqual(i + 1, *e);
        Assert::AreEqual(true, e == eles[i]);
      }

      vector_free(&vector, _free_int);

      for (int i = 0; i < ESize; i++)
      {
        int *e = (int*)vector_get(&vector, i);
        Assert::AreEqual(true, e == NULL);
      }
    }

	};

  TEST_CLASS(VectorUnitTest$STRUCT)
  {
  public:

    vector_t vector;
    int   CAPACITY = 128;
    typedef struct test_s
    {
      int val;
      int val1;
    } test_t;

    TEST_METHOD(add$struct_vector)
    {
      test_t t1 = { 0, };
      test_t t2 = { 0, };
      test_t t3 = { 0, };

      vector_init(&vector, CAPACITY);
      vector_add(&vector, &t1);
      vector_add(&vector, &t2);
      vector_add(&vector, &t3);
      int size = vector_size(&vector);
      Assert::AreEqual(3, size);
      vector_free(&vector, NULL);
    }

    TEST_METHOD(get$struct_vector)
    {
      test_t t1 = { 0, };
      test_t t2 = { 1, 2};
      test_t t3 = { 2, 4};

      vector_init(&vector, CAPACITY);
      vector_add(&vector, &t1);
      vector_add(&vector, &t2);
      vector_add(&vector, &t3);
      int size = vector_size(&vector);
      Assert::AreEqual(3, size);

      test_t *t = (test_t *)vector_get(&vector, 0);
      Assert::AreEqual(true, t != NULL);
      Assert::AreEqual(0, t->val);

      vector_free(&vector, NULL);
    }

    static int _struct_cmp(void *e1, void *e2)
    {
      int v = ((test_t*)e1)->val - ((test_t*)e2)->val;
      if (v==0)
         v = ((test_t*)e1)->val1 - ((test_t*)e2)->val1;
      return v;
    }

    TEST_METHOD(find$ini$STRUCT_vector)
    {
      vector_init(&vector, CAPACITY);
      test_t eles[] = { {1},{2},{3},{4},{5},{6},{7},{8} };
      for (int i = 0; i < sizeof(eles) / sizeof(test_t); i++)
        vector_add(&vector, &eles[i]);
      Assert::AreEqual(8, (int)vector_size(&vector));

      test_t *ele = (test_t*)vector_get(&vector, 2);
      Assert::AreEqual(true, ele != NULL);
      Assert::AreEqual(3, ele->val);

      test_t look_for = { 2 };
      Assert::AreEqual(-1, vector_find(&vector, &look_for, NULL)); //fail default comparator compare pointers
      Assert::AreEqual(2, vector_find(&vector, ele, NULL));       //success

      Assert::AreEqual(1, vector_find(&vector, &look_for, _struct_cmp));
      look_for = { 2, 20 };
      Assert::AreEqual(-1, vector_find(&vector, &look_for, _struct_cmp));

      vector_free(&vector, NULL);
    }

    static void _free_test_t(void *ele)
    {
      free(ele);
    }

    TEST_METHOD(auto$free$ele$STRUCT_vector)
    {
#define ESize  5
      test_t *eles[ESize] = { NULL, };
      vector_init(&vector, CAPACITY);
      for (int i = 0; i < ESize; i++)
      {
        eles[i] = (test_t*)malloc(sizeof(test_t));
        eles[i]->val = i + 1;
        eles[i]->val1 = i + 10;
        vector_add(&vector, eles[i]);
      }

      for (int i = 0; i < ESize; i++)
      {
        test_t *e = (test_t*)vector_get(&vector, i);
        Assert::AreEqual(true, e != NULL);
        Assert::AreEqual(i + 1, e->val);
        Assert::AreEqual(true, e == eles[i]);
      }

      vector_free(&vector, _free_test_t);

      for (int i = 0; i < ESize; i++)
      {
        test_t *e = (test_t*)vector_get(&vector, i);
        Assert::AreEqual(true, e == NULL);
      }
    }
  };
}