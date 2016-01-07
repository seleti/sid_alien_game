#include "gui.h"

Gui::~Gui() {
SDL_FreeSurface(surfacenew);
SDL_FreeSurface(surfaceresume);
SDL_FreeSurface(surfaceexit);
SDL_FreeSurface(surfaceoption);
SDL_FreeSurface(surfaceOff);
SDL_FreeSurface(surfaceOn);
}

Gui::Gui() : 
  io( IOManager::getInstance() ),
  parser( "xmlSpec/menu.xml" ),
  buttons(), 
  clicks(),
  nextIcon(0),
  click(0),
  stop(false),
  first(true),
  backSurface( io.loadAndSet(Gamedata::getInstance()->getXmlStr("backFile"), true) ),  
  world(FrameFactory::getInstance()->getFrame("back",backSurface)[0]),
  bbackSurface( io.loadAndSet(Gamedata::getInstance()->getXmlStr("bbackFile"), false) ),  
  bworld(FrameFactory::getInstance()->getFrame("bback",bbackSurface)[0],5),
  surfaceOn(io.loadAndSet( parser.getXmlStr("glowFile"), true)),
  surfacenew(io.loadAndSet(parser.getXmlStr("newFile"), true)),
  surfaceresume(io.loadAndSet(parser.getXmlStr("resumeFile"), true)),
  surfaceoption(io.loadAndSet(parser.getXmlStr("optionFile"), true)),
  surfaceexit(io.loadAndSet(parser.getXmlStr("exitFile"), true)),
  surfaceOff(io.loadAndSet(parser.getXmlStr("glowFile"), true))
  
{
  float x = parser.getXmlInt("resumeX");
  float y = parser.getXmlInt("resumeY");
  Frame resumeFrame(surfaceresume, 
            parser.getXmlInt("resumeWidth"), 
            parser.getXmlInt("resumeHeight"), 
            parser.getXmlInt("resumeSrcX"), 
            parser.getXmlInt("resumeSrcY")); 
  buttons.push_back( Button("resume", resumeFrame, Vector2f(x, y)) );

  x = parser.getXmlInt("newX");
  y = parser.getXmlInt("newY");
  Frame newFrame(surfacenew, 
            parser.getXmlInt("newWidth"), 
            parser.getXmlInt("newHeight"), 
            parser.getXmlInt("newSrcX"), 
            parser.getXmlInt("newSrcY")); 
  buttons.push_back( Button("new", newFrame, Vector2f(x, y)) );

  x = parser.getXmlInt("optionX"); 
  y = parser.getXmlInt("optionY"); 
  Frame optionFrame(surfaceoption, 
            parser.getXmlInt("optionWidth"), 
            parser.getXmlInt("optionHeight"), 
            parser.getXmlInt("optionSrcX"), 
            parser.getXmlInt("optionSrcY")); 
  buttons.push_back( Button("option", optionFrame, Vector2f(x, y)) );

  x = parser.getXmlInt("exitX"); 
  y = parser.getXmlInt("exitY"); 
  Frame exitFrame(surfaceexit, 
            parser.getXmlInt("exitWidth"), 
            parser.getXmlInt("exitHeight"), 
            parser.getXmlInt("exitSrcX"), 
            parser.getXmlInt("exitSrcY")); 
  buttons.push_back( Button("exit", exitFrame, Vector2f(x, y)) );

  Frame clickon(surfaceOff, 
              parser.getXmlInt("glowWidth"), 
              parser.getXmlInt("glowHeight"), 
              parser.getXmlInt("glowSrcX"), 
              parser.getXmlInt("glowSrcX")); 
  clicks.push_back( clickon );

  Frame clickoff(surfaceOn, 
              parser.getXmlInt("glowWidth"), 
              parser.getXmlInt("glowHeight"), 
              parser.getXmlInt("glowSrcX"), 
              parser.getXmlInt("glowSrcX")); 
  clicks.push_back( clickoff );
  Viewport::getInstance().trackSprite(buttons[0].frame);
}

void Gui::draw() const {
  bworld.draw();
  world.draw();
    Vector2f pos = buttons[nextIcon].position;
  clicks[click].draw(pos[0], pos[1]);
  for (int i=0;i<4;i++){
    buttons[i].frame.draw( buttons[i].position );
  }
}

void Gui::guistop(bool f) {
  f=false;
  if (stop) 
    stop=false;
  else 
    stop=true;
}

void Gui::update() {
  if(not stop ) {  
    for (int i=0;i<4;i++){
      buttons[i].position=buttons[i].position + Vector2f(0.15,0);
    }
     Viewport::getInstance().update(buttons[0].position[0],buttons[0].position[1]);
     bworld.update();
     world.update();
  }
}

void Gui::explode() {

}

