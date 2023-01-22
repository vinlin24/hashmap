# C Hashmap Learning Exercise


## Motivation


A **hashmap** is an essential data structure that all programmers must be familiar with. As a Python main, I often take for granted that all I have to do is use the literal syntax `{}` and boom I have a hashmap. C is a notoriously difficult programming language to learn, and quite interestingly, it doesn't even have a hashmap structure built into the language nor is one provided by the standard library.

Because I will need to use C extensively in my low-level programming classes like CS 111 anyway, I figured I could make this a valuable learning exercise to make myself more comfortable with the language as well as refresh some knowledge about basic data structures and algorithms. This code may also be useful to have in my back pocket if I ever need to implement my own hashmap again for future C projects.

Also, I've been having a massive headache for the past 2 days, and I cannot be bothered to do the many readings and lecture recordings I *should* be catching up on right now. ~~This makes me feel like I'm still being productive.~~


## Description


I decided to go with a simple **chaining** hashmap that maps C-strings (`char const *`) to `int`s. My implementation is fairly standard, using an pre-sized array of linked lists representing the **buckets** of the hashmap.

* [hashmap.c](hashmap.c) contains:
  * Definitions for the basic interface functions `hm_init`, `hm_get`, `hm_put`, `hm_remove`, and `hm_size`.
  * Definitions for the utility interface functions `hm_print`, `hm_print_lists`, `hm_keys`, and `hm_free_keys_array`.
  * A helper type `HashmapIterator` that I use to iterate through `Hashmap`s.
  * Prototypes and definitions for private helper functions, such as the hashing function and `HashmapIterator` functions.

* [hashmap.h](hashmap.h) contains:
  * Macro constants relevant to the program.
  * The definition of my `Hashmap` type.
  * Prototypes for interface functions.

* [main.c](main.c) is simply a sanity test script that performs some basic operations on a `Hashmap` instance.

All of my code is original, only occasionally referring to ChatGPT for assistance on various C syntax/best practices. The only exception is my hashing function `hash()` in `hashmap.c`, which uses a DJB2 string hashing algorithm taken straight from ChatGPT's output. I think this is fine because while hashing functions are definitely an important programming concept, they are not the focus of this exercise.


## Building & Running


To compile my source files, simply run:

```bash
make
```

To run the compiled executable (which is just test code), run:

```bash
./main
```

**Disclaimer:** I do not claim my implementation to be entirely correct, nor does my `main.c` include exhaustive test cases. I have not fully tested my implementation. It's past 5:30 AM right now, and I really want to lie down. You should probably use Google, StackOverflow, and/or ChatGPT if you are entrusted with implementing your own hashmap in C.


## What I Learned


I think I'm significantly more confident with C programming having done this. Some things I learned or reinforced include:

* The C Programming Language
  * Using `#define` for function macros.
  * Managing `#include` dependencies and forward declarations.
  * Refresher on using `malloc()` and `free()` for dealing with dynamically allocated data.
  * Using `typedef`s with `struct`s, as well as self-referencing `struct`s such as the `ListNode`, which needs to hold a pointer to another `ListNode` instance.
  * Better intuition and muscle memory for dealing with pointers.
  * A better sense of when to use the `static` keyword, namely when a symbol should be "private" to a source file.
  * Some practice with common standard library functions and macros like `snprintf()`, `strcmp()`, `strlen()`, `strcpy()`, `size_t`, `bool`, etc.
  * Some basic optimizing techniques, like using the `inline` keyword to inline small function bodies.

* Data Structures and Algorithms
  * Refresher on how a hashmap is implemented, specifically a chaining hashmap.
  * Application of basic linked list algorithms like traversal, node removal with the two pointer technique, etc.
  * Defining and using an iterator type as a state manager for iterating through a nonlinear data structure such as a hashmap.
  * Remembering when and how to handle for the case of something being `NULL`.

* Programming Paradigms and Best Practices
  * Getting used to not having direct access to object-oriented mechanisms.
  * Writing functions that mimic the underlying behavior of object-oriented mechanisms, like passing the reference to the object to operate on as the first argument.
  * Encapsulating getter/setter behavior with functions, even if they are a simple read/write on a `struct` field or a pointer dereference. This makes code more future-proof and maintainable with a consistent interface.
  * Having a good separation of **interface** and **implementation**. In `hashmap.h`, I define a `Hashmap` interface I want to expose including only functions intended for the end-user. All helper functions and types that users of a `Hashmap` need not worry about are defined only in `hashmap.c`.
  * Writing good documentation. For example, if data is dynamically allocated and requires the caller to `free()` it later, that should be well noted in the relevant type or function documentation comments.
  * Some practice on writing a good `Makefile` for better development flow. Notably, I learned some useful Makefile mechanisms like the `$(wildcard)` function, the `%.c` syntax for pattern-matching, and the `$(SOURCES:.c=.o)` trick for declaring a list of object files from their corresponding source file names. I also had a refresher on special Makefile variables like `$@` and `$^`.

* Debugging
  * Some practice with using GDB for low-level debugging, including using **watchpoints** and the `condition` function to execute code until a variable holds a certain value.
  * One bug I was stuck on for some time was where inserting keys into the hashmap would modify existing keys. It turns out the issue was in the test code and not the hashmap. I was passing a pointer to the same `char buffer[20]` when repeatedly inserting into the map, causing a change in `buffer` to take effect on all keys that were inserted with that same `buffer`. This reminds me that it's always important to consider other code that uses the function being debugged, not just the function itself.
  * Tracing code across multiple functions. This is especially important when multiple functions modify the state of some same data structure, potentially making a correctly implemented function appear incorrect because another faulty function(s) fails to achieve a necessary precondition.
