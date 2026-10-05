CC = gcc
CFLAGS = -Wall -Wextra -Werror -O2

TARGETS = avcat avgrep avsed

AVCAT_OBJ = avcat.o
AVGREP_OBJ = avgrep.o
AVSED_OBJ = avsed.o

ALL_OBJS = $(sort $(AVCAT_OBJ) $(AVGREP_OBJ) $(AVSED_OBJ))

all: $(TARGETS)

avcat: $(AVCAT_OBJ)
	$(CC) $(CFLAGS) -o $@ $^

avgrep: $(AVGREP_OBJ)
	$(CC) $(CFLAGS) -o $@ $^

avsed: $(AVSED_OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o

fclean: clean
	rm -f $(TARGETS)

.PHONY: all clean
