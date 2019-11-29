#include <stdio.h>
#include <time.h>
#include "map_person.h"
#include "person.h"
#include "map.h"

#define MAX_ID 100
#define PEOPLE 5

int main(){
    char *names[PEOPLE] = {"John Doe", "Mary Ann", "Black Mamba", "Sunset Call", "Tomato Sauce"};
    uint64_t id;
    map_t map;

    srand(time(NULL));

    // initialize a map for a specific data type
    map_init(&map, sizeof(person_t), init_wrapper_with_id, compare, print, get_key, destroy);

    // insert objects into the map
    for(int i = 0; i < PEOPLE; i++){
      id = rand() % MAX_ID;
      map_put(&map, id, names[i]);
    }

    // display the map
    map_print(&map);

    fprintf(stdout, "\n\e[1;4mPerson with id\e[0m: %lu\n", id);
    print(map_get(&map, id));

    fprintf(stdout, "Replacing the above person's name\n");
    //map_replace(&map, &(person_t){id, "Walt Disney"});

    // free all resources allocated for the buckets and their content
    map_free(&map);
}