# I am a comment, and I want to say that the variable CC will be
# the compiler to use.
CC=g++
# Hey!, I am comment number 2. I want to say that CFLAGS will be the
# options I'll pass to the compiler.
#next put the include directories
IDIR = inc
_DEPS = LinkedList.h DriverFile.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

CFLAGS=-g -Wall -Werror -I$(IDIR)
%.o: %.c $(DEPS)
		$(CC) -c -o $@ $< $(CFLAGS)

all:inc/LinkedList.h inc/DriverFile.h
	$(CC) $(CFLAGS) src/LinkedList.cpp src/DriverFile.cpp -o LinkedList && chmod a+x LinkedList
	
clean:
	rm -rf *.a  && rm LinkedList