#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
 * Create empty queue.
 * Return NULL if could not allocate space.
 */
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    /* TODO: What if malloc returned NULL? */
    if (q != NULL) {
        q->head = NULL;
        q->tail = NULL;
        q->size = 0;
    }
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    /* TODO: How about freeing the list elements and the strings? */
    /* Free queue structure */
    if (!q)
        return;

    list_ele_t *ele = q->head;
    while (ele) {
        list_ele_t *tmp;  // store the element address being freed
        free(ele->value);
        tmp = ele;
        ele = ele->next;
        free(tmp);
    }

    free(q);
}

/*
 * Attempt to insert element at head of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    if (!q)
        return false;

    list_ele_t *newh;
    newh = malloc(sizeof(list_ele_t));
    /* TODO: What should you do if the q is NULL? */
    if (newh == NULL)
        return false;

    /* Don't forget to allocate space for the string and copy it */
    /* What if either call to malloc retiurns NULL? */
    newh->value = malloc(sizeof(char) * (strlen(s) + 1));
    if (newh->value == NULL) {
        free(newh);
        return false;
    }
    int len = strlen(s);
    strncpy(newh->value, s, len + 1);
    newh->next = q->head;
    if (!q->head && !q->tail)
        q->tail = newh;  // empty list
    q->head = newh;
    q->size++;
    return true;
}

/*
 * Attempt to insert element at tail of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    /* TODO: You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */
    /* TODO: Remove the above comment when you are about to implement. */
    if (!q)
        return false;

    list_ele_t *newt;
    newt = malloc(sizeof(list_ele_t));

    if (newt == NULL)
        return false;
    newt->value = malloc(sizeof(char) * (strlen(s) + 1));
    if (newt->value == NULL) {
        free(newt);
        return false;
    }
    int len = strlen(s);
    strncpy(newt->value, s, len + 1);
    newt->next = NULL;
    if (!q->head && !q->tail)
        q->head = newt;
    else
        q->tail->next = newt;
    q->tail = newt;
    q->size++;
    return true;
}

/*
 * Attempt to remove element from head of queue.
 * Return true if successful.
 * Return false if queue is NULL or empty.
 * If sp is non-NULL and an element is removed, copy the removed string to *sp
 * (up to a maximum of bufsize-1 characters, plus a null terminator.)
 * The space used by the list element and the string should be freed.
 */
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    /* TODO: You need to fix up this code. */
    /* TODO: Remove the above comment when you are about to implement. */
    if (!q || q->head == NULL)
        return false;

    if (sp != NULL) {
        strncpy(sp, q->head->value, bufsize - 1);
        sp[bufsize - 1] = '\0';
    }
    list_ele_t *tmp;
    tmp = q->head;
    free(q->head->value);
    q->head = q->head->next;
    if (tmp == q->tail)
        q->tail = NULL;
    free(tmp);
    q->size--;
    return true;
}

/*
 * Return number of elements in queue.
 * Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    /* TODO: You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    /* TODO: Remove the above comment when you are about to implement. */
    return (!q || q->head == NULL) ? 0 : q->size;
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
    if (!q || q->size == 0 || q->size == 1)
        return;

    list_ele_t *prev, *curnt;
    prev = NULL;
    curnt = q->head;
    while (curnt != NULL) {
        list_ele_t *tmp = curnt->next;
        curnt->next = prev;
        prev = curnt;
        curnt = tmp;
    }
    q->tail = q->head;
    q->head = prev;
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
    if (!q || q->size == 0 || q->size == 1)
        return;
    printf("head:%s, tail:%s\n", q->head->value, q->tail->value);
    // Bubble Sort
    list_ele_t *curnt, *prev, *ctail, *tmp;
    for (ctail = q->tail->next; ctail != q->head->next;) {
        for (curnt = q->head, prev = NULL; curnt->next != ctail;
             prev = curnt, curnt = curnt->next) {
            if (strcmp(curnt->next->value, curnt->value) < 0) {
                tmp = curnt->next;
                curnt->next = tmp->next;
                tmp->next = curnt;
                curnt = tmp;
                if (prev == NULL) {
                    q->head = tmp;
                } else {
                    prev->next = curnt;
                }
            }
        }
        if (curnt->next == NULL)
            q->tail = curnt;
        ctail = curnt;
    }
}
