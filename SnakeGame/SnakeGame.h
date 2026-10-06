#pragma once
#include <iostream>
#include <vector>
#include <random>
#include <cctype>
#include <conio.h>
#include <Windows.h>
using namespace std;

class Snake
{
	vector<pair<int, int>> body{};
	int totalScore{};
	char currDirection{};

public:
	Snake(const pair<int, int>& initPosition, const char& initDirection)
	{
		body.push_back(initPosition);
		currDirection = initDirection;
	}

	pair<int, int> Move()
	{
		const pair<int, int> oldTail = body.front();

		int len = (int)body.size() - 1;
		for (int i = 0; i < len; i++)
		{
			body[i] = body[i + 1];
		}

		switch (currDirection)
		{
		case 'W':
			body.back().first--;
			break;
		case 'S':
			body.back().first++;
			break;
		case 'D':
			body.back().second++;
			break;
		case 'A':
			body.back().second--;
			break;
		default:
			break;
		}

		return oldTail;
	}

	void ChangeDirection(const char& newDirection)
	{
		currDirection = newDirection;
	}

	void ExpandLength(const pair<int, int>& oldTail, const int& foodValue)
	{
		totalScore += foodValue;
		body.insert(body.begin(), oldTail);
	}

	bool IsSelfColliding()
	{
		int len = (int)body.size() - 1;
		for (int i = 0; i < len; i++)
		{
			if (body.back() == body[i])
			{
				return true;
			}
		}

		return false;
	}

	pair<int, int> GetHeadPos() const
	{
		return body.back();
	}

	bool isMyPosition(const pair<int, int>& pos)
	{
		for (const auto& p : body)
		{
			if (pos == p)
			{
				return true;
			}
		}

		return false;
	}

	int GetTotalScore() const
	{
		return totalScore;
	}
};

struct Board
{
	Board(const int& initHeight, const int& initWidth)
	{
		width = initWidth;
		height = initHeight;
	}

	bool IsValidPos(const pair<int, int>& position) const
	{
		if (position.first >= height || position.second >= width
			|| position.first < 0 || position.second < 0)
		{
			return false;
		}

		return true;
	}

	int GetWidth() const
	{
		return width;
	}

	int GetHeight() const
	{
		return height;
	}

private:
	int width{}, height{};
};

struct Food
{
	Food(const pair<int, int>& initPosition, const int& foodValue)
	{
		position = initPosition;
		this->foodValue = foodValue;
	}

	pair<int, int> GetFoodPos() const
	{
		return position;
	}

	int GetFoodValue() const
	{
		return foodValue;
	}

private:
	pair<int, int> position{};
	int foodValue{};
};

class SnakeGame
{
	Snake* snake{};
	Board* board{};
	Food* food{};

	bool isGameOver{};
	mt19937 gen;

	/**/

	int genRandNum(const int& start = 0, const int& end = 100)
	{
		uniform_int_distribution<int> distrib(start, end);

		return distrib(gen);
	}

	pair<int, int> genRandPos()
	{
		int width = board->GetWidth() - 1;
		int height = board->GetHeight() - 1;

		return { genRandNum(0, height),genRandNum(0, width) };
	}

	pair<int, int> genFoodPos()
	{
		pair<int, int> foodPos = genRandPos();

		while (snake->isMyPosition(foodPos))
		{
			foodPos = genRandPos();
		}

		return foodPos;
	}

	char genRandDir()
	{
		char dir[] = { 'W','D','S','A' };

		return dir[genRandNum(0, 3)];
	}

	void clear()
	{
		delete snake;
		delete food;
		delete board;
	}

	void displayGame()
	{
		system("cls");

		for (int row = 0; row < board->GetHeight(); row++)
		{
			for (int col = 0; col < board->GetWidth(); col++)
			{
				pair<int, int> pos = { row,col };

				if (snake->isMyPosition(pos))
				{
					cout << "# ";
				}
				else if (food->GetFoodPos() == pos)
				{
					cout << "@ ";
				}
				else
				{
					cout << ". ";
				}
			}

			cout << '\n';
		}

		cout << "Score: " << snake->GetTotalScore() << '\n';
	}

	int setLevel()
	{
		cout << "========== SNAKE GAME ==========\n";
		cout << "1. Easy.\n2. Medium.\n3. Hard\n";
		cout << "Enter here: ";

		int choice{};
		cin >> choice;

		int level{};

		switch (choice)
		{
		case 1 :
			level = 400;
			break;
		case 2:
			level = 250;
			break;
		case 3:
			level = 150;
			break;
		default:
			level = 270;
			break;
		}

		return level;
	}

public:
	SnakeGame() : gen(random_device{}())
	{
		board = new Board(20, 20);
		snake = new Snake(genRandPos(), genRandDir());
		food = new Food(genFoodPos(), genRandNum());
		isGameOver = false;
	}

	~SnakeGame()
	{
		clear();
	}

	void StartGame()
	{
		int level = setLevel();

		displayGame();

		while (!isGameOver)
		{
			// Check if user pressed a key
			if (_kbhit())
			{
				char input = _getch();

				input = toupper(input);

				if (input == 'W' || input == 'A' || input == 'S' || input == 'D')
				{
					snake->ChangeDirection(input);
				}
			}

			// Move
			auto oldTail = snake->Move();

			// Check collisions
			if (!board->IsValidPos(snake->GetHeadPos()) || snake->IsSelfColliding())
			{
				isGameOver = true;
				break;
			}

			// Check food
			if (food->GetFoodPos() == snake->GetHeadPos())
			{
				snake->ExpandLength(oldTail, food->GetFoodValue());

				delete food;
				food = new Food(genFoodPos(), genRandNum());
			}

			displayGame();

			Sleep(level);
		}

		cout << "\nGame End!\n";
		cout << "Total Score: " << snake->GetTotalScore() << '\n';
	}
};