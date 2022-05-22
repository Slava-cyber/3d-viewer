#include "3d-viewer.h"

GtkWidget *label;
GtkWidget *window;
GtkWidget *fixed;
GtkWidget *buttonDigits[11];
GtkWidget *buttonEqual;
GtkWidget *buttonFunctions[9];
GtkWidget *buttonBrackets[2];
GtkWidget *buttonOperations[6];
GtkWidget *buttonDelete;
GtkWidget *buttonDeleteAll;
GtkWidget *buttonX;
GtkWidget *buttonEmpty;
GtkWidget *fixedGraph;
GtkWidget *drawing_area;
GtkWidget *windowGraph;
GtkWidget *scaleUp;
GtkWidget *scaleDown;
GtkWidget *window;
GtkWidget * secondWindow;
GtkWidget *fixed;
GtkWidget* fix;
GtkWidget *darea;
GtkWidget* drawingArea;
GtkWidget* DA;
GtkWidget* isSliderSettings;
GtkWidget* isFillSettings;
GtkWidget* SettingsDrawingArea;
GtkWidget* mainlabel;
GtkWidget* modellabel;
GtkWidget * valueLabel;
GtkWidget* translateLabel;
GtkWidget* rotateLabel;
GtkWidget* scaleLabel;
GtkWidget*  file_chooser_button;
GtkWidget* textViewOneX;
GtkWidget* textViewOneY;
GtkWidget* textViewOneZ;
GtkWidget* textViewTwoX;
GtkWidget* textViewTwoY;
GtkWidget* textViewTwoZ;
GtkWidget* scaleTextView;
GtkWidget* GG;
GtkWidget* buttonTranslate;
GtkWidget* buttonRotate;
GtkWidget* buttonScale;
GtkWidget* buttonScale;
GtkWidget* axisLabel;
GtkWidget* aboutModelLabelV;
GtkWidget* aboutModelLabelF;
GtkWidget* settingsButton;
GtkWidget* settingsWindow;
GtkWidget* translateXSlider;
GtkWidget* translateYSlider;
GtkWidget* translateZSlider;
GtkWidget* rotateXSlider;
GtkWidget* rotateYSlider;
GtkWidget* rotateZSlider;
GtkWidget* scaleSlider;
char * axis[3] = {"X", "Y", "Z"};
char str[300] = "\0";
char str2[300] = "\0";
int point = 0;
double scale_test = 0;
int x_status;
int readFile = 0;
double x_coordinate_translate = 0;
double y_coordinate_translate = 0;
double z_coordinate_translate = 0;
double x_coordinate_rotate = 0;
double y_coordinate_rotate = 0;
double z_coordinate_rotate = 0;
bool isDigitInputFormat = true;
matrix_t points;
matrix_t plane;

// MARK: - Actions
    /*
    Functions designed
        to handle gtkWidget element events
     */
void rotateAction(GtkWidget *button, gpointer *data) {
    
    matrix_t rotataX = rotationX(x_coordinate_rotate);
    modification(&points, &rotataX);
    s21_remove_matrix(&rotataX);
    
    matrix_t rotataY = rotationY(y_coordinate_rotate);
    modification(&points, &rotataY);
    s21_remove_matrix(&rotataY);
    
    matrix_t rotataZ = rotationZ(z_coordinate_rotate);
    modification(&points, &rotataZ);
    s21_remove_matrix(&rotataZ);
    
    GG = gtk_drawing_area_new();
    gtk_fixed_put (GTK_FIXED (fixed), GG, 250, 0);
    gtk_widget_set_size_request(GG, 1150, 800);
    g_signal_connect(G_OBJECT(GG), "draw", G_CALLBACK(draw_model), NULL);
    
}


void ScaleAction(GtkWidget *button, gpointer *data) {
    
    g_print("dsfdsfds");
    matrix_t scale_size2 = scale_size(scale_test);
    modification(&points, &scale_size2);
    s21_remove_matrix(&scale_size2);
}

