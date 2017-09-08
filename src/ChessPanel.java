/*
 * Author: Josue Galeas
 * Last Edit: September 8, 2017
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
	private int x;
	private int y;
	private JLabel label;

	private static boolean click = false;
	private static int[] init = new int[2];
	private static int[] fin = new int[2];
	private static Board board;

	public ChessPanel(int x, int y)
	{
		setLayout(new GridBagLayout());
		addMouseListener(this);

		this.x = x;
		this.y = y;

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

		label = new JLabel("E");
		label.setFont(new Font("Sans Serif", Font.PLAIN, 32));
		add(label);
	}

	public void setLabel(String l)
	{
		label.setText(l);
	}

	public void setBoard(Board b)
	{
		board = b;
	}

	@Override
	public void mouseClicked(MouseEvent e)
	{
		if (!click)
		{
			init[0] = x;
			init[1] = y;
			click = true;
		}
		else
		{
			fin[0] = x;
			fin[1] = y;
			click = false;

			boolean move = board.verifyMove(init, fin);
			init[0] = -1;
			init[1] = -1;
			fin[0] = -1;
			fin[1] = -1;

			if (move)
				board.updateBoard();
		}
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
