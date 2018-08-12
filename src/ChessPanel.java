/*
 * Author: Josue Galeas
 * Last Edit: 2018.08.12
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
	private static Board board;
	private JLabel label;
	private int x, y;

	public ChessPanel(int x, int y)
	{
		this.x = x;
		this.y = y;

		setLayout(new GridBagLayout());
		label = new JLabel("E");
		label.setFont(new Font("Sans Serif", Font.PLAIN, 32));
		add(label);
		addMouseListener(this);
	}

	public static void setBoard(Board b) {board = b;}

	public void setLabel(String l) {label.setText(l);}

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
