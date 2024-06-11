#!/bin/bash

#文字颜色结束符
color_end="\e[0m"
#判断数字大小改变颜色
change_color(){
    local percentage=$1

    # 判断并输出带颜色的百分比
    if (( $(echo "$percentage <= 30" | bc -l) )); then
        color="\e[32m"  # 绿色
    elif (( $(echo "$percentage <= 75" | bc -l) )); then
        color="\e[33m"  # 黄色
    else
        color="\e[31m"  # 红色
    fi
    percentage_str=$color$percentage$color_end
    echo $percentage_str
}

get_color_prefix(){
    local percentage=$1
    # 判断并输出带颜色的百分比
    if (( $(echo "$percentage <= 30" | bc -l) )); then
        color="\e[32m"  # 绿色
    elif (( $(echo "$percentage <= 75" | bc -l) )); then
        color="\e[33m"  # 黄色
    else
        color="\e[31m"  # 红色
    fi
    echo $color
}

# 获取系统信息
current_time=$(date +"%Y-%m-%d, %H:%M:%S")
version=$(cat /etc/os-release | grep "^PRETTY_NAME=" | cut -d '"' -f 2)
kernel=$(uname -r)
uptime=$(uptime -p)
ipaddr=$(hostname -I | awk '{print $1}')
hostname=$(hostname)

cpu_model=$(lscpu | grep "Model name:" | sed -r 's/Model name:\s{1,}//')
# memory=$(free -m | awk '/^Mem:/{printf("%sMB / %sMB (%.2f%% Used)", $3, $2, $3/$2 * 100)}')
# swap=$(free -m | awk '/^Swap:/{printf("%sMB / %sMB (%.2f%% Used)", $3, $2, $3/$2 * 100)}')

# 使用 free -m 并通过 awk 提取 memory/swap 的 total 和 used 的值
mem_info=$(free -m | awk 'NR==2{print $2, $3}')
swap_info=$(free -m | awk 'NR==3{print $2, $3}')
# 将 total 和 used 的值分配给变量并计算使用占比
mem_total=$(echo $mem_info | cut -d' ' -f1)
mem_used=$(echo $mem_info | cut -d' ' -f2)
mem_used_per=$(echo "scale=2; ($mem_used / $mem_total) * 100" | bc)
swap_total=$(echo $swap_info | cut -d' ' -f1)
swap_used=$(echo $swap_info | cut -d' ' -f2)
swap_used_per=$(echo "scale=2; ($swap_used / $swap_total) * 100" | bc)
#更改使用占比的文字颜色
mem_used_per=$(change_color $mem_used_per)
swap_used_per=$(change_color $swap_used_per)

# loadavg=$(cat /proc/loadavg | awk '{print "1m:" $1 ", 5m:" $2 ", 15m:" $3}')
loadavg_m1=$(cat /proc/loadavg | cut -d ' ' -f1)
loadavg_m5=$(cat /proc/loadavg | cut -d ' ' -f2)
loadavg_m15=$(cat /proc/loadavg | cut -d ' ' -f3)
loadavg_m1=$(change_color $loadavg_m1 * 100)
loadavg_m5=$(change_color $loadavg_m5 * 100)
loadavg_m15=$(change_color $loadavg_m15 * 100)
loadavg="$loadavg_m1(1m), $loadavg_m5(5m), $loadavg_m15(15m)"

total_processes=$(ps aux | wc -l)
root_process_count=$(ps -eo user= | grep -w root | wc -l)
non_root_process_count=$(ps -eo user= | grep -v -w root | wc -l)

users_logged=$(who | wc -l)

last_boot=$(who -b | awk '{print $3, $4}')
# last_login=$(last -n 1 -a | head -n 1)
last_login=$(last -n 1 -a | head -n 1 | awk '{print $1 " (" $10 ") " $2 " at " $3 " " $4 " " $5 " " $6 " " $7 " " $8 " " $9}')

# 获取文件系统信息
# filesystem_info=$(df -h | awk 'NR==1; /^\/dev/')
df_head=$(df -h | head -n 1)
df_info=$(df -h | awk 'NR==1; /^\/dev/' | tail -n 1)
used_percent=$(echo $df_info | awk '{print $5}')
used_percent_number=$(echo $used_percent | tr -d '%')
used_color_prefix=$(get_color_prefix $used_percent_number)
used_percent=$(change_color $used_percent_number)

df_info=$(echo $df_info | sed "s/[0-9]\+%/${used_percent//\\/\\\\}%/")
# 占比条长度
bar_length=50

# 计算已使用部分长度
used_length=$((used_percent_number * bar_length / 100))

# 构建占比条
bar=""
for i in $(seq 1 $used_length); do bar="${bar}$used_color_prefix#$color_end"; done
for i in $(seq 1 $((bar_length - used_length))); do bar="${bar}-"; done

# 显示信息
echo ""
echo ""
echo -e "[System Info]"
echo ""
echo ""
echo -e " Current Time      : \e[32m$current_time\e[0m"
echo -e " Version           : $version"
echo -e " Kernel            : Linux $kernel"
echo -e " Uptime            : \e[32m$uptime\e[0m"
echo -e " Ipaddr            : $ipaddr"
echo -e " Hostname          : $hostname"
echo ""
echo -e " Cpu               : $cpu_model"
echo -e " Memory            : $mem_used MB / $mem_total MB ($mem_used_per% Used)"
echo -e " SWAP              : $swap_used MB / $swap_total MB ($swap_used_per% Used)"
echo -e " Load avg          : $loadavg"
echo -e " Processes         : $root_process_count(root), $non_root_process_count(user), $total_processes(total)"
echo -e " Users Logged on   : $users_logged"
echo ""
echo -e " Last Boot         : $last_boot"
echo -e " Last Login        : $last_login"
echo ""
echo -e "[Filesystem Info]"
echo ""
echo ""
echo -e " $df_head"
echo -e " $df_info"
echo -e " [$bar]"
echo ""
echo ""