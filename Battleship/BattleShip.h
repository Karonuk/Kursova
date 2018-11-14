#pragma once
#include<iostream>


using namespace std;

bool endgame = true;
int pozX = 1;
int pozY = 1;
int menuSelectionPosition ;
int menu_size=0;
int currentShipSize =0;
int oneShipCounter = 0;
int twoShipCounter = 0;
int threeShipCounter = 0;
int fourthShipCounter = 0;
int ShipSizeMinus = 0;
bool menuInput = false;
int selection = -1;
bool isShipDestroyed = false;
bool rotatedShip = false;
bool OneShipAlmost=false;
bool TwoShipAlmost = false;
bool ThreeShipAlmost = false;
bool FourthShipAlmost = false;
bool GameReady = false;
bool gameStart = false;
bool shipAIplaced = false;
bool isAIShipNearby = false;
bool wasShoted = false;
int shipDestroySize=0;
int shipPlayer = 0;
int shipAI = 0;
char Button;
char ship[][100] = { "#", "##", "###", "####", "Cancel"};
int turn;
bool isShipNearby = false;

void FillGameField(char PlayerField[11][11]);
void UserInputs(char[11][11],char[11][11]);
void DrawUI(char[11][11],char [11][11]);
void DrawSelectedShip();
void GameLogic(char[11][11], char[11][11]);
void ShipCheck(char[11][11]);
void ShipCounter(char[11][11]);
void ShipPlacement(char[11][11]);
void AIFieldFilling(char[11][11]);
void AIships(char[11][11]);
void AIShipCheck(char field[11][11], int size, int rotate, int x, int y);
void AITurn(char[11][11]);
void battle(char[11][11], char[11][11]);
void AICheckShip(char field[11][11]);
void PlayerCheckShip(char PlayerField[11][11]);
void NewGame();
void gameRun() {
	srand(time(0));
	menu_size = (sizeof(ship) / sizeof(*ship));
	char AIField[11][11];
	char PlayerField[11][11];
	bool PlayerWon=false;
	bool AIWon = false;
	FillGameField(PlayerField);
	AIFieldFilling(AIField);
	system("cls");
	DrawUI(AIField,PlayerField);
	while (endgame) {	
		
		UserInputs(PlayerField,AIField);
		GameLogic(PlayerField, AIField);
		DrawUI(PlayerField, AIField);
		if (gameStart) {
			AICheckShip(AIField);
			PlayerCheckShip(PlayerField);
			if (shipAI == 0) {
				endgame=false;
				PlayerWon = true;
			}
			else if (shipPlayer == 0) {
				endgame = false;
				AIWon = true;
			}
			
	}
	}
	if (PlayerWon) {
		cout << "You Won" << endl;
		system("pause");
	}
	else if (AIWon) {
		cout << "You Lose" << endl;
		system("pause");
	}
	NewGame();
	system("pause");
}

void AIFieldFilling(char field[11][11]) {
	int symbol = 65;
	for (int i = 0; i < 11; i++) {

		for (int j = 0; j < 11; j++) {
			if (i == 0 && j == 0) {
				field[i][j] = ' ';
			}
			else if (i == 0) {
				field[i][j] = symbol - 1;
			}
			else if (j == 0) {
				if (i == 11 - 1)
					field[i][j] = '0';

				else
					field[i][j] = i + 48;
			}
			else
				field[i][j] = ' ';
			symbol++;

		}cout << endl;

	}
}
void DrawBattleFields(char field[11][11], char PlayerField[11][11]) {
	for (int j = 0; j < 11; j++) {		
			for (int g = 0; g < 11; g++) {				
				if (pozY == j && pozX == g && !gameStart) {

					if (PlayerField[pozY][pozX] != '#')
						cout << setw(2) << '_';
					else
						cout << setw(2) << '#';

				}
				else
					cout << setw(2) << PlayerField[j][g];

			}		
			for (int i = 0; i < 11; i++) {
				

				if (pozY == j && pozX == i && gameStart)
					if (field[pozY][pozX] == 'X')
						cout << setw(2) << 'x';
					else if (field[pozY][pozX] == 'O')
							cout << setw(2) << 'o';				
				else
						cout <<setw(2) <<  '_';
				else {
					if (field[j][i] == '#') {
						cout << setw(2) << ' ';
					}
					else
					cout << setw(2) << field[j][i];
				}
		}
		cout << endl;
	}
}

