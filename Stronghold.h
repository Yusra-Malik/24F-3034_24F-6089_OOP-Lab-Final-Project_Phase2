#ifndef STRONGHOLD_H
#define STRONGHOLD_H

#include <string>
#include <fstream>
using namespace std;

const int totalResources = 5;
const int totalClasses = 6;
class SocialStructure
{
protected:
	string name;
	int population;
	int wealth;
	int power;
public:
	SocialStructure();
	SocialStructure(string n, int p, int w, int po);

	string getName();
	void setName(string n);
	int getPopulation();
	void setPopulation(int p);
	int getWealth();
	void setWealth(int w);
	int getPower();
	void setPower(int po);

	virtual void classInteraction(SocialStructure* other) = 0;
	virtual ~SocialStructure();
};

class Merchants :public SocialStructure
{
public:
	Merchants();
	Merchants(int p);

	void classInteraction(SocialStructure* other);
};

class Peasants :public SocialStructure
{
public:
	Peasants();
	Peasants(int p);

	void classInteraction(SocialStructure* other);
};

class Nobles:public SocialStructure
{
public:
	Nobles();
	Nobles(int p);

	void classInteraction(SocialStructure* other);
};

class Migrants :public SocialStructure
{
public:
	Migrants();
	Migrants(int p);

	void classInteraction(SocialStructure* other);
};

class Scholars :public SocialStructure
{
public:
	Scholars();
	Scholars(int p);

	void classInteraction(SocialStructure* other);
};

class Soldiers :public SocialStructure
{
public:
	Soldiers();
	Soldiers(int p);

	void classInteraction(SocialStructure* other);
};

class Population
{
protected:
	string name;
	int size;
	int happiness;
	int health;
public:
	Population();
	Population(string n, int s);
	void Grow(int shelter, int food, int employment);
	void Shrink(int disease, int warThreat);

	bool checkForRevolt();


	void displayStatus();

	string getName();

	int getSize();
	void setSize(int s);

	int getHealth();
	void setHealth(int h);

	int getHappiness();
	void setHappiness(int hap);

	void saveFile(ofstream& outFile);
	void loadFile(ifstream& inFile);

	virtual ~Population();
};

class PopulationManager
{
private:
	Population** groups;
	int numGroups;

public:
	PopulationManager();
	PopulationManager(int initialGroups);
	PopulationManager(const PopulationManager& other);

	void addGroup(Population* newGroup);
	void simulateYear(int foodSupply, int shelter, int employment, int disease, int war);
	void checkRevolts();
	void displayAll();

	void saveGame(const string& filename);
	void loadGame(const string& filename);
	void logScoreAndResources(const string& logFilename, int resourcesUsed, int totalScore);
	 void cleanUp();

	~PopulationManager();
};


class Military
{
protected:
	string unitName;
	int soldiers;
	int trainingLevel;
	int morale;       
	int corruption;   

public:
	Military();
	Military(string name, int soldiers);

	void recruit(int newSoldiers);                
	void train(int trainingResources);          
	void supply(int foodUnits, int weaponUnits); 
	void pay(int goldAmount);                  
	void simulateBattle(bool victory);            
	void updateCorruption();                       
	void displayStatus();

	void saveToFile(ofstream& outFile);
	void loadFromFile(ifstream& inFile);

	
	string getUnitName();
	int getSoldiers();
	int getTrainingLevel();
	int getMorale();
	int getCorruption();

	virtual ~Military();
};

class MilitaryManager
{
private:
	Military** units; 
	int numUnits;
	int capacity;

public:
	MilitaryManager();
	MilitaryManager(int initialCapacity);
	MilitaryManager(const MilitaryManager& other);

	void addUnit(Military* newUnit);
	void simulateTrainingPhase(int trainingResources);
	void supplyAllUnits(int foodSupply, int weaponSupply);
	void payAllUnits(int totalGold);
	void simulateBattles(bool* battleResults, int numBattles);
	void handleCorruption();
	void displayAllUnits();

	void saveMilitary(const string& filename);
	void loadMilitary(const string& filename);

	~MilitaryManager();
};

