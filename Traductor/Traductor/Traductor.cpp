#include <iostream>      // Para operaciones de entrada y salida est�ndar (cout, cin)
#include <fstream>       // Para manejo de archivos (ifstream, ofstream)
#include <sstream>       // Para manipulaci�n de cadenas como flujos (stringstream)
#include <direct.h>      // Para funciones relacionadas con directorios, como _mkdir
#include <unordered_map> // Para el uso de mapas hash (unordered_map) en encriptaci�n y desencriptaci�n
#include <map>           // Para el uso de mapas ordenados (map) en ranking y Huffman
#include <vector>        // Para el uso de arreglos din�micos (vector) en almacenamiento de datos
#include <algorithm>     // Para funciones de ordenamiento y b�squeda (sort, remove_if, max, etc.)
#include <Windows.h>     // Para funciones espec�ficas de Windows (no se usa directamente, pero puede ser requerido por dependencias)
#include <string>        // Para el manejo de cadenas de texto (string)
#include <functional>    // Para el uso de funciones y lambdas (std::function)
#include <queue>         // Para el uso de colas y priority_queue (Huffman)
#include <bitset>        // Para manipulaci�n de bits (no se usa directamente, pero �til para compresi�n)
#include <filesystem>    // Para manipulaci�n de archivos y carpetas (C++17, fs::directory_iterator, fs::remove_all, etc.)
#include <cstring>       // Para funciones de manejo de cadenas de bajo nivel (no se usa directamente, pero puede ser requerido)
#include <limits>        // Para obtener valores l�mite de tipos num�ricos (no se usa directamente, pero �til en validaciones)


// Uso del espacio de nombres est�ndar para evitar escribir std:: en todo el c�digo.
using namespace std;


// Alias para el namespace de filesystem, simplifica el uso de fs:: en vez de std::filesystem::
namespace fs = filesystem;




//==========================ESTRUCTURAS==========================



// Estructura para almacenar una palabra y sus traducciones
// Estructura para almacenar una palabra y sus traducciones en diferentes idiomas.
// Cada campo representa la traducci�n de la palabra en un idioma espec�fico.
//
// Campos:
// - espanol: La palabra en espa�ol (idioma base).
// - ingles: Traducci�n de la palabra al ingl�s.
// - aleman: Traducci�n de la palabra al alem�n.
// - frances: Traducci�n de la palabra al franc�s.
// - italiano: Traducci�n de la palabra al italiano.
//
// Uso:
// - Esta estructura se utiliza para representar las palabras que se almacenan en el �rbol AVL
//   y se procesan en el traductor.

struct Palabra {
    string espanol;
    string ingles;
    string aleman;
    string frances;
    string italiano;
};



// Estructura para almacenar la informaci�n de un usuario registrado en el sistema.
//
// Campos:
// - nombre: Nombre de usuario �nico.
// - clave: Contrase�a del usuario (almacenada encriptada para mayor seguridad).
//
// Uso:
// - Esta estructura se utiliza para manejar el registro y la autenticaci�n de usuarios.
// - Los datos de los usuarios se almacenan en el archivo "usuarios.umg".

struct Usuario {
    string nombre;
    string clave;
};



// Nodo del �rbol Binario de B�squeda (AVL) utilizado para almacenar palabras y sus traducciones.
//
// Campos:
// - palabra: Objeto de tipo `Palabra` que contiene la palabra en espa�ol y sus traducciones.
// - izquierda: Puntero al nodo hijo izquierdo.
// - derecha: Puntero al nodo hijo derecho.
// - altura: Altura del nodo en el �rbol AVL (necesaria para mantener el balance del �rbol).
//
// Constructor:
// - Nodo(Palabra p): Inicializa un nodo con la palabra proporcionada y establece los punteros
//   izquierdo y derecho en nullptr, y la altura en 1.
//
// Uso:
// - Esta estructura se utiliza para construir el �rbol AVL que almacena las palabras y sus traducciones.
// - El �rbol AVL permite realizar b�squedas, inserciones y eliminaciones de palabras de manera eficiente.

struct Nodo {
    Palabra palabra;
    Nodo* izquierda;
    Nodo* derecha;
    int altura;

    Nodo(Palabra p) : palabra(p), izquierda(nullptr), derecha(nullptr), altura(1) {}
};




//==========================FUNCIONES DE ENCRIPTACION==========================



// Funci�n para encriptar una palabra utilizando una tabla de encriptaci�n.
// Cada car�cter de la palabra se reemplaza por un c�digo definido en la tabla.
// Si un car�cter no est� en la tabla, se conserva sin cambios.
//
// Par�metros:
// - palabra: La palabra que se desea encriptar.
//
// Retorno:
// - Un string que representa la palabra encriptada.
//
// Notas:
// - La tabla de encriptaci�n utiliza un mapeo de caracteres a c�digos espec�ficos.
// - Los caracteres que no est�n en la tabla (como n�meros o s�mbolos) se mantienen sin cambios.
// - Esta funci�n es utilizada para proteger datos sensibles como nombres de usuario o palabras buscadas.

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
        {'�', "m12"}, {'�', "g12"},
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

    // Iterar sobre cada car�cter de la palabra.
    for (char c : palabra) {
        // Si el car�cter est� en la tabla, reemplazarlo por su c�digo.
        if (tablaEncriptacion.find(c) != tablaEncriptacion.end()) {
            palabraEncriptada += tablaEncriptacion[c];
        }
        // Si no est� en la tabla, conservar el car�cter original.
        else {
            palabraEncriptada += c;
        }
    }

    return palabraEncriptada;
}



// Funci�n para desencriptar una palabra utilizando una tabla de desencriptaci�n.
// Cada token en la palabra encriptada se reemplaza por el car�cter correspondiente
// definido en la tabla de desencriptaci�n.
//
// Par�metros:
// - palabraEncriptada: La palabra encriptada que se desea desencriptar.
//
// Retorno:
// - Un string que representa la palabra desencriptada.
//
// Notas:
// - La tabla de desencriptaci�n utiliza un mapeo de c�digos espec�ficos a caracteres.
// - La funci�n procesa la palabra encriptada de izquierda a derecha, intentando
//   coincidir con los tokens m�s largos primero (m�ximo 3 caracteres).
// - Si un token no se encuentra en la tabla, el car�cter original se conserva.
// - Esta funci�n es utilizada para revertir la encriptaci�n aplicada por `encriptarPalabra`.

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
        {"m12", '�'}, {"g12", '�'},
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
    size_t maxTokenLength = 3; // La clave m�s larga tiene 3 caracteres

    // Procesar la palabra encriptada de izquierda a derecha.
    while (i < palabraEncriptada.size()) {
        bool encontrado = false;

        // Intentar coincidir con los tokens m�s largos primero.
        for (int len = maxTokenLength; len >= 2; --len) {
            if (i + len <= palabraEncriptada.size()) {
                string token = palabraEncriptada.substr(i, len);
                // Si el token se encuentra en la tabla, agregar el car�cter correspondiente.
                if (tablaDesencriptacion.find(token) != tablaDesencriptacion.end()) {
                    palabraOriginal += tablaDesencriptacion[token];
                    i += len; // Avanzar el �ndice seg�n la longitud del token.
                    encontrado = true;
                    break; // Salir del bucle al encontrar coincidencia.
                }
            }
        }

        // Si no se encontr� un token v�lido, conservar el car�cter original.
        if (!encontrado) {
            palabraOriginal += palabraEncriptada[i];
            ++i;
        }
    }

    return palabraOriginal;
}



// Funci�n para aplicar la operaci�n XOR a un texto utilizando una llave.
// Cada car�cter del texto se combina con un car�cter de la llave mediante la operaci�n XOR.
// La llave se repite c�clicamente si es m�s corta que el texto.
//
// Par�metros:
// - texto: El texto que se desea procesar.
// - llave: La llave utilizada para aplicar la operaci�n XOR.
//
// Retorno:
// - Un string que representa el texto procesado con XOR.
//
// Notas:
// - Esta funci�n es utilizada para encriptar o desencriptar datos de manera reversible.
// - Aplicar XOR dos veces con la misma llave revierte el resultado al texto original.
// - Es importante que la llave no sea vac�a para evitar errores.

