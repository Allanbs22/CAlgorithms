
/*
E: Cantidad de objetos, capasidad (limite),lista de obetos y matriz vacia de campos.
S: Matriz con solucion al problema.
R: La matriz debe ser de tamaño cantidad X capacidad.
O: Resolver el problema de la mochila en todas las versiones
*/
void mochila(struct objeto lista[cantObj],struct campo matriz[tamMochila+1][cantObj]){
    int posibles;
    for(int i=0;i<cantObj;i++){
        for(int a=0;a<tamMochila+1;a++){
            posibles = a/lista[i].peso;
            if(lista[i].existentes != -1 && posibles>lista[i].existentes){
               posibles = lista[i].existentes;
            }
                if(i != 0){
                    while((posibles != 0) && ((posibles*lista[i].valor + matriz[a-(lista[i].peso*posibles)][i-1].val) <= matriz[a][i-1].val)){
                        posibles--;
                    }
                    if(posibles == 0){
                        matriz[a][i].val = matriz[a][i-1].val;
                        matriz[a][i].color = 'r';
                    }
                    else{
                        matriz[a][i].val = posibles*lista[i].valor + matriz[a-(lista[i].peso*posibles)][i-1].val;
                        matriz[a][i].color = 'v';
                    }
                    
                }
                else{
                     if(posibles == 0){
                        matriz[a][i].val = 0;
                        matriz[a][i].color = 'r';
                    }
                    else{
                        matriz[a][i].val = posibles*lista[i].valor;
                        matriz[a][i].color = 'v';
                    }
                }
                matriz[a][i].cant = posibles;
               
        }
    }
   
}

/*
E: lista de obetos, matriz solucion, lista de respuesta. 
S: cantidad de utilizados para cada elemento
R: n/a
O: conseguir la respuesta final
*/

void solucion(struct objeto lista[cantObj], struct campo matriz[tamMochila+1][cantObj],int respuesta[cantObj]){
        int i = cantObj-1;
        int a = tamMochila;
        for(int x=0;x<cantObj;x++){
            respuesta[x] = 0;
        }
        while(a > 0){
            if(matriz[a][i].color == 'v'){
                respuesta[i] = matriz[a][i].cant;
                a = a-(lista[i].peso*matriz[a][i].cant);
            }
            i--;
            if(i < 0){
                a= 0;
            }
        }
}

/*
E: lista de objetos
S: formula inicial
R: ninguno
O: crear la formula que define el problema
*/
void formula(struct objeto lista[cantObj],char exprecion[25500]){
    char iniciar[255] = "Formula: ";
    strcat(exprecion,iniciar);
    char  limite[255];
    sprintf(limite," <= %d",tamMochila);
    for(int i=0;i<cantObj;i++){
        char buffer[255];
        sprintf(buffer,"%d(X%d)",lista[i].valor,i+1);
        strcat(exprecion,buffer);
        if(i+1 != cantObj){
            strcat(exprecion," + ");
        }
        else{
            strcat(exprecion," = Z");
        }
    }
    strcat(exprecion,"\nSujeto a: ");
    for(int i=0;i<cantObj;i++){
        char buffer[255];
        sprintf(buffer,"%d(X%d)",lista[i].peso,i+1);
        strcat(exprecion,buffer);
        if(i+1 != cantObj){
            strcat(exprecion," + ");
        }
    }
    strcat(exprecion,limite);
}


/*
*E: nombre del archivo a guardar y lista de objetos
*S: archivo guardado
*R: Ninguna
*O: guardar la lista de objetos
*/

void guardar(GtkWidget *dummy, gpointer entrada){
    struct objeto lista[cantObj];
    memcpy(lista,g_object_get_data(G_OBJECT(dummy), "datos"),cantObj*sizeof(struct objeto));
    char nombre[255];
    sprintf(nombre,"%s",(char *)gtk_entry_get_text(entrada));
    char texto[15000];
    if(strcmp(nombre,"") != 0){
        strcat(nombre,".ha");
        FILE *archivo = fopen(nombre,"w");
        sprintf(texto,"%d,%d\n",cantObj,tamMochila);
        for(int i=0;i<cantObj;i++){
            char buffer[255];
            sprintf(buffer,"%d,%d,%d\n",lista[i].peso,lista[i].valor,lista[i].existentes);
            strcat(texto,buffer);
        }
        fputs(texto,archivo);
        fclose(archivo);
    }
}


