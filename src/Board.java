/*
 * Author: Josue Galeas
 * Last Edit: 2018.10.11
 */

import java.awt.Dimension;
import java.awt.GridLayout;
import java.io.File;
import java.util.HashMap;
import javax.swing.JPanel;

@SuppressWarnings("serial")
public class Board extends JPanel
{
	public ChessBoard chessBoard;
	private PGN pgn;
	private ChessPanel[][] chessPanels;
	private HashMap<String, String> symbolMap;
	private String an = "EMPTY";
	private boolean click = false;
	private char turn = 'W';
	private int init[] = {-1, -1};
	private int fin[] = {-1, -1};

	public Board()
	{
		setLayout(new GridLayout(8, 8));
		setPreferredSize(new Dimension(500, 500));
		setBackground(Settings.borderColor);

		pgn = new PGN(chessBoard);
		chessPanels = new ChessPanel[8][8];
		ChessPanel.board = this;
		for (int x = 0; x < 8; x++)
			for (int y = 0; y < 8; y++)
				add(chessPanels[x][y] = new ChessPanel(x, y));

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
	}
	static
	{
		System.loadLibrary("JNI");
	}

	public native void createBoard();
	public native void deleteBoard();
	public native char getColor(int x, int y);
	public native char getType(int x, int y);
	public native boolean getCheckmate();
	public native boolean verifyMove(int i[], int f[]);

	private void setLabel(int x, int y)
	{
		Character color = getColor(x, y);
		Character type = getType(x, y);
		String piece = color.toString() + type.toString();

		if (piece.equals("EE"))
			chessPanels[x][y].setLabel("");
		else
		{
			if (symbolMap.get(piece) != null)
				chessPanels[x][y].setLabel(symbolMap.get(piece));
			else
				chessPanels[x][y].setLabel("ERROR");
		}
	}

	private void setInitFin()
	{
		init[0] = init[1] = -1;
		fin[0] = fin[1] = -1;
	}

	private void updateSideBar()
	{
		chessBoard.sideBar.updateTextBox(an, turn);
		an = "CLEARED";
	}

	private void updateBoard()
	{
		for (int i = 0; i < 8; i++)
			for (int j = 0; j < 8; j++)
				setLabel(i, j);
	}

	private char nextColor(char col)
	{
		switch (col)
		{
			case 'W':
				chessBoard.messageBox.setMessage("Black's Turn");
				return 'B';
			case 'B':
				chessBoard.messageBox.setMessage("White's Turn");
				return 'W';
			default:
				chessBoard.messageBox.setMessage("ERROR: Turn could not be determined.");
				return 'E';
		}
	}

	private char nextColorSilent(char col)
	{
		switch (col)
		{
			case 'W':
				return 'B';
			case 'B':
				return 'W';
			default:
				return 'E';
		}
	}

	public void newGame()
	{
		// TODO: Check if game is not saved?
		deleteBoard();
		createBoard();
		updateBoard();

		if (click)
			chessPanels[init[0]][init[1]].setBackground();

		pgn.clear();
		an = "EMPTY";
		click = false;
		turn = 'W';
		setInitFin();

		chessBoard.messageBox.setMessage("White's Turn");
		repaint();
	}

	public boolean loadGame(File f)
	{
		// TODO
		Object[] moves = pgn.ReadPGNFile(f); // Objects are type String
		if (moves == null)
			return false;

		// TODO
		String temp;
		char turn = 'W';
		char valid = '?';

		for (int i = 0; i < moves.length; i++)
		{
			setInitFin();
			temp = (String)moves[i]; // I don't like this, but it's a String
			valid = Parse.convertMove(temp, turn, init, fin);

			if (valid == '?')
				System.out.printf("Could not process %s.\n", temp);
			else
			{
				System.out.printf("Processed %s. Init: (%d, %d) Fin: (%d, %d)\n", temp, init[0], init[1], fin[0], fin[1]);
			}

			turn = nextColorSilent(turn);
		}

		return false;
	}

	public void processClick(int x, int y)
	{
		if (chessBoard.messageBox.getWaiting())
			return;

		if (getCheckmate())
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
				chessPanels[x][y].setBackground(Settings.highlightTile);
			}
			else
				chessBoard.messageBox.setTempMessage("Not your piece!");
		}
		else
		{
			fin[0] = x;
			fin[1] = y;
			click = false;

			boolean move = verifyMove(init, fin);
			chessPanels[init[0]][init[1]].setBackground();
			setInitFin();

			if (move)
			{
				updateBoard();
				pgn.addMove(an);
				updateSideBar();

				if (getCheckmate())
				{
					if (turn == 'W')
						chessBoard.messageBox.setMessage("White Wins");
					else if (turn == 'B')
						chessBoard.messageBox.setMessage("Black Wins");
					else
						chessBoard.messageBox.setMessage("ERROR: Checkmate could not be determined.");
				}
				else
					turn = nextColor(turn);
			}
			else
				chessBoard.messageBox.setTempMessage("Not a valid move!");
		}
	}
}
