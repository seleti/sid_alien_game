#ifndef PLAYER__H
#define PLAYER__H
#include "multisprite.h"
#include<string>
#include "gamedata.h"
using std::string;

class Player  {
public:
  Player(Vector2f pos, Vector2f vel, const std::vector<Frame*> & f) : 
    gdata( Gamedata::getInstance() ),
    player(pos, vel, "plane" ,f, gdata->getXmlInt("planeFrames") ,gdata->getXmlInt("planeFrameInterval")), 
    playerWidth( player.getFrame()->getWidth() ), playerHeight( player.getFrame()->getWidth() ),playerHealth(100)
  {}
  virtual ~Player() {}

  virtual void update(Uint32 ticks) { player.update(ticks); }
  virtual void draw() const {player.draw(); }
  const MultiframeSprite& getSprite() const { return player; }
  int getHealth() {return playerHealth;}
  void reduceHealth() {playerHealth=playerHealth-1;}
  void stop() { 
    player.velocityX(0);  
    player.velocityY(0);  
  }
  int getX() const {return player.X()+110;}
  int getY() const {return player.Y()+28;}
  void right();
  void left();
  void up();
  void down();
  void shoot();
  Player(const Player& p);
  Player& operator=(const Player& p);
  
private:
  const Gamedata* gdata;
  MultiframeSprite player;
  float playerWidth;
  float playerHeight;
  int playerHealth;
};

#endif
