#include <stdio.h>
#include <stdlib.h>
#define SIZE 10
#define LIMIT 5 // Maximum number of collisions allowed
struct Node {
int key;
int data;
struct Node* next;
};
struct Node* createNode(int key, int data) {
struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
newNode->key = key;

newNode->data = data;
newNode->next = NULL;
return newNode;
}
void insert(int hashTable[], int key, int value) {
int index = key % SIZE;
int collisions = 0;
if (hashTable[index] == -1) {
hashTable[index] = value;
} else {
struct Node* newNode = createNode(key, value);
struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
temp->next = NULL;
temp->next = newNode;
collisions++;
while (temp->next != NULL) {
index = (index + 1) % SIZE;
collisions++;
if (collisions > LIMIT) {
printf("Exceeded maximum collisions. Cannot insert.\n");
free(newNode);
return;
}
if (hashTable[index] == -1) {
hashTable[index] = newNode->data;
free(newNode);
return;
}
temp = temp->next;
}
}
}
void display(int hashTable[]) {
for (int i = 0; i < SIZE; i++) {
if (hashTable[i] != -1) {
printf("Index %d: ", i);
printf("%d\n", hashTable[i]);
} else {
printf("Index %d: Empty\n", i);
}
}
}
int main() {

int hashTable[SIZE];
for (int i = 0; i < SIZE; i++) {
hashTable[i] = -1;
}
insert(hashTable, 5, 25);
insert(hashTable, 15, 35);
insert(hashTable, 25, 45);
insert(hashTable, 35, 55);
insert(hashTable, 55, 75); // Causes replacement due to exceeding LIMIT
display(hashTable);
return 0;
}
