#include <iostream>
#include <string>
#include <sstream>
#include <conio.h>

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

		void set_color(string color){
			if(color == white_piece_sign){
				character = '#';
				blank_or_not = color;
				existing_piece = true;
			}
			else if(color == black_piece_sign){
				character = '@';
				blank_or_not = color;
				existing_piece = true;
			}
			else{
				existing_piece = false;
				character = ' ';
				blank_or_not = color;
			}
		}

};


class Board { //@ - czarne, # - bia³e
public:
	Place board[8][8];

	Board() {
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (i % 2 == 0) {
					if (j % 2 == 0) {
						if (j < 3) {
							board[j][i].set_color("white");
						}
						else if (j > 4) {
							board[j][i].set_color("black");
						}
					}
				}
				else {
					if (j % 2 == 1) {
						if (j < 3) {
							board[j][i].set_color("white");
						}
						else if (j > 4) {
							board[j][i].set_color("black");
						}
					}
				}
			}
		}
	}

	void input(bool &white_turn) { //bool ma sprawdzac czy ruch sie wykonal
		char input[2];
		cout << "Wybierz pionek np.H3" << endl;
		input[0] = _getch();
		input[1] = _getch();
		if (input[0] >= 'A' && input[0] <= 'H' && //wybrane pole znajduje sie na szachownicy
			input[1] >= '1' && input[1] <= '8') {

			int x = input[0] - 'A';
			int y = input[1] - '1';
			Place temp = board[y][x];

			if (white_turn && temp.blank_or_not == white_piece_sign) { // white move
				if (places_to_go_white(temp, x, y, white_turn) != white_turn)
				{
					white_turn = false;
					gameBoard();
				}
			}
			else if (!white_turn && temp.blank_or_not == black_piece_sign) { // black move
				if (places_to_go_black(temp, x, y, white_turn) != white_turn)
					{
						white_turn = true;
						gameBoard();
					}
			}
			else{
				cout << "Podales niewlasciwe wspolrzedne :(" << endl;
			}
		}
		else {
				cout << "Podales niewlasciwe wspolrzedne :(" << endl;
		}
	}

	bool out_of_plane(int y, int x){
		if (x < 8 && x >= 0 && y < 8 && y >= 0) //kontrola skrajnych pol szachownicy
			return false;
		return true;
	}

	void piece_down(int x, int y, int x_2, int y_2){ //usuwanie pionka zbitego
		int x_to_kill = (x + x_2)/2;
		int y_to_kill = (y + y_2)/2; 
		board[y_to_kill][x_to_kill].set_color("blank");
	}

	bool places_to_go_white(Place temp, int x, int y, bool turn) {
		string places = "";
		bool move_available = false;
		bool another_move = false; //bicie wielokrotne
		do {
			move_available = false;
			places = "";

			if (temp.queen == false) {
				
					for (int i = -1; i <= 1; i += 2) {
						if (x + i < 8 && x + i >= 0 && y + 1 < 8) { //kontrola skrajnych pol szachownicy
							if (!board[y + 1][x + i].existing_piece && !another_move) { //sprawdza czy na danym polu jest pionek
								places += (char)(x + i + 'A');
								places += (char)(y + 1 + '1');
								places += ", ";
								move_available = true; another_move = false;
							}
							else if (board[y + 1][x + i].character != temp.character && board[y + 1][x + i].existing_piece) {
								//przeciwny kolor na nastepnym polu
								if (!out_of_plane(y + 2, x + 2 * i) && !board[y + 2][x + 2 * i].existing_piece) {
									places += (char)(x + 2 * i + 'A');
									places += (char)(y + 2 + '1');
									places += ", ";
									move_available = true; another_move = false;
								}
							}
							
						}
					}
				
				if (another_move && !move_available) 
					return !turn; 
				else if (!move_available)
					places = "Brak mozliwosci ruchu.";
				else {
					places.erase(places.end() - 2);
					turn = !turn;
				}
				
				if (places.size() > 5 and places.size() < 15)  
				{
					cout << " Jesli chcesz sie ruszyc na pole: " << places[0] << places[1] << " wcisnij 1 ,a jesli interesuje cie pole: " << places[4] << places[5] << " wybierz 2" << endl;
					int wybor;
					cin >> wybor;
					if (wybor == 1) {
						board[(int)(places[1] - '1')][(int)(places[0] - 'A')].set_color(white_piece_sign);
						board[y][x].set_color("blank");

						if (abs(y - (int)(places[1] - '1')) == 2 && abs(x - (int)(places[0] - 'A')) == 2) {//czy zbiles pionek
							piece_down(x, y, (int)(places[0] - 'A'), (int)(places[1] - '1'));
							
							y = (int)(places[1] - '1');
							x = (int)(places[0] - 'A');
							if(board[y+1][x+1].existing_piece==true && board[y + 1][x + 1].blank_or_not == black_piece_sign && board[y + 2][x + 2].existing_piece==false) //warunek na bicie wielokrotne
							{
							another_move = true;gameBoard();
							}
							else
							{
								if (board[y + 1][x - 1].existing_piece == true && board[y + 1][x - 1].blank_or_not == black_piece_sign && board[y + 2][x - 2].existing_piece == false)
								{
									another_move = true; gameBoard();
								}
								else {
									another_move = false;
									return !turn;
								}
							}
							

						}
					}
					else {
						board[(int)(places[5] - '1')][(int)(places[4] - 'A')].set_color(white_piece_sign);
						board[y][x].set_color("blank");

						if (abs(y - (int)(places[5] - '1')) == 2 && abs(x - (int)(places[4] - 'A')) == 2) { //bicie
							piece_down(x, y, (int)(places[4] - 'A'), (int)(places[5] - '1')); {
								
								y = (int)(places[1] - '1');
								x = (int)(places[0] - 'A');
								/*
									sprawdzanie czy na miejscu do bicia jest jakis pionek && sprawdzanie czy jest czarny && sprawdzanie czy pole do lądowania jest puste
								*/
								if (board[y + 1][x + 1].existing_piece == true && board[y + 1][x + 1].blank_or_not == black_piece_sign && board[y + 2][x + 2].existing_piece == false)  //warunek na bicie wielokrotne
								{
									another_move = true; gameBoard();
								}
								else
								{
									if (board[y + 1][x - 1].existing_piece == true && board[y + 1][x - 1].blank_or_not == black_piece_sign && board[y + 2][x - 2].existing_piece == false)
									{
										another_move = true; gameBoard();
									}
									else {
										another_move = false;
										return !turn;

									}
								}

							}
						}
					}
				}
				else {
					if (places.size() > 15)
					{
						cout << places; another_move = false;

					}
					else {
						cout << " Jesli chcesz sie ruszyc na pole: " << places[0] << places[1] << " wcisnij 1" << endl;
						int wybor;
						cin >> wybor;
						if (wybor == 1) {
							board[(int)(places[1] - '1')][(int)(places[0] - 'A')].set_color(white_piece_sign);
							board[y][x].set_color("blank");

							if (abs(y - (int)(places[1] - '1')) == 2 && abs(x - (int)(places[0] - 'A')) == 2) { //bicie
								piece_down(x, y, (int)(places[0] - 'A'), (int)(places[1] - '1'));
								
								y = (int)(places[1] - '1');
								x = (int)(places[0] - 'A');
								if (board[y + 1][x + 1].existing_piece == true && board[y + 1][x + 1].blank_or_not == black_piece_sign && board[y + 2][x + 2].existing_piece == false) //warunek na bicie wielokrotne
								{
									another_move = true; gameBoard();

								}
								else
								{
									if (board[y + 1][x - 1].existing_piece == true && board[y + 1][x - 1].blank_or_not == black_piece_sign && board[y + 2][x - 2].existing_piece == false)
									{
										another_move = true; gameBoard();
									}
									else {
										another_move = false;
										return !turn;

									}
								}

							}
						}
					}
				}
			}
			temp = board[y][x];
		} while (another_move);
		return turn;
	}

	bool places_to_go_black(Place temp, int x, int y, bool turn) {
		string places = "";
		bool move_available = false;
		if (temp.queen == false) { //sprawdza czy na danym polu jest pionek
			for (int i = -1; i <= 1; i += 2) {
				if (x + i < 8 && x + i >= 0 && y - 1 < 8) { //kontrola skrajnych pol szachownicy
					if (!board[y - 1][x + i].existing_piece) {
						places += (char)(x + i + 'A');
						places += (char)(y - 1 + '1');
						places += ", ";
						move_available = true;
					}
					
				}
			}
			
			if (!move_available)
			{
				places = "Brak mozliwosci ruchu.";
			}
			else
			{
				places.erase(places.end() - 2);
				turn = !turn;
			}
			
			if (places.size() > 5 and places.size()<15)
			{
				cout << " Jesli chcesz sie ruszyc na pole: " << places[0] << places[1] << " wcisnij 1 ,a jesli interesuje cie pole: " << places[4] << places[5] << " wybierz 2" << endl;
				int wybor;
				cin >> wybor;
				if (wybor == 1) {
					cout << (int)(places[1] - '1') << " " << (int)(places[0] - 'A');
					board[(int)(places[1] - '1')][(int)(places[0] - 'A')].set_color(black_piece_sign);
					board[y][x].set_color("blank");
				}
				else {
					board[(int)(places[5] - '1')][(int)(places[4] - 'A')].set_color(black_piece_sign);
					board[y][x].set_color("blank");
				}
			}
			else {
				if (places.size() > 15)
					cout << places;
				else {
					cout << " Jesli chcesz sie ruszyc na pole: " << places[0] << places[1] << " wcisnij 1" << endl;
					int wybor;
					cin >> wybor;
					if (wybor == 1);
					board[(int)(places[1] - '1')][(int)(places[0] - 'A')].set_color(black_piece_sign);
					board[y][x].set_color("blank");
				}
			}
		}
		return turn;
	}


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
	bool white_turnn = true;
public:
	Game(){
		Board board = Board();
		board.gameBoard();
		
		while(!win) {
			if (white_turnn)
			{
				board.input(white_turnn);
				
			}
			else
			{
				board.input(white_turnn);
			}
		}
	}
};

int main() {
	Game g1;
}