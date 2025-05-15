#include <iostream>
#include <random>

void initializeCube(char** top, char** bot, char** sides) {
    for (int i = 0; i < 3; i++) {
        top[i] = new char[3];
        bot[i] = new char[3];
        sides[i] = new char[12];

        for (int j = 0; j < 3; j++) {
            top[i][j]      = 'w';
            bot[i][j]      = 'y';
            sides[i][j]        = 'r';
            sides[i][j + 3]    = 'b';
            sides[i][j + 6]    = 'o';
            sides[i][j + 9]    = 'g';
        }
    }
}
void printMat(char** matrix,int size) {
	for (int i = 0; i < 3; i++)	{
		for (int j = 0; j < size; j++)	{
			std::cout << matrix[i][j]<<" ";
		}
		std::cout << std::endl;
	}
}
void changeRow(char** top, char** sides,char** bot, int row, char direction) {
	char aux;
	if (direction == 'l') {
		for (int i = 0; i < 3; i++) {
			aux = sides[row][i];
			sides[row][i] = sides[row][i + 3];
			sides[row][i + 3] = sides[row][i + 6];
			sides[row][i + 6] = sides[row][i + 9];
			sides[row][i + 9] = aux;
		}
	}
	else {
		for (int i = 0; i < 3; i++) {
			aux = sides[row][i];
			sides[row][i] = sides[row][i + 9];
			sides[row][i + 9] = sides[row][i + 6];
			sides[row][i + 6] = sides[row][i + 3];
			sides[row][i + 3] = aux;
		}
	}
	if (row == 0 || row == 2) {
		char** used = (row == 0) ? top : bot;
		char nueva_matriz[3][3];
		if ((direction == 'l' && row == 0) || (direction == 'r' && row == 2)) {
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					nueva_matriz[i][j] = used[2 - j][i];
				}
			}
		}
		else {
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					nueva_matriz[i][j] = used[j][2 - i];
				}
			}
		}
		for (int i = 0; i < 3; i++)	{
			for (int j = 0; j < 3; j++) {
				used[i][j] = nueva_matriz[i][j];
			}
		}
	}
}
void changeColumn(char** top, char** sides, char** bot, int column, char direction) {
	char aux,aux2;
	int start;
	if (direction == 'u') {
		for (int i = 0; i < 3; i++) {
			aux = top[i][column];
			top[i][column] = sides[i][column];
			sides[i][column] = bot[i][column];
			aux2 = sides[2 - i][8 - column];
			sides[2-i][8 - column] = aux;
			bot[i][column] = aux2;
		}
	}
	else {
		for (int i = 0; i < 3; i++) {
			aux = bot[i][column];
			bot[i][column] = sides[i][column];
			sides[i][column] = top[i][column];
			top[i][column] = sides[2-i][8-column];
			sides[2 - i][8 - column] = aux;
		}
	}
	if (column == 0 || column == 2) {
		char nueva_matriz[3][3];
		if ((direction == 'd' && column == 0) || (direction == 'u' && column == 2)) {
			start = column == 2 ? 3 : 9;
			for (int i = start; i < start+3; i++) {
				for (int j = 0; j < 3; j++) {
					nueva_matriz[i-start][j] = sides[2 - j][i];
				}
			}
		}
		else {
			start = column == 2 ? 3 : 9;
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					nueva_matriz[i][j] = sides[j][2 - i + start];
				}
			}
		}
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				sides[i][j+start] = nueva_matriz[i][j];
			}
		}
	}
}
void rotateCube(char** top, char** sides, char** bot, char type) {
	switch (type)
	{
	case 'u':
		for (int i = 0; i < 3; i++)
			changeColumn(top, sides, bot, i, 'u');
		break;
	case 'd':
		for (int i = 0; i < 3; i++)
			changeColumn(top, sides, bot, i, 'd');
		break;
	case 'l':
		for (int i = 0; i < 3; i++)
			changeRow(top, sides, bot, i, 'l');
		break;
	case 'r':
		for (int i = 0; i < 3; i++)
			changeRow(top, sides, bot, i, 'r');
		break;
	default:
		break;
	}
}
void printCube(char** top, char** sides, char** bot) {
	std::cout << "Cube" << std::endl;
	printMat(top, 3);
	printMat(sides, 12);
	printMat(bot, 3);
	std::cout << std::endl;
}
void makeMove(char** top, char** sides, char** bot, char type[]) {
	switch (type[0])
	{
	case 'r':
		changeRow(top, sides, bot, int(type[1] - '0'), type[2]);
		break;
	case 'c':
		changeColumn(top, sides, bot, int(type[1] - '0'), type[2]);
		break;
	case 'm':
		rotateCube(top, sides, bot, type[1]);
		break;
	default:
		break;
	}
}
bool gameOver(char** top, char** sides, char** bot) {
	char prevTop = top[0][0];
	char prevBot = bot[0][0];
	char prevSide1 = sides[0][0];
	char prevSide2 = sides[0][3];
	char prevSide3 = sides[0][6];
	char prevSide4 = sides[0][9];
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++)	{
			if (top[i][j] != prevTop || bot[i][j] != prevBot)
				return false;
			if (sides[i][j] != prevSide1 || sides[i][j + 3] != prevSide2 || sides[i][j + 6] != prevSide3 || sides[i][j + 9] != prevSide4)
				return false;
		}
	}
	return true;
}
void mixCube(char** top, char** sides, char** bot, int iter) {
	char* type = new char[3];
	for (int i = 0; i < iter; i++) {
		int random = rand() % 2;
		type[0] = random == 0 ? 'c' : 'r';
		random = rand() % 3;
		type[1] = random + 48;
		random = rand() % 2;
		if (type[0]=='c')
			type[2] = random == 0 ? 'u' : 'd';
		else
			type[2] = random == 0 ? 'l' : 'r';
		makeMove(top, sides, bot, type);
		//std::cout << type[0] << type[1] << type[2] << std::endl;
	}
}
char* solver_nextMove(){
	char* type=new char[3];
	// Steps (Idea)
		// 1 - Select random color to start
		// 2 - Complete a face
		// 3 - Complete 2nd row for all sides
		// 4 - Obtain desired shape on top side
		// 5 - Get center of each top side to be on the right color
		// 6 - Rotate corner pieces until they colors coincide.
		// 7 - Fix each corner
		// SOLVEEED
	return type;
}

