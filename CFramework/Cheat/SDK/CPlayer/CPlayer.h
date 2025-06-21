#pragma once
#include "../GameSDK/GameSDK.h"

struct CBoneArray {
	uint64_t address[150]{};
};

class CPlayer
{
public:
	uintptr_t m_address{ 0 };

	uintptr_t m_pProfile{ 0 };
	uintptr_t m_pInfo{ 0 };
	uintptr_t m_pSetting{ 0 };
	uintptr_t m_pBodyController{ 0 };
	uintptr_t m_pWeaponAnimation{ 0 };

	// データ
	float m_fHealth{ 0.f };
	float m_fHealthMax{ 0.f };
	int m_iSpawnType{ 0 };
	Vector3 m_vecOrigin{ 0.f, 0.f, 0.f};
	Vector3 m_vecHeadOrigin{ 0.f, 0.f, 0.f };
	Vector3 m_vecNeckOrigin{ 0.f, 0.f, 0.f };
	CBoneArray m_pBoneArray{};
	std::vector<Vector3> m_vecBoneList{};

    // Functions
	bool Update();
	void UpdateStatic();
	void UpdateBone();
	void UpdateHealth();

	bool IsAiming();

	Vector3 GetBonePosition(const int BoneId);
};