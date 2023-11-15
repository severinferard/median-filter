#include "median-filter.h"

void median_filter_init(struct s_median_filter *mf)
{
    for (uint32_t i = 0; i < mf->size; i++)
    {
        mf->nodes[i].value = 0;
        mf->nodes[i].next = &mf->nodes[(i + 1) % mf->size];
        mf->nodes[i].next_oldest = &mf->nodes[(i + 1) % mf->size];
        mf->nodes[(i + 1) % mf->size].prev = &mf->nodes[i];
    }
    mf->min_head = &mf->nodes[0];
    mf->age_head = &mf->nodes[0];
    mf->median_head = &mf->nodes[mf->size / 2];
    mf->is_full = false;
}

float median_filter_push(struct s_median_filter *mf, float value)
{
    struct s_median_filter_node *new_node;
    struct s_median_filter_node *it;
    uint32_t i;

    // If the oldest node (which will be replaced) is also the smallest (and thus min_head), move min_head forward to not lose it.
    if (mf->age_head == mf->min_head)
        mf->min_head = mf->min_head->next;

    // If the oldest node is the last one in the buffer, we (are about to) have filled the whole list.
    if (!mf->is_full)
        mf->is_full = mf->age_head == &(mf->nodes[mf->size - 1]);

    if ((mf->age_head == mf->median_head) || (mf->age_head->value > mf->median_head->value))
        mf->median_head = mf->median_head->prev;

    // Store value in new node
    new_node = mf->age_head;
    new_node->value = value;

    // Remove new node from the list
    mf->age_head->prev->next = mf->age_head->next;
    mf->age_head->next->prev = new_node->prev;

    // Move age_head forward;
    mf->age_head = mf->age_head->next_oldest;

    // Place the new node at the right place
    it = mf->min_head;
    for (i = 0; i < mf->size - 1; i++)
    {
        if (value < it->value)
        {
            // If the new node is the smallest, set it to the min_head
            if (i == 0)
                mf->min_head = new_node;
            break;
        }
        it = it->next;
    }
    it->prev->next = new_node;
    new_node->prev = it->prev;
    it->prev = new_node;
    new_node->next = it;

    if (i >= mf->size / 2)
        mf->median_head = mf->median_head->next;

    return mf->median_head->value;
}

float median_filter_read(struct s_median_filter *mf)
{
    return mf->median_head->value;
}

bool median_filter_fifo_full(struct s_median_filter *mf)
{
    return mf->is_full;
}

void median_filter_print(struct s_median_filter *mf)
{
    struct s_median_filter_node *ptr;

    printf("[");
    ptr = mf->min_head;
    for (uint32_t i = 0; i < mf->size; i++)
    {
        printf("%f, ", ptr->value);
        ptr = ptr->next;
    }
    printf("]\n");
}
