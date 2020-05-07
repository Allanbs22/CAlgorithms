
/*
*E:Valores de los botones
*S:Valores pasados a enteros y enviados a la ventana de tabla D
*R:valores válidos
*O:Convertir los valores a enteros y enviarlos a la ventana correspondiente
*/
void enviarAD(GtkWidget *dummy, gpointer valores[tam][tam]){
	int value = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON(spinButton));
	int respuesta[2][tam][tam];
	for(int i = 0; i < value; i++){
	    	for(int j = 0; j < value; j++){
			    respuesta[1][i][j] = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON(valores[i][j]));
	    	}
	}
    int P[tam][tam];
	cargando = 0;
    memcpy(respuesta[0], P, tam*tam);
	ventanaD(dummy,respuesta);
}


/*
*E:Widget
*S:Ventana del widget cerrada y ventana de ingresar valores abierta
*R:Ninguna
*O:Abrir la ventana de ingresar valores
*/
void ingresarValores(GtkWidget *dummy, gpointer entradas[]){
	tablaActual = -1;
	int value = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON(spinButton));
	tam = value;
	
	//cierra la ventana anterior
	gtk_widget_hide(windowNombres);
	gtk_main_quit();
	
	//fondo de pantalla
	GtkWidget *wallpaper, *fixed, *scrolled_window, *lblMensaje, *btnSiguiente;
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

    //creación de label de mensaje
    lblMensaje = gtk_label_new("Por favor indique el valor de las conexiones (el número -1 simboliza el infinito):");
    gtk_fixed_put(GTK_FIXED(fixed), lblMensaje, 50, 50);

    //spin buttons que se crean de forma dinámica según la cantidad de nodos
    gpointer *valores[value][value];
    for(int i = 0; i <= value; i++){
    	for(int j = 0; j <= value; j++){
    		if(i==j){
    			if(j!=0 || i!=0){
		    		//si se está en la diagonal de la matriz el spin button se bloquea en 0
		    		GtkWidget *spin = gtk_spin_button_new_with_range  (0,0, 1);
			    	gtk_fixed_put(GTK_FIXED(fixed), spin, 5+120*j, 100+50*i);
			    	valores[i-1][j-1] = (gpointer) spin;
			    }
	    	}
    		else if(i==0 && j>0){
			    GtkWidget *lblName = gtk_label_new(gtk_entry_get_text (GTK_ENTRY (entradas[j-1])));
			    gtk_fixed_put(GTK_FIXED(fixed), lblName, 50+120*j, 100+50*i);
    		}
    		else if(j==0 && i>0){
    			GtkWidget *lblName = gtk_label_new(gtk_entry_get_text (GTK_ENTRY (entradas[i-1])));
			    gtk_fixed_put(GTK_FIXED(fixed), lblName, 50+120*j, 100+50*i);
    		}
    		else{
		    	GtkWidget *spin = gtk_spin_button_new_with_range  (-1, 32000, 1);
		    	gtk_fixed_put(GTK_FIXED(fixed), spin, 120*j, 100+50*i);
		    	valores[i-1][j-1] = (gpointer) spin;
		    }
	    	
    	}
    }

    //Creación y configuración del botón de siguiente
    btnSiguiente = gtk_button_new_with_label("");
    g_signal_connect(btnSiguiente, "clicked", G_CALLBACK(enviarAD), valores);
    gtk_fixed_put(GTK_FIXED(fixed), btnSiguiente, 50, 150+50*(value+1));
    GtkWidget *imgSiguiente = gtk_image_new_from_file("button_siguiente.png");
    gtk_button_set_always_show_image(GTK_BUTTON(btnSiguiente),TRUE);
    gtk_button_set_image(GTK_BUTTON(btnSiguiente), imgSiguiente);

    

    //configuración final
    gtk_container_add(GTK_CONTAINER(scrolled_window),fixed);
    gtk_container_add(GTK_CONTAINER(windowValores),scrolled_window);
    gtk_widget_show_all(windowValores);
    gtk_main();
}


