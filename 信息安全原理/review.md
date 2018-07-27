<h2>信息安全原理期末复习整理</h2>

**collect by cy**

绝大部分的泄密都是从内部发生的

密码学的史前时代:
* 凯撒密码：对字母进行移位

密码学的演进：
1. Kerckhoff规则的提出
2. 计算机的产生
3. 公钥算法的提出

Kerckhoff规则:
一个系统的安全性不是建立在算法保密上，而是建立在秘钥上

增强安全性：凡是难以改变而且长时间使用的东西都会被对手知道
算法本身不具有保密性，安全依赖与秘钥的保密

计算机安全特点：
1. 综合性：系统安全总是基于整个体系中最薄弱的点
2. 过程性：是一个螺旋前进的过程
3. 动态性：系统安全是一个过程，会不断变化
4. 层级性：多层级的安全去解决风险
5. 相对性：没有绝对的安全

计算机安全四个要素：
1. 保密性(Confidentiality)：其他人能够看到你的数据吗
2. 完整性(Integrity)：你的数据会被非法篡改吗
3. 可用性(Availability)：我的资源是否可以访问(比如银行卡里面的钱是否能取出来)
4. 真实性(Authenticity)：对于identity的认证

计算机安全的概念：
1. 漏洞(Vulnerabilities)：系统的薄弱处
2. 威胁(Threats)：是否有可能造成损害的潜质
3. 攻击(Attacks)：human/another system利用漏洞进行攻击
4. 控制、对抗措施(Control)：对于漏洞的修复或移除的方式

安全攻击的类型：
1. 中断(Interruption)：攻击安全要素中的Availablity(eg.DOS / remove program or file)
2. 截取(Interception)(四者中唯一一个被动攻击的类型，很难被检测到，防范比检测更重要)：攻击安全要素中的Interceptior
3. 修改(Modification)：攻击安全要素中的Integrity，比如数字水印方式
4. 制造(Fabrication)：攻击安全要素的Authenticity，比如数字签名等方式提高不可抵赖性

其余三者比较容易被检测到，比较难防范，能够在damage后resume

密码的几个基础部分：明文、密文、加密算法、解密算法
* plaintext：P
* ciphertext：C
* encryption method：E()
* decryption method：D()
* key：K
* C = E<sub>k</sub>(P)
* P = D<sub>K</sub>(C)

经典的密码体系：
* 凯撒密码，Queen Mary密码，Vigenere Square(对抗频度分析的方法，而且可以自行决定秘钥而不是保密算法，符合Kerckhoff规则)， Book Cipher(电影中经常出现的桥段)
* 解码方式:频率分析(从高到低为E、T、A、O等)、Kasiski Test<br>
* Enigma体系(通过齿轮和连线和交换构建出庞大的密码)(解密方法：通过证明交换按钮是没用的，密码出现序列是有规律的，之后可以依靠暴力破解)

对称秘密学:
  + Fundamentals
  + Fiestel structure:使用块加密的方式；设计雪崩效应：
    + 扩散(Diffusion):使得密文的统计特性与**明文**之间的关系尽量复杂
    + 扰乱(Confusion):使得密文的统计特性与**加密秘钥**之间的关系尽量复杂

  + Fundamentals and Structure of DES / 3DES / AES
    + DES:使用56-bit的秘钥加密(但是在现代的算力下加密强度不够)，基于Fiestel结构，每个加密块为64-bit的。有很强的雪崩效应，有很强的抗解密性，只能暴力破解
    + 3DES: C = E<sub>k3</sub>[D<sub>k2</sub>[E<sub>k1</sub>[P]]] 这样的加密方式使得可以兼容传统的DES算法
    + AES(Advanced Encryption Standard):加密块为128-bit，key size为128/192/256-bit等，免疫所有已知攻击，在多平台执行快速，代码紧凑，设计简单

  + EBC:将P<sub>1</sub>为1-to-1变成C<sub>1</sub>,但是会被重放攻击(通过C<sub>k</sub>猜出P<sub>k</sub>)<br>
  + CBC:将前一个加密的块同时影响后续的加密，造成雪崩效应

