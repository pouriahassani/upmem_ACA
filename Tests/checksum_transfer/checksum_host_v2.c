#include <assert.h>
#include <dpu.h>
#include <dpu_log.h>
#include <stdio.h>
#include <stdint.h>
#ifndef DPU_BINARY
#define DPU_BINARY "./checksum"
#endif
#define NB_ELEMENTS 1024
#define NB_DPUS 1
#define NB_ELEMENTS_PER_DPU (NB_ELEMENTS/NB_DPUS)
void init_array(uint32_t *buffer, int nb_elements){
    srand(0);
    for(int i=0;i<nb_elements;i++)
        buffer[i] = rand();
}

int main(void) {
  struct dpu_set_t set, dpu;
  uint32_t* buffer  = (uint32_t*)malloc(NB_ELEMENTS * sizeof(int));
  uint32_t* output = (uint32_t*)malloc(sizeof(int));
  DPU_ASSERT(dpu_alloc(NB_DPUS, NULL, &set));
  uint32_t num_ranks,num_dpus;
  dpu_get_nr_ranks(set,&num_ranks);
  dpu_get_nr_dpus(set,&num_dpus);
  printf("\nnumber of ranks for set %d",num_ranks);
  printf("\nnumber of dpus for set %d",num_dpus);
  DPU_ASSERT(dpu_load(set, DPU_BINARY, NULL));

  
  init_array(buffer,NB_ELEMENTS);
  DPU_ASSERT(dpu_copy_to(set,"buffer",0,buffer,sizeof(uint32_t) * NB_ELEMENTS_PER_DPU));
  DPU_ASSERT(dpu_launch(set, DPU_SYNCHRONOUS));
  DPU_FOREACH(set, dpu) {
  DPU_ASSERT(dpu_log_read(dpu, stdout));
  }
  DPU_FOREACH(set,dpu){ 
  DPU_ASSERT(dpu_copy_from(dpu,"checksum",0,output,sizeof(uint32_t)));
  printf("\nReturned value from the set is %u",*output);
  }
  
  DPU_ASSERT(dpu_free(set));

  return 0;
}