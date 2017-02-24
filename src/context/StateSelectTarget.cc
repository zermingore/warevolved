#include <context/StateSelectTarget.hh>
#include <common/enums/input.hh>
#include <input/EventManager.hh>
#include <common/Status.hh>
#include <game/applications/Battle.hh>
#include <game/Map.hh>
#include <game/PathFinding.hh>
#include <game/Cell.hh>
#include <graphics/MapGraphicsProperties.hh>


StateSelectTarget::StateSelectTarget()
  : State()
  , _index_target(0)
{
  _evtMgr->registerEvent(e_input::MOVE_UP_1,    [=] { selectNextTarget();     });
  _evtMgr->registerEvent(e_input::MOVE_DOWN_1,  [=] { selectPreviousTarget(); });
  _evtMgr->registerEvent(e_input::MOVE_LEFT_1,  [=] { selectPreviousTarget(); });
  _evtMgr->registerEvent(e_input::MOVE_RIGHT_1, [=] { selectNextTarget();     });
  _evtMgr->registerEvent(e_input::SELECTION_1,  [=] { validate();             });
  _evtMgr->registerEvent(e_input::EXIT_1,       [=] { exit();                 });

  _targets = PathFinding::getEnemyPositions();
  assert(!_targets->empty() && "StateSelectTarget: no target available");

  // Graphical attributes initialization
  _targetHighlightImage = resources::ResourcesManager::getImage("cursor");
  _targetHighlight = _targetHighlightImage->sprite();

  // explicitly using some floats for the division
  float x = _targetHighlight->getTexture()->getSize().x;
  float y = _targetHighlight->getTexture()->getSize().y;
  using p = graphics::MapGraphicsProperties;
  _targetHighlight->setScale(p::cellWidth()  / x, p::cellHeight() / y);
}


void StateSelectTarget::fetchAttributes()
{
  if (!_attributes.size())
  {
    ERROR("fetchAttributes called without available attributes");
    assert(!"No attribute found");
    return;
  }

  auto p = std::static_pointer_cast<Coords> (_attributes[0]);
  _attackLocation.x = p->x;
  _attackLocation.y = p->y;

  // reset the attributes vector
  _attributes.clear();
}


void StateSelectTarget::resume()
{
  // retrieve attack coordinates from the attributes
  if (_attributes.size()) {
    fetchAttributes();
  }
}


void StateSelectTarget::draw()
{
  assert(_targets && _targets->size() > 0 && _index_target <= _targets->size());

  _targetHighlight->setColor(sf::Color(255, 127, 127, 255));
  _targetHighlightImage->drawAtCell((*_targets)[_index_target]->coords());
}


// void StateSelectTarget::fetchAttributes() final;


void StateSelectTarget::selectPreviousTarget()
{
  if (_index_target == 0)
  {
    _index_target = _targets->size();
    return;
  }

  --_index_target;
}


void StateSelectTarget::selectNextTarget() {
  _index_target = (_index_target + 1) % _targets->size();
}


void StateSelectTarget::validate()
{
  Status::battle()->map()->attack((*_targets)[_index_target]);
  Status::clearStates();

  // move the unit
  Status::battle()->map()->moveUnit(_attackLocation); /// \todo check if the unit survived
}


void StateSelectTarget::exit()
{
  Status::popCurrentState();
}
