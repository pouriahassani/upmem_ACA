#include <stdio.h>
#include <barrier.h>
#include <defs.h>


BARRIER_INIT(my_barrier,NR_TASKLETS);

int global_var = 0;
int main(){
    if(!me())
        global_var = 1;
    barrier_wait(&my_barrier); 
    printf("\n I am tasklet %u and I read glbal_var as %d",me(),global_var);
}