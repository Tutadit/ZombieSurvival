TARGET=os.prg
OS_IMG=os.img

TEST_TARGET=bin/test

SRCDIR=src
TEST_SRCDIR=test

BUILDDIR=build
TEST_BUILDDIR=build\test

OBJECTS=$(BUILDDIR)\start.o 	$(BUILDDIR)\init.o   	$(BUILDDIR)\vbl_isr.o 	\
		$(BUILDDIR)\kbd_isr.o 	$(BUILDDIR)\clear.o 	$(BUILDDIR)\ints.o 		\
		$(BUILDDIR)\player_b.o 	$(BUILDDIR)\zombie_b.o 	$(BUILDDIR)\misc_b.o 	\
		$(BUILDDIR)\renderer.o 	$(BUILDDIR)\effects.o  	$(BUILDDIR)\zs_math.o 	\
		$(BUILDDIR)\raster.o   	$(BUILDDIR)\music.o 	$(BUILDDIR)\model.o 	\
		$(BUILDDIR)\input.o 	$(BUILDDIR)\font.o 		$(BUILDDIR)\psg.o 		\
		$(BUILDDIR)\setup.o		$(BUILDDIR)\main.o

TEST_OBJECTS=	$(OBJECTS) \
				$(TEST_BUILDDIR)\t_raster.o	$(TEST_BUILDDIR)\t_player.o \
			 	$(TEST_BUILDDIR)\t_render.o	$(TEST_BUILDDIR)\t_runner.o

CC=cc68x
ASM=gen
LINKER=ld

ASMFLAGS=-L2
CFLAGS=-W3
INC=-Iinclude

$(OS_IMG): $(TARGET)
	burnroms

$(TARGET): $(OBJECTS)
	@%echo linking...
	@$(LINKER) -o $@ $(OBJECTS)

$(BUILDDIR)\clear.o: $(SRCDIR)\clear.s
	@%echo $(ASM) $<
	@$(ASM) $(ASMFLAGS) -O$@ $<

$(BUILDDIR)\start.o: $(SRCDIR)\start.s
	@%echo $(ASM) $<
	@$(ASM) $(ASMFLAGS) -O$@ $<

$(BUILDDIR)\ints.o: $(SRCDIR)\ints.s
	@%echo $(ASM) $<
	@$(ASM) $(ASMFLAGS) -O$@ $<

$(BUILDDIR)\vbl_isr.o: $(SRCDIR)\vbl_isr.s
	@%echo $(ASM) $<
	@$(ASM) $(ASMFLAGS) -O$@ $<

$(BUILDDIR)\kbd_isr.o: $(SRCDIR)\kbd_isr.s
	@%echo $(ASM) $<
	@$(ASM) $(ASMFLAGS) $(INC) -O$@ $<

$(BUILDDIR)\player_b.o: $(SRCDIR)\player_b.c
	@%echo $(CC) $<
	@$(CC) $(CFLAGS) $(INC) -c -o $@ $<

$(BUILDDIR)\zombie_b.o: $(SRCDIR)\zombie_b.c
	@%echo $(CC) $<
	@$(CC) $(CFLAGS) $(INC) -c -o $@ $<

$(BUILDDIR)\misc_b.o: $(SRCDIR)\misc_b.c
	@%echo $(CC) $<
	@$(CC) $(CFLAGS) $(INC) -c -o $@ $<

$(BUILDDIR)\renderer.o: $(SRCDIR)\renderer.c
	@%echo $(CC) $<
	@$(CC) $(CFLAGS) $(INC) -c -o $@ $<

$(BUILDDIR)\effects.o: $(SRCDIR)\effects.c
	@%echo $(CC) $<
	@$(CC) $(CFLAGS) $(INC) -c -o $@ $<

$(BUILDDIR)\zs_math.o: $(SRCDIR)\zs_math.c
	@%echo $(CC) $<
	@$(CC) $(CFLAGS) $(INC) -c -o $@ $<

$(BUILDDIR)\raster.o: $(SRCDIR)\raster.c
	@%echo $(CC) $<
	@$(CC) $(CFLAGS) $(INC) -c -o $@ $<

$(BUILDDIR)\music.o: $(SRCDIR)\music.c
	@%echo $(CC) $<
	@$(CC) $(CFLAGS) $(INC) -c -o $@ $<

$(BUILDDIR)\model.o: $(SRCDIR)\model.c
	@%echo $(CC) $<
	@$(CC) $(CFLAGS) $(INC) -c -o $@ $<

$(BUILDDIR)\input.o: $(SRCDIR)\input.c
	@%echo $(CC) $<
	@$(CC) $(CFLAGS) $(INC) -c -o $@ $<

$(BUILDDIR)\font.o: $(SRCDIR)\font.c
	@%echo $(CC) $<
	@$(CC) $(CFLAGS) $(INC) -c -o $@ $<

$(BUILDDIR)\psg.o: $(SRCDIR)\psg.c
	@%echo $(CC) $<
	@$(CC) $(CFLAGS) $(INC) -c -o $@ $<

$(BUILDDIR)\init.o: $(SRCDIR)\init.c
	@%echo $(CC) $<
	@$(CC) $(CFLAGS) $(INC) -c -o $@ $<

$(BUILDDIR)\setup.o: $(SRCDIR)\setup.c
	@%echo $(CC) $<
	@$(CC) $(CFLAGS) $(INC) -c -o $@ $<

$(BUILDDIR)\main.o: $(SRCDIR)\main.c
	@%echo $(CC) $<
	@$(CC) $(CFLAGS) $(INC) -c -o $@ $<

test: $(TEST_TARGET)
	@echo Running tests...
	@bin/test

$(TEST_TARGET): $(TEST_OBJECTS)
	@%echo $(CC) $<
	@$(CC) $(CFLAGS) $(INC) $(TEST_OBJECTS) $(MATH_LIB) -o $@

$(TEST_BUILDDIR)\t_raster.o: $(TEST_SRCDIR)\t_raster.c
	@%echo $(CC) $<
	@$(CC) $(CFLAGS) $(INC) -c -o $@ $<

$(TEST_BUILDDIR)\t_player.o: $(TEST_SRCDIR)\t_player.c
	@%echo $(CC) $<
	@$(CC) $(CFLAGS) $(INC) -c -o $@ $<

$(TEST_BUILDDIR)\t_render.o: $(TEST_SRCDIR)\t_render.c
	@%echo $(CC) $<
	@$(CC) $(CFLAGS) $(INC) -c -o $@ $<

$(TEST_BUILDDIR)\t_runner.o: $(TEST_SRCDIR)\t_runner.c
	@%echo $(CC) $<
	@$(CC) $(CFLAGS) $(INC) -c -o $@ $<

all: clean $(OS_IMG)
clean:
	@%echo Cleaning...
	@%Rm $(BUILDDIR)\*
	@%Rm os.img os.prg
