# Set the C compiler
CC = gcc

# Set the C flags
CFLAGS = -O3 -std=gnu99 -I.

# Source files
SRCS = 	global.c \
 		utilities.c \
 		xcmd.c \
 		anderson.c \
 		fileio.c \
 		leapfrog.c \
 		velocity.c \
 		datatype.c \
 		lj.c \
 		unit.c \
 		main.c \
 		verlet.c

# Objects
OBJS = $(SRCS:.c=.o)

# Program
Program = MD

all: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(Program)

.c.o: 
	$(CC) $(CFLAGS) -c $< -o $@
