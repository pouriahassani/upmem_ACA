#include <stdio.h>
#include <defs.h>


int main(){
    /*
        me()
        Returns the current tasklet's sysname.
        sysname_t me();
    */
    sysname_t myName = me();
    /*
        check_stack returns the number of unused 32-bits words in the current thread's stack.
        If the number is negative, it indicates by how much 32-bits words the stack overflowed.
        int check_stack();
    */
    printf("\n\t\t******\nI am thread number %u\tand my unused stack size is %d words\n",myName,check_stack());
}