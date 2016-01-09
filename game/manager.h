#include <SDL.h>
#include <iostream>
#include <string>
#include <vector>

#include "clock.h"
#include "spriteManager.h"
#include "gui.h"
#include "sound.h"

class Manager {
public:
  Manager ();
  ~Manager ();
  void game();
  void startgame();
  void restartgame();

private:
  const bool env;
  const IOManager& io;
  SDL_Surface *screen;
  Clock& clock;
  bool exit;
  bool done;
  bool menu;
  bool returnKey;
  bool story;
  bool keyCatch;
  SpriteManager spritemanager; 
  SDL_Event event;
  Gui gui;
  Manager(const Manager&);
  Manager& operator=(const Manager&);
  void menu_func(bool menu);
  void play_func(bool done);
  void story_func(bool story);
};
