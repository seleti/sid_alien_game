#include <SDL.h>
#include <iostream>
#include <string>
#include <vector>
#include "world.h"
#include "viewport.h"
#include "lsystem.h"
#include "ioManager.h"
#include "gamedata.h"
#include "sprite.h"
#include "multisprite.h"
#include "FrameFactory.h"
#include "explodingSprite.h"
#include "player.h"
#include "collisionStrategy.h"

class SpriteManager {

public:
  SpriteManager();
  virtual ~SpriteManager();
  void setFlag();
  void draw() const;
  void update(Uint32);
  void updateObjectToTrack();
  void explodeCurrentObject();
  Player& getPlayer(){return player;}
  void collisionCheck();
  void make_bullets();
  void make_enemybullets();
  void reload();
  
private:
  const Gamedata* gdata;
  const IOManager& io;
  FrameFactory* ffactory;  
  SDL_Surface * const backSurface;
  World world;
  SDL_Surface * const bbackSurface;
  World bworld;
  Viewport& viewport;
  int currentSprite;
  SDL_Surface* ufoSurface;
  SDL_Surface* cloudSurface;
  
  LSystem lsystem;
  SDL_Surface * const lsysSurface;
  SDL_Surface * const planeSurface;
  SDL_Surface * const enemySurface;
  std::vector<Drawable*> planes_vec;
  std::vector<Drawable*> destroyed;
  std::vector<Drawable*> enemy_vec;
  Player player;
  bool f1;
  int explodednumber ;
  bool spriteExploded;
  CollisionStrategy *collisionStrategy;
  bool collisionFound;
  std::vector<Sprite*> bullets;
  std::vector<Sprite*> enemy_bullets;
  int c;
  MultiframeSprite* ufo;
  void make_multisprite();
  void make_lsystems();
  void make_sprite();
  void make_cloud();
  void make_ufo();
 
  SpriteManager(const SpriteManager&);
  SpriteManager& operator=(const SpriteManager&);
  
};



