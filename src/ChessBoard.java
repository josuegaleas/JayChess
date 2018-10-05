/*
 * Author: Josue Galeas
 * Last Edit: 2018.10.05
 */

import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.GridBagLayout;
import java.awt.GridLayout;
import javax.swing.BorderFactory;
import javax.swing.JLabel;
import javax.swing.JPanel;

@SuppressWarnings("serial")
public class ChessBoard extends JPanel
{
	public Board board;
	public SideBar sideBar;
	public MessageBox messageBox;

	public ChessBoard()
	{
		var foo = new JPanel(new BorderLayout());
		var border = BorderFactory.createLineBorder(Settings.borderColor, 2);
		foo.setBorder(border);
		foo.add(board = new Board());
		foo.add(new FilesBar(), BorderLayout.NORTH);
		foo.add(new RanksBar(), BorderLayout.EAST);
		foo.add(new FilesBar(), BorderLayout.SOUTH);
		foo.add(new RanksBar(), BorderLayout.WEST);

		var bar = new JPanel(new BorderLayout());
		bar.add(foo);
		bar.add(messageBox = new MessageBox(), BorderLayout.SOUTH);

		add(bar);
		add(sideBar = new SideBar());

		board.chessBoard = this;
		sideBar.chessBoard = this;
	}

	private class FilesBar extends JPanel
	{
		public FilesBar()
		{
			var center = new JPanel(new GridLayout(1, 8));
			center.setPreferredSize(new Dimension(500, 20));
			center.setBackground(Settings.boxColor);

			for (Character file = 'a'; file <= 'h'; file++)
				center.add(new JLabel(file.toString(), 0));

			setLayout(new GridBagLayout());
			setBackground(Settings.boxColor);
			add(center);
		}
	}

	private class RanksBar extends JPanel
	{
		public RanksBar()
		{
			var center = new JPanel(new GridLayout(8, 1));
			center.setPreferredSize(new Dimension(20, 500));
			center.setBackground(Settings.boxColor);

			for (Integer rank = 8; rank >= 1; rank--)
				center.add(new JLabel(rank.toString(), 0));

			setLayout(new GridBagLayout());
			setBackground(Settings.boxColor);
			add(center);
		}
	}
}
