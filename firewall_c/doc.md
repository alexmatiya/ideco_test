
Заходим в папку с проектом:
```bash
cd firewall_c
```
Даем разрешение на исполнение файла:
```bash
chmod +x test.sh
```
Запускаем файл из командной строки:
```bash
./test.sh
```
Этот скрипт будет выполнять следующие действия:
- Собирать проект с помощью make.
- Запускать проект со статическими(вручную прописанными) тестовыми пакетами(файл test_packets_с.txt) или
с динамическими(нагенерированными) пакетами(файл test_dinamic_packets_c.txt)
- Выдавать статистику по пакетам, прошли они правила или нет.



Для генерации пакетов:
1. Скомпилировать файл 
```bash
gcc -o generate_packets_c generate_packets_c.c
```
2. Запустить программу из командной строки:
```bash
./generate_packets_c
```

Пример на вход:

```
10.0.1.11 1.1.1.1 0 0 6
10.0.2.12 1.1.1.1 0 0 6
10.0.2.12 8.8.8.8 0 0 6
10.0.3.13 1.1.1.1 0 0 6
1.1.1.1 1.2.3.4 0 0 17
1.1.1.1 1.2.3.4 0 0 6
1.1.1.1 10.0.9.1 0 0 6
10.0.5.32 1.1.1.1 0 0 17
```

Пример на выход:
```bash
------------------------------------------------------------------------------------------------------
№packet          src_ip          dst_ip          src_port        dst_port        protocol        =>action
------------------------------------------------------------------------------------------------------
Пакет 1          10.0.1.11       1.1.1.1         0               0               6               => ACCEPT
Пакет 2          10.0.2.12       1.1.1.1         0               0               6               => DROP
Пакет 3          10.0.2.12       8.8.8.8         0               0               6               => ACCEPT
Пакет 4          10.0.3.13       1.1.1.1         0               0               6               => ACCEPT
Пакет 5          1.1.1.1         1.2.3.4         0               0               17              => DROP
Пакет 6          1.1.1.1         1.2.3.4         0               0               6               => ACCEPT
Пакет 7          1.1.1.1         10.0.9.1        0               0               6               => DROP
Пакет 8          10.0.5.32       1.1.1.1         0               0               17              => ACCEPT
```