/*
*E:Widget
*S:Ventana del widget cerrada y ventana de calculos abierta
*R:Ninguna
*O:Abrir la ventana de calculos de tabla
*/
void ventanaSolucion(GtkWidget *dummy, gpointer widget){
	//cierra la ventana anterior
	gtk_widget_hide(widget);
	gtk_main_quit();
	
	//fondo de pantalla
	GtkWidget *wallpaper, *fixed, *scrolled_window, *btnSiguiente, *windowFinal, *btnVolver, *lblMensaje2, *btnGuardar, *nombreArchivo;
	windowFinal = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(windowFinal, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    
    //configuración de ventana
    gtk_window_set_position(GTK_WINDOW(windowFinal), GTK_WIN_POS_CENTER);
    gtk_window_set_title(GTK_WINDOW(windowFinal), "Mostrando respuesta");
    gtk_window_set_default_size(GTK_WINDOW(windowFinal),1000,550);
    gtk_window_set_resizable(GTK_WINDOW(windowFinal), FALSE);

    //fondo de pantalla y marcos
    scrolled_window = gtk_scrolled_window_new (NULL, NULL);
    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window),GTK_POLICY_AUTOMATIC,GTK_POLICY_AUTOMATIC);
    gtk_widget_set_size_request (scrolled_window, 1000, 550);
    fixed = gtk_fixed_new();

    //define color de fondo de la ventana
    GdkColor color;
    gdk_color_parse("#119BAB", &color);
    gtk_widget_modify_bg(scrolled_window, GTK_STATE_NORMAL, &color);


    //Creación y configuración del label de mensaje
    GtkWidget *lblMensaje = gtk_label_new("Solución final:");
    gtk_fixed_put(GTK_FIXED(fixed), lblMensaje, 50, 100);
    int res[cantObj];
    memcpy(res, g_object_get_data(G_OBJECT(dummy), "mmv"),cantObj*sizeof(int));
    struct objeto lista[cantObj];
    memcpy(lista,g_object_get_data(G_OBJECT(dummy), "lista"),cantObj*sizeof(struct objeto));

    int z =0;
    for(int i =0;i<cantObj;i++){
        z += lista[i].valor*res[i];
    }
    char valorZ[100];
    sprintf(valorZ,"<span font_desc=\"20.0\">Z   = %d</span>",z);

    //Creación y configuración del label de mensaje
    GtkWidget *lblMensajeZ = gtk_label_new("Z  = ");
    gtk_fixed_put(GTK_FIXED(fixed), lblMensajeZ, 170, 150);
    gtk_label_set_markup(GTK_LABEL(lblMensajeZ),valorZ);
  
    for(int i = 0; i < cantObj; i++){
            char variable[80];
            sprintf(variable,"<span font_desc=\"20.0\">X%i = </span>",i+1);
            //sprintf(variable,"X%i = ",i+1);

    		//Label indicando X actual
            GtkWidget *lblMensajeVariable1 = gtk_label_new("");
            gtk_label_set_markup(GTK_LABEL(lblMensajeVariable1), variable);
            gtk_fixed_put(GTK_FIXED(fixed), lblMensajeVariable1, 170, 230+80*i);


            char variable2[80];
            sprintf(variable2,"<span font_desc=\"20.0\">%i</span>",res[i]);
            //sprintf(variable,"X%i = ",i+1);

    		//Label indicando X actual
            GtkWidget *lblMensajeVariable2 = gtk_label_new("");
            gtk_label_set_markup(GTK_LABEL(lblMensajeVariable2), variable2);
            gtk_fixed_put(GTK_FIXED(fixed), lblMensajeVariable2, 240, 230+80*i);
    }

    //Creación y configuración del entry de nombre del archivo
	nombreArchivo = gtk_entry_new();
	gtk_fixed_put(GTK_FIXED(fixed), nombreArchivo, 350, 230+80*(cantObj+1));

	//creación de label de mensaje 2
	lblMensaje2 = gtk_label_new("Indique el nombre del archivo a guardar:");
	gtk_fixed_put(GTK_FIXED(fixed), lblMensaje2, 250, 210+80*(cantObj+1));

	//Creación y configuración del botón de guardar
	btnGuardar = gtk_button_new_with_label("");
	g_signal_connect(btnGuardar, "clicked", G_CALLBACK(guardar),nombreArchivo);
    g_object_set_data(G_OBJECT(btnGuardar),"datos",lista);
	gtk_fixed_put(GTK_FIXED(fixed), btnGuardar, 530, 230+80*(cantObj+1));
	GtkWidget *imgGuardar = gtk_image_new_from_file("button_guardar.png");
	gtk_button_set_always_show_image(GTK_BUTTON(btnGuardar),TRUE);
	gtk_button_set_image(GTK_BUTTON(btnGuardar), imgGuardar);


    //Creación y configuración del botón de volver
    btnVolver = gtk_button_new_with_label("");
    g_signal_connect(btnVolver, "clicked", G_CALLBACK(volverAPrincipal), (gpointer) windowFinal);
    gtk_fixed_put(GTK_FIXED(fixed), btnVolver, 50, 230+80*(cantObj+1));
    GtkWidget *imgVolver = gtk_image_new_from_file("button_volver.png");
    gtk_button_set_always_show_image(GTK_BUTTON(btnVolver),TRUE);
    gtk_button_set_image(GTK_BUTTON(btnVolver), imgVolver);

    

    //configuración final
    gtk_container_add(GTK_CONTAINER(scrolled_window),fixed);
    gtk_container_add(GTK_CONTAINER(windowFinal),scrolled_window);
    gtk_widget_show_all(windowFinal);
    gtk_main();
}


