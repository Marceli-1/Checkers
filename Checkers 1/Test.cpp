//void gameBoard() // Drukuje pelna szachownice wraz z pionkami
//{
//	unsigned char upright = 191;
//	unsigned char leftdown = 192;
//	unsigned char downcentre = 193;
//	unsigned char upcentre = 194;
//	unsigned char leftcentre = 195;
//	unsigned char updown = 196;
//	unsigned char centre = 197;
//
//	unsigned char rightdown = 217;
//	unsigned char upleft = 218;
//	unsigned char stick = 179;
//	unsigned char rightcentre = 180;
//
//	cout << " " << upleft << updown << updown << updown;
//	for (int i = 0; i < 7; i++)
//	{
//		cout << upcentre << updown << updown << updown;
//	}
//	cout << upright << endl;
//
//	int j = 8; // nr szachownicy
//	for (int k = 0; k < 7; k++)
//	{
//		cout << j << stick;
//		for (int i = 0; i < 8; i++)
//		{
//			cout << " " << board[k][i].character << " " << stick;
//		}
//		cout << endl;
//
//		cout << " " << leftcentre << updown << updown << updown;
//		for (int i = 0; i < 7; i++)
//		{
//			cout << centre << updown << updown << updown;
//		}
//		cout << rightcentre << endl;
//		j--;
//	}
//
//	cout << "1" << stick;
//	for (int i = 0; i < 8; i++)
//	{
//		cout << " " << board[7][i].character << " " << stick;
//	}
//	cout << endl;
//
//	cout << " " << leftdown << updown << updown << updown;
//	for (int i = 0; i < 7; i++)
//	{
//		cout << downcentre << updown << updown << updown;
//	}
//	cout << rightdown << endl;
//
//	cout << "   A   B   C   D   E   F   G   H" << endl << endl;
//}