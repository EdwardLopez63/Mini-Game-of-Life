/* 
The Mini Game of Life Program







MAP LAYOUT
STOP SPACE-- Player Automatically stops on that space no matter how many numbers they rolled. They select a choice based on the options and the next player spins. NO DOUBLE SPINS.
STOP INDEX LOCATION NUMBERS    5 = College ___ 17 = Marriage ___   25 = Continue/Family ___ 41 = Safe/ Risky
RETIRE INDEX LOCATION		57 = Retire

Created By Edward Lopez 
Last modified 7/16/2017
*/

#include <iostream>
#include <string>
#include <iomanip>
#include <ctime>
#include <cstdlib>

using namespace std;

// USED TO CALCULATE END GAME STATS
int OverallValue(int housePrice, int numKids, int actionCards, int money) {					
	int totalHouse = housePrice * 2;
	int totalKid = numKids * 50;
	int totalAction = actionCards * 100;
	int totalMoney = money;

	int totalValue = totalHouse + totalKid + totalAction + totalMoney;
	return totalValue;
}


int main() {
	srand((int)time(0));																		// Random Generator

	/* Overall Game Variables */
	bool gameState = true;																		// controls game loop
	string userInput;																			// stores values that user inputs
	int computerInput;																			// COMPUTER uses this variable to store values

	string careerName[5] = { "Chef", "Race Car Driver", "Singer", "Inventor", "Actor" };		// Career titles. Parallel arrays.
	int careerWage[5] = { 50,60,70,90,100 };													// Wages of careerName

	string collegeName[5] = { "Fashion Designer", "Scientist", "Vet", "Lawyer", "Doctor" };		// College career titles. 
	int collegeWage[5] = { 80,90,100,120,130 };													// Wages of College Careers

	string houseName[5] = { "Studio Apartment", "Houseboat","Farmhouse","Dream Villa","City Penthouse" };
	int housePrice[5] = { 100,200,300,400,600 };

	string actionName[10] = { "Gambled on a losing bet. Lose 50k.", "Pay money owed to lost cousin. Lose 100k.", "Bought many girl scout cookies. Lose 150k",
								"Lost money in stocks. Lose 200k.", "Bank account got phished. Lose 300k", "Won a game of BINGO! Win 50k.", "Investment pays dividends. Win 100k",
								"Look under bed at mattress store. Win 150k", "Sell your trading cards online. Win 200k", "Receive money from the Prince of Nigeria. Win 300k" };
	int actionValue[10] = { -50,-100,-150,-200,-300,50,100,150,200,300 };

	// 	int randomSpinner = (rand() % 5) + 1; 				// used for reference. Will declare it each time when the player/computer spins. Returns a number 1-5. 
	//	int randomPath = (rand() % 2) + 1;	  				// used for reference. Used to decide which path the computer will take. 


	/* Player 1 Variables */
	string playerName;
	int money1 = 0;					// total money
	int numKids1 = 0;				// number of kids player has
	int numActionCards1 = 0;		// number of action cards collected
	int totalWorth1 = 0;			// used at the end of the game to see total worth
	string jobName1;				// name of job
	int jobWage1;					// yearly salary of job
	string myHouse = "None" ;		// set to None if player never lands on House space.
	int myHousePrice = 0;			// 

	bool retired1 = false;			// used to control loop within the gameState loop. 
	int currentLocation1 = 0;		// updates after every spin
	string spaceLocation1[58];		// each map is 'unique' to the player and computer and may change its location spaces based on user choices at STOP spaces
									// starts with default options Career/ Continue/ Safe. Other options are College/ Family/ Risky. You can only have 1 of 2 options. EX: "Career or College?"


	/* COMPUTER player Variables */
	int money2 = 0;
	int numKids2 = 0;
	int numActionCards2 = 0;
	int totalWorth2 = 0;
	string jobName2;
	int jobWage2;
	string computerHouse = "None";
	int computerHousePrice = 0;

	bool retired2 = false;
	int currentLocation2 = 0;			// updates after every spins
	string spaceLocation2[58];



	/* Player 1 Array Values*/
	for (int index = 0; index < 58; index++) {															// PLAYER MAP CREATION. ALLOWS PROPER LOCATION OF SPACES

		if (index == 4 || index == 8 || index == 14 || index == 19 ||
			index == 30 || index == 36 || index == 39 || index == 47 || index == 54) {
			spaceLocation1[index] = "PAY";
		}
		else if (index == 17 || index == 25 || index == 41) {
			spaceLocation1[index] = "STOP";
		}
		else if (index == 21 || index == 49) {
			spaceLocation1[index] = "HOUSE";
		}
		else if (index == 0) {
			spaceLocation1[index] = "CAREER";
		}
		else if (index == 57) {
			spaceLocation1[index] = "RETIRE";
		}
		else {
			spaceLocation1[index] = "ACTION";
		}
	}
	/*Player 2 Array Values*/																			// COMPUTER MAP CREATION. ALLOWS PROPER LOCATION OF SPACES
	for (int index = 0; index < 58; index++) {

		if (index == 4 || index == 8 || index == 14 || index == 19 ||
			index == 30 || index == 36 || index == 39 || index == 47 || index == 54) {
			spaceLocation2[index] = "PAY";
		}
		else if (index == 17 || index == 25 || index == 41) {
			spaceLocation2[index] = "STOP";
		}
		else if (index == 21 || index == 49) {
			spaceLocation2[index] = "HOUSE";
		}
		else if (index == 0) {
			spaceLocation2[index] = "CAREER";
		}
		else if (index == 57) {
			spaceLocation2[index] = "RETIRE";
		}
		else {
			spaceLocation2[index] = "ACTION";
		}
	}



	cout << "Welcome to the Mini-Game of Life!" << endl;
	cout << "Would you like to play? Type \"y\" to play. " << endl;
	cin >> userInput;


	/* Player1 Details Chosen*/
	if (userInput == "y") {

		cout << "Awesome lets get going!" << endl;
		cout << "What is your name? " << endl;
		cin >> playerName;																		// your name

		cout << "Here is some money to start you off, " << playerName << "." << endl;
		money1 = 200;
		cout << "Money: " << money1 << "K"<< endl << endl;										// this code will repeat multiple times throughout the program. Displays the players money.

		cout << "Would you like to start with a Career or College? 1 or 2?" << endl;
		cin >> userInput;

		while (userInput != "1" && userInput!= "2") {											// keep asking if the user enters something other than 1 or 2
			cout << "Try again. 1 or 2?" << endl;
			cin >> userInput;
		}
		cout << endl << endl; 
		if (userInput == "1") {
			int randomJob1 = (rand() % 5);														// chooses number 0-4
			cout << "You chose Career!" << endl;
			jobName1 = careerName[randomJob1];													// assigns job from careerName
			jobWage1 = careerWage[randomJob1];													// assigns wage from careerWage

			cout << "Your career is " << jobName1 << "."<< endl;			
			cout << "Yearly salary: " << jobWage1 << "K" << endl;
			cout << playerName << "'s Money: " << money1 << "K" << endl << endl;

		} else if (userInput == "2") {
			cout << "You chose College!" << endl;
			cout << "Pay 100K for your education." << endl;
			money1 = money1 - 100;																// pay 100k if you go to college
			cout << playerName << "'s Money: " << money1 << "K" << endl << endl;

			spaceLocation1[0] = "COLLEGE";														// changes the MAP layout if college is chosen. 
			spaceLocation1[1] = "ACTION";														// replaces the original values, with values that correspond with the "College Path"
			spaceLocation1[2] = "ACTION";
			spaceLocation1[3] = "ACTION";
			spaceLocation1[4] = "ACTION";
			spaceLocation1[5] = "STOP";
			spaceLocation1[6] = "ACTION";
			spaceLocation1[7] = "ACTION";
		}

		/* COMPUTER Player Details*/
		/* FILLS OUT AUTOMATICALLY*/
		cout << endl << endl;

		money2 = 200;
		int pathChoice = (rand() % 2) + 1;														// chooses 1-2

		if (pathChoice == 1) {
			int randomJob2 = (rand() % 5);														// number 0-4
			cout << "COMPUTER chose Career!" << endl;
			jobName2 = careerName[randomJob2];
			jobWage2 = careerWage[randomJob2];

			cout << "COMPUTER's career is: " << jobName2 << "." << endl;
			cout << "Yearly salary: " << jobWage2 << "K" << endl;
			cout << "COMPUTER's MONEY: " << money2 << "K" << endl << endl;

		} else if (pathChoice == 2) {
			cout << "COMPUTER chose College! " << endl;
			cout << "COMPUTER PAYS 100k for the education." << endl;
			money2 = money2 - 100;
			cout << "COMPUTER's MONEY: " << money2 << "K" << endl << endl;

			spaceLocation2[0] = "COLLEGE";														// changes the MAP layout if college is chosen. 
			spaceLocation2[1] = "ACTION";														// replaces the original values, with values that correspond with the "College Path"
			spaceLocation2[2] = "ACTION";
			spaceLocation2[3] = "ACTION";
			spaceLocation2[4] = "ACTION";
			spaceLocation2[5] = "STOP";
			spaceLocation2[6] = "ACTION";
			spaceLocation2[7] = "ACTION";

		}


	} else {																						// EXITS GAME if response is not "y"
		cout << "Later! Exiting. " << endl;
		gameState = false;
	}


	/* ********************************************************************************************************************** /


	/* BEGINNING OF GAME LOOP*/
	while (gameState == true) {						
		// Player Turn
		if (retired1 == false) {
			cout << endl << endl << endl;
			cout << "---------------------------------------------------------------------" << endl;
			cout << "Press \"s\" to spin!" << endl;
			cin >> userInput;

			while (userInput != "s") {
				cout << "Try again. Press \"s\" to spin!" << endl;									// if user doesn't enter "s" it will keep repeating
				cin >> userInput;
			}

			if (userInput == "s") {
				
					int randomSpinner = (rand() % 5) + 1;												// random number from 1-5
					cout << "You spinned " << randomSpinner << endl;
					for (int index = 0; index < randomSpinner; index++) {								// loops the amount of times
						currentLocation1++;

						if (spaceLocation1[currentLocation1] == "PAY") {
							cout << endl << endl;
							money1 = money1 + jobWage1;
							cout << "You passed PAYDAY! Earned " << jobWage1 << "K." << endl;
						} else if (spaceLocation1[currentLocation1] == "STOP") {
							cout << endl << endl;
							index = randomSpinner;														// stops loop

							/* STOP LOCATION CHECKER */
							/* PLAYER STOPS NO MATTER HOW MUCH THEY ROLL*/
							/* IF THEY ENCOUNTER A STOP SPACE THEY WILL STOP AND ROLL AFTERWARDS*/
							switch (currentLocation1) {													// Checks which STOP location the player is at
								case 5: {																	// GRADUATE COLLEGE
									int randomJob1 = (rand() % 5);
									cout << "Congrats you graduated College!" << endl;

									jobName1 = collegeName[randomJob1];
									jobWage1 = collegeWage[randomJob1];
									cout << "Your career is " << jobName1 << "." << endl;
									cout << "Yearly salary: " << jobWage1 << "K" << endl;
									cout << playerName << "'s Money: " << money1 << "K" << endl << endl;
									break; }
								case 17: {																	// GET MARRIED
									cout << "You got married!" << endl;
									cout << "You earned 100k in your account." << endl;
									money1 = money1 + 100;
									cout << playerName << "'s Money: " << money1 << "K" << endl << endl;
									break; }
								case 25: {																		// CONTINUE/ FAMILY PATH
									cout << "Would you like the Continue path or Family path? 1 or 2?" << endl;
									cin >> userInput;

									while (userInput != "1" && userInput != "2") {								// keep asking if the user enters something other than 1 or 2
										cout << "Try again. 1 or 2?" << endl;
										cin >> userInput;
									}

									if (userInput == "1") {
										cout << "You chose Continue Path." << endl;
									}
									else if (userInput == "2") {
										cout << "You chose Family Path." << endl;
										spaceLocation1[26] = "ACTION";											// changes the MAP layout if Family is chosen. 
										spaceLocation1[27] = "BABY";											// the values correspond with the Family path
										spaceLocation1[28] = "ACTION";
										spaceLocation1[29] = "BABY";
										spaceLocation1[30] = "ACTION";
										spaceLocation1[31] = "PAY";
										spaceLocation1[32] = "ACTION";
									}
									break;
								}
								case 41: {
									cout << "Would you like to choose the Safe path or Risky path? 1 or 2?" << endl;
									cin >> userInput;

									while (userInput != "1" && userInput != "2") {								// keep asking if the user enters something other than 1 or 2
										cout << "Try again. 1 or 2?" << endl;
										cin >> userInput;
									}

									if (userInput == "1") {
										cout << "You chose Safe Path." << endl;
									}
									else if (userInput == "2") {
										cout << "You chose Risky Path." << endl;								// changes the MAP layout if Risky is chosen. 
										spaceLocation1[42] = "ACTION";											// corresponds with the Risky path.
										spaceLocation1[43] = "LOSE";
										spaceLocation1[44] = "PAY";
										spaceLocation1[45] = "LOSE";
										spaceLocation1[46] = "PAY";
										spaceLocation1[47] = "ACTION";
										spaceLocation1[48] = "ACTION";

									}

									break;
								}
							}

						}
	else if (spaceLocation1[currentLocation1] == "RETIRE") {
		index = randomSpinner;																// stops loop
		cout << "You have retired!" << endl;
		retired1 = true;																	// exits out of player 1 loop
	}

					}
					/* IF YOU LAND ON THESE SPACES ONLY*/
					/* PASSING THEM WILL NOT ACTIVATE THE VALUE WITHIN THEM*/
					if (spaceLocation1[currentLocation1] == "BABY") {									// if you land on baby. Add one to num of Kids
						cout << endl << endl;
						cout << "You landed on BABY space." << endl;
						cout << "You had a kid!" << endl;
						numKids1 = numKids1 + 1;
						cout << "Number of Kids: " << numKids1 << endl;
					}

					if (spaceLocation1[currentLocation1] == "HOUSE") {
						cout << endl << endl;
						int randomHouse1 = (rand() % 5);									// numbers 0-4
						cout << "You landed on HOUSE space." << endl;
						cout << "You get to buy a house." << endl;
						myHouse = houseName[randomHouse1];									// chooses a house from the houseName array. Parallel array with housePrice.
						myHousePrice = housePrice[randomHouse1];							// selects the housePrice of the same index 
						cout << "You bought a " << myHouse << "." << endl;
						cout << "Price: " << myHousePrice << endl;
						cout << playerName << "'s Money: " << money1 << "K" << endl << endl;
					}

					if (spaceLocation1[currentLocation1] == "LOSE") {
						cout << endl << endl;
						cout << "You landed on LOSE space." << endl;
						cout << "You lose 200k." << endl;
						money1 = money1 - 200;													// subtract 200 from money if you land on LOSE space.
						cout << playerName << "'s Money: " << money1 << "K" << endl << endl;
					}

					if (spaceLocation1[currentLocation1] == "ACTION") {						
						cout << endl << endl;
						cout << "You landed on an ACTION space" << endl;
						int randomAction = (rand() % 10);										// random number 0-9
						numActionCards1 = numActionCards1 + 1;									// adds 1 to the numActionCards variable
						cout << actionName[randomAction] << endl;								// displays name of action
						money1 = money1 + actionValue[randomAction];							// adds the value of the actionCard selected
						cout << playerName << "'s Money: " << money1 << "K" << endl << endl;
					}

					if (spaceLocation1[currentLocation1] == "PAY") {
						cout << endl << endl;
						cout << "You landed on a PAYDAY space." << endl;
					}

			}


		}



		if (retired2 == false) {
			// Computer turn
			int randomSpinner = (rand() % 5) + 1;												// random number from 1-5
			for (int index = 0; index < randomSpinner; index++) {								// loops the amount of times
				currentLocation2++;
				if (spaceLocation2[currentLocation2] == "PAY") {
					money2 = money2 + jobWage2;
				}
				else if (spaceLocation2[currentLocation2] == "STOP") {
					cout << endl << endl;
					index = randomSpinner;														// stops loop

					/* STOP LOCATION CHECKER */
					switch (currentLocation2) {													// Checks which STOP location the player is at
					case 5: {																	// GRADUATE COLLEGE
						int randomJob1 = (rand() % 5);
						jobName2 = collegeName[randomJob1];
						jobWage2 = collegeWage[randomJob1];
						break; }
					case 17: {																	// GET MARRIED
						money2 = money2 + 100;
						break; }
					case 25: {																	// CONTINUE/ FAMILY PATH
						int randomPath = (rand() % 2) + 1;										// random number 1-2
						computerInput = randomPath;												// instead of cin used for the player turn. Computer turn is selected by randomNumbers and computerInput is used. 

						if (computerInput == 1) {

						}
						else if (computerInput == 2) {

							spaceLocation2[26] = "ACTION";										// changes the MAP layout if Family is chosen. 
							spaceLocation2[27] = "BABY";										// corresponds with Family path.
							spaceLocation2[28] = "ACTION";
							spaceLocation2[29] = "BABY";
							spaceLocation2[30] = "ACTION";
							spaceLocation2[31] = "PAY";
							spaceLocation2[32] = "ACTION";
						}
						break;
					}
					case 41: {
						int randomPath = (rand() % 2) + 1;
						computerInput = randomPath;

						if (computerInput == 1) {

						}
						else if (computerInput == 2) {
							spaceLocation2[42] = "ACTION";										// changes the MAP layout if Risky is chosen.
							spaceLocation2[43] = "LOSE";										// corresponds with Risky Path
							spaceLocation2[44] = "PAY";
							spaceLocation2[45] = "LOSE";
							spaceLocation2[46] = "PAY";
							spaceLocation2[47] = "ACTION";
							spaceLocation2[48] = "ACTION";
						}

						break;
					}
					}

				}
				else if (spaceLocation2[currentLocation2] == "RETIRE") {
					index = randomSpinner;																// stops loop
					cout << "COMPUTER retired!" << endl;
					retired2 = true;																	// exits out of player 1 loop
				}

			}

			if (spaceLocation2[currentLocation2] == "BABY") {									// if you land on baby. Add one to num of Kids
				numKids2 = numKids2 + 1;														
			}

			if (spaceLocation2[currentLocation2] == "HOUSE") {
				int randomHouse = (rand() % 5);													// number 0-4
				computerHouse = houseName[randomHouse];											// selects random house from the houseName array. Parallel array.
				computerHousePrice = housePrice[randomHouse];									// selects the price from the housePrice array
			}

			if (spaceLocation2[currentLocation2] == "LOSE") {
				money2 = money2 - 200;															// subtract 200 from money
			}

			if (spaceLocation2[currentLocation2] == "ACTION") {
				int randomAction = (rand() % 10);												// random number 0-9
				numActionCards2 = numActionCards2 + 1;											// adds 1 to number of actionCards
				money2 = money2 + actionValue[randomAction];									// adds the value in the actionValue array to money variable
			}

			if (spaceLocation2[currentLocation2] == "PAY") {

			}

		}

		/* END GAME STATS */
		if (retired1 && retired2 == true) {
			cout << "--------------------------------------" << endl;
			cout << "YOUR STATS" << endl;
			cout << "Job Name: " << jobName1 << endl;
			cout << "Job Wage: " << jobWage1 << "K" << endl;
			cout << "Type of house: " << myHouse << endl;
			cout << "House sale value: " << myHousePrice * 2<< "K" << endl;					// double value
			cout << "Number of kids: " << numKids1 << endl;
			cout << "Number of Action Cards: " << numActionCards1 << endl;
			cout << "Money: " << money1 << "K" << endl;
			cout << endl << endl;
			totalWorth1 = OverallValue( myHousePrice, numKids1, numActionCards1, money1);	// calls function; returns value
			cout << " Total Worth: " << totalWorth1 << "K" << endl;							// the amount of money with everything added up


			cout << "--------------" << endl;
			cout << "COMPUTER STATS" << endl;
			cout << "Job Name: " << jobName2 << endl;
			cout << "Job Wage: " << jobWage2 << "K" << endl;
			cout << "Type of house: " << computerHouse << endl;
			cout << "House sale value: " << computerHousePrice * 2 << "K" << endl;			// double value
			cout << "Number of kids: " << numKids2 << endl;
			cout << "Number of Action Cards: " << numActionCards2 << endl;					
			cout << "Money: " << money2 << "K" << endl;
			cout << endl << endl;
			totalWorth2 = OverallValue(computerHousePrice, numKids2, numActionCards2, money2);		// calls function; returns value
			cout << " Total Worth: " << totalWorth2 << "K" << endl;

			gameState = false;									// exits loop
		}
	}




	system("pause");
	return 0;
}