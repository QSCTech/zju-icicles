LIB = -L /usr/lib/x86_64-linux-gnu -lX11 -lm
INC = -I /usr/include/X11 -I ./include

INCFILE	= all.h draw.h global.h
SOURCE = main.c init.c readline.c toview.c translate.c cast.c drawline.c draw_guide.c
OBJ = $(SOURCE:%.c=%.o)

draw:$(OBJ) 
	gcc -g $(OBJ) $(LIB) -o $@ 
%.o:%.c
	gcc -g -c $(INC) $< -o $@
clean:
	rm -f *.o
	rm draw
