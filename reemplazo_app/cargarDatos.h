
/*
*E:Widget
*S:File dialog abierto y archivo cargado en label
*R:Archivo debe ser válido
*O:Cargar un archivo externo con una tabla
*/
void cargarArchivo(GtkWidget *dummy, gpointer widget){
	GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
	GtkWidget *dialog = gtk_file_chooser_dialog_new ("Open File",widget,action,("_Cancel"),GTK_RESPONSE_CANCEL,("_Open"),GTK_RESPONSE_ACCEPT,NULL);
	gint res = gtk_dialog_run (GTK_DIALOG (dialog));
	if (res == GTK_RESPONSE_ACCEPT){
	    char *filename;
	    GtkFileChooser *chooser = GTK_FILE_CHOOSER (dialog);
	    filename = gtk_file_chooser_get_filename (chooser);
	    gtk_entry_set_text(GTK_ENTRY(ruta), filename);
	}
	gtk_widget_destroy (dialog);
}

void cargador(GtkWidget *dummy,gpointer widget){
    char nombre[255];
    memcpy(nombre,(char *)gtk_entry_get_text (GTK_ENTRY (ruta)),255*sizeof(char));
    if(strcmp(nombre,"") != 0){
        FILE *archivo = fopen(nombre,"r");
        char linea[255];
        fgets(linea,255,archivo);
        char *parte;
        char *parte2;
        parte = strtok(linea,"\n");
        parte2 = strtok(parte,",");
        costoInicial = atoi(parte2);
        parte2 = strtok(NULL,",");
        vidaUtil = atoi(parte2);
        parte2 = strtok(NULL,",");
        inflacion = atoi(parte2);
        parte2 = strtok(NULL,",");
        plazo = atoi(parte2);
        fclose(archivo);
        ventanaIngresarValores(dummy,widget);
    }
}

/*
*E:Widget
*S:Ventana del widget cerrada y ventana de carga abierta
*R:Ninguna
*O:Abrir la ventana de carga
*/
void ventanaCargar(GtkWidget *dummy, gpointer widget){

	vidaUtil = -1;
    plazo = -1; 
	inflacion = -1; 
	costoInicial = -1;
	
	//cierra la ventana anterior
	gtk_widget_hide(widget);
	gtk_main_quit();
	//definición de widgets de la ventana
    GtkWidget *window, *wallpaper, *fixed, *btnCargar, *lblMensaje, *btnVolver, *btnLeer;
	
    //creación de la ventana y asignación del botón de cerrar
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    
    //configuración de ventana
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_title(GTK_WINDOW(window), "Indique la ruta del archivo");
    gtk_window_set_default_size(GTK_WINDOW(window),700,550);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);

    //fondo de pantalla y marco
    wallpaper = gtk_image_new_from_file("wallpaper.jpg");
    fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window),fixed);
    gtk_fixed_put(GTK_FIXED(fixed), wallpaper, 0, 0);

    //Creación y configuración del label de mensaje
    lblMensaje = gtk_label_new("Por favor indique la ruta del archivo con el que desea trabajar:");
    gtk_fixed_put(GTK_FIXED(fixed), lblMensaje, 50, 100);

    //Creación y configuración del entry de tamaño
    ruta = gtk_entry_new();
    gtk_fixed_put(GTK_FIXED(fixed), ruta, 50, 120);
    gtk_widget_set_size_request(ruta,30,30);
    gtk_widget_set_can_focus(GTK_WIDGET(ruta), FALSE);


    //Creación y configuración del botón de leer archivo
    btnLeer = gtk_button_new_with_label("");
    g_signal_connect(btnLeer, "clicked", G_CALLBACK(cargarArchivo), (gpointer) window);
    gtk_fixed_put(GTK_FIXED(fixed), btnLeer, 215, 120);
    GtkWidget *imgLeer = gtk_image_new_from_file("button.png");
    gtk_button_set_always_show_image(GTK_BUTTON(btnLeer),TRUE);
    gtk_button_set_image(GTK_BUTTON(btnLeer), imgLeer);

    //Creación y configuración del botón de cargar
    btnCargar = gtk_button_new_with_label("");
    g_signal_connect(btnCargar, "clicked", G_CALLBACK(cargador), (gpointer) window);
    g_object_set_data(G_OBJECT(btnCargar),"modo","cargar");
    gtk_fixed_put(GTK_FIXED(fixed), btnCargar, 250, 290);
    GtkWidget *imgCargar = gtk_image_new_from_file("button_cargar.png");
    gtk_button_set_always_show_image(GTK_BUTTON(btnCargar),TRUE);
    gtk_button_set_image(GTK_BUTTON(btnCargar), imgCargar);


    //Creación y configuración del botón de volver
    btnVolver = gtk_button_new_with_label("");
    g_signal_connect(btnVolver, "clicked", G_CALLBACK(volverAPrincipal), (gpointer) window);
    gtk_fixed_put(GTK_FIXED(fixed), btnVolver, 450, 480);
    GtkWidget *imgVolver = gtk_image_new_from_file("button_volver.png");
    gtk_button_set_always_show_image(GTK_BUTTON(btnVolver),TRUE);
    gtk_button_set_image(GTK_BUTTON(btnVolver), imgVolver);

    //configuración final
    gtk_widget_show_all(window);
    gtk_main();
}