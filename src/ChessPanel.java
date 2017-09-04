/*
 * Author: Josue Galeas
 * Last Edit: September 4, 2017
 */

import java.awt.Color;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.Font;
import java.awt.GridBagLayout;

import javax.swing.JLabel;
import javax.swing.JPanel;

@SuppressWarnings("serial")
public class ChessPanel extends JPanel implements MouseListener
{
	private int r;
	private int c;
	private JLabel label;

	public ChessPanel(int x, int y)
	{
		setLayout(new GridBagLayout());
		addMouseListener(this);

		r = x;
		c = y;

		if (x % 2 == 0)
		{
			if (y % 2 == 0)
				setBackground(new Color(250, 210, 160));
			else
				setBackground(new Color(210, 140, 70));
		}
		else
		{
			if (y % 2 != 0)
				setBackground(new Color(250, 210, 160));
			else
				setBackground(new Color(210, 140, 70));
		}

		label = new JLabel("?");
		label.setFont(new Font("Sans Serif", Font.PLAIN, 24));
		add(label);
	}

	static
	{
		System.loadLibrary("ChessPanel");
	}

	public native void printClick(int x, int y);

	public void setLabel(String l)
	{
		label.setText(l);
	}

	@Override
	public void mouseClicked(MouseEvent e)
	{
		printClick(r, c);
	}

	@Override
	public void mousePressed(MouseEvent e) {}

	@Override
	public void mouseReleased(MouseEvent e) {}

	@Override
	public void mouseEntered(MouseEvent e) {}

	@Override
	public void mouseExited(MouseEvent e) {}
}