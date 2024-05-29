#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <time.h>

typedef struct {
    char src_ip[16];
    char dst_ip[16];
    uint16_t src_port;
    uint16_t dst_port;
    uint8_t protocol;
} packet_t;

void generate_random_packets(int num_packets) {
    FILE* fp = fopen("test_dinamic_packets_c.txt", "w");
    if (!fp) {
        printf("Error opening file.\n");
        return;
    }

    srand(time(NULL));

    for (int i = 0; i < num_packets; i++) {
        packet_t packet;
        snprintf(packet.src_ip, 16, "%d.%d.%d.%d",
                 rand() % 256, rand() % 256, rand() % 256, rand() % 256);
        snprintf(packet.dst_ip, 16, "%d.%d.%d.%d",
                 rand() % 256, rand() % 256, rand() % 256, rand() % 256);
        packet.src_port = rand() % 65536;
        packet.dst_port = rand() % 65536;
        packet.protocol = rand() % 256;

        fprintf(fp, "%s %s %hu %hu %hhu\n",
                packet.src_ip, packet.dst_ip, packet.src_port, packet.dst_port, packet.protocol);
    }

    fclose(fp);
}

int main() {
    generate_random_packets(1000);
    return 0;
}
