#include <stdlib.h>
#include <stdio.h>
#include <gtk/gtk.h>

/*
    E:Ninguna
    S:Aplicación correspondiente abierta
    R:La aplicación a abrir debe existir
    O:Abrir la aplicación del botón, de caso contrario, abrir la aplicación pending
*/
void execute_routes(){
    if(fork()==0){
        int status = system("cd routes_app && ./routes");
        if(status>0)
            system("cd pending_app && ./pending");
        exit(0);
    }
}

/*
    E:Ninguna
    S:Aplicación correspondiente abierta
    R:La aplicación a abrir debe existir
    O:Abrir la aplicación del botón, de caso contrario, abrir la aplicación pending
*/
void execute_mochila(){
    if(fork()==0){
        int status = system("cd knapsack_app && ./knapsack");
        if(status>0)
            system("cd pending_app && ./pending");
        exit(0);
    }
}

/*
    E:Ninguna
    S:Aplicación correspondiente abierta
    R:La aplicación a abrir debe existir
    O:Abrir la aplicación del botón, de caso contrario, abrir la aplicación pending
*/
void execute_Equipos(){
    if(fork()==0){
        int status = system("cd reemplazo_app && ./reemplazo");
        if(status>0)
            system("cd pending_app && ./pending");
        exit(0);
    }
}

/*
    E:Ninguna
    S:Aplicación correspondiente abierta
    R:La aplicación a abrir debe existir
    O:Abrir la aplicación del botón, de caso contrario, abrir la aplicación pending
*/
void execute_Arboles(){
    if(fork()==0){
        int status = system("cd arboles_app && ./arboles");
        if(status>0)
            system("cd pending_app && ./pending");
        exit(0);
    }
}

/*
    E:Ninguna
    S:Aplicación correspondiente abierta
    R:La aplicación a abrir debe existir
    O:Abrir la aplicación del botón, de caso contrario, abrir la aplicación pending
*/
void execute_Series(){
    if(fork()==0){
        int status = system("cd series_app && ./series");
        if(status>0)
            system("cd pending_app && ./pending");
        exit(0);
    }
}

/*
    E:Ninguna
    S:Aplicación correspondiente abierta
    R:La aplicación a abrir debe existir
    O:Abrir la aplicación del botón, de caso contrario, abrir la aplicación pending
*/
void execute_Matrices(){
    if(fork()==0){
        int status = system("cd matrices_app && ./matrices");
        if(status>0)
            system("cd pending_app && ./pending");
        exit(0);
    }
}


