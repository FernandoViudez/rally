// TODO: Add initial comment for project name, integrants, and others...

#include <iostream>
#include <string>
#include <stdio.h>

using namespace std;

// Constantes
const char nombreArchivo[21] = "rally.txt"; // TODO Pasar a variable ingresada por el user
const int MAX_REGS = 500;

// Tipos
typedef unsigned short int numCorto;

// Registros
struct rCorredor
{
  numCorto etapa;
  numCorto tVehi;
  numCorto nroVehi;
  char nPiloto[21];
  char nCoPiloto[16];
  numCorto minsT; // Cast function into utils
};

// Utils starts ----------

//Agregar ceros para crear un formato necesario
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

// Obtener char desde el archivo
void capturarPorDigitos(numCorto cantDigitos, char *varAGuardar)
{
  cin.ignore();
  cin.get(varAGuardar, cantDigitos);
}

// Imprime todos los registros de vCorredores
void imprimirRegistrosPorDefecto(rCorredor vCorredores[MAX_REGS])
{
  cout << "================LISTA TXT================"
       << "\n";
  for (int i = 1; i <= MAX_REGS; i++)
  {
    if (int(vCorredores[i].etapa) == 0)
    {
      break;
    }

    cout << vCorredores[i].etapa << " " << vCorredores[i].tVehi << " " << agregarCerosANumero(2, vCorredores[i].nroVehi) << " " << vCorredores[i].nPiloto << " " << vCorredores[i].nCoPiloto << " " << agregarCerosANumero(3, vCorredores[i].minsT) << "\n";
  }
}

// Retorna true si está todo ok
bool validarDatosTiempoReal(rCorredor rCorredor)
{
  // Validar que cada campo tenga un formato correcto.
  // Validar caracteres especiales
  // Convertir cada campo a su type correspondiente para validarlo
  return true;
}

// Retorna true si está todo ok
bool validarDatosGral(rCorredor vCorredores[MAX_REGS])
{
  // Validar si no se repite el nro vehiculo
  // Realizar indexado
  // Entre otros
  return true;
}

// Utils ends ------------

// Retorna true si la operación fué exitosa, caso contrario, false
bool leerYGuardarRegistros(rCorredor vCorredores[MAX_REGS])
{
  // Abrir y leer archivo
  if (!freopen(nombreArchivo, "r", stdin))
  {
    // Archivo inexistente
    return false;
  }

  for (int i = 1; i <= MAX_REGS; i++)
  {
    // Capturar datos por orden
    cin >> vCorredores[i].etapa >> vCorredores[i].tVehi >> vCorredores[i].nroVehi;
    capturarPorDigitos(21, vCorredores[i].nPiloto);
    capturarPorDigitos(16, vCorredores[i].nCoPiloto);
    cin >> vCorredores[i].minsT;

    // Si algún dato en especifico es incorrecto en tipo, pues se lanza un error
    if (!validarDatosTiempoReal(vCorredores[i]))
    {
      return false;
    }
  }

  // Validar datos generales como que no se repitan cosas, etc.
  if (!validarDatosGral(vCorredores))
  {
    return false;
  }

  return true;
}

int main()
{
  // Crear array de corredores
  rCorredor vCorredores[MAX_REGS];

  // Validaciones generales y abrir el archivo
  if (!leerYGuardarRegistros(vCorredores))
  {
    cout << "Error intentando leer el archivo: " << nombreArchivo << ". Es probable que algun dato sea incorrecto, o el archivo sea inexistente";
    return 0;
  }

  // A: Imprimir corredores tal como vienen en el txt
  imprimirRegistrosPorDefecto(vCorredores); // TODO: Imprimir fuera de la consola en un txt aparte.
}