#ifndef SRC_CONSUMPTION_H_
#define SRC_CONSUMPTION_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef
struct literGas{
	double l;
} literGas;
typedef
struct kmDriven{
	double km;
} kmDriven;
typedef
struct literPer100km {
	double consumption;
} literPer100km;


 literPer100km consumption(literGas l, kmDriven km);
#ifdef __cplusplus
}
#endif


#endif /* SRC_CONSUMPTION_H_ */
