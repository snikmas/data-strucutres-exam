#include <stdio.h>
#include <stdlib.h>

#define MAX 100
#define INF 9999

typedef struct GMatrix {
  int edges;
  int vertices;
  int matrix[MAX][MAX];
} GMatrix;

// need to create
// 1. head nodes
// 2. nodes
// 3. arcnode



// edje! saves FROM where TO where and it's weight?
// if the 1st node -> saves to the head; otherwise, saves to the last node from the head node
typedef struct ArcNode{
  int from;
  int weight;
  // IT ALSO CAN BE DATA INT AND JUST FIND THE NUMBER IN THE ARRAY
  struct ArcNode *nextArc;
  int to;
} ArcNode;

// headNode - only one, saves is just a head node.
// saves it's name. is a linked list
typedef struct HeadNode {
  int data;
  ArcNode *next;
} HeadNode;

// the main datastructure! actually, just 线性 array, but
// just also have info about this array
typedef struct LGraph {
  int arcs, nodes;
  HeadNode *vertices[MAX];
} LGraph;



GMatrix* createMatrix(GMatrix *gMat){
  if(!gMat) {
    gMat = malloc(sizeof(GMatrix));
  }
  if(!gMat) return NULL;

  printf("Input the N edges:\n>> ");
  scanf("%i", &gMat->edges);
  printf("Input the N vertices:\n>> ");
  scanf("%i", &gMat->vertices);


  for(int i = 0; i < gMat->vertices; i++){
    for(int j = 0; j < gMat->vertices; j++){
      gMat->matrix[i][j] = INF;
    }
  }

  printf("Write [FROM TO WEIGHT] (like 1 2 23 <- from 1 to 2, the weight is 23):\n");
  int x, y, weight;
  for(int i = 0; i < gMat->edges; i++){
    scanf("%i %i %i", &x, &y, &weight);
    gMat->matrix[x - 1][y - 1] = weight;
  }

  printf("Created!\n");
  return gMat;
}

void printGMatrix(GMatrix *gMat){
  if(gMat == NULL) return;
  printf("     |");
  for(int i = 0; i < gMat->vertices; i++){
    printf("%4d", i + 1);
  }
  printf("\n");
  for(int i = 0; i < gMat->vertices; i++){
    printf("%4d |", i + 1);
    for(int j = 0; j < gMat->vertices; j++){
      if(gMat->matrix[i][j] != INF){
        printf("%4d", gMat->matrix[i][j]);
      } else {
        printf(" INF");
      }
    }
    printf("\n");
  }
  return;

}


// linked matrix
LGraph* createGraph(LGraph *lGraph){
  if(!lGraph){
    lGraph = malloc(sizeof(LGraph));
  }
  if(!lGraph) return NULL; // error

  // basic info
  printf("Input the N edges:\n>> ");
  scanf("%d", &lGraph->arcs);
  printf("Input the N vertices:\n>> ");
  scanf("%d", &lGraph->nodes);

  // all head pointers to NULL
  for(int i = 0; i < lGraph->nodes; i++){
    lGraph->vertices[i] = NULL; // is a 线性 list
  }

  printf("Write FROM TO WEIGHT (example: 1 2 12 -> from 1 to 2, the weight is 12)\n");
  for(int i = 0; i < lGraph->arcs; i++){
    printf(">> ");
    // should be.. a pointer?
    
    int weight, from, to;
    scanf("%i %i %i", &from, &to, &weight);
    from--; // cuz from 1 starts
    to--;
    
    
    // if the node FROM doesnt xist
    if(lGraph->vertices[to] == NULL){
      HeadNode *h = malloc(sizeof(HeadNode));
      if(!h){
        printf("ERROR DURING MALLOCING NEW NODE (HEADNODE)...");
        return NULL;
      }
      h->data = to;
      h->next = NULL;
      lGraph->vertices[to] = h;
    }
    
    
    if(lGraph->vertices[from] == NULL){ // YES I KNOW GPT, I ALSO CAN DO !LGRAPH... 
      HeadNode *h = malloc(sizeof(HeadNode));
      if(!h){
        printf("ERROR DURING NEWNODE MALLOC, RETURNING");
        return NULL;
      }
      h->data = from;
      h->next = NULL;
      lGraph->vertices[from] = h;
    }

    // JUST CREATED 2 NODES IN THE LIST, NEXT: CREATE EDGE
    ArcNode *arc = malloc(sizeof(ArcNode));
    arc->from = from;
    arc->to = to;
    arc->weight = weight;
    arc->nextArc = NULL;
    
    HeadNode *fromNode = lGraph->vertices[from];
    
    // APPEND ARC TO ADJAENCY LIST
    if(fromNode->next == NULL){
      // why si wrong? fromNode is headNode, ok, but it's next is arcnodef
      fromNode->next = arc;
    } else {
        ArcNode *cur = fromNode->next;
        while(cur->nextArc != NULL){
            cur = cur->nextArc;
        }
        cur->nextArc = arc;
    }
    
  }
  
  return lGraph;

}

void printLGraph(LGraph *lg){
    if(lg == NULL) return;

    printf("Amount of edges: %i\nAmount of nodes: %i\n", lg->arcs, lg->nodes);

    for(int i = 0; i < lg->nodes; i++){
        printf("Node #%d -> ", i + 1);

        if(lg->vertices[i] == NULL){
            printf("EMPTY\n\n");
            continue;
        }

        ArcNode *arc = lg->vertices[i]->next;

        while(arc != NULL){
            printf("[from %d to %d, weight %d] ", 
                    arc->from + 1, arc->to + 1, arc->weight);
            arc = arc->nextArc;
        }

        printf("\n\n");
    }
}




int main(void){


  int userOption;
  printf("1 - matrix; 2 - list\n>> ");
  scanf("%i", &userOption);
  if(userOption == 1){
    // 1. matrix graph
    GMatrix *gMat = NULL;
    gMat = createMatrix(gMat);
    printGMatrix(gMat);
  } else if(userOption == 2){ 
    // 2. matrix line
    LGraph *lGraph = NULL;
    lGraph = createGraph(lGraph);
    printLGraph(lGraph);
  }
  
  

  

  return 0;
}