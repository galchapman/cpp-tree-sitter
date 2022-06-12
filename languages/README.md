# Langauges

This directory is used to donwload a language for tree sitter

## Adding a new language

```shell
make <lang>-lang.o
```

## Using a langauge

Just add the \<lang>-lang.o object file to your link chain and include \<lang>.hpp file
