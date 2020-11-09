/*
 * pinsFiltering.h
 *
 *  Created on: Oct 20, 2020
 *      Author: Jacek
 */

#ifndef PINSFILTERING_H_
#define PINSFILTERING_H_

#include "functional"
#include "vector"
#include "pinsService.h"

#ifdef __cplusplus
extern "C"
{
#endif

	using namespace std;
	class PinsFiltering
	{
		private:
			function<uint8_t(uint8_t)> Read_Pin_State;
			function<uint32_t()> Get_Milisecond;
			vector<uint8_t> pinsToFiltering;
			vector<uint32_t> filteringTime; //[ms]
			vector<bool> pinsStates;
			vector<bool> filteredPinsStates;
			vector<uint32_t> timeStateStart;
			size_t previousVectorSize;
			void Resize_Vectors();

		public:
			PinsFiltering(function<uint8_t(uint8_t)> Read_Pin, function<uint32_t()> Get_Milisecond);
		~PinsFiltering();
			void Add_Pin_To_Filtering(uint8_t pinNumber, uint32_t filteringTime);
			bool Get_Filtered_Pin_State(uint8_t pinNumber);
			void Filter_Pins_States();

	};
#ifdef __cplusplus
}
#endif

#endif /* PINSFILTERING_H_ */
