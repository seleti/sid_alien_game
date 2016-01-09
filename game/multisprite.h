#ifndef MULTISPRITE__H
#define MULTISPRITE__H

#include <string>
#include <iostream>
#include <vector>
using std::string;

#include "drawable.h"
#include "frame.h"

class MultiframeSprite : public Drawable {
public:
  MultiframeSprite(const Vector2f& pos, const Vector2f& vel,
         const string& n, const std::vector<Frame*>& fms,const int nof,const int fi);
  MultiframeSprite(const MultiframeSprite& s);
  virtual ~MultiframeSprite() { }
  const string& getName() const { return name; }
  void setName(const string& n) { name = n; }
  virtual const Frame* getFrame() const { return frames[currentFrame]; }

  virtual void draw() const;
  virtual void update(Uint32 ticks);
  const std::vector<Frame *> frames;
private:
  string name;
  //const Frame* frame;
  //const Gamedata* gdata;
  //const std::vector<Frame *> frames;
  float dt;
  unsigned currentFrame;
  unsigned numberOfFrames;
  unsigned frameInterval;
  void advanceFrame(Uint32 ticks);
};
#endif
