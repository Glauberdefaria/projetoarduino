/************************Professor Marlon Nardi**************************
Autor: Marlon Nardi Walendorff
Adaptado por Glauber
Projeto: Alarme a Laser com Arduino
Blog: http://professormarlonnardi.blogspot.com.br/
Youtube: https://www.youtube.com/user/Marlon7642
Facebook: https://www.facebook.com/professormarlonnardi
************************************************************************/
// ------------------------------------------------------- Entradas Analógicas ----------------------------------------------------------- //
#define SensorLDR A0 // Diz para o compilador (IDE do arduino) que SersorLDR e A0 são a mesma coisa.
#define Ajuste A1

// -------------------------------------------------------- Saídas Digitais -------------------------------------------------------------- //
#define Sirene 13
#define LedAjustado 12
#define LedAtivado 11

// -------------------------------------------------------- Entradas Digitais ------------------------------------------------------------ //
#define BotaoAtivaOuDesativa 10

// ---------------------- Valor da Constante de Diferença de Iluminação do LDR com Laser e Sem Laser ------------------------------------- //
#define ConstanteDB 100


// ------------------------------------------------- Definições de Variáveis Globais ----------------------------------------------------- //
unsigned int ValorAjuste = 0;
unsigned int ValorSensorLDR = 0;
unsigned int AcionaSireneEMantem = 0;
unsigned int CONTA = 0;
unsigned int PARA = 0;


void setup() {
  // coloque aqui se código que será executado somente uma vez:
  // ------------------------------------------------------ Declaração das saídas ---------------------------------------------------------- //
  pinMode(Sirene, OUTPUT);// Define o pino da Sirene como saída.
  pinMode(LedAjustado, OUTPUT);// Define o pino do Led de ajuste como saída.
  pinMode(LedAtivado, OUTPUT);// Define o pino do Led de ativado como saída.

  // ------------------------------------------------------ Declaração da entrada ---------------------------------------------------------- //
  pinMode(BotaoAtivaOuDesativa, INPUT);// Define o pino do botão de ativar ou desativar como entrada.

  // ------------------------------------------------------- Comunicação Serial ------------=----------------------------------------------- //
  Serial.begin(9600);// Inicia a comunicação serial com velocidade de 9600 bits por segundo.

}

void loop() {
  // coloque aqui se código que será executado repetidamente:

  ValorSensorLDR =  analogRead(A0);// Joga os valores da leitura analógica do pino A0 (de 0 à 1023) para a variável ValorSensorLDR.
  ValorAjuste =  analogRead(A1);// Joga os valores da leitura analógica do pino A1 (de 0 à 1023) para a variável ValorAjuste.

  Serial.print("Valor do LDR: ");// Escreve no monitor serial o texto "Valor do LDR: ".
  Serial.print(ValorSensorLDR);// Escreve no monitor serial o valor da variável ValorSensorLDR.
  Serial.print("   Valor do Ajuste: ");// Escreve no monitor serial o texto "   Valor do Ajuste: ".
  Serial.print(ValorAjuste);// Escreve no monitor serial o valor da variável ValorAjuste.
  Serial.print("   Valor de Conta: ");// Escreve no monitor serial o texto "   Valor de Conta: ".
  Serial.println(CONTA);// Escreve no monitor serial o valor da variável CONTA e pula linha.



  // ---------------------------------------------------------- Ativa/Desativa o Alarme -------------------------------------------------------------------- //

  if (digitalRead(BotaoAtivaOuDesativa) == HIGH && PARA == 0) { // Se o botão Botão Ativa Ou Desativa estiver precionado e para estive igual a 0.
    PARA = 1;// A variável PARA vai para o valor 1.
  }

  if (digitalRead(BotaoAtivaOuDesativa) == LOW && PARA == 1) { // Se o botão Botão Ativa Ou Desativa estiver solto e para estive igual a 1.
    CONTA++;// A variável CONTA soma 1, ou seja, sai de 0 e vai para 1.
    PARA = 0;// A variável PARA vai para o valor 0.
  }


  if (CONTA == 0) { // Se a variável CONTA estiver com o valor 0.

    digitalWrite(LedAtivado, LOW);// Desliga o LED Ativado.
    AcionaSireneEMantem = 0;// A variável AcionaSireneEMantem vai para o valor 0.
  }



  if (CONTA == 1) { // Se a variável CONTA estiver com o valor 1.
    digitalWrite(LedAtivado, HIGH);// Liga o LED Ativado.
  }


  if (CONTA == 2) { // Se a variável CONTA estiver com o valor 2.

    CONTA = 0;// A variável CONTA vai para o valor 0.
  }


  if (ValorAjuste + ConstanteDB >= ValorSensorLDR  && CONTA == 1 ) { // Se o valor do ajuste mais a variável ConstanteDB for maior e igual ao valor da variável ValorSensorLDR e o valor de CONTA estiver para 1 (ou seja, o alarme está ligado).
    digitalWrite(LedAjustado, HIGH);// Liga o LED Ajustado.
  } else {

    digitalWrite(LedAjustado, LOW);// Desliga o LED Ajustado.
  }



  if (ValorSensorLDR <= ValorAjuste && CONTA == 1) { // Se o valor do ValorSensorLDR for menor e igual ao valor da variável ValorAjuste e o valor de CONTA estiver para 1 (ou seja, o alarme está ligado).
    AcionaSireneEMantem = 1;// A variável AcionaSireneEMantem vai para o valor 1.

  }

  if (AcionaSireneEMantem == 0 ) {// Se o valor da variável AcionaSireneEMantem for igual a 0.

    digitalWrite(Sirene, LOW);// Desliga a sirene.
  }


  if (AcionaSireneEMantem == 1 ) {// Se o valor da variável AcionaSireneEMantem for igual a 1.

    digitalWrite(Sirene, HIGH);// Liga a sirene.
  }




}
