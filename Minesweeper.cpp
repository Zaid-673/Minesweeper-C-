#include <SFML/Graphics.hpp>
#include <iostream>

#define LENGTH 16
#define WIDTH 16
#define BOMBS 40

using namespace sf;
using namespace std;

struct poz
{
	int row;
	int column;
};

int w = 32;
int board[LENGTH + 1][WIDTH + 1];
int user_board[LENGTH + 1][WIDTH + 1];
poz tail[10000];
int ltail, excttail, firstMove, bombsFound = 0;

void initialisation_of_user_board()
{
	for (int i = 1; i <= LENGTH; i++)
	{
		for (int j = 1; j <= WIDTH; j++)
		{
			user_board[i][j] = 10;
		}
	}
}

void bomb_intialisation(int a, int b)
{
	for (int i = 1; i <= BOMBS; i++)
	{
		int x = rand() % LENGTH + 1;
		int y = rand() % WIDTH + 1;
		if (x == a && y == b)
		{
			int x = rand() % LENGTH + 1;
			int y = rand() % WIDTH + 1;
			board[x][y] = 10;
		}
		else
		{
			board[x][y] = 9;
		}
	}
}

void number_of_mines()
{
	for (int i = 1; i <= LENGTH; i++)
	{
		for (int j = 1; j <= WIDTH; j++)
		{
			if (board[i][j] != 9)
			{
				int noBombs = 0;
				if (board[i - 1][j - 1] == 9)
				{
					noBombs++;
				}
				if (board[i - 1][j] == 9)
				{
					noBombs++;
				}
				if (board[i - 1][j + 1] == 9)
				{
					noBombs++;
				}
				if (board[i][j - 1] == 9)
				{
					noBombs++;
				}
				if (board[i][j + 1] == 9)
				{
					noBombs++;
				}
				if (board[i + 1][j - 1] == 9)
				{
					noBombs++;
				}
				if (board[i + 1][j] == 9)
				{
					noBombs++;
				}
				if (board[i + 1][j + 1] == 9)
				{
					noBombs++;
				}
				board[i][j] = noBombs;
			}
		}
	}
}

void verify(int i, int j)
{
	user_board[i][j] = 0;
	if (board[i - 1][j - 1] == 0 && i - 1 > 0 && i - 1 <= LENGTH && j - 1 > 0 && j - 1 <= WIDTH)
	{
		tail[ltail].column = i - 1;
		tail[ltail].row = j - 1;
		ltail++;
	}
	if (board[i - 1][j] == 0 && i - 1 > 0 && i - 1 <= LENGTH && j > 0 && j <= WIDTH)
	{
		tail[ltail].column = i - 1;
		tail[ltail].row = j;
		ltail++;
	}
	if (board[i - 1][j + 1] == 0 && i - 1 > 0 && i - 1 <= LENGTH && j + 1 > 0 && j + 1 <= WIDTH)
	{
		tail[ltail].column = i - 1;
		tail[ltail].row = j + 1;
		ltail++;
	}
	if (board[i][j - 1] == 0 && i > 0 && i <= LENGTH && j - 1 > 0 && j - 1 <= WIDTH)
	{
		tail[ltail].column = i;
		tail[ltail].row = j - 1;
		ltail++;
	}
	if (board[i][j + 1] == 0 && i > 0 && i <= LENGTH && j + 1 > 0 && j + 1 <= WIDTH)
	{
		tail[ltail].column = i;
		tail[ltail].row = j + 1;
		ltail++;
	}
	if (board[i + 1][j - 1] == 0 && i + 1 > 0 && i + 1 <= LENGTH && j - 1 > 0 && j - 1 <= WIDTH)
	{
		tail[ltail].column = i + 1;
		tail[ltail].row = j - 1;
		ltail++;
	}
	if (board[i + 1][j] == 0 && i + 1 > 0 && i + 1 <= LENGTH && j > 0 && j <= WIDTH)
	{
		tail[ltail].column = i + 1;
		tail[ltail].row = j;
		ltail++;
	}
	if (board[i + 1][j + 1] == 0 && i + 1 > 0 && i + 1 <= LENGTH && j + 1 > 0 && j + 1 <= WIDTH)
	{
		tail[ltail].column = i + 1;
		tail[ltail].row = j;
		ltail++;
	}
}

