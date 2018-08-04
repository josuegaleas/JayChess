/*
 * Author: Josue Galeas
 * Last Edit: 2018.08.04
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
	private Color borderColor = Color.DARK_GRAY;
	private Color lightTile = Color.LIGHT_GRAY;
	private Color darkTile = Color.GRAY;
	private Color highlightTile = Color.GREEN;

	public Board()
	{
		setLayout(new GridLayout(8, 8));
		setPreferredSize(new Dimension(500, 500));
		setBackground(borderColor);

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
	static
	{
		System.loadLibrary("JNI");
	}

	public native char getColor(int x, int y);
	public native char getType(int x, int y);
	public native void createBoard();
	public native void deleteBoard();
	public native boolean verifyMove(int i[], int f[]);

	public void setSideBar(SideBar sb) {sideBar = sb;}

	public void setLabel(int x, int y)
	{
		char color = getColor(x, y);
		char type = getType(x, y);

		if (color == 'E' && type == 'E')
		{
			board[x][y].setLabel("");
		}
		else if (color == 'W')
		{
			switch (type)
			{
				case 'P':
					board[x][y].setLabel("♙");
					break;
				case 'N':
					board[x][y].setLabel("♘");
					break;
				case 'B':
					board[x][y].setLabel("♗");
					break;
				case 'R':
					board[x][y].setLabel("♖");
					break;
				case 'Q':
					board[x][y].setLabel("♕");
					break;
				case 'K':
					board[x][y].setLabel("♔");
					break;
				default:
					board[x][y].setLabel("ERROR");
			}
		}
		else if (color == 'B')
		{
			switch (type)
			{
				case 'P':
					board[x][y].setLabel("♟");
					break;
				case 'N':
					board[x][y].setLabel("♞");
					break;
				case 'B':
					board[x][y].setLabel("♝");
					break;
				case 'R':
					board[x][y].setLabel("♜");
					break;
				case 'Q':
					board[x][y].setLabel("♛");
					break;
				case 'K':
					board[x][y].setLabel("♚");
					break;
				default:
					board[x][y].setLabel("ERROR");
			}
		}
		else
			board[x][y].setLabel("ERROR");
	}

	public void setTile(int x, int y)
	{
		int tile = (x * 8) + y + (x % 2);

		if (tile % 2 == 0)
			board[x][y].setBackground(lightTile);
		else
			board[x][y].setBackground(darkTile);
	}

	public void updateSideBar()
	{
		sideBar.updateTextBox(an, turn);
		an = "CLEARED";
	}

	public void updateBoard()
	{
		for (int i = 0; i < 8; i++)
			for (int j = 0; j < 8; j++)
				setLabel(i, j);
	}

	public void resetInitFin()
	{
		init[0] = init[1] = -1;
		fin[0] = fin[1] = -1;
	}

	public char flipColor(char col)
	{
		if (col == 'W')
			return 'B';
		else if (col == 'B')
			return 'W';
		else
			return 'E';
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
		resetInitFin();
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
			else if (color != turn)
			{
				System.out.println("Not your piece!");
				return;
			}
			else
			{
				init[0] = x;
				init[1] = y;
				click = true;
				board[x][y].setBackground(highlightTile);
			}
		}
		else
		{
			fin[0] = x;
			fin[1] = y;
			click = false;

			boolean move = verifyMove(init, fin);
			setTile(init[0], init[1]);
			resetInitFin();

			if (move)
			{
				updateBoard();
				updateSideBar();
				turn = flipColor(turn);
			}
			else
			{
				System.out.println("Not a valid move!");
			}
		}
	}
}
