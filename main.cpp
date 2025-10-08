#define NDEBUG
#include <stdio.h>
#include <assert.h>
#include <stdint.h>
#include <stdlib.h>

#include "stack.h"



int main ()
{
    sstack_t stk1 = {};
    ARE_YOU_OKEY(STACK_INIT(stk1, 5, 0xB00B1E5), stack_destructor(&stk1));
    stack_push (&stk1, 10);
    int x = stack_pop (&stk1);
    printf ("%d", x);
    //stack_dump(&stk1, __FILE__, __LINE__);
    stack_destructor (&stk1);
    
    return 0;
}

// TODO replace to stack.cpp

error_codes stack_init (sstack_t* stk1, size_t capacity, STACK_TYPE poison)
{
    assert (capacity > 0);
    assert (stk1);
    assert (stk1->data == NULL);
    poison = poison;
#ifndef NDEBUG
    stk1->poison = poison;
#endif
    stk1->capacity = capacity;
    stk1->data = (STACK_TYPE*)calloc(stk1->capacity, sizeof(*stk1->data));
    if (stk1->data == NULL)
    {
        return STACK_INITIALIZE_ERROR;
    }
    stk1->size = 0;

#ifndef NDEBUG
    for (size_t i = stk1->size ;i < stk1->capacity; i++ )
        {
            stk1->data[i] = stk1->poison;
        }
#endif
    
    VERIFY(stk1);
    return ALL_OKEY;
}

void stack_destructor (sstack_t* stk1)
{
    free (stk1->data);

#ifndef NDEBUG
    stk1->data = NULL;
    stk1->capacity = stk1->poison;
    stk1->size = stk1->poison;
#endif

    return;
}

void stack_push (sstack_t* stk1, STACK_TYPE num)
{
    VERIFY(stk1);

    if (stk1->size == stk1->capacity)
    {
        ARE_YOU_OKEY(resize(stk1));
    }

    stk1->data [stk1->size] = num;
    stk1->size++;

    VERIFY(stk1);
    return;
}

// ERROR_HANDLE(resize(stk), free(array2);free(array3););

// #define ERROR_HANDLE(func, ...) 
//     do {
//         error_t error = func;
//         if (error) {
//             fprintf(stderr, "smth");
//             __VA_ARGS__
//             return error;
//         }
//     } while(false)


error_codes resize (sstack_t* stk1)
{
    stk1->capacity = (2 * stk1->capacity);
    STACK_TYPE* realloc_err = (STACK_TYPE*)realloc (stk1->data, stk1->capacity * sizeof (*stk1->data));
    if (realloc_err == NULL)
    {
        return STACK_RESIZE_ERROR;
    }
    VERIFY(stk1);
    return ALL_OKEY;
}

int stack_pop (sstack_t* stk1)
{
    VERIFY(stk1);

    STACK_TYPE pop_value = stk1->data [stk1->size - 1];
    
#ifndef NDEBUG
    stk1->data [stk1->size - 1] = stk1->poison;
#endif

    stk1->size -=1;

    VERIFY(stk1);

    return pop_value;
}

#ifndef NDEBUG
ERROR_T verificator (sstack_t* stk1)
{
    ERROR_T res_error = 0;
    if (stk1 == NULL)
    {
        res_error |= NULL_STRUCT;
        return res_error;
    }

    if (stk1->data == NULL)
    {
        res_error |= NULL_DATA;
        return res_error;
    }

    if (stk1->size > stk1->capacity)
    {
        res_error |= INVALID_SIZE;
    }

    for (size_t i = 0; i < stk1->capacity; i++)
    {
        if (i < stk1->size)
        {
            if (stk1->data[i] == stk1->poison)
            {
                res_error |= POISON_ERROR;
                return res_error;
            }
        }
        else
        {
            if (stk1->data[i] != stk1->poison)
            {
                res_error |= POISON_ERROR;
                return res_error;
            }
        }
    }
    return res_error;
}

void stack_dump (sstack_t* stk1, const char *file_name, const int line_number)
{
    printf ("\nstack_dump was called from %s : %d\n", file_name, line_number);

    if (stk1 == NULL)
    {
        printf ("stack point is NULL\n");
        return;
    }

    printf ("Stack [%p]\n", stk1);

    if (stk1->data == NULL)
    {
        printf ("data pooint is NULL\n"
                "size = %llu\n"
                "capacity = %llu\n", stk1->size, stk1->capacity);
        return ;
    }

    printf ("{\n"
            "size = %llu\n"
            "capacity = %llu\n"
            "data [%p]\n", stk1->size, stk1->capacity, stk1->data);
    for (size_t i = 0; i < stk1->capacity; i++)
    {
        if (i <= stk1->size)
        {
            printf ("* [%llu] = %x\n", i, stk1->data[i]);
        }
        else
        {
            printf ("[%llu] = %x\n", i, stk1->data[i]);
        }
    }
    printf ("    }\n"
            "}\n");
    return ;
}
#endif 