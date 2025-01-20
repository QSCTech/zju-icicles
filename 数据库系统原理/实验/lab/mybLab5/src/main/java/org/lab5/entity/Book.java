package org.lab5.entity;

public class Book {

    private String ISBN;
    private String Category;
    private String Title;
    private String Publisher;
    private String Author;
    private Integer Year;
    private Double Price;
    private Integer Total;
    private Integer Inventory;

    public Book() {
    }

    public Book(String isbn, String category, String title, String publisher, Integer year, String author, Double price) {
        this.Author = author;
        this.Category = category;
        this.ISBN = isbn;
        this.Price = price;
        this.Publisher = publisher;
        this.Year = year;
        this.Title = title;
    }

    @Override
    public String toString() {
        return "[ISBN : " + ISBN + " Category :" + Category + " Title:" +
                Title + " Publisher: " + Publisher + " Year : " + Year + "  Author: " + Author
                + " Price : " + Price + " Total : " + Total + " Inventory: " + Inventory;
    }


    public String getAuthor() {
        return Author;
    }

    public void setAuthor(String author) {
        Author = author;
    }

    public Book(String isbn, String category, String title, String publisher, Integer year, String author, Double price, Integer total, Integer inventory) {
        this.Author = author;
        this.Category = category;
        this.Inventory = inventory;
        this.ISBN = isbn;
        this.Price = price;
        this.Publisher = publisher;
        this.Year = year;
        this.Total = total;
        this.Title = title;
    }


    public Integer getYear() {
        return Year;
    }

    public void setYear(Integer year) {
        this.Year = year;
    }

    public String getISBN() {
        return ISBN;
    }

    public void setISBN(String ISBN) {
        this.ISBN = ISBN;
    }

    public String getCategory() {
        return Category;
    }

    public void setCategory(String category) {
        Category = category;
    }

    public String getTitle() {
        return Title;
    }

    public void setTitle(String title) {
        Title = title;
    }

    public String getPublisher() {
        return Publisher;
    }

    public void setPublisher(String publisher) {
        Publisher = publisher;
    }


    public Double getPrice() {
        return Price;
    }

    public void setPrice(Double price) {
        Price = price;
    }

    public Integer getTotal() {
        return Total;
    }

    public void setTotal(Integer total) {
        Total = total;
    }

    public Integer getInventory() {
        return Inventory;
    }

    public void setInventory(Integer inventory) {
        Inventory = inventory;
    }
}
