#include <fstream>
#include "Event.h"

Event* read(std::ifstream &f);

void dump(const Event& ev);

void clear(const Event* ev);

int main(int argc, char *argv[])
{

  // read file name from the command string
  const char *name = argv[1];

  // open file
  std::ifstream file(name);

  // loop over events
  Event* ev;
  while ( (ev=read(file)) != nullptr)
  {
    dump(*ev);
    clear(ev);
  }

  return 0;
}
