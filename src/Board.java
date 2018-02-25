/*
 * Author: Josue Galeas
 * Last Edit: 2017.09.22
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
	private boolean click = false;
	private char turn = 'W';
	private int init[] = {-1, -1};
	private int fin[] = {-1, -1};
	private String an = "EMPTY";

	static
	{
		System.loadLibrary("BoardJNI");
	}
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
				setTile(x, y);
				add(board[x][y]);
			}
		}

		createBoard();
		updateBoard();
		ChessPanel.setBoard(this);
	}

	public native void createBoard();
	public native void updateBoard();
	public native void deleteBoard();
	public native char getColor(int x, int y);
	public native boolean verifyMove(int i[], int f[]);
	public void setSideBar(SideBar sb) {sideBar = sb;}

	public void setLabel(int x, int y, String l)
	{
		board[x][y].setLabel(l);
	}

	public void setTile(int x, int y)
	{
		int t = x * 8 + y + x % 2;

		if (t % 2 == 0)
			board[x][y].setBackground(Color.LIGHT_GRAY);
		else
			board[x][y].setBackground(Color.GRAY);
	}

	public void updateSideBar()
	{
		sideBar.updateTextBox(an, turn == 'W');
		an = "CLEAR";
	}

	public void newGame()
	{
		deleteBoard();
		createBoard();
		updateBoard();

		if (click)
			setTile(init[0], init[1]);
		click = false;
		turn = 'W';
		init[0] = init[1] = -1;
		fin[0] = fin[1] = -1;
		an = "EMPTY";
		repaint();
	}

	public void processClick(int x, int y)
	{
		if (!click)
		{
			char color = getColor(x, y);

			if (color == 'E')
				return;
			if (color != turn)
			{
				System.out.println("Not your piece!");
				return;
			}

			init[0] = x;
			init[1] = y;
			click = true;
			board[x][y].setBackground(Color.GREEN);
		}
		else
		{
			fin[0] = x;
			fin[1] = y;
			click = false;

			boolean move = verifyMove(init, fin);
			setTile(init[0], init[1]);

			init[0] = init[1] = -1;
			fin[0] = fin[1] = -1;

			if (move)
			{
				updateBoard();
				updateSideBar();
				turn = (turn == 'W') ? 'B':'W';
			}
			else
			{
				System.out.println("Not a valid move!");
			}
		}
	}
}
