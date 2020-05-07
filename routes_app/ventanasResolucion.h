

/*
*E:Widget y matriz p
*S:Ventana del widget cerrada y ventana de P abierta
*R:Ninguna
*O:Abrir la ventana de la tabla P
*/
void ventanaP(GtkWidget *dummy, int valores[tam][tam]){
	
	GtkWidget *window, *wallpaper, *fixed, *scrolled_window, *btnSiguiente, *btnTabla;
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    
    //configuración de ventana
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_title(GTK_WINDOW(window), "Mostrando tabla P");
    gtk_window_set_default_size(GTK_WINDOW(window),1000,550);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);

    //fondo de pantalla y marcos
    scrolled_window = gtk_scrolled_window_new (NULL, NULL);
    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window),GTK_POLICY_AUTOMATIC,GTK_POLICY_AUTOMATIC);
    gtk_widget_set_size_request (scrolled_window, 1000, 550);
    fixed = gtk_fixed_new();

    //define color de fondo de la ventana
    GdkColor color;
    gdk_color_parse("#119BAB", &color);
    gtk_widget_modify_bg(scrolled_window, GTK_STATE_NORMAL, &color);
    
	//cargando detalles de los nombres de los nodos
	char *name[tam];
	if(cargando == 1){
		char linea[2550];
		FILE *archivo;
		char *ch;
		char *dev;
		int pos = 0;
		archivo=fopen((char *)gtk_entry_get_text (GTK_ENTRY (ruta)),"r");
		dev = fgets(linea,2550,archivo);
		strtok(linea, "\n");
		ch = strtok(linea, ",");
		pos = 0;
		while (ch != NULL) {
			name[pos] = ch;
			ch = strtok(NULL,",");
			pos++;
		}
		fclose(archivo);
		entradas = malloc(sizeof(gpointer)*tam);
		for(int i = 0; i < tam; i++){
			GtkWidget *entry = gtk_entry_new();
			char buffer[64];
			snprintf(buffer, sizeof(buffer), "%s",name[i]);
			gtk_entry_set_text(GTK_ENTRY(entry), buffer);
			entradas[i] = (gpointer) entry;
		}
	}
    
    //creación de label de mensaje
    char buf[12];
    sprintf(buf, "P(%d)", tablaActual);
    lblTablaActual = gtk_label_new(buf);
    gtk_fixed_put(GTK_FIXED(fixed), lblTablaActual, 50, 50);

    //labels que se crean de forma dinámica según la cantidad de nodos
    for(int i = 0; i <= tam; i++){
    	for(int j = 0; j <= tam; j++){
    		if(i>0 || j>0){
	    		if(i==0){
						GtkWidget *lblName = gtk_label_new(gtk_entry_get_text (GTK_ENTRY (entradas[j-1])));
						gtk_fixed_put(GTK_FIXED(fixed), lblName, 50+120*j, 100+50*i);
	    		}
	    		else if(j==0){
						GtkWidget *lblName = gtk_label_new(gtk_entry_get_text (GTK_ENTRY (entradas[i-1])));
						gtk_fixed_put(GTK_FIXED(fixed), lblName, 50+120*j, 100+50*i);
	    		}
	    		else {
	    			char buffer[32];
	    			if(valores[i-1][j-1]>=0)
						snprintf(buffer, sizeof(buffer), "%d",valores[i-1][j-1]);
					else
						snprintf(buffer, sizeof(buffer), "%d",valores[i-1][j-1]+1);
			    	GtkWidget *lblName = gtk_label_new(buffer);
				    gtk_fixed_put(GTK_FIXED(fixed), lblName, 50+120*j, 100+50*i);
			    }
			}
    	}
    }


    //configuración final
    gtk_container_add(GTK_CONTAINER(scrolled_window),fixed);
    gtk_container_add(GTK_CONTAINER(window),scrolled_window);
    gtk_widget_show_all(window);
    gtk_main();

}



