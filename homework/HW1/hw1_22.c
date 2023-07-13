#include <stdio.h>
#include <stdlib.h>

int compare (void* ptr1, void* ptr2);
void* larger (void* dataPtr1, void* dataPtr2, int (*ptrToCmpFun)(void*, void*));

int main (void)
{
    char* a = "abc";
    char* b = "abc ";
    char* lrg;

    lrg = (char*) larger (a, b, compare);
    printf ("Larger value is: %s\n", lrg);
    return 0;
}

int compare (void* ptr1, void* ptr2)
{
    char* s1 = (char*)ptr1;
    char* s2 = (char*)ptr2;

    for(;; s1++, s2++) {
        if(!((*s1) * (*s2))) // 是否達到任一字串結尾
            return *s1 - *s2;
        else if(*s1 - *s2)
            return *s1 - *s2;
    }
}

void* larger (void* dataPtr1, void* dataPtr2, int (*ptrToCmpFun)(void*, void*))
{
    if((*ptrToCmpFun) (dataPtr1, dataPtr2) > 0)
        return dataPtr1;
    else
        return dataPtr2;
}
