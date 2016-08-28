/*
 * Author: Josue Galeas
 * Last Edit: August 27th, 2016
 */

import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JFrame;
import javax.swing.JPanel;

@SuppressWarnings("serial")
public class GUI extends JFrame
{
	public GUI()
	{
		setTitle("PlebeianChess");
		setLayout(new FlowLayout());

		add(new Board());
		add(new SideBar());

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
			setPreferredSize(new Dimension(100, 540));
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
