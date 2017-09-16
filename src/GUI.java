/*
 * Author: Josue Galeas
 * Last Edit: September 16, 2017
 */

import java.awt.FlowLayout;

import javax.swing.JFrame;

@SuppressWarnings("serial")
public class GUI extends JFrame
{
	private ChessBoard chessBoard;
	private SideBar sideBar;

	public GUI()
	{
		setTitle("JNIChess");
		setLayout(new FlowLayout());

		chessBoard = new ChessBoard();
		sideBar = new SideBar();
		chessBoard.setSideBar(sideBar);
		sideBar.setChessBoard(chessBoard);
		add(chessBoard);
		add(sideBar);

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
