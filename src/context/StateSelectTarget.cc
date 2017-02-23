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


// void StateSelectTarget::resume();

void StateSelectTarget::draw()
{
  assert(_targets && _targets->size() > 0 && _index_target <= _targets->size());

  _targetHighlight->setColor(sf::Color(255, 127, 127, 255));
  _targetHighlightImage->drawAtCell((*_targets)[_index_target]->coords());
}


// void StateSelectTarget::fetchAttributes() final;


void StateSelectTarget::selectPreviousTarget()
{
  if (_index_target == 0) {
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
  /// \todo add a state to select a target from the path finding
  NOTICE("validate");


  /// \todo give also coordinates of the holo unit (from where it attacks)
  //Status::battle()->map()->attack(target);
  Status::clearStates();
}


void StateSelectTarget::exit()
{
  Status::popCurrentState();
}
