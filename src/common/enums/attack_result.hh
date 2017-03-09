/**
 * \file
 * \date February 27, 2017
 * \author Zermingore
 */

#ifndef ATTACK_RESULT_HH_
# define ATTACK_RESULT_HH_

/**
 * \enum e_attack_result
 * \brief Identifies the result of an attack
 */
enum class e_attack_result
{
  INVALID = 0,
  NONE_DIED,
  ATTACKER_DIED,
  DEFENDER_DIED,
  BOTH_DIED,
};

#endif /* !ATTACK_RESULT_HH_ */
