#include "spriteManager.h"

SpriteManager::~SpriteManager() {

  SDL_FreeSurface(backSurface);
  SDL_FreeSurface(bbackSurface);
  SDL_FreeSurface(planeSurface);
  SDL_FreeSurface(ufoSurface);
  SDL_FreeSurface(lsysSurface);
  SDL_FreeSurface(cloudSurface);
  SDL_FreeSurface(enemySurface);
  int s=planes_vec.size();
  for (int i=0;i<s;i++) {
    if (planes_vec[i]->getName()!="plane")
      delete planes_vec[i];
  }
  planes_vec.clear();
  delete ufo;
  s=enemy_vec.size();
  for (int i=0;i<s;i++) {
    if (enemy_vec[i]->getName()!="plane")
      delete enemy_vec[i];
  }
  planes_vec.clear();
  
  s=destroyed.size();
  for (int i=0;i<s;i++) {
    if (destroyed[i]->getName()!="plane")
      delete destroyed[i];
  }
  destroyed.clear();
  int b=bullets.size();
  for (int i=0;i<b;i++) {
    delete bullets[i];
  }
  bullets.clear();
  
  b=enemy_bullets.size();
  for (int i=0;i<b;i++) {
    delete enemy_bullets[i];
  }
  enemy_bullets.clear();
  
  delete collisionStrategy;
}

void SpriteManager::reload() {
  
  int s=planes_vec.size();
  for (int i=0;i<s;i++) {
    if (planes_vec[i]->getName()!="plane")
     delete planes_vec[i];
  }
  planes_vec.clear();
  
  s=enemy_vec.size();
  for (int i=0;i<s;i++) {
    if (enemy_vec[i]->getName()!="plane")
     delete enemy_vec[i];
  }
  enemy_vec.clear();
  
  int b=bullets.size();
  for (int i=0;i<b;i++) {
     delete bullets[i];
  }
  bullets.clear();
  b=destroyed.size();
  for (int i=0;i<b;i++) {
     delete destroyed[i];
  }
  destroyed.clear();
  planes_vec.push_back(const_cast<MultiframeSprite*>(&(player.getSprite())));
  make_cloud();
  make_multisprite();
  while (planes_vec[currentSprite]->getName()=="cloud")
    currentSprite = (currentSprite+1) % planes_vec.size();
  viewport.trackSprite(planes_vec[currentSprite]);
}

SpriteManager::SpriteManager() :
  gdata( Gamedata::getInstance() ),
  io( IOManager::getInstance() ),
  ffactory( FrameFactory::getInstance() ),
  backSurface( io.loadAndSet(gdata->getXmlStr("backFile"), true) ),  
  world(ffactory->getFrame("back",backSurface)[0]),
  bbackSurface( io.loadAndSet(gdata->getXmlStr("bbackFile"), false) ),  
  bworld(ffactory->getFrame("bback",bbackSurface)[0],5),
  viewport( Viewport::getInstance() ),
  currentSprite(0),
  ufoSurface( io.loadAndSet(gdata->getXmlStr("ufoFile"),true) ),
  cloudSurface(io.loadAndSet(gdata->getXmlStr("cloudFile"),true) ),
  lsystem(gdata->getXmlStr("lsystemFile")),
  lsysSurface(lsystem.getSurface()),
  planeSurface( io.loadAndSet(gdata->getXmlStr("planeFile"),true) ),
  enemySurface( io.loadAndSet(gdata->getXmlStr("enemyFile"),true) ),
  planes_vec(),
  destroyed(),
  enemy_vec(),
  player(Vector2f(100,90), Vector2f(0,0),
         ffactory->getFrame("plane",planeSurface)),
  f1(false),
  explodednumber(0),
  spriteExploded(false),
  collisionStrategy(NULL),
  collisionFound(false),
  bullets(),
  enemy_bullets(),
  c(0),
  ufo(NULL)
{
  Uint32 colorkey = SDL_MapRGB(lsysSurface->format, 255, 0, 255);
  SDL_SetColorKey(lsysSurface, SDL_SRCCOLORKEY|SDL_RLEACCEL, colorkey);
  planes_vec.push_back(const_cast<MultiframeSprite*>(&(player.getSprite())));
  make_cloud();
  make_multisprite();
  make_lsystems();
  make_ufo();
  collisionStrategy=new PerPixelCollisionStrategy() ;
  atexit(SDL_Quit);
  while (planes_vec[currentSprite]->getName()=="cloud")
    currentSprite = (currentSprite+1) % planes_vec.size();
  viewport.trackSprite(planes_vec[currentSprite]);
}