void translateAction(GtkWidget *button, gpointer *data) {
    g_print("dx:%f\n", x_coordinate_translate);
    matrix_t translate =  translation(x_coordinate_translate, y_coordinate_translate, z_coordinate_translate);
    modification(&points, &translate);
    s21_remove_matrix(&translate);
}

void isDigitsValue(GtkWidget *button, gpointer *data) {
        isDigitInputFormat = true;
      gtk_widget_set_sensitive(isFillSettings, false);
      gtk_widget_set_sensitive(isSliderSettings, true);
    hideAllTextView(true);
    hideAllSliders(false);
}

void isSliderValue(GtkWidget *button, gpointer *data) {
    
    translateXSlider = gtk_scale_new_with_range(0, -100.0, 100.0, 1.0);
       gtk_fixed_put (GTK_FIXED (fixed), translateXSlider, 35, 190);
        gtk_scale_set_digits((GtkScale*)translateXSlider, 5.0);
       gtk_widget_set_size_request(translateXSlider, 180, 20);
       g_signal_connect (translateXSlider, "value-changed", G_CALLBACK (transmitTranslateX), NULL);
    
    translateYSlider = gtk_scale_new_with_range(0, 0.0, 1000.0, 10.0);
       gtk_fixed_put (GTK_FIXED (fixed), translateYSlider, 35, 230);
       gtk_widget_set_size_request(translateYSlider, 180, 20);
      
       translateZSlider = gtk_scale_new_with_range(0, 0.0, 1000.0, 10.0);
       gtk_fixed_put (GTK_FIXED (fixed), translateZSlider, 35, 270);
       gtk_widget_set_size_request(translateZSlider, 180, 20);
    
    rotateXSlider = gtk_scale_new_with_range(0, 0.0, 1000.0, 10.0);
    gtk_fixed_put (GTK_FIXED (fixed), rotateXSlider, 35, 400);
    gtk_widget_set_size_request(rotateXSlider, 180, 20);
    
       rotateYSlider = gtk_scale_new_with_range(0, 0.0, 1000.0, 10.0);
       gtk_fixed_put (GTK_FIXED (fixed), rotateYSlider, 35, 440);
       gtk_widget_set_size_request(rotateYSlider, 180, 20);
    
    rotateZSlider = gtk_scale_new_with_range(0, 0.0, 1000.0, 10.0);
          gtk_fixed_put (GTK_FIXED (fixed), rotateZSlider, 35, 480);
          gtk_widget_set_size_request(rotateZSlider, 180, 20);
    
    scaleSlider = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, -10.0, 10.0, 1.0);
    gtk_fixed_put (GTK_FIXED (fixed), scaleSlider, 35, 605);
    gtk_widget_set_size_request(scaleSlider, 180, 20);
    gtk_scale_set_digits((GtkScale*)scaleSlider, 5.0);
    
    g_signal_connect (scaleSlider, "value-changed", G_CALLBACK (transmitScale), NULL);
    
       isDigitInputFormat = false;
      gtk_widget_set_sensitive(isSliderSettings, false);
      gtk_widget_set_sensitive(isFillSettings, true);
    hideAllTextView(false);
    hideAllSliders(true);
}