string aplicarXOR(const string& texto, const string& llave) {
    string resultado = "";

    // Iterar sobre cada car�cter del texto.
    for (size_t i = 0; i < texto.size(); ++i) {
        // Aplicar XOR entre el car�cter del texto y el car�cter correspondiente de la llave.
        resultado += texto[i] ^ llave[i % llave.size()];
    }

    return resultado;
}



// Funci�n para revertir la operaci�n XOR aplicada a un texto utilizando la misma llave.
// Esta funci�n es id�ntica a `aplicarXOR`, ya que aplicar XOR dos veces con la misma llave
// Se hizo en una funcion diferente para mejorar la legibilidad.
// revierte el resultado al texto original.
//
// Par�metros:
// - texto: El texto procesado con XOR que se desea revertir.
// - llave: La llave utilizada para revertir la operaci�n XOR.
//
// Retorno:
// - Un string que representa el texto original.
//
// Notas:
// - Esta funci�n es utilizada para desencriptar datos procesados con `aplicarXOR`.
// - Es importante que la misma llave utilizada para encriptar sea utilizada para desencriptar.
// - Si la llave no coincide, el resultado ser� incorrecto.

string deshacerXOR(const string& texto, const string& llave) {
    string resultado = "";

    // Iterar sobre cada car�cter del texto.
    for (size_t i = 0; i < texto.size(); ++i) {
        // Aplicar XOR entre el car�cter del texto y el car�cter correspondiente de la llave.
        resultado += texto[i] ^ llave[i % llave.size()];
    }

    return resultado;
}




//===========================FUNCIONES DEL �RBOL AVL==========================



// Funci�n para obtener la altura de un nodo en el �rbol AVL.
//
// Par�metros:
// - nodo: Puntero al nodo del cual se desea obtener la altura.
//
// Retorno:
// - Un entero que representa la altura del nodo.
//   - Si el nodo es nulo, retorna 0 (altura de un �rbol vac�o).
//   - Si el nodo no es nulo, retorna el valor almacenado en el campo `altura`.
//
// Notas:
// - La altura de un nodo es la longitud del camino m�s largo desde ese nodo hasta una hoja.
// - Esta funci�n es utilizada para calcular el balance de los nodos y mantener el �rbol AVL balanceado.

int altura(Nodo* nodo) {
    if (!nodo) return 0; // Caso base: un nodo nulo tiene altura 0.
    return nodo->altura; // Retornar la altura almacenada en el nodo.
}



// Funci�n para calcular el factor de balance de un nodo en el �rbol AVL.
//
// Par�metros:
// - nodo: Puntero al nodo del cual se desea calcular el factor de balance.
//
// Retorno:
// - Un entero que representa el factor de balance del nodo.
//   - Si el nodo es nulo, retorna 0.
//   - Si el nodo no es nulo, retorna la diferencia entre la altura del sub�rbol izquierdo
//     y la altura del sub�rbol derecho.
//
// Notas:
// - El factor de balance se utiliza para determinar si un nodo est� balanceado:
//   - Un nodo est� balanceado si el factor de balance est� en el rango [-1, 1].
//   - Si el factor de balance es menor que -1 o mayor que 1, el �rbol necesita ser re-balanceado.
// - Esta funci�n es clave para mantener las propiedades del �rbol AVL.

int factorBalance(Nodo* nodo) {
    if (!nodo) return 0; // Caso base: un nodo nulo tiene factor de balance 0.
    return altura(nodo->izquierda) - altura(nodo->derecha); // Diferencia de alturas.
}



// Funci�n para actualizar la altura de un nodo en el �rbol AVL.
//
// Par�metros:
// - nodo: Puntero al nodo cuya altura se desea actualizar.
//
// Proceso:
// 1. Verifica si el nodo es nulo. Si lo es, no realiza ninguna acci�n.
// 2. Calcula la nueva altura del nodo como:
//    - 1 + la altura m�xima entre el sub�rbol izquierdo y el sub�rbol derecho.
// 3. Asigna el valor calculado al campo `altura` del nodo.
//
// Notas:
// - Esta funci�n debe ser llamada despu�s de realizar operaciones que puedan modificar
//   la estructura del �rbol, como inserciones, eliminaciones o rotaciones.
// - Mantener actualizada la altura de los nodos es esencial para calcular el factor de balance
//   y garantizar que el �rbol AVL permanezca balanceado.

void actualizarAltura(Nodo* nodo) {
    if (!nodo) return; // Caso base: si el nodo es nulo, no hace nada.

    // Calcular la nueva altura del nodo.
    nodo->altura = 1 + max(altura(nodo->izquierda), altura(nodo->derecha));
}



// Funci�n para realizar una rotaci�n a la derecha en un �rbol AVL.
//
// Par�metros:
// - y: Puntero al nodo que ser� rotado hacia la derecha.
//
// Retorno:
// - Un puntero al nuevo nodo ra�z despu�s de la rotaci�n.
//
// Proceso:
// 1. Identifica el nodo izquierdo (`x`) como el nuevo nodo ra�z.
// 2. Almacena el sub�rbol derecho de `x` (denominado `T2`) temporalmente.
// 3. Realiza la rotaci�n:
//    - El nodo `x` se convierte en la nueva ra�z.
//    - El nodo `y` pasa a ser el hijo derecho de `x`.
//    - El sub�rbol `T2` se asigna como el hijo izquierdo de `y`.
// 4. Actualiza las alturas de los nodos afectados (`y` y `x`).
//
// Notas:
// - Esta operaci�n se utiliza para re-balancear el �rbol AVL cuando el sub�rbol izquierdo
//   de un nodo est� desbalanceado (caso de rotaci�n simple derecha).
// - Mantiene las propiedades del �rbol AVL (balance y orden).

Nodo* rotarDerecha(Nodo* y) {
    Nodo* x = y->izquierda; // El nuevo nodo ra�z ser� el hijo izquierdo.
    Nodo* T2 = x->derecha;  // Almacena temporalmente el sub�rbol derecho de `x`.

    // Realizar la rotaci�n.
    x->derecha = y;
    y->izquierda = T2;

    // Actualizar las alturas de los nodos afectados.
    actualizarAltura(y);
    actualizarAltura(x);

    // Retornar el nuevo nodo ra�z.
    return x;
}



// Funci�n para realizar una rotaci�n a la izquierda en un �rbol AVL.
//
// Par�metros:
// - x: Puntero al nodo que ser� rotado hacia la izquierda.
//
// Retorno:
// - Un puntero al nuevo nodo ra�z despu�s de la rotaci�n.
//
// Proceso:
// 1. Identifica el nodo derecho (`y`) como el nuevo nodo ra�z.
// 2. Almacena el sub�rbol izquierdo de `y` (denominado `T2`) temporalmente.
// 3. Realiza la rotaci�n:
//    - El nodo `y` se convierte en la nueva ra�z.
//    - El nodo `x` pasa a ser el hijo izquierdo de `y`.
//    - El sub�rbol `T2` se asigna como el hijo derecho de `x`.
// 4. Actualiza las alturas de los nodos afectados (`x` y `y`).
//
// Notas:
// - Esta operaci�n se utiliza para re-balancear el �rbol AVL cuando el sub�rbol derecho
//   de un nodo est� desbalanceado (caso de rotaci�n simple izquierda).
// - Mantiene las propiedades del �rbol AVL (balance y orden).

