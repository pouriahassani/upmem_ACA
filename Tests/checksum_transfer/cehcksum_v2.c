#include <stdio.h>
#include <mram.h>
#include <stdint.h>
#include <defs.h>
#include <mram.h>
#define BUFFER_SIZE 1024
#define NR_ELEMENTS_PER_TASKLET (BUFFER_SIZE / NR_TASKLETS)
__mram uint32_t buffer[BUFFER_SIZE];
uint32_t checksums[NR_TASKLETS] = {0};
#define CACHE_SIZE 32
__dma_aligned uint32_t cache[NR_TASKLETS][CACHE_SIZE];
int main(){

    for(int i = me()*NR_ELEMENTS_PER_TASKLET ; i < (me()+1)*NR_ELEMENTS_PER_TASKLET;i+=CACHE_SIZE){
        mram_read(&buffer[i],cache[me()][0],sizeof(uint32_t)*CACHE_SIZE);
        for(int j = 0;j<CACHE_SIZE;j++)
            checksums[me()] += cache[j];
    }
    if(!me()){
        uint32_t checksum =0;
        for(int i = 0;i<NR_TASKLETS;i++){
            checksum += checksums[i];
        }
        printf("\nThe checksum is %u",checksum);
    }
}