/*
 * Author: Josue Galeas
 * Last Edit: September 6, 2017
 */

import java.awt.Color;
import java.awt.Dimension;
import java.awt.GridLayout;

import javax.swing.JLabel;
import javax.swing.JPanel;

@SuppressWarnings("serial")
public class Board extends JPanel
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
				add(board[x][y]);
			}
		}

		createBoard();
		updateBoard(this);
	}

	static
	{
		System.loadLibrary("BoardJNI");
	}

	public native void createBoard();

	public native void updateBoard(Board g);

	public native void deleteBoard();

	public void updateLabelOf(int x, int y, String l)
	{
		board[x][y].setLabel(l);
	}
}
