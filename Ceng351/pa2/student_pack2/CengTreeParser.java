import java.io.*;
import java.util.ArrayList;
import java.util.Scanner;

public class CengTreeParser
{
    public static ArrayList<CengBook> parseBooksFromFile(String filename)
    {
        ArrayList<CengBook> bookList = new ArrayList<CengBook>();

        Scanner s = null;
        try {
            s = new Scanner(new File(filename));
        } catch (FileNotFoundException e1) {

            e1.printStackTrace();
        }

        String my_input = null;

        while(s.hasNextLine()){

            my_input = s.nextLine();
            String[] array = my_input.split("[|]");
            Integer bookID = Integer.parseInt(array[0]);
            String bookTitle = array[1];
            String author = array[2];
            String genre = array[3];

            bookList.add(new CengBook(bookID, bookTitle, author, genre));
        }



        // You need to parse the input file in order to use GUI tables.
        // TODO: Parse the input file, and convert them into CengBooks

        return bookList;
    }

    public static void startParsingCommandLine() throws IOException
    {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        boolean control = true;
        while(control) {
            String inputLine = reader.readLine();
            if (inputLine == null) {
                break;
            }

            String[] array = inputLine.split("[|]");
            if (array.length == 0) { // empty input
                continue;
            }
            String instruction = array[0];

            switch (instruction) {
                case "quit":
                    control = false; // Exit the loop and the function
                    break;

                case "add":

                    if (array.length != 5) {  // wrong input format
                        break;
                    }

                    Integer bookID = Integer.parseInt(array[1]);
                    String bookTitle = array[2];
                    String author = array[3];
                    String genre = array[4];
                    CengBook newBook = new CengBook(bookID, bookTitle, author, genre);
                    CengBookRunner.addBook(newBook);

                    break;

                case "search":

                    if (array.length != 2) {
                        break;
                    }

                    Integer book_ID = Integer.parseInt(array[1]);
                    CengBookRunner.searchBook(book_ID);

                    break;

                case "print":
                    CengBookRunner.printTree();
                    break;
            }
            // TODO: Start listening and parsing command line -System.in-.
            // There are 4 commands:
            // 1) quit : End the app, gracefully. Print nothing, call nothing, just break off your command line loop.
            // 2) add : Parse and create the book, and call CengBookRunner.addBook(newlyCreatedBook).
            // 3) search : Parse the bookID, and call CengBookRunner.searchBook(bookID).
            // 4) print : Print the whole tree, call CengBookRunner.printTree().

            // Commands (quit, add, search, print) are case-insensitive.
        }
    }
}
