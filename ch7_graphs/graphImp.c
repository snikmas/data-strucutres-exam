#include <stdio.h>
#include <stdlib.h>

#define MAX_V 100
#define INF 9999

// FOR MATRIX
typedef struct {
  int nodes;
  int e;
  int edges[MAX_V][MAX_V]; 
} MGraph;

// FOR LIST
// edge node
typedef struct ArcNode {
  int adjvex;
  int weight;
  struct ArcNode *next; 
} ArcNode;

// head node (one per vertex)
typedef struct VNode {
  int data; // Vertex infromation, index/name
  ArcNode *first;
} VNode, AdjList[MAX_V];

// graph structure
typedef struct {
  AdjList vertices;  // array of head ndoes
  int nodes, arcs;
} ALGraph;

// create dirrected graph - adjaency list
void createALGraph(ALGraph *G){
  int i, from, to, w;
  ArcNode *p;

  printf("Enter number of vertices: ");
  scanf("%d", &G->nodes);
  printf("Enter number of arcs: ");
  scanf("%d", &G->arcs);

  // all head pointers to NULL
  for(i = 0; i < G->nodes; i++){
    G->vertices[i].data = i;
    G->vertices[i].first = NULL;
  }

  printf("Enter %d arcs (from to weight):\n", G->arcs);
  for(i = 0; i < G->arcs; i++){
    scanf("%d%d%d", &from, &to, &w);
    // head insertion
    p = (ArcNode*)malloc(sizeof(ArcNode));
    p->adjvex = to;
    p->weight = w;
    p->next = G->vertices[from].first;
    G->vertices[from].first = p;
    
    // if undirected graph, add the reverse edge too:
    // p = ArcNode* malloc sizeof arcnode;
    // p->adjvex = from;
    // p->weight = w;
    // p->next = g->vertices[to].first;
    //g->vertices[to].first = p
  }
}

// printf adjacency list
void printALGraph(ALGraph *G){
  int i;
   ArcNode *p;

   printf("\nAdjacency List:\n");
   for(i = 0; i < G->nodes; i++){
    printf("%d -> ", i);
    p = G->vertices[i].first;
    while(p) {
      printf("%d(w:%d) ", p->adjvex, p->weight);
      p = p->next;
    }
    printf("NULL\n");
   }
   printf("\n");
}


// MATRIX FUNCTIONS
void createMGraph(MGraph *G){
  int i, j, k, weight;
  printf("Input the number of the vertex: ");
  scanf("%d", &G->nodes);
  printf("Input the number of the edges: ");
  scanf("%d", &G->e);

  // put the inifinity inside; initialize
  for(i = 0; i < G->nodes; i++){
    for(j = 0; j < G->nodes; j++){
      G->edges[i][j] = INF;
    }
  }

  // input data
  printf("Input %d arc (from to weight): \n", G->e);
  for(k = 0; k < G->e; k++){
    scanf("%d %d %d", &i, &j, &weight);
    G->edges[i - 1][j - 1] = weight; // directed -> only fill i and j;
    // undirected: also add G->edges[j][i] = weight
  }
}

void printMGraph(MGraph G){
  int i, j;
  printf("\nAdjacency Matrix:\n");
  printf("  ");
  for(j = 0; j < G.nodes; j++) printf("%6d", j);
  printf("\n");

  for(i = 0; i < G.nodes; i++){
    printf("%4d | ", i);
    for(j = 0; j < G.nodes; j++){
      if(G.edges[i][j] == INF){
        printf(" INF ");
      } else printf("%6d", G.edges[i][j]);
    }
    printf("\n");
  }
  printf("\n");
}

// for directed graphs
void degree(MGraph *G, int v){
  int in_degree = 0, out_degree = 0;

  // out degree: count non-inf entries in ROW V
  for(int j = 0; j < G->nodes; j++){
    if(G->edges[v][j] != INF) out_degree++;
  }
  for(int i = 0; i < G->nodes; i++){
    if(G->edges[i][v] != INF) in_degree++;
  }
  printf("Vertex %d:\nOD = %d\nID = %d", v, out_degree, in_degree);

}


int main(){

  // adjency matrix
  printf("Adjaecency matrix - 1\nAdjaecency list - 2\n>> ");
  int n;
  scanf("%d", &n);
  if(n == 1){
    MGraph G;
    createMGraph(&G);
    printMGraph(G);
    degree(&G, 0);
  } else if(n == 2){
    ALGraph G;
    createALGraph(&G);
    printALGraph(&G); // do not copy all matrix

  }
  return 0;
}