#include <cmath>
#include <string>
#include "manager.h"
#include "player.h"

Manager::~Manager() { 
  delete Gamedata::getInstance();
  SDL_FreeSurface(screen);
  delete FrameFactory::getInstance();
}

Manager::Manager() :
  env( SDL_putenv(const_cast<char*>("SDL_VIDEO_CENTERED=center")) ),
  io( IOManager::getInstance() ),
  screen( io.getScreen()),
  clock( Clock::getInstance() ),
  exit(false),
  done(false),
  menu(true),
  story(false),
  keyCatch(false),
  spritemanager(),
  event(),
  gui()
{  
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    throw string("Unable to initialize SDL: ");
  }
  story=true;
}

void Manager::game() {
  while(not exit) {
    if (menu) 
      menu_func(menu); 
    if(story)
      story_func(story);
    if (not done) 
      play_func(done);
  }
}



void Manager::menu_func(bool menu){

  bool returnKey = false;
  SDLSound sound("background");
  while(menu) {
    gui.draw();
    SDL_Flip(screen);
    gui.update();
    SDL_PollEvent(&event);
    if(event.type == SDL_KEYUP) {
      keyCatch = false; 
    }
    if (event.type ==  SDL_QUIT) { break; }
    if(event.type == SDL_KEYDOWN) {
      switch ( event.key.keysym.sym ) {
        case SDLK_ESCAPE : if(!keyCatch) { keyCatch=true;menu= false; story=false;done=true; exit=true;} break;
        case SDLK_q      : if(!keyCatch) { keyCatch=true;menu= false; story=false;done=true; exit=true;} break;
        case SDLK_RETURN : {
                            if ( !keyCatch ) {
                              keyCatch=true;
                              gui.lightOn();
                              returnKey = true;
                            }
                            break;
                           }
        case SDLK_DOWN   : {
                            if ( !keyCatch ) {
                              keyCatch=true;
                              gui.increment();
                              sound[1];
                            }
                            break;
                           }
        case SDLK_UP   : {
                          if ( !keyCatch ) {  
                            keyCatch=true;
                            gui.decrement();
                            sound[1];
                          }
                          break;
                         }
        default          : break;
      }
    }
    if(event.type == SDL_KEYUP) { 
      keyCatch = false; 
      if ( returnKey ) {
        SDL_Delay(100);
       // gui.guistop(true);
        returnKey=false;
        done = false;
        menu=false;
        gui.explode();
        if ( clock.isPaused() ) clock.unpause();
        std::string chosen = gui.getIconClicked();
        cout << "Chosen: " << chosen << endl;
        if (chosen=="exit") {
          menu= false; done=true; exit=true;story=false;
        }
        if (chosen=="new") {
          spritemanager.reload(); story=true;
        }
      }
      gui.lightOff();
    }
  }
  sound.turnoffMusic(true);

}

void Manager::story_func(bool story) {
  bool returnKey = false ;
  menu=true;
  done=true;
  exit=true;
  while (story ) {

    SDL_FillRect( screen, NULL, SDL_MapRGB(screen->format, 0, 0, 255) );
    SDL_Rect dest = {0, 0, 0, 0};
    SDL_BlitSurface( screen, NULL, screen, &dest );
    io.printMessageAt("The world is under attack by aliens and the you try to save", 100 ,50);
    io.printMessageAt("by killing all the aliens and finally destroying the mother", 100 ,70);
    io.printMessageAt("ship which is controlling all the attacks.", 100 ,90);
    io.printMessageAt("Good Luck !!!", 100 ,110);
    SDL_Flip(screen);
    SDL_PollEvent(&event);
    if(event.type == SDL_KEYUP) {
      keyCatch = false; 
    }
    if(event.type ==  SDL_QUIT) { break; }
    if(event.type == SDL_KEYDOWN) {
      switch ( event.key.keysym.sym ) {
        case SDLK_ESCAPE : if(!keyCatch) { keyCatch=true;done = true; menu=true;story=false;} break;
        case SDLK_q      : if(!keyCatch) { keyCatch=true;done = true; menu=true;story=false;} break;
        case SDLK_RETURN : {    
                              if ( !keyCatch ) {
                                keyCatch=true; done = false; menu=false ;story=false;
                                returnKey = true;
                              } 
                              break;
                            }
        default         : break;
      }
    }
  }
  SDL_Delay(250);
}

void Manager::play_func(bool done) {
  done = false; 
  menu=false;
  story=false;
  exit=true;
  SDLSound gameSound("propeller");
  bool shoot=false;
  Player &player=spritemanager.getPlayer();
  gameSound[2];
  while ( not done ) {
    
    spritemanager.draw();
    spritemanager.collisionCheck();
    SDL_Flip(screen);
    Uint32 ticks = clock.getElapsedTicks();
    spritemanager.update(ticks);
    SDL_PollEvent(&event);
    if(event.type ==  SDL_QUIT) { break; }
    if(event.type == SDL_KEYUP) {
      keyCatch = false; 
      //if (shoot == false)
        player.stop();
    }

    if(event.type == SDL_KEYDOWN) {
      switch ( event.key.keysym.sym ) {
        case SDLK_ESCAPE : if(!keyCatch) { clock.pause();keyCatch=true;done=true;menu=true;exit=false;story=false;} break;
        case SDLK_q      : if(!keyCatch) { clock.pause();keyCatch=true;done=true;menu=true;exit=false;story=false;} break;
        case SDLK_e      : 
         if ( !keyCatch ) {
            keyCatch = true;
            gameSound[3];
            spritemanager.explodeCurrentObject();
          }
          break;
        case SDLK_n      :
            if ( !keyCatch ) {
              keyCatch = true;
            }
            break;
        case SDLK_s      :
          if ( !keyCatch )   {
              keyCatch=true;
              shoot=true;
              gameSound[0];
              spritemanager.make_bullets();
            }break;
        case SDLK_t : case SDLK_SPACE :
          if ( !keyCatch ) {
            keyCatch = true;
            spritemanager.updateObjectToTrack();
          }
          break;
        case SDLK_F1     :
          if ( !keyCatch ) {
            keyCatch = true;
            spritemanager.setFlag();
            spritemanager.draw();
          }
          break;
        case SDLK_p      : {
          if (!keyCatch) {
            keyCatch = true;
            if ( clock.isPaused() ) clock.unpause();
            else clock.pause();
          }
          break;
        }
        case SDLK_LEFT  : { player.left(); break; }
        case SDLK_RIGHT : { player.right(); break; }
        case SDLK_UP    : { player.up(); break; }
        case SDLK_DOWN  : { player.down(); break; }
        
        default         : break;
      }
    }
  }
  gameSound.turnoffMusic(true);
}




