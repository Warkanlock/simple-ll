#include <assert.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

/**
    Notes:

    1. We use double-pointer to the structure because we want to modify the head
   of the list always.
    2. We use the assert to check if the head is not NULL.
    3. We use the malloc to allocate memory for the new node.
    4. We use `**` double pointer technique on the methods that affects the
   linkedlist because we want to modify the address that the actual node is
   pointing to instead of modying the actual underyling value
*/

typedef struct Node {
  int value;         // value of the node
  struct Node *next; // pointer to the next element of the list
} Node;

Node *create_node(int value) {
  Node *new_node = (Node *)malloc(sizeof(Node));
  new_node->value = value;
  new_node->next = NULL;
  return new_node;
}

void modify_node(Node *node, int value) { node->value = value; }

void remove_node(Node **head, int value) {
  Node *previous_node = NULL;
  Node *current = *head;

  if (current != NULL && current->value == value) {
    *head = current->next;
    free(current);
    return;
  }

  // search while current is not the value expected
  while (current != NULL && current->value != value) {
    previous_node = current;
    current = current->next;
  }

  // nothing was found
  if (current == NULL) {
    return;
  }

  // current node is exactly the node we want to delete
  // that's why we free from memory however we connect previous_node with the
  // node pointing from the current
  previous_node->next = current->next;
  free(current);
}

void insert_at_beginning(Node **head, int value) {
  // create a new node from scratch
  Node *new_node = create_node(value);

  // assign the node to point to the actual head of the list
  new_node->next = *head;

  // assign the head as the new node
  *head = new_node;
}

void insert_at_end(Node **head, int value) {
  assert(head != NULL);

  // we should iterate the head until we reach next = NULL
  Node *new_node = create_node(value);

  // iterate until reaching the end of the list
  Node *tail = *head;
  while (tail->next != NULL) {
    tail = tail->next;
  }

  // assign the last node the new node
  tail->next = new_node;
}

int main() {
  Node *ll = (Node *)malloc(sizeof(Node));

  ll = create_node(10);
  printf("%d\n", ll->value);

  insert_at_beginning(&ll, 20);
  printf("%d -> %d\n", ll->value,
         ll->next->value); // this should show: 20 -> 10

  insert_at_end(&ll, 30);
  printf("%d -> %d -> %d\n", ll->value, ll->next->value,
         ll->next->next->value); // this should show: 20 -> 10 -> 30

  assert(ll != NULL);
  assert(ll->value == 20);
  modify_node(
      ll,
      40); // as you see here, the pointer is passed by reference so we
           // can modify the value of the node (no need to use double pointers
           // since we don't need to modify the actual underlying data)
  assert(ll->value == 40);
  printf("%d -> %d -> %d\n", ll->value, ll->next->value,
         ll->next->next->value); // this should show: 20 -> 10 -> 30

  // delete value from list
  remove_node(&ll, 40);
  printf("%d -> %d\n", ll->value,
         ll->next->value); // this should show: 10 -> 30

  // free memory
  free(ll);
}
