package ui;

import java.awt.Container;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.math.BigInteger;

import javax.swing.GroupLayout;
import javax.swing.GroupLayout.Alignment;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.JTextField;
import javax.swing.SwingUtilities;

import model.JottoModel;

/**
 * The JottoGUI class keeps a JottoModel as an instance variable, interacting
 * with the model via the model's guess() and setPuzzleNumber() methods.
 * 
 * newPuzzleButton changes the puzzle number when clicked, changing it to equal
 * the text of newPuzzleNumber if it's valid.
 * 
 * The JLabel puzzleNumber displays the current puzzle number.
 * 
 * The JTextField guess is used to enter guesses, and the guesses are added to
 * guessTable when the user presses ENTER. The server's response is added when
 * it is received.
 * 
 * The JTable guessTable is located within a JScrollPane for better viewing of
 * guesses.
 */
public class JottoGUI extends JFrame {

    /**
     * newPuzzleButton changes the puzzle number when clicked, changing it to equal the text of
     * newPuzzleNumber if it's valid.
     */
	private JButton newPuzzleButton;
	private JTextField newPuzzleNumber;
	
	/**
	 * Displays the current puzzle number.
	 */
	private JLabel puzzleNumber;
	
    /**
     * Used to enter guesses. The guesses are added to guessTable when the user
     * presses ENTER.
     */
	private JTextField guess;
	
    /**
     * Stores guesses and results. The server's response to a guess or a win
     * message is added when it is received.
     */
	private JTable guessTable;
	
	/**
	 * The model for the Jotto game.
	 */
	private JottoModel jottoModel;

	/**
	 * Constructs a new JottoGUI instance.
	 */
	public JottoGUI() {
	    super("Jotto Game");
	    jottoModel = new JottoModel();
	    setDefaultCloseOperation(EXIT_ON_CLOSE);
	    Container cp = getContentPane();
	    GroupLayout layout=new GroupLayout(cp);
        cp.setLayout(layout);
        layout.setAutoCreateGaps(true);
        layout.setAutoCreateContainerGaps(true);
	    
		newPuzzleButton = new JButton();
		newPuzzleButton.setName("newPuzzleButton");
		newPuzzleButton.setText("New Puzzle");
		
		newPuzzleNumber = new JTextField();
		newPuzzleNumber.setName("newPuzzleNumber");
		
		puzzleNumber = new JLabel();
		puzzleNumber.setName("puzzleNumber");
		setPuzzleNumber(jottoModel.getPuzzleNumber());
		
		JLabel guessLabel = new JLabel();
		guessLabel.setText("Type a guess here:");
		
		guess = new JTextField();
		guess.setName("guess");
		
		guessTable = new JTable(jottoModel.getTableModel());
		guessTable.setName("guessTable");
		JScrollPane scrollPane = new JScrollPane(guessTable);
		
		newPuzzleButton.addActionListener(new ActionListener() {
		    public void actionPerformed(ActionEvent e){
		        setPuzzleNumber(jottoModel.setPuzzleNumber(newPuzzleNumber.getText()));
		    }
		});
		
		guess.addActionListener(new ActionListener() {
		    public void actionPerformed(ActionEvent e){
		        jottoModel.guess(guess.getText());
		        guess.setText("");
		    }
		});
		
		layout.setHorizontalGroup(layout.createParallelGroup()
		        .addGroup(layout.createSequentialGroup()
		                .addComponent(puzzleNumber)
		                .addComponent(newPuzzleButton)
		                .addComponent(newPuzzleNumber))
		        .addGroup(layout.createSequentialGroup()
		                .addComponent(guessLabel)
		                .addComponent(guess))
		        .addComponent(scrollPane)
		);
		layout.setVerticalGroup(layout.createSequentialGroup()
		        .addGroup(layout.createParallelGroup(Alignment.CENTER)
		                .addComponent(puzzleNumber)
		                .addComponent(newPuzzleButton)
		                .addComponent(newPuzzleNumber))
		        .addGroup(layout.createParallelGroup(Alignment.CENTER)
		                .addComponent(guessLabel)
		                .addComponent(guess))
		        .addComponent(scrollPane)
		);
		
		pack();
	}
	
    // I got a caesar comment here saying that BigInteger is overkill, which is
    // kind of true, but because the spec only mentions "integers" and not
    // "ints", I have to leave this as a BigInteger to match the spec.
	private void setPuzzleNumber(BigInteger b){
	    puzzleNumber.setText("Puzzle #"+b);
	}
	
	public static void main(final String[] args) {
		SwingUtilities.invokeLater(new Runnable() {
			public void run() {
				JottoGUI main = new JottoGUI();

				main.setVisible(true);
			}
		});
	}
}
