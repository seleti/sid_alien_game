#include "FrameFactory.h"
#include <map>

using std::map;
using std::cout;

FrameFactory::~FrameFactory() {
  std::map<string, std::vector<Frame*> >::iterator itr = frameMap.begin();
  while (itr != frameMap.end()) {
    int s=itr->second.size();
    for (int i=0;i<s;i++) {
      delete itr->second[i];      
    }    
    frameMap.erase(itr++);
  }
}

FrameFactory* FrameFactory::getInstance() {
  if ( instance == NULL ) instance = new FrameFactory;
  return instance;
}


FrameFactory::FrameFactory() : gdata(Gamedata::getInstance()),  frames(),  frameMap()  {}

  std::vector<Frame *> FrameFactory::getFrame(const std::string name,SDL_Surface *surface) {
    frames.clear();
    std::map<std::string,std::vector<Frame*> >::const_iterator it = frameMap.find(name);
    if ( it != frameMap.end() ) {
      return it->second;
     }
    else {

      int numberOfFrames = gdata->getXmlInt(name+"Frames");
      Uint16 pwidth = gdata->getXmlInt(name+"MultiWidth") / numberOfFrames;
      Uint16 pheight = gdata->getXmlInt(name+"MultiHeight");
      Uint16 srcX = gdata->getXmlInt(name+"SrcX");  
      Uint16 srcY = gdata->getXmlInt(name+"SrcY"); 

      for (int i=0; i<numberOfFrames;++i) {
        unsigned frameX = i * pwidth + srcX; 
        frames.push_back( new Frame( surface,pwidth,pheight, frameX, srcY));
      }
  
    frameMap.insert(std::pair<string,std::vector<Frame*> >(name,frames));
    return frames;
    }
  }





FrameFactory* FrameFactory::instance = NULL;


