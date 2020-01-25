#include <stdio.h>
#include <math.h>
#include "bmap.h"
#include "utils.h"

#define BITS 26
#define SETS 5

int main(){
    int sets[SETS] = {0, 3, 8, 23, 25};
    bmap_t map;

    fprintf(stdout, " >> Creating a %d-bit map(rounded up to the nearest multiple of %d)\n", BITS, BYTE_TO_BITS);
    bmap_init(&map, BITS);

    for(int i = 0; i < SETS; i++){
        fprintf(stdout, " >> Setting bit number %d\n", sets[i]);
        bmap_set(&map, sets[i]);
    }

    fprintf(stdout, " >> Resulting map\n");
    for(int i = 0; i < BITS; i++)
        fprintf(stdout, "%hhd ", bmap_get(&map, i));
    fputc('\n', stdout);

    fprintf(stdout, " >> Reseting bit %d\n", sets[0]);
    bmap_reset(&map, sets[0]);

    fprintf(stdout, " >> Toggling bits %d & %d\n", sets[SETS-1] - 1, sets[SETS-1]);
    bmap_toggle(&map, sets[SETS - 1] - 1);
    bmap_toggle(&map, sets[SETS - 1]);

    bmap_print(&map);
    bmap_free(&map);
    return 0;
}