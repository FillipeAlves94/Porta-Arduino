# 🔥 Sensor de Fumaça com Arduino

Projeto de um sistema de alarme com detecção de fumaça/gás utilizando o sensor **MQ2**. Ao detectar a presença de fumaça ou gases inflamáveis, o sistema emite **alertas visuais (LEDs)** e **sonoros (buzzer)**, servindo como aviso preventivo em ambientes domésticos, escolares ou laboratoriais. Além disso, LEDs vermelhos são utilizados para indicar a direção de saída ou rota segura.

---

## ✨ Funcionalidades

- Detecção de fumaça/gás inflamável com o sensor MQ2
- Alerta sonoro com buzzer
- LED amarelo acende junto com o buzzer para indicar alerta de risco
- LED vermelho indica caminho seguro ou saída de emergência
- Sistema simples, ideal para projetos educacionais e protótipos

---

## 🔧 Componentes Utilizados

| Componente         | Quantidade |
|--------------------|------------|
| Arduino UNO        | 1          |
| Sensor de Gás MQ2  | 1          |
| LED Vermelho       | 5          |
| LED Amarelo        | 2          |
| Buzzer (ativo)     | 1          |
| Botão              | 1          |
| Resistores 220Ω    | 9          |
| Protoboard         | 1          |
| Jumpers            | Diversos   |

---

## 🔌 Esquema de Ligações

- **MQ2**:  
  - VCC → 5V  
  - GND → GND  
  - AOUT → A0

- **LED Amarelo**: D11  
- **LED Vermelho**: D12  
- **Buzzer**: D10

> 📌 Os pinos podem ser alterados conforme o seu código. Certifique-se de manter consistência entre o circuito e o sketch Arduino.

---

## 💻 Bibliotecas Necessárias

Nenhuma biblioteca externa é necessária. O código usa apenas funções nativas da IDE Arduino.

---

## 🚀 Como Usar

1. Monte o circuito conforme o esquema de ligação.
2. Conecte o Arduino ao computador via USB.
3. Carregue o código `sensor_fumaca.ino` para o Arduino usando a IDE.
4. Após energizar o sistema:
   - O sistema entra em estado de monitoramento.
   - Se o sensor detectar fumaça ou gás:
     - O LED amarelo acende
     - O buzzer emite som de alerta
   - Os LEDs vermelhos permanecem acesos para indicar rotas seguras de saída.

---

## 📌 Observações

- O sensor MQ2 precisa de um tempo de **pré-aquecimento (~20 segundos)** para funcionar corretamente.
- A sensibilidade pode ser ajustada manualmente pelo trimpot azul do sensor.
- Projeto ideal para prototipagem rápida, podendo ser expandido com:
  - LCD para exibir mensagens
  - Módulos Wi-Fi (ESP8266/ESP32) para envio de alertas
  - Monitoramento remoto com IoT

---

## 🧠 Colaboradores

<table>
  <tr>
    <td align="center">
      <a href="https://github.com/FillipeAlves94">
        <img src="https://github.com/FillipeAlves94.png" width="100px;" alt="Foto de Fillipe Alves"/><br />
        <sub><b>Fillipe Alves</b></sub>
      </a><br />
      Desenvolvedor
    </td>
    <td align="center">
      <a href="https://github.com/ValterBeff">
        <img src="https://github.com/ValterBeff.png" width="100px;" alt="Foto de Valter Beff"/><br />
        <sub><b>Valter Beff</b></sub>
      </a><br />
      Desenvolvedor
    </td>
  </tr>
</table>
