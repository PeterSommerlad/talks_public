#include "templatewithstaticmember.h"

int setDummyTo42(){
	using dummytype=staticmember<int>;
	dummytype::dummy=42;
	return dummytype::dummy;
}
