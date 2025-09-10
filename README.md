# 📄 pipex  

> `pipex` é uma implementação em C que simula o funcionamento do operador de **pipe** (`|`) no shell.  
> O programa redireciona a entrada e a saída de múltiplos comandos encadeados, reproduzindo o comportamento do bash em execuções como:  
> ```bash
> < infile cmd1 | cmd2 | ... | cmdn > outfile
> ```  
> Esse projeto aprofunda conceitos de **processos**, **redirecionamento de arquivos**, **duplicação de descritores de arquivo** e **comunicação entre processos** através de **pipes**.

![Banner](https://img.shields.io/badge/Project-pipex-blueviolet) ![C](https://img.shields.io/badge/Language-C-red) ![License](https://img.shields.io/badge/License-MIT-green)

---

## 🎯 Objetivo  

O objetivo do `pipex` é recriar o comportamento do **pipe do shell** (`|`), permitindo a execução de comandos encadeados com redirecionamento de entrada e saída.  

Esse projeto ensina a:  
- Criar e gerenciar **processos filhos** usando `fork`.  
- Executar programas externos com `execve`.  
- Controlar **descritores de arquivos** com `dup` e `dup2`.  
- Implementar a **comunicação entre processos** via `pipe`.  
- Tratar erros de forma robusta (permissões, arquivos inexistentes, comandos inválidos).  
- Entender melhor como o **shell** funciona “por baixo dos panos”.  

---

## 💻 Como usar  

#### 📦 Compilação com Makefile

Para compilar o projeto, basta rodar no terminal:

```bash
make
```
Isso irá compilar todos os arquivos e gerar um executável.

♻️ Outros comandos úteis

`make re` — recompila o projeto do zero (faz fclean e depois all)

`make clean` — remove os arquivos objeto .o

`make fclean` — remove os arquivos objeto e o executável

Execute com os argumentos necessários:

```bash
./pipex infile "cmd1" "cmd2" ... "cmdn" outfile
```
Equivalente a:

```bash
  < infile cmd1 | cmd2 | ... | cmdn > outfile
```
Versão bônus com here_doc:

```bash
./pipex here_doc LIMITER "cmd1" "cmd2" outfile
```
Equivalente a:

```bash
  cmd1 << LIMITER | cmd2 >> outfile
```
O resultado será gravado no arquivo outfile.

---

## ⚙️ Funcionalidades  

### ✅ Versão Mandatória  
- Executa **dois comandos** encadeados com `pipe`.  
- Redireciona a entrada a partir de um `infile`.  
- Redireciona a saída para um `outfile`.  
- Localiza comandos usando o **PATH**.  
- Trata erros comuns:  
  - Arquivo inexistente.  
  - Permissão negada.  
  - Comando não encontrado.  

### ⭐ Versão Bônus  
- Suporte a **múltiplos comandos** encadeados (vários pipes).  
- Implementação do **here_doc** (entrada padrão até encontrar um delimitador).  
- Redirecionamento no modo `here_doc` usa `>>` (append) para não sobrescrever o `outfile`.  
- Reforço no tratamento de erros para cenários com múltiplos processos.  

---

## 🧠 Conceitos Trabalhados  

Durante a implementação do `pipex`, você irá explorar conceitos fundamentais de **programação em C** e **sistemas Unix**, essenciais para entender como o shell funciona por baixo dos panos:

- &emsp; **Processos e Fork**  
  Criação de processos filhos com `fork()` para executar comandos simultaneamente.  

- &emsp; **Execução de Programas Externos**  
  Uso de `execve()` para substituir o processo atual pelo comando desejado.  

- &emsp; **Pipes**  
  Comunicação entre processos usando `pipe()` para conectar a saída de um processo à entrada de outro.  

- &emsp; **Redirecionamento de Arquivos**  
  Manipulação de entrada (`infile`) e saída (`outfile`) com `open()`, `close()`, `dup()` e `dup2()`.  

- &emsp; **Tratamento de Erros**  
  Verificação de condições como arquivo inexistente, comando inválido ou falha em chamadas de sistema.  

- &emsp; **Strings e PATH**  
  Manipulação de strings para localizar corretamente os executáveis no PATH do sistema.  

- &emsp; **Gerenciamento de Memória**  
  Alocação e liberação correta de memória para evitar **memory leaks**.  

- &emsp; **Here Document (Bônus)**  
  Leitura de entrada padrão até encontrar um delimitador, simulando o operador `<<` do shell.  


---

## 📖 Exemplos de Uso Práticos  

### 1. Versão obrigatória (dois comandos)  
```bash
./pipex infile "grep Hello" "wc -l" outfile
```
- Equivalente a:

```bash
    < infile grep Hello | wc -l > outfile
```
° Explicação:

> `grep Hello` busca linhas contendo "Hello" em infile.  
> `wc -l` conta quantas linhas correspondem.  
> Resultado gravado em outfile.  

2. Versão bônus (múltiplos comandos)
```bash
./pipex infile "grep Hello" "sort" "uniq -c" outfile
```
- Equivalente a:

```bash
    < infile grep Hello | sort | uniq -c > outfile
```
° Explicação:

> `grep` Hello filtra linhas.  
> `sort` ordena as linhas filtradas.  
> `uniq -c` conta ocorrências únicas.  
> Resultado final vai para outfile.  

3. Versão bônus com here_doc
```bash
./pipex here_doc EOF "cat" "wc -w" outfile
```
- Equivalente a:

```bash
    cat << EOF | wc -w >> outfile
```
° Explicação:

> O programa lê da entrada padrão até encontrar a linha `EOF`.  
> `cat` passa todo o texto recebido para o próximo comando.  
> `wc -w` conta as palavras.  
> O resultado é acrescentado ao final de outfile (append).  
---

## 📂 Arquivos

| Arquivo/Pasta      | Descrição                                                                 |
|--------------------|---------------------------------------------------------------------------|
| `Makefile`         | Script para compilar, recompilar e limpar o projeto                      |
| `includes/`        | Contém o arquivo de cabeçalho `pipex.h` com protótipos, defines e includes necessários |
| `libft/`           | Biblioteca de funções auxiliares (funções da libft personalizadas)        |
| `srcs/`            | Código-fonte principal do projeto                                         |
| &emsp;`check.c`    | Funções de verificação e validação de argumentos                          |
| &emsp;`exec.c`     | Funções de execução de comandos                                           |
| &emsp;`fd_utils.c` | Funções de manipulação de descritores de arquivos                         |
| &emsp;`here_doc.c` | Implementação do here_doc (modo bônus)                                    |
| &emsp;`utils.c`    | Funções auxiliares gerais                                                 |
| &emsp;`pipex.c`    | Função `main()` e controle geral do programa                               |

---

## 💡 Considerações e Dicas

Aqui vão algumas recomendações para facilitar o uso e estudo do `pipex`:

### ⚙️ Compilação
- Sempre utilize `make` para compilar o projeto.
- Garanta que a versão da `libft` esteja correta e atualizada antes de compilar.

### 🖥️ Execução
- Verifique a ordem dos comandos e os arquivos `infile` e `outfile`.
- Use aspas em comandos que possuam argumentos ou espaços para evitar erros.

### 🚨 Tratamento de Erros
- O programa lida com arquivos inexistentes, comandos inválidos ou falta de permissões.
- Sempre confirme se os caminhos e o PATH do sistema estão corretos.

### 🐞 Debug
- Utilize `printf` ou `perror` para diagnosticar falhas em:
  - abertura de arquivos (`open`)
  - criação de processos (`fork`)
  - execução de comandos (`execve`)

### 📜 Here Document (Modo Bônus)
- Ao usar `here_doc`, a entrada termina quando você digita exatamente o delimitador.
- Espaços extras ou erros de digitação podem causar falhas na execução.

### 💾 Boas Práticas
- Libere sempre a memória alocada para evitar **memory leaks**.
- Feche todos os descritores de arquivos para evitar problemas de concorrência.

### 📚 Estudo
- Este projeto é excelente para entender como o **shell funciona por baixo dos panos**.
- Pratica conceitos essenciais de sistemas Unix como **fork, execve, pipes e redirecionamentos**.



---

## 👩‍💻 Autoria

**✨ Amy Rodrigues ✨** 

🎓 Estudante de C e desenvolvimento de baixo nível na [42 São Paulo](https://www.42sp.org.br/)

🐧 Usuária de Linux | 💻 Fã de terminal | 🎯 Apaixonada por entender como tudo funciona por trás dos bastidores

---

## 📎 Licença

Este projeto foi desenvolvido como parte do currículo educacional da 42 São Paulo.

📘 **Uso permitido**:
- Pode ser utilizado como referência para estudos e aprendizado individual
- Pode servir de inspiração para seus próprios projetos

🚫 **Proibido**:
- Submeter cópias deste projeto como se fossem de sua autoria em avaliações da 42 ou outras instituições

Seja ético e contribua para uma comunidade de desenvolvedores mais honesta e colaborativa 🤝
