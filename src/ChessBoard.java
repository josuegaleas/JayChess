/*
 * Author: Josue Galeas
 * Last Edit: April 1, 2017
 */

import java.awt.Color;
import java.awt.Dimension;
import java.awt.GridLayout;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;

import javax.swing.JPanel;

@SuppressWarnings("serial")
public class ChessBoard extends JPanel
{
	private ChessPanel[][] panels = new ChessPanel[8][8];

	public ChessBoard()
	{
		setLayout(new GridLayout(8, 8));
		setPreferredSize(new Dimension(500, 500));
		setBackground(Color.GRAY);

		for (int x = 0; x < 8; x++)
		{
			for (int y = 0; y < 8; y++)
			{
				panels[x][y] = new ChessPanel(x, y);
				add(panels[x][y]);
			}
		}
	}

	private class ChessPanel extends JPanel implements MouseListener
	{
		private int x;
		private int y;

		public ChessPanel(int x, int y)
		{
			this.x = x;
			this.y = y;
			addMouseListener(this);

			Color light = new Color(250, 210, 160);
			Color dark = new Color(210, 140, 70);

			if (x % 2 == 0)
			{
				if (y % 2 == 0)
					setBackground(light);
				else
					setBackground(dark);
			}
			else
			{
				if (y % 2 != 0)
					setBackground(light);
				else
					setBackground(dark);
			}
		}

		@Override
		public void mouseClicked(MouseEvent e)
		{
			System.out.printf("There was a click at (%d, %d)!\n", x, y);
		}

		@Override
		public void mousePressed(MouseEvent e) {}

		@Override
		public void mouseReleased(MouseEvent e) {}

		@Override
		public void mouseEntered(MouseEvent e) {}

		@Override
		public void mouseExited(MouseEvent e) {}
	}
}
