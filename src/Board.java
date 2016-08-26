import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.GridLayout;
import java.awt.GridBagLayout;
import javax.swing.BorderFactory;
import javax.swing.JLabel;
import javax.swing.JPanel;

@SuppressWarnings("serial")
public class Board extends JPanel
{
	public Board()
	{
		setLayout(new BorderLayout());
		setBorder(BorderFactory.createLineBorder(Color.BLACK));

		add(new ChessBoard());
		add(new FilesBar(), BorderLayout.NORTH);
		add(new RanksBar(), BorderLayout.EAST);
		add(new FilesBar(), BorderLayout.SOUTH);
		add(new RanksBar(), BorderLayout.WEST);
	}

	private class RanksBar extends JPanel
	{
		public RanksBar()
		{
			setLayout(new GridBagLayout());

			JPanel center = new JPanel();
			center.setLayout(new GridLayout(8, 1));
			center.setPreferredSize(new Dimension(20, 500));
			center.setBackground(Color.WHITE);

			for (int c = 8; c >= 1; c--)
			{
				center.add(new JLabel(Integer.toString(c), 0));
			}

			add(center);
		}
	}

	private class FilesBar extends JPanel
	{
		public FilesBar()
		{
			setLayout(new GridBagLayout());
			setBackground(Color.WHITE);

			JPanel center = new JPanel();
			center.setLayout(new GridLayout(1, 8));
			center.setPreferredSize(new Dimension(500, 20));
			center.setBackground(Color.WHITE);

			for (char c = 'a'; c <= 'h'; c++)
			{
				center.add(new JLabel(Character.toString(c), 0));
			}

			add(center);
		}
	}
}
