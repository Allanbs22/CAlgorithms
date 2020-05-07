#include <stdlib.h>
#include <stdio.h>
#include <gtk/gtk.h>
#include <string.h>

static GtkWidget *ruta;
gpointer entradas[99];
int valoresEntradas[99];
int cantE;
int houseG,visitG;
gpointer nombres[99];
gpointer pesos[99];


struct nodo{
    char nombre[255];
    float  peso;
};

void ventanaIngresarValores();



void volverAPrincipal(GtkWidget *dummy, gpointer widget){
	//cierra la ventana anterior
    gtk_widget_hide(widget);
    gtk_main_quit();
	ventanaIngresarValores();
}



#include "algoritmo.c"
#include "ventanasResolucion.h"
#include "recepcionDatos.h"



// gcc arboles.c -o arboles `pkg-config --cflags gtk+-3.0` `pkg-config --libs gtk+-3.0`
int main(int argc, char **argv) {
    gtk_init(&argc, &argv);
    
    ventanaIngresarValores();
    return 0;
}