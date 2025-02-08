# Bibliotech
Piccolo progetto per l'uni in realizzato in C++ e Qt. 
Implementato seguendo best practices e principi SOLID.
Si tratta di una architettura MVC.

I requisiti del progetto si trovano nel file `requisiti.pdf`.

## Build Status
![Windows Build](https://github.com/devVux/Bibliotech/actions/workflows/windows-build.yml/badge.svg?branch=master)
![Linux Build](https://github.com/devVux/Bibliotech/actions/workflows/linux-build.yml/badge.svg?branch=master)

### Short MVC Explaination
In the classic MVC pattern:
- Model is a Subject, notifies both View and Controller
- View is an Observer of the Model (not the Controller)
- Controller updates the Model, but isn't typically an Observer
- View sends user actions to Controller
- Controller modifies Model based on View's input