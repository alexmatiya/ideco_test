from firewall_utils import check_packet

# Загрузка тестовых пакетов статисческих
FILE = "test_packets_py.txt"
# Загрузка тестовых пакетов динамически сгенерированных
# FILE = "test_dinamic_packets_py.txt"

header = f"\nPacket: {'src_ip':15} {'dst_ip':15} {'src_port':8} {'dst_port':8} {'protocol':5} {'Action'}"
separator = "-" * len(header)

print(separator, header, separator, sep="\n")


# Загрузка тестовых пакетов из файла
with open(FILE, 'r') as f:
    for line in f:
        fields = line.strip().split()
        src_ip = fields[0]
        dst_ip = fields[1]
        src_port = int(fields[2])
        dst_port = int(fields[3])
        protocol = int(fields[4])

        action = check_packet(src_ip, dst_ip, src_port, dst_port, protocol)
        print(f"Packet: {src_ip:15} {dst_ip:15} {src_port:8} {dst_port:8} {protocol:5} {action}")
