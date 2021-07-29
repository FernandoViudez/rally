/*
  Nombre del programa: Rally
  Fecha de entrega: 16/08/2021
  Nro versión: ^v1.0.0
  Objetivo: Dado un conjunto de datos desordenados, realizar algoritmos en diferentes módulos capaces de validar, recorrer y transformar esos datos en una estructura interna logicamente manejable para obtener los resultados deseados.
  Integrantes:  - Fernando Viudez
                - ....
*/

#include <iostream>
#include <string>
#include <stdio.h>

using namespace std;

// Constantes
const int MAX_REGS = 500;
const int MAX_ETP = 5;
const int MAX_TVEH = 4;
const int MAX_VEH = 100;
const int TM_ABAND = 999;

// Tipos
typedef unsigned short int numCorto;

// Registros
struct rCorredor
{
  numCorto etapa;
  numCorto tVehi;
  numCorto nroVehi;
  char nPiloto[21];
  char nCoPiloto[21];
  char marcaVeh[16];
  numCorto minsT;
};

// Manejador global de errores (Global error handler)
void abortarEjec(const char *);

// Validaciones
void validarEtapa(numCorto etapa);
void validarTipoVeh(numCorto tVehi);
void validarNroVeh(numCorto nroVeh);
void validarTiempo(numCorto tiempo);
bool validarNoMasRegistros(rCorredor rCorredor);
void validarDatosTiempoReal(rCorredor rCorredor);
void validarDatosGral(rCorredor vCorredores[MAX_REGS]);

// Darle un formato a un numero en base a "0"
string agregarCerosANumero(int digitosTotales, numCorto numero);

// Obtener un char en base a una cantidad definida de digitos
void capturarPorDigitos(numCorto cantDigitos, char *varAGuardar);

// Abre un archivo segun el nombre y la acción
void abrirArchivo(const char[21], const char *);

// Procesar etapas, validando datos
void procEtapasRally(rCorredor vCorredores[MAX_REGS]);

// Leer y guardar todos los datos
void leerEtapasRally(rCorredor vCorredores[MAX_REGS]);

// Imprimir listado de todos los corredores tal como viene en el txt con una estructura interna
void listadoCorredores(rCorredor vCorredores[MAX_REGS]);

int main()
{
  // Crear array de corredores
  rCorredor vCorredores[MAX_REGS];
  const char nombreArchivo[21] = "EtapasRally.txt"; // TODO Pasar a variable ingresada por el user

  // TODO Agregar Nombre de archivo dinámico ingresado por el usuario en v1.1

  // Abre rachivo rally.txt para su lectura ("read")
  abrirArchivo(nombreArchivo, "r");

  // Validaciones generales & leer el archivo & guardar datos
  procEtapasRally(vCorredores);

  // Abrir archivo donde se va a imprimir todo lo siguiente

  // A: Imprimir corredores paralelo a EtapasRally.txt
  listadoCorredores(vCorredores);
}

void abortarEjec(const char *msjError)
{
  cout << msjError << "\n";
  abort();
}

void abrirArchivo(const char nombreArchivo[21], const char *accion)
{
  // Abrir y leer archivo
  if (!freopen(nombreArchivo, accion, stdin))
  {
    // Archivo inexistente
    abortarEjec("Archivo inexistente");
  }
}

void leerEtapasRally(rCorredor vCorredores[MAX_REGS])
{
  for (int i = 1; i <= MAX_REGS; i++)
  {
    // Capturar datos por orden
    cin >> vCorredores[i].etapa >> vCorredores[i].tVehi >> vCorredores[i].nroVehi;
    capturarPorDigitos(21, vCorredores[i].nPiloto);
    capturarPorDigitos(21, vCorredores[i].nCoPiloto);
    capturarPorDigitos(16, vCorredores[i].marcaVeh);
    cin >> vCorredores[i].minsT;

    // Validar cuando se terminan los registros (No iterar 500 veces si no hay 500 registros)
    if(validarNoMasRegistros(vCorredores[i])) {
      break;
    }

    validarDatosTiempoReal(vCorredores[i]);
    
  }
}

