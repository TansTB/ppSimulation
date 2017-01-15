CFLAGS = `root-config --libs` -lMinuit `root-config --cflags` --std=c++11
HEADERS = Point.h Track.h Hit.h MultiplicityGenerator.h VtxGenerator.h TrackGenerator.h MyParser.h Noise.h EventGenerator.h 
OBJECTS = ppSimulation_dict.o Point.o Track.o Hit.o MultiplicityGenerator.o VtxGenerator.o TrackGenerator.o MyParser.o Noise.o EventGenerator.o RunManager.o 

all: ppSimulation 


%.o: %.cxx $(HEADERS) 
	g++ -c -o $@ $< $(CFLAGS)

ppSimulation_dict.cxx: $(HEADERS) ppSimulation_LinkDef.h 
	rootcint -f ppSimulation_dict.cxx -c -p $(HEADERS) ppSimulation_LinkDef.h
	
ppSimulation: $(OBJECTS)
	g++ -o ppSimulation $^ $(CFLAGS)

.PHONY: clean
clean: 
	rm -f *.o *_dict* ppSimulation
