import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;
import java.security.cert.TrustAnchor;
import java.util.Date;
import java.util.Scanner;
import java.util.Vector;
import java.util.concurrent.Executor;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

import static java.lang.Thread.sleep;


// 通信线程
class ClientThread implements Runnable {

    private Socket client; // 客户端套接字
//    private DataInputStream in; // 输入流

    private int type;       // 请求类型: 1 - html, 2 - txt, 3 - img
    private String postfix; // 请求图片时使用

    public ClientThread(Socket s) throws IOException, InterruptedException {

//        System.out.println("port: " + s.getPort() +" " + (new Date()).toString());
        this.client = s;
    }

    // 获取请求资源路径（除前缀)
    public String getResourcePath(String s)
    {
        
        //获取资源的位置
        int begin = s.indexOf(' ')+1;
        int end = s.indexOf(' ', begin);
        String name = s.substring(begin, end);
        if (name.equals("/html/dopost"))
        {
            name = "/dopost";
            return name;
        }
        // 区分请求类型
        String r_type = s.substring(0, begin-1);
        System.out.print(r_type + ": ");

        //默认请求(转到test.html)
        if (name.equals("/")) {
            name = "/html/test.html";
            System.out.println("index.html");
        } else {
            System.out.println(name);
        }

        // 区分资源类型
        postfix = name.substring(name.indexOf('.')+1);
//        System.out.println("postfix:" + postfix);
        if (postfix.equals("html") ||  postfix.equals("htm"))
            type = 1;
        else if(postfix.equals("txt"))
            type = 2;
        else if(postfix.equals("jpg") || postfix.equals("jpeg"))
            type = 3;
        else
            type = 0;

        return name;
    }

    // 返回404
    public void NotFound() throws IOException
    {
        StringBuffer err = new StringBuffer();
        DataOutputStream out = new DataOutputStream(client.getOutputStream());
        err.append("HTTP/1.1 404 file not found\r\n" + "Content-Type:text/html\r\n" + "Content-Length:22\r\n" + "\r\n" + "<h1>404 Not Found</h1>");
        try
        {
            out.write(err.toString().getBytes());
            out.flush();
            out.close();
        }
        catch (IOException e)
        {
            e.printStackTrace();
        }
    }

    // 响应处理
    public void response(File file)
    {
        try {
            DataOutputStream out = new DataOutputStream(client.getOutputStream());
            //根据响应报文格式设置
            out.write("HTTP/1.0 200 OK\r\n".getBytes());
            out.write("Server: MyWebServer\r\n".getBytes());
            out.write(("Date: " + (new Date()).toString() + "\r\n").getBytes());
            switch(type)
            {
                case 1: // html
                    out.write("Content-Type:text/html\r\n".getBytes());
                    break;
                case 2: // txt
                    out.write("Content-Type:text/plain\r\n".getBytes());
                    break;
                case 3: // jpg
                    out.write("Content-Type:image/jpeg\r\n".getBytes());
                    break;
                default:
                    out.write("Content-Type:text/plain\r\n".getBytes());
                    break;
            }
            int len = (int) file.length();
            out.write(("Content-Length:" + len + "\r\n").getBytes());

            out.write("\r\n".getBytes());//报文头和信息之间要空一行
            // 读取文件
            DataInputStream in = new DataInputStream(new FileInputStream(file));
            byte buf[] = new byte[len];
            in.readFully(buf);
            // 发送文件
            out.write(buf, 0, len);
            out.flush();

            in.close();
            out.close();
        }
        catch (Exception e)
        {
            System.out.println(e.getMessage());
            System.exit(1);
        }
    }

