// Buffer para armazenar caracteres da porta serial e testar mensagem  - Prof. Dr. Dalton Vidor

# define S01  8
# define S02  9
String Palavra;

void setup() {
    Serial.begin(9600);
    Serial.println("Bluethoot Conectado");
    pinMode(S01, OUTPUT);  
    pinMode(S02, OUTPUT); 
}

void loop() {
    while (Serial.available() > 0)
    {
        char char_recebido = Serial.read();
        
        Serial.println(char_recebido);
        
        if (char_recebido == ';')                             // encerramento do envio com um ponto e vírgula daí passa a processar a palavra recebida
        {
                                                              // somente durante os testes usei esta parte
            //Serial.print("Palavra recebida = ");
            //Serial.println(Palavra);

                                                              // Teste se as palavras correspindem a comandos
            if(Palavra == "liga 01"){                         // teste do liga 01
              digitalWrite(S01, HIGH);
              delay(5000);                                    // espera o celular falar que enviou
              Serial.println("liga 01 executado");
            }   
            if(Palavra == "desliga 01"){                         // teste do desliga 01
              digitalWrite(S01, LOW);
              delay(5000);                                    // espera o celular falar que enviou
              Serial.println("desliga 01 executado");
            } 
            if(Palavra == "liga 02"){                         // teste do liga 02
              digitalWrite(S02, HIGH);
              delay(5000);                                    // espera o celular falar que enviou
              Serial.println("liga 02 executado");
            }   
            if(Palavra == "desliga 02"){                         // teste do desliga 02
              digitalWrite(S02, LOW);
              delay(5000);                                    // espera o celular falar que enviou
              Serial.println("desliga 02 executado");
            }
        }

        Palavra += char_recebido;                             // acrecenta na palavra os caracteres recebidos
        
        if (char_recebido == ';')                             // encerramento do envio com um ponto e vírgula - tem que limpar o ponto e vírgula também
        {
          Palavra = ""; // limpa a variável palavra
        }
    }
}
