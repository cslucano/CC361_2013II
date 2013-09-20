
void navegar(int * p){
  *p = *p + 1
}
void leermouse(int * p){
  *p = *p -1
}
void leerteclado(){}
void formato(){}
void escribirpantalll(){}
void escribirendisco(){}

void main()
{

  int i = 5;
  crearHilo(navegar(&i))
  crearHilo(leermouse(&i))
  crearHilo(leerteclado)
  crearHilo(formato)
  ...

}
