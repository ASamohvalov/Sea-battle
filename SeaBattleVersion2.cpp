#include <iostream>
#include <fstream>
#include <math.h>
#include <conio.h>
#include <Windows.h>
#include <vector>
#include <time.h>
#include <set>
#include <string>

using namespace std;

//проверка заполнения полей
void readerData(char arena[12][12], string plr);
bool checkArena1(char arena[12][12]);
bool checkArena2(char arena[12][12], int elI, int elJ, int desk, int HV);

//основная игра
void mainGame(char arena1[12][12], char arena2[12][12]);
void cleaning(string point, int fairPoint[2]);
void inputPoint(char fld[12][12], char arena[12][12], int player, int &win);
bool checkingKill(char arena[12][12], int fairPoint[2]);
void changeArena(char fld[12][12], int fairPoint[2]);

int main() 
{
	setlocale(LC_ALL, "ru");
	cout << "\t\t\t\t\t\tSeaBattle version-2\n";
	//Sleep(700);

	while (true) {
		cout << "\nВыберите тип игры: \n 1.Игра в двоём\n 2.Игра с компьютером\n";
		int choose1; cin >> choose1;
		if (choose1 == 1) {
			//player 1
			char arena1[12][12];
			readerData(arena1, "1");
			
			//player 2
			char arena2[12][12];
			readerData(arena2, "2");

			//Sleep(1000);
			cout << "\n\n\n\n\t\t\t\t\t\tSTART GAME!!!\n\n";

			mainGame(arena1, arena2);

			break;
		}
		else if (choose1 == 2) {
			cout << "На этапе разработки";
		}
		else {
			cout << "ERROR 1001";
		}
	}

	return 0;
}

void readerData(char arena[12][12], string plr) {
	while (true) {
		cout << "\n\nPlayer "<< plr <<"\n1.Создать поле или 2.Рандом\n";
		int choose2; cin >> choose2;
		
		if (choose2 == 1) {
			cout << "\n\nВведите игровое поле в файл 'Player" << plr << ".txt' и закройте его\nЕсли ввели, то нажмите на любую цифру\n";
			int choose3; cin >> choose3;
			int check1 = 0;

			//запись данных из файла в обменник (string)
			string exchanger;
			ifstream player("Player" + plr + ".txt");
			if (player.is_open()) {
				char a;
				check1++;
				while (player >> a) {
					exchanger.push_back(a);
				}
			}
			player.close();

			//запись данных из обменника в матрицу
			int k = 0;
			for (int i = 0; i < 12; i++) {
				for (int j = 0; j < 12; j++) {
					arena[i][j] = exchanger[k];
					k++;
				}
			}

			bool boo = checkArena1(arena);
			if (check1 == 1 and boo == true) {
				cout << "\n\nУспешо! Ваши данные были переданы в программу!\n\n";
				//Sleep(500);
				break;
			}
			else {
				cout << "\n\nВаш файл не удалось прочитать или вы допустили ошибку при заполнения поля. Попробуйте снова\n\n";
			}
		}
		else {
			cout << "На этапе разработки";
		}
	}
}

bool checkArena1(char arena[12][12]) {
	//проверка на количество кораблей
	int fourDesk = 0, threeDesk = 0, twoDesk = 0, oneDesk = 0;
	int helper = 0;
	char dubArena[12][12];
	for (int i = 1; i < 11; i++) {
		for (int j = 1; j < 11; j++) {
			dubArena[i][j] = arena[i][j];
		}
	}

	int x = 0, y = 0;
	for (int i = 1; i < 11; i++) {
		for (int j = 1; j < 11; j++) {
			if (dubArena[i][j] == '1') {
				dubArena[i][j] = '+';
				x = i; y = j; int chk = 0; int HV = 0;
				while (true) {
					if (dubArena[x + 1][j] == '1') {
						dubArena[x + 1][j] = '+';
						helper++;
						x++;
						chk = 1;
						HV = 1;
					}
					else if (dubArena[x][j + 1] == '1') {
						dubArena[x][j + 1] = '+';
						helper++;
						j++;
						chk = 1;
						HV = 2;
					}
					else {
						helper++;
						break;
					}
				}
				bool boo;
				switch (helper) {
				case 1: 
					oneDesk++;
					boo = checkArena2(dubArena, i, y, 1, HV);
					break;
				case 2: 
					twoDesk++;
					boo = checkArena2(dubArena, i, y, 2, HV);
					break;
				case 3: 
					threeDesk++;
					boo = checkArena2(dubArena, i, y, 3, HV);
					break;
				case 4: 
					fourDesk++;
					boo = checkArena2(dubArena, i, y, 4, HV);
					break;
				}
				helper = 0;
				if (boo == false) {
					return false;
				}
			}
		}
	}
	
	int chack001 = 0;
	if (oneDesk == 4)
		chack001++;
	if (twoDesk == 3)
		chack001++;
	if (threeDesk == 2)
		chack001++;
	if (fourDesk == 1)
		chack001++;

	if (chack001 == 4)
		return true;

	return false;
}

