/*
 * Author: Josue Galeas
 * Last Edit: September 22, 2017
 */

import java.awt.Dimension;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;

@SuppressWarnings("serial")
public class SideBar extends JPanel
{
	private ChessBoard chessBoard;
	private JTextArea textBox;
	private Integer progress = 1;

	public SideBar()
	{
		setLayout(new GridLayout(2, 1));
		setPreferredSize(new Dimension(125, 540));

		textBox = new JTextArea();
		textBox.setEditable(false);

		add(new ButtonPanel());
		add(new JScrollPane(textBox));
	}

	public void setChessBoard(ChessBoard cb)
	{
		chessBoard = cb;
	}

	public void updateTextBox(String m, boolean t)
	{
		String b;

		if (t)
			b = textBox.getText() + progress + ". " + m + " ";
		else
		{
			b = textBox.getText() + m + "\n";
			progress++;
		}

		textBox.setText(b);
	}

	private class ButtonPanel extends JPanel implements ActionListener
	{
		private JButton[] buttons = new JButton[5];

		public ButtonPanel()
		{
			setLayout(new GridLayout(5, 1));

			buttons[0] = new JButton("New Game");
			buttons[1] = new JButton("Save Game");
			buttons[2] = new JButton("Load Game");
			buttons[3] = new JButton("Undo");
			buttons[4] = new JButton("Settings");

			for (int c = 0; c < 5; c++)
			{
				buttons[c].addActionListener(this);
				add(buttons[c]);
			}

			// TODO: Temporarily Disabled
			buttons[1].setEnabled(false);
			buttons[2].setEnabled(false);
			buttons[3].setEnabled(false);
			buttons[4].setEnabled(false);
		}

		@Override
		public void actionPerformed(ActionEvent e)
		{
			Object source = e.getSource();

			if (source == buttons[0])
			{
				chessBoard.newGame();
				textBox.setText("");
				progress = 1;
			}
		}
	}
}
