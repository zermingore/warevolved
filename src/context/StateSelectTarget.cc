#include <context/StateSelectTarget.hh>
#include <common/enums/input.hh>
#include <input/EventManager.hh>
#include <common/Status.hh>
#include <game/applications/Battle.hh>
#include <game/Map.hh>
#include <game/PathFinding.hh>
#include <game/Cell.hh>
#include <graphics/MapGraphicsProperties.hh>
#include <common/enums/attack_result.hh>
#include <game/Player.hh>
#include <interface/Cursor.hh>


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

  // Graphical attributes initialization
  _targetHighlightImage = resources::ResourcesManager::getImage("cursor");
  _targetHighlight = _targetHighlightImage->sprite();
  _targetHighlight->setColor(sf::Color(255, 127, 127, 255));

  // explicitly using some floats for the division
  float x = _targetHighlight->getTexture()->getSize().x;
  float y = _targetHighlight->getTexture()->getSize().y;
  using p = graphics::MapGraphicsProperties;
  _targetHighlight->setScale(p::cellWidth()  / x, p::cellHeight() / y);

  _holoUnit = resources::ResourcesManager::getImage("soldiers"); /// \todo hard-coded soldiers
  _holoUnitSprite = _holoUnit->sprite();
  _holoUnitSprite->setColor(sf::Color(255, 127, 127, 255));
  x = _holoUnitSprite->getTexture()->getSize().x;
  y = _holoUnitSprite->getTexture()->getSize().y;
  _holoUnitSprite->setScale(p::cellWidth()  / x, p::cellHeight() / y);
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

  _targets = PathFinding::getTargets(Status::battle()->map()->selectedUnit(),
                                     Status::battle()->map()->cell(_attackLocation));

  assert(!_targets->empty() && "StateSelectTarget: no target available");
}


void StateSelectTarget::draw()
{
  assert(_targets && _targets->size() > 0 && _index_target <= _targets->size());

  _targetHighlightImage->drawAtCell((*_targets)[_index_target]->coords());
  _holoUnit->drawAtCell(_attackLocation);
}


// void StateSelectTarget::fetchAttributes() final;


void StateSelectTarget::selectPreviousTarget()
{
  if (_index_target == 0)
  {
    _index_target = _targets->size() - 1;
    return;
  }

  --_index_target;
}


void StateSelectTarget::selectNextTarget() {
  _index_target = (_index_target + 1) % _targets->size();
}


void StateSelectTarget::validate()
{
  // move the unit (if it's still alive)
  auto attackResult(Status::battle()->map()->attack((*_targets)[_index_target]));
  if (   attackResult != e_attack_result::ATTACKER_DIED
      && attackResult != e_attack_result::BOTH_DIED)
  {
    Status::battle()->map()->moveUnit(_attackLocation);
  }

  // move the cursor
  Status::player()->cursor()->setCoords(_attackLocation);

  Status::clearStates();
}


void StateSelectTarget::exit()
{
  Status::popCurrentState();
}
