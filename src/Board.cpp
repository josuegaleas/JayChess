/*
 * Author: Josue Galeas
 * Last Edit: Feb 6, 2017
 */

#include "Board.h"
/* #include "ActivePiece.h" */

void Board::setupPieces(int row)
{
	board[row][0].setType('R');
	board[row][1].setType('N');
	board[row][2].setType('B');
	board[row][3].setType('Q');
	board[row][4].setType('K');
	board[row][5].setType('B');
	board[row][6].setType('N');
	board[row][7].setType('R');
}

void Board::setupSymbols()
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			Piece *p = getPiece(i, j);

			if (p->getColor() == 'E')
				continue;
			else if (p->getColor() == 'W')
			{
				switch (p->getType())
				{
					case 'P':
						p->setSymbol("♙");
						break;
					case 'N':
						p->setSymbol("♘");
						break;
					case 'B':
						p->setSymbol("♗");
						break;
					case 'R':
						p->setSymbol("♖");
						break;
					case 'Q':
						p->setSymbol("♕");
						break;
					case 'K':
						p->setSymbol("♔");
						break;
					default:
						p->setSymbol("?");
						break;
				}
			}
			else
			{
				switch (p->getType())
				{
					case 'P':
						p->setSymbol("♟");
						break;
					case 'N':
						p->setSymbol("♞");
						break;
					case 'B':
						p->setSymbol("♝");
						break;
					case 'R':
						p->setSymbol("♜");
						break;
					case 'Q':
						p->setSymbol("♛");
						break;
					case 'K':
						p->setSymbol("♚");
						break;
					default:
						p->setSymbol("?");
						break;
				}
			}
		}
	}
}

Board::Board()
{
	for (int col = 0; col < 8; col++)
	{
		// Setting top two rows to all black
		board[0][col].setColor('B');
		board[1][col].setColor('B');

		// Setting bottom two rows to all white
		board[6][col].setColor('W');
		board[7][col].setColor('W');

		// Setting up pawns
		board[1][col].setType('P');
		board[6][col].setType('P');
	}

	// Setting up non-pawns
	setupPieces(0);
	setupPieces(7);

	// Setting up symbols
	setupSymbols();
}

/* ActivePiece *Board::getActivePiece(int *location) */
/* { */
/* 	ActivePiece *output = new ActivePiece; */

/* 	int x = location[0]; */
/* 	int y = location[1]; */

/* 	output->piece = &board[x][y]; */
/* 	output->arrayLocation[0] = x; */
/* 	output->arrayLocation[1] = y; */
/* 	output->gameLocation[0] = y + 'a'; */
/* 	output->gameLocation[1] = '8' - x; */

/* 	// TODO: DEBUG */
/* 	printf("%c%c at ", output->piece->getColor(), output->piece->getType()); */
/* 	printf("%c%c\n", output->gameLocation[0], output->gameLocation[1]); */

/* 	delete[] location; */
/* 	return output; */
/* } */

Piece *Board::getPiece(int x, int y)
{
	return &board[x][y];
}

void Board::printBoard() const
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			printf("%c%c ", board[i][j].getColor(), board[i][j].getType());
		}
		printf("\n");
	}
}

void Board::drawBoard() const
{
	char files[] = "|     a   b   c   d   e   f   g   h     |\n";
	char ranks[] = "|   +---+---+---+---+---+---+---+---+   |\n";
	char border[] = "+---------------------------------------+\n";

	printf("%s%s", border, files);

	for (int x = 0; x < 8; x++)
	{
		printf("%s| %d ", ranks, 8 - x);

		for (int y = 0; y < 8; y++)
		{
			printf("| %s ", board[x][y].getSymbol().c_str());
		}

		printf("| %d |\n", 8 - x);
	}

	printf("%s%s%s", ranks, files, border);
}
