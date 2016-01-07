#ifndef VIEWPORT__H
#define VIEWPORT__H
#include "sprite.h"
//#include "multisprite.h"
#include "gamedata.h"
#include "player.h"

class Viewport {
public:
  static Viewport& getInstance();
  ~Viewport() {  std::cout << "Blocking the view ..." << std::endl; }
  void update();

  float X() const { return position[0]; }
  void X(float x) { position[0] = x; }
  float Y() const { return position[1]; }
  void Y(float y) { position[1] = y; }
  void update(float x,float y);
  void trackSprite(const Frame& fr);
  void trackSprite(const Drawable *obj);
  void trackSprite(const Player *player);
  //void setObjectToTrack(const MultiframeSprite *obj);
  //const MultiframeSprite* getObjectToTrack() const { return objectToTrack; } 
  const Drawable* getObjectToTrack() const { return objectToTrack; } 

private:
  Gamedata* const gdata;
  Vector2f position;
  unsigned viewWidth;
  unsigned viewHeight;
  unsigned worldWidth;
  unsigned worldHeight;
  Uint16 objWidth;
  Uint16 objHeight;
  
  //const MultiframeSprite *objectToTrack;

  const Drawable *objectToTrack;
  

  Viewport();
  Viewport(const Viewport&);
  Viewport& operator=(const Viewport&);
};
#endif
