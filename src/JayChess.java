/*
 * Author: Josue Galeas
 * Last Edit: 2018.08.04
 */

import java.awt.Color;
import javax.swing.JFrame;

@SuppressWarnings("serial")
public class JayChess extends JFrame
{
	public static Color borderColor = Color.DARK_GRAY;
	public static Color boxColor = Color.WHITE;
	public static Color lightTile = Color.LIGHT_GRAY;
	public static Color darkTile = Color.GRAY;
	public static Color highlightTile = Color.GREEN;
	public static int delay = 1;

	public static Board board;
	public static SideBar sideBar;
	public static MessageBox messageBox;
	public static PGN pgn;

	public JayChess()
	{
		setTitle("JayChess");
		add(new ChessBoard());

		pack();
		setResizable(false);
		setVisible(true);
		setLocationRelativeTo(null);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	}

	public static void main(String[] args)
	{
		new JayChess();
	}
}
