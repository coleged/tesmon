#*************************************************************************\
#                  Copyright (C) Ed Cole 2016.                            *
#				 colege@gmail.com                         *
#                                                                         *
# This program is free software. You may use, modify, and redistribute it *
# under the terms of the GNU General Public License as published by the   *
# Free Software Foundation, either version 3 or (at your option) any      *
# later version. This program is distributed without any warranty.  See   *
# the file COPYING.gpl-v3 for details.                                    *
#                                                                         *
#*************************************************************************/
TARGET = tesmon
LIBS =
CC = g++
CFLAGS = -std=c++11
# DFLAGS for development build
DFLAGS = -D_DEBUG=true
LIBS = -L/usr/local/lib -lrestclient-cpp -lixwebsocket -lz -framework Security -framework Foundation
IFLAGS = -I/usr/local/include

.PHONY: default all clean install

default: $(TARGET)
all: default

OBJECTS = $(patsubst %.cpp, %.o, $(wildcard *.cpp))
HEADERS = $(wildcard *.hpp)

%.o: %.cpp $(HEADERS) Makefile
	$(CC) $(CFLAGS) $(IFLAGS) $(DFLAGS) -c $< -o $@

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): Makefile $(OBJECTS) $(HEADERS)
	$(CC)  $(LIBS) $(OBJECTS) \
		 -o $(TARGET)

clean:
	-rm -f *.o
	-rm -f $(TARGET)
