/*
 * Author: Josue Galeas
 * Last Edit: 2017.09.22
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
	private int x, y;
	private JLabel label;
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

	public void setLabel(String l) {label.setText(l);}
	public static void setBoard(Board b) {board = b;}

	@Override
	public void mouseClicked(MouseEvent e)
	{
		board.processClick(x, y);
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
