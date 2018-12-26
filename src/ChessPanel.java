/*
 * Author: Josue Galeas
 * Last Edit: 2018.12.25
 */

import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.Font;
import java.awt.GridBagLayout;
import javax.swing.JLabel;
import javax.swing.JPanel;

@SuppressWarnings("serial")
public class ChessPanel extends JPanel
{
	private JLabel label;
	private int x, y;

	public ChessPanel(int x, int y)
	{
		this.x = x;
		this.y = y;

		setLayout(new GridBagLayout());
		setBackground();

		var font = new Font("Sans Serif", Font.PLAIN, 32);
		label = new JLabel("E");
		label.setFont(font);
		add(label);

		var clickEvent = new MouseAdapter()
		{
			public void mouseClicked(MouseEvent e)
			{
				Game.board.processClick(x, y);
			}
		};
		addMouseListener(clickEvent);
	}

	public void setLabel(String l) {label.setText(l);}

	public void setBackground()
	{
		int tile = (x * 8) + y + (x % 2);

		if (tile % 2 == 0)
			setBackground(Settings.lightTile);
		else
			setBackground(Settings.darkTile);
	}
}
