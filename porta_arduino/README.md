# 🔐 Porta de Segurança com Arduino

Projeto de uma porta de segurança com teclado matricial e verificação de senha. Quando a senha correta é digitada, o sistema permite a abertura da porta por 6 segundos, sinalizando com LED verde e som. Se a senha estiver incorreta, o sistema alerta com LED vermelho e som.

---

## ✨ Funcionalidades

- Validação de senha pré-definida: `0000`
- Tecla `#` para confirmação da senha
- Feedback visual e sonoro:
  - LED verde + buzzer: senha correta
  - LED vermelho + buzzer: senha incorreta
- Servo motor aciona abertura da porta por 6 segundos
- Exibição das mensagens no display LCD 16x2 com I2C
- Registrando o Horário e o Dia de acesso à porta

---

## 🔧 Componentes Utilizados

| Componente                  | Quantidade |
|-----------------------------|------------|
| Arduino Uno                 | 1          |
| LCD 16x2 com I2C            | 1          |
| Teclado Matricial 4x4 ou 4x5| 1          |
| Servo Motor (5V)            | 1          |
| LED Verde                   | 1          |
| LED Vermelho                | 1          |
| Resistores 220Ω             | 2          |
| Protoboard                  | 1          |
| Jumpers                     | diversos   |

---

## 🔌 Esquema de Ligações

- **LCD I2C**: SDA → A4, SCL → A5
- **Keypad**: 
  - Colunas (C1 → D4, C2 → D3, C3 → D2)
  - Linhas (R1 → D8, R2 → D7, R3 → D6, R4 → D5)
- **Servo Motor**: pino digital (D9)
- **LED Verde**: pino digital (D10)
- **LED Vermelho**: pino digital (D11)
- **Buzzer (opcional)**: pino digital (D12)

> 📌 Os pinos podem ser personalizados conforme seu código. Certifique-se de atualizar o sketch do Arduino com os pinos corretos.

---

## 💻 Bibliotecas Necessárias

Instale as seguintes bibliotecas na IDE Arduino:

- [`Keypad`](https://playground.arduino.cc/Code/Keypad/)
- [`LiquidCrystal_I2C`](https://github.com/johnrickman/LiquidCrystal_I2C)
- `Servo`

Você pode instalar diretamente pelo **Gerenciador de Bibliotecas** da Arduino IDE.

---

## 🚀 Como Usar

1. Monte o circuito conforme o esquema.
2. Carregue o código no Arduino via USB.
3. No LCD, será exibido o status inicial.
4. Digite a senha `0000` e pressione `#`.
   - Se correta:
     - LED verde pisca
     - Buzzer emite som breve
     - Porta abre por 6 segundos (servo gira)
   - Se incorreta:
     - LED vermelho acende
     - Alarme sonoro é emitido

---

## 📌 Observações

- Este projeto é ideal para fins educativos, prototipagem e estudos sobre segurança e automação.
- Pode ser expandido com sensores de presença, autenticação biométrica, controle via aplicativo, entre outras ideias.

---

## 🧠 Colaboradores

<table>
  <tr>
    <td align="center">
      <a href="https://github.com/ValterBeff">
        <img src="https://github.com/ValterBeff.png" width="100px;" alt="Foto de Valter Beff"/><br />
        <sub><b>Valter Beff</b></sub>
      </a><br />
      Desenvolvedor
    </td>
    ## 🧠 Colaboradores

<table>
  <tr>
    <td align="center">
      <a href="https://github.com/ValterBeff">
        <img src="https://github.com/ValterBeff.png" width="100px;" alt="Foto de Valter Beff"/><br />
        <sub><b>Valter Beff</b></sub>
      </a><br />
      Desenvolvedor
    </td>
    <td align="center">
      <a href="https://github.com/diegoalbuquerquevj">
        <img src="https://github.com/diegoalbuquerquevj.png" width="100px;" alt="Foto de Diego Albuquerque"/><br />
        <sub><b>Diego Albuquerque</b></sub>
      </a><br />
      Infraestrutura
    </td>
  </tr>
</table>

  </tr>
</table>