void procEtapasRally(rCorredor vCorredores[MAX_REGS])
{
  leerEtapasRally(vCorredores);
  // Validar datos generales como que no se repitan cosas, etc.
  validarDatosGral(vCorredores);
}

void validarEtapa(numCorto etapa)
{
  // Conversión a "int" es automatica.
  // Validar si el valor es permitido
  if (
      etapa <= 0 ||
      etapa > MAX_ETP)
  {
    abortarEjec("Formato de etapa incorrecto");
  }
}

void validarTipoVeh(numCorto tVehi)
{
  // Validar si está entre 1 y 4
  if (
      tVehi <= 0 ||
      tVehi > MAX_TVEH)
  {
    abortarEjec("Formato de tipo de vehiculo incorrecto");
  }
}

void validarNroVeh(numCorto nroVeh)
{
  // Validar que su length sea el permitido (entre 0 y 99 inclusive, por ser dos digitos max)
  if (
      nroVeh < 0 ||
      nroVeh >= MAX_VEH)
  {
    abortarEjec("Formato incorrecto en Nro de vehiculo");
  }
}

void validarTiempo(numCorto tiempo)
{
  // Validar si el tiempo está etre 0 y 999 (Max 3 digitos)
  if (
      tiempo < 0 ||
      tiempo > TM_ABAND)
  {
    abortarEjec("Formato de tiempo en mins. incorrecto");
  }
}

bool validarNoMasRegistros(rCorredor rCorredor)
{if (
      rCorredor.etapa == 0 &&
      rCorredor.minsT == 0 &&
      rCorredor.nroVehi == 0 &&
      rCorredor.tVehi == 0)
  {
    return true;
  }
  else
  {
    return false;
  }
}

string agregarCerosANumero(int digitosTotales, numCorto numero)
{
  // Ver el length del numero actual
  int cantDigNumero = to_string(numero).length();
  int cantidadCerosAgregar = digitosTotales - cantDigNumero;
  string nuevoNumero = to_string(numero);

  for (int i = 1; i <= cantidadCerosAgregar; i++)
  {
    // Agregar ceros al numero en string
    nuevoNumero = "0" + nuevoNumero;
  }

  // Devolver el numero
  return nuevoNumero;
}

void capturarPorDigitos(numCorto cantDigitos, char *varAGuardar)
{
  cin.ignore();
  cin.get(varAGuardar, cantDigitos);
}

void validarDatosTiempoReal(rCorredor rCorredor)
{
  validarEtapa(rCorredor.etapa);
  validarTipoVeh(rCorredor.tVehi);
  validarNroVeh(rCorredor.nroVehi);
  validarTiempo(rCorredor.minsT);
}

void validarDatosGral(rCorredor vCorredores[MAX_REGS])
{
  // for(int i = 0; i < MAX_REGS; i++) {
  
    // Validar si no se repite el nro vehiculo
    // Realizar indexado entre el nro veh y los otros datos
    // Setear tiempo de abandono en caso de que se haya abandonado en alguna etapa
  // }
}

void listadoCorredores(rCorredor vCorredores[MAX_REGS])
{
  cout << "Etapa  "
       << "Tipo veh.  "
       << "Nro veh.   "
       << "Nombre del piloto     "
       << "Nombre del copiloto      "
       << "Marca Veh.       "
       << "Tiempo en mins. \n";

  for (int i = 1; i <= MAX_REGS; i++)
  {
    if (int(vCorredores[i].etapa) == 0)
    {
      break;
    }

    cout << vCorredores[i].etapa << "        " << vCorredores[i].tVehi << "         " << agregarCerosANumero(2, vCorredores[i].nroVehi) << "        " << vCorredores[i].nPiloto << "  " << vCorredores[i].nCoPiloto << "     " << vCorredores[i].marcaVeh << "   " << agregarCerosANumero(3, vCorredores[i].minsT) << "\n";
  }
}
