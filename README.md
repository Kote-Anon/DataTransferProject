# Data Transfer Server and Client

This project is a simple file(.cvs for now) transfer server and client. It's a simple, socket based project build with cmake and C++. 
This project is mainly created to learn myself how does networking and GIT work, future plans are mainly to be considered while working with this project. 

## Features

- **Server (DTPServer folder):** Simple server, recieves and stores send files from clients, future features are to be expanded in the future.   
- **Client (DTPClient):** Simple client, sends data to server, saves computer info, future features are to be expanded in the future.
- **File Transfer:** Supports only .cvs files, only Client to Server file transfer (to be reworked in future).
- **Error Handling:** Includes basic error handling for connection issues and file transfer failures.

## Getting Started

### Prerequisites

- GCC 3.x
- A network connection between the server and client(s)

### Installation

1. Clone the repository:

```bash
git clone https://github.com/Kote-Anon/DataTransferProject
```
2. Navige to the project directory

```bash
cd DataTransferProject
```

### Starting Serve

1. Access server files

```bash
cd DTPServer/out/build/
```

2. Build server

```bash
cmake -S ../../ -B .
make
```
3. Start server

In build diretory start server by typing
```bash
./dtps
```
This will start server

4. Closing server

To close server you need to type 
```bash
close
```
after recieving any data or error server will close ensuring all files are working

### Starting Client and sending data

1. Access client files

```bash
cd DTPClient/out/build/
```

2. Checking settings files

in build directory check for ```DTPCSetting.txt``` file and add changes to it by filling it accordingly to given example in it, make sure not to use any spaces.

3. Build client

```bash
cmake -S ../../ -B .
make
```

4. Start client and sending data

```bash
./dtpc <file_name>.cvs
```

this will send .cvs file and save computer data.

## Contribiuting

Contributions are welcome! If you'd like to contribute to this project, please follow these steps:

   1. Fork the repository.
   2. Create a new branch (git checkout -b feature/new-feature).
   3. Make your changes.
   4. Commit your changes (git commit -am 'Add new feature').
   5. Push to the branch (git push origin feature/new-feature).
   6. Create a new pull request.

## License

[Apache 2.0](https://github.com/Kote-Anon/DataTransferProject/blob/main/LICENSE) 

## Acknowledgments

This project is created mainly to learn and study networking.

## Contact Information

For any questions, suggestions, or feedback, please feel free to contact the project maintainer:

    -> Anthony
    -> antonibedkowski+DTP@gmail.com