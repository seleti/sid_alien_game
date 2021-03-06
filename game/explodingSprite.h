#include <vector>
#include <list>
#include "chunk.h"
#include "multisprite.h"
#include "drawable.h"

class ExplodingSprite : public MultiframeSprite {
public:
 // ExplodingSprite(const Sprite& s);
  ExplodingSprite(const MultiframeSprite& s);
 // ExplodingSprite(Frame* s,std::string name);
  ~ExplodingSprite();
  virtual void draw() const;
  virtual void update(Uint32 ticks);
//  void makeChunks(unsigned int);
  void makeChunks_multi(unsigned int);
  void makeChunks_frame(unsigned int);
  unsigned int chunkCount() const { return chunks.size(); }
  unsigned int freeCount()  const { return freeList.size(); }
private:
  std::list<Chunk> chunks;
  std::list<Chunk> freeList;
  std::vector<Frame*> frames;
 // Frame* fframe;
  ExplodingSprite(const ExplodingSprite&);
  ExplodingSprite& operator=(const ExplodingSprite&);
};
