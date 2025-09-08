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

1. Compile o projeto:

```bash
   make
```
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

Durante a implementação do `pipex`, você irá trabalhar com vários conceitos fundamentais de **programação em C** e **sistemas Unix**:

- **Processos e Fork:** criação de processos filhos com `fork()` para executar comandos simultaneamente.  
- **Execução de programas externos:** uso de `execve()` para substituir o processo atual pelo comando desejado.  
- **Pipes:** comunicação entre processos usando `pipe()` para conectar a saída de um processo à entrada de outro.  
- **Redirecionamento de arquivos:** manipulação de entrada (`infile`) e saída (`outfile`) com `open()`, `close()`, `dup()`, `dup2()`.  
- **Tratamento de erros:** verificação de condições como arquivo inexistente, comando inválido ou falha em sistemas de chamadas.  
- **Strings e PATH:** manipulação de strings para localizar corretamente os executáveis no PATH do sistema.  
- **Gerenciamento de memória:** alocação e liberação correta de memória para evitar leaks.  
- **Here Document (bônus):** leitura de entrada padrão até encontrar um delimitador, simulando `<<` do shell.

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