Nodo* rotarIzquierda(Nodo* x) {
    Nodo* y = x->derecha; // El nuevo nodo ra�z ser� el hijo derecho.
    Nodo* T2 = y->izquierda; // Almacena temporalmente el sub�rbol izquierdo de `y`.

    // Realizar la rotaci�n.
    y->izquierda = x;
    x->derecha = T2;

    // Actualizar las alturas de los nodos afectados.
    actualizarAltura(x);
    actualizarAltura(y);

    // Retornar el nuevo nodo ra�z.
    return y;
}



// Funci�n para insertar un nuevo nodo en el �rbol AVL.
//
// Par�metros:
// - nodo: Puntero al nodo ra�z del �rbol donde se realizar� la inserci�n.
// - nuevaPalabra: Objeto de tipo `Palabra` que contiene la palabra en espa�ol y sus traducciones.
//
// Retorno:
// - Un puntero al nodo ra�z actualizado despu�s de la inserci�n.
//
// Proceso:
// 1. Si el nodo actual es nulo, crea un nuevo nodo con la palabra proporcionada y lo retorna.
// 2. Compara la palabra en espa�ol de `nuevaPalabra` con la palabra del nodo actual:
//    - Si es menor, realiza la inserci�n en el sub�rbol izquierdo.
//    - Si es mayor, realiza la inserci�n en el sub�rbol derecho.
//    - Si es igual, no realiza la inserci�n (no se permiten duplicados).
// 3. Actualiza la altura del nodo actual despu�s de la inserci�n.
// 4. Calcula el factor de balance del nodo actual para verificar si est� balanceado.
// 5. Si el nodo est� desbalanceado, aplica las rotaciones necesarias seg�n el caso:
//    - Caso Izquierda Izquierda: Rotaci�n derecha.
//    - Caso Derecha Derecha: Rotaci�n izquierda.
//    - Caso Izquierda Derecha: Rotaci�n izquierda en el hijo izquierdo, luego rotaci�n derecha.
//    - Caso Derecha Izquierda: Rotaci�n derecha en el hijo derecho, luego rotaci�n izquierda.
//
// Notas:
// - Esta funci�n asegura que el �rbol AVL permanezca balanceado despu�s de cada inserci�n.
// - Las rotaciones mantienen las propiedades del �rbol AVL (balance y orden).

Nodo* insertar(Nodo* nodo, Palabra nuevaPalabra) {
    // Caso base: si el nodo es nulo, crea un nuevo nodo con la palabra.
    if (!nodo) return new Nodo(nuevaPalabra);

    // Comparar la palabra en espa�ol para decidir la direcci�n de la inserci�n.
    if (nuevaPalabra.espanol < nodo->palabra.espanol)
        nodo->izquierda = insertar(nodo->izquierda, nuevaPalabra); // Insertar en el sub�rbol izquierdo.
    else if (nuevaPalabra.espanol > nodo->palabra.espanol)
        nodo->derecha = insertar(nodo->derecha, nuevaPalabra); // Insertar en el sub�rbol derecho.
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



// Funci�n para buscar una palabra en el �rbol AVL.
//
// Par�metros:
// - raiz: Puntero al nodo ra�z del �rbol donde se realizar� la b�squeda.
// - palabraBuscada: Cadena que contiene la palabra en espa�ol que se desea buscar.
//
// Retorno:
// - Un puntero al nodo que contiene la palabra buscada.
// - Si la palabra no se encuentra en el �rbol, retorna nullptr.
//
// Proceso:
// 1. Verifica si el nodo actual (`raiz`) es nulo o si contiene la palabra buscada:
//    - Si es nulo, significa que la palabra no est� en el �rbol.
//    - Si contiene la palabra buscada, retorna el nodo actual.
// 2. Compara la palabra buscada con la palabra en espa�ol del nodo actual:
//    - Si es menor, realiza la b�squeda en el sub�rbol izquierdo.
//    - Si es mayor, realiza la b�squeda en el sub�rbol derecho.
//
// Notas:
// - Esta funci�n utiliza la propiedad de orden del �rbol AVL para realizar la b�squeda de manera eficiente.
// - La b�squeda tiene una complejidad de O(log n) en promedio, donde `n` es el n�mero de nodos en el �rbol.

Nodo* buscar(Nodo* raiz, const string& palabraBuscada) {
    // Caso base: el nodo es nulo o contiene la palabra buscada.
    if (!raiz || raiz->palabra.espanol == palabraBuscada)
        return raiz;

    // Decidir la direcci�n de la b�squeda.
    if (palabraBuscada < raiz->palabra.espanol)
        return buscar(raiz->izquierda, palabraBuscada); // Buscar en el sub�rbol izquierdo.
    else
        return buscar(raiz->derecha, palabraBuscada); // Buscar en el sub�rbol derecho.
}



// Funci�n para cargar palabras desde un archivo y construir el �rbol AVL.
//
// Retorno:
// - Un puntero al nodo ra�z del �rbol AVL construido a partir de las palabras en el archivo.
// - Si el archivo no se puede abrir, retorna nullptr.
//
// Proceso:
// 1. Abre el archivo `palabras.umg` en modo lectura.
// 2. Si el archivo no se puede abrir, muestra un mensaje de error y retorna nullptr.
// 3. Inicializa un puntero `raiz` como nullptr para construir el �rbol AVL.
// 4. Lee cada l�nea del archivo, donde cada l�nea contiene una palabra y sus traducciones separadas por comas.
// 5. Divide la l�nea en sus componentes (palabra en espa�ol y traducciones) y crea un objeto `Palabra`.
// 6. Inserta el objeto `Palabra` en el �rbol AVL utilizando la funci�n `insertar`.
// 7. Cierra el archivo y retorna el puntero a la ra�z del �rbol.
//
// Notas:
// - El archivo debe estar ubicado en la ruta `C:\\traductor\\palabras.umg`.
// - Cada l�nea del archivo debe tener el formato: `espanol,ingles,aleman,frances,italiano`.
// - La funci�n utiliza la funci�n `insertar` para mantener el �rbol AVL balanceado.
// - Si el archivo est� vac�o, la funci�n retorna un �rbol vac�o (nullptr).

Nodo* cargarPalabras() {
    const string nombreArchivo = "C:\\traductor\\palabras.umg";
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo: " << nombreArchivo << endl;
        return nullptr;
    }

    Nodo* raiz = nullptr; // Inicializar la ra�z del �rbol AVL como nula.
    string linea;

    // Leer cada l�nea del archivo.
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        Palabra p;

        // Dividir la l�nea en sus componentes y asignarlas al objeto `Palabra`.
        if (getline(ss, p.espanol, ',') &&
            getline(ss, p.ingles, ',') &&
            getline(ss, p.aleman, ',') &&
            getline(ss, p.frances, ',') &&
            getline(ss, p.italiano, ',')) {
            // Insertar la palabra en el �rbol AVL.
            raiz = insertar(raiz, p);
        }
    }

    archivo.close(); // Cerrar el archivo despu�s de leerlo.
    return raiz; // Retornar la ra�z del �rbol AVL.
}



