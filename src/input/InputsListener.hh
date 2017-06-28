/**
 * \file
 * \date June 21, 2017
 * \author Zermingore
 * \brief InputsListener declaration
 */

#ifndef INPUT_INPUTS_LISTENER_HH_
# define INPUT_INPUTS_LISTENER_HH_


/**
 * \class InputsListener
 * \brief Listen to keyboard events and register them into an events fifo
 */
class InputsListener
{
public:
  /**
   * \brief Polls events until the exit event was found
   * \note Infinite loop polling events, populating the KeyManager events queue
   * \note Initialize the KeyManager
   */
  static void listen();
};


#endif /* !INPUT_INPUTS_LISTENER_HH_ */
