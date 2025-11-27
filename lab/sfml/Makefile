UNAME_S := $(shell uname)

ifeq ($(UNAME_S),Darwin)        # macOS
    NAME     = sfml-app
    SOFLAGS  = -Wl,-rpath,@loader_path
else                            # Linux
    NAME     = sfml-app
    SOFLAGS  = -Wl,-rpath,'$$ORIGIN'
endif

CC      = g++
CFLAGS  = -std=c++17 -Wall -Wextra -Werror -O2

SOURCES = src/main.cpp
OBJECTS = $(SOURCES:.cpp=.o)

SFML_DIR        = SFML
SFML_BUILD      = $(SFML_DIR)/build
SFML_INSTALL    = $(SFML_DIR)
SFML_INC        = -I$(SFML_INSTALL)/include
SFML_LIBDIR     = $(SFML_INSTALL)/lib
SFML_LIBS       = -L$(SFML_LIBDIR) -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
SFML_CMAKE_FLAGS = -DSFML_BUILD_EXAMPLES=OFF -DSFML_BUILD_DOC=OFF -DCMAKE_BUILD_TYPE=Release \
                   -DCMAKE_INSTALL_PREFIX=$(abspath $(SFML_INSTALL)) -DBUILD_SHARED_LIBS=ON

all: $(NAME) copy_deps

# Linking step: $(SFML_INSTALL) dependency ensures SFML library files are available
# Purpose: Provides library files (.so/.dylib) needed to link the executable
$(NAME): $(OBJECTS) $(SFML_INSTALL)
	$(CC) $(SOFLAGS) -o $@ $(OBJECTS) $(SFML_LIBS)

# Compilation step: $(SFML_INSTALL) dependency ensures SFML header files are available
# Purpose: Provides header files needed to compile source files
src/%.o: src/%.cpp $(SFML_INSTALL)
	$(CC) $(CFLAGS) $(SFML_INC) -c $< -o $@

# Generic rule to build executables from source files in src/
# Usage: make <filename> (e.g., make gdbe)
%: src/%.o $(SFML_INSTALL) copy_deps
	$(CC) $(SOFLAGS) -o $@ $< $(SFML_LIBS)

# Specific rule for mushroom_2: needs Game.cpp and Window.cpp
mushroom_2: src/mushroom_2.o src/Game.o src/Window.o $(SFML_INSTALL) copy_deps
	$(CC) $(SOFLAGS) -o $@ src/mushroom_2.o src/Game.o src/Window.o $(SFML_LIBS)

# Build and install SFML (creates both headers and libraries)
# Note: This target is used in two different contexts:
#   1. In compilation: ensures header files exist (via SFML_INC pointing to include/)
#   2. In linking: ensures library files exist (via SFML_LIBS pointing to lib/)
$(SFML_INSTALL):
	git clone https://github.com/SFML/SFML.git $(SFML_DIR) || true
	mkdir -p $(SFML_BUILD) $(SFML_INSTALL)
	cd $(SFML_BUILD) && cmake $(SFML_CMAKE_FLAGS) .. && $(MAKE) -j1 && $(MAKE) install

copy_deps:
ifeq ($(UNAME_S), Darwin)
	cp $(SFML_LIBDIR)/libsfml-graphics.3.1.dylib .
	cp $(SFML_LIBDIR)/libsfml-window.3.1.dylib .
	cp $(SFML_LIBDIR)/libsfml-system.3.1.dylib .
	cp $(SFML_LIBDIR)/libsfml-audio.3.1.dylib .
else
	cp $(SFML_LIBDIR)/libsfml-graphics.so.3.1 .
	cp $(SFML_LIBDIR)/libsfml-window.so.3.1 .
	cp $(SFML_LIBDIR)/libsfml-system.so.3.1 .
	cp $(SFML_LIBDIR)/libsfml-audio.so.3.1 .
endif

clean:
	$(RM) $(OBJECTS) src/*.o

fclean: clean
	$(RM) $(NAME)
	$(RM) -rf $(SFML_DIR)
	$(RM) -f *.dylib *.so*

re: fclean all

.PHONY: all clean fclean re copy_deps

