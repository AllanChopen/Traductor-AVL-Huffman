#include <iostream>      // Para operaciones de entrada y salida estándar (cout, cin)
#include <fstream>       // Para manejo de archivos (ifstream, ofstream)
#include <sstream>       // Para manipulación de cadenas como flujos (stringstream)
#include <direct.h>      // Para funciones relacionadas con directorios, como _mkdir
#include <unordered_map> // Para el uso de mapas hash (unordered_map) en encriptación y desencriptación
#include <map>           // Para el uso de mapas ordenados (map) en ranking y Huffman
#include <vector>        // Para el uso de arreglos dinámicos (vector) en almacenamiento de datos
#include <algorithm>     // Para funciones de ordenamiento y búsqueda (sort, remove_if, max, etc.)
#include <Windows.h>     // Para funciones específicas de Windows (no se usa directamente, pero puede ser requerido por dependencias)
#include <string>        // Para el manejo de cadenas de texto (string)
#include <functional>    // Para el uso de funciones y lambdas (std::function)
#include <queue>         // Para el uso de colas y priority_queue (Huffman)
#include <bitset>        // Para manipulación de bits (no se usa directamente, pero útil para compresión)
#include <filesystem>    // Para manipulación de archivos y carpetas (C++17, fs::directory_iterator, fs::remove_all, etc.)
#include <cstring>       // Para funciones de manejo de cadenas de bajo nivel (no se usa directamente, pero puede ser requerido)
#include <limits>        // Para obtener valores límite de tipos numéricos (no se usa directamente, pero útil en validaciones)


// Uso del espacio de nombres estándar para evitar escribir std:: en todo el código.
using namespace std;


// Alias para el namespace de filesystem, simplifica el uso de fs:: en vez de std::filesystem::
namespace fs = filesystem;




//==========================ESTRUCTURAS==========================



// Estructura para almacenar una palabra y sus traducciones
// Estructura para almacenar una palabra y sus traducciones en diferentes idiomas.
// Cada campo representa la traducción de la palabra en un idioma específico.
//
// Campos:
// - espanol: La palabra en español (idioma base).
// - ingles: Traducción de la palabra al inglés.
// - aleman: Traducción de la palabra al alemán.
// - frances: Traducción de la palabra al francés.
// - italiano: Traducción de la palabra al italiano.
//
// Uso:
// - Esta estructura se utiliza para representar las palabras que se almacenan en el árbol AVL
//   y se procesan en el traductor.

struct Palabra {
    string espanol;
    string ingles;
    string aleman;
    string frances;
    string italiano;
};



// Estructura para almacenar la información de un usuario registrado en el sistema.
//
// Campos:
// - nombre: Nombre de usuario único.
// - clave: Contraseña del usuario (almacenada encriptada para mayor seguridad).
//
// Uso:
// - Esta estructura se utiliza para manejar el registro y la autenticación de usuarios.
// - Los datos de los usuarios se almacenan en el archivo "usuarios.umg".

struct Usuario {
    string nombre;
    string clave;
};



// Nodo del Árbol Binario de Búsqueda (AVL) utilizado para almacenar palabras y sus traducciones.
//
// Campos:
// - palabra: Objeto de tipo `Palabra` que contiene la palabra en español y sus traducciones.
// - izquierda: Puntero al nodo hijo izquierdo.
// - derecha: Puntero al nodo hijo derecho.
// - altura: Altura del nodo en el árbol AVL (necesaria para mantener el balance del árbol).
//
// Constructor:
// - Nodo(Palabra p): Inicializa un nodo con la palabra proporcionada y establece los punteros
//   izquierdo y derecho en nullptr, y la altura en 1.
//
// Uso:
// - Esta estructura se utiliza para construir el árbol AVL que almacena las palabras y sus traducciones.
// - El árbol AVL permite realizar búsquedas, inserciones y eliminaciones de palabras de manera eficiente.

struct Nodo {
    Palabra palabra;
    Nodo* izquierda;
    Nodo* derecha;
    int altura;

    Nodo(Palabra p) : palabra(p), izquierda(nullptr), derecha(nullptr), altura(1) {}
};




//==========================FUNCIONES DE ENCRIPTACION==========================



// Función para encriptar una palabra utilizando una tabla de encriptación.
// Cada carácter de la palabra se reemplaza por un código definido en la tabla.
// Si un carácter no está en la tabla, se conserva sin cambios.
//
// Parámetros:
// - palabra: La palabra que se desea encriptar.
//
// Retorno:
// - Un string que representa la palabra encriptada.
//
// Notas:
// - La tabla de encriptación utiliza un mapeo de caracteres a códigos específicos.
// - Los caracteres que no están en la tabla (como números o símbolos) se mantienen sin cambios.
// - Esta función es utilizada para proteger datos sensibles como nombres de usuario o palabras buscadas.

string encriptarPalabra(const string& palabra) {
    unordered_map<char, string> tablaEncriptacion = {
        {'b', "m1"}, {'B', "g1"},
        {'c', "m2"}, {'C', "g2"},
        {'d', "m3"}, {'D', "g3"},
        {'f', "m4"}, {'F', "g4"},
        {'g', "m5"}, {'G', "g5"},
        {'h', "m6"}, {'H', "g6"},
        {'j', "m7"}, {'J', "g7"},
        {'k', "m8"}, {'K', "g8"},
        {'l', "m9"}, {'L', "g9"},
        {'m', "m10"}, {'M', "g10"},
        {'n', "m11"}, {'N', "g11"},
        {'ñ', "m12"}, {'Ñ', "g12"},
        {'p', "m13"}, {'P', "g13"},
        {'q', "m14"}, {'Q', "g14"},
        {'r', "m15"}, {'R', "g15"},
        {'s', "m16"}, {'S', "g16"},
        {'t', "m17"}, {'T', "g17"},
        {'a', "U1"}, {'A', "U1"},
        {'e', "U2"}, {'E', "U2"},
        {'i', "U3"}, {'I', "U3"},
        {'o', "U4"}, {'O', "U4"},
        {'u', "U5"}, {'U', "U5"},
        {'v', "m18"}, {'V', "g18"},
        {'w', "m19"}, {'W', "g19"},
        {'x', "m20"}, {'X', "g20"},
        {'y', "m21"}, {'Y', "g21"},
        {'z', "m22"}, {'Z', "g22"}
    };

    string palabraEncriptada = "";

    // Iterar sobre cada carácter de la palabra.
    for (char c : palabra) {
        // Si el carácter está en la tabla, reemplazarlo por su código.
        if (tablaEncriptacion.find(c) != tablaEncriptacion.end()) {
            palabraEncriptada += tablaEncriptacion[c];
        }
        // Si no está en la tabla, conservar el carácter original.
        else {
            palabraEncriptada += c;
        }
    }

    return palabraEncriptada;
}



// Función para desencriptar una palabra utilizando una tabla de desencriptación.
// Cada token en la palabra encriptada se reemplaza por el carácter correspondiente
// definido en la tabla de desencriptación.
//
// Parámetros:
// - palabraEncriptada: La palabra encriptada que se desea desencriptar.
//
// Retorno:
// - Un string que representa la palabra desencriptada.
//
// Notas:
// - La tabla de desencriptación utiliza un mapeo de códigos específicos a caracteres.
// - La función procesa la palabra encriptada de izquierda a derecha, intentando
//   coincidir con los tokens más largos primero (máximo 3 caracteres).
// - Si un token no se encuentra en la tabla, el carácter original se conserva.
// - Esta función es utilizada para revertir la encriptación aplicada por `encriptarPalabra`.

string desencriptarPalabra(const string& palabraEncriptada) {
    unordered_map<string, char> tablaDesencriptacion = {
        {"m1", 'b'}, {"g1", 'B'},
        {"m2", 'c'}, {"g2", 'C'},
        {"m3", 'd'}, {"g3", 'D'},
        {"m4", 'f'}, {"g4", 'F'},
        {"m5", 'g'}, {"g5", 'G'},
        {"m6", 'h'}, {"g6", 'H'},
        {"m7", 'j'}, {"g7", 'J'},
        {"m8", 'k'}, {"g8", 'K'},
        {"m9", 'l'}, {"g9", 'L'},
        {"m10", 'm'}, {"g10", 'M'},
        {"m11", 'n'}, {"g11", 'N'},
        {"m12", 'ñ'}, {"g12", 'Ñ'},
        {"m13", 'p'}, {"g13", 'P'},
        {"m14", 'q'}, {"g14", 'Q'},
        {"m15", 'r'}, {"g15", 'R'},
        {"m16", 's'}, {"g16", 'S'},
        {"m17", 't'}, {"g17", 'T'},
        {"U1", 'a'}, {"U1", 'A'},
        {"U2", 'e'}, {"U2", 'E'},
        {"U3", 'i'}, {"U3", 'I'},
        {"U4", 'o'}, {"U4", 'O'},
        {"U5", 'u'}, {"U5", 'U'},
        {"m18", 'v'}, {"g18", 'V'},
        {"m19", 'w'}, {"g19", 'W'},
        {"m20", 'x'}, {"g20", 'X'},
        {"m21", 'y'}, {"g21", 'Y'},
        {"m22", 'z'}, {"g22", 'Z'}
    };

    string palabraOriginal = "";
    size_t i = 0;
    size_t maxTokenLength = 3; // La clave más larga tiene 3 caracteres

    // Procesar la palabra encriptada de izquierda a derecha.
    while (i < palabraEncriptada.size()) {
        bool encontrado = false;

        // Intentar coincidir con los tokens más largos primero.
        for (int len = maxTokenLength; len >= 2; --len) {
            if (i + len <= palabraEncriptada.size()) {
                string token = palabraEncriptada.substr(i, len);
                // Si el token se encuentra en la tabla, agregar el carácter correspondiente.
                if (tablaDesencriptacion.find(token) != tablaDesencriptacion.end()) {
                    palabraOriginal += tablaDesencriptacion[token];
                    i += len; // Avanzar el índice según la longitud del token.
                    encontrado = true;
                    break; // Salir del bucle al encontrar coincidencia.
                }
            }
        }

        // Si no se encontró un token válido, conservar el carácter original.
        if (!encontrado) {
            palabraOriginal += palabraEncriptada[i];
            ++i;
        }
    }

    return palabraOriginal;
}



