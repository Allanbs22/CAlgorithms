main: menu.c
	gcc menu.c -o menu `pkg-config --cflags gtk+-3.0` `pkg-config --libs gtk+-3.0`

menu.c:
