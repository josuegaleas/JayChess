/*
 * Author: Josue Galeas
 * Last Edit: September 16, 2017
 */

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.GridBagLayout;
import java.awt.GridLayout;

import javax.swing.BorderFactory;
import javax.swing.JLabel;
import javax.swing.JPanel;

@SuppressWarnings("serial")
public class ChessBoard extends JPanel
{
	private Board board;
	private SideBar sideBar;

	public ChessBoard()
	{
		setLayout(new FlowLayout());

		JPanel game = new JPanel();
		game.setLayout(new BorderLayout());
		game.setBorder(BorderFactory.createLineBorder(Color.DARK_GRAY, 2));
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
			JPanel center = new JPanel();
			center.setLayout(new GridLayout(1, 8));
			center.setPreferredSize(new Dimension(500, 20));
			center.setBackground(Color.WHITE);

			for (Character c = 'a'; c <= 'h'; c++)
				center.add(new JLabel(c.toString(), 0));

			setLayout(new GridBagLayout());
			setBackground(Color.WHITE);
			add(center);
		}
	}

	private class RanksBar extends JPanel
	{
		public RanksBar()
		{
			JPanel center = new JPanel();
			center.setLayout(new GridLayout(8, 1));
			center.setPreferredSize(new Dimension(20, 500));
			center.setBackground(Color.WHITE);

			for (Integer c = 8; c >= 1; c--)
				center.add(new JLabel(c.toString(), 0));

			setLayout(new GridBagLayout());
			add(center);
		}
	}
}