// Función para aplicar la operación XOR a un texto utilizando una llave.
// Cada carácter del texto se combina con un carácter de la llave mediante la operación XOR.
// La llave se repite cíclicamente si es más corta que el texto.
//
// Parámetros:
// - texto: El texto que se desea procesar.
// - llave: La llave utilizada para aplicar la operación XOR.
//
// Retorno:
// - Un string que representa el texto procesado con XOR.
//
// Notas:
// - Esta función es utilizada para encriptar o desencriptar datos de manera reversible.
// - Aplicar XOR dos veces con la misma llave revierte el resultado al texto original.
// - Es importante que la llave no sea vacía para evitar errores.

string aplicarXOR(const string& texto, const string& llave) {
    string resultado = "";

    // Iterar sobre cada carácter del texto.
    for (size_t i = 0; i < texto.size(); ++i) {
        // Aplicar XOR entre el carácter del texto y el carácter correspondiente de la llave.
        resultado += texto[i] ^ llave[i % llave.size()];
    }

    return resultado;
}



// Función para revertir la operación XOR aplicada a un texto utilizando la misma llave.
// Esta función es idéntica a `aplicarXOR`, ya que aplicar XOR dos veces con la misma llave
// Se hizo en una funcion diferente para mejorar la legibilidad.
// revierte el resultado al texto original.
//
// Parámetros:
// - texto: El texto procesado con XOR que se desea revertir.
// - llave: La llave utilizada para revertir la operación XOR.
//
// Retorno:
// - Un string que representa el texto original.
//
// Notas:
// - Esta función es utilizada para desencriptar datos procesados con `aplicarXOR`.
// - Es importante que la misma llave utilizada para encriptar sea utilizada para desencriptar.
// - Si la llave no coincide, el resultado será incorrecto.

string deshacerXOR(const string& texto, const string& llave) {
    string resultado = "";

    // Iterar sobre cada carácter del texto.
    for (size_t i = 0; i < texto.size(); ++i) {
        // Aplicar XOR entre el carácter del texto y el carácter correspondiente de la llave.
        resultado += texto[i] ^ llave[i % llave.size()];
    }

    return resultado;
}




//===========================FUNCIONES DEL ÁRBOL AVL==========================



// Función para obtener la altura de un nodo en el árbol AVL.
//
// Parámetros:
// - nodo: Puntero al nodo del cual se desea obtener la altura.
//
// Retorno:
// - Un entero que representa la altura del nodo.
//   - Si el nodo es nulo, retorna 0 (altura de un árbol vacío).
//   - Si el nodo no es nulo, retorna el valor almacenado en el campo `altura`.
//
// Notas:
// - La altura de un nodo es la longitud del camino más largo desde ese nodo hasta una hoja.
// - Esta función es utilizada para calcular el balance de los nodos y mantener el árbol AVL balanceado.

int altura(Nodo* nodo) {
    if (!nodo) return 0; // Caso base: un nodo nulo tiene altura 0.
    return nodo->altura; // Retornar la altura almacenada en el nodo.
}



// Función para calcular el factor de balance de un nodo en el árbol AVL.
//
// Parámetros:
// - nodo: Puntero al nodo del cual se desea calcular el factor de balance.
//
// Retorno:
// - Un entero que representa el factor de balance del nodo.
//   - Si el nodo es nulo, retorna 0.
//   - Si el nodo no es nulo, retorna la diferencia entre la altura del subárbol izquierdo
//     y la altura del subárbol derecho.
//
// Notas:
// - El factor de balance se utiliza para determinar si un nodo está balanceado:
//   - Un nodo está balanceado si el factor de balance está en el rango [-1, 1].
//   - Si el factor de balance es menor que -1 o mayor que 1, el árbol necesita ser re-balanceado.
// - Esta función es clave para mantener las propiedades del árbol AVL.

int factorBalance(Nodo* nodo) {
    if (!nodo) return 0; // Caso base: un nodo nulo tiene factor de balance 0.
    return altura(nodo->izquierda) - altura(nodo->derecha); // Diferencia de alturas.
}



// Función para actualizar la altura de un nodo en el árbol AVL.
//
// Parámetros:
// - nodo: Puntero al nodo cuya altura se desea actualizar.
//
// Proceso:
// 1. Verifica si el nodo es nulo. Si lo es, no realiza ninguna acción.
// 2. Calcula la nueva altura del nodo como:
//    - 1 + la altura máxima entre el subárbol izquierdo y el subárbol derecho.
// 3. Asigna el valor calculado al campo `altura` del nodo.
//
// Notas:
// - Esta función debe ser llamada después de realizar operaciones que puedan modificar
//   la estructura del árbol, como inserciones, eliminaciones o rotaciones.
// - Mantener actualizada la altura de los nodos es esencial para calcular el factor de balance
//   y garantizar que el árbol AVL permanezca balanceado.

void actualizarAltura(Nodo* nodo) {
    if (!nodo) return; // Caso base: si el nodo es nulo, no hace nada.

    // Calcular la nueva altura del nodo.
    nodo->altura = 1 + max(altura(nodo->izquierda), altura(nodo->derecha));
}



// Función para realizar una rotación a la derecha en un árbol AVL.
//
// Parámetros:
// - y: Puntero al nodo que será rotado hacia la derecha.
//
// Retorno:
// - Un puntero al nuevo nodo raíz después de la rotación.
//
// Proceso:
// 1. Identifica el nodo izquierdo (`x`) como el nuevo nodo raíz.
// 2. Almacena el subárbol derecho de `x` (denominado `T2`) temporalmente.
// 3. Realiza la rotación:
//    - El nodo `x` se convierte en la nueva raíz.
//    - El nodo `y` pasa a ser el hijo derecho de `x`.
//    - El subárbol `T2` se asigna como el hijo izquierdo de `y`.
// 4. Actualiza las alturas de los nodos afectados (`y` y `x`).
//
// Notas:
// - Esta operación se utiliza para re-balancear el árbol AVL cuando el subárbol izquierdo
//   de un nodo está desbalanceado (caso de rotación simple derecha).
// - Mantiene las propiedades del árbol AVL (balance y orden).

Nodo* rotarDerecha(Nodo* y) {
    Nodo* x = y->izquierda; // El nuevo nodo raíz será el hijo izquierdo.
    Nodo* T2 = x->derecha;  // Almacena temporalmente el subárbol derecho de `x`.

    // Realizar la rotación.
    x->derecha = y;
    y->izquierda = T2;

    // Actualizar las alturas de los nodos afectados.
    actualizarAltura(y);
    actualizarAltura(x);

    // Retornar el nuevo nodo raíz.
    return x;
}



// Función para realizar una rotación a la izquierda en un árbol AVL.
//
// Parámetros:
// - x: Puntero al nodo que será rotado hacia la izquierda.
//
// Retorno:
// - Un puntero al nuevo nodo raíz después de la rotación.
//
// Proceso:
// 1. Identifica el nodo derecho (`y`) como el nuevo nodo raíz.
// 2. Almacena el subárbol izquierdo de `y` (denominado `T2`) temporalmente.
// 3. Realiza la rotación:
//    - El nodo `y` se convierte en la nueva raíz.
//    - El nodo `x` pasa a ser el hijo izquierdo de `y`.
//    - El subárbol `T2` se asigna como el hijo derecho de `x`.
// 4. Actualiza las alturas de los nodos afectados (`x` y `y`).
//
// Notas:
// - Esta operación se utiliza para re-balancear el árbol AVL cuando el subárbol derecho
//   de un nodo está desbalanceado (caso de rotación simple izquierda).
// - Mantiene las propiedades del árbol AVL (balance y orden).

Nodo* rotarIzquierda(Nodo* x) {
    Nodo* y = x->derecha; // El nuevo nodo raíz será el hijo derecho.
    Nodo* T2 = y->izquierda; // Almacena temporalmente el subárbol izquierdo de `y`.

    // Realizar la rotación.
    y->izquierda = x;
    x->derecha = T2;

    // Actualizar las alturas de los nodos afectados.
    actualizarAltura(x);
    actualizarAltura(y);

    // Retornar el nuevo nodo raíz.
    return y;
}



// Función para insertar un nuevo nodo en el árbol AVL.
//
// Parámetros:
// - nodo: Puntero al nodo raíz del árbol donde se realizará la inserción.
// - nuevaPalabra: Objeto de tipo `Palabra` que contiene la palabra en español y sus traducciones.
//
// Retorno:
// - Un puntero al nodo raíz actualizado después de la inserción.
//
// Proceso:
// 1. Si el nodo actual es nulo, crea un nuevo nodo con la palabra proporcionada y lo retorna.
// 2. Compara la palabra en español de `nuevaPalabra` con la palabra del nodo actual:
//    - Si es menor, realiza la inserción en el subárbol izquierdo.
//    - Si es mayor, realiza la inserción en el subárbol derecho.
//    - Si es igual, no realiza la inserción (no se permiten duplicados).
// 3. Actualiza la altura del nodo actual después de la inserción.
// 4. Calcula el factor de balance del nodo actual para verificar si está balanceado.
// 5. Si el nodo está desbalanceado, aplica las rotaciones necesarias según el caso:
//    - Caso Izquierda Izquierda: Rotación derecha.
//    - Caso Derecha Derecha: Rotación izquierda.
//    - Caso Izquierda Derecha: Rotación izquierda en el hijo izquierdo, luego rotación derecha.
//    - Caso Derecha Izquierda: Rotación derecha en el hijo derecho, luego rotación izquierda.
//
// Notas:
// - Esta función asegura que el árbol AVL permanezca balanceado después de cada inserción.
// - Las rotaciones mantienen las propiedades del árbol AVL (balance y orden).

