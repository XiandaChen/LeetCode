// array pointer: int (*p)[n];
// pointer array: int *p[n];

// Pointer: pass by reference
#include <stdio.h>
#include <stdlib.h>
typedef struct NODET {
    int val;
    struct NODET * next;
}NODE;
int insertHead(NODE ** head, int val) { // pass by reference
    NODE * node = (NODE*) malloc(sizeof(NODE));
    if (!node) return -1;
    node->val = val;
    node->next = *head;
    *head = node;
    return 0;
}
int main() {
    NODE * head = NULL;
    for (int i = 0; i < 5; ++i) {
        int res = insertHead(&head, i); // &: pass by reference
        if (res == -1) break;
    }
    while (head) {
        printf("%d ", head->val);
        NODE * tmp = head;
        head = head->next;
        free(tmp);
    }
    return 0;
}

// stack implementation in C
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
typedef struct STACK_TS {
    int capacity;
    int top;
    int *array;
} STACK;
STACK * newStack(int capacity) {
    STACK * stack = (STACK*) malloc(sizeof(STACK));
    if (!stack) {
        printf("Error allocating memory: stack!");
        exit(EXIT_FAILURE);
    }
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (int*) malloc(capacity * sizeof(int));
    if (!stack->array) {
        printf("Error allocating memory: stack->array!");
        exit(EXIT_FAILURE);
    }
    return stack;
}
int size(STACK* stack) {
    return stack->top + 1;
}
bool isFull(STACK* stack) {
	// or stack->top == stack->capacity - 1
    return size(stack) == stack->capacity; 
}
bool isEmstacky(STACK* stack) {
    return size(stack) == 0; // stack->top == -1;
}
void push(STACK* stack, int x) {
    if (isFull(stack)) {
        printf("Error: stack is full!");
        exit(EXIT_FAILURE);
    }
    stack->array[++stack->top] = x;
}
int pop(STACK* stack) {
    if (isEmstacky(stack)) {
        printf("Error: stack is empty!");
        exit(EXIT_FAILURE);
    }
    // decrease STACK by one, and (optionally) return the popped array
    return stack->array[stack->top--];
}
int top(STACK* stack) {
    if (isEmstacky(stack)) {
        printf("Error: stack is empty!");
        exit(EXIT_FAILURE);
    }
    return stack->array[stack->top];
}
int main() {
    STACK * stack = newStack(5);
    push(stack, 1);
    push(stack, 3);
    push(stack, 5);
    printf("stack size: %d\n", size(stack));
    printf("top element: %d\n", top(stack));
    pop(stack);
    printf("stack size: %d\n", size(stack));
    printf("top element: %d\n", top(stack));
    return 0;
}

// queue implementation in C
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
typedef struct QUEUE_TS {
    int front, rear, size;
    int capacity;
    int* array;
} QUEUE;
QUEUE* newQueue(int capacity) {
    QUEUE* queue = (QUEUE*) malloc(sizeof(QUEUE));
    if (!queue) {
        printf("Error allocating memory: queue!");
        exit(EXIT_FAILURE);
    }
    queue->capacity = capacity;
    queue->front = queue->size = 0;
    queue->rear = capacity - 1;
    queue->array = (int*) malloc(capacity * sizeof(int));
    if (!queue->array) {
        printf("Error allocating memory: queue->array!");
        exit(EXIT_FAILURE);
    }
    return queue;
}
bool isFull(QUEUE* queue) {
    return queue->size == queue->capacity;
}
bool isEmpty(QUEUE* queue) {
    return queue->size == 0;
}
void enqueue(QUEUE* queue, int x) {
    if (isFull(queue)) {
        printf("Error: queue is full!");
        exit(EXIT_FAILURE);
    } 
    // circular queue: % queue->capacity
    queue->rear = (queue->rear + 1) % queue->capacity;  
    queue->array[queue->rear] = x;
    queue->size += 1;
}
int dequeue(QUEUE* queue) { // remove from the front
    if (isEmpty(queue)) {
        printf("Error: queue is empty!");
        exit(EXIT_FAILURE);
    }
    int item = queue->array[queue->front++];
    queue->size -= 1;
    return item;
}
int front(QUEUE* queue) {
    if (isEmpty(queue)) {
        printf("Error: queue is empty!");
        exit(EXIT_FAILURE);
    }
    return queue->array[queue->front];
}
int rear(QUEUE* queue) {
    if (isEmpty(queue)) {
        printf("Error: queue is empty!");
        exit(EXIT_FAILURE);
    }
    return queue->array[queue->rear];
}
int main() {
    QUEUE * queue = newQueue(5);
    enqueue(queue, 1);
    enqueue(queue, 3);
    enqueue(queue, 5);
    printf("queue size: %d\n", queue->size);
    printf("front element: %d\n", front(queue));
    printf("rear element: %d\n", rear(queue));
    int a = dequeue(queue);
    printf("dequeue: %d\n", a);
    printf("queue size: %d\n", queue->size);
    printf("front element: %d\n", front(queue));
    printf("rear element: %d\n", rear(queue));
    return 0;
}

