#!/usr/bin/env bash

set -e

MIGRATE_HOST="aru2"
NAME="guest14-debian"
IMAGES_DIR="/var/lib/libvirt/images"

sudo pacman -S --needed --noconfirm libvirt dmidecode qemu-full virt-viewer virt-install iptables-nft nfs-utils krb5
sudo usermod -aG libvirt "$USER"

# https://wiki.archlinux.org/title/KVM#Checking_support_for_KVM
# https://docs.redhat.com/en/documentation/red_hat_enterprise_linux/6/html/virtualization_host_configuration_and_guest_installation_guide/app_tcp_ports#App_TCP_Ports

# /etc/exports
# /mnt 192.168.1.0/24(rw,no_root_squash,sync)

ssh "root@$MIGRATE_HOST" "systemctl start libvirtd virtlogd "
sudo systemctl start libvirtd virtlogd nfs-server krb5-kdc krb5-kadmind

#sudo exportfs -arv

ssh "root@$MIGRATE_HOST" "mount aruhost:/mnt $IMAGES_DIR"
sudo mount aruhost:/mnt "$IMAGES_DIR"

cd "$IMAGES_DIR"

sudo curl -LOC - https://cloud.debian.org/images/cloud/bookworm/20240717-1811/debian-12-nocloud-amd64-20240717-1811.qcow2
sudo cp debian-12-nocloud-amd64-20240717-1811.qcow2 "$NAME.qcow2"
sudo chmod 666 "$NAME.qcow2"

ssh "root@$MIGRATE_HOST" "virsh net-start default"
sudo virsh net-start default

sudo virt-install \
	--connect qemu:///system \
	--name "$NAME" \
	--memory 2048 \
	--vcpus 2 \
	--disk "$IMAGES_DIR/$NAME.qcow2" \
	--import \
	--graphics none \
	--os-variant debianbookworm

sudo virsh migrate \
	--live  \
	--verbose \
	--comp-methods zstd \
	--parallel \
	"$NAME" "qemu+ssh://$MIGRATE_HOST/system"