bool checkArena2(char arena[12][12], int elI, int elJ, int desk, int HV) {
	//проверка на правильность заполнения полей

	int helper = 0;
	if (HV != 2) {
		for (int i = elI - 1; i <= elI + desk; i++) {
			for (int j = elJ - 1; j <= elJ + 1; j++) {
				if (arena[i][j] == '1' or arena[i][j] == '+')
					helper++;
			}
		}
	}
	else {
		for (int i = elI - 1; i <= elI + 1; i++) {
			for (int j = elJ - 1; j <= elJ + desk; j++) {
				if (arena[i][j] == '1' or arena[i][j] == '+')
					helper++;
			}
		}
	}

	if (helper == desk) {
		return true;
	}
	return false;
}

void mainGame(char arena1[12][12], char arena2[12][12]) {
	char fld1[12][12] = { {'*', '1', '2', '3', '4', '5', '6', '7', '8', '9', '@', '*'},
						  {'a', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'a'},
						  {'b', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'b'},
						  {'c', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'c'},
						  {'d', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'd'},
						  {'e', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'e'},
						  {'f', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'f'},
						  {'g', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'g'},
						  {'h', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'h'},
						  {'i', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'i'},
						  {'j', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'j'},
						  {'*', '1', '2', '3', '4', '5', '6', '7', '8', '9', '@', '*'}, };

	char fld2[12][12] = { {'*', '1', '2', '3', '4', '5', '6', '7', '8', '9', '@', '*'},
						  {'a', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'a'},
						  {'b', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'b'},
						  {'c', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'c'},
						  {'d', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'd'},
						  {'e', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'e'},
						  {'f', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'f'},
						  {'g', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'g'},
						  {'h', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'h'},
						  {'i', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'i'},
						  {'j', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'j'},
						  {'*', '1', '2', '3', '4', '5', '6', '7', '8', '9', '@', '*'}, };

	cout << "\nСлева поле 1 игрока, а справа поле 2 игрока. Вам необходимо уничтожить все корабли противника, которые зпрятаны за ноликами. '+' - уничтоженный корабль(попадание). '.' - вода(промах).\n\n";
	for (int i = 0; i < 12; i++) {
		cout << "\t";
		for (int j = 0; j < 12; j++) {
			cout << fld1[i][j] << ' ';
		}
		cout << "\t\t\t";
		for (int j = 0; j < 12; j++) {
			cout << fld2[i][j] << ' ';
		}
		cout << endl;
	}

	cout << "\nНажмите на любую цифру или букву чтобы начать игру ";
	char s; cin >> s;

	int win1 = 10, win2 = 10;
	while (true) {
		cout << "\n\n\t\tPlayer 1: \n\n Это поле противника. Введите точку атаки пример: 'a-1' 'a' по вертикали '1' по горизонтали (поле 10x10)\n\n\n";
		for (int i = 0; i < 12; i++) {
			for (int j = 0; j < 12; j++) {
				cout << fld2[i][j] << ' ';
			}
			cout << endl;
		}

		inputPoint(fld2, arena2, 1, win1);
		if (win1 == 0) {
			cout << "\n\n\t\t\t\t  ИГРОК 1 - победил!!!";
			break;
		}

		cout << "\n\n\t\tPlayer 2: \n\n Это поле противника. Введите точку атаки пример: 'a-1' 'a' по вертикали '1' по горизонтали (поле 10x10)\n\n\n";
		for (int i = 0; i < 12; i++) {
			for (int j = 0; j < 12; j++) {
				cout << fld1[i][j] << ' ';
			}
			cout << endl;
		}

		inputPoint(fld1, arena1, 2, win2);
		if (win2 == 0) {
			cout << "\n\n\t\t\t\t  ИГРОК 2 - победил!!!";
			break;
		}
	}

}

