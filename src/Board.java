/*
 * Author: Josue Galeas
 * Last Edit: September 16, 2017
 */

import java.awt.Color;
import java.awt.Dimension;
import java.awt.GridLayout;

import javax.swing.JPanel;

@SuppressWarnings("serial")
public class Board extends JPanel
{
	private SideBar sideBar;
	private ChessPanel[][] board = new ChessPanel[8][8];
	private String an = "EMPTY";

	public Board()
	{
		setLayout(new GridLayout(8, 8));
		setPreferredSize(new Dimension(500, 500));
		setBackground(Color.DARK_GRAY);

		for (int x = 0; x < 8; x++)
		{
			for (int y = 0; y < 8; y++)
			{
				board[x][y] = new ChessPanel(x, y);
				updateTileOf(x, y);
				add(board[x][y]);
			}
		}

		createBoard();
		updateBoard();
		ChessPanel.setBoard(this);
	}

	static
	{
		System.loadLibrary("BoardJNI");
	}

	public native void createBoard();

	public native void updateBoard();

	public native void deleteBoard();

	public native char getColorOf(int x, int y);

	public native boolean verifyMove(int ix, int iy, int fx, int fy);

	public void setSideBar(SideBar sb)
	{
		sideBar = sb;
	}

	public void updateLabelOf(int x, int y, String l)
	{
		board[x][y].setLabel(l);
	}

	public void updateTileOf(int x, int y)
	{
		int t = x * 8 + y + x % 2;

		if (t % 2 == 0)
			board[x][y].setBackground(Color.LIGHT_GRAY);
		else
			board[x][y].setBackground(Color.GRAY);
	}

	public void updateSideBar()
	{
		boolean cond = ChessPanel.getTurn() == 'W';
		sideBar.updateTextBox(an, cond);
		an = "CLEAR";
	}

	public void newGame()
	{
		deleteBoard();
		createBoard();
		updateBoard();
		ChessPanel.setBoard(this);
	}
}
