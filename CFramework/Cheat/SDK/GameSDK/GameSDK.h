#pragma once
#include "Offset.h"
#include "Struct.h"
#include "../../../Framework/Memory/Memory.h"
#include "../../../Framework/Config/Config.h"

class CGame
{
private:
	GameObjectManager m_objGameObjectManager{};
	Camera m_pAllCamera{ 0 };
public:
	uintptr_t m_pGameWorld{ 0 };
	uintptr_t m_pLocalGameWorld{ 0 };
	uintptr_t m_pFpsCamera{ 0 };
	Matrix	  m_mxViewMatrix{};

	bool InitAddress();

	bool IsInRaid();

	bool Update();
	bool UpdateCamera();
	Matrix GetViewMatrix();
};

extern bool Vec2_Empty(const Vector2& value);
extern bool Vec3_Empty(const Vector3& value);
extern float GetDistance(Vector3 value1, Vector3 value2);
extern Vector3 GetTransformPosition(uintptr_t& transform);
extern bool WorldToScreen(Matrix ViewMatrix, const Vector2& GameSize, Vector3& vIn, Vector2& vOut);
extern uintptr_t GetObjectFromList(uintptr_t listPtr, uintptr_t lastObjectPtr, const char* objectName);