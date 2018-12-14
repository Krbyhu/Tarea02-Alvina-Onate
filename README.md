# Prueba


# Instalación
### Obtener repositorio

Para clonar repositorio:
```
git clone https://github.com/Krbyhu/Prueba.git
```

### Modificación parametros

Se deben modificar los parametros del archivo ```config.json``` 
```
{
	"ip"	:	"A.B.C.D",
	"puerto"	:	54000,
	"root_dir"	:	"/home/user/tarea2/WWW-data"
	"notFoundFile":"/home/user/Tarea2/WWW-error"
}
```


### Compilación

Para compilar debe ingresar a la carpeta donde se clono el repositorio ej:
```
cd Tarea2
make clean
make
```

### Ejecución

Una vez se haya compilado, ejecutar:
```
./servidor
```
Ya ejecutado el programa, debe dirigirse a un navegador he ingresar:
```
http://A.B.C.D:54000/uno.html
```
Utilizando la IP y Puerto que se modifico en el archivo ```config.json```


### Modo de uso

El servidor redirige a cuatro paginas.
*uno.html
*dos.html
*tres.html
Se encuentran almacenadas en ```WWW-data```

*404.html
El la pagina de error la cual se redirige en caso de que no se solicita ninguna de las paginas anteriores.
Se encuentra en ```WWW-error```

