# QtSocks5Server  
  
支持:  
socks5。  
用户密码验证  
TCP。  
UDP。  
  
不支持:  
BIND。(无需求，修改了socks5协议，不影响正常使用。有兴趣的朋友可以自行添加。)  
socks4。  
http。  
因看Qt无人使用socks5.而纯c对于我来说麻烦。虽然没有3proxy好，3proxy内存占用1.1M，本应用占用1.7M.暂无高并发高容量测试。  
参考socks5lib后，并使用，发现有很多BUG，并且并没有很好的利用Qt的信号槽，此应用使用信号槽。由其他项目得到的启发，忘记什么项目了。后续增加内容。      
  
    
有兴趣的朋友可以一起做！
