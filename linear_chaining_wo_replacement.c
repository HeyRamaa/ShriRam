#include <stdio.h>
#include <stdlib.h>
#define SIZE 10
struct Node {
int data;
struct Node* next;
};
struct Node* createNode(int data) {
struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
newNode->data = data;
newNode->next = NULL;
return newNode;
}
void insert(int hashTable[], int key, int value) {
int index = key % SIZE;
if (hashTable[index] == -1) {
hashTable[index] = value;
} else {
struct Node* newNode = createNode(value);
struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
temp->next = NULL;
temp->next = newNode;
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
display(hashTable);
return 0;
}