void SpriteManager::updateObjectToTrack() {
  
  if (c==0){
   viewport.trackSprite(planes_vec[0]);
  c=1;
  }
  if (c==1) {
   viewport.trackSprite(ufo);
   c=0;
  }
}

void SpriteManager::explodeCurrentObject() {
  std::vector<Drawable *>::iterator it = enemy_vec.begin(); 
  while(it!=enemy_vec.end()){
       MultiframeSprite *temp = static_cast <MultiframeSprite*> (*it);
       destroyed.push_back(new ExplodingSprite(*temp));
       delete temp;
       it = enemy_vec.erase(it);
       collisionFound=true;
      
    }
}

void SpriteManager::draw() const {
  //world.setAlpha(static_cast<int>(1));
  bworld.draw();
  world.draw();
  viewport.update();
  for (unsigned int i=0;i<planes_vec.size();i++) {
    planes_vec[i]->draw();
  }
  for (unsigned int i=0;i<destroyed.size();i++) {
    destroyed[i]->draw();
  }
  for(unsigned int i=0;i<bullets.size();++i) {
    bullets[i]->draw();
  }
  for(unsigned int i=0;i<enemy_bullets.size();++i) {
    enemy_bullets[i]->draw();
  }  
  for(unsigned int i=0;i<enemy_vec.size();++i) {
    enemy_vec[i]->draw();
  }
  player.draw();
  ufo->draw();
  
    io.printMessageAt("Press T to switch", 0, 10);
    io.printMessageAt("Press E to explode all UFO's'", 0,50);
    io.printMessageAt("Press s to shoot", 0,30);
   if (c==0)
    io.printMessageAt("Tracking: Player", 0, 70);
    else
    io.printMessageAt("Tracking: Alien Ship",0,70);   
    int i=enemy_vec.size();
    io.printMessageValueAt("Number of UFO's left:",i, 500,30);
}

void SpriteManager::update(Uint32 ticks) {
  viewport.update();
  bworld.update();
  world.update();
  //player.update(ticks);
  for (unsigned int i = 0; i < planes_vec.size(); ++i) {
    planes_vec[i]->update(ticks);
  }
  for (unsigned int i = 0; i < destroyed.size(); ++i) {
    destroyed[i]->update(ticks);
  }
  player.update(ticks);
  ufo->update(ticks);
  for(unsigned int i=0;i<bullets.size();++i) {
    bullets[i]->update(ticks);
  }
    for(unsigned int i=0;i<enemy_vec.size();++i) {
    enemy_vec[i]->update(ticks);
  }
    for(unsigned int i=0;i<enemy_bullets.size();++i) {
    enemy_bullets[i]->update(ticks);
  }
  std::vector<Sprite *>::iterator it = bullets.begin(); 
  while(it!=bullets.end()){
    int dist=SDL_GetTicks()-((*it)->getTime());
    if (dist*0.001>1)
      it=bullets.erase(it);
     else ++it;  
    }    
     std::vector<Sprite *>::iterator ite = enemy_bullets.begin(); 
  while(ite!=enemy_bullets.end()){
    int dist=SDL_GetTicks()-((*ite)->getTime());
    if (dist*0.001>1 || (*ite)->X() <= player.getX())
      ite=enemy_bullets.erase(ite);
     else ++ite;  
    }    
    if(rand()%17==0)
    make_enemybullets();
}

void SpriteManager::setFlag() {
  if (f1)
    f1=false;
  else
    f1=true;
}

void SpriteManager::make_ufo() {

}

void SpriteManager::make_sprite() {
}

void SpriteManager::make_cloud() {

  for (int i=0;i<gdata->getXmlInt("cloudCount");i++) {
    int w =  gdata->getXmlInt("worldWidth")-gdata->getXmlInt("cloudWidth");
    int h =  gdata->getXmlInt("worldHeight")-gdata->getXmlInt("cloudHeight");
    Vector2f position(rand()%w,rand()%h);
    planes_vec.push_back(new Sprite( position, 
                        Vector2f(gdata->getXmlInt("cloudXspeed"),
                        gdata->getXmlInt("cloudYspeed")),
                        "cloud", ffactory->getFrame("cloud",cloudSurface)[0]));
  }
}

