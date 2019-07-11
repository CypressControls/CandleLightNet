//This source is released under the LGPL V3
//Copyright (C) 2019 Cypress Robotics Corporation. 
//Portions of this code are taken from https://github.com/HubertD/candle_dll
#include "CandleDevice.h"

CypressRobotics::CandleLightNet::CandleDevice::~CandleDevice()
{
	candle_dev_free(_handle);
	if (msgThread != nullptr)
		msgThread->Abort();
}

void CypressRobotics::CandleLightNet::CandleDevice::listenThreadStart()
{
	while (true)
	{
		candle_frame_t frame;
		if (candle_frame_read(_handle, &frame, 1000)) {

			if (candle_frame_type(&frame) == CANDLE_FRAMETYPE_RECEIVE) {

				uint8_t dlc = candle_frame_dlc(&frame);
				uint8_t* data = candle_frame_data(&frame);
				unsigned int id = candle_frame_id(&frame);

				array<unsigned char>^ newData = gcnew array<unsigned char>(8);
				for (int i = 0; i < 8; ++i)
				{
					newData[i] = data[i];
				}

				CANMessage message(id, newData, 8);
				CANMessageReceived(this, message);
			}
		}
		else {
			candle_err_t err = candle_dev_last_error(_handle);
			if (err == CANDLE_ERR_READ_TIMEOUT) {
				printf("Timeout waiting for CAN data\n");
			}
			else {
				printf("Error reading candle frame: %d\n", err);
			}
		}
	}
}

int CypressRobotics::CandleLightNet::CandleDevice::getState()
{
	candle_devstate_t state;
	candle_dev_get_state(_handle, &state);
	return (int)state;
}

String^ CypressRobotics::CandleLightNet::CandleDevice::getPath()
{
	return gcnew String(_handle->path);
}

bool CypressRobotics::CandleLightNet::CandleDevice::open()
{
	bool res = candle_dev_open(_handle);
	if (res)
	{
		//set bitrate
		res = candle_channel_set_bitrate(_handle, 0, 250000);
		if (res)
		{
			res = candle_channel_start(_handle, 0, 0);
			if (res)
			{
				msgThread = gcnew Thread(gcnew ThreadStart(this, &CandleDevice::listenThreadStart));
				msgThread->Name = "Message Listener";
				msgThread->Start();
			}
		}
		return res;
	}
	return res;
}

bool CypressRobotics::CandleLightNet::CandleDevice::sendMessage(CANMessage message)
{
	candle_frame_t frame;
	frame.can_id = message.ID;
	for (int i = 0; i < message.DataLength; ++i)
		frame.data[i] = message.Data[i];

	//so many other fields... do we need them? need to figure that out. 

	return candle_frame_send(_handle, 0, &frame);
}
