#include "CItem.h"
#include <algorithm>
#include <optional>
#include "ItemList.h"

// Thank you ChatGPT!
std::optional<tarkovItem> findDataById(const std::vector<tarkovItem>& list, const std::string& targetId) {
	auto it = std::find_if(list.begin(), list.end(), [&](const tarkovItem& d) {
		return d.id.find(targetId) != std::string::npos;
		});

	if (it != list.end())
		return *it;
	else
		return std::nullopt;
}

bool CItem::GetAddress(uintptr_t& ptr)
{
	address = ptr;
	return address == NULL ? false : true;
}

bool CItem::Update()
{
	// Position
	uintptr_t TransformInternal = m.ReadChain(address, { 0x10, 0x30, 0x30, 0x8, 0x28, 0x10 });
	m_vecOrigin = GetTransformPosition(TransformInternal);

	if (Vec3_Empty(m_vecOrigin))
		return false;
	
	// ClassName
	uintptr_t nameAddr = m.ReadChain(address, { 0x0, 0x0, 0x48 });
	std::string className = m.ReadString(nameAddr, 64);

	// ƒRƒ“ƒeƒi/Ž€‘Ì‚Å‚Í‚È‚©‚Á‚½‚ç
	if (className.compare("ObservedCorpse") && className.compare("Corpse"))
	{
		// ID
		char ItemID[64]{};
		uintptr_t pBsgId = m.ReadChain(address, { 0x10, 0x28, 0xB8, 0x40, 0x60 });
		const int length = m.Read<int>(pBsgId + 0x10);

		if (length > 0)
		{
			for (int j = 0; j < length; j++)
				ItemID[j] = m.Read<char>(pBsgId + 0x18 + (j * 0x2));

			auto result = findDataById(itemList, ItemID);
			if (result)
			{
				if (result->price > g.g_ESP_ItemPrice)
				{
					m_iMarketPrice = result->price;
					m_szItemName = result->name;
				}
			}
		}
	}
	else
	{
		m_bIsCorpse = true;
	}

	return true;
}