#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#include <gtk/gtk.h>
#include <cairo.h>


typedef enum {
    CORRECT_MATRIX = 0,
    INCORRECT_MATRIX = 1,
    IDENTITY_MATRIX = 2,
    ZERO_MATRIX = 3
} matrix_type_t;

typedef enum {
    nothing = -1,
    INIT = 0,
    rotationOX = 1,
    rotationOY = 2,
    rotationOZ = 3,
    shiftX = 4,
    shiftY = 5,
    SCALE = 6
} type_modification_t;

typedef struct matrix_struct {
    double** matrix;
    int rows;
    int columns;
    type_modification_t type_modification;
    matrix_type_t matrix_type;
} matrix_t;

    // parser
int form_data(matrix_t *points, matrix_t *plane, char *file);
int parsing_line(char *str, matrix_t *points, matrix_t *plane, int *i, int *k);
int file_read(matrix_t *points, matrix_t *plane, char *file);
int set_size(char *file, int *points_number, int *plane_number, int *plane_size);
int digit(char c);
int form_number(char **str, double *number, char ch);
int set_sign(char **str);
char* get_line(FILE *fp);
int check_plane(matrix_t *plane, matrix_t *points);

matrix_t s21_create_matrix(int rows, int columns);
void s21_remove_matrix(matrix_t *A);

    // modification
matrix_t s21_mult_matrix(matrix_t *A, matrix_t *B);

matrix_t init_modification_matrix();
int modification(matrix_t *points, matrix_t *matrixMod);
matrix_t rotationX(double angle);
matrix_t rotationY(double angle);
matrix_t rotationZ(double angle);
matrix_t translation(double dx, double dy, double dz);
matrix_t scale_size(double size);


void draw_graph(cairo_t *cr, int width, int height, matrix_t *buf);
//void graph();
void button_clicked(GtkWidget *button);
void init(int argc, char *argv[]);
void myCSS(void);
void file(GtkFileChooserButton *f);
static void on_draw_event(GtkWidget *widget, cairo_t *cr, gpointer data);
static void settingsWindowDraw(GtkWidget *widget, cairo_t *cr, gpointer data);
void draw_axes(cairo_t *cr, int width, int height, int x_shift, int y_shift);
void one_char_operation(char *str, char *value, int *point);
void many_char_operation(char *str, char *value, int *point);
char *push_char(char *first, char *second, int *point);
char *delete_char(char *first, int *point);
static void draw_model(GtkWidget *widget, cairo_t *cr, gpointer data);
void drawModel();
void ScaleAction(GtkWidget *button, gpointer *data);
void scaleEntry(GtkEntry * e);
void get_text_one_x(GtkEntry * e);
void hideAllTextView(bool isHide);
void hideAllSliders(bool isHide);
static void transmitScale (GtkRange *range, gpointer data);
static void transmitTranslateX (GtkRange *range, gpointer data);
