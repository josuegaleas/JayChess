import java.awt.Color;
import java.awt.Dimension;
import java.awt.GridLayout;
import javax.swing.BorderFactory;
import javax.swing.JPanel;

@SuppressWarnings("serial")
public class ChessBoard extends JPanel
{
	private ChessPanel[][] panels = new ChessPanel[8][8];

	public ChessBoard()
	{
		setLayout(new GridLayout(8, 8));
		setPreferredSize(new Dimension(500, 500));
		setBorder(BorderFactory.createLineBorder(Color.BLACK));
		setBackground(Color.GRAY);

		for (int x = 0; x < 8; x++)
		{
			for (int y = 0; y < 8; y++)
			{
				panels[x][y] = new ChessPanel();
				add(panels[x][y]);
			}
		}
	}

	private class ChessPanel extends JPanel
	{
		// TODO: Exapnd this panel to contain pieces

		public ChessPanel()
		{
			setBorder(BorderFactory.createLineBorder(Color.BLACK));
		}
	}
}
