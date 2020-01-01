#include <stdio.h>
#include <time.h>
#include "set_person.h"
#include "person.h"
#include "set.h"

#define MAX_ID 100
#define PEOPLE 5

int main(){
    char *names[PEOPLE] = {"John Doe", "Mary Ann", "Black Mamba", "Sunset Call", "Tomato Sauce"};
    uint64_t id;
    set_t hash_set;

    srand(time(NULL));

    // initialize a hash_set for a specific data type
    set_init(&hash_set, sizeof(person_t), get_key, init_wrapper_with_id, seek, print, destroy);

    // insert objects into the hash_set
    for(int i = 0; i < PEOPLE; i++){
      id = rand() % MAX_ID;
      set_put(&hash_set, id, names[i]);
    }

    // display the hash_set
    fprintf(stdout, "\e[1;4m >> After insertion, using the default printing methods for all inner parts\n\e[0m");
    set_print(&hash_set);

    fprintf(stdout, "\n\e[1;4m%100c\n\n >> Person with id\e[0m: %lu", ' ', id);
    print(set_get(&hash_set, id));

    fprintf(stdout, "\n\e[1;4m >> Replacing value for id:\e[0m %lu", id);
    set_replace(&hash_set, id, "Walt Disney");
    print(set_get(&hash_set, id));

    fprintf(stdout, "\n\e[1;4m >> After deleting value for id:\e[0m %lu \e[1;4m(using a for each)\e[0m", id);
    set_remove(&hash_set, id);
    set_foreach(&hash_set, print);

    fprintf(stdout, "\n\e[1;4m >> Also a simplified displaying approach\n\e[0m");
    set_display(&hash_set);

    // free all resources allocated for the buckets and their content
    set_free(&hash_set);
}