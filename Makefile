CC     = gcc
CFLAGS = -Wall -O2 -I. $(shell pkg-config --cflags raylib)
LIBS   = $(shell pkg-config --libs raylib) -lm -ldl -lpthread

TARGET = grafika_dda

SRCS = main.c \
       coords.c \
       src/algo/dda.c \
       src/algo/bresenham.c \
       src/algo/midcircle.c \
       src/algo/kurvaBezierKuadratik.c \
       src/ui/back_button.c \
       src/screens/claw.c \
       src/screens/about.c \
       src/screens/menu.c \
       src/ui/prize.c \
       src/ui/drawClaw.c \
       src/ui/cable.c \
       src/ui/tombolCapit.c \
       src/ui/bodyMesin.c \
       src/ui/joystick.c \
       src/ui/tombolOut.c \
       src/ui/indikatorStatus.c \
       src/ui/indikatorSkor.c \
       src/screens/sound.c \
       src/effect/stonePrizeVfx.c \
       src/ui/lampu.c \
       src/screens/model.c

OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJS)

run: all
	LIBGL_ALWAYS_SOFTWARE=1 ./$(TARGET)