非对称密码学:
  + Fundamentals
  + Difference between Symmetric and Asymmetric Key Cryptography?
    + 公开秘钥加密算法依赖于数学函数而不依赖于替代和置换
    + 公开秘钥加密算法是非对称的，使用两个独立的秘钥
    + 公钥密码使得发送端和接收端在不共享任何秘密消息的前提下即可交换大量秘密消息(实现保密通信)成为可能
  + Functions，encryption, signature, key exchange
  + The One-Way functions
    + DH Algorithm: 计算大整数的整数次幂比较容易，但是计算离散对数很困难<br>
      DH算法：
      + A生成自己的秘钥X<sub>a</sub>，B生成自己的秘钥X<sub>b</sub>，原根g=2或者3或者5(较小的数)，再约定一个素数p
      + A计算出KeyA = g<sup>X<sub>a</sub></sup>%p，B计算出KeyB = g<sup>X<sub>b</sub></sup>%p，将计算出的结果分别发给对方
      + B将拿到的A的传过来的数字KeyA，再进行(KeyA)<sup>X<sub>b</sub></sup>%p，同时A将拿到的B的传过来的数字KeyB，再进行(KeyB)<sup>X<sub>a</sub></sup>%p，这计算出的两个数字是相同的，由此交换得以确定了秘钥
    + RSA Algorithm：大素数相乘很容易，但大合数质因子分解很困难，计算方式略

对比对称/非对称密码学与应用模型：
* 对称密码学：
  + 优点：cheap，fast<br>
    用廉价的集成电路芯片即可完成大量的加密和解密
  + 缺点：秘钥分发是非常困难的
* 公钥：
  + 优点：秘钥的分发不再是一个问题
  + 缺点：相对比较昂贵和缓慢<br>
    加密和解密的硬件IC片十分昂贵
* 应用：
  + 使用公钥加密(如RSA)分发秘钥
  + 使用对称秘钥(如DES)去加密和解密 

数字签名：
* 对数字签名的要求
  + “绑定”到签名的文件
  + 收件人可以验证签名，并且任何其他人不能伪造签名
  + 签名人不能抵赖自己的签名
  + 签名必须能够被第三方验证以便解决争议
  + 能够验证签名日期和时间的签名，消息内容的签名时刻（不可重复使用，不可伪造，不可更改，时间绑定）

* 为什么数字签名需要使用单向hash函数：<br>当文档比较长的时候，不能对整份文档签名(即直接对整份文档进行RSA，成本太高)，但是依然要求一旦文档出现变化，签名就要失效。所以解决办法是我们对文档用单向hash函数缩小体积，之后对hash值进行签名以完成数字签名的要求
* 单向hash函数的概念：<br>
要求：将一份输入的文档变成一个大概100-bit左右的hash值输出<br>
要求以下性质：
  + 容易计算
  + 不容易被反向计算
  + 不容易找到碰撞(collision)

* 常用的单向hash函数:MD5/SHA-1/SHA-2...

消息认证码概念(Message Authentication Code, MAC)<br>
MAC主要是提供数据完整性验证服务，还是通过传统的对称秘钥的方法进行信息传递，因为公钥算法还是太慢，在底层实现不合适。

比较MAC和数字签名:
* MAC的发送者和接受者必须share秘钥
  + MAC只能通过专门的接收器进行验证
  + MAC不提供“不可抵赖”，所有可以验证消息机密性的人也可以生成一个MAC
  + 速度较快
* 数字签名不需要交换任何秘密消息
  + 数字签名能够被所有(有发送者的公钥)人验证
  + 数字签名不可抵赖
  + 速度较慢

认证(Authentication)和授权(Authorization)
* Authentication实现：
  + 你拥有的东西:Card, key, smart card
  + 你知道的东西:password etc.
  + 你所在的地方:IP address
  + 个人的特质:
    + 生物特质：指纹、虹膜、DNA
    + 个人习惯：笔迹、声音、走路姿势
* 储存，选择和保护密码:
  + 字典攻击的概念和加盐<br>
    史前的密码直接保存明文<br>
    早期的密码保存密码的hash值(但是人们使用的密码多是有意义的单词，所以可以进行字典攻击)<br>
    **字典攻击**：计算字典中的每一个单词的hash值，与用户的hash值进行匹配，字典大小比较有限，所以攻击很容易奏效<br>
    **加盐**：在用户的密码前加上几个无意义的随机字符(加盐)，再对加完盐的“新”密码进行hash，使得一样的密码却有不一样的hash值(显著提高字典攻击难度，但字典攻击依然是可能的)
  + 如何去选择和保护密码
      1. 字符+数字或随机密码
      2. 密码安全评估与检查
      3. Trojan(木马)防护,使用安全的登录工具
      4. 不同网站使用不同密码
      5. 不相信任何第三方软件
      6. 不要在不信任的地方登录重要的服务

安全访问控制和授权的概念
* 访问控制的三个元素
  1. 主体：可以访问对象的实体，例如用户或应用程序进程等
  2. 客体：正在访问的对象，如文件，程序，数据等
  3. 权限：主体可以使用对象的方法，例如读取，写入，删除，执行，再许可等
