# .bashrc

# Source global definitions
if [ -f /etc/bashrc ]; then
	. /etc/bashrc
fi

# User specific environment
if ! [[ "$PATH" =~ "$HOME/.local/bin:$HOME/bin:" ]]
then
    PATH="$HOME/.local/bin:$HOME/bin:$PATH"
fi
export PATH

# Uncomment the following line if you don't like systemctl's auto-paging feature:
# export SYSTEMD_PAGER=

# User specific aliases and functions
umask 037
CR='\033[1;31m'
CY='\033[2;30m'
CW='\033[1;37m'
NC='\033[0m'
#set -o vi
export EDITOR=vim
export VISUAL=vim
export CODEFORCES_DIR=~/CODE/
printf "\n${CW}SALAM REZA$NC\n"
export PS1="\[\033[s\033[0;0H\033[0;41m\033[K$CY\$(taghvim -l)\033[0;"'$(($COLUMNS-3))'"HSIB$NC\033[u\]<<>> "
unset CR CY CW NC
function LS {
	du -sh * | sort -h | tac;
}
function DICT {
	curl dict://dict.org/d:$1 2>/dev/null | less;
}
function PASTE {
	cat $1 | curl -F 'f:1=<-' ix.io 
}
