import java.awt.FlowLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.JFrame;

@SuppressWarnings("serial")
public class GUI extends JFrame implements ActionListener
{
	public GUI()
	{
		setTitle("PlebeianChess");
		setLayout(new FlowLayout());

		add(new Board());

		pack();
		setResizable(false);
		setVisible(true);
		setLocationRelativeTo(null);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

	}

	public static void main(String[] args)
	{
		new GUI();
	}

	@Override
	public void actionPerformed(ActionEvent e)
	{

	}
}
