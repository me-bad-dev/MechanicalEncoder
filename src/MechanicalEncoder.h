#ifndef MechaEnc_h
#define MechaEnc_h

#include <Arduino.h>

class MechanicalEncoder {
	private:
        const unsigned char stateTable[7][4] = 
        {
            {0, 2, 4, 0},       
            {3, 0, 1, 0 | 16},  
            {3, 2, 0, 0},       
            {3, 2, 1, 0},
            {6, 0, 4, 0},
            {6, 5, 0, 0 | 32}, 
            {6, 5, 4, 0},
        };

		uint8_t pinCLK;  
		uint8_t pinDT;  

		int state;
		int value;

		int value_reported;

		int min;
		int max;
		bool loop;
		static void IRAM_ATTR HandleInterrupt();
	public:
		MechanicalEncoder(uint8_t _clk, uint8_t _dt, int _min, int _max, int _actual, bool _loop);
		void AttachInterrupts();
		void IRAM_ATTR Process();
		bool Updated();
		bool ProcessAndCheck();
		int Value();
		void SetValue(int _value);
};

#endif
