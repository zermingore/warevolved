/**
 * \file
 * \date February 22, 2017
 * \author Zermingore
 * \brief StateSelectTarget class definition
 */


#include <context/StateSelectTarget.hh>

#include <common/enums/attack_result.hh>
#include <common/enums/input.hh>
#include <debug/Debug.hh>
#include <game/Battle.hh>
#include <game/Cell.hh>
#include <game/Map.hh>
#include <game/PathFinding.hh>
#include <game/Player.hh>
#include <game/Status.hh>
#include <graphics/MapGraphicsProperties.hh>
#include <graphics/graphic_types.hh>
#include <input/EventManager.hh>
#include <interface/Cursor.hh>



StateSelectTarget::StateSelectTarget()
  : _index_target(0)
{
  _evtMgr->registerEvent(e_input::MOVE_UP,
                         [=, this] { selectNextTarget();     });
  _evtMgr->registerEvent(e_input::MOVE_DOWN,
                         [=, this] { selectPreviousTarget(); });
  _evtMgr->registerEvent(e_input::MOVE_LEFT,
                         [=, this] { selectPreviousTarget(); });
  _evtMgr->registerEvent(e_input::MOVE_RIGHT,
                         [=, this] { selectNextTarget();     });
  _evtMgr->registerEvent(e_input::SELECTION,
                         [=, this] { validate();             });
  _evtMgr->registerEvent(e_input::EXIT,
                         [=, this] { exit();                 });

  // Graphical attributes initialization
  _targetHighlight = std::make_shared<graphics::Sprite> ("cursor");
  _targetHighlight->setColor(graphics::Color(255, 127, 127, 255));

  using p = graphics::MapGraphicsProperties;

  // explicitly using some floats for the division
  float x(static_cast<float> (_targetHighlight->texture()->getSize().x));
  float y(static_cast<float> (_targetHighlight->texture()->getSize().y));
  _targetHighlight->setScale( p::cellWidth() / x, p::cellHeight() / y);
  _targetHighlight->setOrigin(p::cellWidth() / 2, p::cellHeight() / 2);

  game::Status::battle()->getCurrentPlayer()->updateSelectedUnit();
  auto selected_unit{game::Status::battle()->map()->selectedUnit()};
  _holoUnit = std::make_shared<graphics::Sprite> (
    selected_unit->sprite()->texture());
  _holoUnit->setColor(graphics::Color(255, 127, 127, 255));

  x = static_cast<float> (_holoUnit->texture()->getSize().x);
  y = static_cast<float> (_holoUnit->texture()->getSize().y);
  _holoUnit->setScale(p::cellWidth() / x, p::cellHeight() / y);
}



StateSelectTarget::~StateSelectTarget()
{
  auto map {game::Status::battle()->map()};
  auto cells {map->cells()};
  const auto nb_col(map->nbColumns());
  const auto nb_lines(map->nbLines());

  for (auto col(0u); col < nb_col; ++col)
  {
    for (auto line(0u); line < nb_lines; ++line)
    {
      cells[col][line]->setHighlight(false);
    }
  }
}



void StateSelectTarget::fetchAttributes()
{
  if (_attributes.empty())
  {
    ERROR("StateSelectTarget::fetchAttributes called without attributes");
    assert(false);
    return;
  }

  auto p = std::static_pointer_cast<Coords> (_attributes[0]);
  _attackLocation.c = p->c;
  _attackLocation.l = p->l;

  auto selected_unit(game::Status::battle()->map()->selectedUnit());
  _path = std::make_shared<PathFinding> (selected_unit);
  const auto targets {_path->getTargets(selected_unit, _attackLocation)};
  auto map {game::Status::battle()->map()};
  for (const auto& target: *targets)
  {
    auto c = map->cell(target->coords());
    c->setHighlight(true);
    c->setHighlightColor(graphics::Color::Red);
  }

  // reset the attributes vector
  _attributes.clear();
}


void StateSelectTarget::resume()
{
  // retrieve attack coordinates from the attributes
  if (!_attributes.empty()) {
    fetchAttributes();
  }

  // we need a selected unit to continue
  game::Status::player()->updateSelectedUnit();
  auto selected_unit(game::Status::battle()->map()->selectedUnit());

  _targets = _path->getTargets(selected_unit, _attackLocation);

  assert(!_targets->empty() && "StateSelectTarget: no target available");
}


void StateSelectTarget::draw()
{
  game::Status::player()->cursor()->disableDrawThisFrame();

  auto selected_unit(game::Status::battle()->map()->selectedUnit());
  _targets = _path->getTargets(selected_unit, _attackLocation);

  if (!_targets || _targets->empty())
  {
    ERROR("No target to select");
    return;
  }
  if (_index_target > _targets->size())
  {
    ERROR("Invalid target index", _index_target, "size:", _targets->size());
    return;
  }

  _holoUnit->drawAtCell(_attackLocation);

  // emphasis (rotation) of the cursor over the zone
  static size_t angle = 0;
  angle = (angle + 1) % 360;

  using p = graphics::MapGraphicsProperties;
  auto width(p::cellWidth());
  auto height(p::cellHeight());

  // target cell coordinates
  auto coords((*_targets)[_index_target]->coords());
  auto pos_c(static_cast<float> (coords.c) * width
             + p::gridOffsetX() + width  / 2);
  auto pos_l(static_cast<float> (coords.l) * height
             + p::gridOffsetY() + height / 2);

  _targetHighlight->setPosition(pos_c, pos_l);
  _targetHighlight->setRotation(static_cast<float> (angle));

  _targetHighlight->draw();
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
  auto map(game::Status::battle()->map());

  // move the unit (if it's still alive)
  auto attackResult(map->attack((*_targets)[_index_target]));
  if (   attackResult != e_attack_result::ATTACKER_DIED
      && attackResult != e_attack_result::BOTH_DIED)
  {
    map->moveUnit(_attackLocation);
    game::Status::battle()->map()->selectedUnit()->setPlayed(true);
  }

  // Should lock the draw ? (without unlocking it ?)
  game::Status::player()->cursor()->setCoords(_attackLocation);

  game::Status::clearStates();
}


void StateSelectTarget::exit()
{
  game::Status::popCurrentState();
}