/*
*E:Widget
*S:Ventana del widget cerrada y ventana de calculos abierta
*R:Ninguna
*O:Abrir la ventana de calculos de tabla
*/
void ventanaTabla(GtkWidget *dummy, struct objeto listaObjetos[cantObj]){


	//fondo de pantalla
	GtkWidget *wallpaper, *fixed, *scrolled_window, *btnSiguiente, *windowTabla, *btnVolver;
	windowTabla = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(windowTabla, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    
    //configuración de ventana
    gtk_window_set_position(GTK_WINDOW(windowTabla), GTK_WIN_POS_CENTER);
    gtk_window_set_title(GTK_WINDOW(windowTabla), "Mostrando tabla");
    gtk_window_set_default_size(GTK_WINDOW(windowTabla),1000,550);
    gtk_window_set_resizable(GTK_WINDOW(windowTabla), FALSE);

    //fondo de pantalla y marcos
    scrolled_window = gtk_scrolled_window_new (NULL, NULL);
    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window),GTK_POLICY_AUTOMATIC,GTK_POLICY_AUTOMATIC);
    gtk_widget_set_size_request (scrolled_window, 1000, 550);
    fixed = gtk_fixed_new();

    //define color de fondo de la ventana
    GdkColor color;
    gdk_color_parse("#119BAB", &color);
    gtk_widget_modify_bg(scrolled_window, GTK_STATE_NORMAL, &color);

    struct campo matriz[tamMochila+1][cantObj];
    mochila(listaObjetos,matriz);
    int res[cantObj];
    solucion(listaObjetos,matriz,res);
    char texto[1000];
    char X[100];
    char tam[100];
    char formula_label[2550] = "";
    GdkColor rojo;
    GdkColor verde;
    gdk_color_parse ("red", &rojo);
    gdk_color_parse ("green", &verde);
    formula(listaObjetos,formula_label);
    for(int i=0;i<tamMochila+1;i++){
        for(int a=0;a<cantObj;a++){
            if(i==0 && a == 0){
               GtkWidget *FL = gtk_label_new(formula_label);
                gtk_fixed_put(GTK_FIXED(fixed), FL, 10+10*a, 10+10*i);
            }
            if (i == 0){
                snprintf(X,sizeof(X),"X%d",a+1);
                GtkWidget *posicionX = gtk_label_new(X);
                gtk_fixed_put(GTK_FIXED(fixed), posicionX, 50+120*a, 75+50*i);
            }
            if(a==0){
                snprintf(tam,sizeof(tam),"%d",i);
                GtkWidget *tamactual = gtk_label_new(tam);
                gtk_fixed_put(GTK_FIXED(fixed), tamactual, 25+120*a, 100+50*i);
            }
            snprintf(texto,sizeof(texto),"%d\nX%d=%d",matriz[i][a].val,a+1,matriz[i][a].cant);
            GtkWidget *lblName = gtk_label_new(texto);
            gtk_fixed_put(GTK_FIXED(fixed), lblName, 50+120*a, 100+50*i);
            if(matriz[i][a].color == 'r'){
                gtk_widget_modify_fg (lblName, GTK_STATE_NORMAL, &rojo);
            }
            else{
                gtk_widget_modify_fg (lblName, GTK_STATE_NORMAL, &verde);
            }
            
        }
    }

    //Creación y configuración del botón de siguiente
    btnSiguiente = gtk_button_new_with_label("");
    g_signal_connect(btnSiguiente, "clicked", G_CALLBACK(ventanaSolucion), (gpointer) windowTabla);
    g_object_set_data(G_OBJECT(btnSiguiente), "lista",listaObjetos);
    gtk_fixed_put(GTK_FIXED(fixed), btnSiguiente, 550, 200+50*(tamMochila+1));
    GtkWidget *imgSiguiente = gtk_image_new_from_file("button_siguiente.png");
    gtk_button_set_always_show_image(GTK_BUTTON(btnSiguiente),TRUE);
    gtk_button_set_image(GTK_BUTTON(btnSiguiente), imgSiguiente);
    g_object_set_data(G_OBJECT(btnSiguiente), "mmv",res);


    //Creación y configuración del botón de volver
    btnVolver = gtk_button_new_with_label("");
    g_signal_connect(btnVolver, "clicked", G_CALLBACK(volverAPrincipal), (gpointer) windowTabla);
    gtk_fixed_put(GTK_FIXED(fixed), btnVolver, 50, 200+50*(tamMochila+1));
    GtkWidget *imgVolver = gtk_image_new_from_file("button_volver.png");
    gtk_button_set_always_show_image(GTK_BUTTON(btnVolver),TRUE);
    gtk_button_set_image(GTK_BUTTON(btnVolver), imgVolver);

    

    //configuración final
    gtk_container_add(GTK_CONTAINER(scrolled_window),fixed);
    gtk_container_add(GTK_CONTAINER(windowTabla),scrolled_window);
    gtk_widget_show_all(windowTabla);
    gtk_main();
}