/*
*E:Matriz de caminos, origen y destino
*S:Ruta más corta entre origen y destino calculada
*R:Origen y destino existentes
*O:Mostrar la ruta más corta entre un origen y un destino de un grafo
*/
void calcularRuta(GtkWidget *dummy, int valores[tam][tam]){
	int indice = gtk_combo_box_get_active (GTK_COMBO_BOX(combo1));
	int indice2 = gtk_combo_box_get_active (GTK_COMBO_BOX(combo2));
	char name1[3200];
	char name2[3200];
	snprintf(name1,sizeof(name1),"%s",(char *)gtk_entry_get_text (GTK_ENTRY (entradas[indice])));
	snprintf(name2,sizeof(name2),"%s",(char *)gtk_entry_get_text (GTK_ENTRY (entradas[indice2])));
	gtk_label_set_text(GTK_LABEL(lblRuta),rutamascorta(name1,name2,valores));
}




/*
*E:Widget
*S:Ventana del widget cerrada y ventana de calculos finales abierta
*R:Ninguna
*O:Abrir la ventana de calculos finales
*/
void ventanaFinal(int valores[tam][tam]){

	//carga el valor de tamaño

	
	GtkWidget *window, *wallpaper, *fixed, *lblMensaje, *btnRuta, *btnVolver;
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    
    //configuración de ventana
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_title(GTK_WINDOW(window), "Verificar caminos");
    gtk_window_set_default_size(GTK_WINDOW(window),700,550);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);

    fixed = gtk_fixed_new();

    //fondo de pantalla y marco
    wallpaper = gtk_image_new_from_file("wallpaper.jpg");
    fixed = gtk_fixed_new();
    gtk_fixed_put(GTK_FIXED(fixed), wallpaper, 0, 0);

    //creación de label de mensaje
    lblMensaje = gtk_label_new("Indique los nodos a verificar:");
    gtk_fixed_put(GTK_FIXED(fixed), lblMensaje, 50, 50);

    //creación de label de ruta
    lblRuta = gtk_label_new("");
    gtk_fixed_put(GTK_FIXED(fixed), lblRuta,50, 300);


	//crear combo box
	combo1 = gtk_combo_box_text_new ();
	combo2 = gtk_combo_box_text_new ();
	
	//cargando detalles de los nombres de los nodos
	char *name[tam];
	if(cargando == 1){
		char linea[2550];
		FILE *archivo;
		char *ch;
		char *dev;
		int pos = 0;
		archivo=fopen((char *)gtk_entry_get_text (GTK_ENTRY (ruta)),"r");
		dev = fgets(linea,2550,archivo);
		strtok(linea, "\n");
		ch = strtok(linea, ",");
		pos = 0;
		while (ch != NULL) {
			name[pos] = ch;
			ch = strtok(NULL,",");
			pos++;
		}
		fclose(archivo);
		entradas = malloc(sizeof(gpointer)*tam);
		for(int i = 0; i < tam; i++){
			GtkWidget *entry = gtk_entry_new();
			char buffer[64];
			snprintf(buffer, sizeof(buffer), "%s",name[i]);
			gtk_entry_set_text(GTK_ENTRY(entry), buffer);
			entradas[i] = (gpointer) entry;
		}
	}

    for(int i = 0; i < tam; i++){
		if(cargando == 0){
			gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (combo1), gtk_entry_get_text (GTK_ENTRY (entradas[i])));
			gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (combo2), gtk_entry_get_text (GTK_ENTRY (entradas[i])));
		}
		else{
			gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (combo1), name[i]);
			gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (combo2), name[i]);
		}
    }
    gtk_combo_box_set_active (GTK_COMBO_BOX(combo1), 0);
    gtk_combo_box_set_active (GTK_COMBO_BOX(combo2), 0);
    gtk_fixed_put(GTK_FIXED(fixed), combo1, 100, 100);
    gtk_fixed_put(GTK_FIXED(fixed), combo2, 200, 100);

    //Creación y configuración del botón de ruta
    btnRuta = gtk_button_new_with_label("");
    g_signal_connect(btnRuta, "clicked", G_CALLBACK(calcularRuta),valores);
    gtk_fixed_put(GTK_FIXED(fixed), btnRuta, 100, 200);
    GtkWidget *imgRuta = gtk_image_new_from_file("button_obtener-ruta.png");
    gtk_button_set_always_show_image(GTK_BUTTON(btnRuta),TRUE);
    gtk_button_set_image(GTK_BUTTON(btnRuta), imgRuta);

    //Creación y configuración del botón de volver
    btnVolver = gtk_button_new_with_label("");
    g_signal_connect(btnVolver, "clicked", G_CALLBACK(volverAPrincipal), (gpointer) window);
    gtk_fixed_put(GTK_FIXED(fixed), btnVolver, 450, 350);
    GtkWidget *imgVolver = gtk_image_new_from_file("button_volver.png");
    gtk_button_set_always_show_image(GTK_BUTTON(btnVolver),TRUE);
    gtk_button_set_image(GTK_BUTTON(btnVolver), imgVolver);

    //configuración final
    gtk_container_add(GTK_CONTAINER(window),fixed);
    gtk_widget_show_all(window);
    gtk_main();
}


