#include <stdio.h>
#include <time.h>
#include "hset_person.h"
#include "person.h"
#include "hset.h"
#include "utils.h"

#define PEOPLE 1000
#define MAX_ID 10000
#define MAX_NAME 20

int main(){
    hset_t hash_set;
    char name[MAX_NAME];
    srand(time(NULL));

    // initialize a hash set for a specific data type
    hset_init(&hash_set, sizeof(person_t), get_key, init_wrapper_with_id, compare, print, destroy);

    // insert objects into the hash_set
    for(int i = 0; i < PEOPLE; i++){
        sprintf(name, "John Doe-%d", i);
        hset_put(&hash_set, rand() % MAX_ID, name);
    }

    hset_display(&hash_set);

    uint64_t dividend, i;
    for(i = dividend = 0; i < hash_set.buckets.next; i++){
        list_t *bucket = vector_get(&(hash_set.buckets), i);
        dividend += (float)(bucket->length * (bucket->length + 1))/2;
    }

    fprintf(stdout, "\nEvaluation of distribution: %.2f\n", 
            (dividend/(((float)hash_set.load / (2 * hash_set.buckets.next)) + (hash_set.load -1 + 2 * hash_set.buckets.next)))/10);
    hset_free(&hash_set);
}