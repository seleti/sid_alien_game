#ifndef FRAMEFACTORY_H 
#define FRAMEFACTORY_H
#include <SDL.h>
#include <iostream>
#include "frame.h"
#include "gamedata.h"
#include <map>
#include <vector>

class FrameFactory{
public:

  static FrameFactory* getInstance();
  std::vector <Frame*> getFrame(string name,SDL_Surface *surface);
  ~FrameFactory();

private:
  Gamedata* gdata;
  static FrameFactory* instance;
  FrameFactory();
  FrameFactory(const FrameFactory&);
  FrameFactory& operator=(const FrameFactory&);
  std::vector< Frame*> frames;
  std::map<std::string,std::vector<Frame*> > frameMap;
  
  
  //const Gamedata* gdata;
};
#endif
