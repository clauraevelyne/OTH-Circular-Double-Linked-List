#include <stdio.h>
#include <stdlib.h>

// Definisi struktur node
typedef struct Node {
    int data;
    struct Node *next;
    struct Node *prev;
} Node;

Node *head = NULL;
Node *tail = NULL;

// Fungsi untuk membuat node baru
void insertNode(int data) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;

    if (head == NULL) {
        head = newNode;
        tail = newNode;
        newNode->next = newNode;
        newNode->prev = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        newNode->next = head;
        head->prev = newNode;
        tail = newNode;
    }
}

// Fungsi untuk menambahkan node ke dalam sirkular double linked list
void printList() {
    if (head == NULL) {
        printf("List kosong.\n");
        return;
    }

    Node *temp = head;
    do {
        printf("Address: %p, Data: %d\n", temp, temp->data);
        temp = temp->next;
    } while (temp != head);
}

void swapNodes(Node *a, Node *b) {
    // Swapping nodes by adjusting the links
    if (a->next == b) { // a and b are adjacent
        a->next = b->next;
        b->prev = a->prev;
        a->prev->next = b;
        b->next->prev = a;
        b->next = a;
        a->prev = b;
    } else {
        Node *tempNext = a->next;
        Node *tempPrev = a->prev;
        a->next = b->next;
        a->prev = b->prev;
        b->next = tempNext;
        b->prev = tempPrev;
        a->next->prev = a;
        a->prev->next = a;
        b->next->prev = b;
        b->prev->next = b;
    }

    if (head == a) {
        head = b;
    } else if (head == b) {
        head = a;
    }

    if (tail == a) {
        tail = b;
    } else if (tail == b) {
        tail = a;
    }
}

// Fungsi untuk mengurutkan list
void sortList() {
    if (head == NULL) return;

    int swapped;
    Node *current;

    do {
        swapped = 0;
        current = head;

        do {
            Node *nextNode = current->next;
            if (current->data > nextNode->data) {
                swapNodes(current, nextNode);
                swapped = 1;
            } else {
                current = nextNode;
            }
        } while (current != tail);
    } while (swapped);
}

int main() {
    int n;
    printf("Masukkan jumlah data: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        int data;
        scanf("%d", &data);
        insertNode(data);
    }

    // Simpan alamat head sebelum pengurutan
    Node *originalHead = head;

    printf("\nSebelum pengurutan:\n");
    printList();

    sortList();

    // Cari alamat node dengan data terkecil setelah pengurutan
    Node *minNode = head;
    Node *current = head->next;
    while (current != head) {
        if (current->data < minNode->data) {
            minNode = current;
        }
        current = current->next;
    }

    // Cetak list dimulai dari node dengan data terkecil setelah pengurutan
    printf("\nSetelah pengurutan:\n");
    do {
        printf("Address: %p, Data: %d\n", minNode, minNode->data);
        minNode = minNode->next;
    } while (minNode != head);

    return 0;
}

