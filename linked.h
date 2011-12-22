#pragma once

typedef struct _linked_t {
	void *data;
	struct _linked_t *next;
} linked_t;

extern linked_t *linked_create(void);
extern void linked_add(linked_t **first, void *data);
extern void linked_delete(linked_t *first);
extern linked_t *linked_find(linked_t *first, const void *data, int (*cmp)(const void *a, const void *b));
extern void linked_sort(linked_t **first, int (*cmp)(const void *a, const void *b));