// heap implementation in C: not push/pop/top
// construct complete binary tree, then heapify the tree, O(NlogN)
#include <stdio.h>
#include <stdlib.h>
void swap(int* a, int* b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}
// heapify a subtree rooted at node i, n is heap size
void heapify(int arr[], int n, int i) {
    int largest = i; // initiate the root
    int l = 2 * i + 1; // left node of i
    int r = 2 * i + 2; // right node of i
    if (l < n && arr[l] > arr[largest]) largest = l;
    if (r < n && arr[r] > arr[largest]) largest = r;
    // if largest is not root
    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        // recursively heapify the affected subtree
        heapify(arr, n, largest);
    }
}
// build max-heap for the given array 
void buildHeap(int arr[], int n) {
    // index of the last non-leaf node of complete binary tree
    int startIdx = (n - 2) - 1;
    // heapify from the last non-leaf node, at reverse level order
    for (int i = startIdx; i >= 0; --i) {
        heapify(arr, n, i);
    }
}
void printArr(int arr[], int n) {
    for (int i = 0; i < n; ++i) {
        printf("%d ", arr[i]);
    }
}
int main() {
    int arr[] = {1, 3, 5, 4, 6, 13, 10, 9, 8, 15, 17};
    int n = sizeof(arr) / sizeof(int);
    printf("Input array is: ");
    printArr(arr, n);

    buildHeap(arr, n);
    printf("\nOutput Heap is: ");
    printArr(arr, n); // Output Heap is: 17 15 13 9 6 5 10 4 8 3 1
    return 0;
}

// Queue implementation in C
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
static const unsigned int base_size = 4;
typedef struct HEAP_TS {
    int capacity, count;
    int* array;
} HEAP;
HEAP* newHeap(int capacity) {
    HEAP* heap = (HEAP*) malloc(sizeof(HEAP));
    if (!heap) {
        printf("Error allocating memory: heap!");
        exit(EXIT_FAILURE);
    }
    heap->capacity = capacity;
    heap->count = 0;
    heap->array = (int*) malloc(capacity * sizeof(int));
    if (!heap->array) {
        printf("Error allocating memory: heap->array!");
        exit(EXIT_FAILURE);
    }
    return heap;
}
bool isFull(HEAP* heap) {
    return heap->count == heap->capacity;
}
bool isEmpty(HEAP* heap) {
    return heap->count == 0;
}
void max_heapify(int* array, int count, int loc) {
    int left, right, largest, tmp;
    left = 2 * loc + 1;
    right = 2 * loc + 2;
    largest = loc;
    if (left <= count && array[left] > array[largest]) largest = left;
    if (right <= count && array[right] > array[largest]) largest = right;
    if (largest != loc) {
        tmp = array[loc];
        array[loc] = array[largest];
        array[largest] = tmp;
        // recursively heapify the affected subtree
        max_heapify(array, count, largest);
    }
}
void push(HEAP* heap, int val) {
    int index, parent;
    // resize the heap if it is too small
    if (heap->count == heap->capacity) {
        heap->capacity += 1;
        heap->array = realloc(heap->array, sizeof(int) * heap->capacity);
        if (!heap->array) exit(EXIT_FAILURE);
    }
    index = heap->count++; // first insert at last of array
    // find out where to insert the element, and insert it
    for (; index; index = parent) {
        parent = (index - 1) / 2;
        if (heap->array[parent] >= val) break;
        heap->array[index] = heap->array[parent];
    }
    heap->array[index] = val;
    // max_heapify(heap->array, heap->count, index);
}
int pop(HEAP* heap) {
    int removed, tmp = heap->array[--heap->count];
    // resize the heap if it consumes too much memory
    if ((heap->count <= (heap->capacity >> 2)) 
        && (heap->capacity > base_size)) {
        heap->capacity >>= 1;
        heap->array = realloc(heap->array, sizeof(int) * heap->capacity);
        if (!heap->array) exit(EXIT_FAILURE);
    }
    removed = heap->array[0];
    heap->array[0] = tmp;
    max_heapify(heap->array, 0, heap->count);
    return removed;
}
void printHeap(HEAP* heap) {
    for (int i = 0; i < heap->count; ++i) {
        printf("%d ", heap->array[i]);
    }
    printf("\n");
}
int main() {
    HEAP * heap = newHeap(5);
    push(heap, 1); push(heap, 3); push(heap, 5);
    push(heap, 4); push(heap, 6); push(heap, 13);
    push(heap, 10); push(heap, 9); push(heap, 8);
    push(heap, 15); push(heap, 17);
    printf("Create heap: \n"); // Not correct: 17 15 10 8 13 3 6 1 5 4 9
    printHeap(heap);
    printf("Top elem: %d\n", heap->array[0]);
    pop(heap);
    printf("Heap after poping: \n");
    printHeap(heap);
    return 0;
}





































































