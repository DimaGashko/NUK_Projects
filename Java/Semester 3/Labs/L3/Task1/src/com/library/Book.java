package com.library;

import java.util.UUID;

public class Book {
    private UUID id = UUID.randomUUID();
    private String name = "No name";
    private String author = "No author";
    private String publisher = "No publisher";
    private int year = 0;
    private int pages = 0;
    private double price = 0;

    public Book() {

    }

    public Book(String name, String author, String publisher, int year, int pages, double price) {
        setName(name);
        setAuthor(author);
        setPublisher(publisher);
        setYear(year);
        setPages(pages);
        setPrice(price);
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getAuthor() {
        return author;
    }

    public void setAuthor(String author) {
        this.author = author;
    }

    public String getPublisher() {
        return publisher;
    }

    public void setPublisher(String publisher) {
        this.publisher = publisher;
    }

    public int getPages() {
        return pages;
    }

    public void setPages(int pages) {
        this.pages = pages;
    }

    public double getPrice() {
        return price;
    }

    public void setPrice(double price) {
        this.price = price;
    }

    public int getYear() {
        return year;
    }

    public void setYear(int year) {
        this.year = year;
    }

    public String toString() {
        return getAuthor() + ", " +
                getName() + ", " +
                getPublisher() + ", " +
                getYear() + ", " +
                getPages() + " (price: $" +
                getPrice() + ")";
    }
}
