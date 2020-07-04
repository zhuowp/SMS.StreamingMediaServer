// SMS.StreamingMediaServer.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "HikDeviceRegisterManager.h"
#include "HikRealtimePlayController.h"
#include "Test.cpp"

int main()
{
	std::cout << "Welcome To Use SMS Streaming Media Server!\n";
	HikDeviceRegisterManager hikDevRegisterManager = *HikDeviceRegisterManager::GetInstance();
	HikRealtimePlayController realtimePlayController;
	int64_t playHandle = -1;
	while (true)
	{
		string command;
		getline(cin, command);

		if (command == "q")
		{
			break;
		}
		else if (command == "start play")
		{
			StartPlay();
			return 0;
			LONG loginHandle = hikDevRegisterManager.DeviceRegister("192.168.28.130", 8000, "admin", "admin888");

			playHandle = realtimePlayController.PlayLive(loginHandle, 1, 1);
		}
		else if (command == "stop play")
		{
			realtimePlayController.StopLive(playHandle);
			hikDevRegisterManager.DeviceUnregister("192.168.28.130-8000");
		}

		if (command == "u")
		{
			hikDevRegisterManager.DeviceUnregister("192.168.28.130-8000");
		}
	}
}
