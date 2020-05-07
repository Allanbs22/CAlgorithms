void estadoCambiado(GtkWidget* widget, int data){
     if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget)))
    {
            valoresEntradas[data] = 1;
            //printf("activado%i\n",data);
    }else
    {
            valoresEntradas[data] = 0;
            //printf("desactivado\n");
    }
}


//E: Direccion del archivo a leer(direccion\nombre.extencion), tamaño de la matriz,
//la matriz y lista de nombres.
//S: matriz compuesta por los datos del archivo.
//R: el archivo debe respetar el formato de los archivos.
//O: convertir un archivo a matriz.
void  leer_archivo(GtkWidget* dummy,gpointer widget){
    char* direccion = gtk_entry_get_text (GTK_ENTRY (ruta));
    if(strlen(direccion)>0){
        FILE *archivo;
        char *ch;
        char *dev;
        int lineanum = -1;
        int pos = 0;
        archivo=fopen(direccion,"r");
        

        char linea[255];
        //fgets(linea,255,archivo);

        char casa[255];
        char visita[255];
        char temp[255];

        //casa = strtok(linea,"\n");
        //visita = strtok(casa,"\n");
        //temp = strtok(visita,"\n");
        fgets(casa,255,archivo);
        fgets(visita,255,archivo);
        fgets(temp,255,archivo);

        houseG = atof(casa);
        visitG = atof(visita);
        tamSerie = atoi(temp);

        int listaChecks[99];

        for(int i=0;i<tamSerie;i++){
            fgets(linea,255,archivo);
            valoresEntradas[i] = atoi(linea);
        }
        
        fclose(archivo);

        gtk_spin_button_set_value (GTK_SPIN_BUTTON(g_object_get_data(G_OBJECT(dummy), "spinJuegos")),tamSerie);
        gtk_spin_button_set_value (GTK_SPIN_BUTTON(g_object_get_data(G_OBJECT(dummy), "Ph")),houseG);
        gtk_spin_button_set_value (GTK_SPIN_BUTTON(g_object_get_data(G_OBJECT(dummy), "Pr")),visitG);
        GtkWidget *fixJuegos = gtk_fixed_new();
        for(int i=0;i<tamSerie;i++){
            char texto[50];
            sprintf(texto,"¿Se juega en casa en el juego %i?",i+1);
            //Creación y configuración del label de probabilidad visita
            GtkWidget *lblCasa = gtk_label_new(texto);
            gtk_fixed_put(GTK_FIXED(fixJuegos), lblCasa, 5, 40*i);

            GtkWidget *check = gtk_check_button_new ();
            if(valoresEntradas[i]==1)
                gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check),TRUE);
            gtk_fixed_put(GTK_FIXED(fixJuegos), check, 225, 40*i);
            g_signal_connect(check, "toggled", G_CALLBACK(estadoCambiado), (gpointer)i);
            //entradas[i] = (gpointer)check;
        }
        GtkWidget *scrolled_window = gtk_scrolled_window_new (NULL, NULL);
        gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window),GTK_POLICY_AUTOMATIC,GTK_POLICY_AUTOMATIC);

        //define color de fondo de la ventana
        GdkColor color;
        gdk_color_parse("#FFFFFF", &color);
        gtk_widget_modify_bg(scrolled_window, GTK_STATE_NORMAL, &color);

        gtk_widget_set_size_request (scrolled_window, 270, 200);
        gtk_container_add(GTK_CONTAINER(scrolled_window),fixJuegos);
        gtk_fixed_put(GTK_FIXED(widget),scrolled_window, 800, 230);
        GtkWidget *windowValores = g_object_get_data(G_OBJECT(dummy), "ventana");
        gtk_widget_show_all(windowValores);
    }
                
    
}


void agregarChecks(GtkWidget *dummy, gpointer widget){
    int juegos = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON(g_object_get_data(G_OBJECT(dummy), "cantidad")));
    GtkWidget *windowValores = g_object_get_data(G_OBJECT(dummy), "ventana");
    if(juegos%2==1){
        tamSerie = juegos;
        GtkWidget *fixJuegos = gtk_fixed_new();
        for(int i=0;i<juegos;i++){
            valoresEntradas[i]=0;
            char texto[50];
            sprintf(texto,"¿Se juega en casa en el juego %i?",i+1);
            //Creación y configuración del label de probabilidad visita
            GtkWidget *lblCasa = gtk_label_new(texto);
            gtk_fixed_put(GTK_FIXED(fixJuegos), lblCasa, 5, 40*i);

            GtkWidget *check = gtk_check_button_new ();
            gtk_fixed_put(GTK_FIXED(fixJuegos), check, 225, 40*i);
            g_signal_connect(check, "toggled", G_CALLBACK(estadoCambiado), (gpointer)i);
            //entradas[i] = (gpointer)check;
        }
        GtkWidget *scrolled_window = gtk_scrolled_window_new (NULL, NULL);
        gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window),GTK_POLICY_AUTOMATIC,GTK_POLICY_AUTOMATIC);

        //define color de fondo de la ventana
        GdkColor color;
        gdk_color_parse("#FFFFFF", &color);
        gtk_widget_modify_bg(scrolled_window, GTK_STATE_NORMAL, &color);

        gtk_widget_set_size_request (scrolled_window, 270, 200);
        gtk_container_add(GTK_CONTAINER(scrolled_window),fixJuegos);
        gtk_fixed_put(GTK_FIXED(widget),scrolled_window, 800, 230);
        gtk_widget_show_all(windowValores);
    }
}

