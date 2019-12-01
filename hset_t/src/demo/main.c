#include <stdio.h>
#include <time.h>
#include "hset_person.h"
#include "person.h"
#include "hset.h"

#define MAX_ID 100
#define PEOPLE 5

int main(){
    char *names[PEOPLE] = {"John Doe", "Mary Ann", "Black Mamba", "Sunset Call", "Tomato Sauce"};
    uint64_t id;
    hset_t hash_set;

    srand(time(NULL));

    // initialize a hash_set for a specific data type
    hset_init(&hash_set, sizeof(person_t), get_key, init_wrapper_with_id, seek, print, destroy);

    // insert objects into the hash_set
    for(int i = 0; i < PEOPLE; i++){
      id = rand() % MAX_ID;
      hset_put(&hash_set, id, names[i]);
    }

    // display the hash_set
    fprintf(stdout, "\e[1;4m >> After insertion, using the default printing methods for all inner parts\n\e[0m");
    hset_print(&hash_set);

    fprintf(stdout, "\n\e[1;4m%100c\n\n >> Person with id\e[0m: %lu", ' ', id);
    print(hset_get(&hash_set, id));

    fprintf(stdout, "\n\e[1;4m >> Replacing value for id:\e[0m %lu", id);
    hset_replace(&hash_set, id, "Walt Disney");
    print(hset_get(&hash_set, id));

    fprintf(stdout, "\n\e[1;4m >> After deleting value for id:\e[0m %lu \e[1;4m(using a for each)\e[0m", id);
    hset_remove(&hash_set, id);
    hset_foreach(&hash_set, print);

    fprintf(stdout, "\n\e[1;4m >> Also a simplified displaying approach\n\e[0m");
    hset_display(&hash_set);

    // free all resources allocated for the buckets and their content
    hset_free(&hash_set);
}