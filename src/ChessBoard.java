/*
 * Author: Josue Galeas
 * Last Edit: 2018.12.24
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
	public ChessBoard()
	{
		JayChess.board = new Board();
		JayChess.messageBox = new MessageBox();
		JayChess.sideBar = new SideBar();
		JayChess.pgn = new PGN();

		var foo = new JPanel(new BorderLayout());
		var border = BorderFactory.createLineBorder(JayChess.borderColor, 2);
		foo.setBorder(border);
		foo.add(JayChess.board);
		foo.add(new FilesBar(), BorderLayout.NORTH);
		foo.add(new RanksBar(), BorderLayout.EAST);
		foo.add(new FilesBar(), BorderLayout.SOUTH);
		foo.add(new RanksBar(), BorderLayout.WEST);

		var bar = new JPanel(new BorderLayout());
		bar.add(foo);
		bar.add(JayChess.messageBox, BorderLayout.SOUTH);

		add(bar);
		add(JayChess.sideBar);
	}

	private class FilesBar extends JPanel
	{
		public FilesBar()
		{
			var center = new JPanel(new GridLayout(1, 8));
			center.setPreferredSize(new Dimension(500, 20));
			center.setBackground(JayChess.boxColor);

			for (Character file = 'a'; file <= 'h'; file++)
				center.add(new JLabel(file.toString(), 0));

			setLayout(new GridBagLayout());
			setBackground(JayChess.boxColor);
			add(center);
		}
	}

	private class RanksBar extends JPanel
	{
		public RanksBar()
		{
			var center = new JPanel(new GridLayout(8, 1));
			center.setPreferredSize(new Dimension(20, 500));
			center.setBackground(JayChess.boxColor);

			for (Integer rank = 8; rank >= 1; rank--)
				center.add(new JLabel(rank.toString(), 0));

			setLayout(new GridBagLayout());
			setBackground(JayChess.boxColor);
			add(center);
		}
	}
}
