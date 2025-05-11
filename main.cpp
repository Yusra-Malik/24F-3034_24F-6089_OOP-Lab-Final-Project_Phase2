#include "Stronghold.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main()
{
    srand(static_cast<unsigned int>(time(nullptr)));

    string kingdomName;
    string leaderName;
    string leaderStyle;
    Leader* leader = nullptr;

    int menuChoice;

   
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
                }
                else
                {
                    cerr << "Failed to load saved data. Starting a new game instead.\n";
                    delete leader;
                    leader = new Leader("Default", "Diplomatic");
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
        cout << "8. Show Leader\n9. Save Leader\n10. Population Menu\n0. Exit\n";
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
            switch (rchoice) {
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
            cout << "Exiting game. Goodbye, " << leader->getName() << " of " << kingdomName << ".\n";
            return 0;
        default:
            cout << "Invalid choice.\n";
        }
    }
}


