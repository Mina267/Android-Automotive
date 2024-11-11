#!/bin/bash
USER_NAME=$2
GRP_NAME=$1


if [getent group "$GRP_NAME"  > /dev/null 2>&1 ]; then
        echo "Group "$GRP_NAME" already exist"
else 
        sudo groupadd "$GRP_NAME"
        echo "Group '$GRP_NAME' created"
fi  

if [id -u "$USER_NAME"  > /dev/null 2>&1 ]; then
        echo "User "$USER_NAME" already exist"
else 
	sudo useradd "$USER_NAME"
	sudo usermod -aG "$GRP_NAME" "$USER_NAME"
        echo "User '$USER_NAME' created and add in group '$GRP_NAME'"
fi

echo "Diplay '$USER_NAME' info: "
id $USER_NAME

echo "Diplay '$GRP_NAME' info: "
getent group $GRP_NAME

