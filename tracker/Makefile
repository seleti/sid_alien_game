
ifeq ("$(shell whoami)", "malloy")
  CXX = clang++
else
  CXX = clang++
endif
CXX_LINK = clang++

# Warnings frequently signal eventual errors:
CXXFLAGS=`sdl-config --cflags` -g -W -Wall -Weffc++ -Wextra -pedantic -O0
LDFLAGS = `sdl-config --libs` -lSDL_ttf -lSDL_image -lexpat -lSDL_mixer 

OBJS = \
	main.o \
	viewport.o \
	world.o \
	manager.o \
	gamedata.o \
	parseXML.o \
	clock.o \
	vector2f.o \
	sprite.o \
	frame.o \
	FrameFactory.o \
	multisprite.o \
	parseLsysXML.o \
	aaline.o \
	lsystem.o \
	collisionStrategy.o\
	spriteManager.o \
	sound.o \
	chunk.o \
	explodingSprite.o \
	gui.o \
	player.o\
	ioManager.o   
	
	

EXEC = run

# $< refers to the first dependency
%.o: %.cpp
	$(CXX_LINK) $(CXXFLAGS) -c $< -o $@

# $@ refers to the target
$(EXEC): $(OBJS)
	g++ $(CXXFLAGS) -o $@ $(OBJS) $(LDFLAGS)

main.o: main.cpp
manager.o: manager.cpp manager.h spriteManager.cpp spriteManager.h gamedata.h ioManager.h gui.h frame.h sprite.h clock.h FrameFactory.h
sound.o: sound.h sound.cpp ioManager.h 
ioManager.o: ioManager.cpp ioManager.h
viewport.o: viewport.cpp viewport.h
world.o: world.cpp world.h
parseXML.o: parseXML.cpp parseXML.h
parseLsysXML.o:  parseLsysXML.cpp parseLsysXML.h
aaline.o: aaline.cpp aaline.h
lsystem.o: lsystem.cpp lsystem.h ioManager.h parseLsysXML.h
gamedata.o: gamedata.cpp gamedata.h parseXML.h
clock.o: clock.cpp clock.h
vector2f.o: vector2f.cpp vector2f.h
frame.o: frame.cpp frame.h vector2f.h
sound.o: sound.cpp sound.h 
sprite.o: sprite.cpp sprite.h drawable.h frame.h
chunk.o: chunk.cpp chunk.h sprite.cpp gamedata.h
explodingSprite.o: explodingSprite.cpp explodingSprite.h gamedata.h sprite.h 
frame.o: frame.cpp frame.h ioManager.h chunk.h
multisprite.o: multisprite.cpp multisprite.h drawable.h frame.h
FrameFactory.o: FrameFactory.cpp FrameFactory.h frame.h
collisionStrategy.o: collisionStrategy.h collisionStrategy.cpp   
spriteManager.o: spriteManager.h spriteManager.cpp lsystem.cpp lsystem.h explodingSprite.h parseLsysXML.h sprite.h clock.h FrameFactory.h gamedata.h clock.cpp player.h collisionStrategy.h collisionStrategy.cpp
player.o: player.h player.cpp multisprite.cpp multisprite.h 
gui.o: gui.h gui.cpp frame.h frame.cpp vector2f.h
manager.o: manager.cpp manager.h spriteManager.cpp spriteManager.h gamedata.h ioManager.h gui.h frame.h sprite.h clock.h FrameFactory.h

clean:
	rm -rf $(OBJS)
	rm -rf $(EXEC)
