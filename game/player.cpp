#include "player.h"

void Player::right() { 
  if ( player.X() < gdata->getXmlInt("worldWidth")-playerWidth) {
    player.velocityX(100);
  }
} 
void Player::left()  { 
  if ( player.X() > 0) {
    player.velocityX(-70);
  }
} 
void Player::up()    { 
  if ( player.Y() > 0) {
    player.velocityY(-100);
  }
} 
void Player::down()  { 
  if ( player.Y() < gdata->getXmlInt("worldHeight")-playerHeight) {
    player.velocityY(100);
  }
} 

