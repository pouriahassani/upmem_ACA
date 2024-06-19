#include <assert.h>
#include <dpu.h>
#include <dpu_log.h>
#include <stdio.h>
#include <stdint.h>
#ifndef DPU_BINARY
#define DPU_BINARY "./buddy_allocator"
#endif

int main(void) {
  struct dpu_set_t set, dpu;
  DPU_ASSERT(dpu_alloc(1, NULL, &set));
  uint32_t num_ranks,num_dpus;
  dpu_get_nr_ranks(set,&num_ranks);
  dpu_get_nr_dpus(set,&num_dpus);
  printf("\nnumber of ranks for set %d",num_ranks);
  printf("\nnumber of dpus for set %d",num_dpus);
  DPU_ASSERT(dpu_load(set, DPU_BINARY, NULL));
  DPU_ASSERT(dpu_launch(set, DPU_SYNCHRONOUS));
  DPU_FOREACH(set, dpu) {
  DPU_ASSERT(dpu_log_read(dpu, stdout));
  }

  DPU_ASSERT(dpu_free(set));

  return 0;
}