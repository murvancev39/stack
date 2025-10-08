#include <stdio.h>
#include <stdlib.h>

int main()
{
    const char *s1 = "12312321";
    const char *s2 = "ABC";
    s1 = s2;
    printf("s1: \"%s\"\n", s1);
    // const char *s2 = "s2";
    // const char * const s3 = "s3";
    // char * const s4 = "s4";

    // s1[0] = '$';
    // s2 = "s2new";
    // s2[0] = '$';
    // s3 = "s3new";
    // s3[0] = '$';
    // s4 = "s4new";
    // s4[0] = '$';
    

    return 0;
}