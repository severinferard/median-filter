#include <stdio.h>
#include <stdint.h>
#include "median-filter.h"

MEDIAN_FILTER_CREATE(mf, 6);

int main()
{
    median_filter_init(&mf);
    median_filter_push(&mf, 2);
    median_filter_print(&mf);
    printf("%f\n", median_filter_read(&mf));
    median_filter_push(&mf, 4);
    median_filter_print(&mf);
    printf("%f\n", median_filter_read(&mf));
    median_filter_push(&mf, 5);
    median_filter_print(&mf);
    printf("%f\n", median_filter_read(&mf));
    median_filter_push(&mf, 3);
    median_filter_print(&mf);
    printf("%f\n", median_filter_read(&mf));
    median_filter_push(&mf, 6);
    median_filter_print(&mf);
    printf("%f\n", median_filter_read(&mf));
    median_filter_push(&mf, 7);
    median_filter_print(&mf);
    printf("%f\n", median_filter_read(&mf));
    median_filter_push(&mf, 0);
    median_filter_print(&mf);
    printf("%f\n", median_filter_read(&mf));
    median_filter_push(&mf, 1);
    median_filter_print(&mf);
    printf("%f\n", median_filter_read(&mf));
    return 0;
}