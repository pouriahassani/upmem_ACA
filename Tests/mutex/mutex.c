#include <stdio.h>
#include <mutex.h>
#include <defs.h>
#define UNDEFINED_VAR  (-1)
int shared_var = UNDEFINED_VAR;
MUTEX_INIT(my_mutex);

int main(){
    mutex_lock(my_mutex);
    if(shared_var == UNDEFINED_VAR)
        shared_var = me();
    mutex_unlock(my_mutex);
    if( !me() )
        printf("The first thread that reach shared_var is %d %d\n",shared_var,NR_TASKLETS);
}