/*
*E:Widget
*S:Ventana del widget cerrada y ventana de ingresar nombres abierta
*R:Ninguna
*O:Abrir la ventana de ingresar nombres
*/
void ingresarNombres(GtkWidget *dummy, gpointer widget){

	//carga el valor de tamaño
	int value = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON(spinButton));

	//cierra la ventana anterior
	gtk_widget_hide(widget);
	gtk_main_quit();
	
	GtkWidget *wallpaper, *fixed, *scrolled_window, *lblMensaje, *btnSiguiente, *btnVolver;
	windowNombres = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(windowNombres, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    
    //configuración de ventana
    gtk_window_set_position(GTK_WINDOW(windowNombres), GTK_WIN_POS_CENTER);
    gtk_window_set_title(GTK_WINDOW(windowNombres), "Indique los nombres deseados");
    gtk_window_set_default_size(GTK_WINDOW(windowNombres),700,550);
    gtk_window_set_resizable(GTK_WINDOW(windowNombres), FALSE);

    //marcos y sccrolled windows
    scrolled_window = gtk_scrolled_window_new (NULL, NULL);
    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window),GTK_POLICY_AUTOMATIC,GTK_POLICY_AUTOMATIC);
    gtk_widget_set_size_request (scrolled_window, 700, 550);
    fixed = gtk_fixed_new();

    //creación de label de mensaje
    lblMensaje = gtk_label_new("Por favor indique el nombre de los nodos deseados:");
    gtk_fixed_put(GTK_FIXED(fixed), lblMensaje, 50, 50);

    //define color de fondo de la ventana
    GdkColor color;
    gdk_color_parse("#119BAB", &color);
    gtk_widget_modify_bg(scrolled_window, GTK_STATE_NORMAL, &color);

    //entrys que se crean de forma dinámica según la cantidad de nodos
    entradas = malloc(sizeof(gpointer)*value);
	
    for(int i = 0; i < value; i++){
    	GtkWidget *entry = gtk_entry_new();
    	gtk_fixed_put(GTK_FIXED(fixed), entry, 50, 100+50*i);
    	//Se definen los nombres por defecto de los entrys
    	if(i<=25){
			char buffer[32];
			snprintf(buffer, sizeof(buffer), "%c",i+65);
			gtk_entry_set_text(GTK_ENTRY(entry), buffer);
		}
		else if(i<=51){
			char buffer[32];
			snprintf(buffer, sizeof(buffer), "A%c",i+39);
			gtk_entry_set_text(GTK_ENTRY(entry), buffer);
		}
    	entradas[i] =  (gpointer) entry;
    }

    //Creación y configuración del botón de siguiente
    btnSiguiente = gtk_button_new_with_label("");
    g_signal_connect(btnSiguiente, "clicked", G_CALLBACK(ingresarValores), entradas);
    gtk_fixed_put(GTK_FIXED(fixed), btnSiguiente, 50, 100+50*value);
    GtkWidget *imgSiguiente = gtk_image_new_from_file("button_siguiente.png");
    gtk_button_set_always_show_image(GTK_BUTTON(btnSiguiente),TRUE);
    gtk_button_set_image(GTK_BUTTON(btnSiguiente), imgSiguiente);

    //Creación y configuración del botón de volver
    btnVolver = gtk_button_new_with_label("");
    g_signal_connect(btnVolver, "clicked", G_CALLBACK(volverAPrincipal), (gpointer) windowNombres);
    gtk_fixed_put(GTK_FIXED(fixed), btnVolver, 450, 100+50*value);
    GtkWidget *imgVolver = gtk_image_new_from_file("button_volver.png");
    gtk_button_set_always_show_image(GTK_BUTTON(btnVolver),TRUE);
    gtk_button_set_image(GTK_BUTTON(btnVolver), imgVolver);

    //configuración final
    gtk_container_add(GTK_CONTAINER(scrolled_window),fixed);
    gtk_container_add(GTK_CONTAINER(windowNombres),scrolled_window);
    gtk_widget_show_all(windowNombres);
    gtk_main();
}



/*
*E:Widget
*S:Ventana del widget cerrada y ventana de ingresar tamaño abierta
*R:Ninguna
*O:Abrir la ventana de ingresar tamaño
*/
void ventanaTamano(GtkWidget *dummy, gpointer widget){

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
    gtk_window_set_title(GTK_WINDOW(window), "Ingrese el tamaño deseado");
    gtk_window_set_default_size(GTK_WINDOW(window),700,550);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);

    //fondo de pantalla y marco
    wallpaper = gtk_image_new_from_file("wallpaper.jpg");
    fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window),fixed);
    gtk_fixed_put(GTK_FIXED(fixed), wallpaper, 0, 0);

    //Creación y configuración del label de mensaje
    lblMensaje = gtk_label_new("Por favor indique la cantidad de nodos con los que desea trabajar:");
    gtk_fixed_put(GTK_FIXED(fixed), lblMensaje, 50, 100);

    //Creación y configuración del botón de ir
    btnIr = gtk_button_new_with_label("");
    g_signal_connect(btnIr, "clicked", G_CALLBACK(ingresarNombres), (gpointer) window);
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

	//creación y configuración de spin button
    spinButton = gtk_spin_button_new_with_range  (1, 100, 1);
    gtk_fixed_put(GTK_FIXED(fixed), spinButton, 50, 150);

    //configuración final
    gtk_widget_show_all(window);
    gtk_main();
}
