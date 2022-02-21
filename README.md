
# Notepad

This is a basic text editing app made in Qt for making text Bold/Unbold.
Features of this app are:

    1. Making text Bold.
    2. Superscripting/Subscripting the text.


## Installation on Ubuntu

To use this app you have to install qt5-default also.
But before that download the zip file from this github page.
There are two ways in which you can get those archives.
1. By simply clicking on "Download ZIP" button.
2. By cloning the repository using git clone command:
```bash
git clone https://github.com/0singh-ajit0/Notepad.git
```
Now, let us install qt5 using apt-get
```bash
sudo apt install qt5-default
```
- Now, go to the folder where the archive is downloaded/cloned.
- Open that folder in terminal and type the following commands:
```bash
qmake Notepad.pro
make
```


## How to run the program

Execute the file by the following command:
```bash
./Notepad
```
