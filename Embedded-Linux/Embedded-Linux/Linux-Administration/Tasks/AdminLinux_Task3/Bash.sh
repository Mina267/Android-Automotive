#!/bin/bash

if [ -f "$HOME/.bashrc" ]; then
  echo "export HELLO=/$HOSTNAME" >> "$HOME/.bashrc"
  echo "LOCAL=/$(whoami)" >> "$HOME/.bashrc"
fi

gnome-terminal
