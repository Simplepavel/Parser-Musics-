includes = -l curl -l gumbo
files = main.cpp request.cpp parsers.cpp song.cpp

all:
	g++ $(files) -o main $(includes)