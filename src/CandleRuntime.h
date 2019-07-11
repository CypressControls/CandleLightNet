//This source is released under the LGPL V3
//Copyright (C) 2019 Cypress Robotics Corporation. 
//Portions of this code are taken from https://github.com/HubertD/candle_dll
#pragma once

#include "candle.h"
#include "candle_defs.h"
#include "CandleDevice.h"

using namespace System;
using namespace System::Threading;
using namespace System::Runtime::InteropServices;

namespace CypressRobotics {
	namespace CandleLightNet {
		public ref class CandleRuntime
		{
			// TODO: Add your methods for this class here.
		public:
			int getNumDevicesConnected();
			bool getDevice(int index, [Out]CandleDevice^% dev);
		};
	}
}