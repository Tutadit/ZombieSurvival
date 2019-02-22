OBJECTS = Raster.o Model.o
proj: $(OBJECTS)
    cc68x -g $(OBJECTS) -o proj

Raster.o: Raster.h
		cc68x -g -c Raster.c	

Model.o: model.h
		cc68x -g -c Model.c

clean:
		-rm *.o *~ core paper
