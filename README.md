# TrabalhoIC1-NetFlix


PROJETO FINAL DA DISCIPLINA IC-1
EVANDRO E. S. RUIZ
Objetivo: Este projeto tem como objetivo fixar o conteu ́do recebido sobre introdu ̧ca ̃o `a programa ̧ca ̃o al ́em do conteu ́do praticado sobre a linguagem C de programa ̧ca ̃o de compu- tadores.
Observa ̧c ̃ao: Ressalto que esta proposta de trabalho pode envolver alguns conhecimentos da linguagem de programa ̧ca ̃o C que na ̃o foram cobertos pelos exemplos ou pelos exerc ́ıcios realizados em aula, no entanto, estes conhecimentos esta ̃o dispon ́ıveis nos livros referenci- ados como livros de apoio na ementa da disciplina.
Enunciado
Esta dispon ́ıvel no ambiente edisciplinas.usp.br um arquivo contendo mil v ́ıdeos recomendados pela Netflix. O arquivo esta ́ nomeado como netflix all.csv. Cada linha deste arquivo corresponde a um t ́ıtulo de v ́ıdeo disponibilizado aos assinantes da Netflix. Cada linha deste arquivo, ou seja, cada registro, cont ́em os seguintes campos:
• title, ou seja, o t ́ıtulo do v ́ıdeo;
• rating, a faixa eta ́ria sugerida;
• ratingLevel, descri ̧ca ̃o sobre a restri ̧c ̃ao da faixa eta ́ria; • ratingDescription, faixa eta ́ria numa escala num ́erica; • release year, ano de lan ̧camento do v ́ıdeo;
• user rating score, nota dos usua ́rios; e
• user rating size, tamanho da amostra das notas.
Solicita-se para este trabalho elaborar um programa escrito em linguagem C que fa ̧ca as seguintes tarefas:
(1) Leia todos os dados do arquivo netflix all.csv e armazene-os na memo ́ria princi- pal usando uma estrutura de dados fundamentada em registros, ou seja, em struct (10);
(2) Elabore, ano a ano, a totaliza ̧ca ̃o de v ́ıdeos para cada um dos poss ́ıveis rating, por exemplo (10):
          Ano;  G;  NR;  PG;...
          2016; 35; 124; 60;...
          2015;35...
(3) O programa deve permitir ao usua ́rio mostrar quantos v ́ıdeos foram lan ̧cados pela Netflix a cada ano, segundo este arquivo fornecido (10);
5954001 Introdu ̧c ̃ao `a Computac ̧ ̃ao I, FFCLRP–USP.
1
   
2
EVANDRO E. S. RUIZ
(4) (5)
(6)
Baseado no campo user rating score, o programa deve gerar um arquivo contendo, para cada ano, os 10 v ́ıdeos mais apreciados pelos usu ́arios (20);
O programa deve mostrar tamb ́em quantos v ́ıdeos reconhecidos como violente exis- tem, segundo o campo ratingDescription. Fa ̧ca uma contagem semelhante para sexual content. Calcule a porcentagem dos v ́ıdeos nestas categorias (25); e, por fim; O programa deve poder mostrar os t ́ıtulos de v ́ıdeos que contenham uma palavra chave entrada pela usu ́ario. Mostre os t ́ıtulos com indica ̧ca ̃o de faixa eta ́ria e a descri ̧ca ̃o desta faixa (ratingDescription) (25).
A cada uma destas tarefas ser ́a creditada uma quantidade de pontos, como mostrada ao final de cada tarefa.
Datas, observac ̧o ̃es e demais comenta ́rios
• Um mesmo trabalho podera ́ ser feito por at ́e 2 estudantes matriculados na disci- plina;
• O co ́digo fonte (nome a escolher.c) deve conter, nas suas primeiras linhas, um campo de comenta ́rio com o nome e o nu ́mero USP dos respons ́aveis pelo trabalho;
• O co ́digo fonte deve conter ao menos trˆes fun ̧co ̃es al ́em da fun ̧ca ̃o principal (main());
• Na ̃o sera ̃o aceitos co ́digos em C++ ou outra linguagem de programa ̧ca ̃o;
• O trabalho dever ́a ser entregue at ́e a`s 23h59 do dia 25 de junho de 2019, via email, para o seguinte endere ̧co: evandro@usp.br. O email deve ter o seguinte cabe ̧calho: ‘IC-1 Trabalho final’. E ́ importante colocar o texto correto no cabe ̧calho pois um filtro automatizado colhera ́ todos estes trabalhos. Os trabalhos na ̃o coletados pelo
filtro n ̃ao sera ̃o considerados;
• Trabalhos reconhecidos como ‘muito semelhantes’ pela sua estrutura de programa ̧ca ̃o
sera ̃o desconsiderados. Lembrem-se, varia ́veis com nomes difrentes mas em c ́odigos
com a mesma estrutura s ̃ao considerados ‘muito semelhantes’;
• No dia 25 de junho, terc ̧a-feira, entre 10 e 12h, no lab. 600, todos os estudantes sera ̃o submetidos a um ra ́pido exerc ́ıcio de avaliac ̧ ̃ao, semelhante a uma das tarefas deste trabalho, como forma de mostrar a sua efetiva participac ̧ ̃ao na elabora ̧c ̃ao do
programa;
• O arquivo netflix all.csv esta ́ no formato CSV, ou seja, Comma-separated va-
lues, arquivo texto com os campos separados pelo s ́ımbolo ‘;’;
• O arquivo est ́a codificado em UTF-8 e existem t ́ıtulos com caracteres acentuados da nossa l ́ıngua. O programador esta ́ livre para considerar ou na ̃o estes campos
acentuados escritos em UTF-8;
• Existem registros (linhas) em que nem todos os campos esta ̃o presentes. A falta
de campos pode ser notada por dois sinais ‘;’ consequentes ou por um ‘NA’ (not available ).
Bom trabalho!
Departamento de Computac ̧a ̃o e Matema ́tica, Faculdade de Filosofia, Cieˆncias e Letras de Ribeira ̃o Preto, Universidade de Sa ̃o Paulo – USP
E-mail address: evandro@usp.br
