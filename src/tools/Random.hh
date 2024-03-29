/**
 * \file
 * \date July 29, 2020
 * \author Zermingore
 * \brief Random class declaration
 */

#ifndef RANDOM_HH_
# define RANDOM_HH_

# include <random>
# include <memory>


class OptionsParser;
enum class e_terrain;


/**
 * \class Random
 * \brief Random generator class
 * \note Static class
 */
class Random
{
public:
  /**
   * \brief Random generator initialization
   * \param options_parser Options parser to retrieve the seed
   */
  static void init(const OptionsParser& options_parser);

  static auto seed() { return _randomSeed; }

  /**
   * \brief Random int generation
   * \param min Inclusive minimal value
   * \param max Inclusive maximal value
   * \return Value between min and max
   */
  static int randInt(int min, int max);

  template<typename T>
  static T randVal(T min, T max);

  /**
   * \brief Random terrain generation
   * \return Random terrain
   */
  static e_terrain randTerrain();

  /**
   * \brief Random bool generation
   * \return Random boolean
   */
  static bool randBool();


private:
  inline static long unsigned int _randomSeed; ///< Random generator seed
  inline static std::unique_ptr<std::mt19937> _generator;
};


# include <tools/Random.hxx>

#endif /* !RANDOM_HH_ */
