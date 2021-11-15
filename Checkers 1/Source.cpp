#include <iostream>
#include <string>
#include <conio.h> // system("cls")
#include <Windows.h> //sleep

using namespace std;

const string black_piece_sign = "black";
const string white_piece_sign = "white";
const string whitequeen_piece_sign = "whitequeen";
const string blackqueen_piece_sign = "blackqueen";
const int shape = 8;
int time_fail = 500; // czas przerwy po zlym wybraniu pola

class Place {
public:
	char character = 0;
	string blank_or_not = "blank";
	bool queen = false;
	bool existing_piece = false;

	void set_color(string color) { //ustawianie odpowiednich symboli na planszy
		if (color == white_piece_sign) {
			character = '#';
			blank_or_not = color;
			existing_piece = true;
		}
		else if (color == black_piece_sign) {
			character = '@';
			blank_or_not = color;
			existing_piece = true;
		}
		else if (color == whitequeen_piece_sign) {
			character = '%';
			blank_or_not = color;
			existing_piece = true;
		}
		else if (color == blackqueen_piece_sign) {
			character = '^';
			blank_or_not = color;
			existing_piece = true;
		}
		else {
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

	void input(bool& white_turn) { //bool ma sprawdzac czy ruch sie wykonal
		char input[2];
		

		if(white_turn)
			cout << endl << "Jest ruch bialych # " << endl;
		else
			cout << endl << "Jest ruch czarnych @ " << endl;
		cout << "Wybierz pionek np.H3" << endl;
		input[0] = _getch();
		input[1] = _getch();
		if (input[0] >= 'A' && input[0] <= 'H' && //wybrane pole znajduje sie na szachownicy
			input[1] >= '1' && input[1] <= '8') {

			int x = input[0] - 'A';
			int y = input[1] - '1';
			Place temp = board[y][x];

			if ((white_turn && temp.blank_or_not == white_piece_sign) or (white_turn && temp.blank_or_not == whitequeen_piece_sign )) { // white move
				if (places_to_go_white(temp, x, y, white_turn) != white_turn)
				{
					white_turn = false; 
					//ardard();
				}
			}
			else if ((!white_turn && temp.blank_or_not == black_piece_sign)or (!white_turn && temp.blank_or_not == blackqueen_piece_sign)) { // black move
				if (places_to_go_black(temp, x, y, white_turn) != white_turn)
				{
					white_turn = true;
					//gameBoard();
				}
			}
			else {
				cout << "Podales niewlasciwe wspolrzedne :(" << endl;
				Sleep(time_fail);
			}
		}
		else {
			cout << "Podales niewlasciwe wspolrzedne :(" << endl;
			Sleep(time_fail);
		}
	}

	bool out_of_plane(int y, int x) {
		if (x < 8 && x >= 0 && y < 8 && y >= 0) //kontrola skrajnych pol szachownicy
			return false;
		return true;
	}

	void piece_down(int x, int y, int x_2, int y_2) { //usuwanie pionka zbitego
		int x_to_kill = (x + x_2) / 2;
		int y_to_kill = (y + y_2) / 2;
		board[y_to_kill][x_to_kill].set_color("blank");
	}

	bool places_to_go_white(Place temp, int x, int y, bool turn) {
		
		string places = ""; //najwazniejszy string w klasie, jego rozmiar i poszczegolne elementy odpowiadaja za poruszanie sie, np places[0] i places[1] moze odpowiadac lokacji B3
		bool move_available = false;
		bool another_move = false; //bicie wielokrotne
		do {
			gameBoard();
			move_available = false;
			places = ""; 

			if (temp.queen == false) 
			{

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
								move_available = true; //another_move = false;
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

				}

				if (places.size() > 5 and places.size() < 15)
				{
					cout << " Jesli chcesz sie ruszyc na pole: " << places[0] << places[1] << " wcisnij 1 ,a jesli interesuje cie pole: " << places[4] << places[5] << " wybierz 2" << endl;
					int wybor;
					cin >> wybor;
					if (wybor == 1) {
						if (places[1] - '1' == 7)
						{
							board[(int)(places[1] - '1')][(int)(places[0] - 'A')].set_color(whitequeen_piece_sign);
							board[(int)(places[1] - '1')][(int)(places[0] - 'A')].queen = true;
						}
						else
							board[(int)(places[1] - '1')][(int)(places[0] - 'A')].set_color(white_piece_sign);
						board[y][x].set_color("blank");


						if (abs(y - (int)(places[1] - '1')) == 2 && abs(x - (int)(places[0] - 'A')) == 2) {//czy zbiles pionek
							piece_down(x, y, (int)(places[0] - 'A'), (int)(places[1] - '1'));

							y = (int)(places[1] - '1'); x = (int)(places[0] - 'A');
							
							if (board[y + 1][x + 1].existing_piece == true && board[y + 1][x + 1].blank_or_not == black_piece_sign && board[y + 2][x + 2].existing_piece == false) //warunek na bicie wielokrotne
							{
								another_move = true; //gameBoard();
							}
							else
							{
								if (board[y + 1][x - 1].existing_piece == true && board[y + 1][x - 1].blank_or_not == black_piece_sign && board[y + 2][x - 2].existing_piece == false)
								{
									another_move = true; //gameBoard();
								}
								else {
									another_move = false;
									return !turn;
								}
							}


						}
					}
					else {
						if (places[5] - '1' == 7)
						{
							board[(int)(places[5] - '1')][(int)(places[4] - 'A')].set_color(whitequeen_piece_sign);
							board[(int)(places[5] - '1')][(int)(places[4] - 'A')].queen = true;
						}
						else
							board[(int)(places[5] - '1')][(int)(places[4] - 'A')].set_color(white_piece_sign);
						board[y][x].set_color("blank");

						if (abs(y - (int)(places[5] - '1')) == 2 && abs(x - (int)(places[4] - 'A')) == 2) { //bicie
							piece_down(x, y, (int)(places[4] - 'A'), (int)(places[5] - '1')); {

								y = (int)(places[1] - '1'); x = (int)(places[0] - 'A');
								
								if (board[y + 1][x + 1].existing_piece == true && board[y + 1][x + 1].blank_or_not == black_piece_sign && board[y + 2][x + 2].existing_piece == false)  //warunek na bicie wielokrotne
								{
									another_move = true; //gameBoard();
								}
								else
								{
									if (board[y + 1][x - 1].existing_piece == true && board[y + 1][x - 1].blank_or_not == black_piece_sign && board[y + 2][x - 2].existing_piece == false)
									{
										another_move = true; //gameBoard();
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
							if (places[1] - '1' == 7)
							{
								board[(int)(places[1] - '1')][(int)(places[0] - 'A')].set_color(whitequeen_piece_sign);
								board[(int)(places[1] - '1')][(int)(places[0] - 'A')].queen = true;
							}
							else
								board[(int)(places[1] - '1')][(int)(places[0] - 'A')].set_color(white_piece_sign);
							board[y][x].set_color("blank");

							if (abs(y - (int)(places[1] - '1')) == 2 && abs(x - (int)(places[0] - 'A')) == 2) { //bicie
								piece_down(x, y, (int)(places[0] - 'A'), (int)(places[1] - '1'));

								y = (int)(places[1] - '1'); x = (int)(places[0] - 'A');
								

								if (board[y + 1][x + 1].existing_piece == true && board[y + 1][x + 1].blank_or_not == black_piece_sign && board[y + 2][x + 2].existing_piece == false) //warunek na bicie wielokrotne
								{
									another_move = true; 

								}
								else
								{
									if (board[y + 1][x - 1].existing_piece == true && board[y + 1][x - 1].blank_or_not == black_piece_sign && board[y + 2][x - 2].existing_piece == false)
									{
										another_move = true; 
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
			else {
			for (int i = -1; i <= 1; i += 2) {
				cout << "p" <<places.size()<< endl;
					if (x + i < 8 && x + i >= 0 && y + i < 8 && y + i >= 0) { //kontrola skrajnych pol szachownicy
						if (!board[y + i][x + i].existing_piece && !another_move) { //sprawdza czy na danym polu jest pionek
							places += (char)(x + i + 'A');
							places += (char)(y + i + '1');
							places += ", ";
							cout << places << endl;
							move_available = true; another_move = false;
						}
						else if (board[y + i][x + i].character != '%' and board[y + i][x + i].character != '#' && board[y + i][x + i].existing_piece) {
							//przeciwny kolor na nastepnym polu
							if (!out_of_plane(y + 2 * i, x + 2 * i) && !board[y + 2 * i][x + 2 * i].existing_piece) {
								places += (char)(x + 2 * i + 'A');
								places += (char)(y + 2 * i + '1');
								places += ", "; cout << places << endl;
								move_available = true; another_move = false;
							}
						}
						if (!board[y - i][x + i].existing_piece && !another_move) { //sprawdza czy na danym polu jest pionek
							places += (char)(x + i + 'A');
							places += (char)(y - i + '1');
							places += ", "; cout << places << endl;
							move_available = true; another_move = false;
						}
						else if (board[y - i][x + i].character != '%' and board[y - i][x + i].character != '#' && board[y - i][x + i].existing_piece) {
							//przeciwny kolor na nastepnym polu
							if (!out_of_plane(y - 2 * i, x + 2 * i) && !board[y - 2 * i][x + 2 * i].existing_piece) {
								places += (char)(x + 2 * i + 'A');
								places += (char)(y - 2 * i + '1');
								places += ", "; cout << places << endl;
								move_available = true; 
							}
						}

					}
					
				}

				if (another_move && !move_available)
					return !turn;
				else if (!move_available)
					places = "Brak mozliwosci ruchu krolowej.";
				else {
					places.erase(places.end() - 2);

				}
				cout << places.size()<<endl;
				if (places.size() ==7)
				{
					cout << " Jesli chcesz sie ruszyc na pole: " << places[0] << places[1] << " wcisnij 1 ,a jesli interesuje cie pole: " << places[4] << places[5] << " wybierz 2" << endl;
					int wybor;
					cin >> wybor;
					if (wybor == 1) {
						board[(int)(places[1] - '1')][(int)(places[0] - 'A')].set_color(whitequeen_piece_sign);
						board[(int)(places[1] - '1')][(int)(places[0] - 'A')].queen = true;
						board[y][x].set_color("blank"); board[y][x].existing_piece = false; board[y][x].queen = false;

						if (abs(y - (int)(places[1] - '1')) == 2 && abs(x - (int)(places[0] - 'A')) == 2) {//czy zbiles pionek
							piece_down(x, y, (int)(places[0] - 'A'), (int)(places[1] - '1'));

							y = (int)(places[1] - '1');
							x = (int)(places[0] - 'A');
							if (board[y + 1][x + 1].existing_piece == true && board[y + 1][x + 1].blank_or_not == black_piece_sign && board[y + 2][x + 2].existing_piece == false) //warunek na bicie wielokrotne
							{
								another_move = true; 
							}
							else
							{
								if (board[y + 1][x - 1].existing_piece == true && board[y + 1][x - 1].blank_or_not == black_piece_sign && board[y + 2][x - 2].existing_piece == false)
								{
									another_move = true; 
								}
								else {
									if (board[y - 1][x + 1].existing_piece == true && board[y - 1][x + 1].blank_or_not == black_piece_sign && board[y - 2][x + 2].existing_piece == false) //warunek na bicie wielokrotne
									{
										another_move = true; 
									}
									else
									{
										if (board[y - 1][x + 1].existing_piece == true && board[y - 1][x + 1].blank_or_not == black_piece_sign && board[y - 2][x + 2].existing_piece == false) //warunek na bicie wielokrotne
										{
											another_move = true; 
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
						board[(int)(places[5] - '1')][(int)(places[4] - 'A')].set_color(whitequeen_piece_sign);
						board[(int)(places[5] - '1')][(int)(places[4] - 'A')].queen = true;
						board[y][x].set_color("blank"); board[y][x].existing_piece = false; board[y][x].queen = false;

							if (abs(y - (int)(places[5] - '1')) == 2 && abs(x - (int)(places[4] - 'A')) == 2) { //bicie
								piece_down(x, y, (int)(places[4] - 'A'), (int)(places[5] - '1'));

								y = (int)(places[5] - '1');
								x = (int)(places[4] - 'A');
								/*
									sprawdzanie czy na miejscu do bicia jest jakis pionek && sprawdzanie czy jest czarny && sprawdzanie czy pole do lądowania jest puste
								*/
								if (board[y + 1][x + 1].existing_piece == true && board[y + 1][x + 1].blank_or_not == black_piece_sign && board[y + 2][x + 2].existing_piece == false) //warunek na bicie wielokrotne
								{
									another_move = true; 
								}
								else
								{
									if (board[y + 1][x - 1].existing_piece == true && board[y + 1][x - 1].blank_or_not == black_piece_sign && board[y + 2][x - 2].existing_piece == false)
									{
										another_move = true; 
									}
									else
									{
										if (board[y - 1][x + 1].existing_piece == true && board[y - 1][x + 1].blank_or_not == black_piece_sign && board[y - 2][x + 2].existing_piece == false) //warunek na bicie wielokrotne
										{
											another_move = true; 
										}
										else
										{
											if (board[y - 1][x + 1].existing_piece == true && board[y - 1][x + 1].blank_or_not == black_piece_sign && board[y - 2][x + 2].existing_piece == false) //warunek na bicie wielokrotne
											{
												another_move = true; 
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
				else {
					if (places.size() == 3)
					{
						cout << " Jesli chcesz sie ruszyc na pole: " << places[0] << places[1] << " wcisnij 1" << endl;
						int wybor;
						cin >> wybor;
						if (wybor == 1) {
							board[(int)(places[1] - '1')][(int)(places[0] - 'A')].set_color(whitequeen_piece_sign);
							board[(int)(places[1] - '1')][(int)(places[0] - 'A')].queen = true;
							board[y][x].set_color("blank"); board[y][x].existing_piece = false; board[y][x].queen = false;

							if (abs(y - (int)(places[1] - '1')) == 2 && abs(x - (int)(places[0] - 'A')) == 2) { //bicie
								piece_down(x, y, (int)(places[0] - 'A'), (int)(places[1] - '1'));

								y = (int)(places[1] - '1');
								x = (int)(places[0] - 'A');
								if (board[y + 1][x + 1].existing_piece == true && board[y + 1][x + 1].blank_or_not == black_piece_sign && board[y + 2][x + 2].existing_piece == false) //warunek na bicie wielokrotne
								{
									another_move = true; 
								}
								else
								{
									if (board[y + 1][x - 1].existing_piece == true && board[y + 1][x - 1].blank_or_not == black_piece_sign && board[y + 2][x - 2].existing_piece == false)
									{
										another_move = true; 
									}
									else
									{
										if (board[y - 1][x + 1].existing_piece == true && board[y - 1][x + 1].blank_or_not == black_piece_sign && board[y - 2][x + 2].existing_piece == false) //warunek na bicie wielokrotne
										{
											another_move = true; 
										}
										else
										{
											if (board[y - 1][x + 1].existing_piece == true && board[y - 1][x + 1].blank_or_not == black_piece_sign && board[y - 2][x + 2].existing_piece == false) //warunek na bicie wielokrotne
											{
												another_move = true; 
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
					else
					{
						if (places.size() == 11)
						{
							cout << " Jesli chcesz sie ruszyc na pole: " << places[0] << places[1] << " wcisnij 1 ,a jesli interesuje cie pole: " << places[4] << places[5] << " wybierz 2, a jesli jednak chcesz na pole: " << places[8] << places[9] << " wcisnij 3" << endl;
							int wybor;
							cin >> wybor;
							if (wybor == 1) {
								board[(int)(places[1] - '1')][(int)(places[0] - 'A')].set_color(whitequeen_piece_sign);
								board[(int)(places[1] - '1')][(int)(places[0] - 'A')].queen = true;
								board[y][x].set_color("blank"); board[y][x].existing_piece = false; board[y][x].queen = false;

								if (abs(y - (int)(places[1] - '1')) == 2 && abs(x - (int)(places[0] - 'A')) == 2) {//czy zbiles pionek
									piece_down(x, y, (int)(places[0] - 'A'), (int)(places[1] - '1'));

									y = (int)(places[1] - '1');
									x = (int)(places[0] - 'A');
									if (board[y + 1][x + 1].existing_piece == true && board[y + 1][x + 1].blank_or_not == black_piece_sign && board[y + 2][x + 2].existing_piece == false) //warunek na bicie wielokrotne
									{
										another_move = true; 
									}
									else
									{
										if (board[y + 1][x - 1].existing_piece == true && board[y + 1][x - 1].blank_or_not == black_piece_sign && board[y + 2][x - 2].existing_piece == false)
										{
											another_move = true; 
										}
										else {
											if (board[y - 1][x + 1].existing_piece == true && board[y - 1][x + 1].blank_or_not == black_piece_sign && board[y - 2][x + 2].existing_piece == false) //warunek na bicie wielokrotne
											{
												another_move = true; 
											}
											else
											{
												if (board[y - 1][x + 1].existing_piece == true && board[y - 1][x + 1].blank_or_not == black_piece_sign && board[y - 2][x + 2].existing_piece == false) //warunek na bicie wielokrotne
												{
													another_move = true; 
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
								if (wybor == 2) {
									board[(int)(places[5] - '1')][(int)(places[4] - 'A')].set_color(whitequeen_piece_sign);
									board[(int)(places[5] - '1')][(int)(places[4] - 'A')].queen = true;
									board[y][x].set_color("blank"); board[y][x].existing_piece = false; board[y][x].queen = false;

									if (abs(y - (int)(places[5] - '1')) == 2 && abs(x - (int)(places[4] - 'A')) == 2) { //bicie
										piece_down(x, y, (int)(places[4] - 'A'), (int)(places[5] - '1'));

										y = (int)(places[5] - '1');
										x = (int)(places[4] - 'A');
										/*
											sprawdzanie czy na miejscu do bicia jest jakis pionek && sprawdzanie czy jest czarny && sprawdzanie czy pole do lądowania jest puste
										*/
										if (board[y + 1][x + 1].existing_piece == true && board[y + 1][x + 1].blank_or_not == black_piece_sign && board[y + 2][x + 2].existing_piece == false) //warunek na bicie wielokrotne
										{
											another_move = true; 
										}
										else
										{
											if (board[y + 1][x - 1].existing_piece == true && board[y + 1][x - 1].blank_or_not == black_piece_sign && board[y + 2][x - 2].existing_piece == false)
											{
												another_move = true; 
											}
											else
											{
												if (board[y - 1][x + 1].existing_piece == true && board[y - 1][x + 1].blank_or_not == black_piece_sign && board[y - 2][x + 2].existing_piece == false) //warunek na bicie wielokrotne
												{
													another_move = true; 
												}
												else
												{
													if (board[y - 1][x + 1].existing_piece == true && board[y - 1][x + 1].blank_or_not == black_piece_sign && board[y - 2][x + 2].existing_piece == false) //warunek na bicie wielokrotne
													{
														another_move = true; 
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
									board[(int)(places[9] - '1')][(int)(places[8] - 'A')].set_color(whitequeen_piece_sign);
									board[(int)(places[9] - '1')][(int)(places[8] - 'A')].queen = true;
									board[y][x].set_color("blank"); board[y][x].existing_piece = false; board[y][x].queen = false;

									if (abs(y - (int)(places[9] - '1')) == 2 && abs(x - (int)(places[8] - 'A')) == 2) { //bicie
										piece_down(x, y, (int)(places[8] - 'A'), (int)(places[9] - '1'));

										y = (int)(places[9] - '1');
										x = (int)(places[8] - 'A');
										/*
											sprawdzanie czy na miejscu do bicia jest jakis pionek && sprawdzanie czy jest czarny && sprawdzanie czy pole do lądowania jest puste
										*/
										if (board[y + 1][x + 1].existing_piece == true && board[y + 1][x + 1].blank_or_not == black_piece_sign && board[y + 2][x + 2].existing_piece == false) //warunek na bicie wielokrotne
										{
											another_move = true;
										}
										else
										{
											if (board[y + 1][x - 1].existing_piece == true && board[y + 1][x - 1].blank_or_not == black_piece_sign && board[y + 2][x - 2].existing_piece == false)
											{
												another_move = true; 
											}
											else
											{
												if (board[y - 1][x + 1].existing_piece == true && board[y - 1][x + 1].blank_or_not == black_piece_sign && board[y - 2][x + 2].existing_piece == false) //warunek na bicie wielokrotne
												{
													another_move = true; 
												}
												else
												{
													if (board[y - 1][x + 1].existing_piece == true && board[y - 1][x + 1].blank_or_not == black_piece_sign && board[y - 2][x + 2].existing_piece == false) //warunek na bicie wielokrotne
													{
														another_move = true; 
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
						}
						else
						{
						if (places.size() == 15) 
						{
							cout << " Jesli chcesz sie ruszyc na pole: " << places[0] << places[1] << " wcisnij 1 ,a jesli interesuje cie pole: " << places[4] << places[5] << " wybierz 2, a jesli jednak chcesz na pole: " << places[8] << places[9] << " wcisnij 3, a jak zdecydujesz sie na pole: " <<places[12]<<places[13]<<" wybierz 4" << endl;
							int wybor;
							cin >> wybor;
							if (wybor == 1) {
								board[(int)(places[1] - '1')][(int)(places[0] - 'A')].set_color(whitequeen_piece_sign);
								board[(int)(places[1] - '1')][(int)(places[0] - 'A')].queen = true;
								board[y][x].set_color("blank"); board[y][x].existing_piece = false; board[y][x].queen = false;

								if (abs(y - (int)(places[1] - '1')) == 2 && abs(x - (int)(places[0] - 'A')) == 2) {//czy zbiles pionek
									piece_down(x, y, (int)(places[0] - 'A'), (int)(places[1] - '1'));

									y = (int)(places[1] - '1');
									x = (int)(places[0] - 'A');
									if (board[y + 1][x + 1].existing_piece == true && board[y + 1][x + 1].blank_or_not == black_piece_sign && board[y + 2][x + 2].existing_piece == false) //warunek na bicie wielokrotne
									{
										another_move = true;
									}
									else
									{
										if (board[y + 1][x - 1].existing_piece == true && board[y + 1][x - 1].blank_or_not == black_piece_sign && board[y + 2][x - 2].existing_piece == false)
										{
											another_move = true; 
										}
										else {
											if (board[y - 1][x + 1].existing_piece == true && board[y - 1][x + 1].blank_or_not == black_piece_sign && board[y - 2][x + 2].existing_piece == false) //warunek na bicie wielokrotne
											{
												another_move = true; 
											}
											else
											{
												if (board[y - 1][x + 1].existing_piece == true && board[y - 1][x + 1].blank_or_not == black_piece_sign && board[y - 2][x + 2].existing_piece == false) //warunek na bicie wielokrotne
												{
													another_move = true;
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
								if (wybor == 2) 
								{
									board[(int)(places[5] - '1')][(int)(places[4] - 'A')].set_color(whitequeen_piece_sign);
									board[(int)(places[5] - '1')][(int)(places[4] - 'A')].queen = true;
									board[y][x].set_color("blank"); board[y][x].existing_piece = false; board[y][x].queen = false;

									if (abs(y - (int)(places[5] - '1')) == 2 && abs(x - (int)(places[4] - 'A')) == 2) { //bicie
										piece_down(x, y, (int)(places[4] - 'A'), (int)(places[5] - '1'));

										y = (int)(places[5] - '1');
										x = (int)(places[4] - 'A');
										/*
											sprawdzanie czy na miejscu do bicia jest jakis pionek && sprawdzanie czy jest czarny && sprawdzanie czy pole do lądowania jest puste
										*/
										if (board[y + 1][x + 1].existing_piece == true && board[y + 1][x + 1].blank_or_not == black_piece_sign && board[y + 2][x + 2].existing_piece == false) //warunek na bicie wielokrotne
										{
											another_move = true;
										}
										else
										{
											if (board[y + 1][x - 1].existing_piece == true && board[y + 1][x - 1].blank_or_not == black_piece_sign && board[y + 2][x - 2].existing_piece == false)
											{
												another_move = true;
											}
											else
											{
												if (board[y - 1][x + 1].existing_piece == true && board[y - 1][x + 1].blank_or_not == black_piece_sign && board[y - 2][x + 2].existing_piece == false) //warunek na bicie wielokrotne
												{
													another_move = true;
												}
												else
												{
													if (board[y - 1][x + 1].existing_piece == true && board[y - 1][x + 1].blank_or_not == black_piece_sign && board[y - 2][x + 2].existing_piece == false) //warunek na bicie wielokrotne
													{
														another_move = true;
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
									if (wybor == 3)
									{
										board[(int)(places[9] - '1')][(int)(places[8] - 'A')].set_color(whitequeen_piece_sign);
										board[(int)(places[9] - '1')][(int)(places[8] - 'A')].queen = true;
										board[y][x].set_color("blank"); board[y][x].existing_piece = false; board[y][x].queen = false;

										if (abs(y - (int)(places[9] - '1')) == 2 && abs(x - (int)(places[8] - 'A')) == 2) { //bicie
											piece_down(x, y, (int)(places[8] - 'A'), (int)(places[9] - '1'));

											y = (int)(places[9] - '1');
											x = (int)(places[8] - 'A');
											/*
												sprawdzanie czy na miejscu do bicia jest jakis pionek && sprawdzanie czy jest czarny && sprawdzanie czy pole do lądowania jest puste
											*/
											if (board[y + 1][x + 1].existing_piece == true && board[y + 1][x + 1].blank_or_not == black_piece_sign && board[y + 2][x + 2].existing_piece == false) //warunek na bicie wielokrotne
											{
												another_move = true;
											}
											else
											{
												if (board[y + 1][x - 1].existing_piece == true && board[y + 1][x - 1].blank_or_not == black_piece_sign && board[y + 2][x - 2].existing_piece == false)
												{
													another_move = true;
												}
												else
												{
													if (board[y - 1][x + 1].existing_piece == true && board[y - 1][x + 1].blank_or_not == black_piece_sign && board[y - 2][x + 2].existing_piece == false) //warunek na bicie wielokrotne
													{
														another_move = true;
													}
													else
													{
														if (board[y - 1][x + 1].existing_piece == true && board[y - 1][x + 1].blank_or_not == black_piece_sign && board[y - 2][x + 2].existing_piece == false) //warunek na bicie wielokrotne
														{
															another_move = true;
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
									else
									{
										board[(int)(places[13] - '1')][(int)(places[12] - 'A')].set_color(whitequeen_piece_sign);
										board[(int)(places[13] - '1')][(int)(places[12] - 'A')].queen = true;
										board[y][x].set_color("blank"); board[y][x].existing_piece = false; board[y][x].queen = false;

										if (abs(y - (int)(places[13] - '1')) == 2 && abs(x - (int)(places[12] - 'A')) == 2) { //bicie
											piece_down(x, y, (int)(places[12] - 'A'), (int)(places[13] - '1'));

											y = (int)(places[13] - '1');
											x = (int)(places[12] - 'A');
											/*
												sprawdzanie czy na miejscu do bicia jest jakis pionek && sprawdzanie czy jest czarny && sprawdzanie czy pole do lądowania jest puste
											*/
											if (board[y + 1][x + 1].existing_piece == true && board[y + 1][x + 1].blank_or_not == black_piece_sign && board[y + 2][x + 2].existing_piece == false) //warunek na bicie wielokrotne
											{
												another_move = true;
											}
											else
											{
												if (board[y + 1][x - 1].existing_piece == true && board[y + 1][x - 1].blank_or_not == black_piece_sign && board[y + 2][x - 2].existing_piece == false)
												{
													another_move = true;
												}
												else
												{
													if (board[y - 1][x + 1].existing_piece == true && board[y - 1][x + 1].blank_or_not == black_piece_sign && board[y - 2][x + 2].existing_piece == false) //warunek na bicie wielokrotne
													{
														another_move = true;
													}
													else
													{
														if (board[y - 1][x + 1].existing_piece == true && board[y - 1][x + 1].blank_or_not == black_piece_sign && board[y - 2][x + 2].existing_piece == false) //warunek na bicie wielokrotne
														{
															another_move = true;
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
						}
				}
			}
						}
				}
			
			
}temp = board[y][x];
		} while (another_move);
		return !turn;
	}

	bool places_to_go_black(Place temp, int x, int y, bool turn) {
		
		string places = "";
		bool move_available = false;
		bool another_move = false; //bicie wielokrotne
		do {
			gameBoard();
			move_available = false;
			places = "";

			if (temp.queen == false) {

				for (int i = -1; i <= 1; i += 2) {
					if (x + i < 8 && x + i >= 0 && y - 1 >= 0) { //kontrola skrajnych pol szachownicy
						if (!board[y - 1][x + i].existing_piece && !another_move) { //sprawdza czy na danym polu jest pionek
							places += (char)(x + i + 'A');
							places += (char)(y - 1 + '1');
							places += ", ";
							move_available = true; another_move = false;
						}
						else if (board[y - 1][x + i].character != temp.character && board[y - 1][x + i].existing_piece) {
							//przeciwny kolor na nastepnym polu
							if (!out_of_plane(y - 2, x + 2 * i) && !board[y - 2][x + 2 * i].existing_piece) {
								places += (char)(x + 2 * i + 'A');
								places += (char)(y - 2 + '1');
								places += ", ";
								move_available = true; //another_move = false;
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

				}

				if (places.size() > 5 and places.size() < 15)
				{
					cout << " Jesli chcesz sie ruszyc na pole: " << places[0] << places[1] << " wcisnij 1 ,a jesli interesuje cie pole: " << places[4] << places[5] << " wybierz 2" << endl;
					int wybor;
					cin >> wybor;
					if (wybor == 1) {
						if (places[1] - '1' == 0)
						{
							board[(int)(places[1] - '1')][(int)(places[0] - 'A')].set_color(blackqueen_piece_sign);
							board[(int)(places[1] - '1')][(int)(places[0] - 'A')].queen = true;
						}
						else
						board[(int)(places[1] - '1')][(int)(places[0] - 'A')].set_color(black_piece_sign);
						board[y][x].set_color("blank"); board[y][x].existing_piece = false;

						if (abs(y - (int)(places[1] - '1')) == 2 && abs(x - (int)(places[0] - 'A')) == 2) {//czy zbiles pionek
							piece_down(x, y, (int)(places[0] - 'A'), (int)(places[1] - '1'));

							y = (int)(places[1] - '1');
							x = (int)(places[0] - 'A');
							if (board[y - 1][x + 1].existing_piece == true && board[y - 1][x + 1].blank_or_not == white_piece_sign && board[y - 2][x + 2].existing_piece == false) //warunek na bicie wielokrotne
							{
								another_move = true; //gameBoard();
							}
							else
							{
								if (board[y - 1][x - 1].existing_piece == true && board[y - 1][x - 1].blank_or_not == white_piece_sign && board[y - 2][x - 2].existing_piece == false)
								{
									another_move = true; //gameBoard();
								}
								else {
									another_move = false;
									return !turn;
								}
							}


						}
					}
					else {
						if (places[5] - '1' == 0)
						{
							board[(int)(places[5] - '1')][(int)(places[4] - 'A')].set_color(blackqueen_piece_sign);
							board[(int)(places[5] - '1')][(int)(places[4] - 'A')].queen = true;
						}
						else
						board[(int)(places[5] - '1')][(int)(places[4] - 'A')].set_color(black_piece_sign);
						board[y][x].set_color("blank"); board[y][x].existing_piece = false;

						if (abs(y - (int)(places[5] - '1')) == 2 && abs(x - (int)(places[4] - 'A')) == 2) { //bicie
							piece_down(x, y, (int)(places[4] - 'A'), (int)(places[5] - '1')); {

								y = (int)(places[1] - '1');
								x = (int)(places[0] - 'A');
								/*
									sprawdzanie czy na miejscu do bicia jest jakis pionek && sprawdzanie czy jest czarny && sprawdzanie czy pole do lądowania jest puste
								*/
								if (board[y - 1][x + 1].existing_piece == true && board[y - 1][x + 1].blank_or_not == white_piece_sign && board[y - 2][x + 2].existing_piece == false)  //warunek na bicie wielokrotne
								{
									another_move = true; //gameBoard();
								}
								else
								{
									if (board[y - 1][x - 1].existing_piece == true && board[y - 1][x - 1].blank_or_not == white_piece_sign && board[y - 2][x - 2].existing_piece == false)
									{
										another_move = true; //gameBoard();
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
							if (places[1] - '1' == 0)
							{
								board[(int)(places[1] - '1')][(int)(places[0] - 'A')].set_color(blackqueen_piece_sign);
								board[(int)(places[1] - '1')][(int)(places[0] - 'A')].queen = true;
							}
							else
							board[(int)(places[1] - '1')][(int)(places[0] - 'A')].set_color(black_piece_sign);
							board[y][x].set_color("blank"); board[y][x].existing_piece = false;

							if (abs(y - (int)(places[1] - '1')) == 2 && abs(x - (int)(places[0] - 'A')) == 2) { //bicie
								piece_down(x, y, (int)(places[0] - 'A'), (int)(places[1] - '1'));

								y = (int)(places[1] - '1');
								x = (int)(places[0] - 'A');
								if (board[y - 1][x + 1].existing_piece == true && board[y - 1][x + 1].blank_or_not == white_piece_sign && board[y - 2][x + 2].existing_piece == false) //warunek na bicie wielokrotne
								{
									another_move = true; //gameBoard();

								}
								else
								{
									if (board[y - 1][x - 1].existing_piece == true && board[y - 1][x - 1].blank_or_not == white_piece_sign && board[y - 2][x - 2].existing_piece == false)
									{
										another_move = true; //gameBoard();
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
			}else {
			for (int i = -1; i <= 1; i += 2) {
				if (x + i < 8 && x + i >= 0 && y + i < 8 && y + i >= 0) { //kontrola skrajnych pol szachownicy
					if (!board[y + i][x + i].existing_piece && !another_move) { //sprawdza czy na danym polu jest pionek
						places += (char)(x + i + 'A');
						places += (char)(y + i + '1');
						places += ", ";
						
						move_available = true; another_move = false;
					}
					else if (board[y + i][x + i].character != '@' and board[y + i][x + i].character != '^'  && board[y + i][x + i].existing_piece) {
						//przeciwny kolor na nastepnym polu
						if (!out_of_plane(y + 2 * i, x + 2 * i) && !board[y + 2 * i][x + 2 * i].existing_piece) {
							places += (char)(x + 2 * i + 'A');
							places += (char)(y + 2 * i + '1');
							places += ", "; 
							move_available = true; another_move = false;
						}
					}
					if (!board[y - i][x + i].existing_piece && !another_move) { //sprawdza czy na danym polu jest pionek
						places += (char)(x + i + 'A');
						places += (char)(y - i + '1');
						places += ", "; 
						move_available = true; another_move = false;
					}
					else if (board[y - i][x + i].character != '@' and board[y - i][x + i].character != '^'&& board[y - i][x + i].existing_piece) {
						//przeciwny kolor na nastepnym polu
						if (!out_of_plane(y - 2 * i, x + 2 * i) && !board[y - 2 * i][x + 2 * i].existing_piece) {
							places += (char)(x + 2 * i + 'A');
							places += (char)(y - 2 * i + '1');
							places += ", "; 
							move_available = true;
						}
					}

				}

			}

			if (another_move && !move_available)
				return !turn;
			else if (!move_available)
				places = "Brak mozliwosci ruchu krolowej.";
			else {
				places.erase(places.end() - 2);

			}
			
			if (places.size() == 7)
			{
				cout << " Jesli chcesz sie ruszyc na pole: " << places[0] << places[1] << " wcisnij 1 ,a jesli interesuje cie pole: " << places[4] << places[5] << " wybierz 2" << endl;
				int wybor;
				cin >> wybor;
				if (wybor == 1) {
					board[(int)(places[1] - '1')][(int)(places[0] - 'A')].set_color(blackqueen_piece_sign);
					board[(int)(places[1] - '1')][(int)(places[0] - 'A')].queen = true;
					board[y][x].set_color("blank"); board[y][x].existing_piece = false; board[y][x].queen = false;

					if (abs(y - (int)(places[1] - '1')) == 2 && abs(x - (int)(places[0] - 'A')) == 2) {//czy zbiles pionek
						piece_down(x, y, (int)(places[0] - 'A'), (int)(places[1] - '1'));

						y = (int)(places[1] - '1');
						x = (int)(places[0] - 'A');
						if (board[y + 1][x + 1].existing_piece == true && board[y + 1][x + 1].blank_or_not == white_piece_sign && board[y + 2][x + 2].existing_piece == false) //warunek na bicie wielokrotne
						{
							another_move = true;
						}
						else
						{
							if (board[y + 1][x - 1].existing_piece == true && board[y + 1][x - 1].blank_or_not == white_piece_sign && board[y + 2][x - 2].existing_piece == false)
							{
								another_move = true;
							}
							else {
								if (board[y - 1][x + 1].existing_piece == true && board[y - 1][x + 1].blank_or_not == white_piece_sign && board[y - 2][x + 2].existing_piece == false) //warunek na bicie wielokrotne
								{
									another_move = true;
								}
								else
								{
									if (board[y - 1][x + 1].existing_piece == true && board[y - 1][x + 1].blank_or_not == white_piece_sign && board[y - 2][x + 2].existing_piece == false) //warunek na bicie wielokrotne
									{
										another_move = true;
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
					board[(int)(places[5] - '1')][(int)(places[4] - 'A')].set_color(blackqueen_piece_sign);
					board[(int)(places[5] - '1')][(int)(places[4] - 'A')].queen = true;
					board[y][x].set_color("blank"); board[y][x].existing_piece = false; board[y][x].queen = false;

					if (abs(y - (int)(places[5] - '1')) == 2 && abs(x - (int)(places[4] - 'A')) == 2) { //bicie
						piece_down(x, y, (int)(places[4] - 'A'), (int)(places[5] - '1'));

						y = (int)(places[5] - '1');
						x = (int)(places[4] - 'A');
						/*
							sprawdzanie czy na miejscu do bicia jest jakis pionek && sprawdzanie czy jest czarny && sprawdzanie czy pole do lądowania jest puste
						*/
						if (board[y + 1][x + 1].existing_piece == true && board[y + 1][x + 1].blank_or_not == white_piece_sign && board[y + 2][x + 2].existing_piece == false) //warunek na bicie wielokrotne
						{
							another_move = true;
						}
						else
						{
							if (board[y + 1][x - 1].existing_piece == true && board[y + 1][x - 1].blank_or_not == white_piece_sign && board[y + 2][x - 2].existing_piece == false)
							{
								another_move = true;
							}
							else
							{
								if (board[y - 1][x + 1].existing_piece == true && board[y - 1][x + 1].blank_or_not == white_piece_sign && board[y - 2][x + 2].existing_piece == false) //warunek na bicie wielokrotne
								{
									another_move = true;
								}
								else
								{
									if (board[y - 1][x + 1].existing_piece == true && board[y - 1][x + 1].blank_or_not == white_piece_sign && board[y - 2][x + 2].existing_piece == false) //warunek na bicie wielokrotne
									{
										another_move = true;
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
			else {
				if (places.size() == 3)
				{
					cout << " Jesli chcesz sie ruszyc na pole: " << places[0] << places[1] << " wcisnij 1" << endl;
					int wybor;
					cin >> wybor;
					if (wybor == 1) {
						board[(int)(places[1] - '1')][(int)(places[0] - 'A')].set_color(blackqueen_piece_sign);
						board[(int)(places[1] - '1')][(int)(places[0] - 'A')].queen = true;
						board[y][x].set_color("blank"); board[y][x].existing_piece = false; board[y][x].queen = false;

						if (abs(y - (int)(places[1] - '1')) == 2 && abs(x - (int)(places[0] - 'A')) == 2) { //bicie
							piece_down(x, y, (int)(places[0] - 'A'), (int)(places[1] - '1'));

							y = (int)(places[1] - '1');
							x = (int)(places[0] - 'A');
							if (board[y + 1][x + 1].existing_piece == true && board[y + 1][x + 1].blank_or_not == white_piece_sign && board[y + 2][x + 2].existing_piece == false) //warunek na bicie wielokrotne
							{
								another_move = true;
							}
							else
							{
								if (board[y + 1][x - 1].existing_piece == true && board[y + 1][x - 1].blank_or_not == white_piece_sign && board[y + 2][x - 2].existing_piece == false)
								{
									another_move = true;
								}
								else
								{
									if (board[y - 1][x + 1].existing_piece == true && board[y - 1][x + 1].blank_or_not == white_piece_sign && board[y - 2][x + 2].existing_piece == false) //warunek na bicie wielokrotne
									{
										another_move = true;
									}
									else
									{
										if (board[y - 1][x + 1].existing_piece == true && board[y - 1][x + 1].blank_or_not == white_piece_sign && board[y - 2][x + 2].existing_piece == false) //warunek na bicie wielokrotne
										{
											another_move = true;
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
				else
				{
					if (places.size() == 11) // poruszanie sie damki gdy ma 3 opcje ruchu
					{
						cout << " Jesli chcesz sie ruszyc na pole: " << places[0] << places[1] << " wcisnij 1 ,a jesli interesuje cie pole: " << places[4] << places[5] << " wybierz 2, a jesli jednak chcesz na pole: " << places[8] << places[9] << " wcisnij 3" << endl;
						int wybor;
						cin >> wybor;
						if (wybor == 1) {
							board[(int)(places[1] - '1')][(int)(places[0] - 'A')].set_color(blackqueen_piece_sign);
							board[(int)(places[1] - '1')][(int)(places[0] - 'A')].queen = true;
							board[y][x].set_color("blank"); board[y][x].existing_piece = false; board[y][x].queen = false;

							if (abs(y - (int)(places[1] - '1')) == 2 && abs(x - (int)(places[0] - 'A')) == 2) {//czy zbiles pionek
								piece_down(x, y, (int)(places[0] - 'A'), (int)(places[1] - '1'));

								y = (int)(places[1] - '1');
								x = (int)(places[0] - 'A');
								if (board[y + 1][x + 1].existing_piece == true && board[y + 1][x + 1].blank_or_not == white_piece_sign && board[y + 2][x + 2].existing_piece == false) //warunek na bicie wielokrotne
								{
									another_move = true;
								}
								else
								{
									if (board[y + 1][x - 1].existing_piece == true && board[y + 1][x - 1].blank_or_not == white_piece_sign && board[y + 2][x - 2].existing_piece == false)
									{
										another_move = true;
									}
									else {
										if (board[y - 1][x + 1].existing_piece == true && board[y - 1][x + 1].blank_or_not == white_piece_sign && board[y - 2][x + 2].existing_piece == false) //warunek na bicie wielokrotne
										{
											another_move = true;
										}
										else
										{
											if (board[y - 1][x + 1].existing_piece == true && board[y - 1][x + 1].blank_or_not == white_piece_sign && board[y - 2][x + 2].existing_piece == false) //warunek na bicie wielokrotne
											{
												another_move = true;
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
							if (wybor == 2) {
								board[(int)(places[5] - '1')][(int)(places[4] - 'A')].set_color(blackqueen_piece_sign);
								board[(int)(places[5] - '1')][(int)(places[4] - 'A')].queen = true;
								board[y][x].set_color("blank"); board[y][x].existing_piece = false; board[y][x].queen = false;

								if (abs(y - (int)(places[5] - '1')) == 2 && abs(x - (int)(places[4] - 'A')) == 2) { //bicie
									piece_down(x, y, (int)(places[4] - 'A'), (int)(places[5] - '1'));

									y = (int)(places[5] - '1');
									x = (int)(places[4] - 'A');
									/*
										sprawdzanie czy na miejscu do bicia jest jakis pionek && sprawdzanie czy jest czarny && sprawdzanie czy pole do lądowania jest puste
									*/
									if (board[y + 1][x + 1].existing_piece == true && board[y + 1][x + 1].blank_or_not == white_piece_sign && board[y + 2][x + 2].existing_piece == false) //warunek na bicie wielokrotne
									{
										another_move = true;
									}
									else
									{
										if (board[y + 1][x - 1].existing_piece == true && board[y + 1][x - 1].blank_or_not == white_piece_sign && board[y + 2][x - 2].existing_piece == false)
										{
											another_move = true;
										}
										else
										{
											if (board[y - 1][x + 1].existing_piece == true && board[y - 1][x + 1].blank_or_not == white_piece_sign && board[y - 2][x + 2].existing_piece == false) //warunek na bicie wielokrotne
											{
												another_move = true;
											}
											else
											{
												if (board[y - 1][x + 1].existing_piece == true && board[y - 1][x + 1].blank_or_not == white_piece_sign && board[y - 2][x + 2].existing_piece == false) //warunek na bicie wielokrotne
												{
													another_move = true;
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
								board[(int)(places[9] - '1')][(int)(places[8] - 'A')].set_color(blackqueen_piece_sign);
								board[(int)(places[9] - '1')][(int)(places[8] - 'A')].queen = true;
								board[y][x].set_color("blank"); board[y][x].existing_piece = false; board[y][x].queen = false;

								if (abs(y - (int)(places[9] - '1')) == 2 && abs(x - (int)(places[8] - 'A')) == 2) { //bicie
									piece_down(x, y, (int)(places[8] - 'A'), (int)(places[9] - '1'));

									y = (int)(places[9] - '1');
									x = (int)(places[8] - 'A');
									/*
										sprawdzanie czy na miejscu do bicia jest jakis pionek && sprawdzanie czy jest czarny && sprawdzanie czy pole do lądowania jest puste
									*/
									if (board[y + 1][x + 1].existing_piece == true && board[y + 1][x + 1].blank_or_not == white_piece_sign && board[y + 2][x + 2].existing_piece == false) //warunek na bicie wielokrotne
									{
										another_move = true;
									}
									else
									{
										if (board[y + 1][x - 1].existing_piece == true && board[y + 1][x - 1].blank_or_not == white_piece_sign && board[y + 2][x - 2].existing_piece == false)
										{
											another_move = true;
										}
										else
										{
											if (board[y - 1][x + 1].existing_piece == true && board[y - 1][x + 1].blank_or_not == white_piece_sign && board[y - 2][x + 2].existing_piece == false) //warunek na bicie wielokrotne
											{
												another_move = true;
											}
											else
											{
												if (board[y - 1][x + 1].existing_piece == true && board[y - 1][x + 1].blank_or_not == white_piece_sign && board[y - 2][x + 2].existing_piece == false) //warunek na bicie wielokrotne
												{
													another_move = true;
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
					}
					else
					{
						if (places.size() == 15) // poruszanie sie damki gdy ma 4 opcje ruchu
						{
							cout << " Jesli chcesz sie ruszyc na pole: " << places[0] << places[1] << " wcisnij 1 ,a jesli interesuje cie pole: " << places[4] << places[5] << " wybierz 2, a jesli jednak chcesz na pole: " << places[8] << places[9] << " wcisnij 3, a jak zdecydujesz sie na pole: " << places[12] << places[13] << " wybierz 4" << endl;
							int wybor;
							cin >> wybor;
							if (wybor == 1) {
								board[(int)(places[1] - '1')][(int)(places[0] - 'A')].set_color(blackqueen_piece_sign);
								board[(int)(places[1] - '1')][(int)(places[0] - 'A')].queen = true;
								board[y][x].set_color("blank"); board[y][x].existing_piece = false; board[y][x].queen = false;

								if (abs(y - (int)(places[1] - '1')) == 2 && abs(x - (int)(places[0] - 'A')) == 2) {//czy zbiles pionek
									piece_down(x, y, (int)(places[0] - 'A'), (int)(places[1] - '1'));

									y = (int)(places[1] - '1');
									x = (int)(places[0] - 'A');
									if (board[y + 1][x + 1].existing_piece == true && board[y + 1][x + 1].blank_or_not == white_piece_sign && board[y + 2][x + 2].existing_piece == false) //warunek na bicie wielokrotne
									{
										another_move = true;
									}
									else
									{
										if (board[y + 1][x - 1].existing_piece == true && board[y + 1][x - 1].blank_or_not == white_piece_sign && board[y + 2][x - 2].existing_piece == false)
										{
											another_move = true;
										}
										else {
											if (board[y - 1][x + 1].existing_piece == true && board[y - 1][x + 1].blank_or_not == white_piece_sign && board[y - 2][x + 2].existing_piece == false) //warunek na bicie wielokrotne
											{
												another_move = true;
											}
											else
											{
												if (board[y - 1][x + 1].existing_piece == true && board[y - 1][x + 1].blank_or_not == white_piece_sign && board[y - 2][x + 2].existing_piece == false) //warunek na bicie wielokrotne
												{
													another_move = true;
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
								if (wybor == 2)
								{
									board[(int)(places[5] - '1')][(int)(places[4] - 'A')].set_color(blackqueen_piece_sign);
									board[(int)(places[5] - '1')][(int)(places[4] - 'A')].queen = true;
									board[y][x].set_color("blank"); board[y][x].existing_piece = false; board[y][x].queen = false;

									if (abs(y - (int)(places[5] - '1')) == 2 && abs(x - (int)(places[4] - 'A')) == 2) { //bicie
										piece_down(x, y, (int)(places[4] - 'A'), (int)(places[5] - '1'));

										y = (int)(places[5] - '1');
										x = (int)(places[4] - 'A');
										/*
											sprawdzanie czy na miejscu do bicia jest jakis pionek && sprawdzanie czy jest czarny && sprawdzanie czy pole do lądowania jest puste
										*/
										if (board[y + 1][x + 1].existing_piece == true && board[y + 1][x + 1].blank_or_not == white_piece_sign && board[y + 2][x + 2].existing_piece == false) //warunek na bicie wielokrotne
										{
											another_move = true;
										}
										else
										{
											if (board[y + 1][x - 1].existing_piece == true && board[y + 1][x - 1].blank_or_not == white_piece_sign && board[y + 2][x - 2].existing_piece == false)
											{
												another_move = true;
											}
											else
											{
												if (board[y - 1][x + 1].existing_piece == true && board[y - 1][x + 1].blank_or_not == white_piece_sign && board[y - 2][x + 2].existing_piece == false) //warunek na bicie wielokrotne
												{
													another_move = true;
												}
												else
												{
													if (board[y - 1][x + 1].existing_piece == true && board[y - 1][x + 1].blank_or_not == white_piece_sign && board[y - 2][x + 2].existing_piece == false) //warunek na bicie wielokrotne
													{
														another_move = true;
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
									if (wybor == 3)
									{
										board[(int)(places[9] - '1')][(int)(places[8] - 'A')].set_color(blackqueen_piece_sign);
										board[(int)(places[9] - '1')][(int)(places[8] - 'A')].queen = true;
										board[y][x].set_color("blank"); board[y][x].existing_piece = false; board[y][x].queen = false;

										if (abs(y - (int)(places[9] - '1')) == 2 && abs(x - (int)(places[8] - 'A')) == 2) { //bicie
											piece_down(x, y, (int)(places[8] - 'A'), (int)(places[9] - '1'));

											y = (int)(places[9] - '1');
											x = (int)(places[8] - 'A');
											/*
												sprawdzanie czy na miejscu do bicia jest jakis pionek && sprawdzanie czy jest czarny && sprawdzanie czy pole do lądowania jest puste
											*/
											if (board[y + 1][x + 1].existing_piece == true && board[y + 1][x + 1].blank_or_not == white_piece_sign && board[y + 2][x + 2].existing_piece == false) //warunek na bicie wielokrotne
											{
												another_move = true;
											}
											else
											{
												if (board[y + 1][x - 1].existing_piece == true && board[y + 1][x - 1].blank_or_not == white_piece_sign && board[y + 2][x - 2].existing_piece == false)
												{
													another_move = true;
												}
												else
												{
													if (board[y - 1][x + 1].existing_piece == true && board[y - 1][x + 1].blank_or_not == white_piece_sign && board[y - 2][x + 2].existing_piece == false) //warunek na bicie wielokrotne
													{
														another_move = true;
													}
													else
													{
														if (board[y - 1][x + 1].existing_piece == true && board[y - 1][x + 1].blank_or_not == white_piece_sign && board[y - 2][x + 2].existing_piece == false) //warunek na bicie wielokrotne
														{
															another_move = true;
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
									else
									{
										board[(int)(places[13] - '1')][(int)(places[12] - 'A')].set_color(blackqueen_piece_sign);
										board[(int)(places[13] - '1')][(int)(places[12] - 'A')].queen = true;
										board[y][x].set_color("blank"); board[y][x].existing_piece = false; board[y][x].queen = false;

										if (abs(y - (int)(places[13] - '1')) == 2 && abs(x - (int)(places[12] - 'A')) == 2) { //bicie
											piece_down(x, y, (int)(places[12] - 'A'), (int)(places[13] - '1'));

											y = (int)(places[13] - '1');
											x = (int)(places[12] - 'A');
											/*
												sprawdzanie czy na miejscu do bicia jest jakis pionek && sprawdzanie czy jest czarny && sprawdzanie czy pole do lądowania jest puste
											*/
											if (board[y + 1][x + 1].existing_piece == true && board[y + 1][x + 1].blank_or_not == white_piece_sign && board[y + 2][x + 2].existing_piece == false) //warunek na bicie wielokrotne
											{
												another_move = true;
											}
											else
											{
												if (board[y + 1][x - 1].existing_piece == true && board[y + 1][x - 1].blank_or_not == white_piece_sign && board[y + 2][x - 2].existing_piece == false)
												{
													another_move = true;
												}
												else
												{
													if (board[y - 1][x + 1].existing_piece == true && board[y - 1][x + 1].blank_or_not == white_piece_sign && board[y - 2][x + 2].existing_piece == false) //warunek na bicie wielokrotne
													{
														another_move = true;
													}
													else
													{
														if (board[y - 1][x + 1].existing_piece == true && board[y - 1][x + 1].blank_or_not == white_piece_sign && board[y - 2][x + 2].existing_piece == false) //warunek na bicie wielokrotne
														{
															another_move = true;
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
							}
						}
					}
				}
			}


}			
			temp = board[y][x];
			cin.clear();
			cin.ignore();
			if (y == 0)
				temp.queen = true;
		} while (another_move); // bool another_move kontroluje kolejnosc ruchow przy biciu (bicie wielokrotne, wymaga aby ten sam kolor dalej mial ruch)
		return !turn;
	}

	//void output() { // funkcja sprawdzajaca, wykorzystywana w fazie debugowania
	//	int white;
	//	int black;

	//	for (int i = 7; i >= 0; i--) {
	//		for (int j = 0; j < 8; j++) {

	//			cout << board[i][j].character << " ";

	//		}
	//		cout << endl;
	//	}
	//	char x;
	//	for (int i = 0; i < 8; i++) {
	//		x = 'A' + i;
	//		cout << x << " ";
	//	}
	//}

	bool gameBoard() // Drukuje pelna szachownice wraz z pionkami
	{
		int white=0;
		int black=0;
		Sleep(500);
		system("cls"); //czyszczenie wiersza polecen
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
			for (int i = 0; i < 8; i++)
			{
				cout << " ";
				if (board[k][i].character == NULL)
					cout << " ";
				else
					cout << board[k][i].character;
				cout << " " << stick; //wypisywanie ladnej tablicy, prawie jak w SFML'u

				if ((board[k][i].blank_or_not == white_piece_sign) or (board[k][i].blank_or_not == whitequeen_piece_sign)) { //liczenie pionkow bialych
					white += 1;
				}
				if ((board[k][i].blank_or_not == black_piece_sign) or (board[k][i].blank_or_not == blackqueen_piece_sign)) { //liczenie pionkow czarnych
					black += 1;
				}

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
		
		if (black == 0) {
			return 1;
		}
		else if (white == 0) {
			return 1;
		}
		else
			return 0;
	}

	~Board() {};
};

class Game {
	bool white_turnn = true;
public:
	Game() {
		Board board = Board();
		board.gameBoard();

		while (!board.gameBoard()) {
			if (white_turnn)
			{
				board.input(white_turnn);

			}
			else
			{
				board.input(white_turnn);
			}
		}

		for (int i = 0; i < 20; i++) {
			cout << "KONIEC GRYY!!!!!!!!!!!!" << endl;
		}
		
		
	}
	friend class Place;
	~Game() {};
};

class Rules {
public:
	Rules() {
		cout << "********************************************" << endl;
		cout << "Pionki moga poruszac sie tylko przed siebie" << endl;
		cout << "Pionki bija tylko do przodu" << endl;
		cout << "Damki moga poruszac sie i bic w kazda strone" << endl;
		cout << "Utrata wszystkich pionkow, skutkuje przegrana" << endl;
		cout << "Nieprawidlowy ruch skutkuje jego utrata" << endl;
		cout << "********************************************" << endl;
		cout << endl << endl << endl;
		cout << "Nacisnij ENTER" << endl << endl;;
		system("Pause");
	}
	~Rules() {};
};

int main() {
	SetConsoleTitle("Checkers");
	Rules r1;
	Game g1;
}