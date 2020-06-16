# lkm example

make
make test


(in the above example, replace MAJOR with the value you obtain from “make test” or “dmesg”)

sudo mknod /dev/lkm_example c 244 1
cat /dev/lkm_example
dd if=/dev/lkm_example of=test bs=14 count=100

sudo rmmod lkm_example
sudo rm /dev/lkm_example
