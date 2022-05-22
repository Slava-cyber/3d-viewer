
#include "3d-viewer.h"

int form_data(matrix_t *points, matrix_t *plane, char *file) {
    int error = 0;
    FILE *fp;
    fp = fopen(file, "r");
    if (fp == NULL) {
        error = 1;
    } else {
        char *str = NULL;
        size_t len;
        int i = 0, k = 0;
        while ((str = get_line(fp)) != NULL && error == 0) {
            if (str[0] == 'v' || str[0] == 'f') {
                error = parsing_line(str, points, plane, &i, &k);
                // printf("errorparsing:%d\n", error);
            }
            free(str);
        }
        if (str) free(str);
        fclose(fp);
    }
    return error;
}

int check_plane(matrix_t *plane, matrix_t *points) {
    int error = 0;
    for (int i = 0; i < plane->rows; i++) {
        for (int j = 0; j < plane->columns; j++) {
            int k = (int) plane->matrix[i][j] - 1;
            // printf("check:%d\n", k);
            if (k != -1) {
                if (k < 0 || k >= points->rows) {
                    error += 1;
                }
            }
        }
    }
    return error;
}


int parsing_line(char *str, matrix_t *points, matrix_t *plane, int *i, int *k) {
    int j = 0;
    int error = 0;
    double buf;
    char first = str[0];
    str += 2;
    // printf("parsing:%s\n", str);
    if (first == 'v') {
        while (*str != '\0' && error == 0 && j < 3) {
            // printf("tut\n");
            error = form_number(&str, &buf, first);
            if (*str == ' ' && *str != '\0') {
                str++;
            } else if (*str != ' ' && *str != '\0') {
                error = 1;
            }
            // printf("buf:%f-j:%d-c:%c\n", buf, j, *str);
            points->matrix[*i][j] = buf;
            // printf("hh");
            j += 1;
        }
        if (*str != '\0' || j != 3) {
            error = 1;
        }
        *i += 1;
    } else if (first == 'f') {
        while (*str != '\0' && error == 0) {
            error = form_number(&str, &buf, first);
            if (*str == ' ' && *str != '\0') {
                str++;
            } else if (*str != ' ' && *str != '\0') {
               error = 1;
            }
            // printf("buf:%f-j:%d-c:%c\n", buf, j, *str);
            plane->matrix[*k][j] = buf;
            j++;
        }
        *k += 1;
    }
    return error;
}

int file_read(matrix_t *points, matrix_t *plane, char *file) {
    int error = 0, points_number = 0, plane_number = 0, plane_size = 0;
    error = set_size(file, &points_number, &plane_number, &plane_size);
    printf("errorout\n");
    if (!error) {
        printf("errorin\n");
        *points = s21_create_matrix(points_number, 3);
        *plane = s21_create_matrix(plane_number, plane_size);
        printf("errorbetween:%d\n", error);
        error = form_data(points, plane, file);
        if (!error) {
            error = check_plane(plane, points);
        }
    }
    return error;
}

char* get_line(FILE *fp) {
    char ch;
    char *str = (char*) malloc(sizeof(char));
    int i = 0;
    while ((ch = fgetc(fp)) != -1 && ch != '\n') {
        str = realloc(str, i + 2);
        str[i] = ch;
        i += 1;
    }
    if (ch == -1) {
        if (i == 0) {
            free(str);
            str = NULL;
        } else {
            str[i] = '\0';
        }
    } else {
        str[i] = '\0';
    }
    return str;
}


int set_size(char *file, int *points_number, int *plane_number, int *plane_size) {
    *plane_size = 0, *plane_number = 0, *points_number = 0;
    int error = 0, plane_size_max = 0;
    FILE *fp;
    fp = fopen(file, "r");
    if (fp == NULL) {
        error = 1;
    } else {
        // printf("tut\n");
        char * str = NULL;
        while ((str = get_line(fp)) != NULL) {
            char *tmp = str;
            if (str[0] == 'v') {
                *points_number += 1;
            } else if (str[0] == 'f') {
                *plane_number += 1;
                double buf;
                if (strlen(str) > 3)
                    str +=2;
                else
                    error = 1;
                while (*str != '\0' && error == 0) {
                    // printf("c:%c\n", *str);
                    error = form_number(&str, &buf, tmp[0]);
                    // printf("str-%serror - %d, buf - %f\n", str, error, buf);
                    if (*str == ' ' && *str != '\0') {
                        str++;
                    } else if (*str != ' ' && *str != '\0') {
                        error = 1;
                    }
                    plane_size_max += 1;
                }
                if (*plane_size < plane_size_max) {
                    *plane_size = plane_size_max;
                }
                plane_size_max = 0;
            }
            free(tmp);
        }
        fclose(fp);
    }
    return error;
}

int digit(char c) {
    int result = -1;
    if (c >= '0' && c <= '9')
        result = c - 48;
    return result;
}

int form_number(char **str, double *number, char ch) {
    *number = 0;
    int error = 0;
    int sign = set_sign(str);
    if (digit(**str) > -1) {
        int dig;
        while ((dig = digit(**str)) > -1) {
            *number = 10 * (*number) + dig;
            *str += 1;
            // printf("number:%.2f\n", *number);
                if (**str == '.') {
                    if (ch == 'v') {
                        *str += 1;
                        if ((dig = digit(**str)) > -1) {
                            int i = 0;
                            while ((dig = digit(**str)) > -1) {
                                i += 1;
                                double buf = dig / pow(10, i);
                                *number += buf;
                                *str += 1;
                            }
                        } else {
                            error = 1;
                        }
                    } else {
                        error = 1;
                    }
                }
        }
        *number *= sign;
        if (!(**str == ' ' || **str == '\0')) {
            error = 1;
        }
    } else {
        error = 1;
    }
    return error;
}

int set_sign(char **str) {
    int sign = 1;
    if (**str == '-') {
        sign = -1;
        *str += 1;
    } else if (**str == '+') {
        sign = 1;
        *str += 1;
    }
    return sign;
}

// matrix functions

matrix_t s21_create_matrix(int rows, int columns) {
    matrix_t newMatrix;
    if (rows != 0 && columns != 0) {
        newMatrix.matrix = (double**)malloc(rows * sizeof(double*));
        for (int i = 0; i < rows; i++)
            *(newMatrix.matrix + i) = (double*)malloc(columns * sizeof(double));
        newMatrix.rows = rows;
        newMatrix.columns = columns;
        newMatrix.matrix_type = ZERO_MATRIX;

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++)
                *(*(newMatrix.matrix + i) + j) = 0;
        }
    } else {
        newMatrix.matrix = (double**)malloc(rows * sizeof(double*));
        for (int i = 0; i < 2; i++)
            *(newMatrix.matrix + i) = (double*)malloc(2 * sizeof(double));
        newMatrix.rows = 2;
        newMatrix.columns = 2;
        newMatrix.matrix_type = INCORRECT_MATRIX;
    }
    return newMatrix;
}


void s21_remove_matrix(matrix_t *A) {
    for (int i = 0; i < A->rows; i++)
        free(A->matrix[i]);
    free(A->matrix);
}
