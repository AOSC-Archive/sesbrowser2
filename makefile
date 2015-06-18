TARGET = sesbrowser
FROM = src/main.cpp src/SESBrowser.cpp src/MainWindow.cpp src/BrowserAction.cpp
CXX = gcc
FLAGS = `pkg-config --cflags --libs --static gtk+-3.0 webkit2gtk-4.0` -std="c++11"

${TARGET}:	${FROM} src/sesbrowser.h
	${CXX} ${FROM} -o $@ ${FLAGS} -O3

all:	${TARGET}

run:	all
	./sesbrowser
