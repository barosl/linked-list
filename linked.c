#include "linked.h"
#include <stdio.h>
#include <stdlib.h>

linked_t *linked_create() {
	return NULL;
}

void linked_add(linked_t **first, void *data) {
	linked_t *node = (linked_t*)malloc(sizeof(*node));
	node->data = data;
	node->next = NULL;

	if (!*first) *first = node;
	else {
		linked_t *last = *first;
		while (last->next) last = last->next;

		last->next = node;
	}
}

void linked_delete(linked_t *first) {
	linked_t *node = first;
	while (node) {
		linked_t *next = node->next;
		free(node);
		node = next;
	}
}

linked_t *linked_find(linked_t *first, const void *data, int (*cmp)(const void *a, const void *b)) {
	linked_t *node = first;
	while (node) {
		if (!cmp(node->data, data)) return node;
		node = node->next;
	}
	return NULL;
}

int linked_len(linked_t *first) {
	int cnt = 0;
	linked_t *node = first;
	while (node) {
		cnt++;
		node = node->next;
	}
	return cnt;
}

void linked_sort(linked_t **first, int (*cmp)(const void *a, const void *b)) {
	int i;
	int cnt = linked_len(*first);
	while (cnt) {
		cnt--;

		linked_t *prev_prev_node = NULL;
		linked_t *prev_node = *first;
		linked_t *node = prev_node->next;

		for (i=0;i<cnt;i++) {
			if (cmp(prev_node->data, node->data) > 0) {
				if (prev_prev_node) prev_prev_node->next = node;
				else *first = node;

				prev_node->next = node->next;
				node->next = prev_node;

				linked_t *tmp = prev_node;
				prev_node = node;
				node = tmp;
			}

			prev_prev_node = prev_node;
			prev_node = node;
			node = node->next;
		}
	}
}
