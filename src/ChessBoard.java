/*
 * Author: Josue Galeas
 * Last Edit: September 4, 2017
 */

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.GridLayout;
import java.awt.GridBagLayout;

import javax.swing.BorderFactory;
import javax.swing.JLabel;
import javax.swing.JPanel;

@SuppressWarnings("serial")
public class ChessBoard extends JPanel
{
	private Board game;

	public ChessBoard()
	{
		setLayout(new BorderLayout());
		setBorder(BorderFactory.createLineBorder(Color.GRAY, 2));

		game = new Board();
		add(game);
		add(new FilesBar(), BorderLayout.NORTH);
		add(new RanksBar(), BorderLayout.EAST);
		add(new FilesBar(), BorderLayout.SOUTH);
		add(new RanksBar(), BorderLayout.WEST);

		createBoard();
		updateBoard(game);
	}

	static
	{
		System.loadLibrary("ChessBoard");
	}

	public native void createBoard();

	public native void updateBoard(Board g);

	public native void deleteBoard();

	private class Board extends JPanel
	{
		private ChessPanel[][] board = new ChessPanel[8][8];

		public Board()
		{
			setLayout(new GridLayout(8, 8));
			setPreferredSize(new Dimension(500, 500));
			setBackground(Color.GRAY);

			for (int x = 0; x < 8; x++)
			{
				for (int y = 0; y < 8; y++)
				{
					board[x][y] = new ChessPanel(x, y);
					add(new ChessPanel(x, y));
				}
			}
		}

		public void updateLabelOf(int x, int y, String l)
		{
			board[x][y].setLabel(l);
		}
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
