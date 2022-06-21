package org.lab5.entity;

public class Card {
    private Integer cid;
    private String name;
    private String unit;
    private String category;

    public Card(Integer cid, String name, String unit, String category) {
        this.category = category;
        this.cid = cid;
        this.name = name;
        this.unit = unit;
    }

    public Integer getCid() {
        return cid;
    }

    public void setCid(Integer cid) {
        this.cid = cid;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getUnit() {
        return unit;
    }

    public void setUnit(String unit) {
        this.unit = unit;
    }

    public String getCategory() {
        return category;
    }

    public void setCategory(String category) {
        this.category = category;
    }
}
