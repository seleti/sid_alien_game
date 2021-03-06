#include <iostream>
#include <cmath>
#include "explodingSprite.h"

//ExplodingSprite::ExplodingSprite(const Sprite& s) :
//  Sprite(s), 
//  chunks(), 
//  freeList(),
//  frames() {
//  makeChunks(Gamedata::getInstance()->getXmlInt(s.getName()+"ChunkSize"));
//}

ExplodingSprite::ExplodingSprite(const MultiframeSprite& s) : 
  MultiframeSprite(s),
  chunks(), 
  freeList(),
  frames() {
  
  makeChunks_multi(Gamedata::getInstance()->getXmlInt(s.getName()+"ChunkSize"));
}
//ExplodingSprite::ExplodingSprite(Frame* s,std::string& name) : 
//  fframe(s),
//  chunks(), 
//  freeList(),
//  frames() {
//  
//  makeChunks_frame(Gamedata::getInstance()->getXmlInt(name+"ChunkSize"));
//}

ExplodingSprite::~ExplodingSprite() { 
  chunks.clear();
  freeList.clear();
  for ( unsigned int i = 0; i < frames.size(); ++i ) {
    delete frames[i];
  }
}

void ExplodingSprite::draw() const { 
  std::list<Chunk>::const_iterator ptr = chunks.begin();
  while (ptr != chunks.end()) {
    ptr->draw();
    ++ptr;
  }
}

void ExplodingSprite::update(Uint32 ticks) { 
  std::list<Chunk>::iterator ptr = chunks.begin();
  while (ptr != chunks.end()) {
    ptr->update(ticks);
    if (ptr->goneTooFar()) {
      freeList.push_back(*ptr);
      ptr = chunks.erase(ptr);
    }   
    else ++ptr;
  }
}

//void ExplodingSprite::makeChunks_frame(unsigned int n) { 
//  std::cout<<"inside explode"<<std::endl;
//  Frame* frame=fframe;
//  unsigned int chunk_width = frame->getWidth()/n;
//  unsigned int chunk_height = frame->getHeight()/n;
//  Sint16 source_x = frame->getSourceX();
//  Sint16 source_y = frame->getSourceY();
//  int speedx = static_cast<int>(velocityX())+1; // Make sure it's not 0;
//  int speedy = static_cast<int>(velocityY())+1; // Make sure it's an int.
//  SDL_Surface* spriteSurface(frame->getSurface()); 
//  for (unsigned int i = 0; i < n; ++i) {
//    for (unsigned int j = 0; j < n; ++j) {
//      float sx = (rand() % speedx + rand()%80+20) * (rand()%2?-1:1); // 'cause %0 is 
//      float sy = (rand() % speedy + rand()%80+40) * (rand()%2?-1:1); // float except
//      Frame* frame = 
//            new Frame(spriteSurface, chunk_width, chunk_height,
//                  source_x+i*chunk_width,  // x coord of surface
//                  source_y+j*chunk_height // y coord of surface
//                );
//      Chunk chunk(
//                Vector2f(X()+i*chunk_width,   // x coord of destination 
//                         Y()+j*chunk_height), // y coord of destination
//                Vector2f(sx, sy),
//               getName()+"Chunk",
//               // getName(),
//                frame);
//      chunks.push_back(chunk);
//      frames.push_back(frame);
//    }
//  }
//}

void ExplodingSprite::makeChunks_multi(unsigned int n) { 
  unsigned int chunk_width = getFrame()->getWidth()/n;
  unsigned int chunk_height = getFrame()->getHeight()/n;
  Sint16 source_x = getFrame()->getSourceX();
  Sint16 source_y = getFrame()->getSourceY();
  int speedx = static_cast<int>(velocityX())+1; // Make sure it's not 0;
  int speedy = static_cast<int>(velocityY())+1; // Make sure it's an int.
  SDL_Surface* spriteSurface(getFrame()->getSurface()); 
  for (unsigned int i = 0; i < n; ++i) {
    for (unsigned int j = 0; j < n; ++j) {
      float sx = (rand() % speedx + rand()%80+20) * (rand()%2?-1:1); // 'cause %0 is 
      float sy = (rand() % speedy + rand()%80+40) * (rand()%2?-1:1); // float except
      Frame* frame = 
            new Frame(spriteSurface, chunk_width, chunk_height,
                  source_x+i*chunk_width,  // x coord of surface
                  source_y+j*chunk_height // y coord of surface
                );
      Chunk chunk(
                Vector2f(X()+i*chunk_width,   // x coord of destination 
                         Y()+j*chunk_height), // y coord of destination
                Vector2f(sx, sy),
               getName()+"Chunk",
               // getName(),
                frame);
      chunks.push_back(chunk);
      frames.push_back(frame);
    }
  }
}

//void ExplodingSprite::makeChunks(unsigned int n) { 
//  unsigned int chunk_width = frame->getWidth()/n;
//  unsigned int chunk_height = frame->getHeight()/n;
//  Sint16 source_x = frame->getSourceX();
//  Sint16 source_y = frame->getSourceY();
//  int speedx = static_cast<int>(velocityX())+1; // Make sure it's not 0;
//  int speedy = static_cast<int>(velocityY())+1; // Make sure it's an int.
//  SDL_Surface* spriteSurface(frame->getSurface()); 
//  for (unsigned int i = 0; i < n; ++i) {
//    for (unsigned int j = 0; j < n; ++j) {
//      float sx = (rand() % speedx + rand()%80+20) * (rand()%2?-1:1); // 'cause %0 is 
//      float sy = (rand() % speedy + rand()%80+40) * (rand()%2?-1:1); // float except
//      Frame* frame = 
//            new Frame(spriteSurface, chunk_width, chunk_height,
//                  source_x+i*chunk_width,  // x coord of surface
//                  source_y+j*chunk_height // y coord of surface
//                );
//      Chunk chunk(
//                Vector2f(X()+i*chunk_width,   // x coord of destination 
//                         Y()+j*chunk_height), // y coord of destination
//                Vector2f(sx, sy),
//               getName()+"Chunk",
//               // getName(),
//                frame);
//      chunks.push_back(chunk);
//      frames.push_back(frame);
//    }
//  }
//}

