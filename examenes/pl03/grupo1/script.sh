#! /bin/bash
echo "******Desmontando device USB******";
umount /dev/sda1

echo "******formateando USB con ext3******";
mkfs.vfat /dev/sda1

echo "******creando archivos...******";

mkdir -p /media/hechicero/42AB-E172/A
mkdir -p /media/hechicero/42AB-E172/B
mkdir -p /media/hechicero/42AB-E172/etc

echo "******creando hostname******";
echo $PATH > /media/hechicero/42AB-E172/etc/hostname

echo "******creando imagen.ext3******";
dd if=/dev/sda1 |pv|dd of=/home/hechicero/Desktop/imagen.ext3

echo "******Montando imagen.ext3 a carpeta tmp******";
mount -t ext3 -o defaults /home/hechicero/Desktop/imagen.ext3 /home/hechicero/Desktop/tmp
