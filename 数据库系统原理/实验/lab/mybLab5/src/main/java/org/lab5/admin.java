package org.lab5;

import org.apache.ibatis.io.Resources;
import org.apache.ibatis.session.SqlSession;
import org.apache.ibatis.session.SqlSessionFactory;
import org.apache.ibatis.session.SqlSessionFactoryBuilder;
import org.lab5.entity.Book;
import org.lab5.entity.Card;
import org.lab5.entity.Admin;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import java.io.*;
import java.util.List;

public class admin {
    SqlSession session;

    admin() throws IOException {
        //1.读取mybatis的核心配置文件(mybatis-config.xml)
        InputStream in = Resources.getResourceAsStream("mybatis-config.xml");

        //2.通过配置信息获取一个SqlSessionFactory工厂对象
        SqlSessionFactory fac = new SqlSessionFactoryBuilder().build(in);
        //3.通过工厂获取一个SqlSession对象
        session = fac.openSession();
    }

    private static final Logger logger = LoggerFactory.getLogger(admin.class);

    public void adminProc() throws IOException {
        System.out.println(" please enter 1- 2 . input 9 will exit ");
        System.out.println(" 1 single load book ");
        System.out.println(" 2 multiple load book ");
        System.out.println(" 3 add Libcard ");
        System.out.println(" 4 remove Libcard ");
        // Enter data using BufferReader
        BufferedReader reader = new BufferedReader(
                new InputStreamReader(System.in));
        // Reading data using readLine
        String command;
        command = reader.readLine();
        int com = Integer.parseInt(command);
        BufferedReader databf;
        if (com == 3) {
            System.out.println(" input new card info ");
            String str = null;
            databf = new BufferedReader(new InputStreamReader(System.in));
            while ((str = databf.readLine()) != null) {
                String[] temp = str.split(",");
                Integer cid = Integer.parseInt(temp[0].trim());
                String name = temp[1].trim();
                String unit = temp[2].trim();
                String category = temp[3].trim();
                Card card = new Card(cid, name, unit, category);
                session.insert("cardMapper.insertOne", card);
                session.commit();
                logger.info("insert card successfully!");
            }
        }
        if (com == 4) {
            System.out.println(" input  cid ");
            String str = null;
            databf = new BufferedReader(new InputStreamReader(System.in));
            while ((str = databf.readLine()) != null) {
                Integer cid = Integer.parseInt(str);
                session.insert("cardMapper.deleteOne", cid);
                session.commit();
                logger.info("delete card successfully!");
            }
        }
        if (com == 4 ||com ==3 )
            return;
        //load books
        while (com != 9) {
            if (com == 1) {
                databf = new BufferedReader(new InputStreamReader(System.in));
            } else if (com == 2) {
                File file = new File("databooks/books.dat");
                databf = new BufferedReader(new FileReader(file));
            } else {
                logger.error("wrong input!");
                command = reader.readLine();
                com = Integer.parseInt(command);
                continue;
            }
            String str = null;
            while ((str = databf.readLine()) != null) {
                String[] temp = str.split(",");
                //（书号，类别，书名，出版社，年份，作者，价格，数量）
                String ISBN = temp[0].trim();
                String Category = temp[1].trim();
                String Title = temp[2].trim();
                String Publisher = temp[3].trim();
                Integer Year = Integer.parseInt(temp[4].trim());
                String Author = temp[5].trim();
                Double Price = Double.parseDouble(temp[6].trim());
                Integer Total = Integer.parseInt(temp[7].trim());
                Integer Inventory = Total;
                Book book = new Book(ISBN, Category, Title, Publisher, Year, Author, Price, Total, Inventory);
                session.insert("bookMapper.insertBook", book);
                session.commit();
                System.out.println("insert one line successfully!");
            }
        }
    }

    public Admin findadmin(int aid) throws IOException {
        //4.通过namespace+id找到要执行的sql语句并执行sql语句
        Admin admin = session.selectOne("EmpMapper.selectemp", aid);
        return admin;
    }

    public void findAll() throws IOException {
        List<Admin> list = session.selectList("EmpMapper.findAll");
    }
}
