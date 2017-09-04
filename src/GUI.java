/*
 * Author: Josue Galeas
 * Last Edit: September 4, 2017
 */

import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;

@SuppressWarnings("serial")
public class GUI extends JFrame
{
	public GUI()
	{
		setTitle("JNIChess");
		setLayout(new FlowLayout());

		add(new ChessBoard());
		// add(new SideBar());

		pack();
		setResizable(false);
		setVisible(true);
		setLocationRelativeTo(null);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	}

	private class SideBar extends JPanel implements ActionListener
	{
		public SideBar()
		{
			setLayout(new GridLayout(8, 1));
			setPreferredSize(new Dimension(100, 540));

			for (int c = 0; c < 8; c++)
			{
				add(new JButton(Integer.toString(c)));
			}
		}

		@Override
		public void actionPerformed(ActionEvent e)
		{

		}
	}

	public static void main(String[] args)
	{
		new GUI();
	}
}
