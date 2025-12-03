#include <stdio.h>
#include <stdlib.h>

// listed graphs
#define MAX_SIZE 100
// by what save graphs

// but in this case, there're no name for vertex?;

struct Node {
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
  Node *new = (Node*)malloc(sizeof(node));
  new->name = name;
  new->nextVertex = NULL;
  new->headNode = NULL;
  new->tailNode = NULL;
  new->prevVertex = NULL;
  return new;
}


// if prev/next vertex -> add to the last vertex

void insert(char name, Node *linkedVertex){

  Node *newNode = getNode(weight);
  if(head == NULL){
    head = newNode;
    tail = newNode;
    return;
  }
  
  // 1. if a totally new node; WE SHOULD DO IT FOR ALL NODES
  // add to the tail
  tail->node = newNode;
  tail = newNode;
  if(linkedVertex){
    // we have only one vertex to connnect;
    if(head == NULL) return;
    Node *cur = head;
    while(cur != NULL && cur != linkedVertex){
      cur = cur->nextNode; // find vertically
    }
    // got cur
    if (cur == NULL) return;
    // get horizontally
    while(cur->linkedVertex != NULL){
      cur = cur->linkedVertex;
    }
    cur->linkedVertex = newNode;
    newNode->prevVertex = cur;
  }
}


int main(void){

  insertVertex
  insert('a', NULL);

  return 0;

}
