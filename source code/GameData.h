#pragma once

#include "Upgrade.h"
#include <string>

class GameData
{
public:
	GameData();

	void init(const std::wstring &dataFilePath, const std::wstring &dataFileName);

	void save();

	void addToTotalMoney(uint64_t money);
	void setMaxDepth(uint8_t maxDepth);
	void setLastProfit(uint64_t lastProfit);
	void setLastMaxDepth(uint8_t lastMaxDepth);

	Upgrade &getFuelUpgradeRef();
	Upgrade &getDrillUpgradeRef();
	Upgrade &getSpeedUpgradeRef();

	uint64_t &getTotalMoneyRef();

	const Upgrade &getFuelUpgrade() const;
	const Upgrade &getDrillUpgrade() const;
	const Upgrade &getSpeedUpgrade() const;

	uint64_t getTotalMoney() const;
	uint8_t getMaxDepth() const;
	uint64_t getLastProfit() const;
	uint8_t getLastMaxDepth() const;
private:
	std::wstring filePath_;
	std::wstring fileName_;

	Upgrade fuelUpgrade_;
	Upgrade drillUpgrade_;
	Upgrade speedUpgrade_;

	uint64_t totalMoney_;
	uint8_t maxDepth_;

	uint64_t lastProfit_;
	uint8_t lastMaxDepth_;

	void reset_();
	bool loadSave_();
	void createNewSave_();
};