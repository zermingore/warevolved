#include <context/StateSelectTarget.hh>

#include <debug/Debug.hh>
#include <common/enums/input.hh>
#include <game/Status.hh>
#include <common/enums/attack_result.hh>
#include <input/EventManager.hh>
#include <interface/Cursor.hh>
#include <game/Battle.hh>
#include <game/Map.hh>
#include <game/Cell.hh>
#include <game/Player.hh>
#include <game/PathFinding.hh>
#include <graphics/MapGraphicsProperties.hh>
#include <graphics/GraphicsEngine.hh>
#include <graphics/graphic_types.hh>



StateSelectTarget::StateSelectTarget()
  : State()
  , _index_target(0)
{
  _evtMgr->registerEvent(e_input::MOVE_UP,    [=] { selectNextTarget();     });
  _evtMgr->registerEvent(e_input::MOVE_DOWN,  [=] { selectPreviousTarget(); });
  _evtMgr->registerEvent(e_input::MOVE_LEFT,  [=] { selectPreviousTarget(); });
  _evtMgr->registerEvent(e_input::MOVE_RIGHT, [=] { selectNextTarget();     });
  _evtMgr->registerEvent(e_input::SELECTION,  [=] { validate();             });
  _evtMgr->registerEvent(e_input::EXIT,       [=] { exit();                 });

  // Graphical attributes initialization
  _targetHighlightImage = resources::ResourcesManager::getImage("cursor");
  _targetHighlight = _targetHighlightImage->sprite();
  _targetHighlight->setColor(graphics::Color(255, 127, 127, 255));

  using p = graphics::MapGraphicsProperties;

  // explicitly using some floats for the division
  float x(static_cast<float> (_targetHighlight->getTexture()->getSize().x));
  float y(static_cast<float> (_targetHighlight->getTexture()->getSize().y));
  _targetHighlight->setScale(p::cellWidth()  / x, p::cellHeight() / y);
  _targetHighlight->setOrigin(p::cellWidth() / 2, p::cellHeight() / 2);

  _holoUnit = resources::ResourcesManager::getImage("soldiers"); /// \todo hard-coded soldiers
  _holoUnitSprite = _holoUnit->sprite();
  _holoUnitSprite->setColor(graphics::Color(255, 127, 127, 255));

  x = static_cast<float> (_holoUnitSprite->getTexture()->getSize().x);
  y = static_cast<float> (_holoUnitSprite->getTexture()->getSize().y);
  _holoUnitSprite->setScale(p::cellWidth() / x, p::cellHeight() / y);
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
  _attackLocation.c = p->c;
  _attackLocation.l = p->l;

  // reset the attributes vector
  _attributes.clear();
}


void StateSelectTarget::resume()
{
  // retrieve attack coordinates from the attributes
  if (_attributes.size()) {
    fetchAttributes();
  }

  _targets = PathFinding::getTargets(game::Status::battle()->map()->selectedUnit(),
                                     game::Status::battle()->map()->cell(_attackLocation));

  assert(!_targets->empty() && "StateSelectTarget: no target available");
}


void StateSelectTarget::draw()
{
  assert(_targets && _targets->size() > 0 && _index_target <= _targets->size());

  _holoUnit->drawAtCell(_attackLocation);

  // emphasis (scale and rotation) of the cursor over the target
  static float scale_factor = 1;
  static size_t angle = 0;
  angle % 360 > 180 ? scale_factor -= 0.001f : scale_factor += 0.001f;
  ++angle; // \todo angle will overflow

  using p = graphics::MapGraphicsProperties;
  auto width(p::cellWidth());
  auto height(p::cellHeight());

  // target cell coordinates
  auto coords((*_targets)[_index_target]->coords());
  auto pos_c(static_cast<float> (coords.c) * width  + p::gridOffsetX() + width  / 2);
  auto pos_l(static_cast<float> (coords.l) * height + p::gridOffsetY() + height / 2);
  _targetHighlightImage->sprite()->setPosition(pos_c, pos_l);

  _targetHighlight->setRotation(static_cast<float> (angle));

  graphics::GraphicsEngine::draw(_targetHighlight);
}


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
  auto attackResult(game::Status::battle()->map()->attack((*_targets)[_index_target]));
  if (   attackResult != e_attack_result::ATTACKER_DIED
      && attackResult != e_attack_result::BOTH_DIED)
  {
    game::Status::battle()->map()->moveUnit(_attackLocation);
  }

  // move the cursor
  game::Status::player()->cursor()->setCoords(_attackLocation);

  game::Status::clearStates();
}


void StateSelectTarget::exit()
{
  game::Status::popCurrentState();
}
