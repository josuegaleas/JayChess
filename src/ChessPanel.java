/*
 * Author: Josue Galeas
 * Last Edit: September 16, 2017
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

	private static boolean click;
	private static char turn;
	private static int[] init = new int[2];
	private static int[] fin = new int[2];
	private static Board board;

	public ChessPanel(int x, int y)
	{
		this.x = x;
		this.y = y;

		setLayout(new GridBagLayout());
		label = new JLabel("E");
		label.setFont(new Font("Serif", Font.PLAIN, 32));
		add(label);
		addMouseListener(this);
	}

	public void setLabel(String l)
	{
		label.setText(l);
	}

	public static void setBoard(Board b)
	{
		click = false;
		turn = 'W';
		init[0] = init[1] = -1;
		fin[0] = fin[1] = -1;
		board = b;
	}

	public static char getTurn()
	{
		return turn;
	}

	@Override
	public void mouseClicked(MouseEvent e)
	{
		if (!click)
		{
			char color = board.getColorOf(x, y);

			if (color == 'E')
				return;
			if (color != turn)
			{
				System.out.println("Not your piece!");
				return;
			}

			init[0] = x;
			init[1] = y;
			click = true;
			setBackground(Color.GREEN);
		}
		else
		{
			fin[0] = x;
			fin[1] = y;
			click = false;

			boolean move = board.verifyMove(init[0], init[1], fin[0], fin[1]);
			board.updateTileOf(init[0], init[1]);

			init[0] = init[1] = -1;
			fin[0] = fin[1] = -1;

			if (move)
			{
				board.updateBoard();
				board.updateSideBar();
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
