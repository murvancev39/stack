#ifndef STACK_H
#define STACK_H

#include <stdlib.h>

typedef int STACK_TYPE;
typedef uint64_t ERROR_T;

const int opening = 0xBEBEBE;
const int ending = 0xDABAB7;
const long long int poison = 0xB00B1E5;

struct stack_t
{
    STACK_TYPE *data;
    size_t size; // TODO size_t
    size_t capacity;
};

enum error_codes
{
    NULL_STRUCT =  0b00001,
    NULL_DATA =    0b00010,
    INVALID_SIZE = 0b00100,


};

typedef struct stack_t sstack_t;

void stack_init (sstack_t* stk1, size_t capacity);
void stack_destructor (sstack_t* stk1);
void stack_push (sstack_t* stk1, STACK_TYPE num);
void resize (sstack_t* stk1);
int stack_pop (sstack_t* stk1);
ERROR_T verificator (sstack_t* stk1);
void stack_dump (sstack_t* stk1, const char *file_name, const int line_number);

#ifndef NDEBUG

#define VERIFY(stk)     {\
                            static ERROR_T res = 0;                         \
                            res = verificator(stk);                         \
                            static const char *file_name = __FILE__;        \
                            static const int line_number = __LINE__;        \
                            if (res != 0)                                   \
                            {                                               \
                                stack_dump (stk, file_name, line_number);   \
                            }                                               \
                        }\
                        
#else /*NDEBUG*/

#define VERIFY(stk) do{ } while(false)

#endif /*NDEBUG*/

#endif
