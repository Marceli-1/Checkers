#include <iostream>
#include <string>
using namespace std;

class Place {
	public: 
		char character = 0;
		string blank_or_not = "blank";
		bool existing_piece = false;
};


class Board {
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
							board[j][i].character = '@';
							board[j][i].blank_or_not = "white";
						}
						else if (j > 4){
							board[j][i].character = '#';
							board[j][i].blank_or_not = "black";
						}
					}
				}
				else{
					if(j % 2 == 1) {
						if(j < 3){
							board[j][i].character = '@';
							board[j][i].blank_or_not = "white";
						}
						else if (j > 4){
							board[j][i].character = '#';
							board[j][i].blank_or_not = "black";
						}
					}
				}
			}
		}
	}

	void output(){
		for(int i = 0; i < 8; i++){
			for(int j = 0; j < 8; j++){
				cout << board[i][j].character << " ";
			}
			cout << endl;
		}	
	}
};


class Game {
public:
	Game(){
		Board board = Board();
		board.output();
	}
};

int main() {
	Game g1;
	cout << "test";
}