/*
*E:matriz D actual
*S:Ventana del widget cerrada y ventana de tabla D abierta
*R:Ninguna
*O:Abrir la ventana de tabla D
*/
void ventanaD(GtkWidget *dummy, int valores[2][tam][tam]){
	tablaActual++;
	//int value = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON(spinButton));
	
	if(cargando==0 || tablaActual>0){
		//cierra la ventana anterior
		gtk_widget_hide(windowValores);
		gtk_main_quit();
	}
	
	//Si la tabla actual aún no sobrepasa la final, muestra el D(I)
	if(tablaActual<=tam){
		GtkWidget *wallpaper, *fixed, *scrolled_window, *btnSiguiente, *btnTabla, *btnGuardar, *lblMensaje2;
		windowValores = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	    g_signal_connect(windowValores, "destroy", G_CALLBACK(gtk_main_quit), NULL);
		if(tablaActual>0){
			floyd(valores[1],valores[0],tablaActual);
		}
		else
			PDefault(valores[1],valores[0]);
		
		//cargando detalles de los nombres de los nodos
		char *name[tam];
		if(cargando == 1){
			char linea[2550];
			FILE *archivo;
			char *ch;
			char *dev;
			int pos = 0;
			archivo=fopen((char *)gtk_entry_get_text (GTK_ENTRY (ruta)),"r");
			dev = fgets(linea,2550,archivo);
			strtok(linea, "\n");
			ch = strtok(linea, ",");
			pos = 0;
			while (ch != NULL) {
				name[pos] = ch;
				ch = strtok(NULL,",");
				pos++;
			}
			fclose(archivo);
			entradas = malloc(sizeof(gpointer)*tam);
			for(int i = 0; i < tam; i++){
				GtkWidget *entry = gtk_entry_new();
				char buffer[64];
				snprintf(buffer, sizeof(buffer), "%s",name[i]);
				gtk_entry_set_text(GTK_ENTRY(entry), buffer);
				entradas[i] = (gpointer) entry;
			}
		}
	    //configuración de ventana
	    gtk_window_set_position(GTK_WINDOW(windowValores), GTK_WIN_POS_CENTER);
	    gtk_window_set_title(GTK_WINDOW(windowValores), "Calculando respuesta");
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
		char buf[12];
	    sprintf(buf, "D(%d)", tablaActual);
	    lblTablaActual = gtk_label_new(buf);
	    gtk_fixed_put(GTK_FIXED(fixed), lblTablaActual, 50, 50);
		
	    //labels que se crean de forma dinámica según la cantidad de nodos
	    for(int i = 0; i <= tam; i++){
	    	for(int j = 0; j <= tam; j++){
	    		if(i>0 || j>0){
		    		if(i==0){
							GtkWidget *lblName = gtk_label_new(gtk_entry_get_text (GTK_ENTRY (entradas[j-1])));
							gtk_fixed_put(GTK_FIXED(fixed), lblName, 50+120*j, 100+50*i);
		    		}
		    		else if(j==0){
							GtkWidget *lblName = gtk_label_new(gtk_entry_get_text (GTK_ENTRY (entradas[i-1])));
							gtk_fixed_put(GTK_FIXED(fixed), lblName, 50+120*j, 100+50*i);
		    		}
		    		else {
		    			char buffer[32];
						snprintf(buffer, sizeof(buffer), "%d",valores[1][i-1][j-1]);
				    	GtkWidget *lblName = gtk_label_new(buffer);
				    	if(valores[0][i-1][j-1]==tablaActual && tablaActual>0){
				    		GdkColor color;
							gdk_color_parse ("#00ff00", &color);
							gtk_widget_modify_fg (lblName, GTK_STATE_NORMAL, &color);
				    	}
					    gtk_fixed_put(GTK_FIXED(fixed), lblName, 50+120*j, 100+50*i);
				    }
				}
	    	}
	    }


	    //Creación y configuración del botón de siguiente
	    btnSiguiente = gtk_button_new_with_label("");
	    g_signal_connect(btnSiguiente, "clicked", G_CALLBACK(ventanaD), valores);
	    gtk_fixed_put(GTK_FIXED(fixed), btnSiguiente, 50, 100+50*(tam+1));
	    GtkWidget *imgSiguiente = gtk_image_new_from_file("button_siguiente.png");
	    gtk_button_set_always_show_image(GTK_BUTTON(btnSiguiente),TRUE);
	    gtk_button_set_image(GTK_BUTTON(btnSiguiente), imgSiguiente);

	    //Creación y configuración del botón de ver tabla P
	    btnTabla = gtk_button_new_with_label("");
	    g_signal_connect(btnTabla, "clicked", G_CALLBACK(ventanaP), valores[0]);
	    gtk_fixed_put(GTK_FIXED(fixed), btnTabla, 50+120*(tam+1), 100+50*(tam+1));
	    GtkWidget *imgTabla = gtk_image_new_from_file("button_ver-tabla-p.png");
	    gtk_button_set_always_show_image(GTK_BUTTON(btnTabla),TRUE);
	    gtk_button_set_image(GTK_BUTTON(btnTabla), imgTabla);
	    if(tablaActual==0){
			//Creación y configuración del entry de nombre del archivo
			nombreArchivo = gtk_entry_new();
			gtk_fixed_put(GTK_FIXED(fixed), nombreArchivo, 350, 200+50*(tam+1));

			//creación de label de mensaje 2
			lblMensaje2 = gtk_label_new("Indique el nombre del archivo a guardar:");
			gtk_fixed_put(GTK_FIXED(fixed), lblMensaje2, 250, 180+50*(tam+1));

			//Creación y configuración del botón de guardar
			btnGuardar = gtk_button_new_with_label("");
			g_signal_connect(btnGuardar, "clicked", G_CALLBACK(crear_archivo), valores[1]);
			gtk_fixed_put(GTK_FIXED(fixed), btnGuardar, 530, 200+50*(tam+1));
			GtkWidget *imgGuardar = gtk_image_new_from_file("button_guardar-datos.png");
			gtk_button_set_always_show_image(GTK_BUTTON(btnGuardar),TRUE);
			gtk_button_set_image(GTK_BUTTON(btnGuardar), imgGuardar);
		}

	    //configuración final
	    gtk_container_add(GTK_CONTAINER(scrolled_window),fixed);
	    gtk_container_add(GTK_CONTAINER(windowValores),scrolled_window);
	    gtk_widget_show_all(windowValores);
	    gtk_main();
	}
	//Si ya se superó la ultima tabla D se envía a la ventana de caminos más cortos
	else{
		ventanaFinal(valores[0]);
	}
}
