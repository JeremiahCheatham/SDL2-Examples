TARGET		?= 08-SOUNDS
LIB_NAME	= libsdl_wrappers
CC			= gcc
CFLAGS		= -Wall -Werror
COBC		= cobc
COBCFLAGS	= -x -O -w -fstatic-call
LIBS		= -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -L. -l:$(LIB_NAME).a
AR			= ar
ARFLAGS		= rcs

all: $(TARGET)

$(LIB_NAME).o: $(LIB_NAME).c
	$(CC) $(CFLAGS) -c -o $@ $<

$(LIB_NAME).a: $(LIB_NAME).o
	$(AR) $(ARFLAGS) $@ $<

$(TARGET): $(TARGET).CBL $(LIB_NAME).a
	$(COBC) $(COBCFLAGS) $< $(LIBS) -o $@

clean:
	rm -f $(TARGET) $(LIB_NAME).o $(LIB_NAME).a

run: $(TARGET)
	./$<