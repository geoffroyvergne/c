# lkm simple example

make 
make test


sudo insmod lkm_simple_example.ko
sudo dmesg

lsmod | grep "lkm_simple_example"

sudo rmmod lkm_simple_example
sudo dmesg
