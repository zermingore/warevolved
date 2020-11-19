/**
 * \file
 * \date November 9, 2020
 * \author Zermingore
 * \brief StateSelectCell abstract class declaration
 */

#ifndef STATE_SELECT_CELL_HH_
# define STATE_SELECT_CELL_HH_

# include <vector>
# include <memory>
# include <context/State.hh>
# include <graphics/graphic_types.hh>

class Cell;

namespace graphics {
  class Sprite;
}



/**
 * \class StateSelectCell
 * \brief State in charge of the drop zone selection
 * \note This State is active after the Drop Off or Get Out order
 */
class StateSelectCell: public State
{
public:
  /**
   * \brief registers to callbacks. Initializes the graphical attributes
   */
  StateSelectCell();

  /**
   * \brief Destructor; deactivates cells highlights
   */
  ~StateSelectCell() override;


protected:
  /**
   * \brief Select the previous Cell
   * \note loops on the last Cell if called on the first one
   */
  void selectPrevious();

  /**
   * \brief Highlights the next Cell in the list
   * \note loops on the first Cell if called on the last one
   */
  void selectNext();

  /**
   * \brief Validates the current selected Cell
   * \note must be overriden
   */
  virtual void validate() = 0;

  /**
   * \brief Callback associated with the exit menu event
   */
  virtual void exit();



  /// Free cells list from the PathFinding
  std::vector<std::shared_ptr<const Cell>> _cells;

  size_t _indexSelect; ///< index of the selected cell

  /// sprite associated to the highlight of the selected zone
  std::shared_ptr<graphics::Sprite> _selectHighlight;

  Coords _originLocation; ///< Cell from which we select something
};

#endif /* !STATE_SELECT_CELL_HH_ */
