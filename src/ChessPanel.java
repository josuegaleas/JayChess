/*
 * Author: Josue Galeas
 * Last Edit: September 12, 2017
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

	private static Board board;
	private static boolean click = false;
	private static char turn = 'W';
	private static int[] init = new int[2];
	private static int[] fin = new int[2];

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
			char color = board.getColorOf(x, y);

			if (color == 'E')
			{
				System.out.println("There is nothing there!");
				return;
			}
			else if (color != turn)
			{
				System.out.println("Not your piece!");
				return;
			}

			init[0] = x;
			init[1] = y;
			click = true;
		}
		else
		{
			fin[0] = x;
			fin[1] = y;
			click = false;

			boolean move = board.verifyMove(init[0], init[1], fin[0], fin[1]);
			init[0] = init[1] = -1;
			fin[0] = fin[1] = -1;

			if (move)
			{
				board.updateBoard();
				turn = turn == 'W' ? 'B':'W';
			}
			else
			{
				System.out.println("Not a valid move!");
			}
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
