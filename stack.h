#ifndef STACK_H
#define STACK_H

#include <stdlib.h>

typedef int STACK_TYPE;
typedef uint64_t ERROR_T;

// const int opening = 0xBEBEBE;
// const int ending = 0xDABAB7;
// const long long int poison = 0xB00B1E5;

#ifndef NDEBUG

struct stack_t
{
    STACK_TYPE *data;
    size_t size;
    size_t capacity;
    STACK_TYPE poison;
};

#else //NDEBUG

struct stack_t
{
    STACK_TYPE *data;
    size_t size;
    size_t capacity;
};

#endif

enum error_codes
{
    ALL_OKEY = 0b00000,
    NULL_STRUCT =  0b000001,
    NULL_DATA =    0b000010,
    INVALID_SIZE = 0b000100,
    STACK_INITIALIZE_ERROR = 0b001000,
    STACK_RESIZE_ERROR = 0b010000,
    POISON_ERROR = 0b100000
};

typedef struct stack_t sstack_t;

void stack_init (sstack_t* stk1, size_t capacity);
void stack_destructor (sstack_t* stk1);
void stack_push (sstack_t* stk1, STACK_TYPE num);
error_codes resize (sstack_t* stk1);
int stack_pop (sstack_t* stk1);
#ifndef NDEBUG
ERROR_T verificator (sstack_t* stk1);
void stack_dump (sstack_t* stk1, const char *file_name, const int line_number);
#endif

#ifndef NDEBUG

#define STACK_INIT(stk1, capacity, POISON)  stk1.poison = POISON;               \
                                            stack_init (&stk1, capacity)         \

#define POISON_IN_THE_LAST_CELL(stk) {stk->data [stk->size - 1] = poison;}

#define VERIFY(stk, error)    do{                                               \
                                    ERROR_T res = 0;                            \
                                    res = verificator(stk);                     \
                                    res |= error;                               /*TODO remove this line*/\
                                    if (res != 0)                               \
                                    {                                           \
                                        stack_dump (stk,  __FILE__, __LINE__);  \
                                        abort();                                 \
                                    }                                           \
                                } while(false)                                  \

#else /*NDEBUG*/

#define STACK_INIT(stk1, capacity, POISON) stack_init (&stk1, capacity)

#define ALL_STACK_IN_THE_POISON(stk)  do{} while(false)

#define POISON_IN_THE_CELL(stk) do{ } while(false)

#define poison 0

#define VERIFY(stk, error) do{ } while(false)

#endif /*NDEBUG*/

#endif
