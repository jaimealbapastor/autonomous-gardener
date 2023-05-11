# Checking the Partitions

Before formatting, locate a partition you wish to format. 

To do so, run the lsblk command that displays block devices. 

Block devices are files that represent devices such as hard drives, RAM disks, USB drives, and CD/ROM drives.

```shell
lsblk
```

The terminal prints out a list of all block devices.

We will use the /dev/mmcb1p1 partition.

## Locating partitions with lsblk command.

To display a list containing file system information, add the -f option:

````shell
lsblk -f
````

The terminal prints out the list of all block devices. The partitions that do not contain information on the file system in use are non-formatted partitions.

Locating non-formatted partitions with lsblk -f command.

We will formate the partition with ext4.

## Formatting Disk Partition with ext4 File System

1. Format a disk partition with the ext4 file system using the following command:

````shell
sudo mkfs -t ext4 /dev/mmcb1p1
````

2. Next, verify the file system change using the command:

````shell
lsblk -f
````

The terminal prints out a list of block devices.

3. Locate the preferred partition and confirm that it uses the ext4 file system.
The process of formatting disk partition using the ext4 file system in Linux.

Before using the disk, create a mount point and mount the partition to it. A mount point is a directory used to access data stored in disks.

## Mount's creation point for the partition

1. Create a mount point by entering:

````shell
sudo mkdir -p [mountpoint]
````

2. After that, mount the partition by using the following command:

````shell
sudo mount -t auto /dev/mmcb1p1 [mountpoint]
````

There is no output, the process completes successfully.
The process of creating mount point and mounting.

3. Verify if the partition is mounted using the following command:

````shell
lsblk -f
````

## Temporarily mount the new partition:

````shell
sudo mkdir /mnt/tmp
sudo mount /dev/mmcb1p1 /mnt/tmp
````

assuming /mmcb1p1 is the new partition for HOME

Copy HOME to the new location:

````shell
sudo rsync -avx /home/ /mnt/tmp
````

We then may mount the new partition as HOME with

````shell
sudo mount /dev/mmcb1p1 /home
````

## Make HOME permanent

We need to know the UUID of the new partition for the fstab entry seen from:

````shell
sudo blkid
````

Note or copy/paste the correct UUID to edit your fstab with

````shell
sudo nano /etc/fstab   # or any other editor
````

and add the following line at the end:

````shell
UUID=<noted number from above>    /home    ext4    defaults   0  2
````