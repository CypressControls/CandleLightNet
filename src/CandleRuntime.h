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