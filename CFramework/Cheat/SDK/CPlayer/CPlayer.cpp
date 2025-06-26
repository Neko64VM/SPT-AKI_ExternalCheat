#include "CPlayer.h"

std::vector<int> PlayerBoneList{ BONE_PELVIS, BONE_LEFT_THIGH, BONE_LEFT_FOOT, BONE_RIGHT_THIGH, BONE_RIGHT_FOOT, BONE_LEFT_FOREARM, BONE_LEFT_PALM, BONE_RIGHT_FOREARM, BONE_RIGHT_PALM };

bool CPlayer::Update()
{
	// Position
	m_vecOrigin = GetBonePosition(BONE_ORIGIN);

	if (Vec3_Empty(m_vecOrigin))
		return false;

	return true;
}

void CPlayer::UpdateStatic()
{
	// Health
	uintptr_t m_pHealthController = m.Read<uintptr_t>(m_address + offset::Player::pHealthController);	// HealthController
	uintptr_t m_pHealthBody = m.Read<uintptr_t>(m_pHealthController + 0x68);
	m_pBodyController = m.Read<uintptr_t>(m_pHealthBody + 0x18);

	// Bone
	uintptr_t boneMatrix = m.ReadChain(m_address, { offset::Player::pPlayerBody, 0x30, 0x30, 0x10 });
	m_pBoneArray = m.Read<CBoneArray>(boneMatrix + 0x20);

	// Other pointer
	m_pProfile = m.Read<uintptr_t>(m_address + offset::Player::pProfile);
	m_pInfo = m.Read<uintptr_t>(m_pProfile + 0x40);
	m_pSetting = m.Read<uintptr_t>(m_pInfo + 0x50);

	m_pWeaponAnimation = m.Read<uintptr_t>(m_address + offset::Player::pWeaponAnimation);

	// Player data
	m_iSpawnType = m.Read<int>(m_pSetting + 0x10); // SpawnType
}

void CPlayer::UpdateHealth()
{
	float h{ 0 };
	float max{ 0 };

	for (int j = 0; j < 7; j++)
	{
		uintptr_t body_part = m.Read<uintptr_t>(m_pBodyController + 0x30 + (j * 0x18));
		uintptr_t health_container = m.Read<uintptr_t>(body_part + 0x10);
		h += m.Read<float>(health_container + 0x10);
		max += m.Read<float>(health_container + 0x14);
	}

	m_fHealth = h;
	m_fHealthMax = max;
}

void CPlayer::UpdateBone()
{
	m_vecHeadOrigin = GetBonePosition(BONE_HEAD);
	m_vecNeckOrigin = GetBonePosition(BONE_NECK);

	if (g.g_ESP_Skeleton)
	{
		for (auto& id : PlayerBoneList)
		{
			Vector3 bone = GetBonePosition(id);

			if (Vec3_Empty(bone)) {
				m_vecBoneList.clear();
				break;
			}

			m_vecBoneList.push_back(bone);
		}
	}
}

bool CPlayer::IsAiming()
{
	return m.Read<bool>(m_pWeaponAnimation + offset::WeaponAnimations::isAiming);
}

Vector3 CPlayer::GetBonePosition(const int BoneId)
{
	uintptr_t TransformPtr = m.Read<uintptr_t>(m_pBoneArray.address[BoneId] + 0x10);

	return GetTransformPosition(TransformPtr);
}