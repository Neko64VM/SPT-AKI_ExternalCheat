#pragma once
#include "../GameSDK/GameSDK.h"

class CItem
{
private:

public:
    uintptr_t address;

	bool m_bIsCorpse{ false };
	int m_iMarketPrice{ 0 };
	std::string m_szItemName{};
	Vector3 m_vecOrigin{};

	bool GetAddress(uintptr_t& ptr);
	bool Update();
};