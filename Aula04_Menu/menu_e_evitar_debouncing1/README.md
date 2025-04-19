# Projeto Arduino: Menu Interativo com LCD e Controle de LEDs

Este projeto implementa um **menu interativo usando um display LCD 16x2**, controlado por três botões (subir, descer, selecionar), e permite o controle de **quatro LEDs** de diferentes cores conectados aos pinos analógicos do Arduino. O menu possui opções para acionar LEDs e acessar submenus com mais ações.

---

## 📸 Imagem do Circuito

![!\[> !\\[Circuito Montado\\](./104521f6-1da5-468c-be70-a5cdb4309f21.png)\](<Aula04_Menu/menu_e_evitar_debouncing1/MENU e EVITAR DEBOUNCING.png>)](<MENU e EVITAR DEBOUNCING.png>)

---

## ⚙️ Materiais Utilizados

| Quantidade | Componente              |
|------------|--------------------------|
| 1          | Arduino UNO              |
| 1          | Display LCD 16x2 (com ou sem I2C) |
| 1          | Protoboard               |
| 4          | LEDs (amarelo, azul, vermelho, verde) |
| 4          | Resistores 220Ω          |
| 3          | Botões push-button       |
| Cabos jumper | Macho-Macho             |

---

## 🔌 Ligações

### Display LCD (modo paralelo):

| LCD Pin | Arduino Pin |
|---------|-------------|
| RS      | 12          |
| EN      | 11          |
| D4      | 5           |
| D5      | 4           |
| D6      | 3           |
| D7      | 2           |

### Botões:

| Função        | Pino Arduino |
|---------------|--------------|
| Botão Cima    | 9            |
| Botão Baixo   | 10           |
| Botão Seleciona | 8          |

Todos os botões devem ser ligados com resistores pull-up (internos ativados com `INPUT_PULLUP`).

### LEDs:

| Cor     | Pino Arduino |
|---------|--------------|
| Amarelo | A5           |
| Azul    | A4           |
| Vermelho| A3           |
| Verde   | A2           |

---

## 📋 Funcionamento

- O menu é exibido no LCD e navegado com os botões:
  - 🔼 **Cima (9)**: Move o menu para cima
  - 🔽 **Baixo (10)**: Move o menu para baixo
  - ✅ **Seleciona (8)**: Executa a ação do item atual

- Opções do menu:
  1. **LED Amarelo**: Liga/Desliga
  2. **LED Azul**: Acessa submenu e aciona LED azul
  3. **LED Vermelho**: Acessa submenu e aciona LED vermelho
  4. **LED Verde**: Inicia ou para o piscar do LED verde

---

## Lógica do Código

- Usa biblioteca `LiquidCrystal` para controle do LCD.
- Utiliza `INPUT_PULLUP` nos botões.
- Armazena o estado do menu com a variável `menu`.
- Controla o piscar do LED verde com a variável `LedVerdePisca`.

---

## 📂 Estrutura do Código

- `AtualizaMenu()`: Atualiza o display LCD de acordo com o item selecionado.
- `ExecutaAcao()`: Executa a ação correspondente ao item do menu.
- `acaoX()`: Funções específicas para cada item.

---
## link do circuito no Tinker Cad

a Montagem do circuito se encontra em :

[link](https://www.tinkercad.com/things/1c1Ap8sG8VR-fantastic-jaagub/editel?returnTo=https%3A%2F%2Fwww.tinkercad.com%2Fdashboard)
