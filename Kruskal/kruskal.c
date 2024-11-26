#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct TEdge {
	short int start;
	short int finish;
	int length;
	char vis;
} Edge;

int check(int ver, int edge) {
	if (ver < 0 || ver > 5000) {
		printf("bad number of vertices");
		return 0;
	}
	if (edge < 0 || edge > ver * (ver - 1) / 2) {
		printf("bad number of edges");
		return 0;
	}
	return 1;
}

int check_edge(int start, int finish, int length, int ver) {
	if (start < 1 || start > ver || finish < 1 || finish > ver) {
		printf("bad vertex");
		return 0;
	}
	if (length < 0 || length > INT_MAX) {
		printf("bad length");
		return 0;
	}
	return 1;
}

int create_edges(int ver, int edge, Edge* edges) {
	int start, finish, length;
	for (int i = 0; i < edge; i++) {
		if (scanf("%d %d %d", &start, &finish, &length) < 3) {
			printf("bad number of lines");
			return 0;
		}
		if (check_edge(start, finish, length, ver) == 0) {
			return 0;
		}
		edges[i].start = start - 1;
		edges[i].finish = finish - 1;
		edges[i].length = length;
		edges[i].vis = 0;
	}
	return 1;
}

int compare(const Edge* t1, const Edge* t2) {
	if (t1 -> length > t2 -> length) return 1;
	if (t1 -> length < t2 -> length) return -1;
	return 0;
}

int min_tree(int ver, int edge, Edge* edges) {
	if (ver == 0) {
		return 0;
	}
	qsort(edges, edge, sizeof(Edge), (int (*)(const void*, const void*)) compare);
	int* comp = malloc(sizeof(int) * ver);
	if (comp == NULL) {
		return 0;
	}
	for (int i = 0; i < ver; i++) {
		comp[i] = i;
	}
	for (int i = 0; i < edge; i++) {
		int comp_start = comp[edges[i].start];
		int comp_finish = comp[edges[i].finish];
		if (comp_start != comp_finish) {
			edges[i].vis = 1;
			for (int j = 0; j < ver; j++) {
				if (comp[j] == comp_start) {
					comp[j] = comp_finish;
				}
			}
		}
	}
	for (int i = 1; i < ver; i++) {
		if (comp[0] != comp[i]) {
			free(comp);
			return 0;
		}
	}
	free(comp);
	return 1;
}

void print(int edge, Edge* edges) {
	for (int i = 0; i < edge; i++) {
		if (edges[i].vis != 0) {
			printf("%d %d\n", edges[i].start + 1, edges[i].finish + 1);
		}
	}
}

void kruskal(int ver, int edge) {
	Edge* edges = malloc(sizeof(Edge) * edge);
	if (edges == NULL) {
		free(edges);
		return;
	}
	if (create_edges(ver, edge, edges) == 0) {
		free(edges);
		return;
	}
	if (min_tree(ver, edge, edges) != 0) {
		print(edge, edges);
	}
	else {
		printf("no spanning tree");
	}
	free(edges);
}

int main() {
	int ver, edge;
	if (scanf("%d %d", &ver, &edge) < 2) {
		printf("bad number of lines");
		return 0;
	}
	if (check(ver, edge) == 0) {
		return 0;
	}
	kruskal(ver, edge);
	return 0;
}