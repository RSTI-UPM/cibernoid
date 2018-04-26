
Intalar java 8 y netbeans

Instalación java8
sudo add-apt-repository ppa:webupd8team/java
sudo apt-get update
sudo apt-get install oracle-java8-set-default

Intalación netbeans
wget -c http://download.netbeans.org/netbeans/8.2/final/bundles/netbeans-8.2-linux.sh
chmod +x netbeans-8.2-linux.sh 
./netbeans-8.2-linux.sh
En la ventana del instalodr, seleccionamos "Customize" y seleccionamos "Apache Tomcat 8.0.27" y seguimos con la instalación. Al llegar a la ventana "Choose the installation folder and JDK", realizamos la siguiente configuración de rutas:
Install the NetBeans IDE to:"Path a la carpeta que se ha creado en la instalación" Ej. "/home/user/netbeans-8.2"
JDK for NetBeans IDE:"Path a la librería de java 8" Ej."/usr/lib/jvm/java-8-oracle"
En la siguiente elegimos la ruta para instalar Apache Tomcat.
Y terminamos la configuración de la intalación y se instalará NetBeans.

cd netbeans-8.2

Descargamos gson-2.2.2.jar.
wget -c http://central.maven.org/maven2/com/google/code/gson/gson/2.2.2/gson-2.2.2.jar



Instalar postgres y pgAdminIII 

sudo apt-get install postgresql-9.6

Entramos en el usuario postgres que se ha creado y cambiamos la contraseña
su - postgres
psql
\password postgres
\exit
systemctl restart postgresql

sudo apt-get install pgadmin3
sudo apt-get install smbclient

Abrimos el programa pgadminIII y configuramos un servidor para la base de datos.
File > Add Server

Name: Mi servidor
Host: localhost
Port: 5432
Service: 
Maintenance: postgres
Username: postgres
Password: 123
Group: Servers

Una vez creado el sevidor, creamos las tablas

SeverGroups > Servers > Mi servidor > Databases > postgres

Seleccionamos en la parte superior "Execute arbitrary SQL queries" (Simbolo con las letras SQL) y se abre una pestaña con un editor de SQL. Copiamos las sentecias SQL siguientes:

		-- Table: public.coordenadas
		CREATE TABLE public.coordenadas
		(
		id integer NOT NULL,
		latitud double precision NOT NULL,
		longitud double precision NOT NULL,
		radio integer NOT NULL,
		CONSTRAINT coordenadas_pkey PRIMARY KEY (id)
		)
		WITH (
		OIDS=FALSE
		);
		ALTER TABLE public.coordenadas
		OWNER TO postgres;

		-- Table: public.departamentos
		CREATE TABLE public.departamentos
		(
		id integer NOT NULL,
		nombre character varying(255),
		horario character varying(5) NOT NULL,
		mascara_hora integer NOT NULL,
		mascara_fecha integer NOT NULL,
		CONSTRAINT departamentos_pkey PRIMARY KEY (id)
		)
		WITH (
		OIDS=FALSE
		);
		ALTER TABLE public.departamentos
		OWNER TO postgres;

		-- Table: public.usuarios
		CREATE TABLE public.usuarios
		(
		id integer NOT NULL,
		nombre character varying(255) NOT NULL,
		departamento integer NOT NULL,
		CONSTRAINT usuarios_pkey PRIMARY KEY (id),
		CONSTRAINT usuarios_departamento_fkey FOREIGN KEY (departamento)
		REFERENCES public.departamentos (id) MATCH SIMPLE
		ON UPDATE NO ACTION ON DELETE NO ACTION
		)
		WITH (
		OIDS=FALSE
		);
		ALTER TABLE public.usuarios
		OWNER TO postgres;

		CREATE TABLE public.wifis
		(
		ssid character varying(255) NOT NULL,
		potencia integer NOT NULL,
		CONSTRAINT wifis_pkey PRIMARY KEY (ssid)
		)
		WITH (
		OIDS=FALSE
		);
		ALTER TABLE public.wifis
		OWNER TO postgres;

Ejecutamos, "Execute query" (Símbolo play verde) y salimos. Ya se ha crado la base de datos.

Abrimos el programa netbeans-8.2 y cargamos el proyecto.
File > Open project y seleccionamos la carpeta ServerCiberNoid_1 que se encuentra en el proyecto cibernoid de Github https://github.com/pablo17993/cibernoid

Una vez cargado, pinchamos en el proyecto, botón derecho y seleccionamos "Resolve Reference Problems..".
Project Problems: "gson-2.2.2.jar ..." , hacemos click en "Resolve..." y seleccionamos el gson-2.2.2.jar dentro de la carpeta netbeans-8.2 que acabamos de descargar. 

Por último, ejecutamos el servidor "RunProject".

Para realizar el challenge con el servidor tiene que estar en la misma red que el movil o el dispositivo y añadir la dirección IP del servidor en el archivo "https://github.com/pablo17993/cibernoid/blob/master/Archivos_android_Api_remoto/apiAnChallenge.cpp" antes de crear la librería dinámica .so.  








