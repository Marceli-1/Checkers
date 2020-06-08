#include <iostream>
#include <string>
#include<sstream>
#include<conio.h>
using namespace std;

const string black_piece_sign = "black";
const string white_piece_sign = "white";

const int shape = 8;

class Place {
	public: 
		char character = 0;
		string blank_or_not = "blank";
		bool queen = false;
		bool existing_piece = false;
};


class Board { //@ - czarne, # - bia³e
public:
	Place board[8][8];

	//	{64, 00 ,64, 00 ,64, 00 ,64, 00},
	//	{00 ,64, 00 ,64, 00 ,64, 00, 64},
	//	{64, 00 ,64, 00 ,64, 00 ,64, 00},
	//	{00, 00, 00, 00, 00, 00, 00, 00},
	//	{00, 00, 00, 00, 00, 00, 00, 00},
	//	{00, 35, 00, 35, 00, 35, 00, 35},
	//	{35, 00, 35, 00, 35, 00, 35, 00},
	//	{00, 35, 00, 35, 00, 35, 00, 35},


	Board(){
		for(int i = 0; i < 8; i++){
			for(int j=0; j < 8; j++){
				if(i % 2 == 0){
					if(j % 2 == 0) {
						if(j < 3){
							board[j][i].character = '#';
							board[j][i].blank_or_not = "white";
						}
						else if (j > 4){
							board[j][i].character = '@';
							board[j][i].blank_or_not = "black";
						}
					}
				}
				else{
					if(j % 2 == 1) {
						if(j < 3){
							board[j][i].character = '#';
							board[j][i].blank_or_not = "white";
						}
						else if (j > 4){
							board[j][i].character = '@';
							board[j][i].blank_or_not = "black";
						}
					}
				}
			}
		}
	}

	void input(bool white_turn) {
		char input[2];
		cout << "Wybierz pionek np.H3" << endl;
		input[0] = _getch();
		input[1] = _getch();
		if (input[0] >= 'A' && input[0] <= 'H' &&
			input[1] >= '1' && input[1] <= '8') {

			int x = input[0] - 'A';
			int y = input[1] - '1';
			cout << input[0] << input[1] << endl;
			cout << x << " " << y << endl;
			Place temp = board[y][x];

			if (white_turn && temp.blank_or_not == white_piece_sign) { // white move
				places_to_go(temp, x, y);

			}
			else if (!white_turn && temp.blank_or_not == black_piece_sign) { // black move
				
			}
		}
		else {
				cout << "Podales niewlasciwe wspolrzedne :(" << endl;
		}
	}

	void places_to_go(Place temp, int x, int y){
		int k;
		stringstream ss;
		string places,s;
		if(temp.queen == false){
			if (temp.blank_or_not == white_piece_sign)
				k = y + 1;
			ss << k;
			ss >> s;
			cout << s + s;
		}
	}

	//void move_piece(char input[2]) {
	//	if (blank_or_not == black_piece_sign) {

	//	}
	//}

	void output(){
		for(int i = 7; i >= 0; i--){
			for(int j = 0; j < 8; j++){

				cout << board[i][j].character << " ";
			}
			cout << endl;
		}	
		char x;
		for(int i = 0; i < 8; i++){
			x = 'A'+ i;
			cout << x<< " ";
		}
	}

	void gameBoard() // Drukuje pelna szachownice wraz z pionkami
	{
		unsigned char upright = 191;
		unsigned char leftdown = 192;
		unsigned char downcentre = 193;
		unsigned char upcentre = 194;
		unsigned char leftcentre = 195;
		unsigned char updown = 196;
		unsigned char centre = 197;

		unsigned char rightdown = 217;
		unsigned char upleft = 218;
		unsigned char stick = 179;
		unsigned char rightcentre = 180;

		cout << " " << upcentre << updown << updown << updown;
		for (int i = 0; i < 7; i++)
		{
			cout << upcentre << updown << updown << updown;
		}
		cout << upright << endl;

		int j = 8; // nr szachownicy
		for (int k = 7; k >= 0; k--)
		{
			cout << j << stick;
			for (int i = 0; i <8 ; i++)
			{
				cout << " " << board[k][i].character << " " << stick;
			}
			cout << endl;

			cout << " " << centre << updown << updown << updown;
			for (int i = 0; i < 7; i++)
			{
				cout << centre << updown << updown << updown;
			}
			cout << rightcentre << endl;
			j--;
		}
		cout << "   A   B   C   D   E   F   G   H" << endl << endl;
	}
};

class Game {
	bool win = false;
	bool white_turn = true;
public:

	Game(){
		Board board = Board();
		board.gameBoard();
		
		while(!win) {
			if(white_turn)
				board.input(white_turn);
			break;

		}
	}
};

int main() {

	Game g1;
}
