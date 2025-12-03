#include <stdio.h>
#include <stdlib.h>

// listed graphs
#define MAX_SIZE 100
// by what save graphs

// but in this case, there're no name for vertex?;

// OK GIT IT
typedef struct Node {
  // with link
  struct Node *headNode;
  struct Node *tailNode;

  // withoutLink;
  struct Node *prevVertex;
  struct Node *nextVertex;
  char name;
} Node;

Node *head = NULL;
Node *tail = NULL;
// create array of pointers

Node *getNode(int name){
  Node *new = (Node*)malloc(sizeof(Node));
  new->name = name;

  new->nextVertex = NULL;
  new->prevVertex = NULL;

  new->headNode = NULL;
  new->tailNode = NULL;
  return new;
}


// if prev/next vertex -> add to the last vertex

void insert(char name, char linkedVertex){

  Node *newNode = getNode(name);
  if(head == NULL){
    head = newNode;
    tail = newNode;
    return;
  }
  
  // 1. if a totally new node; WE SHOULD DO IT FOR ALL NODES
  // add to the tail
  tail->nextVertex = newNode;
  tail = newNode;
  if(linkedVertex != '\0'){
    // we have only one vertex to connnect;
    if(head == NULL) return;
    Node *cur = head;
    while(cur != NULL && cur->name != linkedVertex){
      cur = cur->nextVertex; // find vertically
    }
    // got cur
    if (cur == NULL) return;
    // get horizontally
    while(cur->nextVertex != NULL){
      cur = cur->nextVertex;
    }
    cur->nextVertex = newNode;
    newNode->prevVertex = cur;
  }
}

void traverse(){

  if(head == NULL){
    printf("Head is null\n");
  } else {
    Node *cur = head;
    while (cur != NULL){
      printf("Current node: %c\n", cur->name);

      Node *connnectNodes = cur->;
      while(c)

    }

  }

}


int main(void){

  insert('a', '\0');
  
  insert('t', '\0');
  insert('a', 'a');

  traverse();
  return 0;

}
