#include <iostream>
#include <string>
#include <cctype>

bool validarCartaoCredito(const std::string& numeroCartao) {
    
    std::string numero;
    for (char c : numeroCartao) {
        if (!isspace(c)) {
            if (!isdigit(c)) {
                return false;  // Contém caracteres não numéricos
            }
            numero += c;
        }
    }
    
    // Verificar se o comprimento é válido (13-19 dígitos para cartões mais comuns)
    if (numero.length() < 13 || numero.length() > 19) {
        return false;
    }
    
    // Algoritmo de Luhn (mod 10):
    // 1. A partir do último dígito e indo para a esquerda, dobre o valor de cada segundo dígito
    // 2. Some todos os dígitos (dígitos individuais se o valor dobrado > 9)
    // 3. Se a soma total for divisível por 10, o número é válido
    
    int soma = 0;
    bool alternar = false;
    
    for (int i = numero.length() - 1; i >= 0; i--) {
        int digito = numero[i] - '0';
        
        if (alternar) {
            digito *= 2;
            if (digito > 9) {
                digito = digito - 9;  // Equivalente a somar os dígitos (ex: 16 -> 1+6 = 7, que é o mesmo que 16-9)
            }
        }
        
        soma += digito;
        alternar = !alternar;
    }
    
    // Se a soma for divisível por 10, o cartão é válido
    return (soma % 10 == 0);
}

// Função que identifica a bandeira do cartão com base no prefixo e comprimento
std::string identificarBandeira(const std::string& numeroCartao) {
    // Remover espaços
    std::string numero;
    for (char c : numeroCartao) {
        if (!isspace(c)) {
            numero += c;
        }
    }
    
    // Verificar prefixo e comprimento para identificar a bandeira
    // Visa: começa com 4, 13 ou 16 dígitos
    if (numero[0] == '4' && (numero.length() == 13 || numero.length() == 16)) {
        return "Visa";
    }
    
    // MasterCard: começa com 51-55 ou 2221-2720, 16 dígitos
    if (numero.length() == 16) {
        int prefix2 = std::stoi(numero.substr(0, 2));
        if (prefix2 >= 51 && prefix2 <= 55) {
            return "MasterCard";
        }
        
        int prefix4 = std::stoi(numero.substr(0, 4));
        if (prefix4 >= 2221 && prefix4 <= 2720) {
            return "MasterCard";
        }
    }
    
    // American Express: começa com 34 ou 37, 15 dígitos
    if (numero.length() == 15) {
        int prefix2 = std::stoi(numero.substr(0, 2));
        if (prefix2 == 34 || prefix2 == 37) {
            return "American Express";
        }
    }
    
    // Discover: começa com 6011, 622126-622925, 644-649 ou 65, 16-19 dígitos
    if (numero.length() >= 16 && numero.length() <= 19) {
        if (numero.substr(0, 4) == "6011" || 
            (numero.substr(0, 2) == "65") ||
            (numero.substr(0, 3) >= "644" && numero.substr(0, 3) <= "649")) {
            return "Discover";
        }
        
        int prefix6 = 0;
        try {
            prefix6 = std::stoi(numero.substr(0, 6));
            if (prefix6 >= 622126 && prefix6 <= 622925) {
                return "Discover";
            }
        } catch (...) {
            // Caso o número não possa ser convertido, ignora
        }
    }
    
    // JCB: começa com 3528-3589, 16-19 dígitos
    if (numero.length() >= 16 && numero.length() <= 19) {
        int prefix4 = 0;
        try {
            prefix4 = std::stoi(numero.substr(0, 4));
            if (prefix4 >= 3528 && prefix4 <= 3589) {
                return "JCB";
            }
        } catch (...) {
            // Caso o número não possa ser convertido, ignora
        }
    }
    
    return "Desconhecida";
}

int main() {
    std::string numeroCartao;
    
    std::cout << "=== Validador de Cartao de Credito ===" << std::endl;
    std::cout << "Digite o numero do cartao (sem espacos): ";
    std::getline(std::cin, numeroCartao);
    
    if (validarCartaoCredito(numeroCartao)) {
        std::string bandeira = identificarBandeira(numeroCartao);
        std::cout << "Cartao VALIDO!" << std::endl;
        std::cout << "Bandeira: " << bandeira << std::endl;
    } else {
        std::cout << "Cartao INVALIDO!" << std::endl;
    }
    
    return 0;
}