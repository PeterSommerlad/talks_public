#ifndef PLANET_H_
#define PLANET_H_

#include <numeric>
#include <iterator>
#include <vector>

using Species = unsigned;

template<unsigned nOfSpecies>
struct Planet {
  //gigantic type with data on heap
  Planet() : species(nOfSpecies) {
	  std::iota(std::begin(species), std::end(species), 0);
  }
private:
  std::vector<Species> species;
};


#endif /* PLANET_H_ */