Nodo* insertar(Nodo* nodo, Palabra nuevaPalabra) {
    // Caso base: si el nodo es nulo, crea un nuevo nodo con la palabra.
    if (!nodo) return new Nodo(nuevaPalabra);

    // Comparar la palabra en español para decidir la dirección de la inserción.
    if (nuevaPalabra.espanol < nodo->palabra.espanol)
        nodo->izquierda = insertar(nodo->izquierda, nuevaPalabra); // Insertar en el subárbol izquierdo.
    else if (nuevaPalabra.espanol > nodo->palabra.espanol)
        nodo->derecha = insertar(nodo->derecha, nuevaPalabra); // Insertar en el subárbol derecho.
    else
        return nodo; // No se permiten duplicados.

    // Actualizar la altura del nodo actual.
    actualizarAltura(nodo);

    // Calcular el factor de balance del nodo actual.
    int balance = factorBalance(nodo);

    // Verificar y corregir el desbalance si es necesario.
    // Caso Izquierda Izquierda
    if (balance > 1 && nuevaPalabra.espanol < nodo->izquierda->palabra.espanol)
        return rotarDerecha(nodo);

    // Caso Derecha Derecha
    if (balance < -1 && nuevaPalabra.espanol > nodo->derecha->palabra.espanol)
        return rotarIzquierda(nodo);

    // Caso Izquierda Derecha
    if (balance > 1 && nuevaPalabra.espanol > nodo->izquierda->palabra.espanol) {
        nodo->izquierda = rotarIzquierda(nodo->izquierda);
        return rotarDerecha(nodo);
    }

    // Caso Derecha Izquierda
    if (balance < -1 && nuevaPalabra.espanol < nodo->derecha->palabra.espanol) {
        nodo->derecha = rotarDerecha(nodo->derecha);
        return rotarIzquierda(nodo);
    }

    // Retornar el nodo actual si no hubo desbalance.
    return nodo;
}



// Función para buscar una palabra en el árbol AVL.
//
// Parámetros:
// - raiz: Puntero al nodo raíz del árbol donde se realizará la búsqueda.
// - palabraBuscada: Cadena que contiene la palabra en español que se desea buscar.
//
// Retorno:
// - Un puntero al nodo que contiene la palabra buscada.
// - Si la palabra no se encuentra en el árbol, retorna nullptr.
//
// Proceso:
// 1. Verifica si el nodo actual (`raiz`) es nulo o si contiene la palabra buscada:
//    - Si es nulo, significa que la palabra no está en el árbol.
//    - Si contiene la palabra buscada, retorna el nodo actual.
// 2. Compara la palabra buscada con la palabra en español del nodo actual:
//    - Si es menor, realiza la búsqueda en el subárbol izquierdo.
//    - Si es mayor, realiza la búsqueda en el subárbol derecho.
//
// Notas:
// - Esta función utiliza la propiedad de orden del árbol AVL para realizar la búsqueda de manera eficiente.
// - La búsqueda tiene una complejidad de O(log n) en promedio, donde `n` es el número de nodos en el árbol.

Nodo* buscar(Nodo* raiz, const string& palabraBuscada) {
    // Caso base: el nodo es nulo o contiene la palabra buscada.
    if (!raiz || raiz->palabra.espanol == palabraBuscada)
        return raiz;

    // Decidir la dirección de la búsqueda.
    if (palabraBuscada < raiz->palabra.espanol)
        return buscar(raiz->izquierda, palabraBuscada); // Buscar en el subárbol izquierdo.
    else
        return buscar(raiz->derecha, palabraBuscada); // Buscar en el subárbol derecho.
}



// Función para cargar palabras desde un archivo y construir el árbol AVL.
//
// Retorno:
// - Un puntero al nodo raíz del árbol AVL construido a partir de las palabras en el archivo.
// - Si el archivo no se puede abrir, retorna nullptr.
//
// Proceso:
// 1. Abre el archivo `palabras.umg` en modo lectura.
// 2. Si el archivo no se puede abrir, muestra un mensaje de error y retorna nullptr.
// 3. Inicializa un puntero `raiz` como nullptr para construir el árbol AVL.
// 4. Lee cada línea del archivo, donde cada línea contiene una palabra y sus traducciones separadas por comas.
// 5. Divide la línea en sus componentes (palabra en español y traducciones) y crea un objeto `Palabra`.
// 6. Inserta el objeto `Palabra` en el árbol AVL utilizando la función `insertar`.
// 7. Cierra el archivo y retorna el puntero a la raíz del árbol.
//
// Notas:
// - El archivo debe estar ubicado en la ruta `C:\\traductor\\palabras.umg`.
// - Cada línea del archivo debe tener el formato: `espanol,ingles,aleman,frances,italiano`.
// - La función utiliza la función `insertar` para mantener el árbol AVL balanceado.
// - Si el archivo está vacío, la función retorna un árbol vacío (nullptr).

Nodo* cargarPalabras() {
    const string nombreArchivo = "C:\\traductor\\palabras.umg";
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo: " << nombreArchivo << endl;
        return nullptr;
    }

    Nodo* raiz = nullptr; // Inicializar la raíz del árbol AVL como nula.
    string linea;

    // Leer cada línea del archivo.
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        Palabra p;

        // Dividir la línea en sus componentes y asignarlas al objeto `Palabra`.
        if (getline(ss, p.espanol, ',') &&
            getline(ss, p.ingles, ',') &&
            getline(ss, p.aleman, ',') &&
            getline(ss, p.frances, ',') &&
            getline(ss, p.italiano, ',')) {
            // Insertar la palabra en el árbol AVL.
            raiz = insertar(raiz, p);
        }
    }

    archivo.close(); // Cerrar el archivo después de leerlo.
    return raiz; // Retornar la raíz del árbol AVL.
}



// Función para agregar una nueva palabra al árbol AVL y al archivo de palabras.
//
// Parámetros:
// - raiz: Puntero al nodo raíz del árbol AVL donde se agregará la nueva palabra.
// - archivo: Ruta del archivo donde se almacenarán las palabras.
//
// Retorno:
// - Un puntero al nodo raíz actualizado después de agregar la nueva palabra.
//
// Proceso:
// 1. Solicita al usuario que ingrese la palabra en español y sus traducciones (inglés, alemán, francés, italiano).
// 2. Crea un objeto `Palabra` con los datos ingresados por el usuario.
// 3. Inserta la nueva palabra en el árbol AVL utilizando la función `insertar`.
// 4. Abre el archivo en modo de adición (append) para guardar la nueva palabra.
// 5. Escribe la palabra y sus traducciones en el archivo en formato CSV (separadas por comas).
// 6. Cierra el archivo y muestra un mensaje de éxito.
//
// Notas:
// - Si el archivo no se puede abrir, muestra un mensaje de error y retorna la raíz sin cambios.
// - La función asegura que la nueva palabra se agrega tanto al árbol AVL como al archivo.
// - El archivo debe estar ubicado en la ruta especificada por el parámetro `archivo`.

Nodo* agregarPalabra(Nodo* raiz, const string& archivo) {
    Palabra nuevaPalabra;

    // Solicitar al usuario los datos de la nueva palabra.
    cout << "\nIngrese la palabra en espanol: ";
    cin >> nuevaPalabra.espanol;
    cout << "Ingrese la traduccion en ingles: ";
    cin >> nuevaPalabra.ingles;
    cout << "Ingrese la traduccion en aleman: ";
    cin >> nuevaPalabra.aleman;
    cout << "Ingrese la traduccion en frances: ";
    cin >> nuevaPalabra.frances;
    cout << "Ingrese la traduccion en italiano: ";
    cin >> nuevaPalabra.italiano;

    // Agregar la nueva palabra al árbol AVL.
    raiz = insertar(raiz, nuevaPalabra);

    // Abrir el archivo en modo de adición para guardar la nueva palabra.
    ofstream archivoOut(archivo, ios::app);
    if (!archivoOut.is_open()) {
        cerr << "Error al abrir el archivo para escritura.\n";
        return raiz; // Retornar la raíz sin cambios si ocurre un error.
    }

    // Escribir la nueva palabra en el archivo en formato CSV.
    archivoOut << nuevaPalabra.espanol << "," << nuevaPalabra.ingles << ","
        << nuevaPalabra.aleman << "," << nuevaPalabra.frances << ","
        << nuevaPalabra.italiano << endl;
    archivoOut.close(); // Cerrar el archivo.

    cout << "Palabra agregada con exito.\n"; // Mostrar mensaje de éxito.
    return raiz; // Retornar la raíz actualizada.
}



// Función para encontrar el nodo con la clave mínima en un árbol AVL.
//
// Parámetros:
// - nodo: Puntero al nodo raíz del árbol o subárbol donde se buscará el nodo mínimo.
//
// Retorno:
// - Un puntero al nodo que contiene la clave mínima en el árbol o subárbol.
//
// Proceso:
// 1. Comienza desde el nodo raíz proporcionado.
// 2. Itera hacia el hijo izquierdo de cada nodo, ya que en un árbol binario de búsqueda
//    el nodo con la clave mínima siempre se encuentra en el extremo izquierdo.
// 3. Retorna el nodo más a la izquierda encontrado.
//
// Notas:
// - Esta función se utiliza principalmente en operaciones como eliminación de nodos
//   para encontrar el sucesor en caso de que el nodo a eliminar tenga dos hijos.
// - Si el árbol o subárbol está vacío (nodo es nulo), retorna nullptr.
// - La complejidad de esta función es O(h), donde `h` es la altura del árbol o subárbol.

Nodo* minimo(Nodo* nodo) {
    // Iterar hacia el hijo izquierdo hasta encontrar el nodo más a la izquierda.
    while (nodo->izquierda) {
        nodo = nodo->izquierda;
    }
    return nodo; // Retornar el nodo con la clave mínima.
}



