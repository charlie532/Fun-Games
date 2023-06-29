CXX := g++

NAME = fungames

FLAGS = -g -Wall -export-dynamic `pkg-config --cflags gtk+-3.0`

LIBS = -export-dynamic `pkg-config --libs gtk+-3.0`

SRCS = src/tictactoe/ttt-view.cpp    \
       src/tictactoe/ttt-field.cpp   \
       src/tictactoe/ttt-check.cpp   \
       src/connect-four/cf-view.cpp  \
       src/connect-four/cf-field.cpp \
       src/connect-four/cf-check.cpp \
       src/mill/mill-view.cpp        \
       src/mill/mill-field.cpp       \
       src/mill/mill-check.cpp       \
       src/checkers/chks-view.cpp    \
       src/checkers/chks-field.cpp   \
       src/checkers/chks-check.cpp   \
       src/window.cpp                \
       src/preview.cpp               \
       src/main.cpp

.PHONY: all clean

all: $(SRCS)
	$(CXX) $(FLAGS) $(SRCS) $(LIBS) -o $(NAME)

clean: $(NAME)
	rm $(NAME)

install: $(NAME)
	install -Dm 0755 $(NAME) /usr/bin/$(NAME)
	install -Dm 0644 images/mill.png /usr/share/$(NAME)/images/mill.png
	install -Dm 0644 images/tictactoe-preview.png /usr/share/$(NAME)/images/tictactoe-preview.png
	install -Dm 0644 images/connect-four-preview.png /usr/share/$(NAME)/images/connect-four-preview.png
	install -Dm 0644 images/mill-preview.png /usr/share/$(NAME)/images/mill-preview.png
	install -Dm 0644 images/checkers-preview.png /usr/share/$(NAME)/images/checkers-preview.png
	install -Dm 0644 images/checkers.png /usr/share/$(NAME)/images/checkers.png

uninstall:
	rm /usr/bin/$(NAME)
	rm /usr/share/fungames -r