    public void check() throws IOException
    {
        boolean flag = false;
        int len = 0;
        DataInputStream in = new DataInputStream(client.getInputStream());
        // 获取文本长度
        while(true)
        {
            String line = in.readLine();
            if(line.length() == 0) break;
            int pos = line.indexOf(':');
            String key = line.substring(0, pos);
            if(key.equals("Content-Length")) {
                len = Integer.parseInt(line.substring(pos+2));
            }
        }
        // 校验信息
        char[] txt = "login=3200104392&pass=4392".toCharArray();
        if(len == 26)
        {
            int i;
            for(i = 0 ; i < 26; i++)
            {
                char c = (char)in.read();
                if(c != txt[i]) break;
            }
            // 检验通过
            if(i == 26)
                flag = true;
        }
        DataOutputStream out = new DataOutputStream(client.getOutputStream());
        // 返回验证结果
        out.write("HTTP/1.0 200 OK".getBytes());
        out.write("Content-Type:text/html".getBytes());
        if (flag)
        {
            out.write("Content-Length:22\r\n".getBytes());
            out.write("\r\n".getBytes());
            out.write("<h1>Login Success!<h1>".getBytes());
        }
        else
        {
            out.write("Content_Length:21\r\n".getBytes());
            out.write("\r\n".getBytes());
            out.write("<h1>Login Failed!<h1>".getBytes());
        }
        out.flush();
        out.close();
    }

    @Override
    public void run()
    {
        try
        {
            // 读取浏览器提交的请求
            DataInputStream in = new DataInputStream(client.getInputStream());
            String msg = in.readLine();
            String method = msg.substring(0, msg.indexOf(' '));

            if(method.equals("GET"))
            {
                    // 获取文件路径
                    String fileName = getResourcePath(msg);
                    String prefix = "D:\\wwwroot"; // 此处默认读取D盘wwwroot目录下的文件，可以对字符串进行更改
                    File file = new File(prefix + fileName);

                    if (file.exists())
                    {
                        System.out.println("开始发送：" + fileName);
                        response(file);
                    }
                    else
                    { // 错误处理
                        System.out.println("错误：未找到文件");
                        NotFound();
                    }
            }
            else if (method.equals("POST"))
            {
                System.out.println("hanle post");
                if(!getResourcePath(msg).equals("/dopost"))
                {
                    System.out.println("错误：路径不是dopost");
                    NotFound();
                }
                else
                    check();
            }

            client.close();
        }
        catch (Exception e)
        {
            e.printStackTrace();
        }
    }
}

class Handle implements Runnable { // 监听客户端请求
    private ExecutorService threadPool = Executors.newFixedThreadPool(20);
    private ServerSocket server;
    public Handle(int Port) throws IOException {
        ServerSocket server = new ServerSocket(Port);
        System.out.println("初始化完毕，正在监听端口：" + server.getLocalPort());
        this.server = server;
    }
    @Override
    public void run()
    {
        while(true)
        {
            Socket clientSocket = null;
            try
            {
                clientSocket = server.accept();
            }
            catch (IOException e)
            {
                break;
            }
            if (clientSocket != null && !clientSocket.isClosed())
            {
                try
                {
                    threadPool.execute(new ClientThread(clientSocket));  // 通过线程池中分配一个线程
                }
                catch (IOException | InterruptedException e)
                {
                    throw new RuntimeException(e);
                }
            }
        }
    }

    public void stop() throws IOException {
        threadPool.shutdownNow();
        server.close();
        System.out.println("服务器已停止运行!");
    }
}


// 服务器线程
public class WebServer {
    private static int Port = 4392;    // http://dns-name:port/file.监听端口号

    public static void main(String[] args)
    {
//        ExecutorService threadPool = Executors.newFixedThreadPool(20);

        try {
            // 创建服务器，监听客户端请求的线程
            Handle h = new Handle(Port);
            new Thread(h).start();

            System.out.println("您可以输入'exit'以结束运行");
            while(true)
            {
                Scanner in = new Scanner(System.in);
                String input = in.nextLine();
                if(input.equals("exit"))
                {
                    h.stop();
                    break;
                }
            }
        }
        catch
        (Exception e)
        {
            e.printStackTrace();
        }
    }
}