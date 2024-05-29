#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

// Структура для хранения правил файрвола
typedef struct {
    char src_ip[16];
    char dst_ip[16];
    uint16_t src_port;
    uint16_t dst_port;
    uint8_t protocol;
    char action[6];
} firewall_rule_t;

// Правила файрвола
firewall_rule_t firewall_rules[] = {
    {"10.0.1.11", "1.1.1.1", 0, 0, 6, "ACCEPT"},
    {"10.0.2.12", "1.1.1.1", 0, 0, 6, "DROP"},
    {"10.0.2.12", "8.8.8.8", 0, 0, 6, "ACCEPT"},
    {"10.0.3.13", "0.0.0.0", 0, 0, 0, "ACCEPT"},
    {"0.0.0.0", "1.2.3.4", 0, 0, 17, "DROP"},
    {"0.0.0.0", "1.2.3.4", 0, 0, 0, "ACCEPT"},
    {"0.0.0.0", "10.0.9.1", 0, 0, 6, "DROP"},
    {"10.0.5.0/24", "0.0.0.0", 0, 0, 0, "ACCEPT"}
};

int num_firewall_rules = sizeof(firewall_rules) / sizeof(firewall_rule_t);


// Функция для проверки, входит ли IP-адрес в диапазон
int is_ip_in_range(char* ip, char* range) {
    struct in_addr addr, mask;
    char* slash = strchr(range, '/');
    
    if (slash) {
        *slash = '\0';
        inet_pton(AF_INET, range, &addr.s_addr);
        int prefix_len = atoi(slash + 1);
        mask.s_addr = htonl(0xFFFFFFFF << (32 - prefix_len));
        
        struct in_addr pkt_addr;
        inet_pton(AF_INET, ip, &pkt_addr.s_addr);
        
        // Проверяем, попадает ли IP-адрес пакета в диапазон
        return (pkt_addr.s_addr & mask.s_addr) == (addr.s_addr & mask.s_addr);
    } else {
        return strcmp(ip, range) == 0;
    }
}

// Функция для проверки пакета на соответствие правилам файрвола
char* check_packet(char* src_ip, char* dst_ip, uint16_t src_port, uint16_t dst_port, uint8_t protocol) {
    for (int i = 0; i < num_firewall_rules; i++) {
        firewall_rule_t* rule = &firewall_rules[i];
        
        // Проверяем, соответствует ли пакет данному правилу
        if (strchr(rule->src_ip, '/')) {
            if (!is_ip_in_range(src_ip, rule->src_ip)) continue;
        } else if (strcmp(rule->src_ip, "0.0.0.0") != 0 && strcmp(src_ip, rule->src_ip) != 0) {
            continue;
        }
        
        if (strchr(rule->dst_ip, '/')) {
            if (!is_ip_in_range(dst_ip, rule->dst_ip)) continue;
        } else if (strcmp(rule->dst_ip, "0.0.0.0") != 0 && strcmp(dst_ip, rule->dst_ip) != 0) {
            continue;
        }
        
        if (rule->src_port != 0 && src_port != rule->src_port) continue;
        if (rule->dst_port != 0 && dst_port != rule->dst_port) continue;
        if (rule->protocol != 0 && protocol != rule->protocol) continue;
        
        // Если пакет соответствует правилу, возвращаем действие
        return rule->action;
    }
    
    // Если пакет не соответствует ни одному правилу, возвращаем "DROP"
    return "DROP";
}

int main() {
    char src_ip[16], dst_ip[16];
    uint16_t src_port, dst_port;
    uint8_t protocol;
    
    while (scanf("%15s %15s %hu %hu %hhu", src_ip, dst_ip, &src_port, &dst_port, &protocol) == 5) {
        char* action = check_packet(src_ip, dst_ip, src_port, dst_port, protocol);
        printf("%s\n", action);
    }
    
    return 0;
}
