package org.lab5;

import org.lab5.entity.Admin;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;


public class Main {

    private static final Logger logger = LoggerFactory.getLogger(Main.class);

    public static void main(String[] args) throws IOException {
        System.out.println(" please enter 1- 4 input 9 will exit ");
        System.out.println(" 1 admin login  ");
        System.out.println(" 2 query book ");
        System.out.println(" 3 borrow book");
        System.out.println("4 return book");
        // Enter data using BufferReader
        BufferedReader reader = new BufferedReader(
                new InputStreamReader(System.in));

        String command;
        // Reading data using readLine
        command = reader.readLine();
        int com = Integer.parseInt(command);
        normalUser user = new normalUser();
        while (com != 9) {
            if (com == 1) {
                admin ad = new admin();
                System.out.println("please enter admin id");
                String Adminid = reader.readLine();
                Admin corradmin = ad.findadmin(Integer.parseInt(Adminid));
                if (Integer.parseInt(Adminid) == corradmin.getAid())
                    System.out.println("please enter admin password");
                String Adminpassword = reader.readLine();
                if (corradmin.getPassword().equals(Adminpassword)) {
                    System.out.println("login successful!");
                    ad.adminProc();
                } else {
                    System.out.println("ID/password error!");
                }
            } else if (com == 2) {
                user.queryBook();
            } else if (com == 3) {
                user.borrowBook();
            } else if (com == 4) {
                user.returnBook();
            } else {
                logger.error("wrong input");
            }
            command = reader.readLine();
            com = Integer.parseInt(command);
        }
    }


}