class Leader
{
protected:
	string name;
	string leadershipStyle;   
	int militarySupport;
	int economyFocus;
	int freedomFocus;
	int popularity;               
	           

public:
	Leader();
	Leader(string name, string style);

	void displayInfo();
	void improvePopularity(int amount);
	void losePopularity(int amount);
	void strengthenMilitarySupport(int amount);
	void weakenMilitarySupport(int amount);

	string getName();
	string getLeadershipStyle();
	int getMilitarySupport();
	int getEconomyFocus();
	int getFreedomFocus();
	int getPopularity();
	
	

	void saveToFile(ofstream& outFile);
	void loadFromFile(ifstream& inFile);

	virtual ~Leader();
};

class LeadershipSystem
{
private:
	Leader* currentLeader;
	int yearCount;

public:
	LeadershipSystem();
	LeadershipSystem(Leader* initialLeader);
	LeadershipSystem(const LeadershipSystem& other); 

	void conductElection(string newLeaderName, string newStyle);
	void attemptCoup();
	void naturalSuccession(string heirName, string style);

	void simulateYear(); 
	void displayCurrentLeader();

	void saveLeadership(const string& filename);
	void loadLeadership(const string& filename);

	~LeadershipSystem();
};

class Economy
{
private:
	float taxRate;
	float inflationRate;
	int publicMoney;
public:
	Economy();
	void collectTax(int people[]);
	void increasePrices();
	void spendMoney();
	void effectOfWar();
	void showEconomy();
};
class Bank
{
private:
	int totalMoney;
	int totalLoans;
	bool fraud;
public:
	Bank();
	void takeLoan();
	void payLoan();
	void checkMoney();
	void detectFraud();
	void showBank();
};
class Resource
{
public:
	string resourceName[totalResources];
	int resourceAmount[totalResources];
public:
	Resource();
	void collectResource();
	void useResource();
	void tradeResource();
	void showResources();
};
class Event
{
public:
	Event();
	void randomEvent(int people[], int& soldiers, Resource& res, Economy& eco);
	void famine(int people[], Resource& res);
	void war(int& soldiers, Economy& eco);
	void disease(int people[]);
	void weatherDisaster(Resource& res);
	void betrayal(Economy& eco);
};


class AllianceSystem
{
private:
	string* player1Allies;
	string* player2Allies;
	int currentAllianceCount;
	int maxAlliances;
	string allianceLogFile;

public:
	AllianceSystem();

	void formAlliance(const string& player1, const string& player2);
	void breakAlliance(const string& player1, const string& player2);
	void viewCurrentAlliances() const;
	void viewAllianceHistory() const;
	bool isAllied(const string& player1, const string& player2) const;

	~AllianceSystem();
};


class CommunicationSystem
{
private:
	string chatLogFile;

public:
	CommunicationSystem();
	void sendMessage(const string& sender, const string& receiver, const string& message);
	void viewAllMessages() const;
	void viewMessagesFromSender(const string& sender) const;
};




class TradeSystem
{
private:
	string* traders;
	string* resourcesOffered;
	string* goodsRequested;
	string* tradeType;
	int tradeCount;
	int maxTrades;
	string tradeLogFile;

	void resizeIfNeeded();

public:
	TradeSystem();
	~TradeSystem();

	void offerTrade(const string& trader, const string& resource, const string& requestedGood);
	void attemptSmuggle(const string& smuggler, const string& contraband, const string& destination);
	void imposeEmbargo(const string& traderName);
	void viewTradeHistory() const;
};


class Kingdom
{
private:
	string name;
	int armyStrength;
	int resources;
	bool inWar;
public:
	Kingdom(string n, int army, int res);
	string getName();
	int getArmyStrength();
	int getResources();
	void gainResources(int r);
	void loseResources(int r);
	void setWarStatus(bool status);
	bool isInWar();
};

class ConflictSystem
{
public:
	void declareWar(Kingdom* k1, Kingdom* k2);
	void resolveBattle(Kingdom* k1, Kingdom* k2);
	void betrayAlly(Kingdom* betrayer, Kingdom* ally);
};
#endif
