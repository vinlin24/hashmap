// hashmap.h

/*
 * My implementation of a hashmap. This is a good learning exercise for the C
 * programming language and basic data structures/algorithms. It's also useful
 * knowledge to have in the back pocket since hashmaps are not built into C.
 */

#ifndef HASHMAP_H_INCLUDED
#define HASHMAP_H_INCLUDED

#include <stdlib.h>

/* ========= */
/* Constants */
/* ========= */

/**
 * @brief The number of buckets the hashmap uses.
 */
#define HASHMAP_SIZE 5ULL

/**
 * @brief Special sentinel value to use when a key does not exist in the
 * hashmap.
 */
#define NOT_FOUND -1

// The %llu format code is not recognized by MinGW
#ifdef _WIN32
#define LLU "%I64u"
#else
#define LLU "%llu"
#endif // _WIN32

/* ==================== */
/* Forward Declarations */
/* ==================== */

struct ListNode;

/* ================= */
/* Type Declarations */
/* ================= */

/**
 * @brief A simple chaining hashmap that maps C-strings (char const *) to ints.
 *
 * A limitation is that you may not use the value of the macro NOT_FOUND as a
 * mapped value as it is used as a sentinel value representing the absence of a
 * key from the hashmap.
 */
typedef struct
{
    /**
     * @brief Internal array of buckets.
     */
    struct ListNode *lists[HASHMAP_SIZE];

    /**
     * @brief Number of pairs currently mapped by the hashmap.
     */
    size_t size;

} Hashmap;

/* =================== */
/* Interface Functions */
/* =================== */

/**
 * @brief Run appropriate initialization code.
 *
 * @param hm Hashmap to initialize.
 */
void hm_init(Hashmap *hm);

/**
 * @brief Get the mapped value of a key.
 *
 * @param hm Hashmap to query.
 * @param key Key whose value you want.
 * @return int The value the key maps to, or NOT_FOUND if the key does not exist.
 */
int hm_get(const Hashmap *hm, char const *key);

/**
 * @brief Insert a key-value pair.  If the key already exists, the value for
 * that key is simply overwritten without warning.
 *
 * @param hm Hashmap to insert into.
 * @param key Key of the pair to insert.
 * @param value Value of the pair to insert.
 */
void hm_put(Hashmap *hm, char const *key, int value);

/**
 * @brief Remove a key-value pair.  If the key does not exist, the hashmap is
 * not modified.
 *
 * @param hm Hashmap to remove from.
 * @param key Key of the pair to remove.
 * @return int Value of the key that was removed.  NOT_FOUND if the key was not
 * present.
 */
int hm_remove(Hashmap *hm, char const *key);

/**
 * @brief Get the number of elements in the hashmap.
 *
 * @param hm Hashmap to interrogate.
 * @return size_t Number of key-value pairs currently mapped by the hashmap.
 *
 */
size_t hm_size(const Hashmap *hm);

/**
 * @brief Print each key-value pair on a separate line in the format "KEY":
 * VALUE\n".  If the hashmap is empty, the literal "<EMPTY HASHMAP>\n" is
 * printed instead.
 *
 * @param hm Hashmap to print.
 */
void hm_print(const Hashmap *hm);

/**
 * @brief Function for printing a debugging-friendly representation of the
 * internal linked lists of the hashmap.
 *
 * @param hm Hashmap whose lists you want to print.
 */
void hm_print_lists(const Hashmap *hm);

/**
 * @brief Get a list of the keys in the hashmap as a dynamically allocated
 * array of dynamically allocated strings corresponding to the keys.  To free
 * this array, you can use the utility function hm_free_keys_array.
 *
 * @param hm The hashmap whose keys you want.
 * @return char const** The dynamically allocated array.  This is NULL if the
 * hashmap is empty.  Otherwise, the length of the array is exactly the number
 * of pairs in the hashmap at the time of calling i.e. the value returned by
 * hm_size.
 */
char **hm_keys(const Hashmap *hm);

/**
 * @brief Utility function for freeing an array returned by hm_keys.
 *
 * @param keys Dynamically allocated array to free.
 * @param len Length of the array.  This is what would be returned by hm_size at
 * the time of calling hm_keys.
 */
void hm_free_keys_array(char **keys, size_t len);

#endif // HASHMAP_H_INCLUDED
