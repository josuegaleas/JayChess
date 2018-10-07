/*
 * Author: Josue Galeas
 * Last Edit: 2018.10.07
 */

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.util.List;
import java.util.Vector;

public class PGN
{
	public ChessBoard chessBoard;
	private List<String> moves; // TODO: For saving games later

	private List<String> game; // TODO: Another dimension for multiple games?
	private String[] endings = {"1-0", "0-1", "1/2-1/2", "*"};

	// TODO: change name maybe
	private boolean endsWith(String l)
	{
		for (int i = 0; i < 4; i++)
			if (l.endsWith(endings[i]))
				return true;

		return false;
	}

	public void ReadPGNFile(File f)
	{
		try
		{
			var reader = new BufferedReader(new FileReader(f));
			game = new Vector<String>();

			String line = reader.readLine();
			while (line != null)
			{
				game.add(line);

				if (endsWith(line))
					break;

				line = reader.readLine();
			}

			// TODO
			for (int i = 0; i < game.size(); i++)
				System.out.println(game.get(i));
		}
		catch (Exception e)
		{
			System.out.println(e);
			chessBoard.messageBox.setTempMessage("Error loading PGN file!");
		}
	}
}
