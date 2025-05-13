#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define SIZE 100

// Прототипи функцій для завдання 1
double f(double x, double y);
double compute_u(double a, double b);

// Прототипи функцій для завдання 2
void fillArray(int arr[], int n);
void printArray(int arr[], int n);
int findMinAbsIndex(int arr[], int n);
int productBetweenTwoZeros(int arr[], int n);

int main() {
    int choice;
    do {
        printf("\n~~ ого це що меню? ~~\n");
        printf("1. Завдання 1: f(x, y) = ((x - y) + 1) / (1 + x^2 + y^2), u = f(a,b) + f(a+b,a*b) + f(a^2,b^2) + f(1.7, a-b)\n");
        printf("2. Завдання 2: Мінімум за модулем і добуток між першими двома нулями\n");
        printf("0. Вихід\n");
        printf("Ваш вибір: ");
        scanf("%d", &choice);

        if (choice == 1) {
            double a, b;
            printf("\nВведіть a: ");
            scanf("%lf", &a);
            printf("Введіть b: ");
            scanf("%lf", &b);

            double result = compute_u(a, b);
            printf("Результат u = %.4lf\n", result);
        }
        else if (choice == 2) {
            int n;
            printf("\nВведіть розмір масиву (до %d): ", SIZE);
            scanf("%d", &n);

            if (n <= 0 || n > SIZE) {
                printf("Невірна довжина масиву!\n");
                continue;
            }

            int arr[SIZE];
            srand(time(NULL));
            fillArray(arr, n);
            printf("Згенерований масив:\n");
            printArray(arr, n);

            int minAbsIndex = findMinAbsIndex(arr, n);
            printf("Індекс мінімального за модулем елемента: %d (значення: %d)\n", minAbsIndex, arr[minAbsIndex]);

            int product = productBetweenTwoZeros(arr, n);
            if (product == -1)
                printf("У масиві менше двох нульових елементів – добуток не обчислюється.\n");
            else if (product == -2)
                printf("Між першим і другим нулями немає жодного елемента – добуток дорівнює 1.\n");
            else
                printf("Добуток елементів між першим і другим нульовими: %d\n", product);
        }
        else if (choice != 0) {
            printf("Невірний вибір. Спробуйте ще раз.\n");
        }

    } while (choice != 0);

    printf("Програму завершено.\n");
    return 0;
}

// Завдання 1: функції
double f(double x, double y) {
    return ((x - y) + 1) / (1 + x * x + y * y);
}

double compute_u(double a, double b) {
    return f(a, b) + f(a + b, a * b) + f(a * a, b * b) + f(1.7, a - b);
}

// Завдання 2: функції
void fillArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        arr[i] = rand() % 201 - 100;  // [-100;100]
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%4d ", arr[i]);
        if ((i + 1) % 10 == 0)
            printf("\n");
    }
}

int findMinAbsIndex(int arr[], int n) {
    int minIndex = 0;
    for (int i = 1; i < n; i++) {
        if (abs(arr[i]) < abs(arr[minIndex]))
            minIndex = i;
    }
    return minIndex;
}

int productBetweenTwoZeros(int arr[], int n) {
    int first = -1, second = -1;
    for (int i = 0; i < n; i++) {
        if (arr[i] == 0) {
            if (first == -1)
                first = i;
            else {
                second = i;
                break;
            }
        }
    }

    if (first == -1 || second == -1)
        return -1; // недостатньо нулів

    if (second - first == 1)
        return -2; // між нулями нічого

    int product = 1;
    for (int i = first + 1; i < second; i++)
        product *= arr[i];

    return product;
}
