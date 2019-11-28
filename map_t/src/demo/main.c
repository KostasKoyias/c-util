#include <stdlib.h>
#include <time.h>
#include "map_person.h"
#include "person.h"
#include "map.h"

#define MAX_ID 100
#define PEOPLE 5

int main(){
    char *names[PEOPLE] = {"John Doe", "Mary Ann", "Black Mamba", "Sunset Call", "Tomato Sauce"};
    map_t map;

    srand(time(NULL));

    // initialize a map for a specific data type
    map_init(&map, sizeof(person_t), init_wrapper, compare, print, get_key, destroy);

    // insert objects into the map
    //for(int i = 0; i < PEOPLE; i++)
      //  map_insert(&map, &(person_t){rand() % MAX_ID, names[i]});

    // display the map
    map_print(&map);

    // free all resources allocated for the buckets and their content
    map_free(&map);
}