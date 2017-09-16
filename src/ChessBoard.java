/*
 * Author: Josue Galeas
 * Last Edit: September 16, 2017
 */

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.GridBagLayout;
import java.awt.GridLayout;

import javax.swing.BorderFactory;
import javax.swing.JLabel;
import javax.swing.JPanel;

@SuppressWarnings("serial")
public class ChessBoard extends JPanel
{
	private Board board;

	public ChessBoard()
	{
		setLayout(new BorderLayout());
		setBorder(BorderFactory.createLineBorder(Color.DARK_GRAY, 2));

		board = new Board();
		add(board);
		add(new FilesBar(), BorderLayout.NORTH);
		add(new RanksBar(), BorderLayout.EAST);
		add(new FilesBar(), BorderLayout.SOUTH);
		add(new RanksBar(), BorderLayout.WEST);
	}

	public void setSideBar(SideBar sb)
	{
		board.setSideBar(sb);
	}

	public void newGame()
	{
		board.newGame();
	}

	private class RanksBar extends JPanel
	{
		public RanksBar()
		{
			setLayout(new GridBagLayout());

			JPanel center = new JPanel();
			center.setLayout(new GridLayout(8, 1));
			center.setPreferredSize(new Dimension(20, 500));
			center.setBackground(Color.WHITE);

			for (int c = 8; c >= 1; c--)
				center.add(new JLabel(Integer.toString(c), 0));

			add(center);
		}
	}

	private class FilesBar extends JPanel
	{
		public FilesBar()
		{
			setLayout(new GridBagLayout());
			setBackground(Color.WHITE);

			JPanel center = new JPanel();
			center.setLayout(new GridLayout(1, 8));
			center.setPreferredSize(new Dimension(500, 20));
			center.setBackground(Color.WHITE);

			for (char c = 'a'; c <= 'h'; c++)
				center.add(new JLabel(Character.toString(c), 0));

			add(center);
		}
	}
}
