/*
 * Author: Josue Galeas
 * Last Edit: 2018.08.04
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
	private Color borderColor = Color.DARK_GRAY;
	private Color barColor = Color.WHITE;

	public ChessBoard()
	{
		Board board;
		SideBar sideBar;

		JPanel game = new JPanel(new BorderLayout());
		game.setBorder(BorderFactory.createLineBorder(borderColor, 2));
		game.add(board = new Board());
		game.add(new FilesBar(), BorderLayout.NORTH);
		game.add(new RanksBar(), BorderLayout.EAST);
		game.add(new FilesBar(), BorderLayout.SOUTH);
		game.add(new RanksBar(), BorderLayout.WEST);

		add(game);
		add(sideBar = new SideBar());
		board.setSideBar(sideBar);
		sideBar.setBoard(board);
	}

	private class FilesBar extends JPanel
	{
		public FilesBar()
		{
			JPanel center = new JPanel(new GridLayout(1, 8));
			center.setPreferredSize(new Dimension(500, 20));
			center.setBackground(barColor);

			for (Character c = 'a'; c <= 'h'; c++)
				center.add(new JLabel(c.toString(), 0));

			setLayout(new GridBagLayout());
			setBackground(barColor);
			add(center);
		}
	}

	private class RanksBar extends JPanel
	{
		public RanksBar()
		{
			JPanel center = new JPanel(new GridLayout(8, 1));
			center.setPreferredSize(new Dimension(20, 500));
			center.setBackground(barColor);

			for (Integer c = 8; c >= 1; c--)
				center.add(new JLabel(c.toString(), 0));

			setLayout(new GridBagLayout());
			setBackground(barColor);
			add(center);
		}
	}
}