void enviarAVentanaResultados(GtkWidget *dummy, gpointer widget){
    if(tamSerie>0){
        for(int i=0;i<tamSerie;i++){
            //valoresEntradas[i] = 
        }
        gdouble house = gtk_spin_button_get_value (GTK_SPIN_BUTTON(g_object_get_data(G_OBJECT(dummy), "Ph")));
        gdouble visit = gtk_spin_button_get_value (GTK_SPIN_BUTTON(g_object_get_data(G_OBJECT(dummy), "Pr")));
        houseG = house;
        visitG = visit;
        ventanaResultados(dummy,widget,house,visit);
    }
}


//E: dirrecion a crear el archivo(dirreccion\nombre.extencion), tamaño de la matriz, matriz y la lista de nombres.
//S: archivo con los datos de la matriz.
//R: la matiz debe ser cuadrada.
//O: crear archivo con los datos de una matriz.
void guardar(GtkWidget *dummy, gpointer widget){
    char nombre[32];
    snprintf(nombre,sizeof(nombre),"%s",(char *)gtk_entry_get_text (GTK_ENTRY (g_object_get_data(G_OBJECT(dummy), "nombre"))));
    float house = gtk_spin_button_get_value (GTK_SPIN_BUTTON(g_object_get_data(G_OBJECT(dummy), "Ph")));
    float visit = gtk_spin_button_get_value (GTK_SPIN_BUTTON(g_object_get_data(G_OBJECT(dummy), "Pr")));
    //verifica que el nombre tenga caracteres
    if(strlen(nombre)>0 && tamSerie>0){
        char texto[100000];
        char visita[10];
        char tamS[10];
        snprintf(texto,sizeof(texto),"%f\n",house);
        snprintf(visita,sizeof(visita),"%f\n",visit);
        strcat(texto,visita);
        snprintf(tamS,sizeof(tamS),"%i\n",tamSerie);
        strcat(texto,tamS);
        for(int i=0;i<tamSerie;i++){
            char temp[100];
            snprintf(temp,sizeof(temp),"%i\n",valoresEntradas[i]);
            strcat(texto,temp);
        }
        strcat(nombre,".mti");
        FILE *archivo;
        archivo = fopen (nombre, "w" );
        fprintf(archivo, "%s",texto);
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
	tamSerie = 0;
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

    //Creación y configuración del botón de cargar
    btnCargar = gtk_button_new_with_label("");
    g_signal_connect(btnCargar, "clicked", G_CALLBACK(leer_archivo), (gpointer) fixed);
    //g_object_set_data(G_OBJECT(btnCargar),"modo","cargar");
    gtk_fixed_put(GTK_FIXED(fixed), btnCargar, 50, 260);
    GtkWidget *imgCargar = gtk_image_new_from_file("button_cargar.png");
    gtk_button_set_always_show_image(GTK_BUTTON(btnCargar),TRUE);
    gtk_button_set_image(GTK_BUTTON(btnCargar), imgCargar);


    //Creación y configuración del entry de tamaño
    nombreArchivo = gtk_entry_new();
    gtk_fixed_put(GTK_FIXED(fixed), nombreArchivo, 70, 335);
    gtk_widget_set_size_request(nombreArchivo,30,30);

    //Creación y configuración del botón de guardar
    btnGuardar = gtk_button_new_with_label("");
    g_signal_connect(btnGuardar, "clicked", G_CALLBACK(guardar), (gpointer) windowValores);
    g_object_set_data(G_OBJECT(btnGuardar),"nombre",(gpointer)nombreArchivo);
    gtk_fixed_put(GTK_FIXED(fixed), btnGuardar, 50, 375);
    GtkWidget *imgGuardar = gtk_image_new_from_file("button_guardar.png");
    gtk_button_set_always_show_image(GTK_BUTTON(btnGuardar),TRUE);
    gtk_button_set_image(GTK_BUTTON(btnGuardar), imgGuardar);

    GtkWidget *frame2 = gtk_frame_new("Probabilidades");
    gtk_fixed_put(GTK_FIXED(fixed),frame2,380,200);
    gtk_widget_set_size_request(frame2,350,250);


    //Creación y configuración del label de mensaje
    GtkWidget *lblJuegos = gtk_label_new("Número de juegos:");
    gtk_fixed_put(GTK_FIXED(fixed), lblJuegos, 400, 235);


    //creación y configuración de spin button
    GtkWidget *spinJuegos = gtk_spin_button_new_with_range  (3, 99,2);
    gtk_fixed_put(GTK_FIXED(fixed), spinJuegos, 600, 235);


    //Creación y configuración del label de probabilidad casa
    GtkWidget *lblPh = gtk_label_new("Prob. de ganar en casa(Ph):");
    gtk_fixed_put(GTK_FIXED(fixed), lblPh, 400, 285);

    //creación y configuración de spin button
    GtkWidget *spinH = gtk_spin_button_new_with_range  (0, 1, 0.0001);
    gtk_fixed_put(GTK_FIXED(fixed), spinH, 600, 285);
    gtk_spin_button_configure (GTK_SPIN_BUTTON(spinH),NULL,0.0001,4);

    //Creación y configuración del label de probabilidad visita
    GtkWidget *lblPr = gtk_label_new("Prob. de ganar en visita(Pr):");
    gtk_fixed_put(GTK_FIXED(fixed), lblPr, 400, 335);

    //creación y configuración de spin button
    GtkWidget *spinR = gtk_spin_button_new_with_range  (0, 1, 0.0001);
    gtk_fixed_put(GTK_FIXED(fixed), spinR, 600, 335);
    gtk_spin_button_configure (GTK_SPIN_BUTTON(spinR),NULL,0.0001,4);

    //Creación y configuración del botón de guardar
    btnActualizar = gtk_button_new_with_label("");
    g_signal_connect(btnActualizar, "clicked", G_CALLBACK(agregarChecks), (gpointer) fixed);
    g_object_set_data(G_OBJECT(btnActualizar),"cantidad",(gpointer) spinJuegos);
    g_object_set_data(G_OBJECT(btnActualizar),"ventana",(gpointer) windowValores);
    gtk_fixed_put(GTK_FIXED(fixed), btnActualizar, 425, 380);
    GtkWidget *imgActualizar = gtk_image_new_from_file("button_actualizar.png");
    gtk_button_set_always_show_image(GTK_BUTTON(btnActualizar),TRUE);
    gtk_button_set_image(GTK_BUTTON(btnActualizar), imgActualizar);


    GtkWidget *frame3 = gtk_frame_new("Localías");
    gtk_fixed_put(GTK_FIXED(fixed),frame3,780,200);
    gtk_widget_set_size_request(frame3,300,250);


    scrolled_window = gtk_scrolled_window_new (NULL, NULL);
    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window),GTK_POLICY_AUTOMATIC,GTK_POLICY_AUTOMATIC);

    //define color de fondo de la ventana
    GdkColor color;
    gdk_color_parse("#FFFFFF", &color);
    gtk_widget_modify_bg(scrolled_window, GTK_STATE_NORMAL, &color);

    gtk_widget_set_size_request (scrolled_window, 270, 200);
    gtk_fixed_put(GTK_FIXED(fixed),scrolled_window, 800, 230);

    //Creación y configuración del botón de siguiente
    btnSiguiente = gtk_button_new_with_label("");
    g_signal_connect(btnSiguiente, "clicked", G_CALLBACK(enviarAVentanaResultados), (gpointer) windowValores);

    g_object_set_data(G_OBJECT(btnSiguiente), "Ph",(gpointer)spinH);
    g_object_set_data(G_OBJECT(btnSiguiente), "Pr",(gpointer)spinR);

    g_object_set_data(G_OBJECT(btnGuardar), "Ph",(gpointer)spinH);
    g_object_set_data(G_OBJECT(btnGuardar), "Pr",(gpointer)spinR);

    g_object_set_data(G_OBJECT(btnCargar), "Ph",(gpointer)spinH);
    g_object_set_data(G_OBJECT(btnCargar), "Pr",(gpointer)spinR);
    g_object_set_data(G_OBJECT(btnCargar), "spinJuegos",(gpointer)spinJuegos);
    g_object_set_data(G_OBJECT(btnCargar), "ventana",(gpointer)windowValores);

    gtk_fixed_put(GTK_FIXED(fixed), btnSiguiente, 1000, 20);
    GtkWidget *imgSiguiente = gtk_image_new_from_file("button_siguiente.png");
    gtk_button_set_always_show_image(GTK_BUTTON(btnSiguiente),TRUE);
    gtk_button_set_image(GTK_BUTTON(btnSiguiente), imgSiguiente);

    //configuración final
    gtk_container_add(GTK_CONTAINER(windowValores),fixed);
    gtk_widget_show_all(windowValores);
    gtk_main();
}