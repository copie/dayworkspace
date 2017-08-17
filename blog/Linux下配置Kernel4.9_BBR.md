# Linux下配置Kernel4.9_BBR

## 为什么使用 BBR

BBR是近日Google开源的黑科技TCP加速工具。
现已加入Kernel4.9内核

**TCP BBR 致力于解决两个问题：**
1. 在有一定丢包率的网络链路上充分利用带宽。
2. 降低网络链路上的 buffer 占用率，从而降低延迟。

## 如何使用(开启BBR)

1. 先将 linux 内核升级到4.9 现在大多数都应该满足这个条件了

2. 开启BBR

        echo "net.core.default_qdisc=fq" >> /etc/sysctl.conf
        echo "net.ipv4.tcp_congestion_control=bbr" >> /etc/sysctl.conf
        sysctl -p
        sysctl net.ipv4.tcp_available_congestion_control
        sysctl net.ipv4.tcp_congestion_control

然后看下启动成功没：

    lsmod | grep bbr

如果有tcp_bbr，那么就配置成功了