void SpriteManager::make_lsystems(){

  for (int i=0;i<gdata->getXmlInt("lsystemCount");i++) {
    int w =  gdata->getXmlInt("worldWidth")-gdata->getXmlInt("lsystemWidth");
    int h =  gdata->getXmlInt("worldHeight")-gdata->getXmlInt("lsystemHeight");
    Vector2f position(rand()%w,rand()%h);
    planes_vec.push_back(new Sprite( position, 
                      Vector2f(gdata->getXmlInt("lsystemXspeed"), 
                      gdata->getXmlInt("lsystemXspeed")),
                      "lsystem", 
                      ffactory->getFrame("lsystem",lsysSurface)[0]));
  }
}

void SpriteManager::make_multisprite() {
  unsigned numberOfFrames = gdata->getXmlInt("enemyFrames");
  for (int i=0;i<gdata->getXmlInt("enemyCount")/2;i++) {
    int w =  (gdata->getXmlInt("worldWidth")/2)-gdata->getXmlInt("enemyWidth");
    int h =  gdata->getXmlInt("worldHeight")-gdata->getXmlInt("enemyHeight");
    Vector2f position(rand()%w+1400,rand()%h);
    enemy_vec.push_back(new MultiframeSprite(position, Vector2f(gdata->getXmlInt("enemyXspeed"), 
                      gdata->getXmlInt("enemyYspeed")),"enemy",
                        ffactory->getFrame("enemy",enemySurface),
                        numberOfFrames,gdata->getXmlInt("enemyFrameInterval")));
  }
  
  for (int i=0;i<gdata->getXmlInt("enemyCount")/2;i++) {
    int w =  gdata->getXmlInt("worldWidth")/2 - gdata->getXmlInt("enemyWidth");
    int h =  gdata->getXmlInt("worldHeight")/2 - gdata->getXmlInt("enemyHeight");
    Vector2f position(rand()%w+w,rand()%h);
    enemy_vec.push_back(new MultiframeSprite(position, Vector2f(gdata->getXmlInt("enemyXspeed"), 
                      gdata->getXmlInt("enemyYspeed")),"enemy",
                        ffactory->getFrame("enemy",enemySurface),
                        numberOfFrames,gdata->getXmlInt("enemyFrameInterval")));
  }
  
    numberOfFrames = gdata->getXmlInt("ufoFrames");
    int w =  gdata->getXmlInt("worldWidth")-gdata->getXmlInt("ufoWidth");
    int h =  gdata->getXmlInt("worldHeight")-gdata->getXmlInt("ufoHeight");
    Vector2f position(w,h);
    ufo = new MultiframeSprite( position, Vector2f(gdata->getXmlInt("ufoXspeed"),
                        gdata->getXmlInt("ufoYspeed")),"enemy", 
                        ffactory->getFrame("ufo",ufoSurface),
                        numberOfFrames,gdata->getXmlInt("ufoFrameInterval"));
                        
}

void SpriteManager::make_bullets() {
  bullets.push_back(new Sprite( Vector2f(player.getX(),player.getY()), 
                      Vector2f(gdata->getXmlInt("lsystemXspeed"), 0),
                      "lsystem", 
                      ffactory->getFrame("lsystem",lsysSurface)[0]));
}

void SpriteManager::make_enemybullets() {
  int fact;
  for (unsigned i=0;i<enemy_vec.size();i++){
    if (enemy_vec[i]->X() > player.getX())
      fact=-2;
    else 
      fact=1;
      enemy_bullets.push_back(new Sprite( Vector2f(enemy_vec[i]->X(),enemy_vec[i]->Y()), 
                      Vector2f((gdata->getXmlInt("lsystemXspeed"))*fact, 0),
                      "lsystem", 
                      ffactory->getFrame("lsystem",lsysSurface)[0]));
  }
}

void SpriteManager::collisionCheck() {
  collisionFound=false;
  for(unsigned int i=0; i< bullets.size(); ++i) {
  int j=0;
  std::vector<Drawable *>::iterator it = enemy_vec.begin(); 
  while(it!=enemy_vec.end()){
    if ((*it)->getName()=="enemy") {
      if (collisionStrategy->execute(*(bullets[i]),*(*it))) {
       MultiframeSprite *temp = static_cast <MultiframeSprite*> (*it);
       destroyed.push_back(new ExplodingSprite(*temp));
       delete temp;
       it = enemy_vec.erase(it);
       collisionFound=true;
       j++;
       break;
      } 
    }
      ++it;
    }
  }
  if (enemy_vec.size()==0)
  for(unsigned int i=0; i< bullets.size(); ++i) {
    if (collisionStrategy->execute(*(bullets[i]),*ufo)) {
       MultiframeSprite *temp = (ufo);
       ufo=new ExplodingSprite(*temp);
     }
}}
