#ifndef MEDIAN_FILTER_H
#define MEDIAN_FILTER_H
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C"
{
#endif

    struct s_median_filter_node
    {
        struct s_median_filter_node *next;
        struct s_median_filter_node *next_oldest;
        struct s_median_filter_node *prev;
        float value;
    };

    typedef struct s_median_filter
    {
        uint32_t size;
        struct s_median_filter_node *nodes;
        struct s_median_filter_node *min_head;
        struct s_median_filter_node *age_head;
        struct s_median_filter_node *median_head;
        bool is_full;
    } t_median_filter;

#define MEDIAN_FILTER_CREATE(name, filter_size) \
    struct s_median_filter name = {             \
        .size = filter_size,                    \
        .nodes = (struct s_median_filter_node[filter_size]){}}

    void median_filter_init(struct s_median_filter *mf);
    float median_filter_push(struct s_median_filter *mf, float value);
    float median_filter_read(struct s_median_filter *mf);
    bool median_filter_fifo_full(struct s_median_filter *mf);

    void median_filter_print(struct s_median_filter *mf);

#ifdef __cplusplus
}
#endif

#endif