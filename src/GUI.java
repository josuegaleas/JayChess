/*
 * Author: Josue Galeas
 * Last Edit: October 2, 2017
 */

import javax.swing.JFrame;

@SuppressWarnings("serial")
public class GUI extends JFrame
{
	public GUI()
	{
		setTitle("JayChess (Alpha 2017.10.02)");
		add(new ChessBoard());

		pack();
		setResizable(false);
		setVisible(true);
		setLocationRelativeTo(null);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	}

	public static void main(String[] args)
	{
		new GUI();
	}
}
