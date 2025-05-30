#!/bin/bash
set -e

rm -rf build
mkdir build
cd build
cmake ..
cmake --build .

# If no arguments, run two predefined test cases
if [ $# -eq 0 ]; then
    echo "Teste: Criando tabela hash com 11 posições"
    ./main criar 11 hash

    echo "Teste: Inserindo dados de vários alunos"
./main inserir hash "15489730,Thales Vasconcelos Aguiar de Oliveira,Computação,\
41923202,Rosa Oliveira Pinto da Silva,Civil,\
41923202,Rosemar da Silva,Materiais,\
123456789,Pudim de Passas,Petróleo,\
23456789,Olimar,Gastronomia,\
34567890,Jubileu,Standup,\
12039232,Silmar,Filosofia,\
32932123,Rilmar,Filologia,\
38239242,Rola,Prostituição,\
93223129,Rodo,Mestrado,\
39220392,Rei da Cocada,Leiteiro,\
84320123,Clarisse Fernandes,Matemática,\
74219300,Jonas Mota,Engenharia Elétrica,\
62319832,Priscila Torres,Direito,\
51928371,Rubens da Mata,Arquitetura,\
47539210,Daniela Sousa,Medicina,\
39872192,Victor Hugo,Engenharia Mecânica,\
32019283,Suelen Rocha,Biomedicina,\
29837465,Aurélio Lima,Geografia,\
27483920,Helena Pires,Artes Cênicas,\
26192837,Bernardo Lima,Teatro,\
23981293,Yasmin Pereira,Ciências Sociais,\
22938475,Murilo Costa,Letras,\
21394827,Sabrina Martins,Biblioteconomia,\
20293847,André Luiz,História,\
19823746,Fernanda Ribeiro,Enfermagem,\
18273645,Caio Silva,Zootecnia,\
17364528,Marina Duarte,Engenharia de Produção,\
16473829,Igor Gonçalves,Nutrição,\
15372849,Luiza Nascimento,Odontologia,\
14738290,Bruno Almeida,Psicologia,\
13572938,Talita Menezes,Física,\
12384756,Diego Fonseca,Administração,\
11238475,Rafaela Souza,Ciências Atuariais,\
10928374,Gustavo Ramos,Química,\
98234756,Juliana Braga,Cinema,\
89237465,Paulo Vitor,Publicidade,\
87326475,Beatriz Simões,Economia,\
82374652,Ricardo Freitas,Geologia,\
79384526,Evelyn Castro,Biotecnologia,\
74382910,Alexandre Cunha,Ciência da Computação,\
70293847,Larissa Faria,Oceanografia"


    echo "Teste: Removendo um aluno"
    ./main remover hash "23456789,34567890"

    echo "Teste: Consultando dados de um aluno"
    ./main buscar hash "15436911,39220392,62319832"

else
    ./main "$@"
fi