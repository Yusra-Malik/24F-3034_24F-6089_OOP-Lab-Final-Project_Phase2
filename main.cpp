#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
#include "Stronghold.h"


using namespace std;

int main()
{
    srand(static_cast<unsigned int>(time(nullptr)));

    string kingdomName;
    string leaderName;
    string leaderStyle;
    Leader* leader = nullptr;

    int menuChoice;
    AllianceSystem allianceSystem;
    CommunicationSystem communicationSystem;
    TradeSystem tradeSystem;
    ConflictSystem conflictSystem;

   Kingdom** kingdoms = nullptr;
    int kingdomCount = 0;
    int kingdomCapacity = 0;

    while (true)
    {
        cout << "===== Welcome to Stronghold Simulation =====\n";
        cout << "1. Start New Game\n2. Load Game\nEnter choice: ";
        cin >> menuChoice;
        cin.ignore();

        switch (menuChoice)
        {
        case 1:
            cout << "\nEnter your Kingdom Name: ";
            getline(cin, kingdomName);

            cout << "Enter your Leader's Name: ";
            getline(cin, leaderName);

            cout << "Enter your Leadership Style (e.g., 'Warlord', 'Diplomatic', 'Tyrant'): ";
            getline(cin, leaderStyle);

            leader = new Leader(leaderName, leaderStyle);
            cout << "\nKingdom \"" << kingdomName << "\" founded under the rule of " << leaderName << "!\n";

            
            kingdomCapacity = 4;
            kingdoms = new Kingdom * [kingdomCapacity];
            kingdomCount = 0;

            
            kingdoms[kingdomCount++] = new Kingdom(kingdomName, 100, 500);

            
            kingdoms[kingdomCount++] = new Kingdom("Northern Hills", 80, 400);
            kingdoms[kingdomCount++] = new Kingdom("Eastern States", 120, 600);
            kingdoms[kingdomCount++] = new Kingdom("Western Lands", 90, 450);
            break;

        case 2:
            cout << "Loading saved game\n";
            leader = new Leader();
            {
                ifstream inFile("game_save.txt");
                if (inFile.good())
                {
                    leader->loadFromFile(inFile);
                    inFile.close();
                    cout << "game loaded successfully!\n";

                    
                    kingdomCapacity = 4; 
                    kingdoms = new Kingdom * [kingdomCapacity];
                    kingdomCount = 0;

                    kingdoms[kingdomCount++] = new Kingdom(kingdomName, 100, 500);
                    kingdoms[kingdomCount++] = new Kingdom("Northern Hills", 80, 400);
                    kingdoms[kingdomCount++] = new Kingdom("Eastern States", 120, 600);
                    kingdoms[kingdomCount++] = new Kingdom("Western Land", 90, 450);
                }
                else
                {
                    cerr << "Failed to load saved data. Starting a new game instead.\n";
                    delete leader;
                    leader = new Leader("Default", "Diplomatic");
                    kingdomName = "Default Kingdom";

                   
                    kingdomCapacity = 4;
                    kingdoms = new Kingdom * [kingdomCapacity];
                    kingdomCount = 0;

                    kingdoms[kingdomCount++] = new Kingdom(kingdomName, 100, 500);
                    kingdoms[kingdomCount++] = new Kingdom("Northern Hills", 80, 400);
                    kingdoms[kingdomCount++] = new Kingdom("Eastern States", 120, 600);
                    kingdoms[kingdomCount++] = new Kingdom("Western Land", 90, 450);
                }
            }
            break;

        default:
            cout << "Invalid selection. Please try again.\n\n";
            continue;
        }
        break;
    }

   
    LeadershipSystem government(leader);
    Economy eco;
    Bank bank;
    Resource res;
    Event eventSystem;
    Military army("Guards", 100);

    PopulationManager popManager;
    popManager.addGroup(new Population("Peasants", 150));
    popManager.addGroup(new Population("Merchants", 80));
    popManager.addGroup(new Population("Nobles", 30));
    popManager.addGroup(new Population("Migrants", 40));
    popManager.addGroup(new Population("Scholars", 20));

    int people[totalClasses] = { 100, 50, 20 };
    int soldiers = 100;

    int choice;
    while (true)
    {
        cout << "\n===== Kingdom of " << kingdomName << " Menu =====\n";
        cout << "1. View Economy\n2. Collect Tax\n3. Spend Money\n4. Bank Menu\n";
        cout << "5. Resource Menu\n6. Trigger Random Event\n7. Military Info\n";
        cout << "8. Show Leader\n9. Save Leader\n10. Population Menu\n";
        cout << "11. Alliance Menu\n12. Communication Menu\n13. Trade Menu\n14. Kingdom Relations\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            eco.showEconomy();
            break;
        case 2:
            eco.collectTax(people);
            break;
        case 3:
            eco.spendMoney();
            break;
        case 4:
        {
            int bchoice;
            cout << "1. Take Loan\n2. Pay Loan\n3. Bank Status\n4. Detect Fraud\nChoice: ";
            cin >> bchoice;
            switch (bchoice)
            {
            case 1:
                bank.takeLoan();
                break;
            case 2:
                bank.payLoan();
                break;
            case 3:
                bank.showBank();
                break;
            case 4:
                bank.detectFraud();
                break;
            default:
                cout << "Invalid bank option.\n";
            }
            break;
        }
        case 5:
        {
            int rchoice;
            cout << "1. Collect Resource\n2. Use Resource\n3. Trade Resource\n4. Show Resources\nChoice: ";
            cin >> rchoice;
            switch (rchoice)
            {
            case 1:
                res.collectResource();
                break;
            case 2:
                res.useResource();
                break;
            case 3:
                res.tradeResource();
                break;
            case 4:
                res.showResources();
                break;
            default:
                cout << "Invalid resource option.\n";
            }
            break;
        }
        case 6:
        {
            int eChoice;
            cout << "\n--- Chaos & Events Menu ---\n";
            cout << "1. Trigger Random Event\n";
            cout << "2. Trigger Famine\n";
            cout << "3. Trigger Disease\n";
            cout << "4. Trigger War\n";
            cout << "5. Trigger Weather Disaster\n";
            cout << "6. Trigger Betrayal\n";
            cout << "Enter your choice: ";
            cin >> eChoice;

            switch (eChoice)
            {
            case 1:
                eventSystem.randomEvent(people, soldiers, res, eco);
                break;
            case 2:
                eventSystem.famine(people, res);
                cout << "Famine has affected the land!\n";
                break;
            case 3:
                eventSystem.disease(people);
                cout << "Disease has spread through the population!\n";
                break;
            case 4:
                eventSystem.war(soldiers, eco);
                cout << "War has broken out!\n";
                break;
            case 5:
                eventSystem.weatherDisaster(res);
                cout << "A weather disaster has struck!\n";
                break;
            case 6:
                eventSystem.betrayal(eco);
                cout << "Betrayal from within has occurred!\n";
                break;
            default:
                cout << "Invalid event choice.\n";
            }
            break;
        }
        case 7:
        {
            int mchoice;
            cout << "\n--- Military Menu ---\n";
            cout << "1. Recruit Soldiers\n";
            cout << "2. Train Troops\n";
            cout << "3. Supply Units\n";
            cout << "4. Pay Soldiers\n";
            cout << "5. Simulate Battle\n";
            cout << "6. Update Corruption\n";
            cout << "7. Show Military Status\n";
            cout << "Enter your choice: ";
            cin >> mchoice;

            switch (mchoice)
            {
            case 1:
            {
                int newSoldiers;
                cout << "Enter number of soldiers to recruit: ";
                cin >> newSoldiers;
                army.recruit(newSoldiers);
                cout << newSoldiers << " soldiers recruited.\n";
                break;
            }
            case 2:
            {
                int resources;
                cout << "Enter training resources: ";
                cin >> resources;
                army.train(resources);
                cout << "Training completed.\n";
                break;
            }
            case 3:
            {
                int food, weapons;
                cout << "Enter food units: ";
                cin >> food;
                cout << "Enter weapon units: ";
                cin >> weapons;
                army.supply(food, weapons);
                cout << "Units supplied.\n";
                break;
            }
            case 4: {
                int gold;
                cout << "Enter gold amount to pay soldiers: ";
                cin >> gold;
                army.pay(gold);
                cout << "Soldiers paid.\n";
                break;
            }
            case 5: {
                int outcome;
                cout << "Was the battle a victory? (1 = Yes, 0 = No): ";
                cin >> outcome;
                army.simulateBattle(outcome == 1);
                cout << "Battle simulation complete.\n";
                break;
            }
            case 6:
                army.updateCorruption();
                cout << "Corruption level updated.\n";
                break;
            case 7:
                army.displayStatus();
                break;
            default:
                cout << "Invalid military option.\n";
            }
            break;
        }
        case 8:
            government.displayCurrentLeader();
            break;
        case 9:
            cout << "Leader saved successfully.\n";
            break;
        case 10:
        {
            int pchoice;
            cout << "\n--- Population Menu ---\n";
            cout << "1. Display Population\n";
            cout << "2. Simulate Growth/Shrinkage\n";
            cout << "3. Check Revolts\n";
            cout << "Enter choice: ";
            cin >> pchoice;

            switch (pchoice)
            {
            case 1:
                popManager.displayAll();
                break;
            case 2: {
                int food, shelter, jobs, disease, war;
                cout << "Enter food supply: ";
                cin >> food;
                cout << "Enter shelter provided: ";
                cin >> shelter;
                cout << "Enter employment available: ";
                cin >> jobs;
                cout << "Enter disease level: ";
                cin >> disease;
                cout << "Enter war threat: ";
                cin >> war;
                popManager.simulateYear(food, shelter, jobs, disease, war);
                cout << "Population updated.\n";
                break;
            }
            case 3:
                popManager.checkRevolts();
                break;
            default:
                cout << "Invalid population option.\n";
            }
            break;
        }
        
        case 11:
        {
            int aChoice;
            cout << "\n--- Alliance Menu ---\n";
            cout << "1. Form Alliance\n";
            cout << "2. Break Alliance\n";
            cout << "3. View Current Alliances\n";
            cout << "4. View Alliance History\n";
            cout << "5. Check Alliance Status\n";
            cout << "Enter choice: ";
            cin >> aChoice;
            cin.ignore();

            switch (aChoice)
            {
            case 1:
            {
                string kingdom1, kingdom2;
                cout << "Enter first kingdom: ";
                getline(cin, kingdom1);
                cout << "Enter second kingdom: ";
                getline(cin, kingdom2);
                allianceSystem.formAlliance(kingdom1, kingdom2);
                break;
            }
            case 2:
            {
                string kingdom1, kingdom2;
                cout << "Enter first kingdom: ";
                getline(cin, kingdom1);
                cout << "Enter second kingdom: ";
                getline(cin, kingdom2);
                allianceSystem.breakAlliance(kingdom1, kingdom2);
                break;
            }
            case 3:
                allianceSystem.viewCurrentAlliances();
                break;
            case 4:
                allianceSystem.viewAllianceHistory();
                break;
            case 5:
            {
                string kingdom1, kingdom2;
                cout << "Enter first kingdom: ";
                getline(cin, kingdom1);
                cout << "Enter second kingdom: ";
                getline(cin, kingdom2);
                if (allianceSystem.isAllied(kingdom1, kingdom2)) {
                    cout << kingdom1 << " and " << kingdom2 << " are allies.\n";
                }
                else {
                    cout << kingdom1 << " and " << kingdom2 << " are not allies.\n";
                }
                break;
            }
            default:
                cout << "Invalid alliance option.\n";
            }
            break;
        }
        case 12:
        {
            int cChoice;
            cout << "\n--- Communication Menu ---\n";
            cout << "1. Send Message\n";
            cout << "2. View All Messages\n";
            cout << "3. View Messages From Sender\n";
            cout << "Enter choice: ";
            cin >> cChoice;
            cin.ignore();

            switch (cChoice)
            {
            case 1:
            {
                string sender, receiver, message;
                cout << "Enter sender: ";
                getline(cin, sender);
                cout << "Enter receiver: ";
                getline(cin, receiver);
                cout << "Enter message: ";
                getline(cin, message);
                communicationSystem.sendMessage(sender, receiver, message);
                break;
            }
            case 2:
                communicationSystem.viewAllMessages();
                break;
            case 3:
            {
                string sender;
                cout << "Enter sender to filter by: ";
                getline(cin, sender);
                communicationSystem.viewMessagesFromSender(sender);
                break;
            }
            default:
                cout << "Invalid communication option.\n";
            }
            break;
        }
        case 13:
        {
            int tChoice;
            cout << "\n--- Trade Menu ---\n";
            cout << "1. Offer Trade\n";
            cout << "2. Attempt Smuggling\n";
            cout << "3. Impose Embargo\n";
            cout << "4. View Trade History\n";
            cout << "Enter choice: ";
            cin >> tChoice;
            cin.ignore();

            switch (tChoice)
            {
            case 1:
            {
                string trader, resource, requestedGood;
                cout << "Enter trader: ";
                getline(cin, trader);
                cout << "Enter resource to offer: ";
                getline(cin, resource);
                cout << "Enter requested good: ";
                getline(cin, requestedGood);
                tradeSystem.offerTrade(trader, resource, requestedGood);
                break;
            }
            case 2:
            {
                string smuggler, contraband, destination;
                cout << "Enter smuggler: ";
                getline(cin, smuggler);
                cout << "Enter contraband: ";
                getline(cin, contraband);
                cout << "Enter destination: ";
                getline(cin, destination);
                tradeSystem.attemptSmuggle(smuggler, contraband, destination);
                break;
            }
            case 3:
            {
                string traderName;
                cout << "Enter trader to embargo: ";
                getline(cin, traderName);
                tradeSystem.imposeEmbargo(traderName);
                break;
            }
            case 4:
                tradeSystem.viewTradeHistory();
                break;
            default:
                cout << "Invalid trade option.\n";
            }
            break;
        }
        case 14:
        {
            int kChoice;
            cout << "\n--- Kingdom Relations Menu ---\n";
            cout << "1. View All Kingdoms\n";
            cout << "2. Declare War\n";
            cout << "3. Resolve Battle\n";
            cout << "4. Betray Ally\n";
            cout << "Enter choice: ";
            cin >> kChoice;
            cin.ignore();

            switch (kChoice)
            {
            case 1:
                cout << "--- List of Kingdoms ---\n";
                for (int i = 0; i < kingdomCount; i++) {
                    cout << i << ". " << kingdoms[i]->getName()
                        << " (Army: " << kingdoms[i]->getArmyStrength()
                        << ", Resources: " << kingdoms[i]->getResources()
                        << ", War Status: " << (kingdoms[i]->isInWar() ? "At War" : "At Peace")
                        << ")\n";
                }
                break;
            case 2:
            {
                int k1Index, k2Index;
                cout << "Enter index of first kingdom (attacker): ";
                cin >> k1Index;
                cout << "Enter index of second kingdom (defender): ";
                cin >> k2Index;

                if (k1Index >= 0 && k1Index < kingdomCount &&
                    k2Index >= 0 && k2Index < kingdomCount &&
                    k1Index != k2Index) {
                    conflictSystem.declareWar(kingdoms[k1Index], kingdoms[k2Index]);
                }
                else {
                    cout << "Invalid kingdom indices.\n";
                }
                break;
            }
            case 3:
            {
                int k1Index, k2Index;
                cout << "Enter index of first kingdom: ";
                cin >> k1Index;
                cout << "Enter index of second kingdom: ";
                cin >> k2Index;

                if (k1Index >= 0 && k1Index < kingdomCount &&
                    k2Index >= 0 && k2Index < kingdomCount &&
                    k1Index != k2Index) {
                    conflictSystem.resolveBattle(kingdoms[k1Index], kingdoms[k2Index]);
                }
                else {
                    cout << "Invalid kingdom indices.\n";
                }
                break;
            }
            case 4:
            {
                int betrayerIndex, allyIndex;
                cout << "Enter index of betrayer kingdom: ";
                cin >> betrayerIndex;
                cout << "Enter index of ally kingdom: ";
                cin >> allyIndex;

                if (betrayerIndex >= 0 && betrayerIndex < kingdomCount &&
                    allyIndex >= 0 && allyIndex < kingdomCount &&
                    betrayerIndex != allyIndex) 
                {
                
                    if (allianceSystem.isAllied(kingdoms[betrayerIndex]->getName(), kingdoms[allyIndex]->getName())) 
                    {
                        conflictSystem.betrayAlly(kingdoms[betrayerIndex], kingdoms[allyIndex]);
                        allianceSystem.breakAlliance(kingdoms[betrayerIndex]->getName(), kingdoms[allyIndex]->getName());
                    }
                    else 
                    {
                        cout << "These kingdoms are not allies.\n";
                    }
                }
                else 
                {
                    cout << "Invalid kingdom indices.\n";
                }
                break;
            }
            default:
                cout << "Invalid kingdom relations option.\n";
            }
            break;
        }
        case 0:
            cout << "Saving game...\n";
            {
                ofstream outFile("game_save.txt");
                if (outFile.is_open())
                {
                    leader->saveToFile(outFile);
                    outFile.close();
                    cout << "Game saved successfully!\n";
                }
                else
                {
                    cerr << "Failed to save game.\n";
                }
            }

            
            for (int i = 0; i < kingdomCount; i++) 
            {
                delete kingdoms[i];
            }
            delete[] kingdoms;

            cout << "Exiting game. Goodbye, " << leader->getName() << " of " << kingdomName << ".\n";
            return 0;
        default:
            cout << "Invalid choice.\n";
        }
    }
}