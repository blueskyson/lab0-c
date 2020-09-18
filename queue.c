#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    if (!q)
        return NULL;
    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    if (!q)
        return;
    while (q->head) {
        list_ele_t *del = q->head;
        q->head = q->head->next;
        free(del->value);
        free(del);
    }
    free(q);
}

bool q_insert_head(queue_t *q, char *s)
{
    if (!q)
        return false;
    list_ele_t *newh = malloc(sizeof(list_ele_t));
    if (!newh)
        return false;
    unsigned len = strlen(s) + 1;
    char *val = malloc(sizeof(char) * len);
    if (!val) {
        free(newh);
        return false;
    }
    memcpy(val, s, len);
    newh->value = val;
    newh->next = q->head;
    q->head = newh;
    if (q->size == 0)
        q->tail = newh;
    (q->size)++;
    return true;
}

bool q_insert_tail(queue_t *q, char *s)
{
    if (q == NULL)
        return false;
    list_ele_t *newt = malloc(sizeof(list_ele_t));
    if (!newt)
        return false;
    unsigned len = strlen(s) + 1;
    char *val = malloc(sizeof(char) * len);
    if (!val) {
        free(newt);
        return false;
    }
    memcpy(val, s, len);
    newt->value = val;
    newt->next = NULL;
    if (q->size == 0) {
        q->head = newt;
        q->tail = newt;
    } else {
        q->tail->next = newt;
        q->tail = newt;
    }
    (q->size)++;
    return true;
}

bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    if (!q || !(q->head))
        return false;
    if (q->size == 1)
        q->tail = NULL;
    list_ele_t *del;
    del = q->head;
    q->head = q->head->next;

    if (sp) {
        if (strlen(del->value) > bufsize) {
            memcpy(sp, del->value, bufsize);
            sp[bufsize - 1] = '\0';
        } else {
            memcpy(sp, del->value, sizeof(char) * (strlen(del->value) + 1));
        }
    }
    free(del->value);
    free(del);
    (q->size)--;
    return true;
}

int q_size(queue_t *q)
{
    if (!q)
        return 0;
    return q->size;
}

/*
 * Reverse elements in queue
 * No effect if q is NULL or empty
 * This function should not allocate or free any list elements
 * (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
 * It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    /* TODO: You need to write the code for this function */
    /* TODO: Remove the above comment when you are about to implement. */
}

/*
 * Sort elements of queue in ascending order
 * No effect if q is NULL or empty. In addition, if q has only one
 * element, do nothing.
 */
void q_sort(queue_t *q)
{
    /* TODO: You need to write the code for this function */
    /* TODO: Remove the above comment when you are about to implement. */
}
