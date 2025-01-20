package org.lab5;

import org.apache.ibatis.io.Resources;
import org.apache.ibatis.session.SqlSession;
import org.apache.ibatis.session.SqlSessionFactory;
import org.apache.ibatis.session.SqlSessionFactoryBuilder;
import org.lab5.entity.Book;
import org.lab5.entity.Record;
import org.lab5.entity.queryCondition;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.text.SimpleDateFormat;
import java.util.Comparator;
import java.util.List;

public class normalUser {
    SqlSession session;

    normalUser() throws IOException {
        //1.读取mybatis的核心配置文件(mybatis-config.xml)
        InputStream in = Resources.getResourceAsStream("mybatis-config.xml");

        //2.通过配置信息获取一个SqlSessionFactory工厂对象
        SqlSessionFactory fac = new SqlSessionFactoryBuilder().build(in);
        //3.通过工厂获取一个SqlSession对象
        session = fac.openSession();
    }

    private static final Logger logger = LoggerFactory.getLogger(normalUser.class);

    public void borrowBook() throws IOException {
        logger.info("""
                 please enter 1 or 2 . input 9 will exit\s
                1 show books\s
                2 borrow book
                """
        );
        String str = null;
        BufferedReader databf = new BufferedReader(new InputStreamReader(System.in));
        // 借书的实现：
        // 如果有库存， 那 book update库存- 1， records  插入，  isbn 来自输入， cid来自输入，Borrowtime是现在的时间
        // due是40天， aid是输入。
        //如果没有库存， 那么找到records， 找到最快的归还时间。
        while ((str = databf.readLine()) != null) {
            int com = Integer.parseInt(str);
            // find Records cardnum ->   isbn -> book. info
            if (com == 1) {
                logger.info("please input card id:");
                Integer cid = Integer.parseInt(databf.readLine());
                logger.info("showing all books...");
                List<Record> recordlist = session.selectList("recordMapper.showRecords", cid);
                for (Record r : recordlist) {
                    Book book = session.selectOne("bookMapper.showBooks", r.getISBN());
                    System.out.println(book);
                }
            } else {
                // borrow book
                Integer cardnum = Integer.parseInt(databf.readLine());
                Integer aid = Integer.parseInt(databf.readLine());
                logger.info("please input isdn:");
                String isbn = databf.readLine();
                logger.info("searching books...");
                Book book = session.selectOne("bookMapper.showBooks", isbn);
                Record record = new Record(isbn, cardnum, aid);
                if (book.getInventory() > 0) {
                    session.update("bookMapper.borrowbook", isbn);
                    session.insert("recordMapper.insertOne", record);
                    session.commit();
                    logger.info("borrow book success!");
                } else {
                    logger.error("This book doesn't have inventory!");
                    List<Record> recordlist = session.selectList("recordMapper.findNearestDue", isbn);
                    SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd");
                    logger.info("The nearest due is : "+sdf.format(recordlist.get(0).getDue()));
                }
            }
        }
    }

    public void returnBook() throws IOException {
        logger.info("""
                 please enter 1 or 2 . input 9 will exit\s
                1 show books\s
                2 return book
                """
        );
        String str = null;
        BufferedReader databf = new BufferedReader(new InputStreamReader(System.in));
        // 还书的实现：
        while ((str = databf.readLine()) != null) {
            int com = Integer.parseInt(str);
            if (com == 1) {
                logger.info("please input card id:");
                Integer cid = Integer.parseInt(databf.readLine());
                logger.info("showing all books...");
                List<Record> recordlist = session.selectList("recordMapper.showRecords", cid);
                for (Record r : recordlist) {
                    Book book = session.selectOne("bookMapper.showBooks", r.getISBN());
                    System.out.println(book);
                }
            } else {
                // return book
                Integer cardnum = Integer.parseInt(databf.readLine());
                Integer aid = Integer.parseInt(databf.readLine());
                Integer cid = 2;
                logger.info("please input isdn:");
                String isbn = databf.readLine();
                logger.info("searching books...");
                List<Record> recordlist = session.selectList("recordMapper.showRecords", cid);
                boolean flag = false;
                for (Record r : recordlist) {
                    if (r.getISBN().equals(isbn)) {
                        session.update("bookMapper.returnbook", isbn);
                        session.delete("recordMapper.deleteOne", r);
                        session.commit();
                        logger.info("return book success!");
                        flag = true;
                        break;
                    }
                }
                if (flag == false)
                    logger.error("This book isn't borrowed! ");
            }
        }
    }



    public void queryBook() throws IOException {
        System.out.print("""
                 please enter 8 parameters . input 9 will exit\s
                1 category\s
                2 title\s
                3 publisher\s
                4 pub year1\s
                5 pub year2\s
                6 author\s
                7 price1\s
                8 price2\s
                """
        );
        String str = null;
        BufferedReader databf = new BufferedReader(new InputStreamReader(System.in));
        logger.info("please enter attribute");
        String sortattr = databf.readLine();
        while ((str = databf.readLine()) != null) {
            String[] temp = str.split(",");
            //（书号，类别，书名，出版社，年份，作者，价格，数量）
            String ISBN = temp[0].trim().equals("") ? null : temp[0].trim();
            String Category = temp[1].trim().equals("") ? null : temp[1].trim();
            String Title = temp[2].trim().equals("") ? null : temp[2].trim();
            String Publisher = temp[3].trim().equals("") ? null : temp[3].trim();
            Integer Year = Integer.parseInt(temp[4].trim());
            Integer Year2 = Integer.parseInt(temp[5].trim());
            String Author = temp[6].trim().equals("") ? null : temp[6].trim();
            Double Price = temp[7].trim().equals("") ? null : Double.parseDouble(temp[7].trim());
            Double Price2 = Double.parseDouble(temp[8].trim());
            queryCondition query = new queryCondition(ISBN, Category, Title, Publisher, Year, Author, Price, Price2, Year2);
            List<Book> list = session.selectList("bookMapper.findBooks", query);
            switch (sortattr) {
                case "Category":
                    list.sort(Comparator.comparing(Book::getCategory));
                    break;
                case "Title":
                    list.sort(Comparator.comparing(Book::getTitle));
                    break;
                case "Year":
                    list.sort(Comparator.comparing(Book::getYear));
                    break;
                case "Author":
                    list.sort(Comparator.comparing(Book::getAuthor));
                    break;
                case "Publisher":
                    list.sort(Comparator.comparing(Book::getPublisher));
                    break;
                case "Price":
                    list.sort(Comparator.comparing(Book::getPrice));
                    break;
                case "Total":
                    list.sort(Comparator.comparing(Book::getTotal));
                    break;
                case "Inventory":
                    list.sort(Comparator.comparing(Book::getInventory));
                    break;
            }
            for (Book B : list) {
                System.out.println(B);
            }
        }
    }
}
