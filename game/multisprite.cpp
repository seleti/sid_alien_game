#include <iostream>
#include <cmath>
#include "multisprite.h"
#include "gamedata.h"

//const int NUMBER_FRAMES = gdata->getXmlInt("planeFrames");
//const int FRAME_INTERVAL = gdata->getXmlInt("planeFrameInterval");

void MultiframeSprite::advanceFrame(Uint32 ticks) {
  float ms = 1000.0/frameInterval;
  dt += ticks;
  int df = dt / ms;
  dt -= df * ms;
  currentFrame = (currentFrame + df) % numberOfFrames;
}

MultiframeSprite::MultiframeSprite(const Vector2f& pos, 
                                   const Vector2f& vel, 
               const string& n, const std::vector<Frame*> & fms,const int nof,const int fi) :
  Drawable(pos, vel, vel), 
  frames(fms),
  name(n),
  dt(0),
  currentFrame(0),
  numberOfFrames( nof),
  frameInterval( fi )
{ }

MultiframeSprite::MultiframeSprite(const MultiframeSprite& s) :
  Drawable(s.getPosition(), s.getVelocity(), s.getMaxVelocity()), 
  frames(s.frames),
  name( s.getName() ),
  dt(s.dt),
  currentFrame(s.currentFrame),
  numberOfFrames( s.numberOfFrames ),
  frameInterval( s.frameInterval )
  { }

void MultiframeSprite::draw() const { 
  Uint32 x = static_cast<Uint32>(X());
  Uint32 y = static_cast<Uint32>(Y());
  frames[currentFrame]->draw(x, y);
}



void MultiframeSprite::update(Uint32 ticks) { 
  advanceFrame(ticks);
  float incr = velocityY() * static_cast<float>(ticks) * 0.001;
  Y(( Y()+incr) );
  float height = static_cast<float>(frames[currentFrame]->getHeight());
  
  if ( Y() < 0) {
    velocityY( abs( velocityY() ) );
  }
  if ( Y() > (Gamedata::getInstance()->getXmlInt("worldHeight")-height)) {
    velocityY( -abs( velocityY() ) );
  }

  incr = velocityX() * static_cast<float>(ticks) * 0.001;
  X( X()+incr );
  float width = static_cast<float>(frames[currentFrame]->getWidth());
  if ( X() + width < 0) {
   X( Gamedata::getInstance()->getXmlInt("worldWidth") );
   //velocityX( abs( velocityX() ) );
  }
  if ( X() > Gamedata::getInstance()->getXmlInt("worldWidth")+width ) {
    //velocityX( -abs( velocityX() ) );
    
    X( -width );
  }
}
