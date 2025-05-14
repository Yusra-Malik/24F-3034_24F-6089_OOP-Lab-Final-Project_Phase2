# 24F-3034_24F-6089_OOP-Lab-Final-Project_Phase2
oop lab final project: stronghold game
Stronghold Project - Module 2: Multiplayer and Diplomacy Engine
Project Overview
The Stronghold Game now enters its second phase with Module 2: Multiplayer and Diplomacy Engine. Building upon the internal kingdom systems developed in Module 1, this module introduces inter-kingdom communication, alliances, trade, betrayal, and warfare. The goal is to simulate dynamic real-time decision-making between multiple kingdoms in a text-based multiplayer strategy simulation using advanced Object-Oriented Programming in C++.
This module adds a new layer of complexity by allowing multiple players (kingdoms) to interact, negotiate, and engage in diplomacy and conflict.
 Purpose
While Module 1 focused on the internal mechanics of a single kingdom, Module 2 expands the simulation to handle player-to-player interactions. Players can now:
•	Form or break alliances
•	Trade or smuggle resources
•	Engage in war or deception
•	Strategically expand or defend territories
 Core Features
Players can experience the following functionalities in Module 2:
 Communication System
"A text-based messaging system enabling negotiation, alliances, deception, and threats"
Allows kingdoms to send and receive text messages during gameplay. These messages can be used to negotiate treaties, propose trades, issue threats, or deceive opponents.
 Alliances and Treaties
"Form, track, and break alliances and diplomatic agreements"
Players can establish formal treaties or temporary alliances. The system logs relationship history, tracks current alliance status, and applies consequences when treaties are broken.
Trade and Smuggling System
"Shared marketplace with legal and illegal (black market) trades"
Kingdoms can exchange resources through a secure trade system. The system also supports smuggling, which involves risks like being caught, leading to penalties or reputation loss.
 Conflict and Betrayal System
"Supports war mechanics, surprise attacks, and betrayal consequences"
Alliances can be broken suddenly, leading to war. The system determines outcomes based on available forces and resources. Betrayals result in morale drops or trust penalties.
Map and Movement System
"Grid-based map to track kingdom zones and proximity"
Implements a simple textual or grid-based map system showing each kingdom’s territory, movement between zones, and proximity for trade or battle.
 Technologies Used
•	C++: Object-oriented design, modular structure
•	File Handling: Chat logs, treaty records, and market history
•	Random Number Generation: Simulating risk in smuggling and surprise attacks
•	Grid Systems: Representing map and movement
 Project Division
Yusra's Contributions:
1.	Communication Class
o	Developed the system for text-based messages between kingdoms.
2.	Alliance System Class
o	Implemented logic for forming, tracking, and breaking treaties.
3.	Map System Class
o	Created the textual/grid map representing control zones and kingdom proximity.
Nadia Atiq's Contributions:
1.	Trade System Class
o	Developed the marketplace and smuggling logic, including transaction tracking.
2.	Conflict System Class
o	Built the mechanics for war, betrayal, penalties, and combat resolution.
 Code Explanation
main() Function
The main function integrates all classes and simulates multiplayer interaction between kingdoms. It allows each player to:
•	View messages and respond
•	Propose or break alliances
•	Trade or smuggle resources
•	Declare or respond to war
•	Move across the grid-based map
Multiplayer Session Log
The system maintains logs for:
•	Chat communications
•	Treaty agreements and changes
•	Trade transactions (legal & illegal)
•	War outcomes and player movements


