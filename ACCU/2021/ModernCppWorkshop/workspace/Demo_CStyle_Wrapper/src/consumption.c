#include "consumption.h"


literPer100km consumption(literGas l, kmDriven km) {
	 literPer100km res = {l.l/(km.km/100.0)};
	 return res;
}

void dummy(){
	literGas l={42};
	kmDriven km={500};
//	literPer100km res = consumption(km,l); // error even in C
}
