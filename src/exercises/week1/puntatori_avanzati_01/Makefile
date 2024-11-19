#CFLAGS+=-Wall -Wextra -ansi -pedantic -g
CFLAGS+=-Wall -Wextra -std=c11 -pedantic -g

objects = int_by_byte \
		  int_byte \
		  dangling_ptr_free \
		  dangling_ptr_outscope \
		  memleak_nofree \
		  array_copy \
		  void_ptr \

all: $(objects)

clean:
	$(RM) $(objects)
	$(RM) vgcore.*
