#include "yaya_logger_private.h"

void logger_memory_new(___logger *lvg, void **ptr, void *old_ptr, size_t new_size)
{
    if(old_ptr == NULL){
        *ptr = malloc(new_size);
        memset(*ptr, 0, new_size);

        if(lvg != NULL){
            lvg->memory_total += new_size;
            lvg->memory_usage += new_size;
            lvg->memory_count_new++;
        }
    }else{
        size_t old_sise = malloc_usable_size(old_ptr);
        size_t diff = new_size - old_sise;

        lvg->memory_count_res++;

        if(diff == 0){
            return;
        }
        if(diff < 0){
            *ptr = realloc(old_ptr, new_size);
            lvg->memory_usage -= diff;
        }
        if(diff > 0){
            *ptr = realloc(old_ptr, new_size);
            memset(&(*ptr)[old_sise], 0, diff);
            lvg->memory_usage += diff;
        }

        lvg->memory_total += diff;
    }
}

void logger_memory_del(___logger *lvg, void *ptr)
{
    if(ptr != NULL){
        lvg->memory_usage -= malloc_usable_size(ptr);
        lvg->memory_count_del++;
        free(ptr);
        ptr = NULL;
    }
}
