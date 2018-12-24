/*
 * Author: Josue Galeas
 * Last Edit: 2018.12.24
 */

import java.awt.Dimension;
import java.awt.GridLayout;
import java.io.File;
import java.util.HashMap;
import javax.swing.JPanel;

@SuppressWarnings("serial")
public class Board extends JPanel
{
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
		// symbolMap.put("BP", "♟"); // TODO: Not displaying, weird bug with Java?
		symbolMap.put("BP", "BP");
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
			var symbol = symbolMap.get(piece);

			if (symbol != null)
				chessPanels[x][y].setLabel(symbol);
			else
				chessPanels[x][y].setLabel(piece + "?");
		}
	}

	private void setInitFin()
	{
		init[0] = init[1] = -1;
		fin[0] = fin[1] = -1;
	}

	private void updateSideBar()
	{
		Game.sideBar.updateTextBox(an, turn);
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
				Game.messageBox.setMessage("Black's Turn");
				return 'B';
			case 'B':
				Game.messageBox.setMessage("White's Turn");
				return 'W';
			default:
				Game.messageBox.setMessage("ERROR: Turn could not be determined.");
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

		Game.pgn.clear();
		an = "EMPTY";
		click = false;
		turn = 'W';
		setInitFin();

		Game.messageBox.setMessage("White's Turn");
		repaint();
	}

	public void loadGame(File f) throws Exception
	{
		Object[] moves = Game.pgn.ReadPGN(f); // Objects are type String

		// TODO
		newGame(); // Destructive
		String move;
		char valid = '?';

		for (int i = 0; i < moves.length; i++)
		{
			setInitFin();
			move = (String)moves[i]; // I don't like this, but it's a String
			valid = Parse.convertMove(move, turn, init, fin);

			if (valid == '?')
			{
				// TODO
				System.out.printf("Could not process move: %s\n", move);
				newGame();
				throw new Exception();
			}
			else
			{
				System.out.printf("%s --> (%d, %d) to (%d, %d)\n", move, init[0], init[1], fin[0], fin[1]);
			}

			if (turn == 'W')
				turn = 'B';
			else if (turn == 'B')
				turn = 'W';
			else
				throw new Exception();
		}
	}

	public void processClick(int x, int y)
	{
		if (Game.messageBox.getWaiting())
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
				Game.messageBox.setTempMessage("Not your piece!");
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
				Game.pgn.addMove(an);
				updateSideBar();

				if (getCheckmate())
				{
					if (turn == 'W')
						Game.messageBox.setMessage("White Wins");
					else if (turn == 'B')
						Game.messageBox.setMessage("Black Wins");
					else
						Game.messageBox.setMessage("ERROR: Checkmate could not be determined.");
				}
				else
					turn = nextColor(turn);
			}
			else
				Game.messageBox.setTempMessage("Not a valid move!");
		}
	}
}
