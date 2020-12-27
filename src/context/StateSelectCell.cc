/**
 * \file
 * \date November 9, 2020
 * \author Zermingore
 * \brief StateSelectCell class definition
 */

#include <context/StateSelectCell.hh>

#include <game/Battle.hh>
#include <game/Cell.hh>
#include <game/Map.hh>
#include <game/Status.hh>
#include <graphics/graphic_types.hh>
#include <graphics/Properties.hh>
#include <graphics/Sprite.hh>
#include <input/EventManager.hh>



StateSelectCell::StateSelectCell()
  : _indexSelect(0)
{
  _evtMgr->registerEvent(e_input::MOVE_UP,
                         [=, this] { selectNext();     });
  _evtMgr->registerEvent(e_input::MOVE_DOWN,
                         [=, this] { selectPrevious(); });
  _evtMgr->registerEvent(e_input::MOVE_LEFT,
                         [=, this] { selectPrevious(); });
  _evtMgr->registerEvent(e_input::MOVE_RIGHT,
                         [=, this] { selectNext();     });
  _evtMgr->registerEvent(e_input::SELECTION,
                         [=, this] { validate();       });
  _evtMgr->registerEvent(e_input::EXIT,
                         [=, this] { exit();           });

  // Graphical attributes initialization
  _selectHighlight = std::make_shared<graphics::Sprite> ("cursor");
  _selectHighlight->setColor(graphics::Color(255, 127, 127, 255));

  using p = graphics::Properties;

  // explicitly using some floats for the division
  float x(static_cast<float> (_selectHighlight->texture()->getSize().x));
  float y(static_cast<float> (_selectHighlight->texture()->getSize().y));
  _selectHighlight->setScale( p::cellWidth() / x, p::cellHeight() / y);
  _selectHighlight->setOrigin(p::cellWidth() / 2, p::cellHeight() / 2);
}



StateSelectCell::~StateSelectCell()
{
  game::Status::battle()->map()->clearHighlights();
}



void StateSelectCell::selectPrevious()
{
  if (_indexSelect == 0)
  {
    _indexSelect = _cells.size() - 1;
    return;
  }

  --_indexSelect;
}



void StateSelectCell::selectNext()
{
  _indexSelect = (_indexSelect + 1) % _cells.size();
}



void StateSelectCell::exit()
{
  game::Status::popCurrentState();
}
