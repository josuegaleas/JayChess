/*
 * Author: Josue Galeas
 * Last Edit: 2018.08.12
 */

import java.awt.Color;
import java.awt.Dimension;
import java.awt.GridLayout;
import java.util.HashMap;

import javax.swing.JPanel;

@SuppressWarnings("serial")
public class Board extends JPanel
{
	private static SideBar sideBar;
	private static MessageBox messageBox;

	private ChessPanel[][] board;
	private HashMap<String, String> symbolMap;
	private String an = "EMPTY";
	private boolean click = false;
	private char turn = 'W';
	private int init[] = {-1, -1};
	private int fin[] = {-1, -1};

	private Color borderColor = Color.DARK_GRAY;
	private Color lightTile = Color.LIGHT_GRAY;
	private Color darkTile = Color.GRAY;
	private Color highlightTile = Color.GREEN;
	private int delay = 1;

	public Board()
	{
		setLayout(new GridLayout(8, 8));
		setPreferredSize(new Dimension(500, 500));
		setBackground(borderColor);

		board = new ChessPanel[8][8];
		for (int x = 0; x < 8; x++)
		{
			for (int y = 0; y < 8; y++)
			{
				board[x][y] = new ChessPanel(x, y);
				setTile(x, y);
				add(board[x][y]);
			}
		}

		symbolMap = new HashMap<String, String>();
		symbolMap.put("WP", "♙");
		symbolMap.put("WN", "♘");
		symbolMap.put("WB", "♗");
		symbolMap.put("WR", "♖");
		symbolMap.put("WQ", "♕");
		symbolMap.put("WK", "♔");
		symbolMap.put("BP", "♟");
		symbolMap.put("BN", "♞");
		symbolMap.put("BB", "♝");
		symbolMap.put("BR", "♜");
		symbolMap.put("BQ", "♛");
		symbolMap.put("BK", "♚");

		createBoard();
		updateBoard();
		ChessPanel.setBoard(this);
	}
	static
	{
		System.loadLibrary("JNI");
	}

	public native void createBoard();
	public native void deleteBoard();
	public native char getColor(int x, int y);
	public native char getType(int x, int y);
	public native boolean verifyMove(int i[], int f[]);

	public static void setSideBar(SideBar sb) {sideBar = sb;}

	public static void setMessageBox(MessageBox mb) {messageBox = mb;}

	public void setLabel(int x, int y)
	{
		Character color = getColor(x, y);
		Character type = getType(x, y);
		var piece = color.toString() + type.toString();

		if (piece.equals("EE"))
			board[x][y].setLabel("");
		else
		{
			if (symbolMap.get(piece) != null)
				board[x][y].setLabel(symbolMap.get(piece));
			else
				board[x][y].setLabel("ERROR");
		}
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

	public char nextColor(char col)
	{
		if (col == 'W')
		{
			messageBox.setMessage("Black's Turn");
			return 'B';
		}
		else if (col == 'B')
		{
			messageBox.setMessage("White's Turn");
			return 'W';
		}
		else
		{
			messageBox.setMessage("ERROR");
			return 'E';
		}
	}

	public void newGame()
	{
		if (messageBox.getWaiting())
			return;

		deleteBoard();
		createBoard();
		updateBoard();

		if (click)
			setTile(init[0], init[1]);

		an = "EMPTY";
		click = false;
		turn = 'W';
		resetInitFin();

		messageBox.setMessage("White's Turn");
		repaint();
	}

	public void processClick(int x, int y)
	{
		if (messageBox.getWaiting())
			return;

		if (!click)
		{
			char color = getColor(x, y);

			if (color == 'E')
				return;
			else if (color == turn)
			{
				init[0] = x;
				init[1] = y;
				click = true;
				board[x][y].setBackground(highlightTile);
			}
			else
				messageBox.customMessage("Not your piece!", delay);
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
				turn = nextColor(turn);
			}
			else
				messageBox.customMessage("Not a valid move!", delay);
		}
	}
}
