#include "3d-viewer.h"



int modification(matrix_t *points, matrix_t *matrixMod) {
    matrix_t vector = s21_create_matrix(1, 4);
    for (int i = 0; i < points->rows; i++) {
        vector.matrix[0][0] = points->matrix[i][0];
        vector.matrix[0][1] = points->matrix[i][1];
        vector.matrix[0][2] = points->matrix[i][2];
        vector.matrix[0][3] = 1;
        vector = s21_mult_matrix(&vector, matrixMod);
        points->matrix[i][0] = vector.matrix[0][0];
        points->matrix[i][1] = vector.matrix[0][1];
        points->matrix[i][2] = vector.matrix[0][2];
    }
    s21_remove_matrix(&vector);
    return 1;
}

matrix_t init_modification_matrix() {
    matrix_t matrixMod = s21_create_matrix(4, 4);
    matrixMod.matrix[0][0] = sqrt(1.0 / 2.0);
    matrixMod.matrix[0][1] = (-1) * sqrt(1.0 / 6.0);
    // matrixMod.matrix[0][2] = sqrt(1.0 / 3.0);
    matrixMod.matrix[1][1] = sqrt(2.0 / 3.0);
    // matrixMod.matrix[1][2] = sqrt(1.0 / 3.0);
    matrixMod.matrix[2][0] = (-1) * sqrt(1.0 / 2.0);
    matrixMod.matrix[2][1] = (-1) * sqrt(1.0 / 6.0);
    // matrixMod.matrix[2][2] = sqrt(1.0 / 3.0);
    matrixMod.matrix[3][3] = 1;
    // matrixMod.type_modification = i;
    return matrixMod;
}

matrix_t rotationX(double angle) {
    matrix_t matrixMod = s21_create_matrix(4, 4);
    double radian = angle * (M_PI / 180);
    matrixMod.matrix[0][0] = 1;
    matrixMod.matrix[1][1] = cos(radian);
    matrixMod.matrix[1][2] = (-1) * sin(radian);
    matrixMod.matrix[2][1] = sin(radian);
    matrixMod.matrix[2][2] = cos(radian);
    matrixMod.matrix[3][3] = 1;
    return matrixMod;
}

matrix_t rotationY(double angle) {
    matrix_t matrixMod = s21_create_matrix(4, 4);
    double radian = angle * (M_PI / 180);
    matrixMod.matrix[0][0] = cos(radian);
    matrixMod.matrix[0][2] = sin(radian);
    matrixMod.matrix[1][1] = 1;
    matrixMod.matrix[2][0] = (-1) * sin(radian);
    matrixMod.matrix[2][2] = cos(radian);
    matrixMod.matrix[3][3] = 1;
    return matrixMod;
}

matrix_t rotationZ(double angle) {
    matrix_t matrixMod = s21_create_matrix(4, 4);
    double radian = angle * (M_PI / 180);
    matrixMod.matrix[0][0] = cos(radian);
    matrixMod.matrix[0][1] = (-1) * sin(radian);
    matrixMod.matrix[1][0] = sin(radian);
    matrixMod.matrix[1][1] = cos(radian);
    matrixMod.matrix[2][2] = 1;
    matrixMod.matrix[3][3] = 1;
   return matrixMod;
}

matrix_t translation(double dx, double dy, double dz) {
    matrix_t matrixMod = s21_create_matrix(4, 4);
    matrixMod.matrix[0][0] = 1;
    matrixMod.matrix[1][1] = 1;
    matrixMod.matrix[2][2] = 1;
    matrixMod.matrix[3][3] = 1;
    matrixMod.matrix[3][0] = dx;
    matrixMod.matrix[3][1] = dy;
    matrixMod.matrix[3][2] = dz;
    return matrixMod;
}

matrix_t scale_size(double size) {
    matrix_t matrixMod = s21_create_matrix(4, 4);
    matrixMod.matrix[0][0] = size;
    matrixMod.matrix[1][1] = size;
    matrixMod.matrix[2][2] = size;
    matrixMod.matrix[3][3] = 1;
    return matrixMod;
}

matrix_t s21_mult_matrix(matrix_t *A, matrix_t *B) {
    matrix_t result = s21_create_matrix(A->rows, B->columns);
    if (A->columns != B->rows ||
        A->matrix_type == INCORRECT_MATRIX || B->matrix_type == INCORRECT_MATRIX) {
        result.matrix_type = INCORRECT_MATRIX;
    } else {
        for (int i = 0; i < A->rows; i++) {
            for (int j = 0; j < B->columns; j++) {
                for (int k = 0; k < A->columns; k++) {
                    result.matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
                }
            }
        }
        // type_msatrix(&result);
    }
    return result;
}

