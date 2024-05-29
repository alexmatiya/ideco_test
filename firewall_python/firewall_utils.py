import ipaddress
from firewall_rules import rules


def check_packet(src_ip, dst_ip, src_port, dst_port, protocol):
    for rule in rules:
        # Проверка исходного IP-адреса
        src_ip_net = ipaddress.ip_network(rule["src_ip"], strict=False)
        if rule["src_ip"] != "0.0.0.0" and ipaddress.ip_address(src_ip) not in src_ip_net:
            continue

        # Проверка целевого IP-адреса
        dst_ip_net = ipaddress.ip_network(rule["dst_ip"], strict=False)
        if rule["dst_ip"] != "0.0.0.0" and ipaddress.ip_address(dst_ip) not in dst_ip_net:
            continue

        # Проверка портов и протокола
        if all([
            rule["src_port"] == 0 or rule["src_port"] == src_port,
            rule["dst_port"] == 0 or rule["dst_port"] == dst_port,
            rule["protocol"] == 0 or rule["protocol"] == protocol
        ]):
            return rule["action"]

    return "DROP"

