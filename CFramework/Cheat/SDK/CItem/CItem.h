#pragma once
#include "../GameSDK/GameSDK.h"

class CItem
{
private:

public:
    uintptr_t address;

	int m_iPrice;
	std::string m_CName;
	Vector3 m_vecLocation;

	bool GetAddress(uintptr_t& ptr);
	bool Update();
};