void crearVentana(){

    //definición de widgets de la ventana
    GtkWidget *window, *wallpaper, *fixed, *btnRutas, *btnMochila, *btnEquipos, *btnArboles, *btnSeries, *btnMatrices, *btnSalir;

    //creación de la ventana y asignación del botón de cerrar
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    
    //configuración de ventana
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_title(GTK_WINDOW(window), "Menú principal");
    gtk_window_set_default_size(GTK_WINDOW(window),700,550);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);

    //fondo de pantalla y marco
    wallpaper = gtk_image_new_from_file("wallpaper.jpg");
    fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window),fixed);
    gtk_fixed_put(GTK_FIXED(fixed), wallpaper, 0, 0);

    //Creación y configuración del botón de rutas
    btnRutas = gtk_button_new_with_label("");
    g_signal_connect(btnRutas, "clicked", G_CALLBACK(execute_routes), NULL);
    gtk_fixed_put(GTK_FIXED(fixed), btnRutas, 50, 50);
    GtkWidget *imgRutas = gtk_image_new_from_file("button_rutas-mas-cortas.png");
    gtk_button_set_always_show_image(GTK_BUTTON(btnRutas),TRUE);
    gtk_button_set_image(GTK_BUTTON(btnRutas), imgRutas);
    gtk_widget_set_tooltip_text(btnRutas, "Algoritmo para encontrar el camino más corto entre dos nodos de un grafo");

    //Creación y configuración del botón de mochila
    btnMochila = gtk_button_new_with_label("");
    g_signal_connect(btnMochila, "clicked", G_CALLBACK(execute_mochila), NULL);
    gtk_fixed_put(GTK_FIXED(fixed), btnMochila, 50, 120);
    GtkWidget *imgMochila = gtk_image_new_from_file("button_problema-de-la-mochila.png");
    gtk_button_set_always_show_image(GTK_BUTTON(btnMochila),TRUE);
    gtk_button_set_image(GTK_BUTTON(btnMochila), imgMochila);
    gtk_widget_set_tooltip_text(btnMochila, "Algoritmo para llenar una mochila de capacidad limitada con distintos\nobjetos de forma óptima");

    //Creación y configuración del botón de equipos
    btnEquipos = gtk_button_new_with_label("");
    g_signal_connect(btnEquipos, "clicked", G_CALLBACK(execute_Equipos), NULL);
    gtk_fixed_put(GTK_FIXED(fixed), btnEquipos, 50, 190);
    GtkWidget *imgEquipos = gtk_image_new_from_file("button_reemplazo-de-equipos.png");
    gtk_button_set_always_show_image(GTK_BUTTON(btnEquipos),TRUE);
    gtk_button_set_image(GTK_BUTTON(btnEquipos), imgEquipos);
    gtk_widget_set_tooltip_text(btnEquipos, "Algoritmo que calcula el plan reemplazos óptimo de un equipo en un periodo\nde tiempo determinado");

    //Creación y configuración del botón de arboles
    btnArboles = gtk_button_new_with_label("");
    g_signal_connect(btnArboles, "clicked", G_CALLBACK(execute_Arboles), NULL);
    gtk_fixed_put(GTK_FIXED(fixed), btnArboles, 50, 260);
    GtkWidget *imgArboles = gtk_image_new_from_file("button_arboles-binarios-de-busqueda-optimos.png");
    gtk_button_set_always_show_image(GTK_BUTTON(btnArboles),TRUE);
    gtk_button_set_image(GTK_BUTTON(btnArboles), imgArboles);
    gtk_widget_set_tooltip_text(btnArboles, "Algoritmo que ordena una lista de nodos para crear un árbol binario de búsqueda óptimo");

    //Creación y configuración del botón de series
    btnSeries = gtk_button_new_with_label("");
    g_signal_connect(btnSeries, "clicked", G_CALLBACK(execute_Series), NULL);
    gtk_fixed_put(GTK_FIXED(fixed), btnSeries, 50, 330);
    GtkWidget *imgSeries = gtk_image_new_from_file("button_series-deportivas.png");
    gtk_button_set_always_show_image(GTK_BUTTON(btnSeries),TRUE);
    gtk_button_set_image(GTK_BUTTON(btnSeries), imgSeries);
    gtk_widget_set_tooltip_text(btnSeries, "Algoritmo que calcula la probabilidad de que un equipo gane un juego de múltiples series");

    //Creación y configuración del botón de matrices
    btnMatrices = gtk_button_new_with_label("");
    g_signal_connect(btnMatrices, "clicked", G_CALLBACK(execute_Matrices), NULL);
    gtk_fixed_put(GTK_FIXED(fixed), btnMatrices, 50, 400);
    GtkWidget *imgMatrices = gtk_image_new_from_file("button_multiplicacion-de-matrices.png");
    gtk_button_set_always_show_image(GTK_BUTTON(btnMatrices),TRUE);
    gtk_button_set_image(GTK_BUTTON(btnMatrices), imgMatrices);
    gtk_widget_set_tooltip_text(btnMatrices, "Algoritmo que calcula el orden óptimo a la hora de hacer múltiples multiplicaciones de matrices");

    //Creación y configuración del botón de salir
    btnSalir = gtk_button_new_with_label("");
    g_signal_connect(btnSalir, "clicked", G_CALLBACK(gtk_main_quit), NULL);
    gtk_fixed_put(GTK_FIXED(fixed), btnSalir, 50, 470);
    GtkWidget *imgSalir = gtk_image_new_from_file("button_salir-del-programa.png");
    gtk_button_set_always_show_image(GTK_BUTTON(btnSalir),TRUE);
    gtk_button_set_image(GTK_BUTTON(btnSalir), imgSalir);
    gtk_widget_set_tooltip_text(btnSalir, "Salir del programa");

    //configuración final
    gtk_widget_show_all(window);
    gtk_main();
}

// gcc menu.c -o menu `pkg-config --cflags gtk+-3.0` `pkg-config --libs gtk+-3.0`
int main(int argc, char **argv) {
    
    gtk_init(&argc, &argv);

    crearVentana();

    return 0;
}