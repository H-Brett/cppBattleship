// ProjectSixPartOne.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <conio.h>
#include <cstdlib> 
#include <sstream> 
#include <time.h> 

using namespace std; 

enum OrientShip{HORIZONTAL, VERTICAL}; 

class Ship
{
	private:
		string shipType;
		int size;
		int row;
		int col;
		OrientShip dir; 
		bool sunk; 

	public:
		//default constructor 
		Ship() 
		{
			shipType = "default"; 
			size = 0; 
			row = 0;
			col = 0;
			dir = HORIZONTAL; 
			sunk = false; 
		}

		// 2 arg constructor that sets name and size of ship
		Ship(string type, int s)
		{
			row = 0; 
			col = 0; 
			dir = HORIZONTAL; 
			size = s;
			shipType = type;
			sunk = false; 
		}

		int getRow()
		{
			return row; 
		}

		void setRow(int r)
		{
			row = r; 
		}

		int getCol()
		{
			return col;
		}

		void setCol(int c) 
		{
			col = c; 
		}

		string getShipType()
		{
			return shipType; 
		}

		void setShipType(string type)
		{
			shipType = type; 
		}

		int getSize()
		{
			return size;
		}

		void setSize(int s)
		{
			size = s; 
		}

		OrientShip getShipDirect()
		{
			return dir;
		}

		void setShipDirect(OrientShip direct)
		{
			dir = direct; 
		}

		void setSunk(bool t)
		{
			sunk = t; 
		} 

		bool getSunk()
		{
			return sunk; 
		}


};

class Board
{
	private:
		int board[10][10]; 

	public:
		Board()
		{
			for(int row = 0; row < 10; row++)
			{
				for(int col = 0; col < 10; col++)
				{
					board[row][col] = 0; 
				}
			}
		}
		
		void printBoard()
		{
			char label = 'A'; 
			cout << "  1 2 3 4 5 6 7 8 9 10" << endl; 

			for(int row = 0; row < 10; row++)
			{
				cout << label << " "; 
				label++; 
				for(int col = 0; col < 10; col++)
				{
					if(board[row][col] == 0 || board[row][col] == 1)
					{
						cout << "~" << " ";
					}
					else if(board[row][col] == 2)
					{
						cout << "H" << " ";
					}
					else
					{
						cout << "M" << " ";
					}	
				}
				cout << endl; 
			}
		}

		void placeShip(Ship &ship)
		{
			int randNum = rand()%2;
			bool isPlaced = false;
			
			while(!isPlaced)
			{
				bool isClear = true; 
				int randNum = rand()%2;

				if(randNum == 0) 
					ship.setShipDirect(HORIZONTAL); 
				else
					ship.setShipDirect(VERTICAL); 

				if(ship.getShipDirect() == HORIZONTAL) 
				{
					int column = rand()%(10 - ship.getSize()); 
					int row = rand()%10; 

					for(int i = column; i < column + ship.getSize(); i++)
					{
						if(board[row][i]!=0)
						{
							isClear = false; 
						}
					}

					if(isClear)
					{
						ship.setRow(row);
						ship.setCol(column);

						for(int i = column; i < (column + ship.getSize()); i++)
						{
							 board[row][i] = 1; 
						}
						isPlaced = true; 
					}
				} // end if::HORIZONTAL
				else
				{
					int row = rand()%(10 - ship.getSize()); 
					int column = rand()%10; 

					for(int i = row; i < row + ship.getSize(); i++)
					{
						if(board[i][column]!=0)
						{
							isClear = false; 
						}

					}

					if(isClear)
					{
						ship.setRow(row);
						ship.setCol(column);

						for(int i = row; i < (row + ship.getSize()); i++)
						{
							 board[i][column] = 1; 
						}
						isPlaced = true; 
					} // end if isClear
				} // end else:: VERTICAL
			} // end while isPlaced
		} // end function placeShip

		bool isGameWon()
		{
			for(int row = 0; row < 10; row++)
			{
				for(int col = 0; col < 10; col++)
				{
					if(board[row][col]==1)
						return false; 
				}
			}
			return true; 
		}

		bool isHit(int row, int col) 
		{
			if(board[row][col]!=0)
			{
				board[row][col] = 2;
				return true; 
			}
			else
			{
				board[row][col] = 3; 
				return false; 	
			}
		}

		bool isSunk(Ship &ship)
		{
			int column = ship.getCol();
			int row = ship.getRow();


			if(ship.getShipDirect() == HORIZONTAL)
			{
				for(int i = column; i < column + ship.getSize(); i++)
				{
					if(board[row][i]!=2)
					{
						return false; 
					}
				} // end for 
			} // end if::HORIZONTAL
			
			if(ship.getShipDirect() == VERTICAL) 
			{
				for(int i = row; i < row + ship.getSize(); i++)
				{
					if(board[i][column]!=2)
					{
						return false; 
					}
				} // end for 
			} // end else::VERTICAL

			if(!ship.getSunk())
			{
				cout << "You sunk my " << ship.getShipType() << "!!!";
				ship.setSunk(true); 
				getch();
			}

			return true; // if not evaluated false, return true;
		} // end bool isSunk method
}; // end class Board


int _tmain(int argc, _TCHAR* argv[])
{

	char response = 'Y'; 

	do
	{

		srand(time(0)); 

		char row;
		int col; 
	
		Ship ships[5]; 
		ships[0].setShipType("Destroyer");
		ships[0].setSize(2);
		ships[1].setShipType("Crusier");
		ships[1].setSize(3);
		ships[2].setShipType("Submarine");
		ships[2].setSize(3);
		ships[3].setShipType("Battleship");
		ships[3].setSize(4);
		ships[4].setShipType("Carrier");
		ships[4].setSize(5);

		Board board;

		for(int i = 0; i < 5; i++)
		{
			board.placeShip(ships[i]); 
		}

		while(!board.isGameWon())
		{
			system("cls");
			board.printBoard();
			cout << "Enter Guess: "; 
			cin >> row >> col; 

			col--; // fixes user guess to array value

			int rowInt = (int)row; // fix ascii value
			rowInt -= 65;  // to int coord
			
			if(board.isHit(rowInt,col))
			{			
				for(int i = 0; i < 5; i++)
				{
					board.isSunk(ships[i]); 
				} 
			}
		}

		cout << "CONGRATULATIONS! YOU WIN!\n\nPlay again?(y/n): ";
		cin >> response; 

	}while(response == 'Y' || response == 'y'); 

	return 0;
}