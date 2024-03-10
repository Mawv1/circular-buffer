#include <stdio.h>
#include <stdlib.h>
#include "circular_buffer.h"

int main() {
    int volume;
    struct circular_buffer_t *buffer;
    printf("Podaj rozmiar bufora:");
    if (scanf("%d", &volume) != 1) {
        printf("Incorrect input");
        return 1;
    }
    if (volume <= 0) {
        printf("Incorrect input data");
        return 2;
    }
    int whot = circular_buffer_create_struct(&buffer, volume);
    if (whot != 0) {
        printf("Failed to allocate memory");
        return 8;
    }
    int choice;
    while (1) {
        printf("Co chcesz zrobic?");
        if (scanf("%d", &choice) != 1) {
            printf("Incorrect input");
            circular_buffer_destroy_struct(&buffer);
            return 1;
        }
        if (choice > 6 || choice < 0) {
            printf("Incorrect input data\n");
        }
        if (choice == 1) {
            int number;
            printf("Podaj liczbe:");
            if (scanf("%d", &number) != 1) {
                printf("Incorrect input");
                circular_buffer_destroy_struct(&buffer);
                return 1;
            }
            circular_buffer_push_back(buffer, number);
        } else if (choice == 2) {
            int error;
            int what = circular_buffer_pop_back(buffer, &error);
            if (error == 2) {
                printf("Buffer is empty\n");
            } else {
                printf("%d\n", what);
            }
        } else if (choice == 3) {
            int error;
            int what = circular_buffer_pop_front(buffer, &error);
            if (error == 2) {
                printf("Buffer is empty\n");
            } else {
                printf("%d\n", what);
            }
        } else if (choice == 4) {
            if (circular_buffer_empty(buffer) == 1) {
                printf("Buffer is empty\n");
            } else {
                circular_buffer_display(buffer);
            }
        } else if (choice == 5) {
            if (circular_buffer_empty(buffer) == 1) {
                printf("1\n");
            } else {
                printf("0\n");
            }
        } else if (choice == 6) {
            if (circular_buffer_full(buffer) == 1) {
                printf("1\n");
            } else {
                printf("0\n");
            }
        } else if (choice == 0) {
            circular_buffer_destroy_struct(&buffer);
            break;
        }
    }
    return 0;
}

