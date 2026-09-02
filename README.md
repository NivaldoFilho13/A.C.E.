# A CUBE EXPERT

Hardware embarcado para montar (resolver) automaticamente um cubo mágico, usando um sistema embarcado em C++.

## Visão geral

O CUBE EXPERT é um robô controlado por um microcontrolador **ESP32**, capaz de:

1. Ler o estado atual do cubo (cores de cada face)
2. Calcular a sequência de movimentos necessária para resolvê-lo
3. Acionar 6 atuadores (um por face) para executar os movimentos fisicamente

Todo o firmware é escrito em **C++**, rodando diretamente no microcontrolador (sem depender de um PC durante a resolução).

## Arquitetura

```
                    ┌──────────────────┐
                    │ Fonte de energia │
                    └────────┬─────────┘
                             │
                    ┌────────▼────────────┐
                    │    ESP32-WROOM-32   │
                    │(controlador central)│
                    └───┬───────────┬─────┘
             ┌──────────┘           └──────────┐
    ┌────────▼─────│───┐            ┌───────────▼────────┐
    │  Drivers/Servos  │            │  Sensores de cor   │
    │ (6x, um por face)│            │    (6x TCS3200)    │
    └────────┬─────────┘            └──────────┬─────────┘
             │                                 │
    ┌────────▼─────────────┐                   │
    │  Estrutura mecânica  │ ◄─────────────────┘
    │  + cubo mágico       │
    └──────────────────────┘
```

## Hardware

### Controle central
- ESP32-WROOM-32 (dual-core, WiFi/BLE, GPIO suficiente)

### Atuação (mover as faces)
- 6x Servo motor MG996R (ou, na versão de maior precisão, 6x NEMA17 + driver A4988/TMC2208)

### Leitura do estado do cubo
- 6x Sensor de cor TCS3200 (um por face)
- Alternativa: câmera ESP32-CAM + visão computacional

### Alimentação
- Fonte chaveada 5V/6V (versão servo) ou 12V (versão stepper)
- Regulador de tensão conforme necessário

### Estrutura mecânica
- Chassi impresso em 3D (PLA/PETG)
- Rolamentos 608ZZ + parafusos M3
- Cubo mágico com mecanismo solto (tipo speedcube)

Ver o BOM completo (lista de materiais com preços) na seção abaixo.

## BOM — versão mais barata e funcional

| Componente | Modelo | Qtd | Preço estimado |
|---|---|---|---|
| Microcontrolador | ESP32-WROOM-32 DevKit | 1 | R$ 42,00 |
| Atuador de face | Servo MG996R | 6 | R$ 168,00 |
| Leitura de cor | Sensor TCS3200 | 6 | R$ 108,00 |
| Alimentação | Fonte chaveada 5V/6V 3A | 1 | R$ 30,00 |
| Estrutura | Filamento PLA (~250g) | 1 | R$ 25,00 |
| Mecânica | Rolamentos 608ZZ + parafusos M3 | 1 | R$ 30,00 |
| Cubo | Speedcube básico | 1 | R$ 45,00 |
| Fiação | Jumpers + protoboard | 1 | R$ 20,00 |
| Cabo | USB micro-USB | 1 | R$ 10,00 |
| **Total** | | | **R$ 478,00** |

> Valores de mercado (Brasil), sujeitos a variação por vendedor e frete.

## Firmware

- Linguagem: **C++**
- Ambiente sugerido: Arduino IDE ou PlatformIO
- Módulos principais planejados:
  - `leitura_cubo.cpp` — captura o estado das faces via sensores de cor
  - `resolver.cpp` — algoritmo de resolução (ex: Kociemba)
  - `controle_motores.cpp` — traduz a sequência de movimentos em comandos para os servos/motores
  - `main.cpp` — orquestra o fluxo: ler → resolver → executar

## Status do projeto

Em desenvolvimento — definição de hardware e arquitetura inicial concluídas.

## Próximos passos

- [ ] Montar protótipo mecânico
- [ ] Implementar leitura de cor por face
- [ ] Implementar algoritmo de resolução em C++
- [ ] Implementar controle dos atuadores
- [ ] Testes de integração completa