* DAC，MAC和RBAC的概念和规则
  + 自主访问控制(Discretionary Access Control, DAC):(例如：Unix OS)
    + 特性:主体可以自动将其访问权限的子集授予其他主体。
    + 缺点：访问权限会随着信息流改变，导致访问控制在某些时候不够严格；子主体的授权有时不是我们所希望的
    + 访问控制矩阵
      + 访问控制列表：每一个主体增加一个列表，里面指出他能访问的客体
      + Capability List: 每一个客体增加一个列表，指出能访问它的主体
  + 强制访问控制(Mandatory Access Control, MAC):通过给文件以密级来进行访问控制
    + Bell-Lapadula规则(in MAC):保证了机密性
      + 不向上读(低权限的不可读高密级的文件)
      + 不向下写(高权限的不可写低密级的文件):防止高密级的可以通过此方法向下泄露高密级的文件
    + 隐通道(Convert Channel):利用系统资源进行通信的通道<br>
    通过一些系统资源的变化以获取一些高密级的文档到底在做什么<br>
    识别后对策：
      + 关闭隐通道或者使他slow down
      + 侦测那些尝试使用隐通道的user
      + 容忍它的存在
    + 隐通道无法完全消除,处理隐通道的方法：
      + 限制共享资源(如磁盘、CPU，内存等等)，share只有在同一个密级的情况下产生
      + 限制带宽(如增加噪音等)
  + 基于角色的访问控制(Role-Based Access Control,RBAC)
    + Role:每一个role都是由一组用户组成，他们都与相关操作相关，用户只要属于这个role就有权执行这些操作

    可以很好地进行授权管理，也能很好地建立起层级关系，而且容易获得最小权限，防止高等级的人权限过大导致一些意外产生，同时RBAC能够实现DAC和MAC
* 安全访问控制的核心原则
  + 最小的特权(如把super-user分为system Administrator，Security Administrator和Audit Administrator三个)，分权
  + 授权管理模式
    MAC:密级管理
    DAC:很多种
    RBAC:很多种

网络安全：
* 常规攻击
  + 嗅探(Sniff)<br>
    很多在网上传输到东西都没有加密，混合模式网络接口卡能读取所有信息(工具比如Wireshark,Tcpdump / libpcap等)
  + ARP欺骗(ARP Spoofing)<br>
    OS采用ARP缓存实现ARP，但ARP缓存的更新策略不同。一些OS（Solaris等）只接受第一个响应包。<br>
    所以，伪造一个ICMP数据包，让受害者机器启动一个ARP请求。在紧要关头，向受害者机器发送伪造的ARP响应包，ARP缓存将被毒死。
  + IP欺骗(IP Spoofing)
    原始方法：伪造受害者ip在广播端口发送ping，导致同一个网段内所有主机同时回包导致受害者直接crash
  + TCP SYN Flooding(important!)
    + 概念,如何攻击,如何成功?<br>
      因为TCP建立连接需要3次握手，分别为客户端发给服务器的SYN<sub>c</sub>，服务器发给客户端的SYN<sub>s</sub>和ACK<sub>c</sub>，与最后客户端发给服务器的ACK<sub>s</sub><br>
      如果客户端不断用不同IP向服务器发送SYN<sub>c</sub>而不进行后续过程不回复ACK，因为服务器每次需要额外开一个线程处理，能够很快让进程的堆栈(2M/线程)溢出(总共32位机器可使用的就2G左右的堆栈)<br>
    攻击者通过伪造ip发送大量请求，每一次请求都能够获得一部分服务器资源，最后使得服务器资源耗尽，无法再进行连接<br>
    这是最经典的DOS攻击，进攻者无需太多资源，而接收的服务器却为每一个请求需要开额外的线程(利用两端不对等进行的攻击)<br>
    DOS攻击是攻击者伪造造成的，是可以被解决的,但是DDOS攻击是难以被解决的（如银行挤兑等）许多真实的请求导致资源的耗竭
    + 如何避免<br>
    第一种方法：如果一旦SYN队列满了，随机删掉一个，如果删掉正常的请求，那个用户很快就会再次connect，而且正常情况下删掉不正常请求的概率要远大于删除正常的请求;而且整个代码实现十分容易<br>
    第二种方法:使用SYN Cookie的方式，尝试解决攻击者与被害者资源请求不均等的情况。保证服务器不会储存状态除非收到第二次含服务器确认cookie的请求(**这个请求是不可伪造的，因为服务器发还给的cookie包含了端口，时间等各种信息的hash值**)。
      + 服务器将将套接字信息（服务器和客户端的IP和端口）存储在Cookie中，并将Cookie发送给客户端(利用单向hash函数进行计算，而且要快速计算，否则一样会导致计算资源的耗竭)
      + 客户端必须将Cookie连同第二个请求一起发送，服务器将重新计算Cookie并与客户端发送的Cookie进行比较。
  + TCP SYN prediction<br>
    TCP协议中的每个包都有序列号SYN，接收方将排序与根据SYN重组数据包，一旦攻击者可以预测SYN，他可以发送“伪造”的数据包给接受者并将包重新组织使得其满足攻击者的目的。<br>
    TCP SYN预测攻击是许多其他攻击的来源，包括
      + TCP欺骗
      + TCP连接劫持
      + TCP重置

    对抗方式很简单，使得SYN随机生成就可以了
  + TCP拥堵控制(TCP Congestion Control)
    + 一旦丢包，TCP要求降速到之前的一半，查看是否还会丢包，如果还会丢，就再降速直至0
    + 如果不再丢包，就将速度缓慢提升上去
    + 但是，如果在整个体系中，有人不遵守整个协议，当一端降速之后另一端反而提高速度，会使得一端速度直接为0，而另一端获得很高的速度
    + 解决方法:添加ACK nonces，在ACK返回nonce以证明它不是欺骗。
  + DNS Spoofing
    + 修改DNS服务器或本地DNS服务(经常修改DNS缓存数据库，使其成为DNS缓存中毒攻击)，重定向所需页面到错误IP，这使得流量被发送到另一个服务器(通常是攻击者自己的机器)
    + DNS的响应与请求是没有认证的，DNSSEC(Domain Name System Security Extensions)可以解决这个问题
