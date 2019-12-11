package com.library;

import java.util.Arrays;

public class Library {
    private Book[] books;

    public  Library() {

    }

    public Book[] getBooks() {
        return Arrays.copyOf(books, books.length);
    }

    /**
     * Добавляет переданные книги
     * @param books Книги, что нужно добавить
     */
    public void addBooks(Book[] books) {
        this.books = books;

        Book[] newBooks = Arrays.copyOf(this.books, this.books.length + books.length);
        System.arraycopy(books, 0, newBooks, this.books.length, books.length);
    }

    /**
     * Взвращает массив книг переданного автора
     * @param _author Автор
     * @return массив книг переданного автора
     */
    public Book[] getBooksByAuthor(String _author) {
        String author = _author.toLowerCase();

        return Arrays.stream(books)
                .filter(book -> book.getAuthor().toLowerCase().equals(author))
                .toArray(Book[]::new);
    }

    /**
     * Взвращает массив книг переданного издательства
     * @param _publisher Издательство
     * @return массив книг переданного издательства
     */
    public Book[] getBooksByPublisher(String _publisher) {
        String publisher = _publisher.toLowerCase();

        return Arrays.stream(books)
                .filter(book -> book.getPublisher().toLowerCase().equals(publisher))
                .toArray(Book[]::new);
    }

    /**
     * Взвращает массив книг изданных после переданного года
     * @param year Год
     * @return массив книг изданных после переданного года
     */
    public Book[] getBooksAfterYear(int year) {
        return Arrays.stream(books)
                .filter(book -> book.getYear() > year)
                .toArray(Book[]::new);
    }

}