void settingsAction(GtkWidget *button, gpointer *data) {
   settingsWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
     gtk_window_set_title(GTK_WINDOW(settingsWindow), "Settings");
     gtk_window_set_modal(GTK_WINDOW(settingsWindow), TRUE);
     gtk_window_set_default_size(GTK_WINDOW(settingsWindow), 400, 400);
     gtk_window_set_position(GTK_WINDOW(settingsWindow), GTK_WIN_POS_CENTER);
     gtk_widget_set_name(settingsWindow, "settingsWindow");
     g_signal_connect(G_OBJECT(settingsWindow), "destroy",
                            G_CALLBACK(gtk_main_quit), NULL);
     fix = gtk_fixed_new();
     gtk_container_add(GTK_CONTAINER(settingsWindow), fix);
    
    
    SettingsDrawingArea = gtk_drawing_area_new();
      gtk_fixed_put (GTK_FIXED (fix), SettingsDrawingArea, 0, 0);
      gtk_widget_set_size_request(SettingsDrawingArea, 400, 400);
      gtk_widget_set_name(SettingsDrawingArea, "drae");
      g_signal_connect(G_OBJECT(SettingsDrawingArea), "draw", G_CALLBACK(settingsWindowDraw), NULL);
    
    
    
    isSliderSettings = gtk_button_new_with_label("Слайдеры");
    gtk_fixed_put (GTK_FIXED (fix), isSliderSettings, 70, 70);
    gtk_widget_set_size_request(isSliderSettings, 25, 25);
    gtk_widget_set_name(isSliderSettings, "isSliderSettings");

    isFillSettings = gtk_button_new_with_label("Цифровые значения");
     gtk_fixed_put (GTK_FIXED (fix), isFillSettings, 170, 70);
     gtk_widget_set_size_request(isFillSettings, 25, 25);
     gtk_widget_set_name(isFillSettings, "isFillSettings");
    
    if (isDigitInputFormat) {
          gtk_widget_set_sensitive(isFillSettings, false);
    } else {
        gtk_widget_set_sensitive(isSliderSettings, false);
    }
     g_signal_connect(G_OBJECT(isSliderSettings), "clicked", G_CALLBACK(isSliderValue), NULL);
    
      g_signal_connect(G_OBJECT(isFillSettings), "clicked", G_CALLBACK(isDigitsValue), NULL);
    
    valueLabel = gtk_label_new("Тип управления моделью:");
    gtk_label_set_xalign ((GtkLabel*)valueLabel, 0.02);
    gtk_fixed_put (GTK_FIXED (fix), valueLabel, 110, 20);
    gtk_widget_set_size_request(valueLabel, 50, 50);
    gtk_widget_set_name(valueLabel, "valueLabel");
    
        gtk_widget_show_all(settingsWindow);
       gtk_main();
}

static void on_draw_event(GtkWidget *widget, cairo_t *cr, gpointer data) {
    cairo_set_source_rgb(cr, 0.9, 0.8, 0.3);
    cairo_rectangle(cr, 0, 0, 250, 800);
    cairo_fill(cr);
    
    
    cairo_set_source_rgb(cr, 0.5, 0.9, 0.7);
    cairo_rectangle(cr, 0, 0, 700, 565);
    cairo_fill(cr);
    
    cairo_move_to(cr, 500, 0);
    cairo_line_to(cr, 400, 50);
    cairo_move_to(cr, 500, 0);
    cairo_line_to(cr, 500, 100);
    cairo_move_to(cr, 500, 0);
    cairo_line_to(cr, 600, 50);
    
    cairo_stroke(cr);
}


static void settingsWindowDraw(GtkWidget *widget, cairo_t *cr, gpointer data) {
    cairo_set_source_rgb(cr, 0.1, 0.1, 0.1);
    cairo_rectangle(cr, 0, 0, 250, 800);
    cairo_fill(cr);
    
    
    cairo_set_source_rgb(cr, 0.35, 0.31, 0.71);
    cairo_rectangle(cr, 0, 0, 700, 565);
    cairo_fill(cr);
    
    cairo_move_to(cr, 500, 0);
    cairo_line_to(cr, 400, 50);
    cairo_move_to(cr, 500, 0);
    cairo_line_to(cr, 500, 100);
    cairo_move_to(cr, 500, 0);
    cairo_line_to(cr, 600, 50);
    
    cairo_stroke(cr);
}


static void draw_model(GtkWidget *widget, cairo_t *cr, gpointer data) {
    if (readFile != 0) {
        int width = 1200, height = 700, x_shift = 50, y_shift = 150;
        matrix_t buf = s21_create_matrix(points.rows, 3);
        for (int i = 0; i < points.rows; i++) {
            for (int j = 0; j < 3; j++) {
                buf.matrix[i][j] = points.matrix[i][j];
            }
        }
        matrix_t modif = init_modification_matrix();
        modification(&buf, &modif);
        draw_graph(cr, width, height, &buf);
        gtk_widget_queue_draw(widget);
        s21_remove_matrix(&buf);
        g_print("zashel\n");
    }
}

