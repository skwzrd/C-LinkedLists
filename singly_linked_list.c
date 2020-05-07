#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
  struct Node* next;
  int data;
} Node;


void print_linked_list(Node* head)
{
  if(head == NULL){
    printf("Empty linked list.");
    return;
  }

  Node* node = head;
  while(node != NULL){
    printf("%d\n", node->data);
    node = node->next;
  }
}


Node* create_node(int data)
{
  Node* new_node = (Node*) malloc(sizeof(Node));
  new_node->data = data;
  new_node->next = NULL;
  return new_node;
}


Node* get_tail(Node* head)
{
  if(head == NULL){
    return NULL;
  }

  Node* node = head;
  while(node->next != NULL){
    node = node->next;
  }
  return node;
}


void push_tail(Node* head, int data)
{
  if(head == NULL){
    return;
  }

  // get last node
  Node* tail = get_tail(head);
  
  // make new tail node
  Node* new_node = create_node(data);

  // bind new tail node
  tail->next = new_node;
}


void push_head(Node** head, int data)
{
  // make new head
  Node* new_head = create_node(data);

  // bind new head
  new_head->next = *head;
  *head = new_head;
}


void remove_head(Node** head)
{
  // nothing to delete
  if(*head == NULL){
    return;
  }

  // delete head
  Node* temp_node = *head;
  *head = (*head)->next;
  free(temp_node);
  temp_node = NULL;
  return;
}

void remove_tail(Node* head, Node** head_ref)
{
  // nothing to do
  if(head==NULL){
    return;
  }

  // remove head
  if(head->next == NULL){
    free(*head_ref);
    *head_ref = NULL;
    return;
  }

  Node* node = head;
  while(node->next->next != NULL)
  {
    node = node->next;
  }
  Node* tail = node->next;
  node->next = NULL;
  free(tail);
  tail=NULL;
}


void remove_index(Node** head, int index)
{
  // delete head
  if(index==0){
    remove_head(head);
    return;
  }

  // delete node after head
  int count = 0;
  Node* node = *head;
  // stop before reaching the indexed node
  while((count != index-1) && (node->next != NULL))
  {
    node = node->next;
    count++;
  }

  // in case index > length of linked list
  if(node->next != NULL){
    // remove indexed node
    Node* indexed_node = node->next;
    node->next = indexed_node->next;
    free(indexed_node);
    indexed_node = NULL;
  }
}


void insert_at_index(Node* head, Node** head_ref, int index, int data)
{
  if(head==NULL)
  {
    *head_ref = create_node(data);
    return;
  }

  if(index <= 0){
    push_head(head_ref, data);
    return;
  }
  
  int count = 0;
  Node* node = head;
  // go up to index-1 or the end of the linked list
  while((count < index-1) && (node->next != NULL)){
    node = node->next;
    count++;
  }

  // if at the end of the linked list
  if(node->next == NULL){
    node->next = create_node(data);
    return;
  }

  // if we're within the linked list
  Node* new_node = create_node(data);
  new_node->next = node->next;
  node->next = new_node;
}


void delete_linked_list(Node** head_ref)
{
  Node* node = *head_ref;
  while(node != NULL){
    Node* temp_node = node;
    node = node->next;
    free(temp_node);
    temp_node = NULL;
  }
  *head_ref = NULL;
}


int main ()
{
  Node* head = create_node(-1); // -1
  
  push_tail(head, 1); // -1 1
  
  remove_tail(head, &head); // -1
  remove_tail(head, &head); // Empty

  push_head(&head, 7); // 7
  push_head(&head, 8); // 8 7
  push_head(&head, 9); // 9 8 7

  remove_index(&head, 0); // 8 7

  push_tail(head, 6); // 8 7 6
  push_tail(head, 5); // 8 7 6 5
  push_tail(head, 4); // 8 7 6 5 4

  remove_tail(head, &head); // 8 7 6 5
  remove_tail(head, &head); // 8 7 6

  insert_at_index(head, &head, -10, 9); // 9 8 7 6
  insert_at_index(head, &head, 2, 0); // 9 8 0 7 6
  insert_at_index(head, &head, 10, 5); // 9 8 0 7 6 5

  print_linked_list(head); // 9 8 0 7 6 5

  delete_linked_list(&head); // Empty

  print_linked_list(head); // Empty

  return 0;
}
