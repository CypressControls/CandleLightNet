//This source is released under the LGPL V3
//Copyright (C) 2019 Cypress Robotics Corporation. 
//Portions of this code are taken from https://github.com/HubertD/candle_dll
#pragma once

#include "candle.h"
#include "candle_defs.h"

using namespace System;
using namespace System::Threading;
using namespace System::Runtime::InteropServices;
using namespace CypressRobotics::CAN;

namespace CypressRobotics {
	namespace CandleLightNet {
		public ref class CandleDevice
		{
			~CandleDevice();

		private:
			Thread^ msgThread;

			candle_device_t* _handle;
			void listenThreadStart();

		internal:
			CandleDevice(candle_device_t* handle)
			{
				_handle = handle;
			}

		public:
			int getState();
			String^ getPath();
			bool open();
			bool sendMessage(CANMessage message);

			event CANMessageReceivedHandler^ CANMessageReceived;
		};

	}
}