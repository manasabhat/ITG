CPP := g++
CPPFLAGS := -c
OPENCVFLAGS := `pkg-config --cflags opencv`
OPENCVLIBS := `pkg-config --libs opencv`
MATHFLAGS := -lm

all : main.o level1.o level2.o level3.o
	$(CPP) $(OPENCVFLAGS) $(MATHFLAGS) main.o level1.o level2.o level3.o capture.o metric.o validation.o greedy.o backtracking.o parse.o top_level.o -o main $(OPENCVLIBS)

main.o : header.h  main.cpp
		$(CPP) $(CPPFLAGS) $(OPENCVFLAGS) header.h main.cpp $(OPENCVLIBS)

#level_1.o : level1.o capture.o metric.o validation.o
#		$(CPP) $(CPPFLAGS) $(OPENCVFLAGS) capture.o metric.o validation.o level1.o

#level1.o : level1.cpp
#		$(CPP) $(CPPFLAGS) level1.cpp

#capture.o : capture.cpp
#		$(CPP) $(CPPFLAGS) $(OPENCVFLAGS) capture.cpp $(OPENCVLIBS)

#metric.o : metric.cpp
#		$(CPP) $(CPPFLAGS) $(OPENCVFLAGS) metric.cpp $(OPENCVLIBS)

#validation.o : validation.cpp
#		$(CPP) $(CPPFLAGS) $(OPENCVFLAGS) validation.cpp $(OPENCVLIBS)

level1.o : capture.cpp metric.cpp validation.cpp level1.cpp
	$(CPP) $(CPPFLAGS) $(OPENCVFLAGS)  header.h capture.cpp metric.cpp validation.cpp level1.cpp $(OPENCVLIBS)

#level1 : 
#	   $(CPP) $(OPENCVFLAGS)  header.h capture.cpp metric.cpp validation.cpp level1.cpp -o level1.o $(OPENCVLIBS)

level2.o :level2.cpp greedy.cpp parse.cpp backtracking.cpp
		$(CPP) $(CPPFLAGS) $(OPENCVFLAGS) $(MATHFLAGS) level2.cpp greedy.cpp parse.cpp backtracking.cpp $(OPENCVLIBS)

#greedy.o : greedy.cpp
#		$(CPP) $(CPPFLAGS) $(MATHFLAGS) greedy.cpp

level3.o :level3.cpp top_level.cpp
		$(CPP) $(CPPFLAGS) $(OPENCVFLAGS) $(MATHFLAGS) level3.cpp top_level.cpp $(OPENCVLIBS)

clean: 
	rm -f *.o *.gch
	rm -r output_*
