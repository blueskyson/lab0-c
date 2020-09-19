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

void q_reverse(queue_t *q)
{
    if (!q || !(q->head))
        return;
    list_ele_t *prev, *curr, *next;
    prev = q->head;
    q->tail = q->head;
    curr = prev->next;
    while (curr) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    q->head = prev;
    q->tail->next = NULL;
}

void sort_recur(list_ele_t **headref)
{
    list_ele_t *head = *headref;
    if (head == NULL || head->next == NULL)
        return;

    /* find the middle node */
    list_ele_t *fast = head->next, *slow = head;
    while (fast != NULL) {
        fast = fast->next;
        if (fast != NULL) {
            fast = fast->next;
            slow = slow->next;
        }
    }

    /* partition */
    list_ele_t *right_head = slow->next;
    slow->next = NULL;
    sort_recur(&head);
    sort_recur(&right_head);
    list_ele_t *head_tmp;

    /* find out the smallest node in 2 partitions
     * and set it as the head of combined partition */
    if (strcmp(head->value, right_head->value) <= 0) {
        *headref = head;
        head = head->next;
    } else {
        *headref = right_head;
        right_head = right_head->next;
    }
    head_tmp = *headref;

    /* compare values in 2 partitions and
     * reorder them in combined partition */
    while (true) {
        if (head == NULL) {
            head_tmp->next = right_head;
            break;
        } else if (right_head == NULL) {
            head_tmp->next = head;
            break;
        }

        if (strcmp(head->value, right_head->value) <= 0) {
            head_tmp->next = head;
            head = head->next;
        } else {
            head_tmp->next = right_head;
            right_head = right_head->next;
        }
        head_tmp = head_tmp->next;
    }
}

void q_sort(queue_t *q)
{
    if (!q || q->size < 2)
        return;
    sort_recur(&(q->head));
}
