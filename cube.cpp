#include <iostream>
#include <random>
#include <cstring>

void initializeCube(char **top, char **bot, char **sides, int type){
	if (type == 0){
		for (int i = 0; i < 3; i++){
			top[i] = new char[3];
			bot[i] = new char[3];
			sides[i] = new char[12];
			for (int j = 0; j < 3; j++){
				top[i][j] = 'w';
				bot[i][j] = 'y';
				sides[i][j] = 'r';
				sides[i][j + 3] = 'b';
				sides[i][j + 6] = 'o';
				sides[i][j + 9] = 'g';
			}
		}
	}else if (type == 1) {
		top[0] = new char[3]{'w', 'w', 'o'};
		top[1] = new char[3]{'w', 'w', 'w'};
		top[2] = new char[3]{'y', 'w', 'b'};

		sides[0] = new char[12]{'o', 'r', 'r', 'y', 'o', 'g', 'w', 'g', 'g', 'r', 'b', 'g'};
		sides[1] = new char[12]{'r', 'b', 'r', 'b', 'o', 'o', 'g', 'g', 'b', 'y', 'r', 'y'};
		sides[2] = new char[12]{'g', 'r', 'b', 'r', 'o', 'o', 'y', 'y', 'w', 'o', 'o', 'y'};

		bot[0] = new char[3]{'r', 'g', 'w'};
		bot[1] = new char[3]{'b', 'y', 'y'};
		bot[2] = new char[3]{'b', 'g', 'b'};
	} else if (type == 5) {
		top[0] = new char[3]{'w', 'w', 'o'};
		top[1] = new char[3]{'w', 'w', 'w'};
		top[2] = new char[3]{'o', 'o', 'o'};

		sides[0] = new char[12]{'y', 'g', 'g', 'w', 'b', 'w', 'b', 'o', 'g', 'r', 'g', 'b'};
		sides[1] = new char[12]{'b', 'r', 'y', 'g', 'b', 'y', 'r', 'o', 'b', 'y', 'g', 'o'};
		sides[2] = new char[12]{'b', 'r', 'o', 'g', 'b', 'w', 'b', 'y', 'y', 'g', 'g', 'r'};

		bot[0] = new char[3]{'y', 'w', 'y'};
		bot[1] = new char[3]{'r', 'y', 'r'};
		bot[2] = new char[3]{'r', 'o', 'r'};
	}else if (type == 4) {
		top[0] = new char[3]{'w', 'w', 'o'};
		top[1] = new char[3]{'w', 'w', 'w'};
		top[2] = new char[3]{'o', 'y', 'o'};

		sides[0] = new char[12]{'y', 'o', 'g', 'w', 'b', 'w', 'b', 'o', 'g', 'r', 'g', 'b'};
		sides[1] = new char[12]{'b', 'r', 'y', 'g', 'b', 'y', 'r', 'o', 'b', 'y', 'g', 'o'};
		sides[2] = new char[12]{'g', 'o', 'r', 'b', 'b', 'o', 'g', 'r', 'w', 'b', 'w', 'y'};

		bot[0] = new char[3]{'r', 'g', 'y'};
		bot[1] = new char[3]{'r', 'y', 'r'};
		bot[2] = new char[3]{'r', 'g', 'y'};
	}else if (type == 3) {
		top[0] = new char[3]{'b', 'y', 'o'};
		top[1] = new char[3]{'r', 'g', 'o'};
		top[2] = new char[3]{'b', 'y', 'w'};
		bot[0] = new char[3]{'y', 'g', 'r'};
		bot[1] = new char[3]{'o', 'b', 'r'};
		bot[2] = new char[3]{'w', 'y', 'r'};
		sides[0] = new char[12]{'y', 'b', 'g', 'r', 'g', 'g', 'w', 'g', 'y', 'o', 'g', 'r'};
		sides[1] = new char[12]{'y', 'o', 'w', 'o', 'y', 'b', 'w', 'r', 'r', 'b', 'w', 'o'};
		sides[2] = new char[12]{'g', 'w', 'w', 'b', 'w', 'y', 'g', 'r', 'o', 'b', 'b', 'o'};
	}else if (type == 2) {
		top[0] = new char[3]{'g', 'w', 'r'};
		top[1] = new char[3]{'y', 'g', 'r'};
		top[2] = new char[3]{'y', 'y', 'o'};
		bot[0] = new char[3]{'y', 'g', 'y'};
		bot[1] = new char[3]{'y', 'b', 'o'};
		bot[2] = new char[3]{'b', 'b', 'w'};
		sides[0] = new char[12]{'b', 'b', 'y', 'g', 'b', 'b', 'w', 'r', 'w', 'o', 'o', 'o'};
		sides[1] = new char[12]{'r', 'w', 'o', 'w', 'o', 'b', 'w', 'y', 'g', 'y', 'r', 'g'};
		sides[2] = new char[12]{'b', 'w', 'g', 'r', 'g', 'r', 'g', 'o', 'w', 'o', 'r', 'r'};
	}
}
void printMat(char **matrix, int size){
	for (int i = 0; i < 3; i++)	{
		for (int j = 0; j < size; j++)
			std::cout << matrix[i][j] << " ";
		std::cout << std::endl;
	}
}
void changeRow(char **top, char **sides, char **bot, int row, char direction){
	char aux;
	if (direction == 'l'){
		for (int i = 0; i < 3; i++){
			aux = sides[row][i];
			sides[row][i] = sides[row][i + 3];
			sides[row][i + 3] = sides[row][i + 6];
			sides[row][i + 6] = sides[row][i + 9];
			sides[row][i + 9] = aux;
		}
	}else{
		for (int i = 0; i < 3; i++){
			aux = sides[row][i];
			sides[row][i] = sides[row][i + 9];
			sides[row][i + 9] = sides[row][i + 6];
			sides[row][i + 6] = sides[row][i + 3];
			sides[row][i + 3] = aux;
		}
	}
	if (row == 0 || row == 2){
		char **used = (row == 0) ? top : bot;
		char new_matrix[3][3];
		if ((direction == 'l' && row == 0) || (direction == 'r' && row == 2)){
			for (int i = 0; i < 3; i++){
				for (int j = 0; j < 3; j++)
					new_matrix[i][j] = used[2 - j][i];
			}
		}else{
			for (int i = 0; i < 3; i++){
				for (int j = 0; j < 3; j++)
					new_matrix[i][j] = used[j][2 - i];
			}
		}
		for (int i = 0; i < 3; i++){
			for (int j = 0; j < 3; j++){
				used[i][j] = new_matrix[i][j];
			}
		}
	}
}
void changeColumn(char **top, char **sides, char **bot, int column, char direction){
	char aux, aux2;
	int start;
	if (direction == 'u'){
		for (int i = 0; i < 3; i++){
			aux = top[i][column];
			top[i][column] = sides[i][column];
			sides[i][column] = bot[i][column];
			aux2 = sides[2 - i][8 - column];
			sides[2 - i][8 - column] = aux;
			bot[i][column] = aux2;
		}
	}else{
		for (int i = 0; i < 3; i++){
			aux = bot[i][column];
			bot[i][column] = sides[i][column];
			sides[i][column] = top[i][column];
			top[i][column] = sides[2 - i][8 - column];
			sides[2 - i][8 - column] = aux;
		}
	}
	if (column == 0 || column == 2){
		char new_matrix[3][3];
		if ((direction == 'd' && column == 0) || (direction == 'u' && column == 2)){
			start = column == 2 ? 3 : 9;
			for (int i = start; i < start + 3; i++){
				for (int j = 0; j < 3; j++)
					new_matrix[i - start][j] = sides[2 - j][i];
			}
		}else{
			start = column == 2 ? 3 : 9;
			for (int i = 0; i < 3; i++){
				for (int j = 0; j < 3; j++)
					new_matrix[i][j] = sides[j][2 - i + start];
			}
		}
		for (int i = 0; i < 3; i++){
			for (int j = 0; j < 3; j++)
				sides[i][j + start] = new_matrix[i][j];
		}
	}
}
void rotateCube(char **top, char **sides, char **bot, char type){
	switch (type){
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
void printCube(char **top, char **sides, char **bot){
	std::cout << "Cube" << std::endl;
	printMat(top, 3);
	printMat(sides, 12);
	printMat(bot, 3);
	std::cout << std::endl;
}
void makeMove(char **top, char **sides, char **bot, char type[]){
	switch (type[0]){
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
	printCube(top, sides, bot);
}
bool gameOver(char **top, char **sides, char **bot){
	char prevTop = top[0][0];
	char prevBot = bot[0][0];
	char prevSide1 = sides[0][0];
	char prevSide2 = sides[0][3];
	char prevSide3 = sides[0][6];
	char prevSide4 = sides[0][9];
	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 3; j++){
			if (top[i][j] != prevTop || bot[i][j] != prevBot)
				return false;
			if (sides[i][j] != prevSide1 || sides[i][j + 3] != prevSide2 || sides[i][j + 6] != prevSide3 || sides[i][j + 9] != prevSide4)
				return false;
		}
	}
	return true;
}
void mixCube(char **top, char **sides, char **bot, int iter){
	char *type = new char[3];
	for (int i = 0; i < iter; i++){
		int random = rand() % 2;
		type[0] = random == 0 ? 'c' : 'r';
		random = rand() % 3;
		type[1] = random + 48;
		random = rand() % 2;
		if (type[0] == 'c')
			type[2] = random == 0 ? 'u' : 'd';
		else
			type[2] = random == 0 ? 'l' : 'r';
		makeMove(top, sides, bot, type);
	}
}
void solver_nextMove(char **top, char **sides, char **bot){
	int i = 1;

	char center = '0';
	int piece_x = 0;
	int piece_y = 0;
	char pos = 't';
	// Steps (Idea)
	// 1 - Select random color to start
	// We will select the center color of the top face
	// For simplicity we will start by solving the cube in a specific way, where we always start
	// with white at the top yellow bottom, red blue orange green
	// 1.1 Place white center on top position
	if (top[1][1] != 'w'){
		if (bot[1][1] == 'w'){
			makeMove(top, sides, bot, strcpy(new char[3], "mu"));
			makeMove(top, sides, bot, strcpy(new char[3], "mu"));
		}else{
			if (sides[1][1] == 'w')
				makeMove(top, sides, bot, strcpy(new char[3], "mu"));
			else{
				for (i = 1; i < 4; i++){
					pos = sides[1][1 + (3 * i)];
					if (sides[1][1 + (3 * i)] == 'w'){
						for (int j = 0; j < i; j++)
							makeMove(top, sides, bot, strcpy(new char[3], "ml"));
						makeMove(top, sides, bot, strcpy(new char[3], "mu"));
						break;
					}
				}
			}
		}
	}
	// Strategy to solve first face of the cube . . .
	// 1.2 Place white cross on top face
	while (!(top[0][1] == 'w' && top[1][0] == 'w' && top[1][2] == 'w' && top[2][1] == 'w' && sides[0][1] == sides[1][1] && sides[0][4] == sides[1][4] && sides[0][7] == sides[1][7])){
		// Extreme case where all cross pieces are already in place but with the wrong centers
		if (top[0][1] == 'w' && top[1][0] == 'w' && top[1][2] == 'w' && top[2][1] == 'w'){
			// Find a wrong placed cross piece then continue with the normal evaluation
			if (sides[0][1] != sides[1][1]){
				makeMove(top,sides,bot,strcpy(new char[3], "ml"));
				makeMove(top,sides,bot,strcpy(new char[4], "c0d"));
				makeMove(top,sides,bot,strcpy(new char[4], "c0d"));
			}else if(sides[0][4] == sides[1][4]){
				makeMove(top,sides,bot,strcpy(new char[4], "c2d"));
				makeMove(top,sides,bot,strcpy(new char[4], "c2d"));
			}else if(sides[0][10] == sides[1][10]){
				makeMove(top,sides,bot,strcpy(new char[4], "c0d"));
				makeMove(top,sides,bot,strcpy(new char[4], "c0d"));
			}
		}
		// First Check if there are cross pieces at the bot face
		if (bot[0][1] == 'w' || bot[1][0] == 'w' || bot[1][2] == 'w' || bot[2][1] == 'w'){
			center = sides[2][1]; 			// Top
			if (bot[1][0] == 'w'){ 			// Left
				center = sides[2][4];
				makeMove(top,sides,bot,strcpy(new char[4], "r2r"));
			}else if (bot[1][2] == 'w'){ 	// Right
				center = sides[2][7];
				makeMove(top,sides,bot,strcpy(new char[4], "r2l"));
			}else if (bot[2][1] == 'w'){	// Bottom
				center = sides[2][10];
				makeMove(top,sides,bot,strcpy(new char[4], "r2l"));
				makeMove(top,sides,bot,strcpy(new char[4], "r2l"));
			}
			while (sides[1][1]!=center){
				makeMove(top,sides,bot,strcpy(new char[4], "r2r"));
				makeMove(top,sides,bot,strcpy(new char[3], "ml"));
			}
			makeMove(top,sides,bot,strcpy(new char[4], "c1d"));
			makeMove(top,sides,bot,strcpy(new char[4], "r2r"));
			makeMove(top,sides,bot,strcpy(new char[4], "r2r"));
			makeMove(top,sides,bot,strcpy(new char[4], "c1u"));
		}else{ // Lets check if there are cross pieces at the side faces
			for (i = 0; i < 11; i += 3){
				if (sides[0][i + 1] == 'w'){ 	// Top
					piece_x = 0;
					piece_y = i + 1;
					pos = 't';
					if (i == 0)
						center = top[2][1];
					else if (i == 3)
						center = top[1][2];
					else if (i == 6)
						center = top[0][1];
					else
						center = top[1][0];
					break;
				}
				if (sides[1][i] == 'w'){ 		// Left
					piece_x = 1;
					piece_y = i;
					pos = 'l';
					center = sides[1][(i + 11) % 12];
					break;
				}
				if (sides[1][i + 2] == 'w'){ 	// Right
					piece_x = 1;
					piece_y = i + 2;
					pos = 'r';
					center = sides[1][(i + 3) % 12];
					break;
				}
				if (sides[2][i + 1] == 'w'){ 	// Bottom
					piece_x = 2;
					piece_y = i + 1;
					pos = 'b';
					if (i == 0)
						center = bot[0][1];
					else if (i == 3)
						center = bot[1][2];
					else if (i == 6)
						center = bot[2][1];
					else
						center = bot[1][0];
					break;
				}
			}
			// Now decide moves to bring it to position
			while (piece_y>=3){			// First move target piece to bot and to do so first bring piece to front,
				makeMove(top,sides,bot,strcpy(new char[3], "ml"));
				piece_y-=3;
			}
			if (pos!='b'){
				makeMove(top,sides,bot,strcpy(new char[4], "c1u"));
				makeMove(top,sides,bot,strcpy(new char[3], "mr"));
				switch (pos){ // Move piece to bottom
					case 'l':
						makeMove(top,sides,bot,strcpy(new char[4], "c2d"));
						break;
					case 't':
						makeMove(top,sides,bot,strcpy(new char[4], "c2u"));
					case 'r':
						makeMove(top,sides,bot,strcpy(new char[4], "c2u"));
						break;
				}
				makeMove(top,sides,bot,strcpy(new char[3], "ml"));
				makeMove(top,sides,bot,strcpy(new char[4], "r2l"));
				makeMove(top,sides,bot,strcpy(new char[4], "c1d"));
				makeMove(top,sides,bot,strcpy(new char[4], "r2r"));
			}
			// Then check if current center is the targe center if not then rotate last row and move cube.
			while (sides[1][1] != center){
				makeMove(top,sides,bot,strcpy(new char[4], "r2r"));
				makeMove(top,sides,bot,strcpy(new char[3], "ml"));
			}
			// Finally we place it in the correct spot
			makeMove(top,sides,bot,strcpy(new char[3], "mr"));
			makeMove(top,sides,bot,strcpy(new char[4], "c0d"));
			makeMove(top,sides,bot,strcpy(new char[4], "c1d"));
			makeMove(top,sides,bot,strcpy(new char[3], "ml"));
			makeMove(top,sides,bot,strcpy(new char[4], "c1u"));
			makeMove(top,sides,bot,strcpy(new char[3], "mr"));
			makeMove(top,sides,bot,strcpy(new char[4], "c0u"));
			makeMove(top,sides,bot,strcpy(new char[4], "c1u"));
			makeMove(top,sides,bot,strcpy(new char[4], "r1l"));
		}
	}
	// 1.3 Place corner pieces on top face
	while (!(top[0][0] == 'w' && top[0][2] == 'w' && top[2][0] == 'w' && top[2][2] == 'w' && sides[0][0] == sides[1][1] && sides[0][2] == sides[1][1] && sides[0][3] == sides[1][4] && sides[0][5] == sides[1][4])){
		// Extreme case where all corner pieces are already in place but with the wrong centers
		if(top[0][0] == 'w' && top[0][2] == 'w' && top[2][0] == 'w' && top[2][2] == 'w'){
			//todo
		}
	}
	// 2 - Complete a face
	// In order to acomplish this we will start with the top, making a cross first
	// 3 - Complete 2nd row for all sides
	// 4 - Obtain desired shape on top side
	// 5 - Get center of each top side to be on the right color
	// 6 - Rotate corner pieces until they colors coincide.
	// 7 - Fix each corner
	// SOLVEEED
}

int main()
{
	// Cube face representations (3x3 arrays for each face)
	char **top = new char *[3];	  // Top face of the cube
	char **bot = new char *[3];	  // Bottom face of the cube
	char **sides = new char *[3]; // Side faces of the cube (4 sides x 3 rows)
	// Game state
	bool win = false; // Flag indicating whether the cube is solved
	// Solver mode options
	enum SolverMode
	{
		USER = 0, // Manual solving by the user
		AUTO = 1  // Automatic solving by the program
	};

	// === Editable Parameters ===
	// Number of random moves to scramble the cube at the start
	int mixing = 2;
	// Select the solving mode: USER for manual, AUTO for automatic solver
	SolverMode solver = AUTO;

	initializeCube(top, bot, sides, 3);

	// mixCube(top, sides, bot, mixing);
	// Hardcoded moves to test stuff
	// makeMove(top,sides,bot,(char*)"mu");
	// printCube(top, sides, bot);

	switch (solver)
	{
	case USER:
		while (!win)
		{
			char *type = new char[3];
			std::cout << "Move column (c+number+up/down) ex: c2u or Move row (r+number+right/left) ex: r1l";
			std::cout << std::endl;
			std::cout << "Move Cube m+right(r)left(l)up(u)down(d) ex: mr";
			std::cout << std::endl;
			std::cin >> type;
			makeMove(top, sides, bot, type);
			win = gameOver(top, sides, bot);
		}
		break;
	case AUTO:
		while (!win)
		{
			solver_nextMove(top, sides, bot);
			win = gameOver(top, sides, bot);
		}
		break;
	default:
		break;
	}
	return 0;
}