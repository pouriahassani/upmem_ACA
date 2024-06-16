To define the number of tasklets of a program and the size of each tasklets stack, the user needs to compile the program with specific options:

NR_TASKLETS is used to define the number of tasklets.

STACK_SIZE_DEFAULT is used to define the size of the stack for all the tasklets which stack is not specified.

STACK_SIZE_TASKLET_<X> is used to define the size of the stack for a specific tasklet.

dpu-upmem-dpurte-clang -DNR_TASKLETS=3 -DSTACK_SIZE_DEFAULT=256 -DSTACK_SIZE_TASKLET_1=2048 -O2 -o tasklet_stack_check tasklet_stack_check.c
Note: Make sure to put those options before the -o option, otherwise they won’t be taken into account by the clang driver.