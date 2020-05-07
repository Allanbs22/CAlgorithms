void agregarEntrys(GtkWidget *dummy, gpointer widget){
    GtkWidget *windowValores = g_object_get_data(G_OBJECT(dummy), "ventana");
    GtkWidget *fixInfo = gtk_fixed_new();
    char *modo;
    modo = g_object_get_data(G_OBJECT(dummy), "modo");
    if(strcmp(modo,"cargar") != 0){
        cantE  = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON(g_object_get_data(G_OBJECT(dummy), "cantidad")));
        for(int i=0;i<cantE;i++){
            valoresEntradas[i]=0;
            char texto[50];
            sprintf(texto,"%i: Nombre:",i+1);
            //Creación y configuración del label de probabilidad visita
            GtkWidget *lblNombre = gtk_label_new(texto);
            gtk_fixed_put(GTK_FIXED(fixInfo), lblNombre, 5, 40*i);

            GtkWidget *name = gtk_entry_new();
            gtk_fixed_put(GTK_FIXED(fixInfo), name, 85, 40*i);

            sprintf(texto,"Peso:");
            //Creación y configuración del label de probabilidad visita
            GtkWidget *lblPeso = gtk_label_new(texto);
            gtk_fixed_put(GTK_FIXED(fixInfo), lblPeso, 260, 40*i);


            GtkWidget *spinPeso = gtk_spin_button_new_with_range  (0, 99999, 0.01);
            gtk_fixed_put(GTK_FIXED(fixInfo), spinPeso, 310, 40*i);
            gtk_spin_button_configure (GTK_SPIN_BUTTON(spinPeso),NULL,0.01,2);


            nombres[i] = (gpointer)name;
            pesos[i] = (gpointer)spinPeso;
        }
    }
    else{
        char nombre[255];
        struct nodo lista[cantE];
        memcpy(nombre,(char *)gtk_entry_get_text (GTK_ENTRY (ruta)),255*sizeof(char));
        FILE *archivo = fopen(nombre,"r");
        char linea[255];
        fgets(linea,255,archivo);
        char *parte;
        parte = strtok(linea,"\n");
        for(int i=0;i<cantE;i++){
            fgets(linea,255,archivo);
            parte = strtok(linea,"-");
            sprintf(lista[i].nombre,"%s",parte);
            parte = strtok(NULL,"-");
            lista[i].peso = atof(parte);
           
        }
        fclose(archivo);
        for(int i=0;i<cantE;i++){
            valoresEntradas[i]=0;
            char texto[50];
            sprintf(texto,"%i: Nombre:",i+1);
            //Creación y configuración del label de probabilidad visita
            GtkWidget *lblNombre = gtk_label_new(texto);
            gtk_fixed_put(GTK_FIXED(fixInfo), lblNombre, 5, 40*i);

            GtkWidget *name = gtk_entry_new();
            gtk_entry_set_text(GTK_ENTRY(name),lista[i].nombre);
            gtk_fixed_put(GTK_FIXED(fixInfo), name, 85, 40*i);

            sprintf(texto,"Peso:");
            //Creación y configuración del label de probabilidad visita
            GtkWidget *lblPeso = gtk_label_new(texto);
            gtk_fixed_put(GTK_FIXED(fixInfo), lblPeso, 260, 40*i);


            GtkWidget *spinPeso = gtk_spin_button_new_with_range  (0, 99999, 0.01);
            gtk_spin_button_set_value (GTK_SPIN_BUTTON(spinPeso),lista[i].peso);
            gtk_fixed_put(GTK_FIXED(fixInfo), spinPeso, 310, 40*i);
            gtk_spin_button_configure (GTK_SPIN_BUTTON(spinPeso),NULL,0.01,2);


            nombres[i] = (gpointer)name;
            pesos[i] = (gpointer)spinPeso;
        }
    }
    GtkWidget *scrolled_window = gtk_scrolled_window_new (NULL, NULL);
    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window),GTK_POLICY_AUTOMATIC,GTK_POLICY_AUTOMATIC);

    //define color de fondo de la ventana
    GdkColor color;
    gdk_color_parse("#FFFFFF", &color);
    gtk_widget_modify_bg(scrolled_window, GTK_STATE_NORMAL, &color);
    gtk_widget_set_size_request (scrolled_window, 455, 200);
    gtk_container_add(GTK_CONTAINER(scrolled_window),fixInfo);
    gtk_fixed_put(GTK_FIXED(widget),scrolled_window, 735, 230);
    gtk_widget_show_all(windowValores);
    
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
        cantE = atoi(parte2);
        fclose(archivo);
        agregarEntrys(dummy,widget);
    }
}

