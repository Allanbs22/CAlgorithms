void guardar2(GtkWidget *dummy,struct nodo lista[cantE]){
    char nombre[255];
    char texto[15000];
    sprintf(nombre,"%s",gtk_entry_get_text (GTK_ENTRY (g_object_get_data(G_OBJECT(dummy), "nombre"))));
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


void ventanaResultados(GtkWidget *dummy, gpointer widget, struct nodo elementos[cantE]){
    //cierra la ventana anterior
    gtk_widget_hide(widget);
    gtk_main_quit();

    //fondo de pantalla
    GtkWidget *fixed, *fixedScroll, *fixedScroll2, *scrolled_window2, *wallpaper, *scrolled_window, *windowResultados, *btnGuardar, *nombreArchivo, *btnVolver;
    windowResultados = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(windowResultados, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    
    //configuración de ventana
    gtk_window_set_position(GTK_WINDOW(windowResultados), GTK_WIN_POS_CENTER);
    gtk_window_set_title(GTK_WINDOW(windowResultados), "Mostrando resultados");
    gtk_window_set_default_size(GTK_WINDOW(windowResultados),1300,750);
    gtk_window_set_resizable(GTK_WINDOW(windowResultados), FALSE);

    //fondo de pantalla y marco
    wallpaper = gtk_image_new_from_file("wallpaper2.jpg");
    fixed = gtk_fixed_new();
    gtk_fixed_put(GTK_FIXED(fixed), wallpaper, 0, 0);


    GtkWidget *frame2 = gtk_frame_new("Guardar Datos");
    gtk_fixed_put(GTK_FIXED(fixed),frame2,50,530);
    gtk_widget_set_size_request(frame2,250,120);

    //Creación y configuración del entry de nombre del archivo
    nombreArchivo = gtk_entry_new();
    gtk_fixed_put(GTK_FIXED(fixed), nombreArchivo, 70, 550);
    gtk_widget_set_size_request(nombreArchivo,30,30);


    //Creación y configuración del botón de guardar
    btnGuardar = gtk_button_new_with_label("");
    g_signal_connect(btnGuardar, "clicked", G_CALLBACK(guardar2),elementos);
    g_object_set_data(G_OBJECT(btnGuardar),"nombre",(gpointer)nombreArchivo);
    gtk_fixed_put(GTK_FIXED(fixed), btnGuardar, 60, 585);
    GtkWidget *imgGuardar = gtk_image_new_from_file("button_guardar.png");
    gtk_button_set_always_show_image(GTK_BUTTON(btnGuardar),TRUE);
    gtk_button_set_image(GTK_BUTTON(btnGuardar), imgGuardar);


    scrolled_window = gtk_scrolled_window_new (NULL, NULL);
    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window),GTK_POLICY_AUTOMATIC,GTK_POLICY_AUTOMATIC);


    float A[cantE+1][cantE+1];
    int R[cantE+1][cantE+1];
    arboles(A,R,elementos);


    fixedScroll = gtk_fixed_new();

    
    GtkWidget *lblTexto = gtk_label_new("Tabla A");
    gtk_widget_set_size_request (lblTexto, 80, 60);
    gtk_fixed_put(GTK_FIXED(fixedScroll), lblTexto, 0, 0);

    for(int i=0;i<=cantE;i++){
        char txtCuadro[200];
        sprintf(txtCuadro,"%i",i);
        GtkWidget *cuadro = gtk_label_new(txtCuadro);
        gtk_widget_set_size_request (cuadro, 80, 60);
        gtk_fixed_put(GTK_FIXED(fixedScroll), cuadro, 50+100*i, 10);

        sprintf(txtCuadro,"%i",i+1);
        GtkWidget *cuadro2 = gtk_label_new(txtCuadro);
        gtk_widget_set_size_request (cuadro2, 80, 60);
        gtk_fixed_put(GTK_FIXED(fixedScroll), cuadro2, 0, 70*(i+1));
    }


    for(int i=0;i<=cantE;i++){
        for(int j=0;j<=cantE;j++){
            char txtCuadro[200];
            sprintf(txtCuadro,"%lf",A[j][i]);
            GtkWidget *cuadro = gtk_label_new(txtCuadro);
            GdkColor color;
            gdk_color_parse ("#F7FE2E", &color);
            gtk_widget_modify_bg (cuadro, GTK_STATE_NORMAL, &color);
            gtk_widget_set_size_request (cuadro, 80, 60);
            gtk_fixed_put(GTK_FIXED(fixedScroll), cuadro, 50+100*i, 70+70*j);
            
        }
    }

    //define color de fondo de la ventana
    GdkColor color;
    gdk_color_parse("#FFFFFF", &color);
    gtk_widget_modify_bg(scrolled_window, GTK_STATE_NORMAL, &color);

    gtk_widget_set_size_request (scrolled_window, 550, 425);

    gtk_container_add(GTK_CONTAINER(scrolled_window),fixedScroll);


    gtk_fixed_put(GTK_FIXED(fixed),scrolled_window, 30, 35);



    //fixed 2
    fixedScroll2 = gtk_fixed_new();

    scrolled_window2 = gtk_scrolled_window_new (NULL, NULL);
    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window2),GTK_POLICY_AUTOMATIC,GTK_POLICY_AUTOMATIC);


    GtkWidget *cuadro2 = gtk_label_new("Tabla R");
    gtk_widget_set_size_request (cuadro2, 80, 60);
    gtk_fixed_put(GTK_FIXED(fixedScroll2), cuadro2,0, 0);


    for(int i=0;i<=cantE;i++){
        char txtCuadro[200];
        sprintf(txtCuadro,"%i",i);
        GtkWidget *cuadro = gtk_label_new(txtCuadro);
        gtk_widget_set_size_request (cuadro, 80, 60);
        gtk_fixed_put(GTK_FIXED(fixedScroll2), cuadro, 50+100*i, 10);

        sprintf(txtCuadro,"%i",i+1);
        GtkWidget *cuadro2 = gtk_label_new(txtCuadro);
        gtk_widget_set_size_request (cuadro2, 80, 60);
        gtk_fixed_put(GTK_FIXED(fixedScroll2), cuadro2, 0, 70*(i+1));
    }


    for(int i=0;i<=cantE;i++){
        for(int j=0;j<=cantE;j++){
            char txtCuadro[200];
            sprintf(txtCuadro,"%i",R[j][i]);
            GtkWidget *cuadro = gtk_label_new(txtCuadro);
            GdkColor color;
            gdk_color_parse ("#F7FE2E", &color);
            gtk_widget_modify_bg (cuadro, GTK_STATE_NORMAL, &color);
            gtk_widget_set_size_request (cuadro, 80, 60);
            gtk_fixed_put(GTK_FIXED(fixedScroll2), cuadro, 50+100*i, 70+70*j);
            
        }
    }

    //define color de fondo de la ventana
    gdk_color_parse("#FFFFFF", &color);
    gtk_widget_modify_bg(scrolled_window2, GTK_STATE_NORMAL, &color);

    gtk_widget_set_size_request (scrolled_window2, 550, 425);

    gtk_container_add(GTK_CONTAINER(scrolled_window2),fixedScroll2);


    gtk_fixed_put(GTK_FIXED(fixed),scrolled_window2, 600, 35);

    //Scrolled Window 3

    GtkWidget *fixedScroll3 = gtk_fixed_new();

    GtkWidget *scrolled_window3 = gtk_scrolled_window_new (NULL, NULL);
    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window3),GTK_POLICY_AUTOMATIC,GTK_POLICY_AUTOMATIC);

    for(int i=0;i<cantE;i++){
        char txtCuadro[200];
        sprintf(txtCuadro,"%d- %s",i+1,elementos[i].nombre);
        GtkWidget *cuadro = gtk_label_new(txtCuadro);
        gtk_fixed_put(GTK_FIXED(fixedScroll3), cuadro, 0, 25*i);
    }

    //define color de fondo de la ventana
    gdk_color_parse("#FFFFFF", &color);
    gtk_widget_modify_bg(scrolled_window3, GTK_STATE_NORMAL, &color);

    gtk_widget_set_size_request (scrolled_window3, 400, 150);

    gtk_container_add(GTK_CONTAINER(scrolled_window3),fixedScroll3);


    gtk_fixed_put(GTK_FIXED(fixed),scrolled_window3, 400, 480);

    //Creación y configuración del botón de volver
    btnVolver = gtk_button_new_with_label("");
    g_signal_connect(btnVolver, "clicked", G_CALLBACK(volverAPrincipal), (gpointer) windowResultados);
    gtk_fixed_put(GTK_FIXED(fixed), btnVolver, 960,600);
    GtkWidget *imgVolver = gtk_image_new_from_file("button_volver.png");
    gtk_button_set_always_show_image(GTK_BUTTON(btnVolver),TRUE);
    gtk_button_set_image(GTK_BUTTON(btnVolver), imgVolver);

    //configuración final
    gtk_container_add(GTK_CONTAINER(windowResultados),fixed);
    gtk_widget_show_all(windowResultados);
    gtk_main();
}