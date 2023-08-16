#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <time.h>

#define MAX_SIZE 18000

// Структура для представления элемента очереди с приоритетами

typedef struct {
    char color[50];
    int priority;
} QueueItem;

// Структура для представления очереди с приоритетами

typedef struct {
    QueueItem items[MAX_SIZE];
    int size;
} PriorityQueue;

//  Выполняет сдвиг элементов вниз по пирамиде

void SiftDown(QueueItem arr[], int heapSize, int root) {
    int largest = root;
    int left = 2 * root + 1;
    int right = 2 * root + 2;

    if (left < heapSize && arr[left].priority > arr[largest].priority) {
        largest = left;
    }

    if (right < heapSize && arr[right].priority > arr[largest].priority) {
        largest = right;
    }

    if (largest != root) {
        QueueItem temp = arr[root];
        arr[root] = arr[largest];
        arr[largest] = temp;

        SiftDown(arr, heapSize, largest);
    }
}

// Постройка пирамиды из элементов массива

void Heapify(QueueItem arr[], int n) {
    // Строим пирамиду снизу вверх
    for (int i = n / 2 - 1; i >= 0; i--) {
        SiftDown(arr, n, i);
    }
}

// Инициализация очереди с приоритетами

void InitializeQueue(PriorityQueue *queue) {
    queue->size = 0;
}

// Добавление элементов в очередь

void Enqueue(PriorityQueue *queue, QueueItem item) {
    if (queue->size >= MAX_SIZE) {
        printf("Очередь переполнена\n");
        return;
    }

    queue->items[queue->size] = item;
    queue->size++;

    // Выполняем пирамидальную сортировку после добавления элемента

    Heapify(queue->items, queue->size);
}

// Извлечение элементов из очереди

void Dequeue(PriorityQueue *queue) {
    if (queue->size <= 0) {
        printf("Очередь пуста\n");
        return;
    }

    // Обмениваем первый и последний элементы

    QueueItem temp = queue->items[0];
    queue->items[0] = queue->items[queue->size - 1];
    queue->items[queue->size - 1] = temp;
    queue->size--;

    // Выполняем пирамидальную сортировку после извлечения элемента

    Heapify(queue->items, queue->size);
}

// Функция для вывода элементов и их приоритетов

void PrintQueue(PriorityQueue queue) {
    printf("Элементы в очереди с приоритетом (по убыванию приоритета):\n");

    while(queue.size > 0) {
        QueueItem item = queue.items[0];
        Dequeue(&queue);
        printf("Цвет: %s, Приоритет: %d\n", item.color, item.priority);
    }

    printf("\n");
}

// Функция генерации случайных цветов

void GenerateRandomColor(char color[]) {
    const char *colors[]  = {"Red", "Green", "Blue", "White", "Black",
                             "Cyan", "Orange", "Gray", "Pink", "Yellow",
                             "Alice blue", "Amaranth", "Cadmium Green",
                             "China Pink", "Cyber Yellow"};
    int numColors = sizeof(colors) / sizeof(colors[0]);
    int randomIndex = rand() % numColors;
    strcpy(color, colors[randomIndex]);
}

int main() {
    setlocale(LC_ALL, "ru");

    printf("%s", "Введите ключ: ");
    int key;
    scanf("%d", &key);
    srand(key);

    PriorityQueue queue;
    InitializeQueue(&queue);

    int n = 0;
    printf("%s", "Введите количество элементов: ");
    scanf("%d", &n);

    clock_t start, end;
    start = clock();

    for (int i = 0; i < n; i++) {
        QueueItem item;
        GenerateRandomColor(item.color);
        item.priority = rand() % 10000;
        Enqueue(&queue, item);
    }

    end = clock();
    double time = (double) (end - start) / CLOCKS_PER_SEC;
    printf("\nВремя выполнения алгоритма: %lf секунд\n", time);

    PrintQueue(queue);

    return 0;
}
