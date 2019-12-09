# In-Switch-Packet-Creation-
In Switch packet Generation API used for creating Control packets at the switch

To Run this:

1)Install the Beba-Controller from the below link:
https://github.com/beba-eu/beba-ctrl

2)Install the beba-switch from the below link:
https://github.com/beba-eu/beba-switch

3)Install the mininet and then install the Beba-switch in the mininet. Follow the below steps:
 git clone git://github.com/mininet/mininet
  mininet/util/install.sh -n3f 

4)The above steps will install the beba-switch in mininet. Then later copy the files in the repository to the below directory:
beba-switch/oflib-exp/

5)Restart mininet and connect them the beba controller.
