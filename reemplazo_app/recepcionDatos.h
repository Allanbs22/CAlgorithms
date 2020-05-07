
void enviarAsolucion(GtkWidget *dummy, gpointer widget){
   	plazo = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON(spinButton2));
	inflacion = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON(spinButton3));
	costoInicial = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON(spinButton4));

    gpointer *valores[vidaUtil][3];
    memcpy(valores,g_object_get_data(G_OBJECT(dummy), "lista"), vidaUtil*3*sizeof(gpointer));
    int lista[vidaUtil][3];
    for(int i=0; i<vidaUtil; i++){
        lista[i][0]= gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON(valores[i][0]));
        lista[i][1]= gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON(valores[i][1]));
        lista[i][2] = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON(valores[i][2]));
    }
    //cierra la ventana anterior
    gtk_widget_hide(widget);
    gtk_main_quit();
    
    ventanaResolver(dummy, lista);
}



/*
*E:Widget
*S:Ventana del widget cerrada y ventana de ingresar valores abierta
*R:Ninguna
*O:Abrir la ventana de ingresar valores
*/
void ventanaIngresarValores(GtkWidget *dummy, gpointer widget){
	
	//cierra la ventana anterior
	gtk_widget_hide(widget);
	gtk_main_quit();
	
	//fondo de pantalla
	GtkWidget *wallpaper, *fixed, *scrolled_window, *btnSiguiente, *windowValores, *btnVolver;
	windowValores = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(windowValores, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    
    //configuración de ventana
    gtk_window_set_position(GTK_WINDOW(windowValores), GTK_WIN_POS_CENTER);
    gtk_window_set_title(GTK_WINDOW(windowValores), "Indique los valores deseados");
    gtk_window_set_default_size(GTK_WINDOW(windowValores),1000,550);
    gtk_window_set_resizable(GTK_WINDOW(windowValores), FALSE);

    //fondo de pantalla y marcos
    scrolled_window = gtk_scrolled_window_new (NULL, NULL);
    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window),GTK_POLICY_AUTOMATIC,GTK_POLICY_AUTOMATIC);
    gtk_widget_set_size_request (scrolled_window, 1000, 550);
    fixed = gtk_fixed_new();

    //define color de fondo de la ventana
    GdkColor color;
    gdk_color_parse("#119BAB", &color);
    gtk_widget_modify_bg(scrolled_window, GTK_STATE_NORMAL, &color);

    char *modo;
    modo = g_object_get_data(G_OBJECT(dummy), "modo");


    //creación y configuración de spin button
    if(vidaUtil != -1){
        spinButton2 = gtk_spin_button_new_with_range  (1, 100, 1);
        gtk_spin_button_set_value (GTK_SPIN_BUTTON(spinButton2),plazo);

        spinButton3 = gtk_spin_button_new_with_range  (0, 100, 1);
        gtk_spin_button_set_value (GTK_SPIN_BUTTON(spinButton3),inflacion);

        spinButton4 = gtk_spin_button_new_with_range  (1, 1000000, 1);
        gtk_spin_button_set_value (GTK_SPIN_BUTTON(spinButton4),costoInicial);
    
    }
    else{
        spinButton2 = gtk_spin_button_new_with_range  (1, 100, 1);
        spinButton3 = gtk_spin_button_new_with_range  (0, 100, 1);
        spinButton4 = gtk_spin_button_new_with_range  (1, 1000000, 1);
    }

     //Creación y configuración del label de mensaje
    GtkWidget *lblMensaje = gtk_label_new("Plazo del proyecto");
    gtk_fixed_put(GTK_FIXED(fixed), lblMensaje,50, 50);

    GtkWidget *lblMensaje2 = gtk_label_new("Porcentaje de inflación");
    gtk_fixed_put(GTK_FIXED(fixed), lblMensaje2,200, 50);

    GtkWidget *lblMensaje3 = gtk_label_new("Costo del equipo");
    gtk_fixed_put(GTK_FIXED(fixed), lblMensaje3, 400, 50);


    gtk_fixed_put(GTK_FIXED(fixed), spinButton2, 60, 100);
    gtk_fixed_put(GTK_FIXED(fixed), spinButton3, 220, 100);
    gtk_fixed_put(GTK_FIXED(fixed), spinButton4, 400, 100);


    char texto[20];
    gpointer *valores[vidaUtil][3];
    if(strcmp(modo,"cargar") != 0){
        //spin buttons que se crean de forma dinámica según la cantidad de nodos
        for(int i = -1; i < vidaUtil; i++){
        	if(i ==  -1){
        		
        		GtkWidget *lblMensajeA = gtk_label_new("Año");
                gtk_fixed_put(GTK_FIXED(fixed), lblMensajeA, 57, 193+50);
        		GtkWidget *lblMensajeVariable1 = gtk_label_new("Ganancia");
                gtk_fixed_put(GTK_FIXED(fixed), lblMensajeVariable1, 157, 193+50);
				GtkWidget *lblMensajeVariable2 = gtk_label_new("Reventa:");
                gtk_fixed_put(GTK_FIXED(fixed), lblMensajeVariable2, 327, 193+50);
                GtkWidget *lblMensajeVariable3 = gtk_label_new("Mantenimiento");
                gtk_fixed_put(GTK_FIXED(fixed), lblMensajeVariable3, 522, 193+50);


        	}
        	else{
        		sprintf(texto,"%d",i+1);
        		GtkWidget *lblMensajeAN = gtk_label_new(texto);
                gtk_fixed_put(GTK_FIXED(fixed), lblMensajeAN, 57, 193+50*(i+2));
        		GtkWidget *spin = gtk_spin_button_new_with_range  (0,1000000, 1);
            	gtk_fixed_put(GTK_FIXED(fixed), spin, 157, 193+50*(i+2));
	 			GtkWidget *spin2 = gtk_spin_button_new_with_range  (0, 1000000, 1);
                gtk_fixed_put(GTK_FIXED(fixed), spin2, 327, 193+50*(i+2));
            	GtkWidget *spin3 = gtk_spin_button_new_with_range  (0,1000000, 1);
                gtk_fixed_put(GTK_FIXED(fixed), spin3, 522, 193+50*(i+2));
                valores[i][0] = (gpointer) spin;
                valores[i][1] = (gpointer) spin2;
                valores[i][2] = (gpointer) spin3;

        	}
    	}
    }
    else{
        char nombre[255];
        int lista[vidaUtil][3];
        memcpy(nombre,(char *)gtk_entry_get_text (GTK_ENTRY (ruta)),255*sizeof(char));
        FILE *archivo = fopen(nombre,"r");
        char linea[255];
        fgets(linea,255,archivo);
        char *parte;
        parte = strtok(linea,"\n");
        for(int i=0;i<vidaUtil;i++){
            fgets(linea,255,archivo);
            parte = strtok(linea,",");
            lista[i][0]= atoi(parte);
            parte = strtok(NULL,",");
            lista[i][1] = atoi(parte);
            parte = strtok(NULL,",");
            lista[i][2] = atoi(parte);
        }
        fclose(archivo);
        //spin buttons que se crean de forma dinámica según la cantidad de nodos
        for(int i = -1; i < vidaUtil; i++){
        	if(i ==  -1){
        		
        		GtkWidget *lblMensajeA = gtk_label_new("Año");
                gtk_fixed_put(GTK_FIXED(fixed), lblMensajeA, 57, 193+50);
        		GtkWidget *lblMensajeVariable1 = gtk_label_new("Ganancia");
                gtk_fixed_put(GTK_FIXED(fixed), lblMensajeVariable1, 157, 193+50);
				GtkWidget *lblMensajeVariable2 = gtk_label_new("Reventa:");
                gtk_fixed_put(GTK_FIXED(fixed), lblMensajeVariable2, 327, 193+50);
                GtkWidget *lblMensajeVariable3 = gtk_label_new("Mantenimiento");
                gtk_fixed_put(GTK_FIXED(fixed), lblMensajeVariable3, 522, 193+50);


        	}
        	else{
        		sprintf(texto,"%d",i+1);
        		GtkWidget *lblMensajeAN = gtk_label_new(texto);
                gtk_fixed_put(GTK_FIXED(fixed), lblMensajeAN, 57, 193+50*(i+2));
        		GtkWidget *spin = gtk_spin_button_new_with_range  (0,1000000, 1);
        		gtk_spin_button_set_value (GTK_SPIN_BUTTON(spin),lista[i][0]);
            	gtk_fixed_put(GTK_FIXED(fixed), spin, 157, 193+50*(i+2));
	 			GtkWidget *spin2 = gtk_spin_button_new_with_range  (0, 1000000, 1);
	 			gtk_spin_button_set_value (GTK_SPIN_BUTTON(spin2),lista[i][1]);
                gtk_fixed_put(GTK_FIXED(fixed), spin2, 327, 193+50*(i+2));
            	GtkWidget *spin3 = gtk_spin_button_new_with_range  (0,1000000, 1);
            	gtk_spin_button_set_value (GTK_SPIN_BUTTON(spin3),lista[i][2]);
                gtk_fixed_put(GTK_FIXED(fixed), spin3, 522, 193+50*(i+2));
                valores[i][0] = (gpointer) spin;
                valores[i][1] = (gpointer) spin2;
                valores[i][2] = (gpointer) spin3;

        	}

			


        }
    }
    //Creación y configuración del botón de siguiente
    btnSiguiente = gtk_button_new_with_label("");
    g_signal_connect(btnSiguiente, "clicked", G_CALLBACK(enviarAsolucion), (gpointer) windowValores);
    g_object_set_data(G_OBJECT(btnSiguiente), "lista",valores);
    gtk_fixed_put(GTK_FIXED(fixed), btnSiguiente, 550, 200+50*(vidaUtil+3));
    GtkWidget *imgSiguiente = gtk_image_new_from_file("button_siguiente.png");
    gtk_button_set_always_show_image(GTK_BUTTON(btnSiguiente),TRUE);
    gtk_button_set_image(GTK_BUTTON(btnSiguiente), imgSiguiente);


    //Creación y configuración del botón de volver
    btnVolver = gtk_button_new_with_label("");
    g_signal_connect(btnVolver, "clicked", G_CALLBACK(volverAPrincipal), (gpointer) windowValores);
    gtk_fixed_put(GTK_FIXED(fixed), btnVolver, 50, 200+50*(vidaUtil+3));
    GtkWidget *imgVolver = gtk_image_new_from_file("button_volver.png");
    gtk_button_set_always_show_image(GTK_BUTTON(btnVolver),TRUE);
    gtk_button_set_image(GTK_BUTTON(btnVolver), imgVolver);

    

    //configuración final
    gtk_container_add(GTK_CONTAINER(scrolled_window),fixed);
    gtk_container_add(GTK_CONTAINER(windowValores),scrolled_window);
    gtk_widget_show_all(windowValores);
    gtk_main();
}