void first_move(int i, int j)
{
	if (board[i][j] == 0)
	{
		user_board[i][j] = 0;
		verify(i, j);
		while (excttail < ltail)
		{
			user_board[tail[excttail].column][tail[excttail].row] = 0;
			excttail++;
		}
	}
	else
	{
		user_board[i][j] = board[i][j];
	}
	if (board[i - 1][j - 1] != 9 && i - 1 > 0 && i - 1 <= LENGTH && j - 1 > 0 && j - 1 <= WIDTH)
	{
		if (board[i - 1][j - 1] == 0)
		{
			user_board[i - 1][j - 1] = 0;
			verify(i - 1, j - 1);
			while (excttail < ltail)
			{
				user_board[tail[excttail].column][tail[excttail].row] = 0;
				excttail++;
			}
		}
		else
		{
			user_board[i - 1][j - 1] = board[i - 1][j - 1];
		}
	}
	if (board[i - 1][j] != 9 && i - 1 > 0 && i - 1 <= LENGTH && j > 0 && j <= WIDTH)
	{
		if (board[i - 1][j] == 0)
		{
			user_board[i - 1][j] = 0;
			verify(i - 1, j);
			while (excttail < ltail)
			{
				user_board[tail[excttail].column][tail[excttail].row] = 0;
				excttail++;
			}
		}
		else
		{
			user_board[i - 1][j] = board[i - 1][j];
		}
	}
	if (board[i - 1][j + 1] != 9 && i - 1 > 0 && i - 1 <= LENGTH && j + 1 > 0 && j + 1 <= WIDTH)
	{
		if (board[i - 1][j + 1] == 0)
		{
			user_board[i - 1][j + 1] = 0;
			verify(i - 1, j + 1);
			while (excttail < ltail)
			{
				user_board[tail[excttail].column][tail[excttail].row] = 0;
				excttail++;
			}
		}
		else
		{
			user_board[i - 1][j + 1] = board[i - 1][j + 1];
		}
	}
	if (board[i][j - 1] != 9 && i > 0 && i <= LENGTH && j - 1 > 0 && j - 1 <= WIDTH)
	{
		if (board[i][j - 1] == 0)
		{
			user_board[i][j - 1] = 0;
			verify(i, j - 1);
			while (excttail < ltail)
			{
				user_board[tail[excttail].column][tail[excttail].row] = 0;
				excttail++;
			}
		}
		else
		{
			user_board[i][j - 1] = board[i - 1][j - 1];
		}
	}
	if (board[i][j + 1] != 9 && i > 0 && i <= LENGTH && j + 1 > 0 && j + 1 <= WIDTH)
	{
		if (board[i][j + 1] == 0)
		{
			user_board[i][j + 1] = 0;
			verify(i, j + 1);
			while (excttail < ltail)
			{
				user_board[tail[excttail].column][tail[excttail].row] = 0;
				excttail++;
			}
		}
		else
		{
			user_board[i][j + 1] = board[i + 1][j + 1];
		}
	}
	if (board[i + 1][j - 1] != 9 && i + 1 > 0 && i + 1 <= LENGTH && j - 1 > 0 && j - 1 <= WIDTH)
	{
		if (board[i + 1][j - 1] == 0)
		{
			user_board[i + 1][j - 1] = 0;
			verify(i + 1, j - 1);
			while (excttail < ltail)
			{
				user_board[tail[excttail].column][tail[excttail].row] = 0;
				excttail++;
			}
		}
		else
		{
			user_board[i + 1][j - 1] = board[i + 1][j - 1];
		}
	}
	if (board[i + 1][j] != 9 && i + 1 > 0 && i + 1 <= LENGTH && j > 0 && j <= WIDTH)
	{
		if (board[i + 1][j] == 0)
		{
			user_board[i + 1][j] = 0;
			verify(i + 1, j);
			while (excttail < ltail)
			{
				user_board[tail[excttail].column][tail[excttail].row] = 0;
				excttail++;
			}
		}
		else
		{
			user_board[i + 1][j] = board[i + 1][j];
		}
	}
	if (board[i + 1][j + 1] != 9 && i + 1 > 0 && i + 1 <= LENGTH && j + 1 > 0 && j + 1 <= WIDTH)
	{
		if (board[i + 1][j + 1] == 0)
		{
			user_board[i + 1][j + 1] = 0;
			verify(i + 1, j + 1);
			while (excttail < ltail)
			{
				user_board[tail[excttail].column][tail[excttail].row] = 0;
				excttail++;
			}
		}
		else
		{
			user_board[i + 1][j + 1] = board[i + 1][j + 1];
		}
	}
	if (board[i - 1][j + 2] != 9 && i - 1 > 0 && i - 1 <= LENGTH && j + 2 > 0 && j + 2 <= WIDTH)
	{
		if (board[i - 1][j + 2] == 0)
		{
			user_board[i - 1][j + 2] = 0;
			verify(i - 1, j + 2);
			while (excttail < ltail)
			{
				user_board[tail[excttail].column][tail[excttail].row] = 0;
				excttail++;
			}
		}
		else
		{
			user_board[i - 1][j + 2] = board[i - 1][j + 2];
		}
	}
	if (board[i][j + 2] != 9 && i > 0 && i <= LENGTH && j + 2 > 0 && j + 2 <= WIDTH)
	{
		if (board[i][j + 2] == 0)
		{
			user_board[i][j + 2] = 0;
			verify(i, j + 2);
			while (excttail < ltail)
			{
				user_board[tail[excttail].column][tail[excttail].row] = 0;
				excttail++;
			}
		}
		else
		{
			user_board[i][j + 2] = board[i][j + 2];
		}
	}
	if (board[i + 1][j + 2] != 9 && i + 1 > 0 && i + 1 <= LENGTH && j + 2 > 0 && j + 2 <= WIDTH)
	{
		if (board[i + 1][j + 2] == 0)
		{
			user_board[i + 1][j + 2] = 0;
			verify(i + 1, j + 2);
			while (excttail < ltail)
			{
				user_board[tail[excttail].column][tail[excttail].row] = 0;
				excttail++;
			}
		}
		else
		{
			user_board[i + 1][j + 2] = board[i + 1][j + 2];
		}
	}
}

