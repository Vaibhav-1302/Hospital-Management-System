#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct {
    char name[50];
    int age;
    int priority; // 1 = High, 2 = Medium, 3 = Low
} Patient;

Patient heap[MAX];
int size = 0;

void swap(Patient *a, Patient *b) {
    Patient temp = *a;
    *a = *b;
    *b = temp;
}

void insertPatient(Patient p) {
    heap[++size] = p;
    int i = size;
    while (i > 1 && heap[i].priority < heap[i / 2].priority) {
        swap(&heap[i], &heap[i / 2]);
        i = i / 2;
    }
}

void displayQueue() {
    if (size == 0) {
        printf("\nNo patients in the queue.\n");
        return;
    }

    printf("\nCurrent Patient Queue (by priority):\n");
    for (int i = 1; i <= size; i++) {
        printf("%s (Age: %d, Priority: %d)\n", heap[i].name, heap[i].age, heap[i].priority);
    }
}

void dischargePatient() {
    if (size == 0) {
        printf("No patients in the queue.\n");
        return;
    }

    printf("Discharging patient: %s\n", heap[1].name);
    heap[1] = heap[size--];

    int i = 1;
    while (2 * i <= size) {
        int min = i;
        if (heap[2 * i].priority < heap[min].priority) min = 2 * i;
        if (2 * i + 1 <= size && heap[2 * i + 1].priority < heap[min].priority) min = 2 * i + 1;

        if (min != i) {
            swap(&heap[i], &heap[min]);
            i = min;
        } else {
            break;
        }
    }
}

int main() {
    int choice;
    Patient p;

    do {
        printf("\n--- HospitalCare DS Menu ---\n");
        printf("1. Add Patient\n");
        printf("2. Display Queue\n");
        printf("3. Discharge Patient\n");
        printf("4. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);
        getchar(); // to consume newline after number input

        switch (choice) {
            case 1:
                printf("Enter name: ");
                fgets(p.name, sizeof(p.name), stdin);
                p.name[strcspn(p.name, "\n")] = 0; // remove newline

                printf("Enter age: ");
                scanf("%d", &p.age);

                do {
                    printf("Enter priority (1 = High, 2 = Medium, 3 = Low): ");
                    scanf("%d", &p.priority);
                    if (p.priority < 1 || p.priority > 3) {
                        printf("Invalid priority. Try again.\n");
                    }
                } while (p.priority < 1 || p.priority > 3);

                insertPatient(p);
                break;

            case 2:
                displayQueue();
                break;

            case 3:
                dischargePatient();
                break;

            case 4:
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid choice. Try again.\n");
        }

    } while (choice != 4);

    return 0;
}
