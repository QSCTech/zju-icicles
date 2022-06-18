package org.lab5.entity;

public class Admin {
    private Integer aid;
    private String password;
    private String Name;
    private String Contact;

    public Integer getAid() {
        return aid;
    }

    public void setAid(Integer aid) {
        this.aid = aid;
    }

    public String getPassword() {
        return password;
    }

    public void setPassword(String password) {
        this.password = password;
    }

    public String getName() {
        return Name;
    }

    public void setName(String name) {
        Name = name;
    }

    public String getContact() {
        return Contact;
    }

    public void setContact(String contact) {
        Contact = contact;
    }
    @Override
    public String toString(){
        return "ud" + aid + "name" + Name;
    }
}
