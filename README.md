# FT_MALCOLM

In this project of network security, you will implement the Address Resolution Protocol spoofing/poisoning method, which is one of the most basic Man In The Middle attacks. This attack is possible using a vulnerability present in the the way the ARP protocol works and interacts in a network.


### WHAT IS ARP?

The Address Resolution Protocol is a layer 2 protocol used to map MAC addresses to IP addresses. All hosts on a network are located by their IP address, but NICs do not have IP addresses, they have MAC addresses. ARP is the protocol used to associate the IP address to a MAC address. ARP uses broadcast communication (one-to-all) in order to ask all end clients within a LAN, what is the physical address of a given IP. 


### WHAT IS ARP POISONING?

ARP poisoning (also known as ARP Spoofing) is a well-known technique used to perform MITM (man-in-the-middle) or DoS (denial of service) attacks on a LAN. You might think that every security researcher and every hacker knows this technique inside out. After all it is pretty simple. The attack consists of an attacker sending a false ARP reply message to the default network gateway, informing it that his or her MAC address should be associated with his or her target's IP address. Because the ARP protocol was designed purely for efficiency and not for security, ARP Poisoning attacks are extremely easy to carry out as long as the attacker has control of a machine within the target LAN or is directly connected to it.


### USAGE

- Clone the repository `git clone`
- Build and start up the Docker Containers with `make docker` (make sure you have Make, Docker and Docker Compose installed before this step)
- Get inside Docker Images using `docker exec -it [DOCKER ID] bash` or using VSCode Docker extension
- Inside **Victim's Docker Container**, run `ifconfig` and get the Container IP (inet) and MAC (ether) adresses
- Inside **Attacker's Docker Container**, get in ft_malcolm directory and compile with `make`
- Run the program with `./ft_malcolm [SOURCE IP] [SOURCE MAC] [VICTIM IP] [VICTIM MAC]` where:
  - **SOURCE IP** is the IP of the machine you're pretending to be. You can simple get Victim IP and change the last byte (e.g. if the victim IP is 172.0.0.4, you can use 172.0.0.6)
  - **SOURCE MAC** is the **spoofed MAC Adress** you're sending to the victim. You can use any valid MAC, like aa:aa:aa:aa:aa:aa
  - **VICTIM IP** is the IP you got in Victim Container with `ifconfig`
  - **VICTIM MAC** is the MAC you got in Victim Container with `ifconfig`
- Now the program is waiting an ARP Request to be broadcasted by the victim
- Inside **Victim Docker Container**, try to establish a connection with the **SOURCE IP**, in this example `ping 172.0.0.6`
- Note that the program running in **Attacker's Container** intercepted the ARP Request and responded.
- The **ARP Poisoning** is complete. If you run `arp -a` inside **Victim's Container** you will notice that the **spoofed MAC Address** we passed to the program has been injected into the victims ARP table. Now every request addressed to the **Source IP** will be sent to the Attacker's machine, even if this IP does not belong to him.
- You can listen the ARP traffic if you run `tcpdump -vv -i eth0 arp` in another terminal inside **Attacker's Docker Container** before the attack. You will notice the Victim Request and the Attacker Reply.


### RESOURCES

(https://datatracker.ietf.org/doc/html/rfc826)
(https://datatracker.ietf.org/doc/html/rfc7042)
(https://www.networkacademy.io/ccna/ethernet/what-is-arp)
(https://man7.org/linux/man-pages/man7/arp.7.html)
(https://yurmagccie.wordpress.com/2018/04/18/address-resolution-protocol-arp/)
(https://stackoverflow.com/questions/16710040/arp-request-and-reply-using-c-socket-programming)
(https://copyprogramming.com/howto/arp-request-and-reply-using-c-socket-programming)
(https://lynxbee.com/sending-arp-request-and-receiving-arp-reply-using-c-code/)
(https://copyprogramming.com/howto/filter-arp-replies)
