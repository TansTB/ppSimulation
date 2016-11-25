CFLAGS = `root-config --libs` -lMinuit `root-config --cflags` --std=c++11
HEADERS = Point.h MyParser.h
OBJECTS = RunManager.o Point.o MyParser.o

%.o: %.cxx $(HEADERS)
	g++ -c -o $@ $< $(CFLAGS)

ppSimulation: $(OBJECTS)
	g++ -o ppSimulation $^ $(CFLAGS)
	rm *.o