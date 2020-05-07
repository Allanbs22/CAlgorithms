void Matrices(int M[cantE][cantE],int P[cantE][cantE],int D[cantE+1]){
    for(int i=0;i<cantE;i++){
        for(int j=0;j<cantE;j++){
        M[i][j] = 0;
        P[i][j] = 0;
        }
    }
    for(int i =0;i<cantE;i++){
        M[i][i] = 0;
        P[i][i] = 0;
        if(i+1 != cantE){
            M[i][i+1] = D[i]*D[i+1]*D[i+2];
            P[i][i+1] = i+1;
        }
    }

    int x = 0;
    int y = 2;
    int actual;
    int peon;
    int k  = 0;
    int ciclo = 1;
    int vuelta = 1;
    while(ciclo == 1 && cantE > 2){
        actual = -1;
        for(int i =x;i<y;i++){
            if(i <= y-1){
                peon = M[x][i] + M[i+1][y] + (D[x]*D[y+1]*D[i+1]);
                if(actual == -1  ||  actual>peon){
                    k= i+1;
                    actual  = peon;
                }
            }
        }
        M[x][y] = actual;
        P[x][y] = k;
        x++;
        y++;
        if(y == cantE){
            x = 0;
            y = vuelta+2;
            vuelta++;
            if(y == cantE){
                ciclo = 0;
            }
        }
    }
}

int pertenece(int ele,int lista[cantE]){
    for(int i = 0;i<cantE;i++){
        if(ele == lista[i]){
            return 1;
        }
    }
    return 0;
}

void agregarultimos(int lista[cantE]){
    int pos = 0;
    for(int i = 1;i<cantE+1;i++){
        if(pertenece(i,lista) == 0){
            lista[pos] = i;
            pos++;
        }
    }
}
void invertir(int pq,int valores[pq]){
	int temp = 0;
	int ini = 0;
	int fin = pq-1;
	while(ini < fin){
		temp = valores[ini];
		valores[ini] = valores[fin];
		valores[fin] = temp;
		ini++;
		fin--;
	}
}
void orden(char txtOrden[2000],int P[cantE][cantE]){
    int inicio = 0;
    int fin = cantE-1;
    int corte = 0;
    int orden[cantE][cantE];
    int profundidad = 0;
    int vueltas = 0;
    int usados[cantE];
    int posusados = 2;
    int ultimo = fin;
    int agregando = 0;
    int pos = 0;
    int pq;
    for (int i = 0; i <cantE; i++){
    	for (int x = 0; x <cantE; x++){
        	orden[i][x] = 0; 
        }
    } 
    while((fin+1)-inicio != 2){
        corte = P[inicio][fin];
        if(corte-inicio <= (fin+1)-corte){
        	agregando = corte-inicio;
        	int valores[agregando];
        	pq = agregando;
        	inicio = corte;
        	while(agregando != 0){
            	valores[pos] =corte;
            	usados[posusados] = corte;
            	corte--;
            	posusados++;
            	pos++;
            	agregando --;
        	}
        	invertir(pq,valores);
        	for(int a = 0;a<pq;a++){
        		orden[profundidad][a] = valores[a];
        	}
        }
        else{
            agregando = (fin+1)-corte;
            fin = corte-1;
            while(agregando != 0){
            	orden[profundidad][pos] =corte+1;
            	usados[posusados] = corte+1;
            	posusados++;
            	corte++;
            	agregando --;
            	pos++;
        	}
        }
        pos = 0;
        profundidad++;
    }
    agregarultimos(usados);
    sprintf(txtOrden,"( A%d A%d )",usados[0],usados[1]);
    int iz = usados[0];
    int de = usados[1]; 
    pos = 0;
    for(int k = profundidad-1; k > -1;k--){
        char buferr3[2000];
        char buffer[1000];
        sprintf(buffer,"%s","(");
        while(orden[k][pos] != 0){
           char buffer2[10];
            sprintf(buffer2," A%d",orden[k][pos]);
            strcat(buffer,buffer2);
            pos++;
        }
        strcat(buffer," )");

        if (de+1 == orden[k][0]){
            sprintf(buferr3,"(%s %s)",txtOrden,buffer);
            de = orden[k][pos-1];
        }
        else{
            sprintf(buferr3,"(%s %s)",buffer,txtOrden);
            iz = orden[k][0];
        }
        pos = 0;
        sprintf(txtOrden,"%s","");
        strcat(txtOrden,buferr3);
    }
}

