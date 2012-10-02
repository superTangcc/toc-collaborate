package model;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.math.BigInteger;
import java.net.MalformedURLException;
import java.net.URL;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.Random;
import java.util.concurrent.ExecutionException;

import javax.swing.SwingWorker;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.TableModel;

/**
 * The JottoModel class is responsible for keeping track of the puzzle number and the table of guesses and results.
 * 
 * currPuzzleNumber holds the current puzzle number, pastGuessTable is the table of guesses and results.
 * activeThreads is a list of active SwingWorkers. A new SwingWorker executes for each new call to guess().
 * 
 * The main points of entry into the class are the guess() and setPuzzleNumber() methods.
 */
public class JottoModel {
    
	/**
     *Randomly generated puzzle numbers will be between 1 and 2^p, where p is MAX_PUZZLE_NUM_PARAMETER.
     */
    private static final int MAX_PUZZLE_NUM_PARAMETER=14;
    
    /**
     * Holds the current puzzle number.
     */
    private BigInteger currPuzzleNumber;
    
    /**
     * Table of guesses and results.
     */
    private DefaultTableModel pastGuessTable;
    
    /**
     * List of the active SwingWorkers processing server requests and responses.
     */
    private LinkedList<SwingWorker<Object[],Void>> activeThreads;
    
    /**
     * Creates a new model. currPuzzleNumber is set to a random integer between 1 and 2^14 inclusive.
     */
    public JottoModel(){
        currPuzzleNumber=BigInteger.ONE.add(new BigInteger(MAX_PUZZLE_NUM_PARAMETER,new Random()));
        pastGuessTable=new DefaultTableModel(new Object[] {"word","# in word","# correct"},0);
        activeThreads = new LinkedList<SwingWorker<Object[],Void>>();
    }

    /**
     * Sends a guess to the server and returns the server's output. Returns null
     * and prints a stack trace if a MalformedURLException or an IOException is
     * thrown.
     * 
     * @param guess
     *            the word to guess
     * @return the response from the server. Returns null if an exception is
     *         thrown.
     */
	public String makeGuess(String guess) {
		try {
		    BufferedReader br = new BufferedReader(new InputStreamReader((new URL("http://6.005.scripts.mit.edu/jotto.py?puzzle="+currPuzzleNumber+"&guess="+guess)).openStream()));
		    String output = br.readLine();
		    br.close();
            return output;
        } catch (MalformedURLException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
		return null;
	}
	
    /**
     * Adds a row to the table and creates a new SwingWorker to send the guess
     * to the server and add its response to the table. The guessed word is
     * added to the table immediately, and the response is added later by the
     * SwingWorker.
     * 
     * @param guess
     *            the guessed word
     */
	public void guess(final String guess){
	    final int myIndex = pastGuessTable.getRowCount();
	    pastGuessTable.addRow(new Object[] {guess,null,null});
	    
	    class QueryThread extends SwingWorker<Object[],Void>{
            public Object[] doInBackground() {
                String response = makeGuess(guess);
                if (response==null){
                    return null;
                }
                System.out.println(response);
                String[] tokens = response.split(" ");
                if (tokens[0].equals("guess")){
                    int numInPlace, numCorrect;
                    try{
                        numInPlace = Integer.parseInt(tokens[1]);
                        numCorrect = Integer.parseInt(tokens[2]);
                    } catch (NumberFormatException e){
                        return null;
                    }
                    if (numInPlace>=0 && numInPlace<=5 && numCorrect>=0 && numCorrect<=5){
                        return new Object[] {numInPlace,numCorrect};
                    }
                } else if (tokens[0].equals("error")){
                    // I got a comment on caesar saying that I could have a
                    // String array mapping tokens[1] values to return values,
                    // but because there are only three possibilities, I think
                    // it's probably not worth it to convert tokens[1] to an
                    // index or a hash; it's probably faster the way
                    // I have it.
                    if (tokens[1].equals("2")){
                        return new Object[] {"Invalid guess.",null};
                    } else if (tokens[1].equals("1")){
                        return new Object[] {"Non-number puzzle ID.",null};
                    } else if (tokens[1].equals("0")){
                        return new Object[] {"Ill-formatted request.",null};
                    }
                }
                return null;
            }
            
            public void done(){
                if (!isCancelled()){
                    Object[] response = null;
                    try {
                        response = get();
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    } catch (ExecutionException e) {
                        e.printStackTrace();
                    }
                    if (response!=null&&(!response[0].equals(5)||!response[1].equals(5))){
                        pastGuessTable.setValueAt(response[0], myIndex, 1);
                        pastGuessTable.setValueAt(response[1], myIndex, 2);
                    } else if (response!=null){
                        pastGuessTable.setValueAt("You win! The secret word was "+guess, myIndex,1);
                        System.out.println("You win! The secret word was "+guess);
                    }
                    activeThreads.remove(this);
                }
            }
	        
	    }
	    QueryThread q = new QueryThread();
	    activeThreads.addFirst(q);
	    q.execute();
	}
	
	/**
	 * Sets the current puzzle number to the value given by text if it's valid. Otherwise picks a new random puzzle (from 1 to 2^14)
	 * @param text
	 *         the new puzzle number
	 * @return
	 *         the puzzle number that was set as a result of this method
	 */
	public BigInteger setPuzzleNumber(String text){
        BigInteger puzNum;
        try{
            puzNum = new BigInteger(text);
        } catch (NumberFormatException ex){
            puzNum = BigInteger.ZERO;
        }
        if (puzNum.compareTo(BigInteger.ONE)<0){
            puzNum = BigInteger.ONE.add(new BigInteger(14,new Random()));
        }
        currPuzzleNumber=puzNum;
        
        //clean up old puzzle data
        Iterator<SwingWorker<Object[],Void>> iter = activeThreads.iterator();
        while (iter.hasNext()){
            iter.next().cancel(true);
            iter.remove();
        }
        pastGuessTable.setRowCount(0);
        return currPuzzleNumber;
	}
	
	public BigInteger getPuzzleNumber(){
	    return currPuzzleNumber;
	}
	
	public TableModel getTableModel(){
	    return pastGuessTable;
	}
}
