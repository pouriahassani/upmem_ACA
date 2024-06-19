#include <mram.h>
#include <stdint.h>
#include <defs.h>
#include <stdio.h>
#define BUFFER_SIZE 256

/* Buffer in MRAM. */
uint8_t __mram mram_array[BUFFER_SIZE];

int main() {
  /* A 256-bytes buffer in WRAM, containing the initial data. */
  __dma_aligned uint8_t input[BUFFER_SIZE];
  /* The other buffer in WRAM, where data are copied back. */
  __dma_aligned uint8_t output[BUFFER_SIZE];

  /* Populate the initial buffer. */
  for (int i = 0; i < BUFFER_SIZE; i++)
    input[i] = i;
  mram_write(input, mram_array, sizeof(input));

  /* Copy back the data. */
  mram_read(mram_array, output, sizeof(output));
  for (int i = 0; i < BUFFER_SIZE; i++)
    if (i != output[i])
      printf("\nI am tasklet %d and the data I read from MRAM is not matching!",me());
printf("\nI am tasklet %d and the data I successfuly read data from MRAM",me());

  return 0;
}