void guardar2(GtkWidget *dummy,int lista[cantE+1]){
    char nombre[255];
    char texto[15000];
    sprintf(nombre,"%s",gtk_entry_get_text (GTK_ENTRY (g_object_get_data(G_OBJECT(dummy), "nombre"))));
    if(strcmp(nombre,"") != 0){
        strcat(nombre,".ha");
        FILE *archivo = fopen(nombre,"w");
        sprintf(texto,"%d\n",cantE);
        for(int i=0;i<cantE+1;i++){
            char buffer[255];
            if(i+1 != cantE+1){
                sprintf(buffer,"%d,",lista[i]);
            }
            else{
                sprintf(buffer,"%d\n",lista[i]);
            }
            strcat(texto,buffer);
        }
        fputs(texto,archivo);
        fclose(archivo);
    }
}

void ventanaResultados(GtkWidget *dummy, gpointer widget,int D[cantE+1]){
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
    g_signal_connect(btnGuardar, "clicked", G_CALLBACK(guardar2),D);
    g_object_set_data(G_OBJECT(btnGuardar),"nombre",(gpointer)nombreArchivo);
    gtk_fixed_put(GTK_FIXED(fixed), btnGuardar, 60, 585);
    GtkWidget *imgGuardar = gtk_image_new_from_file("button_guardar.png");
    gtk_button_set_always_show_image(GTK_BUTTON(btnGuardar),TRUE);
    gtk_button_set_image(GTK_BUTTON(btnGuardar), imgGuardar);


    scrolled_window = gtk_scrolled_window_new (NULL, NULL);
    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window),GTK_POLICY_AUTOMATIC,GTK_POLICY_AUTOMATIC);


    int M[cantE][cantE];
    int P[cantE][cantE];
    
    Matrices(M,P,D);
    

    fixedScroll = gtk_fixed_new();

    
    GtkWidget *lblTexto = gtk_label_new("Tabla M");
    gtk_widget_set_size_request (lblTexto, 80, 60);
    gtk_fixed_put(GTK_FIXED(fixedScroll), lblTexto, 0, 0);

    for(int i=0;i<cantE;i++){
        char txtCuadro[200];
        sprintf(txtCuadro,"%i",i+1);
        GtkWidget *cuadro = gtk_label_new(txtCuadro);
        gtk_widget_set_size_request (cuadro, 80, 60);
        gtk_fixed_put(GTK_FIXED(fixedScroll), cuadro, 50+100*i, 10);

        sprintf(txtCuadro,"%i",i+1);
        GtkWidget *cuadro2 = gtk_label_new(txtCuadro);
        gtk_widget_set_size_request (cuadro2, 80, 60);
        gtk_fixed_put(GTK_FIXED(fixedScroll), cuadro2, 0, 70*(i+1));
    }


    for(int i=0;i<cantE;i++){
        for(int j=0;j<cantE;j++){
            char txtCuadro[200];
            sprintf(txtCuadro,"%i",M[j][i]);
            GtkWidget *cuadro = gtk_label_new(txtCuadro);
            GdkColor color;
            gdk_color_parse ("#F7FE2E", &color);
            gtk_widget_modify_bg (cuadro, GTK_STATE_NORMAL, &color);
            if(j==0 && i==cantE){
                gdk_color_parse ("#FE0000", &color);
            gtk_widget_modify_fg (cuadro, GTK_STATE_NORMAL, &color);
            }
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


    GtkWidget *cuadro2 = gtk_label_new("Tabla P");
    gtk_widget_set_size_request (cuadro2, 80, 60);
    gtk_fixed_put(GTK_FIXED(fixedScroll2), cuadro2,0, 0);


    for(int i=0;i<cantE;i++){
        char txtCuadro[200];
        sprintf(txtCuadro,"%i",i+1);
        GtkWidget *cuadro = gtk_label_new(txtCuadro);
        gtk_widget_set_size_request (cuadro, 80, 60);
        gtk_fixed_put(GTK_FIXED(fixedScroll2), cuadro, 50+100*i, 10);

        sprintf(txtCuadro,"%i",i+1);
        GtkWidget *cuadro2 = gtk_label_new(txtCuadro);
        gtk_widget_set_size_request (cuadro2, 80, 60);
        gtk_fixed_put(GTK_FIXED(fixedScroll2), cuadro2, 0, 70*(i+1));
    }


    for(int i=0;i<cantE;i++){
        for(int j=0;j<cantE;j++){
            char txtCuadro[200];
            sprintf(txtCuadro,"%i",P[j][i]);
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

	
	
	
	char txtOrden[2000] = "";
    orden(txtOrden,P);
    GtkWidget *lblOrdenMatrices = gtk_label_new(txtOrden);
    gtk_fixed_put(GTK_FIXED(fixedScroll3), lblOrdenMatrices, 10, 10);
	
	

    //define color de fondo de la ventana
    gdk_color_parse("#FFFFFF", &color);
    gtk_widget_modify_bg(scrolled_window3, GTK_STATE_NORMAL, &color);

    gtk_widget_set_size_request (scrolled_window3, 400, 50);

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