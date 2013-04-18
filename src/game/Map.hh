#ifndef MAP_HH_
# define MAP_HH_

class Map
{
public:
  Map();
  Map(unsigned int nbColumns, unsigned int nbLines);
  ~Map();

  unsigned int getNbLines();
  unsigned int getNbColumns();

private:
  unsigned int _nbColumns;
  unsigned int _nbLines;
};

#endif /* !MAP_HH_ */
