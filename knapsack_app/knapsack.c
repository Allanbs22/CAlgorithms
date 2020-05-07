#include <stdlib.h>
#include <stdio.h>
#include <gtk/gtk.h>
#include <string.h>

static GtkWidget *spinButton, *ruta, *spinButton2;
int cantObj;
int tamMochila = 0;




void ventanaPrincipal();




/*
*E:Dummy y widget del que se viene
*S:Ventana anterior cerrada y ventana principal abierta
*R:Ninguna
*O:Volver a la ventana principal desde cualquier parte
*/
void volverAPrincipal(GtkWidget *dummy, gpointer widget){
    //cierra la ventana anterior
    gtk_widget_hide(widget);
    gtk_main_quit();
    //abre la ventana principal
    ventanaPrincipal();
}



//estructura para almacenar los objetos.
struct objeto 
{
     int peso;
     int valor;
     int existentes; //-1 es igual a infinito
};

//estructura para determinar la tabla
struct campo{
    int val;
    int cant;
    char color;//'r' = rojo y 'v' = verde
};





#include "ventanasResolucion.h"
#include "recepcionDatos.h"
#include "cargarDatos.h"

/*
*E:Ninguna
*S:Ventana principal abierta
*R:Ninguna
*O:Abrir la ventana principal
*/
void ventanaPrincipal(){
	//definición de widgets de la ventana
    GtkWidget *window, *wallpaper, *fixed, *btnCargar, *btnResolver, *lblMensaje;

    //creación de la ventana y asignación del botón de cerrar
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    
    //configuración de ventana
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_title(GTK_WINDOW(window), "Ventana Principal");
    gtk_window_set_default_size(GTK_WINDOW(window),700,550);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);

    //fondo de pantalla y marco
    wallpaper = gtk_image_new_from_file("wallpaper.jpg");
    fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window),fixed);
    gtk_fixed_put(GTK_FIXED(fixed), wallpaper, 0, 0);

    //Creación y configuración del label de mensaje
    lblMensaje = gtk_label_new("Indique si desea resolver un problema o cargar uno ya existente:");
    gtk_fixed_put(GTK_FIXED(fixed), lblMensaje, 50, 100);

    //Creación y configuración del botón de ir
    btnResolver = gtk_button_new_with_label("");
    g_signal_connect(btnResolver, "clicked", G_CALLBACK(ventanaCantidad), (gpointer) window);
    gtk_fixed_put(GTK_FIXED(fixed), btnResolver, 250, 200);
    GtkWidget *imgResolver = gtk_image_new_from_file("button_resolver.png");
    gtk_button_set_always_show_image(GTK_BUTTON(btnResolver),TRUE);
    gtk_button_set_image(GTK_BUTTON(btnResolver), imgResolver);


    //Creación y configuración del botón de ir
    btnCargar = gtk_button_new_with_label("");
    g_signal_connect(btnCargar, "clicked", G_CALLBACK(ventanaCargar), (gpointer) window);
    gtk_fixed_put(GTK_FIXED(fixed), btnCargar, 250, 300);
    GtkWidget *imgCargar = gtk_image_new_from_file("button_cargar-archivo.png");
    gtk_button_set_always_show_image(GTK_BUTTON(btnCargar),TRUE);
    gtk_button_set_image(GTK_BUTTON(btnCargar), imgCargar);

    //configuración final
    gtk_widget_show_all(window);
    gtk_main();

    
}

// gcc knapsack.c -o knapsack `pkg-config --cflags gtk+-3.0` `pkg-config --libs gtk+-3.0`
int main(int argc, char **argv) {
    gtk_init(&argc, &argv);
    ventanaPrincipal();
    return 0;
}