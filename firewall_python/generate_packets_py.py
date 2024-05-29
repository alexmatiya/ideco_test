import random

def generate_random_packets(num_packets):
    with open("test_dinamic_packets_py.txt", "w") as f:
        for _ in range(num_packets):
            src_ip = f"{random.randint(0, 255)}.{random.randint(0, 255)}.{random.randint(0, 255)}.{random.randint(0, 255)}"
            dst_ip = f"{random.randint(0, 255)}.{random.randint(0, 255)}.{random.randint(0, 255)}.{random.randint(0, 255)}"
            src_port = random.randint(0, 65535)
            dst_port = random.randint(0, 65535)
            protocol = random.randint(0, 255)
            f.write(f"{src_ip} {dst_ip} {src_port} {dst_port} {protocol}\n")

if __name__ == "__main__":
    generate_random_packets(1000)
