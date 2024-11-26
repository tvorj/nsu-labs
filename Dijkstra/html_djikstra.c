#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int check(int ver, int start, int finish, int edge) {
	if (ver < 0 || ver > 5000) {
		printf("bad number of vertices");
		return 0;
	}
	if (start < 1 || start > ver || finish < 0 || finish > ver) {
		printf("bad vertex");
		return 0;
	}
	if (edge < 0 || edge > ver * (ver - 1) / 2) {
		printf("bad number of edges");
		return 0;
	}
	return 1;
}

int* create_array(int count, int value) {
	int* arr = malloc(sizeof(int) * count);
	if (arr == NULL) {
		return NULL;
	}
	for (int i = 0; i < count; i++) {
		arr[i] = value;
	}
	return arr;
}

unsigned int* create_array_dis(int count, int value) {
	unsigned int* arr = malloc(sizeof(unsigned int) * count);
	if (arr == NULL) {
		return NULL;
	}
	for (int i = 0; i < count; i++) {
		arr[i] = value;
	}
	return arr;
}

int** create_matrix(int count) {
	int** matrix = malloc(sizeof(int*) * count);
	if (matrix == NULL) {
		return NULL;
	}
	for (int i = 0; i < count; i++) {
		matrix[i] = create_array(count, -1);
	}
	return matrix;
}

int** create_matrix_html(int count) {
	int** matrix = malloc(sizeof(int*) * count);
	if (matrix == NULL) {
		return NULL;
	}
	for (int i = 0; i < count; i++) {
		matrix[i] = create_array(count, 0);
	}
	return matrix;
}

int create_graph(int ver, int edge, int** graph) {
	int start, finish, length;
	for (int i = 0; i < edge; i++) {
		if (scanf("%d %d %d", &start, &finish, &length) < 3) {
			printf("bad number of lines");
			return 0;
		}
		if (start < 1 || start > ver || finish < 1 || finish > ver) {
			printf("bad vertex");
			return 0;
		}
		if (length < 0 || length > INT_MAX) {
			printf("bad length");
			return 0;
		}
		graph[start - 1][finish - 1] = length;
		graph[finish - 1][start - 1] = length;
	}
	return 1;
}

void min_path(int start, int ver, unsigned int* distance, int* path, int* path_count, int** graph) {
	distance[start - 1] = 0;
	path[start - 1] = start - 1;
	path_count[start - 1] = 1;
	int* vis = create_array(ver, 0);
	for (int i = 0; i < ver; i++) {
		int v = -1;
		for (int j = 0; j < ver; j++) {
			if (vis[j] == 0 && (v == -1 || distance[j] < distance[v])) {
				v = j;
			}
		}
		if (distance[v] == UINT_MAX) {
			free(vis);
			return;
		}
		for (int j = 0; j < ver; j++) {
			if (vis[j] == 0 && graph[v][j] != -1) {
				path_count[j] += path_count[v];
				unsigned int t = distance[v] + graph[v][j];
				if (t > INT_MAX) {
					t = (unsigned int)INT_MAX + 1;
				}
				if (t < distance[j]) {
					distance[j] = t;
					path[j] = v;
				}
			}
		}
		vis[v] = 1;
	}
	free(vis);
}

void print(int finish, int ver, int* path, unsigned int* distance, int* path_count) {
	for (int i = 0; i < ver; i++) {
		if (distance[i] == UINT_MAX) {
			printf("oo ");
		}
		else if (distance[i] > INT_MAX) {
			printf("INT_MAX+ ");
		}
		else {
			printf("%u ", distance[i]);
		}
	}
	printf("\n"); //distance
	if (path[finish - 1] == -1) {
		printf("no path");
		return;
	}
	if (distance[finish - 1] > INT_MAX && path_count[finish - 1] > 1) {
		printf("overflow");
		return;
	}
	//check
	int vert = finish - 1;
	printf("%d ", finish);
	while (path[vert] != vert) {
		vert = path[vert];
		printf("%d ", vert + 1);
	}
	//vert
}

void dijkstra(int ver, int start, int finish, int edge) {
	int** graph = create_matrix(ver);
	if (create_graph(ver, edge, graph) == 0) {
		for (int i = 0; i < ver; i++) {
			free(graph[i]);
		}
		free(graph);
		return;
	}
	unsigned int* distance = create_array_dis(ver, -1);
	int* path = create_array(ver, -1);
	int* path_count = create_array(ver, 0);
	min_path(start, ver, distance, path, path_count, graph);
	print(finish, ver, path, distance, path_count);
	free(path_count);
	free(distance);
	free(path);
	for (int i = 0; i < ver; i++) {
		free(graph[i]);
	}
	free(graph);
}

void html(int ver, int edge) {
	int** graph = create_matrix_html(ver);
	int f, s, l;
	for (int i = 0; i < edge; i++) {
		if (scanf("%d %d %d", &s, &f, &l) < 3) {
			printf("bad number of lines");
			return;
		}
		if (s < 1 || s > ver || f < 1 || f > ver) {
			printf("bad vertex");
			return;
		}
		graph[s - 1][f - 1] = 1;
		graph[f - 1][s - 1] = 1;
	}

	/*FILE* ptrFile = fopen("graph.html", "w");*/

	printf("<HTML>\n ");
	printf("<HEAD> <TITLE> Dijkstra algorithm </TITLE> </HEAD>\n");
	printf("<BODY> \n");
	printf("<p>Dijkstra</p>\n");
	printf("<table border=\"1\" width=\"100\" cellpadding=\"5\">\n");
	printf("<tr>\n");
	for (int i = 0; i < ver + 1; i++) {
		if (i == 0) {
			printf("<th>GRAPH</th>\n");
		}
		else {
			printf("<th>%d</th>\n", i);
		}
	}
	printf("</tr>\n");
	for (int i = 0; i < ver; i++) {
		printf("<tr>\n");
		for (int j = 0; j < ver + 1; j++) {
			if (j == 0) {
				printf("<td>%d</td>\n", i + 1);
			}
			else {
				printf("<td>%d</td>\n", graph[i][j - 1]);
			}
		}
		printf("</tr>\n");
	}
	printf("</table>");
	printf("</BODY>\n");
	printf("</HTML>");
	/*fclose(ptrFile);*/
	for (int i = 0; i < ver; i++) {
		free(graph[i]);
	}
	free(graph);
}

int main(int argc, char* argv[]) {
	int key = 0;
	if (argc > 1) {
		if (argv[1][0] == '-' && argv[1][1] == 'p') {
			key = 1;
		}
	}
	int ver, start, finish, edge;
	if (scanf("%d %d %d %d", &ver, &start, &finish, &edge) < 4) {
		printf("bad number of lines");
		return 0;
	}
	if (check(ver, start, finish, edge) == 0) {
		return 0;
	}
	if (key == 1) {
		html(ver,edge);
	}
	else {
		dijkstra(ver, start, finish, edge);
	}
	return 0;
}