// Funci�n para agregar una nueva palabra al �rbol AVL y al archivo de palabras.
//
// Par�metros:
// - raiz: Puntero al nodo ra�z del �rbol AVL donde se agregar� la nueva palabra.
// - archivo: Ruta del archivo donde se almacenar�n las palabras.
//
// Retorno:
// - Un puntero al nodo ra�z actualizado despu�s de agregar la nueva palabra.
//
// Proceso:
// 1. Solicita al usuario que ingrese la palabra en espa�ol y sus traducciones (ingl�s, alem�n, franc�s, italiano).
// 2. Crea un objeto `Palabra` con los datos ingresados por el usuario.
// 3. Inserta la nueva palabra en el �rbol AVL utilizando la funci�n `insertar`.
// 4. Abre el archivo en modo de adici�n (append) para guardar la nueva palabra.
// 5. Escribe la palabra y sus traducciones en el archivo en formato CSV (separadas por comas).
// 6. Cierra el archivo y muestra un mensaje de �xito.
//
// Notas:
// - Si el archivo no se puede abrir, muestra un mensaje de error y retorna la ra�z sin cambios.
// - La funci�n asegura que la nueva palabra se agrega tanto al �rbol AVL como al archivo.
// - El archivo debe estar ubicado en la ruta especificada por el par�metro `archivo`.

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

    // Agregar la nueva palabra al �rbol AVL.
    raiz = insertar(raiz, nuevaPalabra);

    // Abrir el archivo en modo de adici�n para guardar la nueva palabra.
    ofstream archivoOut(archivo, ios::app);
    if (!archivoOut.is_open()) {
        cerr << "Error al abrir el archivo para escritura.\n";
        return raiz; // Retornar la ra�z sin cambios si ocurre un error.
    }

    // Escribir la nueva palabra en el archivo en formato CSV.
    archivoOut << nuevaPalabra.espanol << "," << nuevaPalabra.ingles << ","
        << nuevaPalabra.aleman << "," << nuevaPalabra.frances << ","
        << nuevaPalabra.italiano << endl;
    archivoOut.close(); // Cerrar el archivo.

    cout << "Palabra agregada con exito.\n"; // Mostrar mensaje de �xito.
    return raiz; // Retornar la ra�z actualizada.
}



// Funci�n para encontrar el nodo con la clave m�nima en un �rbol AVL.
//
// Par�metros:
// - nodo: Puntero al nodo ra�z del �rbol o sub�rbol donde se buscar� el nodo m�nimo.
//
// Retorno:
// - Un puntero al nodo que contiene la clave m�nima en el �rbol o sub�rbol.
//
// Proceso:
// 1. Comienza desde el nodo ra�z proporcionado.
// 2. Itera hacia el hijo izquierdo de cada nodo, ya que en un �rbol binario de b�squeda
//    el nodo con la clave m�nima siempre se encuentra en el extremo izquierdo.
// 3. Retorna el nodo m�s a la izquierda encontrado.
//
// Notas:
// - Esta funci�n se utiliza principalmente en operaciones como eliminaci�n de nodos
//   para encontrar el sucesor en caso de que el nodo a eliminar tenga dos hijos.
// - Si el �rbol o sub�rbol est� vac�o (nodo es nulo), retorna nullptr.
// - La complejidad de esta funci�n es O(h), donde `h` es la altura del �rbol o sub�rbol.

Nodo* minimo(Nodo* nodo) {
    // Iterar hacia el hijo izquierdo hasta encontrar el nodo m�s a la izquierda.
    while (nodo->izquierda) {
        nodo = nodo->izquierda;
    }
    return nodo; // Retornar el nodo con la clave m�nima.
}



// Funci�n para eliminar una palabra del �rbol AVL.
//
// Par�metros:
// - nodo: Puntero al nodo ra�z del �rbol o sub�rbol donde se realizar� la eliminaci�n.
// - palabra: Cadena que contiene la palabra en espa�ol que se desea eliminar.
//
// Retorno:
// - Un puntero al nodo ra�z actualizado despu�s de la eliminaci�n.
//
// Proceso:
// 1. Realiza una b�squeda normal en el �rbol AVL para encontrar el nodo que contiene la palabra:
//    - Si la palabra es menor que la palabra del nodo actual, busca en el sub�rbol izquierdo.
//    - Si la palabra es mayor, busca en el sub�rbol derecho.
//    - Si encuentra el nodo, procede con la eliminaci�n.
// 2. Elimina el nodo seg�n los siguientes casos:
//    - Caso 1: El nodo no tiene hijos (es una hoja). Elimina el nodo y lo reemplaza con nullptr.
//    - Caso 2: El nodo tiene un solo hijo. Reemplaza el nodo con su �nico hijo y lo elimina.
//    - Caso 3: El nodo tiene dos hijos. Encuentra el sucesor en el sub�rbol derecho (el nodo con la clave m�nima),
//      copia su contenido al nodo actual, y elimina el sucesor recursivamente.
// 3. Despu�s de eliminar el nodo, actualiza la altura del nodo actual.
// 4. Calcula el factor de balance del nodo actual para verificar si est� balanceado.
// 5. Si el nodo est� desbalanceado, aplica las rotaciones necesarias seg�n el caso:
//    - Caso Izquierda Izquierda: Rotaci�n derecha.
//    - Caso Izquierda Derecha: Rotaci�n izquierda en el hijo izquierdo, luego rotaci�n derecha.
//    - Caso Derecha Derecha: Rotaci�n izquierda.
//    - Caso Derecha Izquierda: Rotaci�n derecha en el hijo derecho, luego rotaci�n izquierda.
//
// Notas:
// - Esta funci�n asegura que el �rbol AVL permanezca balanceado despu�s de cada eliminaci�n.
// - Las rotaciones mantienen las propiedades del �rbol AVL (balance y orden).

Nodo* eliminarPalabra(Nodo* nodo, const string& palabra) {
    if (!nodo) return nodo; // Caso base: el nodo es nulo.

    // B�squeda normal en el �rbol AVL.
    if (palabra < nodo->palabra.espanol)
        nodo->izquierda = eliminarPalabra(nodo->izquierda, palabra); // Buscar en el sub�rbol izquierdo.
    else if (palabra > nodo->palabra.espanol)
        nodo->derecha = eliminarPalabra(nodo->derecha, palabra); // Buscar en el sub�rbol derecho.
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
                *nodo = *temp; // Reemplazar el nodo actual con su �nico hijo.
            }
            delete temp; // Eliminar el nodo.
        }
        else {
            // Caso 3: Nodo con dos hijos.
            Nodo* temp = minimo(nodo->derecha); // Encontrar el sucesor (m�nimo en el sub�rbol derecho).
            nodo->palabra = temp->palabra; // Copiar los datos del sucesor al nodo actual.
            nodo->derecha = eliminarPalabra(nodo->derecha, temp->palabra.espanol); // Eliminar el sucesor.
        }
    }

    // Si el �rbol est� vac�o despu�s de la eliminaci�n.
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



// Estructura para almacenar informaci�n de un archivo a comprimir.
// Cada campo representa:
// - rutaRelativa: Ruta del archivo relativa a la carpeta base de compresi�n.
// - contenido: Vector de caracteres que contiene los datos binarios del archivo.
//
// Uso:
// - Esta estructura se utiliza para recopilar y manipular los archivos que ser�n comprimidos
//   y descomprimidos mediante el algoritmo de Huffman.

struct ArchivoParaComprimir {
    string rutaRelativa;      // Ruta relativa del archivo respecto a la carpeta base
    vector<char> contenido;   // Contenido binario del archivo
};



// Funci�n para leer completamente un archivo binario y devolver su contenido en un vector de caracteres.
//
// Par�metros:
// - ruta: Ruta completa del archivo que se desea leer.
//
// Retorno:
// - Un vector de caracteres que contiene el contenido binario del archivo.
//   Si el archivo no se puede abrir, retorna un vector vac�o.
//
// Notas:
// - Esta funci�n se utiliza para cargar archivos que ser�n comprimidos o descomprimidos.
// - El archivo se abre en modo binario para preservar todos los datos tal como est�n en disco.

