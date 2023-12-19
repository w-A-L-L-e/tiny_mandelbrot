EXECUTABLE=tiny_mandelbrot
# LIBS=`sdl2-config --libs`
# LIBS=`sdl2-config --static-libs`
LIBS=/usr/local/lib/libSDL2.a -lm -liconv -Wl,-framework,CoreAudio -Wl,-framework,AudioToolbox -Wl,-weak_framework,CoreHaptics -Wl,-weak_framework,GameController -Wl,-framework,ForceFeedback -lobjc -Wl,-framework,CoreVideo -Wl,-framework,Cocoa -Wl,-framework,Carbon -Wl,-framework,IOKit -Wl,-weak_framework,QuartzCore -Wl,-weak_framework,Metal
# STATIC (/usr/local/lib/libSDL2main.a for windows might be needed)
CPPFLAGS=-I. 
ENGINE_OBJECTS=${EXECUTABLE}.o screen.o
all: $(EXECUTABLE)

$(EXECUTABLE): $(ENGINE_OBJECTS)
	$(CXX) -O2 $^ -o $(EXECUTABLE) -Iinclude $(LIBS)

clean:
	@rm -vf *.o $(EXECUTABLE)

