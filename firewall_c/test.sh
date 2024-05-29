#!/bin/bash

# Сборка файрвола
make firewall

# Путь к файлу с тестовыми статическими данными пакетами
TEST_FILE="test_packets_c.txt"

# Путь к файлу с тестовыми динамическими данными пакетами
# TEST_FILE="test_dinamic_packets_c.txt"

# Счетчик пакетов
packet_count=1

# Функция для форматирования вывода
format_output() {
    local packet="$1"
    local action="$2"
    IFS=' ' read -ra packet_parts <<< "$packet"
    
    # Форматирование каждого блока в пакете
    printf "Пакет %-10s %-15s %-15s %-15s %-15s %-15s => %s\n" \
           "$packet_count" "${packet_parts[0]}" "${packet_parts[1]}" \
           "${packet_parts[2]}" "${packet_parts[3]}" "${packet_parts[4]}" "$action"
}

# Вывод шапки таблицы
echo "------------------------------------------------------------------------------------------------------"
printf "%-18s %-15s %-15s %-15s %-15s %-15s =>%s\n" "№packet" "src_ip" "dst_ip" "src_port" "dst_port" "protocol" "action"
echo "------------------------------------------------------------------------------------------------------"

# Чтение и обработка тестовых пакетов
while read -r line; do
    output=$(echo "$line" | ./firewall)
    if [[ "$output" == "ACCEPT" ]]; then
        format_output "$line" "ACCEPT"
    else
        format_output "$line" "DROP"
    fi
    ((packet_count++))
done < "$TEST_FILE"

make clean