vector<char> leerArchivo(const string& ruta) {
    ifstream file(ruta, ios::binary);
    if (!file) {
        cerr << "No se pudo abrir archivo: " << ruta << "\n";
        return {};
    }
    return vector<char>((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
}



// Funci�n para guardar el contenido binario en un archivo.
//
// Par�metros:
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
// - Esta funci�n se utiliza para restaurar archivos durante la descompresi�n o para guardar archivos binarios generados.
// - Si el archivo no se puede crear o abrir, no se realiza ninguna acci�n.

void guardarArchivo(const string& ruta, const vector<char>& contenido) {
    ofstream file(ruta, ios::binary);
    if (!file) {
        cerr << "No se pudo guardar archivo: " << ruta << "\n";
        return;
    }
    file.write(contenido.data(), contenido.size());
}



// Funci�n para recorrer una carpeta de forma recursiva y obtener todos los archivos que contiene,
// almacenando su ruta relativa y su contenido binario en un vector de estructuras.
//
// Par�metros:
// - carpetaBase: Ruta de la carpeta base desde donde se inicia la b�squeda de archivos.
// - archivos: Vector de estructuras ArchivoParaComprimir donde se almacenar�n los archivos encontrados.
//
// Proceso:
// 1. Utiliza un iterador recursivo para recorrer todos los archivos dentro de la carpeta base y sus subcarpetas.
// 2. Para cada archivo regular encontrado:
//    - Obtiene la ruta completa del archivo.
//    - Calcula la ruta relativa respecto a la carpeta base.
//    - Lee el contenido binario del archivo usando la funci�n leerArchivo.
//    - Agrega una estructura ArchivoParaComprimir al vector con la ruta relativa y el contenido.
//
// Notas:
// - Solo se procesan archivos regulares (no carpetas).
// - Esta funci�n es utilizada para preparar los archivos antes de la compresi�n Huffman.

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



// Funci�n para serializar un conjunto de archivos en un solo buffer binario.
// El formato del buffer es:
// [numArchivos][longRuta][ruta][tamContenido][contenido]...
//
// Par�metros:
// - archivos: Vector de estructuras ArchivoParaComprimir que contiene la ruta relativa y el contenido de cada archivo.
//
// Retorno:
// - Un vector de caracteres que representa el buffer binario serializado con todos los archivos.
//
// Proceso:
// 1. Inserta el n�mero total de archivos al inicio del buffer.
// 2. Para cada archivo:
//    - Inserta la longitud de la ruta relativa.
//    - Inserta la ruta relativa como cadena de caracteres.
//    - Inserta el tama�o del contenido binario.
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



// Funci�n para deserializar un buffer binario y reconstruir los archivos originales en una carpeta destino.
// El buffer debe tener el formato: [numArchivos][longRuta][ruta][tamContenido][contenido]...
//
// Par�metros:
// - buffer: Vector de caracteres que contiene los datos serializados de los archivos.
// - carpetaDestino: Ruta de la carpeta donde se restaurar�n los archivos y carpetas.
//
// Proceso:
// 1. Lee el n�mero total de archivos almacenados en el buffer.
// 2. Para cada archivo:
//    - Lee la longitud de la ruta relativa y la ruta relativa.
//    - Lee el tama�o del contenido y el contenido binario.
//    - Crea las carpetas necesarias en la ruta destino.
//    - Guarda el contenido en la ruta correspondiente usando la funci�n guardarArchivo.
//
// Notas:
// - Si el buffer est� corrupto o incompleto, lanza una excepci�n.
// - Esta funci�n se utiliza durante la descompresi�n para restaurar la estructura original de archivos y carpetas.

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



// Estructura para representar un nodo del �rbol de Huffman utilizado en la compresi�n de archivos.
// Cada nodo puede ser una hoja (car�cter y frecuencia) o un nodo interno (suma de frecuencias).
//
// Campos:
// - c: Car�cter representado por el nodo (solo v�lido en hojas; '\0' en nodos internos).
// - freq: Frecuencia total de aparici�n del car�cter o suma de frecuencias de los hijos.
// - izq: Puntero al hijo izquierdo del nodo Huffman.
// - der: Puntero al hijo derecho del nodo Huffman.
//
// Constructores:
// - NodoHuffman(char c, int freq): Crea una hoja con un car�cter y su frecuencia.
// - NodoHuffman(NodoHuffman* izq, NodoHuffman* der): Crea un nodo interno a partir de dos hijos.
//
// Uso:
// - Esta estructura se utiliza para construir el �rbol de Huffman necesario para la codificaci�n y decodificaci�n de datos binarios.

struct NodoHuffman {
    char c;                // Car�cter (solo v�lido en hojas)
    int freq;              // Frecuencia del car�cter o suma de frecuencias
    NodoHuffman* izq;      // Puntero al hijo izquierdo
    NodoHuffman* der;      // Puntero al hijo derecho

    NodoHuffman(char c, int freq) : c(c), freq(freq), izq(nullptr), der(nullptr) {}
    NodoHuffman(NodoHuffman* izq, NodoHuffman* der)
        : c('\0'), freq(izq->freq + der->freq), izq(izq), der(der) {
    }
};



// Estructura comparadora para nodos de Huffman utilizada en la priority_queue.
// Compara dos punteros a NodoHuffman seg�n su frecuencia (freq).
// El nodo con menor frecuencia tendr� mayor prioridad (menor freq sale primero).
//
// Uso:
// - Esta estructura se utiliza como comparador en la cola de prioridad (priority_queue)
//   para construir el �rbol de Huffman de manera eficiente.

struct CompareNodo {
    bool operator()(NodoHuffman* a, NodoHuffman* b) {
        return a->freq > b->freq;
    }
};



// Funci�n para construir el �rbol de Huffman a partir de un mapa de frecuencias de caracteres.
// Utiliza una cola de prioridad (priority_queue) para combinar los nodos de menor frecuencia.
//
// Par�metros:
// - freq: Mapa que asocia cada car�cter con su frecuencia de aparici�n.
//
// Retorno:
// - Un puntero a la ra�z del �rbol de Huffman construido.
//
// Proceso:
// 1. Crea un nodo hoja para cada car�cter y lo inserta en la cola de prioridad.
// 2. Mientras haya m�s de un nodo en la cola:
//    - Extrae los dos nodos con menor frecuencia.
//    - Crea un nuevo nodo interno con estos dos nodos como hijos y la suma de sus frecuencias.
//    - Inserta el nuevo nodo en la cola.
// 3. El nodo restante en la cola es la ra�z del �rbol de Huffman.
//
// Notas:
// - El �rbol de Huffman se utiliza para la compresi�n y descompresi�n eficiente de datos binarios.

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



// Funci�n para construir la tabla de c�digos Huffman a partir del �rbol de Huffman.
// Asigna a cada car�cter una cadena de bits �nica seg�n el recorrido del �rbol.
//
// Par�metros:
// - nodo: Puntero al nodo actual del �rbol de Huffman.
// - codigo: Cadena que representa el c�digo binario acumulado hasta el nodo actual.
// - tabla: Mapa donde se almacenar�n los c�digos Huffman generados para cada car�cter.
//
// Proceso:
// 1. Si el nodo es nulo, retorna (caso base).
// 2. Si el nodo es una hoja (no tiene hijos), asigna el c�digo acumulado al car�cter del nodo.
// 3. Llama recursivamente para el hijo izquierdo agregando '0' al c�digo.
// 4. Llama recursivamente para el hijo derecho agregando '1' al c�digo.
//
// Notas:
// - Esta funci�n se utiliza para generar los c�digos Huffman necesarios para la compresi�n y descompresi�n de datos.

void construirCodigos(NodoHuffman* nodo, const string& codigo, map<char, string>& tabla) {
    if (!nodo) return;
    if (!nodo->izq && !nodo->der) { // Es una hoja
        tabla[nodo->c] = codigo;
    }
    construirCodigos(nodo->izq, codigo + "0", tabla);
    construirCodigos(nodo->der, codigo + "1", tabla);
}



// Funci�n para liberar la memoria utilizada por un �rbol binario (como el �rbol de Huffman).
//
// Par�metros:
// - nodo: Puntero al nodo ra�z del �rbol a liberar.
//
// Proceso:
// 1. Llama recursivamente a la funci�n para liberar el sub�rbol izquierdo.
// 2. Llama recursivamente a la funci�n para liberar el sub�rbol derecho.
// 3. Elimina el nodo actual.
//
// Notas:
// - Es importante llamar a esta funci�n para evitar fugas de memoria cuando se termina de usar el �rbol.

void liberarArbol(NodoHuffman* nodo) {
    if (!nodo) return;
    liberarArbol(nodo->izq);
    liberarArbol(nodo->der);
    delete nodo;
}



// Funci�n para comprimir un buffer de datos utilizando el algoritmo de Huffman y guardar el resultado en un archivo binario.
//
// Par�metros:
// - buffer: Vector de caracteres que contiene los datos originales a comprimir.
// - archivoSalida: Ruta del archivo donde se guardar� el resultado comprimido.
//
// Proceso:
// 1. Cuenta la frecuencia de cada car�cter en el buffer.
// 2. Construye el �rbol de Huffman a partir del mapa de frecuencias.
// 3. Genera la tabla de c�digos Huffman para cada car�cter.
// 4. Abre el archivo de salida en modo binario.
// 5. Escribe la tabla de c�digos en el archivo (n�mero de entradas, cada car�cter, tama�o y c�digo).
// 6. Codifica el buffer original en una cadena de bits usando la tabla de c�digos.
// 7. Escribe la cantidad de bits codificados y empaqueta los bits en bytes para almacenarlos en el archivo.
// 8. Libera la memoria del �rbol de Huffman.
//
// Notas:
// - Si el archivo no se puede abrir para escritura, muestra un mensaje de error y no realiza la compresi�n.
// - El archivo generado puede ser descomprimido usando la funci�n correspondiente que lee la tabla y decodifica los bits.

void comprimirBufferConHuffman(const vector<char>& buffer, const string& archivoSalida) {
    // Contar frecuencias de cada car�cter en el buffer
    map<char, int> freq;
    for (char c : buffer) freq[c]++;

    // Construir el �rbol de Huffman
    NodoHuffman* raiz = construirArbol(freq);

    // Generar la tabla de c�digos Huffman
    map<char, string> codigos;
    construirCodigos(raiz, "", codigos);

    // Abrir el archivo de salida en modo binario
    ofstream ofs(archivoSalida, ios::binary);
    if (!ofs.is_open()) {
        cerr << "No se pudo crear archivo para comprimir\n";
        liberarArbol(raiz);
        return;
    }

    // Guardar el tama�o de la tabla de c�digos
    int tamTabla = static_cast<int>(codigos.size());
    ofs.write(reinterpret_cast<const char*>(&tamTabla), sizeof(int));

    // Guardar la tabla de c�digos: [char][int tama�o c�digo][string c�digo]
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



// Funci�n para leer la tabla de c�digos Huffman desde un archivo binario y reconstruir el mapa de decodificaci�n.
//
// Par�metros:
// - ifs: Flujo de entrada de archivo binario abierto en modo lectura.
// - tablaReversa: Mapa donde se almacenar�n los c�digos Huffman como clave y el car�cter correspondiente como valor.
//
// Proceso:
// 1. Lee el n�mero de entradas de la tabla de c�digos (int).
// 2. Para cada entrada:
//    - Lee el car�cter asociado (char).
//    - Lee el tama�o del c�digo (int).
//    - Lee el c�digo Huffman (string de tama�o tamCod).
//    - Almacena el par (c�digo, car�cter) en el mapa tablaReversa.
//
// Notas:
// - Esta funci�n se utiliza durante la descompresi�n para reconstruir la tabla de decodificaci�n Huffman.
// - El formato debe coincidir exactamente con el utilizado al guardar la tabla en la compresi�n.

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



// Funci�n para descomprimir un archivo comprimido con Huffman y devolver el buffer original.
//
// Par�metros:
// - archivoEntrada: Ruta del archivo .huff comprimido.
//
// Retorno:
// - Un vector de caracteres con el contenido original descomprimido.
//   Si ocurre un error al abrir o leer el archivo, retorna un vector vac�o.
//
// Proceso:
// 1. Abre el archivo en modo binario.
// 2. Lee la tabla de c�digos Huffman invertida (c�digo -> car�cter).
// 3. Lee la cantidad de bits codificados y los bytes codificados.
// 4. Decodifica los bits usando la tabla para reconstruir el buffer original.
//
// Notas:
// - Esta funci�n es utilizada por descomprimirCarpetaHuffman para restaurar archivos comprimidos.

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



// Funci�n para eliminar todos los archivos y carpetas dentro de una carpeta,
// excepto un archivo espec�fico (por ejemplo, el archivo .huff).
//
// Par�metros:
// - rutaCarpeta: Ruta de la carpeta donde se eliminar� el contenido.
// - nombreArchivoHuff: Nombre del archivo que NO debe eliminarse (por ejemplo, "traductor.huff").
//
// Proceso:
// 1. Recorre todos los archivos y subcarpetas dentro de la carpeta especificada.
// 2. Si el nombre del archivo es igual al archivo que se debe conservar, lo omite.
// 3. Elimina recursivamente todos los dem�s archivos y carpetas.
//
// Notas:
// - Esta funci�n es �til para limpiar la carpeta antes de descomprimir archivos,
//   asegurando que solo se conserve el archivo comprimido .huff.

void eliminarContenidoExceptoHuff(const string& rutaCarpeta, const string& nombreArchivoHuff) {
    for (const auto& entry : fs::directory_iterator(rutaCarpeta)) {
        if (entry.path().filename() == nombreArchivoHuff) continue;
        fs::remove_all(entry.path());
    }
}



// Funci�n principal para comprimir el contenido de una carpeta utilizando Huffman.
//
// Par�metros:
// - rutaCarpeta: Ruta de la carpeta cuyo contenido se desea comprimir.
// - rutaArchivoDestino: Ruta donde se guardar� el archivo comprimido (.huff).
//
// Proceso:
// 1. Obtiene todos los archivos de la carpeta y subcarpetas (excepto el archivo .huff si existe).
// 2. Serializa los archivos en un solo buffer binario.
// 3. Si el buffer est� vac�o, muestra una advertencia y no realiza la compresi�n.
// 4. Comprime el buffer utilizando el algoritmo de Huffman y guarda el resultado en el archivo destino.
//
// Notas:
// - Esta funci�n es llamada antes de salir del programa para respaldar el estado de la carpeta.
// - El archivo .huff se excluye para evitar auto-incluirse en la compresi�n.

void comprimirCarpetaHuffman(const string& rutaCarpeta, const string& rutaArchivoDestino) {
    vector<ArchivoParaComprimir> archivos;
    obtenerArchivos(rutaCarpeta, archivos);

    // Excluir el archivo .huff existente
    archivos.erase(remove_if(archivos.begin(), archivos.end(), [&](const ArchivoParaComprimir& a) {
        return a.rutaRelativa == "traductor.huff";
        }), archivos.end());

    vector<char> buffer = serializarArchivos(archivos);

    if (buffer.empty()) {
        cerr << "Advertencia: El buffer est� vac�o. No se comprimir� nada.\n";
        return;
    }

    comprimirBufferConHuffman(buffer, rutaArchivoDestino);
}



// Funci�n principal para descomprimir el contenido de una carpeta a partir de un archivo comprimido con Huffman.
//
// Par�metros:
// - rutaCarpeta: Ruta de la carpeta donde se restaurar�n los archivos descomprimidos.
// - archivoHuff: Ruta del archivo comprimido (.huff) que contiene los datos serializados y comprimidos.
//
// Proceso:
// 1. Descomprime el archivo .huff y obtiene el buffer binario original.
// 2. Si el buffer est� vac�o o ocurre un error, muestra un mensaje y no realiza la restauraci�n.
// 3. Antes de restaurar, elimina todo el contenido de la carpeta excepto el archivo .huff (si estuviera en la misma carpeta).
// 4. Deserializa el buffer y reconstruye los archivos y carpetas originales en la ruta especificada.
//
// Notas:
// - Esta funci�n es llamada al inicio del programa si existe un archivo .huff para restaurar el estado anterior.
// - Si el archivo .huff est� en una carpeta separada, la exclusi�n del .huff es innecesaria pero no afecta el resultado.

void descomprimirCarpetaHuffman(const string& rutaCarpeta, const string& archivoHuff) {
    vector<char> buffer = descomprimirArchivoHuffman(archivoHuff);
    if (buffer.empty()) {
        cerr << "No se pudo descomprimir el archivo o est� vac�o\n";
        return;
    }

    // Antes de restaurar, eliminar todo excepto el archivo .huff
    eliminarContenidoExceptoHuff(rutaCarpeta, "traductor.huff");

    // Reconstruir archivos
    deserializarYReconstruir(buffer, rutaCarpeta);
}



// Funci�n para eliminar todos los archivos y subcarpetas dentro de una carpeta especificada.
//
// Par�metros:
// - rutaCarpeta: Ruta de la carpeta cuyo contenido se desea eliminar.
//
// Proceso:
// 1. Recorre todos los archivos y subcarpetas dentro de la carpeta especificada usando un iterador de directorio.
// 2. Para cada entrada encontrada (archivo o carpeta), intenta eliminarla recursivamente usando fs::remove_all.
// 3. Si ocurre un error al eliminar alg�n archivo o carpeta, muestra un mensaje de error con detalles.
//
// Notas:
// - Esta funci�n elimina todo el contenido de la carpeta, pero no elimina la carpeta en s�.
// - Es �til para limpiar completamente una carpeta antes de restaurar o comprimir su contenido.
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



// Funci�n para buscar una palabra en el �rbol AVL, mostrar su traducci�n en el idioma seleccionado
// y guardar la palabra buscada en los archivos correspondientes.
//
// Par�metros:
// - raiz: Puntero al nodo ra�z del �rbol AVL que contiene las palabras y sus traducciones.
// - rutaUsuario: Ruta de la carpeta del usuario actual, donde se almacenan los archivos.
//
// Proceso:
// 1. Solicita al usuario una palabra en espa�ol para buscar en el �rbol AVL.
// 2. Si la palabra existe, permite seleccionar un idioma para mostrar la traducci�n.
// 3. Reproduce la traducci�n en forma de audio utilizando PowerShell.
// 4. Guarda la palabra buscada en dos archivos:
//    - `conversion.umg`: La palabra encriptada y procesada con XOR.
//    - `informacion_original.umg`: La palabra original.
//
// Notas:
// - Si la palabra no se encuentra en el �rbol, muestra un mensaje de error.
// - Utiliza las funciones `encriptarPalabra` y `aplicarXOR` para proteger los datos antes de guardarlos.
// - La reproducci�n de audio requiere que PowerShell est� disponible en el sistema.

void mostrarTraduccion(Nodo* raiz, const string& rutaUsuario) {
    string palabraBuscada;
    int idioma;

    // Solicitar al usuario la palabra en espa�ol que desea buscar.
    cout << "\nIngrese una palabra en espanol: ";
    cin >> palabraBuscada;

    // Buscar la palabra en el �rbol AVL.
    Nodo* nodo = buscar(raiz, palabraBuscada);
    if (!nodo) {
        cout << "Palabra no encontrada.\n";
        return;
    }

    // Solicitar al usuario que seleccione un idioma para la traducci�n.
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

    // Reproducir la traducci�n en forma de audio utilizando PowerShell.
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



// Funci�n para mostrar el historial de palabras buscadas por el usuario.
// Las palabras se desencriptan y se muestran en su forma original.
//
// Par�metros:
// - rutaUsuario: Ruta de la carpeta del usuario actual, donde se encuentra el archivo `conversion.umg`.
//
// Proceso:
// 1. Abre el archivo `conversion.umg` que contiene las palabras encriptadas con XOR.
// 2. Lee la llave del archivo `llave.umg` para desencriptar las palabras.
// 3. Para cada palabra encriptada:
//    - Aplica la operaci�n XOR para revertir la encriptaci�n.
//    - Desencripta la palabra utilizando la tabla de desencriptaci�n.
//    - Muestra la palabra original.
//
// Notas:
// - Si el archivo `conversion.umg` no existe o no se puede abrir, muestra un mensaje de error.
// - Utiliza las funciones `deshacerXOR` y `desencriptarPalabra` para procesar las palabras.
// - La llave debe coincidir con la utilizada para encriptar las palabras, de lo contrario, el resultado ser� incorrecto.

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
        // Deshacer el XOR primero para revertir la encriptaci�n.
        string palabraConXORDeshecho = deshacerXOR(palabraEncriptada, llave);
        // Desencriptar la palabra utilizando la tabla de desencriptaci�n.
        string palabraOriginal = desencriptarPalabra(palabraConXORDeshecho);
        // Mostrar la palabra original.
        cout << palabraOriginal << endl;
    }

    archivo.close();
}



// Funci�n para mostrar el ranking de palabras m�s buscadas por el usuario.
// Las palabras se desencriptan, se cuentan sus frecuencias y se ordenan en orden descendente.
//
// Par�metros:
// - rutaUsuario: Ruta de la carpeta del usuario actual, donde se encuentra el archivo `conversion.umg`.
//
// Proceso:
// 1. Abre el archivo `conversion.umg` que contiene las palabras encriptadas con XOR.
// 2. Lee la llave del archivo `llave.umg` para desencriptar las palabras.
// 3. Para cada palabra encriptada:
//    - Aplica la operaci�n XOR para revertir la encriptaci�n.
//    - Desencripta la palabra utilizando la tabla de desencriptaci�n.
//    - Incrementa el contador de frecuencia de la palabra en un mapa.
// 4. Convierte el mapa de frecuencias en un vector de pares clave-valor.
// 5. Ordena el vector en orden descendente seg�n la frecuencia de las palabras.
// 6. Muestra el ranking de palabras m�s buscadas en la consola.
//
// Notas:
// - Si el archivo `conversion.umg` no existe o no se puede abrir, muestra un mensaje de error.
// - Utiliza las funciones `deshacerXOR` y `desencriptarPalabra` para procesar las palabras.
// - La llave debe coincidir con la utilizada para encriptar las palabras, de lo contrario, el resultado ser� incorrecto.

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
        // Deshacer el XOR primero para revertir la encriptaci�n.
        string palabraConXORDeshecho = deshacerXOR(palabraEncriptada, llave);
        // Desencriptar la palabra utilizando la tabla de desencriptaci�n.
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

    // Mostrar el ranking de palabras m�s buscadas.
    cout << "\n--- RANKING DE PALABRAS M�S BUSCADAS ---\n";
    for (const auto& par : ranking) {
        cout << par.first << ": " << par.second << " veces\n";
    }
}



// Funci�n para guardar el contenido del �rbol AVL en un archivo utilizando un recorrido inorden.
// El recorrido inorden asegura que las palabras se guarden en orden alfab�tico.
//
// Par�metros:
// - nodo: Puntero al nodo actual del �rbol AVL que se est� procesando.
// - archivoOut: Flujo de salida hacia el archivo donde se guardar�n las palabras.
//
// Proceso:
// 1. Si el nodo actual es nulo, retorna (caso base de la recursi�n).
// 2. Llama recursivamente a la funci�n para procesar el sub�rbol izquierdo.
// 3. Escribe la palabra y sus traducciones en el archivo en formato CSV (separadas por comas).
// 4. Llama recursivamente a la funci�n para procesar el sub�rbol derecho.
//
// Notas:
// - El archivo debe estar abierto antes de llamar a esta funci�n.
// - Cada l�nea del archivo contiene una palabra en espa�ol y sus traducciones en otros idiomas.

void guardarEnArchivo(Nodo* nodo, ofstream& archivoOut) {
    if (!nodo) return; // Caso base: si el nodo es nulo, no hace nada.

    // Recorrer el sub�rbol izquierdo.
    guardarEnArchivo(nodo->izquierda, archivoOut);

    // Escribir la palabra y sus traducciones en el archivo.
    archivoOut << nodo->palabra.espanol << "," << nodo->palabra.ingles << ","
        << nodo->palabra.aleman << "," << nodo->palabra.frances << ","
        << nodo->palabra.italiano << endl;

    // Recorrer el sub�rbol derecho.
    guardarEnArchivo(nodo->derecha, archivoOut);
}




//==========================FUNCIONES DE LOGIN==========================



// Funci�n para autenticar a un usuario utilizando un archivo de usuarios encriptados.
//
// Par�metros:
// - usuarioActual: Referencia a una cadena donde se almacenar� el nombre del usuario autenticado.
//
// Proceso:
// 1. Solicita al usuario que ingrese su nombre de usuario y clave.
// 2. Abre el archivo `usuarios.umg` que contiene los nombres de usuario y claves encriptados.
// 3. Para cada l�nea del archivo:
//    - Desencripta el nombre de usuario y la clave utilizando la funci�n `desencriptarPalabra`.
//    - Compara los datos desencriptados con los ingresados por el usuario.
// 4. Si se encuentra una coincidencia:
//    - Almacena el nombre de usuario desencriptado en `usuarioActual`.
//    - Retorna `true` indicando que la autenticaci�n fue exitosa.
// 5. Si no se encuentra coincidencia, retorna `false`.
//
// Notas:
// - Si el archivo `usuarios.umg` no existe o no se puede abrir, muestra un mensaje de error y retorna `false`.
// - La funci�n utiliza encriptaci�n y desencriptaci�n para proteger los datos sensibles de los usuarios.

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
    // Leer cada l�nea del archivo.
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string uEncriptado, cEncriptado;
        // Dividir la l�nea en nombre de usuario y clave encriptados.
        if (getline(ss, uEncriptado, ',') && getline(ss, cEncriptado, ',')) {
            // Desencriptar el usuario y la clave.
            string uDesencriptado = desencriptarPalabra(uEncriptado);
            string cDesencriptado = desencriptarPalabra(cEncriptado);

            // Comparar con los datos ingresados.
            if (uDesencriptado == usuario && cDesencriptado == clave) {
                usuarioActual = uDesencriptado; // Guardar el nombre de usuario desencriptado.
                return true; // Autenticaci�n exitosa.
            }
        }
    }

    return false; // Si no se encuentra coincidencia.
}



