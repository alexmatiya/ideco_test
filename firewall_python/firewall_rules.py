rules = [
    {"src_ip": "10.0.1.11", "dst_ip": "1.1.1.1", "src_port": 0, "dst_port": 0, "protocol": 6, "action": "ACCEPT"},
    {"src_ip": "10.0.2.12", "dst_ip": "1.1.1.1", "src_port": 0, "dst_port": 0, "protocol": 6, "action": "DROP"},
    {"src_ip": "10.0.2.12", "dst_ip": "8.8.8.8", "src_port": 0, "dst_port": 0, "protocol": 6, "action": "ACCEPT"},
    {"src_ip": "10.0.3.13", "dst_ip": "0.0.0.0", "src_port": 0, "dst_port": 0, "protocol": 0, "action": "ACCEPT"},
    {"src_ip": "0.0.0.0", "dst_ip": "1.2.3.4", "src_port": 0, "dst_port": 0, "protocol": 17, "action": "DROP"},
    {"src_ip": "0.0.0.0", "dst_ip": "1.2.3.4", "src_port": 0, "dst_port": 0, "protocol": 0, "action": "ACCEPT"},
    {"src_ip": "0.0.0.0", "dst_ip": "10.0.9.1", "src_port": 0, "dst_port": 0, "protocol": 6, "action": "DROP"},
    {"src_ip": "10.0.5.0/24", "dst_ip": "0.0.0.0", "src_port": 0, "dst_port": 0, "protocol": 0, "action": "ACCEPT"}
]