+ Concepts of IPSEC
  + 验证头Authentication Headers(AH):提供IP包的数据完整性和认证服务
  + 载荷安全性封装Encapsulating Security Payloads(ESP):提供安全、保密和认证服务（可选）
  + 安全相关Security Associations(SA):IPSec使用安全关联（SA）来集成安全服务
  + Model of Operation：
    + Transport Model<br>
    传输模式IPSec只保护IP分组内容，而不保护IP头<br>
    由于IP头没有被修改，路由过程不会受到影响。传输层和应用层的数据都受到保护。<br>
    典型地用于PtoP通信
    + Tunnel Model<br>
    隧道模式IPSec将对整个IP分组进行加密或认证。原始IP分组将被隐藏到新的IP分组中，并且将附加新的IP头。<br>
    典型地用于保护VPN在网络和网络之间、主机的调制解调器通信和PtoP通信。

+ Concepts of TLS/SSL
  + SSL connection and SSL session
    + SSL Connection<br>
    SSL连接，一个端到另一个端的连接，这个连接是临时的
    + SSL Session<br>
    SSL会话，一个客户端与服务器的建立，在建立的时候进行协商，之后就不需要协商秘钥
  + SSL/TLS protocol
    + 在传输层和应用层中间的一个协议，本身将这里再分成两层:
      + 握手层:相互认证(客户端与服务器都要认证)四次握手的过程<br>
      这其中，告知服务器客户端的操作系统、分辨率等各种信息（客户端系统支持的内容）然后服务器给客户端适合的界面
      + 数据层：数据分块，协商秘钥，加密和增加SSL头(用握手保证信息的加密与完整性校验)

Malicious Code:
+ Concepts and difference of virus, worm and Trojan horse.
  + 木马：有显性目的，同时具有隐性目的（恶意）的程序，通过内部进行攻击(可以有复制能力，但是核心特征是隐身性)
  + 病毒：一定要附着在另一个软件上的程序，当执行软件的时候同时执行病毒。可以通过跳转等方式将恶意代码藏在执行文件内以躲过杀毒软件的病毒库匹配
    + 病毒也可以加密，通过一段解密代码放在加密代码前面，以躲过侦测(侦测该病毒方法：侦测解密段(正常程序不会加密自己))
    + 通过改变加密方式或者多次加密的方式可以让病毒发生"变异"
    + 病毒还可以通过增加无用代码的方式来绕过杀毒软件的检查
+ Defenses of Malicious Code
  + Distinguish between data, instructions(区分数据与指令，使得恶意代码无法隐藏，而且不会出现代码在运行时变化)
  + Limit objects accessible to processes(控制信息流，如在浏览器，虚拟机等中运行)
  + Inhibit sharing(控制分享)
  + Detect altering of files(检测文件变更)
  + Detect actions beyond specifications(检测超出规范的行为):多版本编程为了稳定性3机计算投票进行决定计算结果以防止单机失败（在航空航天领域）;同时也通过assert等方式及时验证正确性
  + Analyze statistical characteristics(分析统计特征)
+ How botnets formed, how does it used for attack? Concepts of DDOS attack.
  + 早期：通过聊天室的方式控制的僵尸网络
  + 现在：层级化管理（层级化聊天室）的方式进行僵尸网络一起完成（以防聊天室被发现）
  + 未来：向着无中心化的方向发展
  + 进行DDOS攻击不再需要伪装ip