// Función para eliminar una palabra del árbol AVL.
//
// Parámetros:
// - nodo: Puntero al nodo raíz del árbol o subárbol donde se realizará la eliminación.
// - palabra: Cadena que contiene la palabra en español que se desea eliminar.
//
// Retorno:
// - Un puntero al nodo raíz actualizado después de la eliminación.
//
// Proceso:
// 1. Realiza una búsqueda normal en el árbol AVL para encontrar el nodo que contiene la palabra:
//    - Si la palabra es menor que la palabra del nodo actual, busca en el subárbol izquierdo.
//    - Si la palabra es mayor, busca en el subárbol derecho.
//    - Si encuentra el nodo, procede con la eliminación.
// 2. Elimina el nodo según los siguientes casos:
//    - Caso 1: El nodo no tiene hijos (es una hoja). Elimina el nodo y lo reemplaza con nullptr.
//    - Caso 2: El nodo tiene un solo hijo. Reemplaza el nodo con su único hijo y lo elimina.
//    - Caso 3: El nodo tiene dos hijos. Encuentra el sucesor en el subárbol derecho (el nodo con la clave mínima),
//      copia su contenido al nodo actual, y elimina el sucesor recursivamente.
// 3. Después de eliminar el nodo, actualiza la altura del nodo actual.
// 4. Calcula el factor de balance del nodo actual para verificar si está balanceado.
// 5. Si el nodo está desbalanceado, aplica las rotaciones necesarias según el caso:
//    - Caso Izquierda Izquierda: Rotación derecha.
//    - Caso Izquierda Derecha: Rotación izquierda en el hijo izquierdo, luego rotación derecha.
//    - Caso Derecha Derecha: Rotación izquierda.
//    - Caso Derecha Izquierda: Rotación derecha en el hijo derecho, luego rotación izquierda.
//
// Notas:
// - Esta función asegura que el árbol AVL permanezca balanceado después de cada eliminación.
// - Las rotaciones mantienen las propiedades del árbol AVL (balance y orden).

Nodo* eliminarPalabra(Nodo* nodo, const string& palabra) {
    if (!nodo) return nodo; // Caso base: el nodo es nulo.

    // Búsqueda normal en el árbol AVL.
    if (palabra < nodo->palabra.espanol)
        nodo->izquierda = eliminarPalabra(nodo->izquierda, palabra); // Buscar en el subárbol izquierdo.
    else if (palabra > nodo->palabra.espanol)
        nodo->derecha = eliminarPalabra(nodo->derecha, palabra); // Buscar en el subárbol derecho.
    else {
        // Nodo encontrado.
        if (!nodo->izquierda || !nodo->derecha) {
            // Caso 1 y Caso 2: El nodo tiene 0 o 1 hijo.
            Nodo* temp = nodo->izquierda ? nodo->izquierda : nodo->derecha;
            if (!temp) {
                // Caso 1: Nodo sin hijos.
                temp = nodo;
                nodo = nullptr;
            }
            else {
                // Caso 2: Nodo con un solo hijo.
                *nodo = *temp; // Reemplazar el nodo actual con su único hijo.
            }
            delete temp; // Eliminar el nodo.
        }
        else {
            // Caso 3: Nodo con dos hijos.
            Nodo* temp = minimo(nodo->derecha); // Encontrar el sucesor (mínimo en el subárbol derecho).
            nodo->palabra = temp->palabra; // Copiar los datos del sucesor al nodo actual.
            nodo->derecha = eliminarPalabra(nodo->derecha, temp->palabra.espanol); // Eliminar el sucesor.
        }
    }

    // Si el árbol está vacío después de la eliminación.
    if (!nodo) return nodo;

    // Actualizar la altura del nodo actual.
    actualizarAltura(nodo);

    // Calcular el factor de balance del nodo actual.
    int balance = factorBalance(nodo);

    // Verificar y corregir el desbalance si es necesario.
    // Caso Izquierda Izquierda
    if (balance > 1 && factorBalance(nodo->izquierda) >= 0)
        return rotarDerecha(nodo);

    // Caso Izquierda Derecha
    if (balance > 1 && factorBalance(nodo->izquierda) < 0) {
        nodo->izquierda = rotarIzquierda(nodo->izquierda);
        return rotarDerecha(nodo);
    }

    // Caso Derecha Derecha
    if (balance < -1 && factorBalance(nodo->derecha) <= 0)
        return rotarIzquierda(nodo);

    // Caso Derecha Izquierda
    if (balance < -1 && factorBalance(nodo->derecha) > 0) {
        nodo->derecha = rotarDerecha(nodo->derecha);
        return rotarIzquierda(nodo);
    }

    return nodo; // Retornar el nodo actual.
}




//==========================FUNCIONES DE COMPRESION==========================



// Estructura para almacenar información de un archivo a comprimir.
// Cada campo representa:
// - rutaRelativa: Ruta del archivo relativa a la carpeta base de compresión.
// - contenido: Vector de caracteres que contiene los datos binarios del archivo.
//
// Uso:
// - Esta estructura se utiliza para recopilar y manipular los archivos que serán comprimidos
//   y descomprimidos mediante el algoritmo de Huffman.

struct ArchivoParaComprimir {
    string rutaRelativa;      // Ruta relativa del archivo respecto a la carpeta base
    vector<char> contenido;   // Contenido binario del archivo
};



// Función para leer completamente un archivo binario y devolver su contenido en un vector de caracteres.
//
// Parámetros:
// - ruta: Ruta completa del archivo que se desea leer.
//
// Retorno:
// - Un vector de caracteres que contiene el contenido binario del archivo.
//   Si el archivo no se puede abrir, retorna un vector vacío.
//
// Notas:
// - Esta función se utiliza para cargar archivos que serán comprimidos o descomprimidos.
// - El archivo se abre en modo binario para preservar todos los datos tal como están en disco.