// Funci�n para registrar un nuevo usuario en el sistema.
// El nombre de usuario y la clave se encriptan y se almacenan en un archivo.
// Adem�s, se crea una carpeta espec�fica para el usuario con archivos iniciales.
//
// Proceso:
// 1. Solicita al usuario que ingrese un nombre de usuario y una clave.
// 2. Verifica si el nombre de usuario ya existe en el archivo `usuarios.umg`.
//    - Si ya existe, muestra un mensaje de error y finaliza el registro.
// 3. Encripta el nombre de usuario y la clave utilizando la funci�n `encriptarPalabra`.
// 4. Almacena el nombre de usuario y la clave encriptados en el archivo `usuarios.umg`.
// 5. Crea una carpeta espec�fica para el usuario en `C:\\traductor\\usuarios\\`.
// 6. Genera una llave �nica para el usuario utilizando la operaci�n XOR y la almacena en un archivo.
// 7. Crea archivos iniciales vac�os (`conversion.umg` y `informacion_original.umg`) en la carpeta del usuario.
//
// Notas:
// - Si el archivo `usuarios.umg` no existe o no se puede abrir, muestra un mensaje de error.
// - La llave generada se utiliza para encriptar y desencriptar datos espec�ficos del usuario.
// - La funci�n utiliza encriptaci�n para proteger los datos sensibles de los usuarios.

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

    // Generar una llave �nica utilizando XOR.
    string semilla = "umg"; // Semilla fija para generar la llave.
    string llave = "";
    for (size_t i = 0; i < nuevoUsuario.size(); ++i) {
        llave += nuevoUsuario[i] ^ semilla[i % semilla.size()];
    }

    // Guardar la llave en un archivo con la extensi�n `.umg`.
    ofstream llaveFile(rutaUsuario + "\\llave.umg");
    if (llaveFile.is_open()) {
        llaveFile << llave << endl;
        llaveFile.close();
    }
    else {
        cerr << "Error al crear el archivo de llave.\n";
    }

    // Crear los archivos iniciales vac�os en la carpeta del usuario.
    ofstream conversionFile(rutaUsuario + "\\conversion.umg");
    conversionFile.close(); // Crear archivo vac�o.

    ofstream infoFile(rutaUsuario + "\\informacion_original.umg");
    infoFile.close(); // Crear archivo vac�o.

    cout << "Usuario registrado con �xito.\n"; 
}




