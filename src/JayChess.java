/*
 * Author: Josue Galeas
 * Last Edit: 2018.02.25
 */

import javax.swing.JFrame;

@SuppressWarnings("serial")
public class JayChess extends JFrame
{
	public JayChess()
	{
		setTitle("JayChess (Alpha 2018.02.25)");
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