vector<char> leerArchivo(const string& ruta) {
    ifstream file(ruta, ios::binary);
    if (!file) {
        cerr << "No se pudo abrir archivo: " << ruta << "\n";
        return {};
    }
    return vector<char>((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
}



// Función para guardar el contenido binario en un archivo.
//
// Parámetros:
// - ruta: Ruta completa del archivo donde se desea guardar el contenido.
// - contenido: Vector de caracteres que contiene los datos binarios a guardar.
//
// Proceso:
// 1. Abre el archivo en modo binario para escritura.
// 2. Si no se puede abrir el archivo, muestra un mensaje de error y retorna.
// 3. Escribe el contenido del vector en el archivo.
// 4. Cierra el archivo.
//
// Notas:
// - Esta función se utiliza para restaurar archivos durante la descompresión o para guardar archivos binarios generados.
// - Si el archivo no se puede crear o abrir, no se realiza ninguna acción.

void guardarArchivo(const string& ruta, const vector<char>& contenido) {
    ofstream file(ruta, ios::binary);
    if (!file) {
        cerr << "No se pudo guardar archivo: " << ruta << "\n";
        return;
    }
    file.write(contenido.data(), contenido.size());
}



// Función para recorrer una carpeta de forma recursiva y obtener todos los archivos que contiene,
// almacenando su ruta relativa y su contenido binario en un vector de estructuras.
//
// Parámetros:
// - carpetaBase: Ruta de la carpeta base desde donde se inicia la búsqueda de archivos.
// - archivos: Vector de estructuras ArchivoParaComprimir donde se almacenarán los archivos encontrados.
//
// Proceso:
// 1. Utiliza un iterador recursivo para recorrer todos los archivos dentro de la carpeta base y sus subcarpetas.
// 2. Para cada archivo regular encontrado:
//    - Obtiene la ruta completa del archivo.
//    - Calcula la ruta relativa respecto a la carpeta base.
//    - Lee el contenido binario del archivo usando la función leerArchivo.
//    - Agrega una estructura ArchivoParaComprimir al vector con la ruta relativa y el contenido.
//
// Notas:
// - Solo se procesan archivos regulares (no carpetas).
// - Esta función es utilizada para preparar los archivos antes de la compresión Huffman.

void obtenerArchivos(const string& carpetaBase, vector<ArchivoParaComprimir>& archivos) {
    for (const auto& entry : fs::recursive_directory_iterator(carpetaBase)) {
        if (fs::is_regular_file(entry.path())) {
            string rutaCompleta = entry.path().string();
            string rutaRelativa = fs::relative(entry.path(), carpetaBase).string();
            vector<char> contenido = leerArchivo(rutaCompleta);
            archivos.push_back({ rutaRelativa, contenido });
        }
    }
}



// Función para serializar un conjunto de archivos en un solo buffer binario.
// El formato del buffer es:
// [numArchivos][longRuta][ruta][tamContenido][contenido]...
//
// Parámetros:
// - archivos: Vector de estructuras ArchivoParaComprimir que contiene la ruta relativa y el contenido de cada archivo.
//
// Retorno:
// - Un vector de caracteres que representa el buffer binario serializado con todos los archivos.
//
// Proceso:
// 1. Inserta el número total de archivos al inicio del buffer.
// 2. Para cada archivo:
//    - Inserta la longitud de la ruta relativa.
//    - Inserta la ruta relativa como cadena de caracteres.
//    - Inserta el tamaño del contenido binario.
//    - Inserta el contenido binario del archivo.
//
// Notas:
// - Este buffer puede ser comprimido y almacenado, o deserializado posteriormente para reconstruir los archivos.
// - El formato es compacto y permite reconstruir la estructura de archivos y carpetas original.

vector<char> serializarArchivos(const vector<ArchivoParaComprimir>& archivos) {
    vector<char> buffer;

    int numArchivos = static_cast<int>(archivos.size());
    buffer.insert(buffer.end(), reinterpret_cast<char*>(&numArchivos), reinterpret_cast<char*>(&numArchivos) + sizeof(int));

    for (const auto& archivo : archivos) {
        int lenRuta = static_cast<int>(archivo.rutaRelativa.size());
        buffer.insert(buffer.end(), reinterpret_cast<char*>(&lenRuta), reinterpret_cast<char*>(&lenRuta) + sizeof(int));
        buffer.insert(buffer.end(), archivo.rutaRelativa.begin(), archivo.rutaRelativa.end());

        int tamContenido = static_cast<int>(archivo.contenido.size());
        buffer.insert(buffer.end(), reinterpret_cast<char*>(&tamContenido), reinterpret_cast<char*>(&tamContenido) + sizeof(int));
        buffer.insert(buffer.end(), archivo.contenido.begin(), archivo.contenido.end());
    }
    return buffer;
}



// Función para deserializar un buffer binario y reconstruir los archivos originales en una carpeta destino.
// El buffer debe tener el formato: [numArchivos][longRuta][ruta][tamContenido][contenido]...
//
// Parámetros:
// - buffer: Vector de caracteres que contiene los datos serializados de los archivos.
// - carpetaDestino: Ruta de la carpeta donde se restaurarán los archivos y carpetas.
//
// Proceso:
// 1. Lee el número total de archivos almacenados en el buffer.
// 2. Para cada archivo:
//    - Lee la longitud de la ruta relativa y la ruta relativa.
//    - Lee el tamaño del contenido y el contenido binario.
//    - Crea las carpetas necesarias en la ruta destino.
//    - Guarda el contenido en la ruta correspondiente usando la función guardarArchivo.
//
// Notas:
// - Si el buffer está corrupto o incompleto, lanza una excepción.
// - Esta función se utiliza durante la descompresión para restaurar la estructura original de archivos y carpetas.

void deserializarYReconstruir(const vector<char>& buffer, const string& carpetaDestino) {
    size_t pos = 0;

    auto leerInt = [&](int& val) {
        if (pos + sizeof(int) > buffer.size()) throw runtime_error("Buffer corrupto");
        val = *reinterpret_cast<const int*>(&buffer[pos]);
        pos += sizeof(int);
        };

    int numArchivos = 0;
    leerInt(numArchivos);

    for (int i = 0; i < numArchivos; i++) {
        int lenRuta = 0;
        leerInt(lenRuta);

        if (pos + lenRuta > buffer.size()) throw runtime_error("Buffer corrupto");
        string ruta(buffer.begin() + pos, buffer.begin() + pos + lenRuta);
        pos += lenRuta;

        int tamContenido = 0;
        leerInt(tamContenido);

        if (pos + tamContenido > buffer.size()) throw runtime_error("Buffer corrupto");
        vector<char> contenido(buffer.begin() + pos, buffer.begin() + pos + tamContenido);
        pos += tamContenido;

        // Crear carpetas necesarias
        fs::path rutaCompleta = fs::path(carpetaDestino) / ruta;
        fs::create_directories(rutaCompleta.parent_path());

        // Guardar archivo
        guardarArchivo(rutaCompleta.string(), contenido);
    }
}



// Estructura para representar un nodo del árbol de Huffman utilizado en la compresión de archivos.
// Cada nodo puede ser una hoja (carácter y frecuencia) o un nodo interno (suma de frecuencias).
//
// Campos:
// - c: Carácter representado por el nodo (solo válido en hojas; '\0' en nodos internos).
// - freq: Frecuencia total de aparición del carácter o suma de frecuencias de los hijos.
// - izq: Puntero al hijo izquierdo del nodo Huffman.
// - der: Puntero al hijo derecho del nodo Huffman.
//
// Constructores:
// - NodoHuffman(char c, int freq): Crea una hoja con un carácter y su frecuencia.
// - NodoHuffman(NodoHuffman* izq, NodoHuffman* der): Crea un nodo interno a partir de dos hijos.
//
// Uso:
// - Esta estructura se utiliza para construir el árbol de Huffman necesario para la codificación y decodificación de datos binarios.

struct NodoHuffman {
    char c;                // Carácter (solo válido en hojas)
    int freq;              // Frecuencia del carácter o suma de frecuencias
    NodoHuffman* izq;      // Puntero al hijo izquierdo
    NodoHuffman* der;      // Puntero al hijo derecho

    NodoHuffman(char c, int freq) : c(c), freq(freq), izq(nullptr), der(nullptr) {}
    NodoHuffman(NodoHuffman* izq, NodoHuffman* der)
        : c('\0'), freq(izq->freq + der->freq), izq(izq), der(der) {
    }
};



// Estructura comparadora para nodos de Huffman utilizada en la priority_queue.
// Compara dos punteros a NodoHuffman según su frecuencia (freq).
// El nodo con menor frecuencia tendrá mayor prioridad (menor freq sale primero).
//
// Uso:
// - Esta estructura se utiliza como comparador en la cola de prioridad (priority_queue)
//   para construir el árbol de Huffman de manera eficiente.

struct CompareNodo {
    bool operator()(NodoHuffman* a, NodoHuffman* b) {
        return a->freq > b->freq;
    }
};



// Función para construir el árbol de Huffman a partir de un mapa de frecuencias de caracteres.
// Utiliza una cola de prioridad (priority_queue) para combinar los nodos de menor frecuencia.
//
// Parámetros:
// - freq: Mapa que asocia cada carácter con su frecuencia de aparición.
//
// Retorno:
// - Un puntero a la raíz del árbol de Huffman construido.
//
// Proceso:
// 1. Crea un nodo hoja para cada carácter y lo inserta en la cola de prioridad.
// 2. Mientras haya más de un nodo en la cola:
//    - Extrae los dos nodos con menor frecuencia.
//    - Crea un nuevo nodo interno con estos dos nodos como hijos y la suma de sus frecuencias.
//    - Inserta el nuevo nodo en la cola.
// 3. El nodo restante en la cola es la raíz del árbol de Huffman.
//
// Notas:
// - El árbol de Huffman se utiliza para la compresión y descompresión eficiente de datos binarios.

NodoHuffman* construirArbol(const map<char, int>& freq) {
    priority_queue<NodoHuffman*, vector<NodoHuffman*>, CompareNodo> pq;
    for (auto& p : freq) {
        pq.push(new NodoHuffman(p.first, p.second));
    }
    while (pq.size() > 1) {
        NodoHuffman* a = pq.top(); pq.pop();
        NodoHuffman* b = pq.top(); pq.pop();
        pq.push(new NodoHuffman(a, b));
    }
    return pq.top();
}



// Función para construir la tabla de códigos Huffman a partir del árbol de Huffman.
// Asigna a cada carácter una cadena de bits única según el recorrido del árbol.
//
// Parámetros:
// - nodo: Puntero al nodo actual del árbol de Huffman.
// - codigo: Cadena que representa el código binario acumulado hasta el nodo actual.
// - tabla: Mapa donde se almacenarán los códigos Huffman generados para cada carácter.
//
// Proceso:
// 1. Si el nodo es nulo, retorna (caso base).
// 2. Si el nodo es una hoja (no tiene hijos), asigna el código acumulado al carácter del nodo.
// 3. Llama recursivamente para el hijo izquierdo agregando '0' al código.
// 4. Llama recursivamente para el hijo derecho agregando '1' al código.
//
// Notas:
// - Esta función se utiliza para generar los códigos Huffman necesarios para la compresión y descompresión de datos.

void construirCodigos(NodoHuffman* nodo, const string& codigo, map<char, string>& tabla) {
    if (!nodo) return;
    if (!nodo->izq && !nodo->der) { // Es una hoja
        tabla[nodo->c] = codigo;
    }
    construirCodigos(nodo->izq, codigo + "0", tabla);
    construirCodigos(nodo->der, codigo + "1", tabla);
}



// Función para liberar la memoria utilizada por un árbol binario (como el árbol de Huffman).
//
// Parámetros:
// - nodo: Puntero al nodo raíz del árbol a liberar.
//
// Proceso:
// 1. Llama recursivamente a la función para liberar el subárbol izquierdo.
// 2. Llama recursivamente a la función para liberar el subárbol derecho.
// 3. Elimina el nodo actual.
//
// Notas:
// - Es importante llamar a esta función para evitar fugas de memoria cuando se termina de usar el árbol.

void liberarArbol(NodoHuffman* nodo) {
    if (!nodo) return;
    liberarArbol(nodo->izq);
    liberarArbol(nodo->der);
    delete nodo;
}



// Función para comprimir un buffer de datos utilizando el algoritmo de Huffman y guardar el resultado en un archivo binario.
//
// Parámetros:
// - buffer: Vector de caracteres que contiene los datos originales a comprimir.
// - archivoSalida: Ruta del archivo donde se guardará el resultado comprimido.
//
// Proceso:
// 1. Cuenta la frecuencia de cada carácter en el buffer.
// 2. Construye el árbol de Huffman a partir del mapa de frecuencias.
// 3. Genera la tabla de códigos Huffman para cada carácter.
// 4. Abre el archivo de salida en modo binario.
// 5. Escribe la tabla de códigos en el archivo (número de entradas, cada carácter, tamaño y código).
// 6. Codifica el buffer original en una cadena de bits usando la tabla de códigos.
// 7. Escribe la cantidad de bits codificados y empaqueta los bits en bytes para almacenarlos en el archivo.
// 8. Libera la memoria del árbol de Huffman.
//
// Notas:
// - Si el archivo no se puede abrir para escritura, muestra un mensaje de error y no realiza la compresión.
// - El archivo generado puede ser descomprimido usando la función correspondiente que lee la tabla y decodifica los bits.

void comprimirBufferConHuffman(const vector<char>& buffer, const string& archivoSalida) {
    // Contar frecuencias de cada carácter en el buffer
    map<char, int> freq;
    for (char c : buffer) freq[c]++;

    // Construir el árbol de Huffman
    NodoHuffman* raiz = construirArbol(freq);

    // Generar la tabla de códigos Huffman
    map<char, string> codigos;
    construirCodigos(raiz, "", codigos);

    // Abrir el archivo de salida en modo binario
    ofstream ofs(archivoSalida, ios::binary);
    if (!ofs.is_open()) {
        cerr << "No se pudo crear archivo para comprimir\n";
        liberarArbol(raiz);
        return;
    }

    // Guardar el tamaño de la tabla de códigos
    int tamTabla = static_cast<int>(codigos.size());
    ofs.write(reinterpret_cast<const char*>(&tamTabla), sizeof(int));

    // Guardar la tabla de códigos: [char][int tamaño código][string código]
    for (auto& p : codigos) {
        ofs.write(&p.first, sizeof(char));
        int tamCod = static_cast<int>(p.second.size());
        ofs.write(reinterpret_cast<const char*>(&tamCod), sizeof(int));
        ofs.write(p.second.c_str(), tamCod);
    }

    // Codificar el buffer original en una cadena de bits
    string bitsCodificados;
    for (char c : buffer) bitsCodificados += codigos[c];

    // Escribir la cantidad de bits codificados
    int bitCount = static_cast<int>(bitsCodificados.size());
    ofs.write(reinterpret_cast<const char*>(&bitCount), sizeof(int));

    // Empaquetar los bits en bytes y escribirlos en el archivo
    for (size_t i = 0; i < bitsCodificados.size(); i += 8) {
        char byte = 0;
        for (int j = 0; j < 8 && i + j < bitsCodificados.size(); ++j) {
            if (bitsCodificados[i + j] == '1') {
                byte |= (1 << (7 - j));
            }
        }
        ofs.write(&byte, sizeof(char));
    }

    ofs.close();
    liberarArbol(raiz);
}



// Función para leer la tabla de códigos Huffman desde un archivo binario y reconstruir el mapa de decodificación.
//
// Parámetros:
// - ifs: Flujo de entrada de archivo binario abierto en modo lectura.
// - tablaReversa: Mapa donde se almacenarán los códigos Huffman como clave y el carácter correspondiente como valor.
//
// Proceso:
// 1. Lee el número de entradas de la tabla de códigos (int).
// 2. Para cada entrada:
//    - Lee el carácter asociado (char).
//    - Lee el tamaño del código (int).
//    - Lee el código Huffman (string de tamaño tamCod).
//    - Almacena el par (código, carácter) en el mapa tablaReversa.
//
// Notas:
// - Esta función se utiliza durante la descompresión para reconstruir la tabla de decodificación Huffman.
// - El formato debe coincidir exactamente con el utilizado al guardar la tabla en la compresión.

void leerTabla(ifstream& ifs, map<string, char>& tablaReversa) {
    int tamTabla;
    ifs.read(reinterpret_cast<char*>(&tamTabla), sizeof(int));

    for (int i = 0; i < tamTabla; i++) {
        char c;
        ifs.read(&c, sizeof(char));
        int tamCod;
        ifs.read(reinterpret_cast<char*>(&tamCod), sizeof(int));
        string codigo(tamCod, ' ');
        ifs.read(&codigo[0], tamCod);
        tablaReversa[codigo] = c;
    }
}



// Función para descomprimir un archivo comprimido con Huffman y devolver el buffer original.
//
// Parámetros:
// - archivoEntrada: Ruta del archivo .huff comprimido.
//
// Retorno:
// - Un vector de caracteres con el contenido original descomprimido.
//   Si ocurre un error al abrir o leer el archivo, retorna un vector vacío.
//
// Proceso:
// 1. Abre el archivo en modo binario.
// 2. Lee la tabla de códigos Huffman invertida (código -> carácter).
// 3. Lee la cantidad de bits codificados y los bytes codificados.
// 4. Decodifica los bits usando la tabla para reconstruir el buffer original.
//
// Notas:
// - Esta función es utilizada por descomprimirCarpetaHuffman para restaurar archivos comprimidos.

vector<char> descomprimirArchivoHuffman(const string& archivoEntrada) {
    ifstream ifs(archivoEntrada, ios::binary);
    if (!ifs.is_open()) {
        cerr << "No se pudo abrir archivo para descomprimir\n";
        return {};
    }

    // Leer tabla reversa
    map<string, char> tablaReversa;
    leerTabla(ifs, tablaReversa);

    // Leer cantidad de bits codificados
    int bitCount = 0;
    ifs.read(reinterpret_cast<char*>(&bitCount), sizeof(int));

    // Leer bytes codificados
    int byteCount = (bitCount + 7) / 8;
    vector<char> bytesCodificados(byteCount);
    ifs.read(bytesCodificados.data(), byteCount);

    // Decodificar bits
    string codigoActual;
    vector<char> bufferOriginal;
    for (int i = 0; i < bitCount; i++) {
        int byteIndex = i / 8;
        int bitIndex = 7 - (i % 8);
        bool bit = (bytesCodificados[byteIndex] & (1 << bitIndex)) != 0;
        codigoActual += bit ? '1' : '0';

        if (tablaReversa.find(codigoActual) != tablaReversa.end()) {
            bufferOriginal.push_back(tablaReversa[codigoActual]);
            codigoActual.clear();
        }
    }

    ifs.close();
    return bufferOriginal;
}



// Función para eliminar todos los archivos y carpetas dentro de una carpeta,
// excepto un archivo específico (por ejemplo, el archivo .huff).
//
// Parámetros:
// - rutaCarpeta: Ruta de la carpeta donde se eliminará el contenido.
// - nombreArchivoHuff: Nombre del archivo que NO debe eliminarse (por ejemplo, "traductor.huff").
//
// Proceso:
// 1. Recorre todos los archivos y subcarpetas dentro de la carpeta especificada.
// 2. Si el nombre del archivo es igual al archivo que se debe conservar, lo omite.
// 3. Elimina recursivamente todos los demás archivos y carpetas.
//
// Notas:
// - Esta función es útil para limpiar la carpeta antes de descomprimir archivos,
//   asegurando que solo se conserve el archivo comprimido .huff.

void eliminarContenidoExceptoHuff(const string& rutaCarpeta, const string& nombreArchivoHuff) {
    for (const auto& entry : fs::directory_iterator(rutaCarpeta)) {
        if (entry.path().filename() == nombreArchivoHuff) continue;
        fs::remove_all(entry.path());
    }
}



// Función principal para comprimir el contenido de una carpeta utilizando Huffman.
//
// Parámetros:
// - rutaCarpeta: Ruta de la carpeta cuyo contenido se desea comprimir.
// - rutaArchivoDestino: Ruta donde se guardará el archivo comprimido (.huff).
//
// Proceso:
// 1. Obtiene todos los archivos de la carpeta y subcarpetas (excepto el archivo .huff si existe).
// 2. Serializa los archivos en un solo buffer binario.
// 3. Si el buffer está vacío, muestra una advertencia y no realiza la compresión.
// 4. Comprime el buffer utilizando el algoritmo de Huffman y guarda el resultado en el archivo destino.
//
// Notas:
// - Esta función es llamada antes de salir del programa para respaldar el estado de la carpeta.
// - El archivo .huff se excluye para evitar auto-incluirse en la compresión.

void comprimirCarpetaHuffman(const string& rutaCarpeta, const string& rutaArchivoDestino) {
    vector<ArchivoParaComprimir> archivos;
    obtenerArchivos(rutaCarpeta, archivos);

    // Excluir el archivo .huff existente
    archivos.erase(remove_if(archivos.begin(), archivos.end(), [&](const ArchivoParaComprimir& a) {
        return a.rutaRelativa == "traductor.huff";
        }), archivos.end());

    vector<char> buffer = serializarArchivos(archivos);

    if (buffer.empty()) {
        cerr << "Advertencia: El buffer está vacío. No se comprimirá nada.\n";
        return;
    }

    comprimirBufferConHuffman(buffer, rutaArchivoDestino);
}



// Función principal para descomprimir el contenido de una carpeta a partir de un archivo comprimido con Huffman.
//
// Parámetros:
// - rutaCarpeta: Ruta de la carpeta donde se restaurarán los archivos descomprimidos.
// - archivoHuff: Ruta del archivo comprimido (.huff) que contiene los datos serializados y comprimidos.
//
// Proceso:
// 1. Descomprime el archivo .huff y obtiene el buffer binario original.
// 2. Si el buffer está vacío o ocurre un error, muestra un mensaje y no realiza la restauración.
// 3. Antes de restaurar, elimina todo el contenido de la carpeta excepto el archivo .huff (si estuviera en la misma carpeta).
// 4. Deserializa el buffer y reconstruye los archivos y carpetas originales en la ruta especificada.
//
// Notas:
// - Esta función es llamada al inicio del programa si existe un archivo .huff para restaurar el estado anterior.
// - Si el archivo .huff está en una carpeta separada, la exclusión del .huff es innecesaria pero no afecta el resultado.

void descomprimirCarpetaHuffman(const string& rutaCarpeta, const string& archivoHuff) {
    vector<char> buffer = descomprimirArchivoHuffman(archivoHuff);
    if (buffer.empty()) {
        cerr << "No se pudo descomprimir el archivo o está vacío\n";
        return;
    }

    // Antes de restaurar, eliminar todo excepto el archivo .huff
    eliminarContenidoExceptoHuff(rutaCarpeta, "traductor.huff");

    // Reconstruir archivos
    deserializarYReconstruir(buffer, rutaCarpeta);
}



// Función para eliminar todos los archivos y subcarpetas dentro de una carpeta especificada.
//
// Parámetros:
// - rutaCarpeta: Ruta de la carpeta cuyo contenido se desea eliminar.
//
// Proceso:
// 1. Recorre todos los archivos y subcarpetas dentro de la carpeta especificada usando un iterador de directorio.
// 2. Para cada entrada encontrada (archivo o carpeta), intenta eliminarla recursivamente usando fs::remove_all.
// 3. Si ocurre un error al eliminar algún archivo o carpeta, muestra un mensaje de error con detalles.
//
// Notas:
// - Esta función elimina todo el contenido de la carpeta, pero no elimina la carpeta en sí.
// - Es útil para limpiar completamente una carpeta antes de restaurar o comprimir su contenido.
// - Utiliza manejo de excepciones para evitar que el programa termine si ocurre un error de sistema de archivos.

void eliminarCarpetaContenido(const string& rutaCarpeta) {
    for (auto& entry : fs::directory_iterator(rutaCarpeta)) {
        try {
            fs::remove_all(entry.path());  // Elimina archivos o carpetas recursivamente
        }
        catch (const fs::filesystem_error& e) {
            cerr << "Error al eliminar " << entry.path() << ": " << e.what() << '\n';
        }
    }
}




//==========================FUNCIONES DEL TRADUCTOR==========================



// Función para buscar una palabra en el árbol AVL, mostrar su traducción en el idioma seleccionado
// y guardar la palabra buscada en los archivos correspondientes.
//
// Parámetros:
// - raiz: Puntero al nodo raíz del árbol AVL que contiene las palabras y sus traducciones.
// - rutaUsuario: Ruta de la carpeta del usuario actual, donde se almacenan los archivos.
//
// Proceso:
// 1. Solicita al usuario una palabra en español para buscar en el árbol AVL.
// 2. Si la palabra existe, permite seleccionar un idioma para mostrar la traducción.
// 3. Reproduce la traducción en forma de audio utilizando PowerShell.
// 4. Guarda la palabra buscada en dos archivos:
//    - `conversion.umg`: La palabra encriptada y procesada con XOR.
//    - `informacion_original.umg`: La palabra original.
//
// Notas:
// - Si la palabra no se encuentra en el árbol, muestra un mensaje de error.
// - Utiliza las funciones `encriptarPalabra` y `aplicarXOR` para proteger los datos antes de guardarlos.
// - La reproducción de audio requiere que PowerShell esté disponible en el sistema.

void mostrarTraduccion(Nodo* raiz, const string& rutaUsuario) {
    string palabraBuscada;
    int idioma;

    // Solicitar al usuario la palabra en español que desea buscar.
    cout << "\nIngrese una palabra en espanol: ";
    cin >> palabraBuscada;

    // Buscar la palabra en el árbol AVL.
    Nodo* nodo = buscar(raiz, palabraBuscada);
    if (!nodo) {
        cout << "Palabra no encontrada.\n";
        return;
    }

    // Solicitar al usuario que seleccione un idioma para la traducción.
    cout << "Seleccione el idioma:\n";
    cout << "1. Ingles\n2. Aleman\n3. Frances\n4. Italiano\n";
    cout << "Opcion: ";
    cin >> idioma;

    string traduccion;
    cout << "Traduccion: ";
    switch (idioma) {
    case 1:
        traduccion = nodo->palabra.ingles;
        cout << traduccion;
        break;
    case 2:
        traduccion = nodo->palabra.aleman;
        cout << traduccion;
        break;
    case 3:
        traduccion = nodo->palabra.frances;
        cout << traduccion;
        break;
    case 4:
        traduccion = nodo->palabra.italiano;
        cout << traduccion;
        break;
    default:
        cout << "Opcion no valida.";
        return;
    }
    cout << endl;

    // Reproducir la traducción en forma de audio utilizando PowerShell.
    string comando = "powershell -Command \"Add-Type -AssemblyName System.Speech; "
        "$speak = New-Object System.Speech.Synthesis.SpeechSynthesizer; "
        "$speak.Speak('" + traduccion + "');\"";
    system(comando.c_str());

    // Encriptar la palabra buscada.
    string palabraEncriptada = encriptarPalabra(palabraBuscada);

    // Leer la llave desde el archivo del usuario.
    ifstream llaveFile(rutaUsuario + "\\llave.umg");
    string llave;
    getline(llaveFile, llave);
    llaveFile.close();

    // Aplicar XOR sobre la palabra encriptada con la llave.
    string palabraFinal = aplicarXOR(palabraEncriptada, llave);

    // Guardar la palabra encriptada con XOR en el archivo `conversion.umg`.
    ofstream archivoConversion(rutaUsuario + "\\conversion.umg", ios::app);
    if (archivoConversion.is_open()) {
        archivoConversion << palabraFinal << endl;
        archivoConversion.close();
    }
    else {
        cerr << "Error al abrir conversion.umg para escritura.\n";
    }

    // Guardar la palabra original en el archivo `informacion_original.umg`.
    ofstream archivoOriginal(rutaUsuario + "\\informacion_original.umg", ios::app);
    if (archivoOriginal.is_open()) {
        archivoOriginal << palabraBuscada << endl;
        archivoOriginal.close();
    }
    else {
        cerr << "Error al abrir informacion_original.umg para escritura.\n";
    }
}



// Función para mostrar el historial de palabras buscadas por el usuario.
// Las palabras se desencriptan y se muestran en su forma original.
//
// Parámetros:
// - rutaUsuario: Ruta de la carpeta del usuario actual, donde se encuentra el archivo `conversion.umg`.
//
// Proceso:
// 1. Abre el archivo `conversion.umg` que contiene las palabras encriptadas con XOR.
// 2. Lee la llave del archivo `llave.umg` para desencriptar las palabras.
// 3. Para cada palabra encriptada:
//    - Aplica la operación XOR para revertir la encriptación.
//    - Desencripta la palabra utilizando la tabla de desencriptación.
//    - Muestra la palabra original.
//
// Notas:
// - Si el archivo `conversion.umg` no existe o no se puede abrir, muestra un mensaje de error.
// - Utiliza las funciones `deshacerXOR` y `desencriptarPalabra` para procesar las palabras.
// - La llave debe coincidir con la utilizada para encriptar las palabras, de lo contrario, el resultado será incorrecto.

void mostrarHistorial(const string& rutaUsuario) {
    string rutaArchivo = rutaUsuario + "\\conversion.umg";
    ifstream archivo(rutaArchivo);
    if (!archivo.is_open()) {
        cerr << "Error al abrir conversion.umg para lectura.\n";
        return;
    }

    // Leer la llave desde el archivo del usuario.
    ifstream llaveFile(rutaUsuario + "\\llave.umg");
    string llave;
    getline(llaveFile, llave);
    llaveFile.close();

    cout << "\n--- HISTORIAL DE PALABRAS BUSCADAS ---\n";
    string palabraEncriptada;

    // Procesar cada palabra encriptada en el archivo.
    while (getline(archivo, palabraEncriptada)) {
        // Deshacer el XOR primero para revertir la encriptación.
        string palabraConXORDeshecho = deshacerXOR(palabraEncriptada, llave);
        // Desencriptar la palabra utilizando la tabla de desencriptación.
        string palabraOriginal = desencriptarPalabra(palabraConXORDeshecho);
        // Mostrar la palabra original.
        cout << palabraOriginal << endl;
    }

    archivo.close();
}



// Función para mostrar el ranking de palabras más buscadas por el usuario.
// Las palabras se desencriptan, se cuentan sus frecuencias y se ordenan en orden descendente.
//
// Parámetros:
// - rutaUsuario: Ruta de la carpeta del usuario actual, donde se encuentra el archivo `conversion.umg`.
//
// Proceso:
// 1. Abre el archivo `conversion.umg` que contiene las palabras encriptadas con XOR.
// 2. Lee la llave del archivo `llave.umg` para desencriptar las palabras.
// 3. Para cada palabra encriptada:
//    - Aplica la operación XOR para revertir la encriptación.
//    - Desencripta la palabra utilizando la tabla de desencriptación.
//    - Incrementa el contador de frecuencia de la palabra en un mapa.
// 4. Convierte el mapa de frecuencias en un vector de pares clave-valor.
// 5. Ordena el vector en orden descendente según la frecuencia de las palabras.
// 6. Muestra el ranking de palabras más buscadas en la consola.
//
// Notas:
// - Si el archivo `conversion.umg` no existe o no se puede abrir, muestra un mensaje de error.
// - Utiliza las funciones `deshacerXOR` y `desencriptarPalabra` para procesar las palabras.
// - La llave debe coincidir con la utilizada para encriptar las palabras, de lo contrario, el resultado será incorrecto.

void mostrarRanking(const string& rutaUsuario) {
    string rutaArchivo = rutaUsuario + "\\conversion.umg";
    ifstream archivo(rutaArchivo);
    if (!archivo.is_open()) {
        cerr << "Error al abrir conversion.umg para lectura.\n";
        return;
    }

    // Leer la llave desde el archivo del usuario.
    ifstream llaveFile(rutaUsuario + "\\llave.umg");
    string llave;
    getline(llaveFile, llave);
    llaveFile.close();

    // Mapa para contar la frecuencia de cada palabra desencriptada.
    map<string, int> frecuenciaPalabras;
    string palabraEncriptada;

    // Procesar cada palabra encriptada en el archivo.
    while (getline(archivo, palabraEncriptada)) {
        // Deshacer el XOR primero para revertir la encriptación.
        string palabraConXORDeshecho = deshacerXOR(palabraEncriptada, llave);
        // Desencriptar la palabra utilizando la tabla de desencriptación.
        string palabraOriginal = desencriptarPalabra(palabraConXORDeshecho);
        // Incrementar la frecuencia de la palabra en el mapa.
        frecuenciaPalabras[palabraOriginal]++;
    }

    archivo.close();

    // Convertir el mapa a un vector de pares para ordenar.
    vector<pair<string, int>> ranking(frecuenciaPalabras.begin(), frecuenciaPalabras.end());

    // Ordenar el vector por frecuencia en orden descendente.
    sort(ranking.begin(), ranking.end(), [](const pair<string, int>& a, const pair<string, int>& b) {
        return a.second > b.second;
        });

    // Mostrar el ranking de palabras más buscadas.
    cout << "\n--- RANKING DE PALABRAS MÁS BUSCADAS ---\n";
    for (const auto& par : ranking) {
        cout << par.first << ": " << par.second << " veces\n";
    }
}



// Función para guardar el contenido del árbol AVL en un archivo utilizando un recorrido inorden.
// El recorrido inorden asegura que las palabras se guarden en orden alfabético.
//
// Parámetros:
// - nodo: Puntero al nodo actual del árbol AVL que se está procesando.
// - archivoOut: Flujo de salida hacia el archivo donde se guardarán las palabras.
//
// Proceso:
// 1. Si el nodo actual es nulo, retorna (caso base de la recursión).
// 2. Llama recursivamente a la función para procesar el subárbol izquierdo.
// 3. Escribe la palabra y sus traducciones en el archivo en formato CSV (separadas por comas).
// 4. Llama recursivamente a la función para procesar el subárbol derecho.
//
// Notas:
// - El archivo debe estar abierto antes de llamar a esta función.
// - Cada línea del archivo contiene una palabra en español y sus traducciones en otros idiomas.

void guardarEnArchivo(Nodo* nodo, ofstream& archivoOut) {
    if (!nodo) return; // Caso base: si el nodo es nulo, no hace nada.

    // Recorrer el subárbol izquierdo.
    guardarEnArchivo(nodo->izquierda, archivoOut);

    // Escribir la palabra y sus traducciones en el archivo.
    archivoOut << nodo->palabra.espanol << "," << nodo->palabra.ingles << ","
        << nodo->palabra.aleman << "," << nodo->palabra.frances << ","
        << nodo->palabra.italiano << endl;

    // Recorrer el subárbol derecho.
    guardarEnArchivo(nodo->derecha, archivoOut);
}




//==========================FUNCIONES DE LOGIN==========================



// Función para autenticar a un usuario utilizando un archivo de usuarios encriptados.
//
// Parámetros:
// - usuarioActual: Referencia a una cadena donde se almacenará el nombre del usuario autenticado.
//
// Proceso:
// 1. Solicita al usuario que ingrese su nombre de usuario y clave.
// 2. Abre el archivo `usuarios.umg` que contiene los nombres de usuario y claves encriptados.
// 3. Para cada línea del archivo:
//    - Desencripta el nombre de usuario y la clave utilizando la función `desencriptarPalabra`.
//    - Compara los datos desencriptados con los ingresados por el usuario.
// 4. Si se encuentra una coincidencia:
//    - Almacena el nombre de usuario desencriptado en `usuarioActual`.
//    - Retorna `true` indicando que la autenticación fue exitosa.
// 5. Si no se encuentra coincidencia, retorna `false`.
//
// Notas:
// - Si el archivo `usuarios.umg` no existe o no se puede abrir, muestra un mensaje de error y retorna `false`.
// - La función utiliza encriptación y desencriptación para proteger los datos sensibles de los usuarios.

bool login(string& usuarioActual) {
    string usuario, clave;
    cout << "Usuario: ";
    cin >> usuario;
    cout << "Clave: ";
    cin >> clave;

    // Abrir el archivo de usuarios encriptados.
    ifstream archivo("C:\\traductor\\usuarios.umg");
    if (!archivo.is_open()) {
        cerr << "Error al abrir archivo de usuarios.\n";
        return false;
    }

    string linea;
    // Leer cada línea del archivo.
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string uEncriptado, cEncriptado;
        // Dividir la línea en nombre de usuario y clave encriptados.
        if (getline(ss, uEncriptado, ',') && getline(ss, cEncriptado, ',')) {
            // Desencriptar el usuario y la clave.
            string uDesencriptado = desencriptarPalabra(uEncriptado);
            string cDesencriptado = desencriptarPalabra(cEncriptado);

            // Comparar con los datos ingresados.
            if (uDesencriptado == usuario && cDesencriptado == clave) {
                usuarioActual = uDesencriptado; // Guardar el nombre de usuario desencriptado.
                return true; // Autenticación exitosa.
            }
        }
    }

    return false; // Si no se encuentra coincidencia.
}



// Función para registrar un nuevo usuario en el sistema.
// El nombre de usuario y la clave se encriptan y se almacenan en un archivo.
// Además, se crea una carpeta específica para el usuario con archivos iniciales.
//
// Proceso:
// 1. Solicita al usuario que ingrese un nombre de usuario y una clave.
// 2. Verifica si el nombre de usuario ya existe en el archivo `usuarios.umg`.
//    - Si ya existe, muestra un mensaje de error y finaliza el registro.
// 3. Encripta el nombre de usuario y la clave utilizando la función `encriptarPalabra`.
// 4. Almacena el nombre de usuario y la clave encriptados en el archivo `usuarios.umg`.
// 5. Crea una carpeta específica para el usuario en `C:\\traductor\\usuarios\\`.
// 6. Genera una llave única para el usuario utilizando la operación XOR y la almacena en un archivo.
// 7. Crea archivos iniciales vacíos (`conversion.umg` y `informacion_original.umg`) en la carpeta del usuario.
//
// Notas:
// - Si el archivo `usuarios.umg` no existe o no se puede abrir, muestra un mensaje de error.
// - La llave generada se utiliza para encriptar y desencriptar datos específicos del usuario.
// - La función utiliza encriptación para proteger los datos sensibles de los usuarios.

void registrarUsuario() {
    string nuevoUsuario, nuevaClave;

    cout << "\n--- REGISTRO DE NUEVO USUARIO ---\n";
    cout << "Ingrese nombre de usuario: ";
    cin >> nuevoUsuario;
    cout << "Ingrese clave: ";
    cin >> nuevaClave;

    // Verificar si el usuario ya existe en el archivo `usuarios.umg`.
    ifstream archivoIn("C:\\traductor\\usuarios.umg");
    string linea;
    while (getline(archivoIn, linea)) {
        stringstream ss(linea);
        string u, c;
        if (getline(ss, u, ',') && getline(ss, c, ',')) {
            if (desencriptarPalabra(u) == nuevoUsuario) { // Desencriptar para comparar.
                cout << "El usuario ya existe. Intente con otro nombre.\n";
                return;
            }
        }
    }
    archivoIn.close();

    // Encriptar el nombre de usuario y la clave.
    string usuarioEncriptado = encriptarPalabra(nuevoUsuario);
    string claveEncriptada = encriptarPalabra(nuevaClave);

    // Guardar el nuevo usuario en el archivo `usuarios.umg`.
    ofstream archivoOut("C:\\traductor\\usuarios.umg", ios::app);
    if (!archivoOut.is_open()) {
        cerr << "Error al abrir el archivo de usuarios.\n";
        return;
    }
    archivoOut << usuarioEncriptado << "," << claveEncriptada << endl;
    archivoOut.close();

    // Crear la carpeta del usuario.
    string rutaUsuario = "C:\\traductor\\usuarios\\" + nuevoUsuario;
    _mkdir(rutaUsuario.c_str()); // Crear carpeta.

    // Generar una llave única utilizando XOR.
    string semilla = "umg"; // Semilla fija para generar la llave.
    string llave = "";
    for (size_t i = 0; i < nuevoUsuario.size(); ++i) {
        llave += nuevoUsuario[i] ^ semilla[i % semilla.size()];
    }

    // Guardar la llave en un archivo con la extensión `.umg`.
    ofstream llaveFile(rutaUsuario + "\\llave.umg");
    if (llaveFile.is_open()) {
        llaveFile << llave << endl;
        llaveFile.close();
    }
    else {
        cerr << "Error al crear el archivo de llave.\n";
    }

    // Crear los archivos iniciales vacíos en la carpeta del usuario.
    ofstream conversionFile(rutaUsuario + "\\conversion.umg");
    conversionFile.close(); // Crear archivo vacío.

    ofstream infoFile(rutaUsuario + "\\informacion_original.umg");
    infoFile.close(); // Crear archivo vacío.

    cout << "Usuario registrado con éxito.\n"; 
}




//==========================FUNCIONES PRINCIPALES==========================



// Función principal del programa.
// Controla el flujo general: descompresión inicial, autenticación, menú principal y compresión final.
//
// Proceso general:
// 1. Si existe un archivo comprimido (.huff), descomprime la carpeta de trabajo al iniciar.
// 2. Solicita al usuario iniciar sesión o registrarse hasta que la autenticación sea exitosa.
// 3. Carga las palabras al árbol AVL desde el archivo principal de palabras.
// 4. Muestra un menú con opciones para buscar, agregar, eliminar palabras, ver historial y ranking.
// 5. Al salir, comprime el contenido de la carpeta y elimina los archivos originales para mantener solo el respaldo comprimido.

int main() {
    // Rutas principales para la compresión y descompresión
    const string rutaCarpetaHuffman = "C:\\traductorhuffman";
    const string archivoHuff = rutaCarpetaHuffman + "\\traductor.huff";
    const string rutaCarpeta = "C:\\traductor";

    // 1. Descomprimir al inicio si existe el archivo comprimido
    if (fs::exists(archivoHuff)) {
        descomprimirCarpetaHuffman(rutaCarpeta, archivoHuff);
    }

    string usuarioActual;
    int opcionInicio;

    // 2. Mostrar mensaje de bienvenida y manejar autenticación
    cout << "--- BIENVENIDO AL TRADUCTOR ---\n";
    while (true) {
        cout << "1. Iniciar sesión\n";
        cout << "2. Registrarse\n";
        cout << "Seleccione una opción: ";
        cin >> opcionInicio;

        if (opcionInicio == 2) {
            registrarUsuario(); // Permite registrar un nuevo usuario
        }

        if (login(usuarioActual)) { // Intenta iniciar sesión
            cout << "Bienvenido, " << usuarioActual << "!\n";
            break; // Sale del bucle si la autenticación es exitosa
        }
        else {
            cout << "Credenciales inválidas. Intente de nuevo.\n";
        }
    }

    // 3. Definir la ruta de la carpeta del usuario autenticado
    string rutaUsuario = "C:\\traductor\\usuarios\\" + usuarioActual;

    // 4. Cargar las palabras al árbol AVL desde el archivo principal
    Nodo* raiz = cargarPalabras();

    int opcion;
    // 5. Bucle principal del menú de usuario
    do {
        cout << "\n--- MENU ---\n";
        cout << "1. Buscar una palabra\n";
        cout << "2. Agregar una nueva palabra\n";
        cout << "3. Eliminar una palabra\n";
        cout << "4. Mostrar historial de palabras buscadas\n";
        cout << "5. Mostrar ranking de palabras más buscadas\n";
        cout << "6. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        // Ejecutar la opción seleccionada
        if (opcion == 1) {
            mostrarTraduccion(raiz, rutaUsuario); // Buscar y traducir una palabra
        }
        else if (opcion == 2) {
            raiz = agregarPalabra(raiz, "C:\\traductor\\palabras.umg"); // Agregar una nueva palabra
        }
        else if (opcion == 3) {
            string palabra;
            cout << "Ingrese la palabra en espanol que desea eliminar: ";
            cin >> palabra;

            raiz = eliminarPalabra(raiz, palabra); // Eliminar una palabra del árbol

            // Reescribir el archivo de palabras tras la eliminación
            ofstream archivoOut("C:\\traductor\\palabras.umg");
            if (!archivoOut.is_open()) {
                cerr << "Error al abrir el archivo para reescribir.\n";
            }
            else {
                guardarEnArchivo(raiz, archivoOut);
                archivoOut.close();
                cout << "Palabra eliminada y archivo actualizado.\n";
            }
        }
        else if (opcion == 4) {
            mostrarHistorial(rutaUsuario); // Mostrar historial de palabras buscadas
        }
        else if (opcion == 5) {
            mostrarRanking(rutaUsuario); // Mostrar ranking de palabras más buscadas
        }
        // Si la opción es 6, el bucle termina y el programa sale

    } while (opcion != 6);

    // 6. Al salir, comprimir la carpeta y limpiar archivos originales
    cout << "Saliendo del programa...\n";
    comprimirCarpetaHuffman(rutaCarpeta, archivoHuff);
    eliminarCarpetaContenido("C:\\traductor");

    return 0;
}

