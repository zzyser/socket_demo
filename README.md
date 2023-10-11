# socket_demo
TCP/UDP 实现通信的demo

运行环境为 Linux / Ubuntu 系统

#### TCP 和 UDP 的区别

1. TCP面向连接（（如打电话要先拨号建立连接）;UDP是无连接的，即发送数据之前不需要建立连接。
2. TCP要求安全性，提供可靠的服务，通过TCP连接传送的数据，不丢失、不重复、安全可靠。而UDP尽最大努力交付，即不保证可靠交付。
3. TCP是点对点连接的，UDP一对一，一对多，多对多都可以
4. TCP传输效率相对较低,而UDP传输效率高，它适用于对高速传输和实时性有较高的通信或广播通信。
5. TCP适合用于网页，邮件等;UDP适合用于视频，语音广播等
6. TCP面向字节流，UDP面向报文



##### 为什么要三次握手而不是两次握手？

这是为了防止，因为已失效的请求报文，突然又传到服务器，引起错误， 这是什么意思？

​		假设采用两次握手建立连接，客户端向服务端发送一个syn包请求建立连接，因为某些未知的原因，并没有到达服务器，在中间某个网络节点产生了滞留，为了建立连接，客户端会重发syn包，这次的数据包正常送达，服务端发送syn+ack之后就建立起了连接。

​		但是第一包数据阻塞的网络突然恢复，第一包syn包又送达到服务端，这时服务端会认为客户端又发起了一个新的连接，从而在两次握手之后进入等待数据状态，服务端认为是两个连接，而客户端认为是一个连接，造成了状态不一致，如果在三次握手的情况下，服务端收不到最后的ack包，自然不会认为连接建立成功。

​		所以三次握手本质上来说就是为了解决网络信道不可靠的问题，为了在不可靠的信道上建立起可靠的连接，经过三次握手之后，客户端和服务端都进入了数据传输状态。



##### TIME-WAIT 状态为什么需要等待 2MSL?

​		2MSL，2 Maximum Segment Lifetime，即两个最大段生命周期,

- 1个 MSL 保证四次挥手中主动关闭方最后的 ACK 报文能最终到达对端
- 1个 MSL 保证对端没有收到 ACK 那么进行重传的 FIN 报文能够到达



------



- TCP.client： socket()  connect()  send()

- TCP.server:  socket()  bind()  listen()  accept()  recv()

  

  ------

  

- UDP.client：socket()  sendto()
- UDP.server: socket()  bind()  recvfrom()

------