void draw_graph(cairo_t *cr, int width, int height, matrix_t *buf) {
    g_print("%d\n",plane.rows);
    g_print("%d\n", plane.columns);
    char  tmpV[128] = "Всего вершин:  ";
    char  tmpF[128] = "Всего ребер:  ";
    char v[128];
    char f[128];
    sprintf(v, "%d", plane.rows);
    sprintf(f, "%d", plane.columns);
    strcat(tmpF, f);
    strcat(tmpV, v);
    gtk_label_set_label((GtkLabel*)aboutModelLabelF, tmpF);
    gtk_label_set_label((GtkLabel*)aboutModelLabelV, tmpV);
    double x_start = 500;
    double y_start = 400;
    cairo_translate(cr, x_start, y_start);
    cairo_scale(cr, 1, -1);
    cairo_set_source_rgb(cr, 1, 0.4, 0.7);
    cairo_set_line_width(cr, 0.5);
    int line = 0, k, k1, j1;
    int err = 0;
    int scale = 4;
    for (int i = 0; i < plane.rows; i++) {
        err = 0;
        for (int j = 0; j < plane.columns - 1; j++) {
            k = (int) plane.matrix[i][j] - 1;
            k1 = (int) plane.matrix[i][j + 1] - 1;
            
            if (k1 == -1) {
                k1 = k;
                break;
            }
            cairo_move_to(cr, buf->matrix[k][0], buf->matrix[k][1]);
            cairo_line_to(cr, buf->matrix[k1][0], buf->matrix[k1][1]);
        }
        
        cairo_move_to(cr, buf->matrix[k1][0], buf->matrix[k1][1]);
        cairo_line_to(cr,buf->matrix[(int) plane.matrix[i][0] - 1][0], buf->matrix[(int) plane.matrix[i][0] - 1][1]);
    }
    cairo_stroke(cr);
}

static void transmitTranslateX (GtkRange *range, gpointer data)
{
    x_coordinate_translate = gtk_range_get_value (range);
    g_print("%lf\n", x_coordinate_translate);
       matrix_t translate =  translation(x_coordinate_translate, y_coordinate_translate, z_coordinate_translate);
       modification(&points, &translate);
       s21_remove_matrix(&translate);
}

static void transmitScale (GtkRange *range, gpointer data) {
    g_print("fsaf");
    scale_test = gtk_range_get_value (range);
     matrix_t scale_size2 = scale_size(scale_test);
     modification(&points, &scale_size2);
     s21_remove_matrix(&scale_size2);
}
// MARK: - Support Functions
    /*
        Auxiliary functions with which the program works
     */

void hideAllTextView(bool isHide) {
     gtk_widget_set_visible(textViewOneX, isHide);
     gtk_widget_set_visible(textViewOneY, isHide);
     gtk_widget_set_visible(textViewOneZ, isHide);
    
     gtk_widget_set_visible(textViewTwoX, isHide);
     gtk_widget_set_visible(textViewTwoY, isHide);
     gtk_widget_set_visible(textViewTwoZ, isHide);
    
     gtk_widget_set_visible(scaleTextView, isHide);
     gtk_widget_set_visible(buttonTranslate, isHide);
     gtk_widget_set_visible(buttonRotate, isHide);
     gtk_widget_set_visible(buttonScale, isHide);
}

void hideAllSliders(bool isHide) {
     gtk_widget_set_visible(translateXSlider, isHide);
     gtk_widget_set_visible(translateYSlider, isHide);
     gtk_widget_set_visible(translateZSlider, isHide);
    
     gtk_widget_set_visible(rotateXSlider, isHide);
     gtk_widget_set_visible(rotateYSlider, isHide);
     gtk_widget_set_visible(rotateZSlider, isHide);
    
     gtk_widget_set_visible(scaleSlider, isHide);
}

void get_text_one_x(GtkEntry * e) {
    char tmp[128];
    sprintf(tmp,"%s",gtk_entry_get_text(e));
    x_coordinate_translate = atof(tmp);
    
}

