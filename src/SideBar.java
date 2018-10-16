/*
 * Author: Josue Galeas
 * Last Edit: 2018.10.16
 */

import java.awt.Dimension;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.filechooser.FileNameExtensionFilter;
import javax.swing.JButton;
import javax.swing.JFileChooser;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;

@SuppressWarnings("serial")
public class SideBar extends JPanel implements ActionListener
{
	public ChessBoard chessBoard;
	private JButton[] buttons;
	private JTextArea textBox;
	private int progress = 1;

	public SideBar()
	{
		setLayout(new GridLayout(2, 1));
		setPreferredSize(new Dimension(120, 570));

		var foo = new JPanel();
		foo.setLayout(new GridLayout(5, 1));

		buttons = new JButton[5];
		buttons[0] = new JButton("New Game");
		buttons[1] = new JButton("Save Game");
		buttons[1].setEnabled(false);
		buttons[2] = new JButton("Load Game");
		buttons[3] = new JButton("Undo");
		buttons[4] = new JButton("Settings");

		for (JButton b : buttons)
		{
			b.addActionListener(this);
			foo.add(b);
		}

		// TODO: Undo and Settings temporarily disabled
		buttons[3].setEnabled(false);
		buttons[4].setEnabled(false);

		textBox = new JTextArea();
		textBox.setEditable(false);

		add(foo);
		add(new JScrollPane(textBox));
	}

	public void updateTextBox(String an, char col)
	{
		String box = an;
		if (col == 'B')
			progress++;

		if (col == 'W')
			box = textBox.getText() + progress + ". " + an + " ";
		else if (col == 'B')
			box = textBox.getText() + an + "\n";
		else
			box = "ERROR: Side bar could not be updated.";

		buttons[1].setEnabled(true);
		textBox.setText(box);
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
				chessBoard.messageBox.setTempMessage("Game is not saved!");
				// TODO: Need to find out how to ignore unsaved games
			}
			else
			{
				var fileChooser = new JFileChooser();
				var filter = new FileNameExtensionFilter("PGN Files", "pgn");
				fileChooser.setAcceptAllFileFilterUsed(false);
				fileChooser.setFileFilter(filter);

				try
				{
					int choice = fileChooser.showOpenDialog(null);

					if (choice == JFileChooser.APPROVE_OPTION)
					{
						chessBoard.board.loadGame(fileChooser.getSelectedFile());
						// TODO: Should check if read was successful
						textBox.setText("");
						// TODO: How do we determine progress?
						buttons[1].setEnabled(false);
					}
					else if (choice == JFileChooser.ERROR_OPTION)
						chessBoard.messageBox.setTempMessage("Error loading PGN file!");
				}
				catch (Exception error)
				{
					chessBoard.messageBox.setTempMessage("Error loading PGN file!");
				}
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
			chessBoard.messageBox.setTempMessage("What button did you even press?");
	}
}
