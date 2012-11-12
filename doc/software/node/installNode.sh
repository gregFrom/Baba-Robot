#!/bin/bash

# http://www.tumblr.com/tagged/occidentalis

sudo apt-get update && sudo apt-get upgrade
[[ -z $(which git-core) ]] && sudo apt-get install git-core build-essential

cd ~
git clone https://github.com/joyent/node.git
cd node
git checkout v0.8.9 -b v0.8.9

cd ~
curl -O https://github.com/joyent/node/commit/25c2940a08453ec206268f5e86cc520b06194d88.patch
curl -O https://github.com/joyent/node/commit/1d52968d1dbd04053356d62dc0804bcc68deed8a.patch
cd node
git apply --stat --apply ../25c2940a08453ec206268f5e86cc520b06194d88.patch
git apply --stat --apply ../1d52968d1dbd04053356d62dc0804bcc68deed8a.patch

./configure
make
sudo make install
