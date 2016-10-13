#include <input/EventManager.hh>
#include <common/enums/states.hh>
#include <input/KeyManager.hh>
#include <common/Status.hh>
#include <common/Settings.hh>
#include <interface/Interface.hh>
#include <graphics/GraphicsEngine.hh>


bool EventManager::process(e_input input)
{
 if (_callbacks.find(input) == _callbacks.end())
 {
   std::cout << "callback not found for input "
             << static_cast<int> (input)
             << std::endl;
   return false;
 }

 _callbacks[input]();
 return true;
}
