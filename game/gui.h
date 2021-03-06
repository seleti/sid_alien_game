#include <vector>
#include <map>
#include <string>
using std::string;
#include "ioManager.h"

#include "parseXML.h"
#include "world.h"
#include "FrameFactory.h"
#include "gamedata.h"

using std::vector;
using std::map;

class Gui {
public:
  Gui();
  ~Gui();
  void draw() const;
  void update();
  void explode();
  const string& getIconClicked() const { return buttons[nextIcon].name; } 
  void increment() { nextIcon = (nextIcon + 1) % buttons.size(); }
  void decrement() { nextIcon = (nextIcon + buttons.size()-1) % buttons.size(); }
  void lightOn() { click = 1; }
  void lightOff() { click = 0; }
  void guistop(bool f);
  void setFirst(bool x){first=x;}
private:
  struct Button {
    Button(const string& n, const Frame& f, const Vector2f& pos) : 
      name(n), 
      frame(f),
      position(pos) 
    {}
    Button(const Button& button) : 
      name(button.name), 
      frame(button.frame),
      position(button.position) 
    {}
    string name;
    Frame frame;
    Vector2f position;
  };
  IOManager& io;
  const ParseXML parser;
  // Buttons are stored in alphabetical order
  vector<Button> buttons; 
  vector<Frame> clicks;
  unsigned nextIcon;
  unsigned click;
  bool stop;
  bool first;
  SDL_Surface * const backSurface;
  World world;
  SDL_Surface * const bbackSurface;
  World bworld;
  Gui(const Gui&);
  Gui& operator=(const Gui&);
  SDL_Surface* surfaceOn;
  SDL_Surface* surfacenew;
  SDL_Surface* surfaceresume;
  SDL_Surface* surfaceoption;
  SDL_Surface* surfaceexit;
  SDL_Surface* surfaceOff;



};