void FillGameField(char PlayerField[11][11]) {
	int symbol = 65;
	for (int i = 0; i < 11; i++) {

		for (int j = 0; j < 11; j++) {
			if (i == 0 && j == 0) {
				PlayerField[i][j] = ' ';
			}
			else if (i == 0) {
				PlayerField[i][j] = symbol - 1;
			}
			else if (j == 0) {
				if (i == 11 - 1)
					PlayerField[i][j] = '0';

				else
					PlayerField[i][j] = i + 48;
			}
			else
				PlayerField[i][j] = ' ';
			symbol++;

		}cout << endl;

	}
}
void AIships(char field[11][11]) {
	int randX, randY, randRotate;
	int size =0;
	int  counterAIShip = 0;
	
	while (true) {
		randX = 1 + rand() %8;
		randY = 1 + rand() % 8;
		
		randRotate =1+ rand() % 2;
		AIShipCheck(field, size, randRotate, randX, randY);
		if (!isAIShipNearby) {
			for (int j = 0; j <= size; j++) {
				if (randRotate == 1) {
					field[randY][randX + j] = '#';
				}

				else {
					field[randY + j][randX] = '#';
				}
				
				
			}
			counterAIShip++;
		}
		else {
			isAIShipNearby = false;
		}
				if (size == 0 && counterAIShip == 4) {
					size++;
					
					counterAIShip = 0;
				}
				 if (size == 1 && counterAIShip == 3) {
					size++;
					counterAIShip = 0;
				}
				 if (size == 2 && counterAIShip == 2) {
					size++;
					counterAIShip = 0;
				}
				 if (size == 3 && counterAIShip == 1) {
					size++;
					counterAIShip = 0;
					shipAIplaced = true;
					break;
					
				}
				
	}
}
void DrawUI(char PlayerField[11][11], char Field[11][11]) {
	system("cls");
	DrawBattleFields(Field, PlayerField);
	if (menuInput && !gameStart)DrawSelectedShip();
	if (!gameStart) {
		cout << "You:" << endl;
		cout << "#-" << oneShipCounter << endl;
		cout << "##-" << twoShipCounter << endl;
		cout << "###-" << threeShipCounter << endl;
		cout << "####-" << fourthShipCounter << endl;
	}
	
	if (GameReady&&!gameStart)cout << "Press e to start battle" << endl;
	cout << "Press b to end game" << endl;
}
void UserInputs(char PlayerField[11][11],char field[11][11]) {
	while (!_kbhit()) {}
	Button = _getch();

	switch (Button) {

	case 'w':
		if (!menuInput) {
			pozY--;
			if (pozY < 1) pozY = 10;
		}
		else {
			menuSelectionPosition++;
			if (menuSelectionPosition > menu_size - 1) menuSelectionPosition = 0;
		}
		break;
	case 's':
		if (!menuInput) {
			pozY++;
			if (pozY > 10) pozY = 1;
		}
		else {
			menuSelectionPosition--;
			if (menuSelectionPosition < 0) menuSelectionPosition = menu_size - 1;
		}
		break;
	case 'a':
		if (!menuInput) {
			pozX--;
			if (pozX < 1)pozX = 10;
		}
		else {
			rotatedShip = !rotatedShip;
		}
		break;
	case 'd':
		if (!menuInput) {
			pozX++;
			if (pozX > 10)pozX = 1;
		}
		else {
			rotatedShip = !rotatedShip;
		}
		break;
	case 'b': {endgame = false;
		break; }
	case'e': {
		AIships(field); 
		if (GameReady)
			gameStart = true;
		break;
	}
	case ' ': {
		if(!gameStart)
		ShipPlacement(PlayerField); 
		else {
			battle(PlayerField, field);
		}
			  break;
	}
			  Button = '\0';
			  menuSelectionPosition = 0;
  }

	
}
void ShipPlacement(char PlayerField[11][11]) {
	
		if (menuSelectionPosition != menu_size - 1) {
			menuInput = !menuInput;
			selection = menuSelectionPosition;
			if (selection >= 0 && selection != menu_size - 1) {
				ShipCheck(PlayerField);
				if (!isShipNearby && !menuInput) {
					for (int j = 0; j <= selection; j++) {
						
							if (!rotatedShip) {
								if (menuSelectionPosition == 0 && !OneShipAlmost) {
									PlayerField[pozY][pozX + j] = '#';
									currentShipSize++;
								}
								else if (menuSelectionPosition == 1 && !TwoShipAlmost) {
									PlayerField[pozY][pozX + j] = '#';
									currentShipSize++;
								}
								else if (menuSelectionPosition == 2 && !ThreeShipAlmost) {
									PlayerField[pozY][pozX + j] = '#';
									currentShipSize++;
								}
								else if (menuSelectionPosition == 3 && !FourthShipAlmost) {
									PlayerField[pozY][pozX + j] = '#';
									currentShipSize++;
								}
								else PlayerField[pozY][pozX + j] = ' ';
							}
							else {
								if (menuSelectionPosition == 0 && !OneShipAlmost) {
									PlayerField[pozY + j][pozX] = '#';
									currentShipSize++;
								}
								else if (menuSelectionPosition == 1 && !TwoShipAlmost) {
									PlayerField[pozY + j][pozX] = '#';
									currentShipSize++;
								}
								else if (menuSelectionPosition == 2 && !ThreeShipAlmost) {
									PlayerField[pozY + j][pozX] = '#';
									currentShipSize++;
								}
								else if (menuSelectionPosition == 3 && !FourthShipAlmost) {
									PlayerField[pozY + j][pozX] = '#';
									currentShipSize++;
								}
								else PlayerField[pozY + j][pozX] = ' ';
							}
						}
					
					}
				else {
					isShipNearby = false;
					menuSelectionPosition = 0;
				
				}
			}
		}
		else {
			selection = 0;
			PlayerField[pozY][pozX] = ' ';
			menuInput = !menuInput;
			int j = 1;

			if (PlayerField[pozY][pozX + j] == '#') {
				ShipSizeMinus = 1;
				while (PlayerField[pozY][pozX + j] != ' ') {
					PlayerField[pozY][pozX + j] = ' ';
					j++;
					ShipSizeMinus++;
				}
			}
			else if (PlayerField[pozY + j][pozX] == '#') {
				ShipSizeMinus = 1;
				while (PlayerField[pozY + j][pozX] != ' ') {
					PlayerField[pozY + j][pozX] = ' ';
					j++;
					ShipSizeMinus++;
				}
			}
			j = 0;
		}
	
}
void DrawSelectedShip() {
	cout << "Choose a ship" << endl;
	
	if (!rotatedShip) {
		
		cout << ship[menuSelectionPosition] << endl;
	}
	else {
		if(menuSelectionPosition !=menu_size-1)
		for (int j = 0; j <= menuSelectionPosition; j++) {
			cout << '#' << endl;
		}
		else{
			cout << "Cancel" << endl;
		}
	}
}
void GameLogic(char PlayerField[11][11],char field[11][11]) {
	ShipCounter(PlayerField);
}
void ShipCheck(char PlayerField[11][11]) {
	if (!rotatedShip){
		if (PlayerField[pozY][pozX]=='#'||PlayerField[pozY - 1][pozX - 1] == '#' || PlayerField[pozY][pozX + menuSelectionPosition + 1] == '#' || PlayerField[pozY + 1][pozX - 1] == '#' || PlayerField[pozY][pozX - 1] == '#' || PlayerField[pozY + 1][pozX] == '#' || PlayerField[pozY - 1][pozX] == '#'){
			isShipNearby = true;
		}
		for (int j = 0; j <= menuSelectionPosition; j++){
			if (PlayerField[pozY - 1][pozX + j+1 ] == '#' || PlayerField[pozY + 1][pozX + j+1 ] == '#' || PlayerField[pozY][pozX + j + 1] == '#' ){
				isShipNearby = true;
				break;

			}
		}
	}
	else{
		if (PlayerField[pozY - 1][pozX - 1] == '#' || PlayerField[pozY + menuSelectionPosition + 1][pozX] == '#' || PlayerField[pozY - 1][pozX + 1] == '#' || PlayerField[pozY - 1][pozX] == '#' || PlayerField[pozY + 1][pozX] == '#' || PlayerField[pozY][pozX - 1] == '#'){
			isShipNearby = true;
		}
		for (int j = 0; j <= menuSelectionPosition; j++){
			if (PlayerField[pozY + j + 1][pozX - 1] == '#' || PlayerField[pozY + j + 1][pozX + 1] == '#' || PlayerField[pozY + j + 1][pozX] == '#'){
				isShipNearby = true;
				break;

			}
		}
	}
}
void ShipCounter(char PlayerField[11][11]) {
	
	if (currentShipSize == 1) {
		oneShipCounter++;
		currentShipSize = 0;
	}
	else if(currentShipSize == 2) {
		currentShipSize = 0;
		twoShipCounter++;
	}
	else if (currentShipSize == 3) {
		currentShipSize = 0;
		threeShipCounter++;
	}
	else if (currentShipSize == 4) {
		currentShipSize = 0;
		fourthShipCounter++;
	}
	if (ShipSizeMinus == 1) {
		oneShipCounter--;
		ShipSizeMinus = 0;
	}
	else if (ShipSizeMinus == 2) {
		twoShipCounter--;
		ShipSizeMinus = 0;
	}
	else if (ShipSizeMinus == 3) {
		threeShipCounter--;
		ShipSizeMinus = 0;
	}
	else if (ShipSizeMinus == 4) {
		fourthShipCounter--;
		ShipSizeMinus = 0;
	}
	if (oneShipCounter == 4) {
		OneShipAlmost = true;
	}
	if (twoShipCounter == 3) {
		TwoShipAlmost = true;
	}
	if (threeShipCounter == 2) {
		ThreeShipAlmost = true;
	}
	if (fourthShipCounter == 1) {
		FourthShipAlmost = true;
	}
	if (OneShipAlmost&&TwoShipAlmost&&ThreeShipAlmost&&FourthShipAlmost) {
		GameReady = true;
	}
}
void AIShipCheck(char field[11][11], int size, int rotate,int x,int y) {
	if (rotate==1) {
		if (field[y][x]=='#'||field[y - 1][x - 1] == '#' || field[y][x + size + 1] == '#' || field[y + 1][x - 1] == '#' || field[y][x - 1] == '#' || field[y + 1][x] == '#' || field[y - 1][x] == '#') {
			isAIShipNearby = true;
		}
		for (int j = 0; j <= size; j++) {
			if (field[y - 1][x + j + 1] == '#' || field[y + 1][x + j + 1] == '#' || field[y][x + j + 1] == '#') {
				isAIShipNearby = true;
				break;

			}
		}
	}
	else {
		if (field[y - 1][x - 1] == '#' || field[y + size + 1][x] == '#' || field[y - 1][x + 1] == '#' || field[y - 1][x] == '#' || field[y + 1][x] == '#' || field[y][x - 1] == '#' || field[y][x+1] == '#') {
			isAIShipNearby = true;
		}
		for (int j = 0; j <= size; j++) {
			if (field[y + j + 1][x - 1] == '#' || field[y + j + 1][x + 1] == '#' || field[y + j + 1][x] == '#') {
				isAIShipNearby = true;
				break;

			}
		}
	}
}
void AITurn(char PlayerField[11][11]) {
	int randX, randY;
	
	randX = 1 + rand() % 9;
	randY = 1 + rand() % 9;
	while (true) {
		if (PlayerField[randY][randX] != 'X' || PlayerField[randY][randX] != 'O') {
			randX = 1 + rand() % 9;
			randY = 1 + rand() % 9;
			break;
		}
	}
	if (PlayerField[randY][randX] == '#') {
		PlayerField[randY][randX] = 'X';
		wasShoted=true;
	}
	else {
		PlayerField[randY][randX] = 'O';
	}
	
}
void battle(char PlayerField[11][11], char Field[11][11]) {
	turn++;
	if (turn % 2 == 1) {
		AITurn(PlayerField);
		
		
	}
	else {
		if (Field[pozY][pozX] == '#'|| Field[pozY][pozX] == 'X') {
			Field[pozY][pozX] = 'X';
			wasShoted = true;
		}
		else {
			Field[pozY][pozX] = 'O';
		}
	}
	if (wasShoted) {
		turn--;
	}
	
		wasShoted = false;
	
}
void AICheckShip(char field[11][11]) {
	shipAI = 0;
	for (int i = 1; i < 12; i++) {
		for (int j = 1; j < 12; j++) {
			if (field[i][j] == '#') {
				shipAI++;
			}
		}
	}
}
void PlayerCheckShip(char PlayerField[11][11]) {
	shipPlayer = 0;
	for (int i = 1; i < 12; i++) {
		for (int j = 1; j < 12; j++) {
			if (PlayerField[i][j] == '#') {
				shipPlayer++;
			}
		}
	}
}
void NewGame() {
	 endgame = true;
	pozX = 1;
	pozY = 1;
	menuSelectionPosition;
	menu_size = 0;
	currentShipSize = 0;
	oneShipCounter = 0;
	twoShipCounter = 0;
	threeShipCounter = 0;
	fourthShipCounter = 0;
	ShipSizeMinus = 0;
	menuInput = false;
	selection = -1;
	isShipDestroyed = false;
	rotatedShip = false;
	OneShipAlmost = false;
	TwoShipAlmost = false;
	ThreeShipAlmost = false;
	FourthShipAlmost = false;
	GameReady = false;
	gameStart = false;
	shipAIplaced = false;
	isAIShipNearby = false;
	wasShoted = false;
	shipDestroySize = 0;
	shipPlayer = 0;
	shipAI = 0;
	Button;
	turn;
	isShipNearby = false;

}