int main()
{
	RenderWindow app(VideoMode(600, 600), "Minesweeper <3");

	Clock clock;

	int time = clock.getElapsedTime().asSeconds();

	Texture t;
	t.loadFromFile("images/tiles.jpg");
	Texture winSource;

	Sprite s(t);
	initialisation_of_user_board();
	while (app.isOpen())
	{
		Vector2i pos = Mouse::getPosition(app);
		int x = pos.x / w;
		int y = pos.y / w;
		Event e;
		while (app.pollEvent(e))
		{
			if (e.type == Event::Closed)
			{
				app.close();
			}
			if (e.type == Event::MouseButtonPressed)
			{
				if (e.key.code == Mouse::Left)
				{
					if (firstMove == 0)
					{
						bomb_intialisation(x, y);
						number_of_mines();
						first_move(x, y);
						firstMove = 1;
					}
					else if (board[x][y] == 0)
					{
						verify(x, y);
						while (excttail < ltail)
						{
							user_board[tail[excttail].column][tail[excttail].row] = 0;
							excttail++;
						}
					}
					else
					{
						user_board[x][y] = board[x][y];
					}
				}
				else if (e.key.code == Mouse::Right)
				{
					if (user_board[x][x] == 11)
					{
						user_board[x][y] = 10;
					}
					else if (user_board[x][y] > 9)
					{
						user_board[x][y] = 11;
					}
					if (board[x][y] == 9)
					{
						bombsFound++;
					}
				}
			}
		}
		app.clear(Color::White);
		if (bombsFound == BOMBS)
		{
			Sprite win(winSource);
			win.setTexture(winSource);
			app.draw(win);
			app.display();
		}
		else
		{
			for (int i = 1; i <= LENGTH; i++)
			{
				for (int j = 1; j <= WIDTH; j++)
				{
					if (user_board[x][y] == 9)
					{
						user_board[i][j] = board[i][j];
					}
					s.setTextureRect(IntRect(user_board[i][j] * w, 0, w, w));
					s.setPosition(i * w, j * w);
					app.draw(s);

				}
			}
			app.display();
		}
	}

	cout << "You Lost" << endl;
	cout << "Your Game Lasted For " << time << " seconds" << endl;

	return 0;

}