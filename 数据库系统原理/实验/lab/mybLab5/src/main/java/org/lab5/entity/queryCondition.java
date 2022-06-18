package org.lab5.entity;

import org.lab5.entity.Book;

public class queryCondition extends Book {
    private Double Price2;
    private Integer Year2;

    public queryCondition(String isbn, String category, String title, String publisher, Integer year, String author, Double price, Double price2, Integer year2) {
        super(isbn, category, title, publisher, year, author, price);
        this.Price2 = price2;
        this.Year2 = year2;
    }

    public Double getPrice2() {
        return Price2;
    }

    public void setPrice2(Double price2) {
        this.Price2 = price2;
    }

    public Integer getYear2() {
        return Year2;
    }

    public void setYear2(Integer year2) {
        this.Year2 = year2;
    }
}
