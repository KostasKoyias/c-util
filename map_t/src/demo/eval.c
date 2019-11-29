#include <stdio.h>
#include <time.h>
#include "map_person.h"
#include "person.h"
#include "map.h"
#include "utils.h"

#define PEOPLE 1000
#define MAX_ID 10000
#define MAX_NAME 20

int main(){
    map_t map;
    char name[MAX_NAME];
    srand(time(NULL));

    // initialize a map for a specific data type
    map_init(&map, sizeof(person_t), get_key, init_wrapper_with_id, compare, print, destroy);

    // insert objects into the map
    for(int i = 0; i < PEOPLE; i++){
        sprintf(name, "John Doe-%d", i);
        map_put(&map, rand() % MAX_ID, name);
    }

    map_display(&map);

    uint64_t dividend, i;
    for(i = dividend = 0; i < map.buckets.next; i++){
        list_t *bucket = vector_get(&(map.buckets), i);
        dividend += (float)(bucket->length * (bucket->length + 1))/2;
    }

    fprintf(stdout, "\nEvaluation of distribution: %.2f\n", 
            (dividend/(((float)map.load / (2 * map.buckets.next)) + (map.load -1 + 2 * map.buckets.next)))/10);
    map_free(&map);
}