void get_text_one_y(GtkEntry * e) {
    char tmp[128];
    sprintf(tmp,"%s",gtk_entry_get_text(e));
    y_coordinate_translate = atof(tmp);
}

void get_text_one_z(GtkEntry * e) {
    char tmp[128];
    sprintf(tmp,"%s",gtk_entry_get_text(e));
    z_coordinate_translate = atof(tmp);
}

void get_text_two_x(GtkEntry * e) {
    char tmp[128];
    sprintf(tmp,"%s",gtk_entry_get_text(e));
    x_coordinate_rotate = atof(tmp);
}

void get_text_two_y(GtkEntry * e) {
    char tmp[128];
    sprintf(tmp,"%s",gtk_entry_get_text(e));
    y_coordinate_rotate = atof(tmp);
}

void get_text_two_z(GtkEntry * e) {
    char tmp[128];
    sprintf(tmp,"%s",gtk_entry_get_text(e));
    z_coordinate_rotate = atof(tmp);
}

void scaleEntry(GtkEntry * e) {
    char tmp[128];
    sprintf(tmp,"%s",gtk_entry_get_text(e));
    scale_test  = atof(tmp);
}

char *push_char(char *first, char *second, int *point) {
    while (*second != '\0' && *point < 300) {
        first[*point] = *second;
        *point += 1;
        second++;
    }
    first[*point] = '\0';
    return first;
}

char *delete_char(char *first, int *point) {
    if (strlen(first) != 0 && *point != 0) {
        *point -= 1;
        first[*point] = '\0';
    }
    return first;
}

void file(GtkFileChooserButton *f) {
    if (fopen(gtk_file_chooser_get_filename (GTK_FILE_CHOOSER(f)),"r")) {
        file_read(&points, &plane, gtk_file_chooser_get_filename (GTK_FILE_CHOOSER(f)));
        readFile = 1;
    } else {
    }
}

// MARK: - Styles

/*
    This function is needed for parsing styles from a css file
 */

