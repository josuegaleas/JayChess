/*
 * Author: Josue Galeas
 * Last Edit: 2018.10.11
 */

public class Parse
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
			case 'N':
				break;
			case 'B':
				break;
			case 'R':
				break;
			case 'Q':
				break;
			case 'K':
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

					return '0';
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
}
