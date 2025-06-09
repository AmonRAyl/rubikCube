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
		top[0] = new char[3]{'g', 'r', 'o'};
		top[1] = new char[3]{'r', 'r', 'y'};
		top[2] = new char[3]{'b', 'g', 'b'};

		sides[0] = new char[12]{'y', 'o', 'w', 'r', 'b', 'g', 'w', 'w', 'o', 'y', 'y', 'r'};
		sides[1] = new char[12]{'g', 'y', 'g', 'r', 'b', 'w', 'o', 'w', 'o', 'y', 'g', 'w'};
		sides[2] = new char[12]{'g', 'o', 'y', 'g', 'g', 'o', 'y', 'b', 'w', 'o', 'b', 'r'};

		bot[0] = new char[3]{'w', 'b', 'r'};
		bot[1] = new char[3]{'r', 'o', 'y'};
		bot[2] = new char[3]{'b', 'w', 'b'};
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
void cube_solver(char **top, char **sides, char **bot){
	int i = 1;

	char center = '0';
	char center2 = '0';
	char avoid = '0';
	int piece_x = 0;
	int piece_y = 0;
	char pos = 't';
	bool found = false;
	printCube(top,sides,bot);
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
				center = sides[2][10];
				makeMove(top,sides,bot,strcpy(new char[4], "r2r"));
			}else if (bot[1][2] == 'w'){ 	// Right
				center = sides[2][4];
				makeMove(top,sides,bot,strcpy(new char[4], "r2l"));
			}else if (bot[2][1] == 'w'){	// Bottom
				center = sides[2][7];
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
	// 1.3 Place corner pieces on top face, completing the face
	while (!(top[0][0] == 'w' && top[0][2] == 'w' && top[2][0] == 'w' && top[2][2] == 'w' && sides[0][0] == sides[1][1] && sides[0][2] == sides[1][1] && sides[0][3] == sides[1][4] && sides[0][5] == sides[1][4])){
		// Extreme case where all corner pieces are already in place but with the wrong centers
		if(top[0][0] == 'w' && top[0][2] == 'w' && top[2][0] == 'w' && top[2][2] == 'w'){
			if(sides[0][0] != sides[1][1] || sides[0][11] != sides[1][10]){
				makeMove(top,sides,bot,strcpy(new char[4], "c0d"));
				makeMove(top,sides,bot,strcpy(new char[4], "r2r"));
				makeMove(top,sides,bot,strcpy(new char[4], "c0u"));
			}else if(sides[0][2] != sides[1][1] || sides[0][3] != sides[1][4]){
				makeMove(top,sides,bot,strcpy(new char[4], "c2d"));
				makeMove(top,sides,bot,strcpy(new char[4], "r2r"));
				makeMove(top,sides,bot,strcpy(new char[4], "c2u"));
			}else{
				makeMove(top,sides,bot,strcpy(new char[4], "c2u"));
				makeMove(top,sides,bot,strcpy(new char[4], "r2r"));
				makeMove(top,sides,bot,strcpy(new char[4], "c2d"));
			}
		}
		// Lets start by checking the bot
		if(bot[0][0] == 'w' || bot[0][2] == 'w' || bot[2][0] == 'w' || bot[2][2] == 'w'){
			center = sides[2][2];			// Top Right
			center2 = sides[2][3];
			piece_x = 0;
			piece_y = 2;
			if (bot[0][0] == 'w'){ 			// Top Left
				center = sides[2][11];
				center2 = sides[2][0];
				piece_x = 0;
				piece_y = 0;
			}else if (bot[2][0] == 'w'){ 	// Bottom Left
				center = sides[2][8];
				center2 = sides[2][9];
				piece_x = 2;
				piece_y = 0;
			}else if (bot[2][2] == 'w'){	// Bottom Right
				center = sides[2][5];
				center2 = sides[2][6];
				piece_x = 2;
				piece_y = 2;
			}
			while (bot[0][2]!='w' || sides[2][2]!=center || sides[2][3]!=center2)
				makeMove(top,sides,bot,strcpy(new char[3], "ml"));
			while (sides[1][4]!=center || sides[1][1]!=center2){
				makeMove(top,sides,bot,strcpy(new char[4], "r2r"));
				makeMove(top,sides,bot,strcpy(new char[3], "ml"));
			}
			makeMove(top,sides,bot,strcpy(new char[4], "c2d"));
			makeMove(top,sides,bot,strcpy(new char[4], "r2l"));
			makeMove(top,sides,bot,strcpy(new char[4], "r2l"));
			makeMove(top,sides,bot,strcpy(new char[4], "c2u"));
			makeMove(top,sides,bot,strcpy(new char[4], "r2r"));
			makeMove(top,sides,bot,strcpy(new char[4], "c2d"));
			makeMove(top,sides,bot,strcpy(new char[4], "r2l"));
			makeMove(top,sides,bot,strcpy(new char[4], "c2u"));
		}else{
			// Locate those that are on the bottom row
			for (i = 0; i < 11; i+=3){
				if (sides[2][i]=='w'){ // Bottom Left
					piece_x = 2;
					piece_y = (i+11) % 12;
					break;
				}
				if (sides[2][i+2]=='w'){ // Bottom right
					piece_x = 2;
					piece_y = (i+3) % 12;
					break;
				}
				if (sides[0][i]=='w'){ // Top Left
					piece_x = 0;
					piece_y = (i+11) % 12;
					break;
				}
				if (sides[0][i+2]=='w'){ // Top right
					piece_x = 0;
					piece_y = (i+3) % 12;
					break;
				}
			}
			// Place target piece in front
			while (piece_y>3){
				makeMove(top,sides,bot,strcpy(new char[3], "ml"));
				piece_y-=3;
			}
			// Now if it is in the 1st row move to 3d row
			if (piece_x==0){
				if (piece_y == 0){
					makeMove(top,sides,bot,strcpy(new char[4], "c0d"));
					makeMove(top,sides,bot,strcpy(new char[4], "r2r"));
					makeMove(top,sides,bot,strcpy(new char[4], "c0u"));
					makeMove(top,sides,bot,strcpy(new char[4], "r2l"));
				}else{
					makeMove(top,sides,bot,strcpy(new char[4], "c2d"));
					makeMove(top,sides,bot,strcpy(new char[4], "r2l"));
					makeMove(top,sides,bot,strcpy(new char[4], "c2u"));
					makeMove(top,sides,bot,strcpy(new char[4], "r2r"));
				}
				piece_x = 2;
			}
			// Make the target piece coincide with the center color
			while (sides[1][1]!=sides[piece_x][piece_y]){
				makeMove(top,sides,bot,strcpy(new char[4], "r2r"));
				makeMove(top,sides,bot,strcpy(new char[3], "ml"));
			}
			if(piece_y==0){
				makeMove(top,sides,bot,strcpy(new char[4], "c0d"));
				makeMove(top,sides,bot,strcpy(new char[4], "r2r"));
				makeMove(top,sides,bot,strcpy(new char[4], "c0u"));
			}else{
				makeMove(top,sides,bot,strcpy(new char[4], "c2d"));
				makeMove(top,sides,bot,strcpy(new char[4], "r2l"));
				makeMove(top,sides,bot,strcpy(new char[4], "c2u"));
			}
		}
	}
	// 2 - Complete 2nd row for all sides
	makeMove(top,sides,bot,strcpy(new char[3], "mu"));
	makeMove(top,sides,bot,strcpy(new char[3], "mu"));
	avoid = top[1][1];
	while (sides[1][0]!=sides[1][1] || sides[1][1]!=sides[1][2] || sides[1][3]!=sides[1][4] || sides[1][4]!=sides[1][5] || sides[1][6]!=sides[1][7] || sides[1][7]!=sides[1][8] || sides[1][9]!=sides[1][10] || sides[1][11]!=sides[1][10]){
		//Find center pieces without the top color (avoid)
		piece_x = 0;
		piece_y = 0;
		for (i = 1; i < 11; i+=3) {
			if (sides[0][i] == avoid) continue;

			if (i == 1)      { piece_x = 2; piece_y = 1; }
			else if (i == 4) { piece_x = 1; piece_y = 2; }
			else if (i == 7) { piece_x = 0; piece_y = 1; }
			else             { piece_x = 1; piece_y = 0; }

			if (top[piece_x][piece_y] != avoid) {
				piece_y = i;
				piece_x = 44; // Used to tell that we have found a target
				break;
			}
		}
		// This will take into account the case where the needed pieces are already placed in the wrong side
		if (piece_x!=44) {
			for (i = 0; i < 3; i++) {
				if(sides[1][0]!=sides[1][1]){
					makeMove(top,sides,bot,strcpy(new char[4], "r0r"));
					makeMove(top,sides,bot,strcpy(new char[4], "c0u"));
					makeMove(top,sides,bot,strcpy(new char[4], "r0l"));
					makeMove(top,sides,bot,strcpy(new char[4], "c0d"));
					makeMove(top,sides,bot,strcpy(new char[4], "r0l"));
					makeMove(top,sides,bot,strcpy(new char[4], "mr"));
					makeMove(top,sides,bot,strcpy(new char[4], "c2u"));
					makeMove(top,sides,bot,strcpy(new char[4], "r0r"));
					makeMove(top,sides,bot,strcpy(new char[4], "c2d"));
					break;
				}else if(sides[1][1]!=sides[1][2]){
					makeMove(top,sides,bot,strcpy(new char[4], "r0l"));
					makeMove(top,sides,bot,strcpy(new char[4], "c2u"));
					makeMove(top,sides,bot,strcpy(new char[4], "r0r"));
					makeMove(top,sides,bot,strcpy(new char[4], "c2d"));
					makeMove(top,sides,bot,strcpy(new char[4], "r0r"));
					makeMove(top,sides,bot,strcpy(new char[4], "ml"));
					makeMove(top,sides,bot,strcpy(new char[4], "c0u"));
					makeMove(top,sides,bot,strcpy(new char[4], "r0l"));
					makeMove(top,sides,bot,strcpy(new char[4], "c0d"));
					break;
				}else {
					makeMove(top,sides,bot,strcpy(new char[3], "ml"));
				}
			}
		}else{
			//Move target to front face
			while (piece_y>3){
				makeMove(top,sides,bot,strcpy(new char[3], "ml"));
				piece_y-=3;
			}
			//Make target be with its center
			while (sides[1][1]!=sides[0][1]){
				makeMove(top,sides,bot,strcpy(new char[4], "r0r"));
				makeMove(top,sides,bot,strcpy(new char[3], "ml"));
			}
			//Depending on top color do the moves to place it on the right or left
			if (top[2][1]==sides[1][4]){ // Move it to the right
				makeMove(top,sides,bot,strcpy(new char[4], "r0l"));
				makeMove(top,sides,bot,strcpy(new char[4], "c2u"));
				makeMove(top,sides,bot,strcpy(new char[4], "r0r"));
				makeMove(top,sides,bot,strcpy(new char[4], "c2d"));
				makeMove(top,sides,bot,strcpy(new char[4], "r0r"));
				makeMove(top,sides,bot,strcpy(new char[4], "ml"));
				makeMove(top,sides,bot,strcpy(new char[4], "c0u"));
				makeMove(top,sides,bot,strcpy(new char[4], "r0l"));
				makeMove(top,sides,bot,strcpy(new char[4], "c0d"));
			}else{ // Move it to the left
				makeMove(top,sides,bot,strcpy(new char[4], "r0r"));
				makeMove(top,sides,bot,strcpy(new char[4], "c0u"));
				makeMove(top,sides,bot,strcpy(new char[4], "r0l"));
				makeMove(top,sides,bot,strcpy(new char[4], "c0d"));
				makeMove(top,sides,bot,strcpy(new char[4], "r0l"));
				makeMove(top,sides,bot,strcpy(new char[4], "mr"));
				makeMove(top,sides,bot,strcpy(new char[4], "c2u"));
				makeMove(top,sides,bot,strcpy(new char[4], "r0r"));
				makeMove(top,sides,bot,strcpy(new char[4], "c2d"));
			}
		}
	}
	// 3 - Obtain desired shape on top side
	while (top[0][1]!=avoid || top[1][0]!=avoid || top[1][2]!=avoid || top[2][1]!=avoid){
		// First check if we have the line
		if((top[0][1]==avoid && top[2][1]==avoid) || (top[1][0]==avoid && top[1][2]==avoid)){
			if (top[1][0]==avoid && top[1][2]==avoid)
				makeMove(top,sides,bot,strcpy(new char[3], "mr"));
			makeMove(top,sides,bot,strcpy(new char[4], "c2u"));
			makeMove(top,sides,bot,strcpy(new char[3], "ml"));
			makeMove(top,sides,bot,strcpy(new char[4], "c2u"));
			makeMove(top,sides,bot,strcpy(new char[4], "r0l"));
			makeMove(top,sides,bot,strcpy(new char[4], "c2d"));
			makeMove(top,sides,bot,strcpy(new char[4], "r0r"));
			makeMove(top,sides,bot,strcpy(new char[3], "mr"));
			makeMove(top,sides,bot,strcpy(new char[4], "c2d"));
		}else {// You have no sides correctly placed
		if (top[0][1]!=avoid && top[1][0]!=avoid && top[1][2]!=avoid && top[2][1]!=avoid){
			makeMove(top,sides,bot,strcpy(new char[4], "c2u"));
			makeMove(top,sides,bot,strcpy(new char[3], "ml"));
			makeMove(top,sides,bot,strcpy(new char[4], "c2u"));
			makeMove(top,sides,bot,strcpy(new char[4], "r0l"));
			makeMove(top,sides,bot,strcpy(new char[4], "c2d"));
			makeMove(top,sides,bot,strcpy(new char[4], "r0r"));
			makeMove(top,sides,bot,strcpy(new char[3], "mr"));
			makeMove(top,sides,bot,strcpy(new char[4], "c2d"));
		}
		// You have a small L, L should be in bottom left from front side
		while (top[1][0]!=avoid || top[2][1]!=avoid)
			makeMove(top,sides,bot,strcpy(new char[4], "r0r"));
		makeMove(top,sides,bot,strcpy(new char[4], "c2u"));
		makeMove(top,sides,bot,strcpy(new char[3], "ml"));
		makeMove(top,sides,bot,strcpy(new char[4], "c2u"));
		makeMove(top,sides,bot,strcpy(new char[4], "r0l"));
		makeMove(top,sides,bot,strcpy(new char[4], "c2d"));
		makeMove(top,sides,bot,strcpy(new char[4], "r0r"));
		makeMove(top,sides,bot,strcpy(new char[3], "mr"));
		makeMove(top,sides,bot,strcpy(new char[4], "c2d"));
		}
	}
	// 4 - Get center of each top side to be on the right color
	while (sides[0][1]!=sides[1][1] || sides[0][4]!=sides[1][4] || sides[0][7]!=sides[1][7] || sides[0][10]!=sides[1][10] ){
		// Rotate first row until at least there are two correct sides
		while ((sides[0][1] == sides[1][1]) + (sides[0][4] == sides[1][4]) + (sides[0][7] == sides[1][7]) + (sides[0][10] == sides[1][10]) < 2)
			makeMove(top,sides,bot,strcpy(new char[4], "r0r"));
		// All correct, then break
		if ((sides[0][1] == sides[1][1]) + (sides[0][4] == sides[1][4]) + (sides[0][7] == sides[1][7]) + (sides[0][10] == sides[1][10]) == 4)
			break;
		//Otherwise we have two sides correctly placed, two options, 1) Two contiguous sides, 2) Two opposite sides
		if((sides[0][1]==sides[1][1])&&(sides[0][7]==sides[1][7])||(sides[0][4]==sides[1][4])&&(sides[0][10]==sides[1][10])){//Check opposite, its easier
			if((sides[0][1]==sides[1][1])&&(sides[0][7]==sides[1][7]))
				makeMove(top,sides,bot,strcpy(new char[3], "ml"));
			makeMove(top,sides,bot,strcpy(new char[4], "c2u"));
			makeMove(top,sides,bot,strcpy(new char[4], "r0l"));
			makeMove(top,sides,bot,strcpy(new char[4], "c2d"));
			makeMove(top,sides,bot,strcpy(new char[4], "r0l"));
			makeMove(top,sides,bot,strcpy(new char[4], "c2u"));
			makeMove(top,sides,bot,strcpy(new char[4], "r0l"));
			makeMove(top,sides,bot,strcpy(new char[4], "r0l"));
			makeMove(top,sides,bot,strcpy(new char[4], "c2d"));
		}
		// Look for what two contiguous sides are well placed , no else needed
		while ((sides[0][7]!=sides[1][7]) || (sides[0][4]!=sides[1][4]))
			makeMove(top,sides,bot,strcpy(new char[3], "ml"));
		makeMove(top,sides,bot,strcpy(new char[4], "c2u"));
		makeMove(top,sides,bot,strcpy(new char[4], "r0l"));
		makeMove(top,sides,bot,strcpy(new char[4], "c2d"));
		makeMove(top,sides,bot,strcpy(new char[4], "r0l"));
		makeMove(top,sides,bot,strcpy(new char[4], "c2u"));
		makeMove(top,sides,bot,strcpy(new char[4], "r0l"));
		makeMove(top,sides,bot,strcpy(new char[4], "r0l"));
		makeMove(top,sides,bot,strcpy(new char[4], "c2d"));
	}
	// 5 - Rotate corner pieces until they colors coincide.
	found = false;
	i=0;
	while (!(found && (i == 2 || i < 0))){ // Find one correct corner, or 2 correct corners
		if (top[2][0] == avoid){
			center = sides[0][0];
			center2 = sides[0][11];
		} else if (sides[0][0]==avoid){
			center = top[2][0];
			center2 = sides[0][11];
		} else{
			center = top[2][0];
			center2 = sides[0][0];
		}
		if (((center==sides[1][1])&&(center2==sides[1][10]))||((center==sides[1][11])&&(center2==sides[1][1]))){
			found = true;
			piece_y = 11;
			i++;
		}else
			i-=2;
		makeMove(top,sides,bot,strcpy(new char[3],"mr"));
		piece_y+=3;
		if (i==-8){ // All corners are incorrect
			makeMove(top,sides,bot,strcpy(new char[4], "r0l"));
			makeMove(top,sides,bot,strcpy(new char[4], "c2u"));
			makeMove(top,sides,bot,strcpy(new char[4], "r0r"));
			makeMove(top,sides,bot,strcpy(new char[4], "c0u"));
			makeMove(top,sides,bot,strcpy(new char[4], "r0l"));
			makeMove(top,sides,bot,strcpy(new char[4], "c2d"));
			makeMove(top,sides,bot,strcpy(new char[4], "r0r"));
			makeMove(top,sides,bot,strcpy(new char[4], "c0d"));
			i=0;
		}
	}
	if (i!=2){ // Not all corners are well placed
		piece_y=piece_y%12;
		while ( piece_y!=2){
			makeMove(top,sides,bot,strcpy(new char[3],"ml"));
			piece_y-=3;
		}
		do {
			makeMove(top,sides,bot,strcpy(new char[4], "r0l"));
			makeMove(top,sides,bot,strcpy(new char[4], "c2u"));
			makeMove(top,sides,bot,strcpy(new char[4], "r0r"));
			makeMove(top,sides,bot,strcpy(new char[4], "c0u"));
			makeMove(top,sides,bot,strcpy(new char[4], "r0l"));
			makeMove(top,sides,bot,strcpy(new char[4], "c2d"));
			makeMove(top,sides,bot,strcpy(new char[4], "r0r"));
			makeMove(top,sides,bot,strcpy(new char[4], "c0d"));
			if (top[2][0] == avoid){
				center = sides[0][0];
				center2 = sides[0][11];
			} else if (sides[0][0]==avoid){
				center = top[2][0];
				center2 = sides[0][11];
			} else{
				center = top[2][0];
				center2 = sides[0][0];
			}
		} while (!((center==sides[1][1])&&(center2==sides[1][10])) && !((center==sides[1][11])&&(center2==sides[1][1])));
	}	
	// First look for the one that is already in place
	// 6 - Fix each corner
	while (top[0][0]!=top[1][1] || top[0][2]!=top[1][1] || top[2][0]!=top[1][1] || top[2][2]!=top[1][1]){
		while (top[2][2]!=top[1][1]){
			makeMove(top,sides,bot,strcpy(new char[4], "c2d"));
			makeMove(top,sides,bot,strcpy(new char[4], "r2l"));
			makeMove(top,sides,bot,strcpy(new char[4], "c2u"));
			makeMove(top,sides,bot,strcpy(new char[4], "r2r"));
		}
		makeMove(top,sides,bot,strcpy(new char[4], "r0r"));
	}
	// 7 - Solved, put each row with its center
	while (sides[0][0]!=sides[1][1]) // I dont really know if there are more options at the end
		makeMove(top,sides,bot,strcpy(new char[4], "r0r"));
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
	int mixing = 2;	// Number of random moves to scramble the cube at the start

	SolverMode solver = AUTO;	// Select the solving mode: USER for manual, AUTO for automatic solver

	initializeCube(top, bot, sides, 1); // Select starting position, 0 is a solved cube, 1 is a random position, add more if needed

	// mixCube(top, sides, bot, mixing);

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
		while (!win){
			cube_solver(top, sides, bot);
			win = gameOver(top, sides, bot);
		}
		break;
	}
	system("Pause");
	return 0;
}