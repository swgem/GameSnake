#ifndef TOOLS_H
#define TOOLS_H

//// EXTERNAL FUNCTION DECLARATION

void set_system_fatal_func(void (*system_fatal)());
void set_mem_alloc_func(void* (*mem_alloc)(int));
void set_generate_random_func(int (*generate_random)());

void system_fatal();
void* mem_alloc(int size);
int generate_random();

#endif