void enviarAVentanaValores(GtkWidget *dummy, gpointer widget){
    vidaUtil = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON(spinButton));
    ventanaIngresarValores(dummy, widget);
}


/*
*E:Widget
*S:Ventana del widget cerrada y ventana de ingresar tamaño abierta
*R:Ninguna
*O:Abrir la ventana de ingresar tamaño
*/
void ventanaCantidad(GtkWidget *dummy, gpointer widget){

    vidaUtil = -1;
    plazo = -1; 
	inflacion = -1; 
	costoInicial = -1;
	
	//cierra la ventana anterior
	gtk_widget_hide(widget);
	gtk_main_quit();

	//definición de widgets de la ventana
    GtkWidget *window, *wallpaper, *fixed, *btnIr, *lblMensaje, *btnVolver;

    //creación de la ventana y asignación del botón de cerrar
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    //configuración de ventana
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_title(GTK_WINDOW(window), "Vida Útil");
    gtk_window_set_default_size(GTK_WINDOW(window),700,550);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);

    //fondo de pantalla y marco
    wallpaper = gtk_image_new_from_file("wallpaper.jpg");
    fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window),fixed);
    gtk_fixed_put(GTK_FIXED(fixed), wallpaper, 0, 0);

    //Creación y configuración del label de mensaje
    lblMensaje = gtk_label_new("Por favor indique la vida útil del equipo:");
    gtk_fixed_put(GTK_FIXED(fixed), lblMensaje, 50, 100);

    //creación y configuración de spin button
    spinButton = gtk_spin_button_new_with_range  (1, 100, 1);
    gtk_fixed_put(GTK_FIXED(fixed), spinButton, 50, 150);

    //Creación y configuración del botón de ir
    btnIr = gtk_button_new_with_label("");
    g_signal_connect(btnIr, "clicked", G_CALLBACK(enviarAVentanaValores), (gpointer) window);
    g_object_set_data(G_OBJECT(btnIr),"modo","nuevo");
    gtk_fixed_put(GTK_FIXED(fixed), btnIr, 250, 290);
    GtkWidget *imgSalir = gtk_image_new_from_file("button_ir.png");
    gtk_button_set_always_show_image(GTK_BUTTON(btnIr),TRUE);
    gtk_button_set_image(GTK_BUTTON(btnIr), imgSalir);


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
