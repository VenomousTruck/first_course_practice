#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <time.h>

// Функция для обмена значениями

void Swap(int *firstNumber, int *secondNumber) {
    int tempNumber = *firstNumber;
    *firstNumber = *secondNumber;
    *secondNumber = tempNumber;
}

// Просеивание поддерева, корень которого находится в узле root,
// который является индексом в массиве arr

void Heapify(int arr[], int heapSize, int root) {
    // Инициализируем left как 2 * i + 1, а right как 2 * i + 2,
    // поскольку индексация идет с нуля

    int largest = root;        // наименьшее значение - это корень дерева
    int left = 2 * root + 1;    // левый дочерний элемент
    int right = 2 * root + 2;    // правый дочерний элемент

    // Если левый дочерний элемент меньше корня

    if (left < heapSize && arr[left] > arr[largest]) {
        largest = left;
    }

    // Если правый дочерний элемент меньше, чем самый
    // маленький элемент на данный момент

    if (right < heapSize && arr[right] > arr[largest]) {
        largest = right;
    }

    // Если самый маленький элемент не является корневым элементом

    if (largest != root) {
        Swap(&arr[root], &arr[largest]);

        // Рекурсивно просеиваем вниз измененное поддерево

        Heapify(arr, heapSize, largest);
    }
}

// Функция пирамидальной сортировки

void HeapSort(int arr[], int numberOfElements) {
    // Построение дерева

    for (int i = numberOfElements / 2 - 1; i >= 0; i--) {
        Heapify(arr, numberOfElements, i);
    }

    // Извлекаем элементы из пирамиды один за другим

    for (int i = numberOfElements - 1; i > 0; i--) {
        // Текущий корень передвигаем в конец дерева

        Swap(&arr[0], &arr[i]);

        // Просеиваем поддерево вниз

        Heapify(arr, i, 0);
    }
}

// Функция вывода массива на экран

void PrintArray(int arr[], int numberOfElements) {
    for (int i = 0; i < numberOfElements; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    setlocale(LC_ALL, "ru");

    printf("%s", "Введите ключ: ");
    int key;
    scanf("%d", &key);
    srand(key);

    printf("%s", "Введите размер массива: ");
    int n;
    scanf("%d", &n);
    int *arr = (int *) malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 1000000;
    }

    printf("%s", "\nИсходный массив: \n\n");
    PrintArray(arr, n);

    clock_t start, end;
    start = clock();
    HeapSort(arr, n);
    end = clock();
    double time = (double) (end - start) / CLOCKS_PER_SEC;
    printf("\nВремя выполнения сортировки: %lf секунд\n", time);

    printf("%s", "\nОтсортированный массив: \n\n");
    PrintArray(arr, n);

    free(arr);

    return 0;
}
