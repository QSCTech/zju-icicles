package org.lab5.entity;

import java.util.Calendar;
import java.util.Date;

public class Record {
    private String ISBN;
    private Integer cid;
    private Date BorrowTime;
    private Date Due;
    private Integer AID;

    public Record(){

    }

    public Record(String ISBN, Integer cid, Integer aid) {
        this.ISBN = ISBN;
        this.cid = cid;
        this.BorrowTime = new Date();
        Calendar cal = Calendar.getInstance();
        cal.setTime(this.BorrowTime);
        cal.add(Calendar.DATE, 40);
        this.Due  = cal.getTime();
        this.AID = aid;
    }

    public String getISBN() {
        return ISBN;
    }

    public void setISBN(String ISBN) {
        this.ISBN = ISBN;
    }

    public Integer getCid() {
        return cid;
    }

    public void setCid(Integer cid) {
        this.cid = cid;
    }

    public Date getBorrowTime() {
        return BorrowTime;
    }

    public void setBorrowTime(Date borrowTime) {
        BorrowTime = borrowTime;
    }

    public Date getDue() {
        return Due;
    }

    public void setDue(Date due) {
        this.Due = due;
    }

    public Integer getAID() {
        return AID;
    }

    public void setAID(Integer AID) {
        this.AID = AID;
    }



}
