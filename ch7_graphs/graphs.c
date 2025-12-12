#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct Graph{
  int numNodes;
  bool **edges;
} Graph;


void destroy_graph(Graph *g){
  if(!g== NULL){
    return;
  }
  if(g->edges){

    for(int i = 0; i < g->numNodes; i++){
        free(g->edges[i]);
    }
    free(g->edges);
  }
  free(g);
}

void print(Graph *g){
  printf("digraph {\n}");
  for(int i = 0; i < g->numNodes; i++){
    for(int j = 0; j < g->numNodes; j++){
      if(g->edges[i][j]){
        print("%d -> %d\n", i, j);
      }
    }
  }
  printf("}\n");
}

Graph *createGraph(int numNodes){
  Graph *g = malloc(sizeof(Graph));
  if(!g) return NULL;

  g->numNodes = numNodes;

  // allocate our matrix;
  g->edges= calloc(numNodes, sizeof(bool *));
  if(!g->edges){
    free(g);
    return NULL;
  }

  for(int i = 0; i < numNodes; i++){
    g->edges[i] = calloc(numNodes, sizeof(bool));
    if(!g->edges[i]){
      destroy_graph(g);
      return NULL;
    }
  }
  return g;

}

int main(void){



  return 0;
}