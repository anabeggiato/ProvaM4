# Sistema no Modo Convencional
- Alternância dos Leds como um semaforo (verde -> amarelo -> vermelho)

- Se o Led vermelho estiver acionado e o botão for pressionado, o semaforo fica verde um segundo depois
<img src='./assets/abrir.png' />

Para o acionamento de cada estado do semaforo (aberto, amarelo, fechado), foram definidas as seguintes funções:
<img src='./assets/funcoes.png' />

A implementação dessas funções foi feita da seguinte maneira:
<img src='./assets/convencional.png' />

# Sistema no Modo Noturno
- Led amarelo pisca de 1 em 1 segundo => tempo verificado com a função millis

Para identificar que o ambiente está escuro, verificamos de <code>ldrstatus<=threshold</code>

A implementação do modo noturna ocorreu da sgeuinte maneira:
<img src='./assets/noturno.png' />


**O wokwi não conectou o wifi, como observado na imagem abaixo, então não foi possível verificar o funcionamento dos estados.**

<img src='./assets/wokwi.png' />