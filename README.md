# Command line shell
This program reads command line from keyboard. Then find the API which it is mapped to from the database.\
The API is a simple fuction print out the name of command line to show that the API called is TRUE.

##Build\
$ Go to the mclishell path. \
$ make all\
$ ./Atmain\
$ make clean

##Run
There are some command supported like:\
	+ device init\
	+ close shell\
	+ exit\
	+ default (print out "Invalid command")

#The getchar folder\
This folder include a custom getchar funtion.\
This is the wrapped getchar fuction in C, but it is not useful.\
This fuction will call API for each input key. The key is support is backspace. It remove one
character out of screen.
