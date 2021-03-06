// Brian Malloy        Game Construction

#include "manager.h"
Gamedata* Gamedata::instance;

int main(int, char*[]) {
   try {
      Manager game_manager;
      game_manager.game();
   }
   catch (const string& msg) { std::cout << msg << std::endl; }
   catch (const std::exception &exc)
{
    // catch anything thrown within try block that derives from std::exception
    std::cerr << exc.what();
}
 //  catch (...) {
  //    std::cout << "Oops, someone threw an exception!" << std::endl;
  // }
   return 0;
}