void enviarAVentanaResultados(GtkWidget *dummy, gpointer widget){
    if(cantE>0){

        struct nodo elementos[cantE];
        for(int i=0;i<cantE;i++){
            elementos[i].peso = gtk_spin_button_get_value (GTK_SPIN_BUTTON(pesos[i]));
            sprintf(elementos[i].nombre,"%s",gtk_entry_get_text (GTK_ENTRY (nombres[i])));
        }
        ventanaResultados(dummy,widget,elementos);
    }
}


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

void guardar1(GtkWidget *dummy, gpointer entrada){
    struct nodo lista[cantE];
    for(int i=0;i<cantE;i++){
        lista[i].peso = gtk_spin_button_get_value (GTK_SPIN_BUTTON(pesos[i]));
        sprintf(lista[i].nombre,"%s",gtk_entry_get_text (GTK_ENTRY (nombres[i])));
    }
    char nombre[255];
    sprintf(nombre,"%s",(char *)gtk_entry_get_text(entrada));
    char texto[15000];
    if(strcmp(nombre,"") != 0){
        strcat(nombre,".ha");
        FILE *archivo = fopen(nombre,"w");
        sprintf(texto,"%d\n",cantE);
        for(int i=0;i<cantE;i++){
            char buffer[255];
            sprintf(buffer,"%s-%f\n",lista[i].nombre,lista[i].peso);
            strcat(texto,buffer);
        }
        fputs(texto,archivo);
        fclose(archivo);
    }
}

