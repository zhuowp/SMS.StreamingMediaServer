// SMS.StreamingMediaServer.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "HikDeviceRegisterManager.h"

int main()
{
	std::cout << "Hello world!\n";
	HikDeviceRegisterManager hikDevRegisterManager;

	while (true)
	{
		int input = getchar();

		if (input == 'q')
		{
			break;
		}

		if (input == 'r')
		{
			hikDevRegisterManager.DeviceRegister("192.168.28.130", 8000, "admin", "admin888");
		}

		if (input == 'u')
		{
			hikDevRegisterManager.DeviceUnregister("192.168.28.130-8000");
		}
	}
}
