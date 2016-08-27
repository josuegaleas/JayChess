/*
 * Author: Josue Galeas
 * Last Edit: August 26th, 2016
 */

import java.awt.Color;
import java.awt.Dimension;
import java.awt.GridLayout;
import javax.swing.BorderFactory;
import javax.swing.JPanel;

@SuppressWarnings("serial")
public class ChessBoard extends JPanel
{
	private ChessPanel[][] panels = new ChessPanel[8][8];
	private Color light = new Color(250, 210, 160);
	private Color dark = new Color(210, 140, 70);

	public ChessBoard()
	{
		setLayout(new GridLayout(8, 8));
		setPreferredSize(new Dimension(500, 500));
		setBackground(Color.GRAY);

		for (int x = 0; x < 8; x++)
		{
			for (int y = 0; y < 8; y++)
			{
				panels[x][y] = new ChessPanel();

				if (x % 2 == 0)
				{
					if (y % 2 == 0)
						panels[x][y].setBackground(light);
					else
						panels[x][y].setBackground(dark);
				}
				else
				{
					if (y % 2 != 0)
						panels[x][y].setBackground(light);
					else
						panels[x][y].setBackground(dark);
				}

				add(panels[x][y]);
			}
		}
	}

	private class ChessPanel extends JPanel
	{
		// TODO: Expand this panel to contain pieces

		public ChessPanel()
		{
			// TODO
		}
	}
}
