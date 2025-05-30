# Traductor-AVL-Huffman

A secure multilingual translator written in C++17.

Features include:
- Fast word lookup and management using an AVL tree.
- Supports Spanish, English, German, French, and Italian.
- User authentication with encrypted credentials.
- Search history and ranking, protected with custom encryption and XOR.
- Huffman compression for efficient backup and restore of all data.
- Text-to-speech for translated words (Windows/PowerShell).

## Folder Structure & Paths

- Main app data:  
  `C:\traductor\`
- User data:  
  `C:\traductor\usuarios\<nombre_usuario>\`
- Dictionary file:  
  `C:\traductor\palabras.umg`
- User credentials:  
  `C:\traductor\usuarios.umg`
- Huffman backup:  
  `C:\traductorhuffman\traductor.huff`

## Requirements

- Windows OS
- C++17 compatible compiler (e.g., Visual Studio 2022)
- PowerShell (for text-to-speech)

## Usage

1. Build the project in Visual Studio 2022.
2. Run the executable.
3. Register a new user or log in.
4. Use the menu to search, add, or delete words, view history, or see ranking.

All user data and dictionary files are stored and compressed automatically.

## License

This project is provided for educational purposes.

All user data and dictionary files are stored and compressed automatically.

## License

This project is provided for educational purposes.
