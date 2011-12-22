#include "linked.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

static const char *INPUT_FPATH = "input.txt";
#define OUTPUT_SEPARATOR "----"

typedef struct {
	char name[50];
	int stu_no;
	double gpa;
	char phone[20];
	char addr[80];
} rec_t;

static int input(linked_t **first, const char *fpath) {
	char buf[1024];
	rec_t *rec;

	FILE *fin = fopen(fpath, "r");

	while (fgets(buf, sizeof(buf), fin)) {
		rec = (rec_t*)malloc(sizeof(*rec));
		if (sscanf(buf, "%s %d %lf %s %[^\n]", rec->name, &rec->stu_no, &rec->gpa, rec->phone, rec->addr) != 5) {
			free(rec);
			continue;
		}

		linked_add(first, rec);
	}

	fclose(fin);

	return 0;
}

static void print_node(linked_t *node) {
	rec_t *rec = (rec_t*)node->data;
	printf("%d. %s: %.2f / %s / %s\n", rec->stu_no, rec->name, rec->gpa, rec->phone, rec->addr);
}

static void print_node_brief(linked_t *node) {
	rec_t *rec = (rec_t*)node->data;
	printf("%d. %s / ", rec->stu_no, rec->name);
}

static void print_linked(linked_t *node) {
	while (node) {
		print_node(node);
		node = node->next;
	}

	printf(OUTPUT_SEPARATOR "\n");
}

static void print_linked_brief(linked_t *node) {
	while (node) {
		print_node_brief(node);
		node = node->next;
	}
	putchar('\n');
}

static int name_cmp(const void *_a, const void *_b) {
	rec_t *a = (rec_t*)_a;
	rec_t *b = (rec_t*)_b;

	return strcmp(a->name, b->name);
}

static int stu_no_cmp(const void *_a, const void *_b) {
	rec_t *a = (rec_t*)_a;
	rec_t *b = (rec_t*)_b;

	return a->stu_no - b->stu_no;
}

bool print_between(linked_t *first, const char *name1, const char *name2) {
	linked_t *start, *end;

	if (!(start = linked_find(first, name1, name_cmp))) return true;
	if (!(end = linked_find(first, name2, name_cmp))) return true;

	linked_t *node = first;

	int pass = 0;
	while (node) {
		if (node == start || node == end) pass++;

		if (pass) {
			print_node(node);

			if (pass == 2 || start == end) break;
		}

		node = node->next;
	}

	printf(OUTPUT_SEPARATOR "\n");

	return false;
}

static void process(linked_t *first) {
	char name1[50], name2[50];

	printf("Enter the names of the two students: ");
	scanf("%s %s", name1, name2);

	if (print_between(first, name1, name2)) {
		fprintf(stderr, "Student not exists.\n");
	}

	printf("Before sorting: ");
	print_linked_brief(first);

	printf("Sorted by student number: ");
	linked_sort(&first, stu_no_cmp);
	print_linked_brief(first);

	printf("Sorted by name: ");
	linked_sort(&first, name_cmp);
	print_linked_brief(first);
}

static void finalize(linked_t *first) {
	linked_t *node = first;
	while (node) {
		free(node->data);
		node = node->next;
	}

	linked_delete(first);
}

int main(void) {
	linked_t *first = linked_create();

	if (input(&first, INPUT_FPATH)) goto err;

	print_linked(first);

	process(first);

	finalize(first);

	return 0;

err:
	finalize(first);
	return 1;
}
