all: heat2d heat2d-demo

CC = gcc
CFLAGS = -O -Wall -O3 
INCL= -I/System/Library/Frameworks/GLUT.framework/Versions/A/Headers
LIBPATH = -L/usr/X11R6/lib -L/sw/lib
LIBS = -lglut -lGLU -lGL -lXmu -lXi -lXext -lX11 -lm

heat2d: heat2d.c
	$(CC) $(CFLAGS) $(INCL) $(LIBPATH) -o $@ $< $(LIBS)

heat2d-demo: heat2d-demo.c
	$(CC) $(CFLAGS) $(INCL) $(LIBPATH) -o $@ $< $(LIBS)

coheat2d: coheat2d.c
	$(CC) $(CFLAGS) -o $@ $< -lm