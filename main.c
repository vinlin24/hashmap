// main.c

/*
 * Some sanity check test code.
 */

#include <stdio.h>

#include "hashmap.h"

#define NUM_TEST_KEYS 4ULL
#define NUM_TEST_VALUES NUM_TEST_KEYS - 1

static char const *test_keys[NUM_TEST_KEYS] = {
    "Alice",
    "Bob",
    "Carlos",
    "Dave"};
static int test_values[NUM_TEST_VALUES] = {
    30,
    6,
    15};

static void print_pair(const Hashmap *hm, char const *key)
{
    int value = hm_get(hm, key);
    if (value == NOT_FOUND)
        printf("Key \"%s\" is not mapped to any value.\n", key);
    else
        printf("Key \"%s\" is mapped to the value %d.\n", key, value);
}

static void print_size(const Hashmap *hm)
{
    size_t size = hm_size(hm);
    printf("The hashmap currently has " LLU " pair(s) in it.\n", size);
}

int main(void)
{
    Hashmap hm;
    hm_init(&hm);
    hm_print(&hm);
    hm_print_lists(&hm);
    print_size(&hm);

    // Insert initial dummy data
    for (size_t i = 0; i < NUM_TEST_VALUES; i++)
    {
        hm_put(&hm, test_keys[i], test_values[i]);
    }

    // Show that all the data is present, or a key is not in the map
    hm_print(&hm);
    hm_print_lists(&hm);
    print_size(&hm);

    // Test removing keys, including the case where the key does not exist
    char const *values_to_remove[] = {"Bob", "Dave"};
    int value_removed;
    for (size_t i = 0; i < sizeof(values_to_remove) / sizeof(char const *); i++)
    {
        char const *key = values_to_remove[i];
        value_removed = hm_remove(&hm, key);
        if (value_removed == NOT_FOUND)
            printf("Key \"%s\" was not found, hashmap unmodified.\n", key);
        else
            printf("Removed key \"%s\", which was mapped to value %d.\n",
                   key,
                   value_removed);
    }
    print_pair(&hm, "Bob");
    print_size(&hm);

    // Try inserting more pairs than there are buckets to prove that the linked
    // list logic works

    // NOTE: DON'T REUSE THE SAME BUFFER FOR SUCH TEST CASES.  The key in a
    // hashmap node is stored as a pointer to the string, so if you overwrite
    // the same buffer, you change previous keys in the hashmap.
    char buffers[HASHMAP_SIZE * 2][100];
    for (size_t i = 0; i < HASHMAP_SIZE * 2; i++)
    {
        snprintf(buffers[i], 100, LLU, i);
    }
    printf("Inserting " LLU " pairs into the hashmap...\n", HASHMAP_SIZE * 2);
    for (size_t i = 0; i < HASHMAP_SIZE * 2; i++)
    {
        hm_put(&hm, buffers[i], i);
        hm_print_lists(&hm);
        printf("-----------\n");
    }
    printf("Successfully performed " LLU " insert operations.\n",
           HASHMAP_SIZE * 2);
    print_size(&hm);

    char **current_keys = hm_keys(&hm);
    size_t current_size = hm_size(&hm);
    for (size_t i = 0; i < current_size; i++)
    {
        printf("%s ", current_keys[i]);
    }
    printf("\n");
    hm_free_keys_array(current_keys, current_size);

    return 0;
}
