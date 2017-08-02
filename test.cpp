location /
{
    root / usr / local / www;
    index index.php index.html index.htm;
}

location ~ \.php$
{
    root / usr / local / www;
    fastcgi_pass 127.0.0.1 : 9000;
    fastcgi_index index.php;
    include fastcgi.conf;
}