#include<iostream>
#include<time.h>
#include<conio.h>
#include<iomanip>
#include <windows.h>
#include"Battleship.h"

using namespace std;

char menu[][100] = { "Start"};
int poz;
bool endprogram = false;
int Menu_num=1;
int MaxMenu;
char button;


void output();
void move();
void logic();





int main() {

	while (!endprogram) {

		output();
		move();
		logic();
		system("cls");
		
	}
}

void output() {
	if (Menu_num == 1) {
		cout << "\t..::Main Menu::.." << endl;
		for (int i = 0; i < (sizeof(menu) / sizeof(*menu)); i++) {
			if (poz == i) cout << ">";
			cout <<"\t    "<< menu[i] << endl;
		}
		cout << "\tpres q to exit" << endl;
		MaxMenu = sizeof(menu) / sizeof*(menu)-1;
	}
}

void move() {
	
	button = _getch();

	switch (button) {

	case 'w':
		poz--;
		if (poz < 0) poz = MaxMenu ;
		break;
	case 's':
		poz++;
		if (poz > MaxMenu)poz = 0;
		break;
	case 'q':
		endprogram = true;
		break;
	}

	
}

void logic() {
	
	if (button == ' ') {
		if (Menu_num == 1) {
			if (poz == 0) {
				gameRun();
			}
		}
	}
}