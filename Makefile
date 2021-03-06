#
# Cross Platform Makefile
# Compatible with MSYS2/MINGW, Ubuntu 14.04.1 and Mac OS X
#
# You will need SDL2 (http://www.libsdl.org):
# Linux:
#   apt-get install libsdl2-dev
# Mac OS X:
#   brew install sdl2
# MSYS2:
#   pacman -S mingw-w64-i686-SDL2
#

#CXX = g++
#CXX = clang++

EXE = app
IMGUI_DIR = ./UI/imgui
FILE_BROWSER_DIR = ./UI/FileBrowser
SR_DIR = ./src
SOURCES = main.cpp
SOURCES += $(IMGUI_DIR)/imgui.cpp $(IMGUI_DIR)/imgui_draw.cpp $(IMGUI_DIR)/imgui_tables.cpp $(IMGUI_DIR)/imgui_widgets.cpp
SOURCES += $(FILE_BROWSER_DIR)/ImGuiFileBrowser.cpp $(IMGUI_DIR)/backends/imgui_impl_sdl.cpp $(IMGUI_DIR)/backends/imgui_impl_opengl3.cpp
SOURCES += $(SR_DIR)/emulator.cpp $(SR_DIR)/gui.cpp $(SR_DIR)/renderer.cpp $(SR_DIR)/shader.cpp $(SR_DIR)/memory_map.cpp $(SR_DIR)/cartridge.cpp $(SR_DIR)/cpu.cpp

OBJS = $(addsuffix .o, $(basename $(notdir $(SOURCES))))
UNAME_S := $(shell uname -s)
LINUX_GL_LIBS = -lGL -lGLEW

CXXFLAGS = -I$(IMGUI_DIR) -I$(IMGUI_DIR)/backends -I$(FILE_BROWSER_DIR) -I$(SR_DIR)
CXXFLAGS += -g -Wall -Wformat
LIBS =

##---------------------------------------------------------------------
## BUILD FLAGS PER PLATFORM
##---------------------------------------------------------------------

ifeq ($(UNAME_S), Linux) #LINUX
	ECHO_MESSAGE = "Linux"
	LIBS += $(LINUX_GL_LIBS) -ldl `sdl2-config --libs`

	CXXFLAGS += `sdl2-config --cflags`
	CFLAGS = $(CXXFLAGS)
endif

##---------------------------------------------------------------------
## BUILD RULES
##---------------------------------------------------------------------
%.o:%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

%.o:$(SR_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

%.o:$(FILE_BROWSER_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

%.o:$(IMGUI_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

%.o:$(IMGUI_DIR)/backends/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

all: $(EXE)
	@echo Build complete for $(ECHO_MESSAGE)

$(EXE): $(OBJS)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBS)

clean:
	rm -f $(EXE) $(OBJS)
