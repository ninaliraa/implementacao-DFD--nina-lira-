#include "dfs.h"
#include <stdlib.h>

static void resetarDFS(DFS *dfs) {
    for (int v = 0; v < MAX_VERTICES; v++) {
        dfs->cor[v] = BRANCO;
        dfs->ante[v] = -1;
        dfs->i[v] = 0;
        dfs->f[v] = 0;
    }
    dfs->tempo = 0;
}

DFS *inicializarDFS() {
    DFS *dfs = (DFS *) malloc(sizeof(DFS));

    if (dfs == NULL) {
        return NULL;
    }

    resetarDFS(dfs);
    return dfs;
}

void destruirDFS(DFS *dfs) {
    free(dfs);
}


void dfs_start_matriz(DFS *dfs, Grafo *g, int s) {
    if (dfs == NULL || g == NULL || s < 0 || s >= MAX_VERTICES) {
        return;
    }

    resetarDFS(dfs);
    dfs_visit_matriz(dfs, s, g);
}

void dfs_visit_matriz(DFS *dfs, int u, Grafo *g) {
    if (dfs == NULL || g == NULL || u < 0 || u >= MAX_VERTICES) {
        return;
    }

    dfs->cor[u] = CINZA;
    dfs->tempo++;
    dfs->i[u] = dfs->tempo;

    for (int v = 0; v < MAX_VERTICES; v++) {
        if (existeAresta(g, u, v) && dfs->cor[v] == BRANCO) {
            dfs->ante[v] = u;
            dfs_visit_matriz(dfs, v, g);
        }
    }

    dfs->cor[u] = PRETO;
    dfs->tempo++;
    dfs->f[u] = dfs->tempo;
}


void dfs_start_lista(DFS *dfs, Grafo *g, int s) {
    if (dfs == NULL || g == NULL || s < 0 || s >= MAX_VERTICES) {
        return;
    }

    resetarDFS(dfs);
    dfs_visit_lista(dfs, s, g);
}

void dfs_visit_lista(DFS *dfs, int u, Grafo *g) {
    if (dfs == NULL || g == NULL || u < 0 || u >= MAX_VERTICES) {
        return;
    }

    dfs->cor[u] = CINZA;
    dfs->tempo++;
    dfs->i[u] = dfs->tempo;

    for (No *p = g->listaAdj[u]; p != NULL; p = p->proximo) {
        int v = p->vertice;

        if (dfs->cor[v] == BRANCO) {
            dfs->ante[v] = u;
            dfs_visit_lista(dfs, v, g);
        }
    }

    dfs->cor[u] = PRETO;
    dfs->tempo++;
    dfs->f[u] = dfs->tempo;
}