void inputPoint(char fld[12][12], char arena[12][12], int player, int &win) {
	while (true) {
		cout << "\n\t\tPLAYER " << player;
		string point;
		cout << "\nВаша точка: "; cin >> point;

		int fairPoint[2];
		cleaning(point, fairPoint);

		int helper = 0;
		if ((fairPoint[0] >= 10 or fairPoint[1] >= 10) 
			and (fairPoint[0] < 1 or fairPoint[1] < 1)) {
			cout << "\nError - Вы допустили ошибку при введении точки. Попробуйте снова\n";
			continue;
		}
		if (fld[fairPoint[0]][fairPoint[1]] == '.' or fld[fairPoint[0]][fairPoint[1]] == '+') {
			cout << "\nError - Разве вы сюда не стреляли? Попробуйте ввести точку снова\n";
			continue;
		}
		if (arena[fairPoint[0]][fairPoint[1]] == '1') {
			cout << "\nПревосходно! Вы попали\n";
			arena[fairPoint[0]][fairPoint[1]] = '+';
			fld[fairPoint[0]][fairPoint[1]] = '+';

			bool boo = checkingKill(arena, fairPoint);
			if (boo == true) {
				win--;
				cout << "\nКорабль противника уничтожен. осталось " << win << " кораблей\n\n";
				changeArena(fld, fairPoint);
			}
			helper = 1;
		}
		else {
			cout << "\nПромах!!\n\n";
			arena[fairPoint[0]][fairPoint[1]] = '.';
			fld[fairPoint[0]][fairPoint[1]] = '.';
		}

		for (int i = 0; i < 12; i++) {
			for (int j = 0; j < 12; j++) {
				cout << fld[i][j] << ' ';
			}
			cout << endl;
		}

		if (win == 0) {
			break;
		}

		if (helper == 1) {
			continue;
		}
		break;
	}
}

void cleaning(string point, int fairPoint[2]) {
	int j = 0;
	if (point[point.size() - 1] == '0' and point[point.size() - 2] == '1') {
		point[point.size() - 2] = '@';
		point[point.size() - 1] = ' ';
 	}
	for (int i = 0; i < point.size() and j < 2; i++) {
		if (isdigit(point[i])) {
			fairPoint[j] = point[i] - '0';
			j++;
		}
		else {
			switch (point[i]) {
			case 'a': fairPoint[j] = 1;
				break;
			case 'b': fairPoint[j] = 2;
				break;
			case 'c': fairPoint[j] = 3;
				break;
			case 'd': fairPoint[j] = 4;
				break;
			case 'e': fairPoint[j] = 5;
				break;
			case 'f': fairPoint[j] = 6;
				break;
			case 'g': fairPoint[j] = 7;
				break;
			case 'h': fairPoint[j] = 8;
				break;
			case 'i': fairPoint[j] = 9;
				break;
			case 'j': fairPoint[j] = 10;
				break;
			case '@': fairPoint[j] = 10;
				break;
			default: j--;
				break;
			}
			j++;
		}
	}
}

bool checkingKill(char arena[12][12], int fairPoint[2]) {
	bool helper = true;
	if (arena[fairPoint[0] - 1][fairPoint[1]] == '1' or arena[fairPoint[0]][fairPoint[1] + 1] == '1'
		or arena[fairPoint[0] + 1][fairPoint[1]] == '1' or arena[fairPoint[0]][fairPoint[1] - 1] == '1') {
		helper = false;
	}
	return helper;
}

void changeArena(char fld[12][12], int fairPoint[2]) {
	int HV = 0;
	if (fld[fairPoint[0] - 1][fairPoint[1]] == '+' or fld[fairPoint[0] + 1][fairPoint[1]] == '+') {
		HV = 1; //v
	}
	else if (fld[fairPoint[0]][fairPoint[1] + 1] == '+' or fld[fairPoint[0] - 1][fairPoint[1]] == '+') {
		HV = 2; //h
	}

	int point = 0;
	if (HV == 1) {
		int i = fairPoint[0], j = fairPoint[1];
		while (point != 1) {
			if (fld[i][j + 1] == '0') {
				fld[i][j + 1] = '.';
			}
			if (fld[i][j - 1] == '0') {
				fld[i][j - 1] = '.';
			}
			if (fld[i][j] != '+') {
				if (fld[i][j] == '0')
					fld[i][j] = '.';
				point++;
			}
			i--;
		}

		point = 0;
		int v = fairPoint[0] + 1, h = fairPoint[1];
		while (point != 1) {
			if (fld[v][h + 1] == '0') {
				fld[v][h + 1] = '.';
			}
			if (fld[v][h - 1] == '0') {
				fld[v][h - 1] = '.';
			}
			if (fld[v][h] != '+') {
				if (fld[v][h] == '0')
					fld[v][h] = '.';
				point++;
			}
			v++;
		}
	}
	else {
		int i = fairPoint[0], j = fairPoint[1];
		while (point != 1) {
			if (fld[i + 1][j] == '0') {
				fld[i + 1][j] = '.';
			}
			if (fld[i - 1][j] == '0') {
				fld[i - 1][j] = '.';
			}
			if (fld[i][j] != '+') {
				if (fld[i][j] == '0')
					fld[i][j] = '.';
				point++;
			}
			j--; 
		}

		point = 0;
		int v = fairPoint[0], h = fairPoint[1] + 1;
		while (point != 1) {
			if (fld[v + 1][h] == '0') {
				fld[v + 1][h] = '.';
			}
			if (fld[v - 1][h] == '0') {
				fld[v - 1][h] = '.';
			}
			if (fld[v][h] != '+') {
				if (fld[v][h] == '0')
					fld[v][h] = '.';
				point++;
			}
			v++;
		}
	}
}