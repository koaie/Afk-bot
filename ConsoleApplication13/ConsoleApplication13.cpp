#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <Windows.h>

int Random(int Min, int Max)
{
	int Result = rand() % Max + Min;
	return Result;
}

void RandomNumber(int* Number, int Min, int Max)
{
	*Number = Random(Min, Max);
}

void ActiveCheck(bool* Active)
{
	while(true)
	{
	std::this_thread::sleep_for(std::chrono::milliseconds(5));
	if (GetAsyncKeyState(0x77))
	{
		*Active = false;
	}
	std::this_thread::sleep_for(std::chrono::milliseconds(5));
	}
}


class Action
{
	public:
	void Delay(int ms)
	{
	std::this_thread::sleep_for(std::chrono::milliseconds(ms));
	}

	void KeyboradInput(int VirtualCode , int DwFlags)
	{
	int HumanDelay;
	RandomNumber(&HumanDelay, 110, 250);
	Delay(HumanDelay);
	INPUT input;
	input.type = INPUT_KEYBOARD;
	input.ki.wScan = MapVirtualKey(VirtualCode , MAPVK_VK_TO_VSC);
	input.ki.time = NULL;
	input.ki.dwExtraInfo = NULL;
	input.ki.wVk = VirtualCode;
	input.ki.dwFlags = DwFlags;
	SendInput(1, &input, sizeof(INPUT));
	}

	void MouseInput(int x , int y , int DwFlags)
	{
	int HumanDelay;
	RandomNumber(&HumanDelay, 110, 250);
	Delay(HumanDelay);
	INPUT input;
	input.type = INPUT_MOUSE;
	input.mi.dx = x;
	input.mi.dy = y;
	input.mi.mouseData = NULL;
	input.mi.dwFlags = DwFlags;
	input.mi.time = NULL;
	input.mi.dwExtraInfo = NULL;
	SendInput(1, &input, sizeof(INPUT));
	}
};

void InputAction(int ActionNumber , int UseKeyInput, int UseMouseInput , int VirtualCode, int MouseDwFlags , int MouseDwFlags2, int UseDelayBetweenKeyInput, int UseDelayBetweenMouseInput)
{
	int RandomPixelsX, RandomPixelsY , RandomDelay , HumanDelay;
	RandomNumber(&HumanDelay, 110, 250);
	RandomNumber(&RandomDelay, 700, 1200);
	RandomNumber(&RandomPixelsX, -750, 1400);
	RandomNumber(&RandomPixelsY, -300, 600);
	Action t1;
	std::cout << ActionNumber << "\t Key:" << "\t " << VirtualCode << std::endl;
	if (UseKeyInput == 1)
	{
	t1.KeyboradInput(VirtualCode, NULL);
	}
	if (UseDelayBetweenKeyInput == 1)
	{
		t1.Delay(HumanDelay);
    }
    if (UseDelayBetweenKeyInput == 2)
	{
		t1.Delay(RandomDelay);
	}
	if (UseKeyInput == 1)
	{
		t1.KeyboradInput(VirtualCode, KEYEVENTF_KEYUP);
	}
    if (UseMouseInput == 1 || UseMouseInput == 2)
	{
	t1.MouseInput(RandomPixelsX, RandomPixelsY, MouseDwFlags);
	}
	if (UseDelayBetweenMouseInput == 1)
	{
		t1.Delay(HumanDelay);
	}
	if (UseDelayBetweenMouseInput == 2)
	{
		t1.Delay(RandomDelay);
	}
	if (UseMouseInput == 2)
	{
	t1.MouseInput(RandomPixelsX, RandomPixelsY, MouseDwFlags2);
	}
}



int main(int RandomAction , int LoopDelay , bool Active = false)
{
	SetConsoleTitle("Afk Bot");
	while (true)
	{
		Action Delay;
		Delay.Delay(1);
		while (true)
		{
			Delay.Delay(100);
			std::thread t1(ActiveCheck, &Active);
			t1.detach();
			while (GetAsyncKeyState(0x76))
			{
				Active = true;
				while (Active == true)
				{
					srand(Random(1, 100));
					RandomNumber(&LoopDelay, 100, 200);
					RandomNumber(&RandomAction, 1, 250);
					std::cout << "Delay: " << LoopDelay << std::endl;
					Delay.Delay(LoopDelay);

					if (RandomAction <= 25)
					{
						InputAction(1 , 1, 1, 0x57, MOUSEEVENTF_MOVE, NULL, 2, 1);
					}
    				if (RandomAction >= 26 && RandomAction <=50)
					{
						InputAction(2 , 1, 1, 0x44, MOUSEEVENTF_MOVE, NULL, 2, 1);
					}
					if (RandomAction >= 51 && RandomAction <= 75)
					{
						InputAction(3 , 1, 1, 0x20, MOUSEEVENTF_MOVE, NULL, 1, 1);
					}
					if (RandomAction >= 76 && RandomAction <= 100)
					{
						InputAction(4 , 1, 1, 0x57, MOUSEEVENTF_MOVE, NULL, 2, 1);
					}
					if (RandomAction >= 101 && RandomAction <= 125)
					{
						InputAction(5 , 1, 1, 0x53, MOUSEEVENTF_MOVE, NULL, 1, 1);
					}
					if (RandomAction >= 126 && RandomAction <= 135)
					{
						InputAction(6 , 1, 1, 0x51, MOUSEEVENTF_MOVE, NULL, 1, 1);
					}
					if (RandomAction >= 136 && RandomAction <= 150)
					{
						InputAction(7 , 1, 1, 0x51, MOUSEEVENTF_LEFTDOWN, MOUSEEVENTF_LEFTUP, 1, 2);
					}
					if (RandomAction >= 151 && RandomAction <= 175)
					{
						InputAction(8 , 1, 1, 0x41, MOUSEEVENTF_MOVE, NULL, 2, 1);
					}
					if (RandomAction >= 176 && RandomAction <= 200)
					{
						InputAction(9 , 1, 1, 0x11, MOUSEEVENTF_MOVE, NULL, 2, 1);
					}
					if (RandomAction >= 201 && RandomAction <= 250)
					{
						InputAction(10 , 1, 1, 0x57, MOUSEEVENTF_MOVE, NULL, 2, 1);
					}
				}
			}

			break;
		}
	}
    return 0;
}
