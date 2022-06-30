#include "GameData.h"
#include <fstream>
#include <filesystem>

GameData::GameData() :
	filePath_(L""),
	fuelUpgrade_(0, 8, 10, 2.0f),
	drillUpgrade_(0, 8, 25, 2.0f),
	speedUpgrade_(0, 8, 50, 2.0f),
	totalMoney_(0),
	maxDepth_(0),
	lastProfit_(0),
	lastMaxDepth_(0)
{}

void GameData::init(const std::wstring &dataFilePath, const std::wstring &dataFileName)
{
	filePath_ = dataFilePath;
	fileName_ = dataFileName;

	if (!this->loadSave_())
	{
		this->createNewSave_();
		this->loadSave_();
	}
}

void GameData::save()
{
	std::ofstream out(filePath_ + fileName_, std::ios_base::out | std::ios_base::binary);

	out.write((char *)&fuelUpgrade_, sizeof(Upgrade));
	out.write((char *)&drillUpgrade_, sizeof(Upgrade));
	out.write((char *)&speedUpgrade_, sizeof(Upgrade));
	out.write((char *)&totalMoney_, sizeof(uint64_t));
	out.write((char *)&maxDepth_, sizeof(uint8_t));
	out.write((char *)&lastProfit_, sizeof(uint64_t));
	out.write((char *)&lastMaxDepth_, sizeof(uint8_t));

	out.close();
}

void GameData::addToTotalMoney(uint64_t money)
{
	totalMoney_ += money;
}

void GameData::setMaxDepth(uint8_t maxDepth)
{
	maxDepth_ = maxDepth;
}

void GameData::setLastProfit(uint64_t lastProfit)
{
	lastProfit_ = lastProfit;
}

void GameData::setLastMaxDepth(uint8_t lastMaxDepth)
{
	lastMaxDepth_ = lastMaxDepth;
}

Upgrade &GameData::getFuelUpgradeRef()
{
	return fuelUpgrade_;
}

Upgrade &GameData::getDrillUpgradeRef()
{
	return drillUpgrade_;
}

Upgrade &GameData::getSpeedUpgradeRef()
{
	return speedUpgrade_;
}

const Upgrade &GameData::getFuelUpgrade() const
{
	return fuelUpgrade_;
}

const Upgrade &GameData::getDrillUpgrade() const
{
	return drillUpgrade_;
}

const Upgrade &GameData::getSpeedUpgrade() const
{
	return speedUpgrade_;
}

uint64_t &GameData::getTotalMoneyRef()
{
	return totalMoney_;
}

uint64_t GameData::getTotalMoney() const
{
	return totalMoney_;
}

uint8_t GameData::getMaxDepth() const
{
	return maxDepth_;
}

uint64_t GameData::getLastProfit() const
{
	return lastProfit_;
}

uint8_t GameData::getLastMaxDepth() const
{
	return lastMaxDepth_;
}

void GameData::reset_()
{
	fuelUpgrade_ = Upgrade(0, 8, 10, 2.0f);
	drillUpgrade_ = Upgrade(0, 8, 25, 2.0f);
	speedUpgrade_ = Upgrade(0, 8, 50, 2.0f);
	totalMoney_ = 0;
	maxDepth_ = 0;
	lastProfit_ = 0;
	lastMaxDepth_ = 0;
}

bool GameData::loadSave_()
{
	std::ifstream in(filePath_ + fileName_, std::ios_base::in | std::ios_base::binary);

	if (!in.is_open())
	{
		return false;
	}

	in.read((char *)&fuelUpgrade_, sizeof(Upgrade));
	in.read((char *)&drillUpgrade_, sizeof(Upgrade));
	in.read((char *)&speedUpgrade_, sizeof(Upgrade));
	in.read((char *)&totalMoney_, sizeof(uint64_t));
	in.read((char *)&maxDepth_, sizeof(uint8_t));
	in.read((char *)&lastProfit_, sizeof(uint64_t));
	in.read((char *)&lastMaxDepth_, sizeof(uint8_t));

	in.close();

	return true;
}

void GameData::createNewSave_()
{
	this->reset_();

	std::filesystem::create_directories(filePath_);

	this->save();
}