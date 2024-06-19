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
__host uint32_t checksum;
int main(){

    for(int i = me()*NR_ELEMENTS_PER_TASKLET ; i < (me()+1)*NR_ELEMENTS_PER_TASKLET;i+=CACHE_SIZE){
        mram_read(&buffer[i],&cache[me()][0],sizeof(uint32_t)*CACHE_SIZE);
        uint32_t tmp_checksum = 0;
        for(int j = 0;j<CACHE_SIZE;j++)
            tmp_checksum += cache[me()][j];
        checksums[me()] += tmp_checksum; 
    }
    if(!me()){
        for(int i = 0;i<NR_TASKLETS;i++){
            checksum += checksums[i];
        }
        printf("\nThe checksum is %u",checksum);
    }
}