/*
 * Author: Josue Galeas
 * Last Edit: 2018.08.12
 */

import java.awt.Color;
import java.awt.Dimension;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.GridBagLayout;

import javax.swing.BorderFactory;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.Timer;

@SuppressWarnings("serial")
public class MessageBox extends JPanel
{
	private JLabel message;
	private boolean waiting = false;

	private Color borderColor = Color.DARK_GRAY;
	private Color boxColor = Color.WHITE;

	public MessageBox()
	{
		setLayout(new GridBagLayout());
		setPreferredSize(new Dimension(540, 30));
		setBackground(boxColor);
		setBorder(BorderFactory.createLineBorder(borderColor, 1));

		message = new JLabel("White's Turn");
		add(message);
	}

	public void setMessage(String l) {message.setText(l);}

	public String getMessage() {return message.getText();}

	public boolean getWaiting() {return waiting;}

	public void customMessage(String custom, int sec)
	{
		waiting = true;
		String backup = message.getText();
		message.setText(custom);

		var restoreBackup = new ActionListener()
		{
			public void actionPerformed(ActionEvent e)
			{
				message.setText(backup);
				waiting = false;
			}
		};

		var timer = new Timer(sec * 1000, restoreBackup);
		timer.setRepeats(false);
		timer.start();
	}
}
