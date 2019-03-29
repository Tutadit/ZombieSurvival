TARGET=bin/runner
TEST_TARGET=bin/test

SRCDIR=src
TEST_SRCDIR=test

BUILDDIR=build
TEST_BUILDDIR=build\test

OBJECTS=$(BUILDDIR)\model.o $(BUILDDIR)\raster.o $(BUILDDIR)\clear.o $(BUILDDIR)\player_b.o $(BUILDDIR)\zombie_b.o $(BUILDDIR)\misc_b.o $(BUILDDIR)\renderer.o $(BUILDDIR)\font.o $(BUILDDIR)\zs.o

TEST_OBJECTS=$(OBJECTS) $(TEST_BUILDDIR)\t_raster.o $(TEST_BUILDDIR)\t_player.o $(TEST_BUILDDIR)\t_render.o $(TEST_BUILDDIR)\t_runner.o

MATH_LIB=c:\c68\lib\libm.a

CC=cc68x
ASM=gen

ASMFLAGS=-D -L2
CFLAGS=-g -W3
INC=-Iinclude

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) $(MATH_LIB) -o $(TARGET)

$(BUILDDIR)\raster.o: $(SRCDIR)\raster.c
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

$(BUILDDIR)\model.o: $(SRCDIR)\model.c
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

$(BUILDDIR)\zombie.o: $(SRCDIR)\zombie.c
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

$(BUILDDIR)\renderer.o: $(SRCDIR)\renderer.c
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

$(BUILDDIR)\player_b.o: $(SRCDIR)\player_b.c
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

$(BUILDDIR)\zombie_b.o: $(SRCDIR)\zombie_b.c
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

$(BUILDDIR)\misc_b.o: $(SRCDIR)\misc_b.c
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

$(BUILDDIR)\clear.o: $(SRCDIR)\clear.s
	$(ASM) $(ASMFLAGS) $(INC) -O$@ $<

$(BUILDDIR)\font.o: $(SRCDIR)\font.c
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

$(BUILDDIR)\zs.o: $(SRCDIR)\zs.c
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

test: $(TEST_TARGET)
	%echo "Running tests..."
	bin/test

$(TEST_TARGET): $(TEST_OBJECTS)
	$(CC) $(CFLAGS) $(INC) $(TEST_OBJECTS) $(MATH_LIB) -o $@

$(TEST_BUILDDIR)\t_raster.o: $(TEST_SRCDIR)\t_raster.c
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

$(TEST_BUILDDIR)\t_player.o: $(TEST_SRCDIR)\t_player.c
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

$(TEST_BUILDDIR)\t_render.o: $(TEST_SRCDIR)\t_render.c
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

$(TEST_BUILDDIR)\t_runner.o: $(TEST_SRCDIR)\t_runner.c
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

clean:
	%Rm build\*.o
	%Rm build\test\*.o
