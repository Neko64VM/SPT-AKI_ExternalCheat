#pragma once
#include <iostream>
#include <SimpleMath.h>
using namespace DirectX::SimpleMath;

struct Matrix34
{
	Vector4 vec0;
	Vector4 vec1;
	Vector4 vec2;
};

struct UnityList
{
	char padding[0x10]{};
	uintptr_t list_address{ 0 }; // 0x10
	int count{ 0 }; // 0x18
};

struct BaseObject
{
    uint64_t previousObjectLink;
    uint64_t nextObjectLink;
    uint64_t object;
};
struct GameObjectManager
{
    uint64_t lastTaggedObject;
    uint64_t taggedObjects;
    uint64_t lastActiveObject;
    uint64_t activeObjects;
    uint64_t LastActiveNode;
    uint64_t ActiveNodes;
};

struct TransformAccessReadOnly
{
	uintptr_t	pTransformData;
    int			index;
};

struct TransformData
{
    uintptr_t pTransformArray;
	uintptr_t pTransformIndices;
};

struct Camera
{
    uint64_t list;
    uint64_t min;
    uint64_t count;
    uint64_t max;
};

enum ExfilStatus : int
{
	CLOSE = 1,
	NOTREADY = 2,
	OPEN = 4,
	READY = 6
};

enum PlayerSide : int
{
	SIDE_USEC = 1,
	SIDE_BEAR = 2,
	SIDE_SCAV = 4
};

enum CGameBoneID : int
{
	BONE_ORIGIN = 0,
	BONE_PELVIS = 14,
	BONE_LEFT_THIGH = 16,
	BONE_LEFT_CALF = 17,
	BONE_LEFT_FOOT = 18,
	BONE_LEFT_TOE = 19,
	BONE_RIGHT_THIGH = 21,
	BONE_RIGHT_CALF = 22,
	BONE_RIGHT_FOOT = 23,
	BONE_RIGHT_TOE = 24,
	BONE_SPINE_1 = 29,
	BONE_SPINE_2 = 36,
	BONE_SPINE_3 = 37,
	BONE_LEFT_COLLARBONE = 89,
	BONE_LEFT_UPPERARM = 90,
	BONE_LEFT_FOREARM = 92,
	BONE_LEFT_PALM = 94,
	BONE_RIGHT_COLLARBONE = 110,
	BONE_RIGHT_UPPERARM = 111,
	BONE_RIGHT_FOREARM = 113,
	BONE_RIGHT_PALM = 115,
	BONE_NECK = 132,
	BONE_HEAD = 133
};

enum SkeletonBoneID : int
{
	CPelvis = 0,
	CLeftThigh = 1,
	CLeftFoot = 2,
	CRightThigh = 3,
	CRightFoot = 4,
	CLeftForearm = 5,
	CLeftPalm = 6,
	CRightForearm = 7,
	CRightPalm = 8
};

// SPT
enum WildSpanwType : int
{
	// Scav
	SNIPER_SCAV = 0,
	SCAV = 1,

	// Customs
	RESHALA_BOSS = 3,
	RESHALA_FOLLOW = 5,

	// InterChange
	KILLA_BOSS = 6,

	// Woods
	SHTURMAN_BOSS = 7,
	SHTURMAN_FOLLOW = 8,

	// Global
	RAIDER_SCAV = 9,

	// Reserve
	GLUKHAR_BOSS = 11,
	GLUKHAR_FOLLOW_01 = 12,
	GLUKHAR_FOLLOW_02 = 13,
	GLUKHAR_FOLLOW_03 = 14,

	// Shoreline
	SANITOR_FOLLOW = 16,
	SANITOR_BOSS = 17,

	// Global
	NORMAL_SCAV = 19, // è≠Çµã≠âªÇ≥ÇÍÇΩScav (?????
	CULTIST_01_SCAV = 20,
	CULTIST_02_SCAV = 21,

	// Factory
	TAGILLA_BOSS = 22,

	// Lighthouse
	ROGUE_SCAV = 24,

	// Global
	KNIGHT_SCAV = 26,
	BIGPIPE_SCAV = 27,
	BRIDEYE_SCAV = 28,

	// Lighthouse
	ZRYACHIY_BOSS = 29,
	ZRYACHIY_FOLLOW = 30,

	// Street of Tarkov
	KABAN_BOSS = 32,
	KABAN_FOLLOW_0 = 33,

	// Global (?
	BLOODHOUND_SCAV = 35,

	KABAN_FOLLOW_1 = 36,

	KABAN_FOLLOW_2 = 41,
	KABAN_FOLLOW_3 = 42,

	KOLLONTAY_BOSS = 43,
	KOLLONTAY_FOLLOW_01 = 44,
	KOLLONTAY_FOLLOW_02 = 45,

	// Global
	BTR_VEHICLE = 46,
	SCAV_PARTISAN,

	// OLD
	PMC_BEAR_PvE = 49,
	PMC_USEC_PvE = 50,

	// Global (?
	PMC_BEAR_NEW = 51,
	PMC_USEC_NEW = 52
};