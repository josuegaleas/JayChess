/*
 * Author: Josue Galeas
 * Last Edit: 2018.10.16
 */

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.util.Vector;

public class PGN
{
	public ChessBoard chessBoard;
	private Vector<String> moves;
	private Vector<String> games; // TODO: Another dimension for multiple games?
	private String[] gameEndings = {"1-0", "0-1", "1/2-1/2", "*"};

	public PGN(ChessBoard cb)
	{
		chessBoard = cb;
		moves = new Vector<String>();
		games = new Vector<String>();
	}

	public void clear()
	{
		moves.clear();
		games.clear();
	}

	public void addMove(String m) {moves.add(m);}

	private boolean endsWith(String l)
	{
		for (int i = 0; i < 4; i++)
			if (l.endsWith(gameEndings[i]))
				return true;

		return false;
	}

	public Object[] ReadPGN(File f)
	{
		// Sort of unsafe reading, but this allows for flexibility in parsing
		// data in PGN files, especially with the variety of tags there can be.
		try
		{
			var reader = new BufferedReader(new FileReader(f));
			games.clear();

			String line;
			while ((line = reader.readLine()) != null)
			{
				games.add(line);

				if (endsWith(line))
					break;
			}

			reader.close();
			String moveLine = games.lastElement();
			String[] moveList = moveLine.split(" ");

			// TODO: Clean the following up
			Integer num = 1;
			String number;
			boolean comment = false;
			var parsedMoves = new Vector<String>();

			for (int i = 0; i < moveList.length; i++)
			{
				if (moveList[i].startsWith("{"))
				{
					comment = true;
					continue;
				}
				else if (moveList[i].endsWith("}"))
				{
					comment = false;
					continue;
				}
				else if (comment)
					continue;
				else if (i == moveList.length - 1)
					break;
				else if (moveList[i].endsWith("."))
				{
					number = num.toString() + ".";

					if (moveList[i].equals(number))
						num++;
					else
						throw new Exception();
				}
				else
					parsedMoves.add(moveList[i]);
			}

			return parsedMoves.toArray();
		}
		catch (Exception e)
		{
			chessBoard.messageBox.setTempMessage("Error loading PGN file!");
			games.clear();
			return null;
		}
	}
}
