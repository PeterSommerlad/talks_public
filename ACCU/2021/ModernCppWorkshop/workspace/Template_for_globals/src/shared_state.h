#ifndef SRC_SHARED_STATE_H_
#define SRC_SHARED_STATE_H_


template<auto &state>
void signal_handler(int i){
	state += i;
}

#endif /* SRC_SHARED_STATE_H_ */