/*
*E:Widget
*S:Ventana del widget cerrada y ventana de ingresar valores abierta
*R:Ninguna
*O:Abrir la ventana de ingresar valores
*/
void ventanaIngresarValores(){
	cantE = 0;
	//fondo de pantalla
	GtkWidget *wallpaper, *logo, *fixed, *scrolled_window, *btnSiguiente, *windowValores, *btnLeer, *btnCargar, *btnGuardar, *nombreArchivo, *btnActualizar;
	windowValores = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(windowValores, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    
    //configuración de ventana
    gtk_window_set_position(GTK_WINDOW(windowValores), GTK_WIN_POS_CENTER);
    gtk_window_set_title(GTK_WINDOW(windowValores), "Indique los valores deseados");
    gtk_window_set_default_size(GTK_WINDOW(windowValores),1300,750);
    gtk_window_set_resizable(GTK_WINDOW(windowValores), FALSE);

    //fondo de pantalla y marco
    wallpaper = gtk_image_new_from_file("wallpaper.jpg");
    fixed = gtk_fixed_new();
    gtk_fixed_put(GTK_FIXED(fixed), wallpaper, 0, 0);


    logo = gtk_image_new_from_file("logo.jpg");
    gtk_fixed_put(GTK_FIXED(fixed), logo, 125, 10);

    GtkWidget *frame1 = gtk_frame_new("Lectura/Escritura");
    gtk_fixed_put(GTK_FIXED(fixed),frame1,40,200);
    gtk_widget_set_size_request(frame1,250,250);


    //Creación y configuración del entry de tamaño
    ruta = gtk_entry_new();
    gtk_fixed_put(GTK_FIXED(fixed), ruta, 50, 220);
    gtk_widget_set_size_request(ruta,30,30);
    gtk_widget_set_can_focus(GTK_WIDGET(ruta), FALSE);


    //Creación y configuración del botón de leer archivo
    btnLeer = gtk_button_new_with_label("");
    g_signal_connect(btnLeer, "clicked", G_CALLBACK(cargarArchivo), (gpointer) windowValores);
    gtk_fixed_put(GTK_FIXED(fixed), btnLeer, 215, 220);
    GtkWidget *imgLeer = gtk_image_new_from_file("button.png");
    gtk_button_set_always_show_image(GTK_BUTTON(btnLeer),TRUE);
    gtk_button_set_image(GTK_BUTTON(btnLeer), imgLeer);


    //Creación y configuración del entry de tamaño
    nombreArchivo = gtk_entry_new();
    gtk_fixed_put(GTK_FIXED(fixed), nombreArchivo, 70, 335);
    gtk_widget_set_size_request(nombreArchivo,30,30);

    //Creación y configuración del botón de guardar
    btnGuardar = gtk_button_new_with_label("");
    g_signal_connect(btnGuardar, "clicked", G_CALLBACK(guardar1), (gpointer) nombreArchivo);
    g_object_set_data(G_OBJECT(btnGuardar),"nombre",(gpointer)nombreArchivo);
    gtk_fixed_put(GTK_FIXED(fixed), btnGuardar, 50, 375);
    GtkWidget *imgGuardar = gtk_image_new_from_file("button_guardar.png");
    gtk_button_set_always_show_image(GTK_BUTTON(btnGuardar),TRUE);
    gtk_button_set_image(GTK_BUTTON(btnGuardar), imgGuardar);

    GtkWidget *frame2 = gtk_frame_new("Nodos");
    gtk_fixed_put(GTK_FIXED(fixed),frame2,315,200);
    gtk_widget_set_size_request(frame2,350,250);


    //Creación y configuración del label de mensaje
    GtkWidget *lblNodos = gtk_label_new("Número de nodos:");
    gtk_fixed_put(GTK_FIXED(fixed), lblNodos, 335, 235);


    //creación y configuración de spin button
    GtkWidget *spinNodos = gtk_spin_button_new_with_range  (2, 99,1);
    gtk_fixed_put(GTK_FIXED(fixed), spinNodos, 535, 235);


     //Creación y configuración del botón de cargar
    btnCargar = gtk_button_new_with_label("");
    //g_signal_connect(btnCargar, "clicked", G_CALLBACK(leer_archivo), (gpointer) fixed);
    //g_object_set_data(G_OBJECT(btnCargar),"modo","cargar");
    gtk_fixed_put(GTK_FIXED(fixed), btnCargar, 50, 260);
    GtkWidget *imgCargar = gtk_image_new_from_file("button_cargar.png");
    g_signal_connect(btnCargar, "clicked", G_CALLBACK(cargador),(gpointer) fixed);
    g_object_set_data(G_OBJECT(btnCargar),"ventana",(gpointer) windowValores);
    g_object_set_data(G_OBJECT(btnCargar),"modo","cargar");
    gtk_button_set_always_show_image(GTK_BUTTON(btnCargar),TRUE);
    gtk_button_set_image(GTK_BUTTON(btnCargar), imgCargar);


    //Creación y configuración del botón de actualizar
    btnActualizar = gtk_button_new_with_label("");
    g_signal_connect(btnActualizar, "clicked", G_CALLBACK(agregarEntrys), (gpointer) fixed);
    g_object_set_data(G_OBJECT(btnActualizar),"cantidad",(gpointer) spinNodos);
    g_object_set_data(G_OBJECT(btnActualizar),"ventana",(gpointer) windowValores);
    g_object_set_data(G_OBJECT(btnActualizar),"modo","nuevo");
    gtk_fixed_put(GTK_FIXED(fixed), btnActualizar, 360, 300);
    GtkWidget *imgActualizar = gtk_image_new_from_file("button_actualizar.png");
    gtk_button_set_always_show_image(GTK_BUTTON(btnActualizar),TRUE);
    gtk_button_set_image(GTK_BUTTON(btnActualizar), imgActualizar);


    GtkWidget *frame3 = gtk_frame_new("Valores");
    gtk_fixed_put(GTK_FIXED(fixed),frame3,715,200);
    gtk_widget_set_size_request(frame3,485,250);


    scrolled_window = gtk_scrolled_window_new (NULL, NULL);
    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window),GTK_POLICY_AUTOMATIC,GTK_POLICY_AUTOMATIC);

    //define color de fondo de la ventana
    GdkColor color;
    gdk_color_parse("#FFFFFF", &color);
    gtk_widget_modify_bg(scrolled_window, GTK_STATE_NORMAL, &color);

    gtk_widget_set_size_request (scrolled_window, 455, 200);
    gtk_fixed_put(GTK_FIXED(fixed),scrolled_window, 735, 230);

    //Creación y configuración del botón de siguiente
    btnSiguiente = gtk_button_new_with_label("");
    g_signal_connect(btnSiguiente, "clicked", G_CALLBACK(enviarAVentanaResultados), (gpointer) windowValores);

    //g_object_set_data(G_OBJECT(btnSiguiente), "Ph",(gpointer)spinH);
    //g_object_set_data(G_OBJECT(btnSiguiente), "Pr",(gpointer)spinR);

    //g_object_set_data(G_OBJECT(btnGuardar), "Ph",(gpointer)spinH);
    //g_object_set_data(G_OBJECT(btnGuardar), "Pr",(gpointer)spinR);

    //g_object_set_data(G_OBJECT(btnCargar), "Ph",(gpointer)spinH);
   // g_object_set_data(G_OBJECT(btnCargar), "Pr",(gpointer)spinR);
   // g_object_set_data(G_OBJECT(btnCargar), "spinNodos",(gpointer)spinNodos);
  //  g_object_set_data(G_OBJECT(btnCargar), "ventana",(gpointer)windowValores);

    gtk_fixed_put(GTK_FIXED(fixed), btnSiguiente, 1000, 20);
    GtkWidget *imgSiguiente = gtk_image_new_from_file("button_siguiente.png");
    gtk_button_set_always_show_image(GTK_BUTTON(btnSiguiente),TRUE);
    gtk_button_set_image(GTK_BUTTON(btnSiguiente), imgSiguiente);

    //configuración final
    gtk_container_add(GTK_CONTAINER(windowValores),fixed);
    gtk_widget_show_all(windowValores);
    gtk_main();
}