//==========================FUNCIONES PRINCIPALES==========================



// Funci�n principal del programa.
// Controla el flujo general: descompresi�n inicial, autenticaci�n, men� principal y compresi�n final.
//
// Proceso general:
// 1. Si existe un archivo comprimido (.huff), descomprime la carpeta de trabajo al iniciar.
// 2. Solicita al usuario iniciar sesi�n o registrarse hasta que la autenticaci�n sea exitosa.
// 3. Carga las palabras al �rbol AVL desde el archivo principal de palabras.
// 4. Muestra un men� con opciones para buscar, agregar, eliminar palabras, ver historial y ranking.
// 5. Al salir, comprime el contenido de la carpeta y elimina los archivos originales para mantener solo el respaldo comprimido.

int main() {
    // Rutas principales para la compresi�n y descompresi�n
    const string rutaCarpetaHuffman = "C:\\traductorhuffman";
    const string archivoHuff = rutaCarpetaHuffman + "\\traductor.huff";
    const string rutaCarpeta = "C:\\traductor";

    // 1. Descomprimir al inicio si existe el archivo comprimido
    if (fs::exists(archivoHuff)) {
        descomprimirCarpetaHuffman(rutaCarpeta, archivoHuff);
    }

    string usuarioActual;
    int opcionInicio;

    // 2. Mostrar mensaje de bienvenida y manejar autenticaci�n
    cout << "--- BIENVENIDO AL TRADUCTOR ---\n";
    while (true) {
        cout << "1. Iniciar sesi�n\n";
        cout << "2. Registrarse\n";
        cout << "Seleccione una opci�n: ";
        cin >> opcionInicio;

        if (opcionInicio == 2) {
            registrarUsuario(); // Permite registrar un nuevo usuario
        }

        if (login(usuarioActual)) { // Intenta iniciar sesi�n
            cout << "Bienvenido, " << usuarioActual << "!\n";
            break; // Sale del bucle si la autenticaci�n es exitosa
        }
        else {
            cout << "Credenciales inv�lidas. Intente de nuevo.\n";
        }
    }

    // 3. Definir la ruta de la carpeta del usuario autenticado
    string rutaUsuario = "C:\\traductor\\usuarios\\" + usuarioActual;

    // 4. Cargar las palabras al �rbol AVL desde el archivo principal
    Nodo* raiz = cargarPalabras();

    int opcion;
    // 5. Bucle principal del men� de usuario
    do {
        cout << "\n--- MENU ---\n";
        cout << "1. Buscar una palabra\n";
        cout << "2. Agregar una nueva palabra\n";
        cout << "3. Eliminar una palabra\n";
        cout << "4. Mostrar historial de palabras buscadas\n";
        cout << "5. Mostrar ranking de palabras m�s buscadas\n";
        cout << "6. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        // Ejecutar la opci�n seleccionada
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

            raiz = eliminarPalabra(raiz, palabra); // Eliminar una palabra del �rbol

            // Reescribir el archivo de palabras tras la eliminaci�n
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
            mostrarRanking(rutaUsuario); // Mostrar ranking de palabras m�s buscadas
        }
        // Si la opci�n es 6, el bucle termina y el programa sale

    } while (opcion != 6);

    // 6. Al salir, comprimir la carpeta y limpiar archivos originales
    cout << "Saliendo del programa...\n";
    comprimirCarpetaHuffman(rutaCarpeta, archivoHuff);
    eliminarCarpetaContenido("C:\\traductor");

    return 0;
}

