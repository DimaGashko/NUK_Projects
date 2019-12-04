package com.Lab3Corporation;

import com.helpers.Prompt;
import com.library.Book;
import com.library.Library;

public class Main {
    private Library library = new Library();

    public static void main(String[] args) {
        var main = new Main();
        main.run();
    }

    private void run() {
        //var books = getBooksFromConsole();
        var books = getTestBooks();
        library.addBooks(books);

        var prompt = new Prompt();

        printHr();

        String author = prompt.getLine("Enter the author: ");
        printBooks(library.getBooksByAuthor(author));

        String publisher = prompt.getLine("Enter the publisher: ");
        printBooks(library.getBooksByPublisher(publisher));

        int year = prompt.getInt("Enter the year: ");
        printBooks(library.getBooksAfterYear(year));
    }

    private Book[] getBooksFromConsole() {
        var prompt = new Prompt();

        var number = prompt.getInt("Enter the number of books: ");
        Book[] books = new Book[number];

        printHr();

        for (int i = 0; i < books.length; i++) {
            String name = prompt.getLine("Enter the name of the book: ");
            String author = prompt.getLine("Enter the author: ");
            String publisher = prompt.getLine("Enter the publisher: ");
            int year = prompt.getInt("Enter the year: ");
            int pages = prompt.getInt("Enter the number of pages: ");
            double price = prompt.getDouble("Enter the price: ");

            books[i] = new Book(name, author, publisher, year, pages, price);

            printHr();
        }

        return books;
    }

    private Book[] getTestBooks() {
        Book[] books = new Book[7];

        books[0] = new Book("JavaScript: The Definitive Guide", "David Flanagan", "O'Reilly", 2006, 999, 50);
        books[1] = new Book("Java Programming", "Donald Bales", "O'Reilly", 2001, 450, 60);
        books[2] = new Book("Thinking in Java", "Bruce Eckel", "Oracle", 2002, 328, 50);
        books[3] = new Book("JS.Next", "Aaron Frost", "O'Reilly", 2015, 250, 50);
        books[4] = new Book("You don't know JS", "Simpson K.", "O'Reilly", 2015, 88, 30);
        books[5] = new Book("Angular", "David Flanagan", "O'Reilly", 2016, 396, 30);
        books[6] = new Book("Java in a Nutshell", "David Flanagan", "O'Reilly", 2014, 396, 60);

        return books;
    }

    private void printBooks(Book[] books) {
        for (Book book : books) {
            System.out.println(book);
        }
    }

    private void printHr() {
        System.out.println("- - - - - - - - - - - - -");
    }

}
