FROM ubuntu

ADD run.sh /run.sh
RUN chmod 755 /*.sh

# 更新
RUN apt-get update
RUN apt-get upgrade -y
# 安装 ssh server
RUN apt-get install ssh -y
# 修改 root 密码
RUN echo "root:copyist" | chpasswd
# 修改 ssh server 配置文件 远程 root 登录 启动自启 和 端口映射
RUN sed -i "s/PermitEmptyPasswords no/PermitEmptyPasswords yes/g" /etc/ssh/sshd_config
RUN sed -i "s/PermitRootLogin prohibit-password/PermitRootLogin yes/g" /etc/ssh/sshd_config
RUN mkdir /var/run/sshd
EXPOSE 22/tcp


ENV APACHE_RUN_USER www-data
ENV APACHE_RUN_GROUP www-data
ENV APACHE_LOG_DIR /var/log/apache2
ENV APACHE_PID_FILE /var/run/apache2.pid
ENV APACHE_RUN_DIR /var/run/apache2
ENV APACHE_LOCK_DIR /var/lock/apache2
ENV APACHE_SERVERADMIN admin@localhost
ENV APACHE_SERVERNAME localhost
ENV APACHE_SERVERALIAS docker.localhost
ENV APACHE_DOCUMENTROOT /var/www

# apache 安装与启动自启
EXPOSE 80/tcp
RUN apt-get install apache2 -y
RUN mkdir -p /var/lock/apache2 && mkdir -p /app && rm -rf /var/www/html && ln -s /app /var/www/html
COPY sample/ /app

WORKDIR /app
CMD ["/run.sh"]