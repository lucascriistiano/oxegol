#include "aux.h"

no_literal_t* criar_no_literal(tipo_t tipo, valor_t valor) {
  no_literal_t* no = (no_literal_t*) malloc(sizeof(no_literal_t));
  no->tipo = tipo;
  no->valor = valor;  //Criar cópia e desalocar quando for do tipo string?
  return no;
}