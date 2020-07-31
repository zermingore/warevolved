/**
 * \file
 * \date July 31, 2020
 * \author Zermingore
 * \brief Random class templates definition
 */

#ifndef RANDOM_HXX_
# define RANDOM_HXX_

template<typename T>
T Random::randVal(T min, T max)
{
  std::uniform_int_distribution<T> rand(min, max);
  return static_cast<T> (rand(*_generator));
}

#endif // RANDOM_HXX_
