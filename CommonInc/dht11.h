/*
 * dht11.h
 *
 *  Created on: 3 lis 2020
 *      Author: Jacek
 */

#ifndef DHT11_H_
#define DHT11_H_

#include "functional"

#ifdef __cplusplus
extern "C"
{
#endif
using namespace std;
	class DHT11_Service
	{
		private:
			function<uint8_t(uint8_t)> Read_Pin_State;
			function<void(const uint16_t)> Delay_us;
			function<void(uint8_t)> Set_Pin_Input;
			function<void(uint8_t)> Set_Pin_Output;
			function<void(uint8_t,uint8_t)>Write_Pin;
			function<uint32_t()> Get_Miliseconds;
			uint8_t communicationState;
			float humadity;
			float temperature;
			uint8_t pinNumber;//pin do komunikacji
			uint32_t previousMilisecond;
			bool isDataValid = false;
		private:
			uint8_t* ReadDataFromDHT(uint8_t dataRecevied[]);
			uint8_t GetHighStateDuration(uint8_t timeout);
			uint8_t GetByteFromDHT();
			void SetHighStateForStart();
			void SetInputStateForReadResponse();
			uint8_t IsStateDetectedWithTimeout(uint8_t expectedState, uint16_t timeout);
			bool IsDataValid(uint8_t dataReceived[]);
			void CommunicationWithDHT();
			void CheckIfTimeElapsedToStart();
			void SetLowStateForStart();
			void CheckIfEnoughTimeElapsedForWaiting();
			void SetHighStateForWaiting();
		public:
			DHT11_Service(function<uint8_t(uint8_t)> Read_Pin,
					function<void(const uint16_t)> Delay_us,
					function<void(uint8_t)> Set_Pin_Input,
					function<void(uint8_t)> Set_Pin_Output,
					function<void(uint8_t,uint8_t)>Write_Pin,
					function<uint32_t()> Get_Milisecond,
					uint8_t pinNumber);
			~DHT11_Service();
			float GetHumadity();
			float GetTemperature();
			void Communication_Init();
			void Communication_Loop();
	};


#ifdef __cplusplus
}
#endif
#endif /* DHT11_H_ */
