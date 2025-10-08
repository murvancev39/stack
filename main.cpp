#include <stdio.h>
#include <assert.h>
#include <stdint.h>
#include <stdlib.h>

#include "stack.h"


int main ()
{
    sstack_t stk1 = {};
    stack_init (&stk1, 5);
    stack_push (&stk1, 10);
    int x = stack_pop (&stk1);
    printf ("%d", x);
    stack_destructor (&stk1);
    
    return 0;
}

// TODO replace to stack.cpp

void stack_init (sstack_t* stk1, size_t capacity) // TODO add poison in args
{
    assert (capacity > 0);
    assert (stk1);
    assert (stk1->data == NULL);

    stk1->capacity = capacity;
    stk1->data = (STACK_TYPE*)calloc(stk1->capacity, sizeof(*stk1->data));
    if (stk1->data == NULL)
    {
        // return STACK_INITIALIZE_ERROR;
        VERIFY(stk1, STACK_INITIALIZE_ERROR); // TODO return error code
    }
    stk1->size = 0;

    ALL_STACK_IN_THE_POISON(stk1); // TODO remove define or do func
    
    VERIFY(stk1, 0);
}//

void stack_destructor (sstack_t* stk1)
{
    free (stk1->data);
    stk1->data = NULL; // TODO in debug
    stk1->capacity = poison;
    stk1->size = poison;
    return;
}

void stack_push (sstack_t* stk1, STACK_TYPE num)
{
    VERIFY(stk1, 0);

    if (stk1->size == stk1->capacity)
    {
        error_codes err = resize(stk1);
        if (err != ALL_OKEY)
        {
            VERIFY(stk1, STACK_RESIZE_ERROR); // TODO return STACK_RESIZE_ERROR, in release also
        }
    }

    stk1->data [stk1->size] = num;
    stk1->size++;

    VERIFY(stk1, 0);
    return;
}

error_codes resize (sstack_t* stk1)
{
    stk1->capacity = (2 * stk1->capacity);
    STACK_TYPE* realloc_err = (STACK_TYPE*)realloc (stk1->data, stk1->capacity * sizeof (*stk1->data));
    if (realloc_err == NULL)
    {
        return STACK_RESIZE_ERROR;
    }
    VERIFY(stk1, 0);
    return ALL_OKEY;
}

int stack_pop (sstack_t* stk1)
{
    VERIFY(stk1, ALL_OKEY);

    STACK_TYPE pop_value = stk1->data [stk1->size - 1];
    
    POISON_IN_THE_LAST_CELL(stk1); // TODO in debug
    
    stk1->size -=1;

    VERIFY(stk1, ALL_OKEY);

    return pop_value;
}

ERROR_T verificator (sstack_t* stk1)
{
    ERROR_T res_error = 0;
    if (stk1 == NULL)
    {
        res_error |= NULL_STRUCT; // TODO return
    }

    if (stk1->data == NULL)
    {
        res_error |= NULL_DATA;
    }

    if (stk1->size > stk1->capacity)
    {
        res_error |= INVALID_SIZE;
    }

    // TODO poisons check
    return res_error;
}

void stack_dump (sstack_t* stk1, const char *file_name, const int line_number)
{
    printf ("\nstack_dump was called from %s : %d\n", file_name, line_number);

    if (stk1 != NULL)
    {
        printf ("Stack [%p]\n", stk1);
    }
    else
    {
        printf ("stack point is NULL\n");
        abort ();
    }

    if (stk1->data == NULL)
    {
        printf ("data pooint is NULL\n"
                "size = %llu\n"
                "capacity = %llu\n", stk1->size, stk1->capacity);
        abort ();
    }
    printf ("{\n"
            "size = %llu\n"
            "capacity = %llu\n"
            "data [%p]\n", stk1->size, stk1->capacity, stk1->data);
    for (size_t i = 0; i < stk1->capacity; i++)
    {
        if (i <= stk1->size)
        {
            printf ("* [%llu] = %d\n", i, stk1->data[i]);
        }
        else
        {
            printf ("[%llu] = %d\n", i, stk1->data[i]);
        }
    }
    printf ("    }\n"
            "}\n");
    abort ();
}