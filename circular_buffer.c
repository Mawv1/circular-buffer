#include "circular_buffer.h"
#include <stdio.h>
#include <stdlib.h>

int circular_buffer_empty(const struct circular_buffer_t *a) {
    if (a == NULL || a->begin < 0 || a->end < 0 || a->capacity <= 0 || a->begin > a->capacity || a->end > a->capacity) {
        return -1;
    }
    if (a->begin == a->end && a->full == 0) {
        return 1;
    }
    return 0;
}

int circular_buffer_full(const struct circular_buffer_t *a) {
    if (a == NULL || a->begin < 0 || a->end < 0 || a->capacity <= 0 || a->begin > a->capacity || a->end > a->capacity) {
        return -1;
    }
    if (a->begin == a->end && a->full == 1) {
        return 1;
    }
    return 0;
}

int circular_buffer_create(struct circular_buffer_t *a, int N) {
    if (a == NULL || N <= 0) {
        return 1;
    }
    a->ptr = malloc(N * sizeof(int));
    if (a->ptr == NULL) {
        return 2;
    }
    a->full = 0;
    a->capacity = N;
    a->begin = 0;
    a->end = 0;
    return 0;
}

int circular_buffer_create_struct(struct circular_buffer_t **cb, int N) {
    if (cb == NULL || N <= 0) {
        return 1;
    }
    *cb = (struct circular_buffer_t *) malloc(sizeof(struct circular_buffer_t));
    if (*cb == NULL) {
        return 2;
    }
    int result = circular_buffer_create(*cb, N);
    if (result == 2) {
        free(*cb);
        return 2;
    }
    return 0;
}

void circular_buffer_destroy(struct circular_buffer_t *a) {
    if (a == NULL || a->begin < 0 || a->end < 0 || a->capacity <= 0 || a->ptr == NULL) {
        return;
    }
    free(a->ptr);
}

void circular_buffer_destroy_struct(struct circular_buffer_t **a) {
    if (a == NULL || *a == NULL) {
        return;
    }
    circular_buffer_destroy(*a);
    free(*a);
}

int circular_buffer_push_back(struct circular_buffer_t *cb, int value) {
    if (cb == NULL || cb->ptr == NULL || cb->capacity <= 0 || cb->end < 0
        || cb->begin < 0 || cb->end > cb->capacity || cb->begin > cb->capacity) {
        return 1;
    }
    if (cb->full == 0) {
        int finish = cb->end;
        int *wsk = cb->ptr;
        *(wsk + finish) = value;
        cb->end++;
        if (cb->end == cb->capacity) {
            cb->end = 0;
        }
        if (cb->begin == cb->end) {
            cb->full = 1;
        }
    } else if (cb->full == 1) {
        cb->begin++;
        if (cb->begin >= cb->capacity) {
            cb->begin = 0;
        }
        int finish = cb->end;
        int *wsk = cb->ptr;
        *(wsk + finish) = value;
        cb->end++;
        if (cb->end >= cb->capacity) {
            cb->end = 0;
        }
    }
    return 0;
}

int circular_buffer_pop_front(struct circular_buffer_t *a, int *err_code) {
    if (a == NULL || a->ptr == NULL || a->begin > a->capacity || a->end > a->capacity
        || a->begin < 0 || a->end < 0 || a->capacity <= 0) {
        if (err_code != NULL) {
            *err_code = 1;
        }
        return 1;
    }
    if (circular_buffer_empty(a) == 1) {
        if (err_code != NULL) {
            *err_code = 2;
        }
        return 2;
    }
    int start = a->begin;
    int *wsk = a->ptr;
    if (err_code != NULL) {
        *err_code = 0;
    }
    a->begin++;
    if (a->begin == a->capacity) {
        a->begin = 0;
    }
    a->full = 0;
    return *(wsk + start);
}

int circular_buffer_pop_back(struct circular_buffer_t *a, int *err_code) {
    if (a == NULL || a->ptr == NULL || a->begin > a->capacity || a->end > a->capacity
        || a->begin < 0 || a->end < 0 || a->capacity <= 0) {
        if (err_code != NULL) {
            *err_code = 1;
        }
        return 1;
    }
    if (circular_buffer_empty(a)) {
        if (err_code != NULL) {
            *err_code = 2;
        }
        return 0;
    }
    int *wsk = a->ptr;
    if (err_code != NULL) {
        *err_code = 0;
    }
    a->end--;
    if (a->end < 0) {
        a->end = a->capacity - 1;
    }
    a->full = 0;
    return *(wsk + a->end);
}

void circular_buffer_display(const struct circular_buffer_t *a) {
    if (a == NULL || a->capacity <= 0 || a->end < 0 || a->begin < 0 || a->begin > a->capacity || a->end > a->capacity) {
        return;
    }
    if (a->end < a->begin) {
        for (int i = a->begin; i < a->capacity; i++) {
            printf("%d ", *(a->ptr + i));
        }
        for (int i = 0; i < a->end; i++) {
            printf("%d ", *(a->ptr + i));
        }
    } else if (a->end > a->begin) {
        for (int i = a->begin; i < a->end; i++) {
            printf("%d ", *(a->ptr + i));
        }
    } else if (a->end == a->begin) {
        if (a->full == 0) {
            return;
        } else if (a->full == 1) {
            for (int i = a->begin; i < a->capacity; i++) {
                printf("%d ", *(a->ptr + i));
            }
            for (int i = 0; i < a->end; i++) {
                printf("%d ", *(a->ptr + i));
            }
        }
    }
    printf("\n");
}
