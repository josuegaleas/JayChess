/*
 * Author: Josue Galeas
 * Last Edit: 2018.10.05
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
	public ChessBoard chessBoard;
	private JButton[] buttons;
	private JTextArea textBox;
	private int progress = 1;

	public SideBar()
	{
		setLayout(new GridLayout(2, 1));
		setPreferredSize(new Dimension(120, 570));

		textBox = new JTextArea();
		textBox.setEditable(false);

		add(new ButtonPanel());
		add(new JScrollPane(textBox));
	}

	public void updateTextBox(String an, char col)
	{
		var box = an;
		if (col == 'B')
			progress++;

		if (col == 'W')
			box = textBox.getText() + progress + ". " + an + " ";
		else if (col == 'B')
			box = textBox.getText() + an + "\n";
		else
			box = "ERROR";

		buttons[1].setEnabled(true);
		textBox.setText(box);
	}

	private class ButtonPanel extends JPanel implements ActionListener
	{

		public ButtonPanel()
		{
			buttons = new JButton[5];
			setLayout(new GridLayout(5, 1));

			buttons[0] = new JButton("New Game");
			buttons[1] = new JButton("Save Game");
			buttons[1].setEnabled(false);
			buttons[2] = new JButton("Load Game");
			buttons[3] = new JButton("Undo");
			buttons[4] = new JButton("Settings");

			for (JButton b : buttons)
			{
				b.addActionListener(this);
				add(b);
			}

			// TODO: Temporarily Disabled
			buttons[3].setEnabled(false);
			buttons[4].setEnabled(false);
		}

		@Override
		public void actionPerformed(ActionEvent e)
		{
			if (chessBoard.messageBox.getWaiting())
				return;

			var source = e.getSource();

			if (source == buttons[0])
			{
				// New Game
				chessBoard.board.newGame();
				textBox.setText("");
				progress = 1;
				buttons[1].setEnabled(false);
			}
			else if (source == buttons[1])
			{
				// Save Game
				System.out.println("\"Saving\" game!");
				// chessBoard.board.saveGame();
				buttons[1].setEnabled(false);
			}
			else if (source == buttons[2])
			{
				// Load Game
				if (buttons[1].isEnabled())
				{
					chessBoard.messageBox.setTempMessage("Game is not saved!", Settings.delay);
					// Need to find out how to ignore unsaved games
				}
				else
				{
					System.out.println("\"Loading\" game!");
					// chessBoard.board.loadGame();
					buttons[1].setEnabled(false);
				}
			}
			else if (source == buttons[3])
			{
				// Undo
			}
			else if (source == buttons[4])
			{
				// Settings
			}
			else
				chessBoard.messageBox.setTempMessage("What button did you even press?", Settings.delay);
		}
	}
}