int main() {
// Cube face representations (3x3 arrays for each face)
char** top = new char*[3];     // Top face of the cube
char** bot = new char*[3];     // Bottom face of the cube
char** sides = new char*[12];  // Side faces of the cube (4 sides x 3 rows)
// Game state
bool win = false;  // Flag indicating whether the cube is solved
// Solver mode options
enum SolverMode {
    USER = 0, // Manual solving by the user
    AUTO = 1  // Automatic solving by the program
};
// === Editable Parameters ===
// Number of random moves to scramble the cube at the start
int mixing = 2;
// Select the solving mode: USER for manual, AUTO for automatic solver
SolverMode solver = USER;

	initializeCube(top, bot, sides);

	mixCube(top, sides, bot, mixing);

	switch (solver)
	{
	case USER:
		while (!win) {
			char* type=new char[3];
			printCube(top, sides, bot);
			std::cout << "Move column (c+number+up/down) ex: c2u or Move row (r+number+right/left) ex: r1l";
			std::cout << std::endl;
			std::cout << "Move Cube m+right(r)left(l)up(u)down(d) ex: mr";
			std::cout<<std::endl;
			std::cin >> type;
			makeMove(top,sides,bot,type);
			win = gameOver(top, sides, bot);
		}
		break;
	case AUTO:
		while (!win) {
			char* type=new char[3];
			printCube(top, sides, bot);
			type = solver_nextMove();
			makeMove(top,sides,bot,type);
			win = gameOver(top, sides, bot);
		}
		break;
	default:
		break;
	}
	return 0;
}