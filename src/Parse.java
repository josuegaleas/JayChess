/*
 * Author: Josue Galeas
 * Last Edit: 2018.10.09
 */

public class Parse
{
	private static boolean convertRow(char b, int x)
	{
		x = 8 - b;
		if (x >= 0 && x <= 7)
			return true;

		x = -1;
		return false;
	}

	private static boolean convertColumn(char a, int y)
	{
		y = a - 97;
		if (y >= 0 && y <= 7)
			return true;

		y = -1;
		return false;
	}

	private static boolean convertPosition(char a, char b, int x, int y)
	{
		if (convertRow(b, x))
			if (convertColumn(a, y))
				return true;

		x = y = -1;
		return false;
	}

	public static boolean convertMove(String m, char t, int i[], int f[])
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
			case '0':
				i[1] = 4;
				if (m.equals("0-0"))
				{
					f[1] = 6;

					if (t == 'W')
						i[0] = f[0] = 7;
					else if (t == 'B')
						i[0] = f[0] = 0;
				}
				else if (m.equals("0-0-0"))
				{
					f[1] = 2;

					if (t == 'W')
						i[0] = f[0] = 7;
					else if (t == 'B')
						i[0] = f[0] = 0;
				}
				break;
			default:
				// Pawns?
				if (m.charAt(1) == 'x')
				{
					// If pawn captured
					if (m.length() > 3)
					{
						boolean foo1 = convertPosition(m.charAt(2), m.charAt(3), f[0], f[1]);
					}
						return false;
				}
				else
				{
					// If pawn is just moving
					boolean foo2 = convertPosition(m.charAt(0), m.charAt(1), f[0], f[1]);
					boolean foo3 = convertColumn(m.charAt(0), i[1]);
					// i[0] is going to be difficult to determine
				}
		}

		return false;
	}
}
