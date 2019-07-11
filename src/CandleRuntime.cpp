#include "CandleRuntime.h"

int CypressRobotics::CandleLightNet::CandleRuntime::getNumDevicesConnected()
{
	candle_list_handle cList;

	bool result = candle_list_scan(&cList);
	if (!result) 
		return -1;

	uint8_t numDevices = -1;
	candle_list_length(cList, &numDevices);

	candle_list_free(cList);

	return numDevices;
}

bool CypressRobotics::CandleLightNet::CandleRuntime::getDevice(int index, CypressRobotics::CandleLightNet::CandleDevice^% dev)
{
	candle_list_handle cList;
	candle_handle hdev;

	bool result = candle_list_scan(&cList);
	if (!result)
		return false;

	if (!candle_dev_get(cList, 0, &hdev)) 
		return false;

	candle_device_t* h = ((candle_device_t*)hdev);
	
	dev = gcnew CandleDevice((candle_device_t*)hdev);
	return true;
}