void myCSS(void) {
    GtkCssProvider *provider;
    GdkDisplay *display;
    GdkScreen *screen;
    
    provider = gtk_css_provider_new ();
    display = gdk_display_get_default ();
    screen = gdk_display_get_default_screen (display);
    gtk_style_context_add_provider_for_screen (screen, GTK_STYLE_PROVIDER (provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    
    const gchar *myCssFile = "Styles/mystyle.css";
    GError *error = 0;
    
    gtk_css_provider_load_from_file(provider, g_file_new_for_path(myCssFile), &error);
    g_object_unref (provider);
}

// MARK: - Init Window

/*
    The main function in which the initialization of the window and elements takes place
 */

void init(int argc, char *argv[]) {
    gtk_init(&argc, &argv);
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_widget_set_size_request(GTK_WIDGET(window),1300,800);
    gtk_window_set_title(GTK_WINDOW(window), "3DViewer");
    gtk_widget_set_name(window, "mainWindow");
    g_signal_connect(G_OBJECT(window), "destroy",
                     G_CALLBACK(gtk_main_quit), NULL);
    
    fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window), fixed);
    gtk_widget_set_name(fixed, "fixed");
    
    drawingArea = gtk_drawing_area_new();
    gtk_fixed_put (GTK_FIXED (fixed), drawingArea, 0, 0);
    gtk_widget_set_size_request(drawingArea, 250, 800);
    gtk_widget_set_name(drawingArea, "drae");
    g_signal_connect(G_OBJECT(drawingArea), "draw", G_CALLBACK(on_draw_event), NULL);
    
    DA = gtk_drawing_area_new();
    gtk_fixed_put (GTK_FIXED (fixed), DA, 250, 0);
    gtk_widget_set_size_request(DA, 1150, 800);
    g_signal_connect(G_OBJECT(DA), "draw", G_CALLBACK(draw_model), NULL);
    mainlabel = gtk_label_new("3DViewer");
    
    gtk_label_set_xalign ((GtkLabel*)mainlabel, 0.02);
    gtk_fixed_put (GTK_FIXED (fixed), mainlabel, 75, 5);
    gtk_widget_set_size_request(mainlabel, 50, 50);
    gtk_widget_set_name(mainlabel, "mainlabel");

        
    modellabel = gtk_label_new("Model");
    gtk_label_set_xalign ((GtkLabel*)modellabel, 0.02);
    gtk_fixed_put (GTK_FIXED (fixed), modellabel, 90, 50);
    gtk_widget_set_size_request(modellabel, 50, 50);
    gtk_widget_set_name(modellabel, "modellabel");
    

    aboutModelLabelV = gtk_label_new(" ");
    gtk_label_set_xalign ((GtkLabel*)aboutModelLabelV, 0.02);
    gtk_fixed_put (GTK_FIXED (fixed), aboutModelLabelV, 60, 690);
    gtk_widget_set_size_request(aboutModelLabelV, 50, 50);
    gtk_widget_set_name(aboutModelLabelV, "aboutModelLabelV");
    
    aboutModelLabelF = gtk_label_new(" ");
       gtk_label_set_xalign ((GtkLabel*)aboutModelLabelF, 0.02);
       gtk_fixed_put (GTK_FIXED (fixed), aboutModelLabelF, 60, 710);
       gtk_widget_set_size_request(aboutModelLabelF, 50, 50);
       gtk_widget_set_name(aboutModelLabelF, "aboutModelLabelF");
    
    
    translateLabel = gtk_label_new("Translate");
    gtk_label_set_xalign ((GtkLabel*)translateLabel, 0.02);
    gtk_fixed_put (GTK_FIXED (fixed), translateLabel, 85, 140);
    gtk_widget_set_size_request(translateLabel, 50, 50);
    gtk_widget_set_name(translateLabel, "translateLabel");
    
    
    settingsButton = gtk_button_new();
    gtk_fixed_put (GTK_FIXED (fixed), settingsButton, 98, 760);
    gtk_widget_set_size_request(settingsButton, 25, 25);
    gtk_widget_set_name(settingsButton, "settingsButton");
    GtkWidget *image = gtk_image_new_from_file("Styles/settings.png");
    gtk_button_set_image((GtkButton*)settingsButton, image);
    
    
    file_chooser_button = gtk_file_chooser_button_new("Choose", GTK_FILE_CHOOSER_ACTION_OPEN);
    gtk_fixed_put (GTK_FIXED (fixed), file_chooser_button, 10, 100);
    gtk_widget_set_size_request(file_chooser_button, 230, 25);
    gtk_widget_set_name(file_chooser_button, "file_chooser_button");
    g_signal_connect(G_OBJECT(file_chooser_button), "file-set", G_CALLBACK(file), NULL);
    
    double startAxis = 195;
    
    for (int i = 0; i < 3; i++) {
        axisLabel = gtk_label_new(axis[i]);
        gtk_label_set_xalign ((GtkLabel*)axisLabel, 0.02);
        gtk_fixed_put (GTK_FIXED (fixed), axisLabel, 10,startAxis);
        gtk_widget_set_size_request(axisLabel, 5, 5);
        startAxis += 40;
    }

    textViewOneX = gtk_entry_new();
    gtk_fixed_put (GTK_FIXED (fixed), textViewOneX, 35, 190);
    gtk_widget_set_size_request(textViewOneX, 180, 20);
    
    textViewOneY = gtk_entry_new();
    gtk_fixed_put (GTK_FIXED (fixed), textViewOneY, 35, 230);
    gtk_widget_set_size_request(textViewOneY, 180, 20);
    
    textViewOneZ = gtk_entry_new();
    gtk_fixed_put (GTK_FIXED (fixed), textViewOneZ, 35, 270);
    gtk_widget_set_size_request(textViewOneZ, 180, 20);
    
    buttonTranslate = gtk_button_new_with_label("Translate");
    gtk_fixed_put (GTK_FIXED (fixed), buttonTranslate, 80, 315);
    gtk_widget_set_size_request(buttonTranslate, 60, 20);
    gtk_widget_set_name(buttonTranslate, "buttonTranslate");
    
    rotateLabel = gtk_label_new("Rotate");
    gtk_label_set_xalign ((GtkLabel*)rotateLabel, 0.02);
    gtk_fixed_put (GTK_FIXED (fixed), rotateLabel, 92, 348);
    gtk_widget_set_size_request(rotateLabel, 50, 50);
    gtk_widget_set_name(rotateLabel, "rotatelabel");
    
    double startAxisTwo = 405;
    
    for (int i = 0; i < 3; i++) {
        axisLabel = gtk_label_new(axis[i]);
        gtk_label_set_xalign ((GtkLabel*)axisLabel, 0.02);
        gtk_fixed_put (GTK_FIXED (fixed), axisLabel, 10,startAxisTwo);
        gtk_widget_set_size_request(axisLabel, 5, 5);
        startAxisTwo += 40;
    }
    
    textViewTwoX = gtk_entry_new();
    gtk_fixed_put (GTK_FIXED (fixed), textViewTwoX, 35, 400);
    gtk_widget_set_size_request(textViewTwoX, 180, 20);
    
    textViewTwoY = gtk_entry_new();
    gtk_fixed_put (GTK_FIXED (fixed), textViewTwoY, 35, 440);
    gtk_widget_set_size_request(textViewTwoY, 180, 20);
    //
    textViewTwoZ = gtk_entry_new();
    gtk_fixed_put (GTK_FIXED (fixed), textViewTwoZ, 35, 480);
    gtk_widget_set_size_request(textViewTwoZ, 180, 20);
    //
    buttonRotate = gtk_button_new_with_label("Rotate");
    gtk_fixed_put (GTK_FIXED (fixed), buttonRotate, 85, 525);
    gtk_widget_set_size_request(buttonRotate, 60, 20);
    gtk_widget_set_name(buttonRotate, "buttonRotate");
    //
    scaleLabel = gtk_label_new("Scale");
    gtk_label_set_xalign ((GtkLabel*)scaleLabel, 0.02);
    gtk_fixed_put (GTK_FIXED (fixed), scaleLabel, 102, 555);
    gtk_widget_set_size_request(scaleLabel, 50, 50);
    gtk_widget_set_name(scaleLabel, "scaleLabel");
    
    

    scaleTextView = gtk_entry_new();
    gtk_fixed_put (GTK_FIXED (fixed), scaleTextView, 35, 605);
    gtk_widget_set_size_request(scaleTextView, 180, 20);
    
    buttonScale = gtk_button_new_with_label("Scale");
    gtk_fixed_put (GTK_FIXED (fixed), buttonScale, 90, 650);
    gtk_widget_set_size_request(buttonScale, 60, 20);
    gtk_widget_set_name(buttonScale, "buttonScale");
   
    g_signal_connect(G_OBJECT(buttonRotate), "clicked", G_CALLBACK(rotateAction), NULL);
    g_signal_connect(G_OBJECT(buttonScale), "clicked", G_CALLBACK(ScaleAction), NULL);
    g_signal_connect(G_OBJECT(buttonTranslate), "clicked", G_CALLBACK(translateAction), NULL);
    g_signal_connect(G_OBJECT(textViewOneX), "changed", G_CALLBACK(get_text_one_x), NULL);
    g_signal_connect(G_OBJECT(textViewOneY), "changed", G_CALLBACK(get_text_one_y), NULL);
    g_signal_connect(G_OBJECT(textViewOneZ), "changed", G_CALLBACK(get_text_one_z), NULL);
    g_signal_connect(G_OBJECT(textViewTwoX), "changed", G_CALLBACK(get_text_two_x), NULL);
    g_signal_connect(G_OBJECT(textViewTwoY), "changed", G_CALLBACK(get_text_two_y), NULL);
    g_signal_connect(G_OBJECT(textViewTwoZ), "changed", G_CALLBACK(get_text_two_z), NULL);
    g_signal_connect(G_OBJECT(scaleTextView), "changed", G_CALLBACK(scaleEntry), NULL);
       g_signal_connect(G_OBJECT(settingsButton), "clicked", G_CALLBACK(settingsAction), NULL);
    myCSS();
    gtk_widget_show_all(GTK_WIDGET(window));
    gtk_main();
}
