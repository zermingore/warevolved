#include <common/debug/EnumPrint.hh>


namespace debug {

void printState(e_state state)
{
  switch (state)
  {
    case e_state::NONE:
      PRINTF("STATE: NONE");
      break;

    case e_state::PLAYING:
      PRINTF("STATE: PLAYING");
      break;

    case e_state::MAP_MENU:
      PRINTF("STATE: MAP_MENU");
      break;

    case e_state::SELECTION_UNIT:
      PRINTF("STATE: SELECTION_UNIT");
      break;

    case e_state::MOVING_UNIT:
      PRINTF("STATE: MOVING_UNIT");
      break;

    case e_state::ACTION_MENU:
      PRINTF("STATE: ACTION_MENU");
      break;

    case e_state::SELECT_TARGET:
      PRINTF("STATE: SELECT_TARGET");
      break;

    default:
      exit(1);
//        assert(!"Debug printing failure (e_state)");
  }
}

} // namespace debug
