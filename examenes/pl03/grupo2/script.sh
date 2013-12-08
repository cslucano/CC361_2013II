#ejecutar con sudo
sudo mkdir /home/a;
sudo mkdir /home/b;
cd /home/b;
dd if=/dev/zero of=imagen.ext3 count=4314141;
mkfs.ext3 /home/b/imagen.ext3;
sudo mount /home/b/imagen.ext3 /home/a;
sudo mkdir /home/a/A;
sudo mkdir /home/a/B;
sudo mkdir /home/a/etc;
touch /home/a/etc/hostname;
echo $host > /home/a/etc/hostname;
sudo umount /home/a;
sudo dd if=/home/b/imagen.ext3 of=/dev/sdg bs=4M; sync;
#modificar /dev/sdg (ruta usb) segun la pc
