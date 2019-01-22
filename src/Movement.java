/*
 * Author: Josue Galeas
 * Last Edit: 2018.10.16
 */

public class Movement
{
	private static boolean convertRow(char b, int p[])
	{
		p[0] = 8 - Character.getNumericValue(b);
		if (p[0] >= 0 && p[0] <= 7)
			return true;

		p[0] = -1;
		return false;
	}

	private static boolean convertColumn(char a, int p[])
	{
		p[1] = a - 97;
		if (p[1] >= 0 && p[1] <= 7)
			return true;

		p[1] = -1;
		return false;
	}

	private static boolean convertPosition(char a, char b, int p[])
	{
		if (convertRow(b, p))
			if (convertColumn(a, p))
				return true;

		p[0] = p[1] = -1;
		return false;
	}

	public static char convertMove(String m, char t, int i[], int f[])
	{
		switch (m.charAt(0))
		{
			case 'N': // Knights
			case 'B': // Bishops
			case 'R': // Rooks
			case 'Q': // Queens
			case 'K': // Kings
				if (m.length() >= 3)
				{
					if (convertPosition(m.charAt(1), m.charAt(2), f))
					{
						// Potentially risky, but this means that convertPosition
						// was able to successfully convert the 2nd and 3rd characters,
						// meaning that the is in the form of Txy... where x
						// and y are the file and rank respectively
						return m.charAt(0);
					}
				}
				if (m.length() >= 4)
				{
					if (convertPosition(m.charAt(2), m.charAt(3), f))
					{
						if (m.charAt(1) == 'x')
							return m.charAt(0);
						else
						{
							if (convertColumn(m.charAt(1), i))
								return m.charAt(0);
						}
					}
				}
				break;
			case 'O': // Castling
				i[1] = 4;
				if (m.equals("O-O"))
				{
					f[1] = 6;

					if (t == 'W')
						i[0] = f[0] = 7;
					else if (t == 'B')
						i[0] = f[0] = 0;
					else
						return '?';

					return 'O';
				}
				else if (m.equals("O-O-O"))
				{
					f[1] = 2;

					if (t == 'W')
						i[0] = f[0] = 7;
					else if (t == 'B')
						i[0] = f[0] = 0;
					else
						return '?';

					return 'O';
				}
				break;
			default: // Pawns, maybe
				if (m.charAt(1) == 'x')
				{
					// If pawn is capturing
					if (m.length() >= 4)
					{
						boolean init = convertColumn(m.charAt(0), i);
						boolean fin = convertPosition(m.charAt(2), m.charAt(3), f);

						if (init && fin)
							return 'P';
					}
				}
				else
				{
					// If pawn is moving
					if (m.length() >= 2)
					{
						boolean init = convertColumn(m.charAt(0), i);
						boolean fin = convertPosition(m.charAt(0), m.charAt(1), f);

						if (init && fin)
							return 'P';
					}
				}
		}

		return '?';
	}

	private static boolean inRange(int i)
	{
		return i >= 0 && i <= 7;
	}

	public static boolean processKnight(int i[], int f[])
	{
		for (i[0] = f[0] - 2; i[0] <= f[0] + 2; i[0]++)
		{
			if (i[0] == f[0])
				continue;

			for (i[1] = f[1] - 2; i[1] <= f[1] + 2; i[1]++)
			{
				if (i[1] == f[1])
					continue;
				if (!inRange(i[0]) || !inRange(i[1]))
					continue;
				if (Math.abs(i[0]) == Math.abs(i[1]))
					continue;
				if (JayChess.board.getType(i[0], i[1]) != 'N')
					continue;

				if (JayChess.board.verifyMove(i, f))
					return true;
			}
		}

		return false;
	}

	public static boolean processBishop(int i[], int f[], char match)
	{
		for (int x = -1; x <= 1; x += 2)
		{
			for (int y = -1; y <= 1; y += 2)
			{
				i[0] = f[0];
				i[1] = f[1];

				while (true)
				{
					i[0] += x;
					i[1] += y;

					if (!inRange(i[0]) || !inRange(i[1]))
						break;
					if (JayChess.board.getType(i[0], i[1]) != match)
						continue;

					if (JayChess.board.verifyMove(i, f))
						return true;
				}
			}
		}

		return false;
	}

	public static boolean processRook(int i[], int f[], char match)
	{
		for (int x = 0; x <= 1; x++)
		{
			for (int y = -1; y <= 1; y += 2)
			{
				i[0] = f[0];
				i[1] = f[1];

				while (true)
				{
					i[x] += y;

					if (!inRange(i[x]))
						break;
					if (JayChess.board.getType(i[0], i[1]) != match)
						continue;

					if (JayChess.board.verifyMove(i, f))
						return true;
				}
			}
		}

		return false;
	}

	public static boolean processQueen(int i[], int f[])
	{
		if (processBishop(i, f, 'Q') || processRook(i, f, 'Q'))
			return true;

		return false;
	}

	public static boolean processKing(int i[], int f[])
	{
		for (i[0] = f[0] - 1; i[0] <= f[0] + 1; i[0]++)
		{
			for (i[1] = f[1] - 1; i[1] <= f[1] + 1; i[1]++)
			{
				if (!inRange(i[0]) || !inRange(i[1]))
					continue;
				if (JayChess.board.getType(i[0], i[1]) != 'K')
					continue;

				if (JayChess.board.verifyMove(i, f))
					return true;
			}
		}

		return false;
	}

	public static boolean processPawn(char t, int i[], int f[])
	{
		if (t == 'W')
		{
			i[0] = f[0] + 1;
			if (inRange(i[0]))
			{
				if (JayChess.board.verifyMove(i, f))
					return true;
			}
			else
				return false;

			i[0]++;
			if (inRange(i[0]))
			{
				if (JayChess.board.verifyMove(i, f))
					return true;
			}
			else
				return false;
		}
		else if (t == 'B')
		{
			i[0] = f[0] - 1;
			if (inRange(i[0]))
			{
				if (JayChess.board.verifyMove(i, f))
					return true;
			}
			else
				return false;

			i[0]--;
			if (inRange(i[0]))
			{
				if (JayChess.board.verifyMove(i, f))
					return true;
			}
			else
				return false;
		}

		return false;
	}

	public static boolean processMove(char p, char t, int i[], int f[])
	{
		switch (p)
		{
			case 'N':
				return processKnight(i, f);
			case 'B':
				return processBishop(i, f, p);
			case 'R':
				return processRook(i, f, p);
			case 'Q':
				return processQueen(i, f);
			case 'K':
				return processKing(i, f);
			case 'O':
				return JayChess.board.verifyMove(i, f);
			case 'P':
				return processPawn(t, i, f);
			default:
				return false;
		}
	}
}
