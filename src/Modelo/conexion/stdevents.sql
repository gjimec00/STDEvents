CREATE DATABASE STDEVENTS;

CREATE TABLE administrador (
dni varchar(10) PRIMARY KEY UNIQUE,
nombre varchar(50),
apellidos varchar(50),
telefono INT,
correo varchar(50),
contrasena varchar(50)
);

CREATE TABLE clientes (
dni varchar(10) PRIMARY KEY UNIQUE,
nombre varchar(50),
apellidos varchar(50),
telefono INT,
correo varchar(50),
contrasena varchar(50),
abonado boolean DEFAULT 0,
numAsientoAbonado INT CHECK (numAsientoAbonado <= 500)
);

CREATE TABLE productos (
idProducto INT auto_increment PRIMARY KEY,
nombre varchar(50),
cantidad INT,
precio double,
descripcion text,
talla varchar(5),
color varchar(20)
);

CREATE TABLE eventos (
idEvento INT auto_increment PRIMARY KEY,
nombre varchar(50),
descripcion text,
fecha date,
hora time,
tipo varchar(50),
dniAdmin varchar(10),
FOREIGN KEY (dniAdmin) REFERENCES administrador(dni)
);

CREATE TABLE asientos (
idAsiento INT auto_increment PRIMARY KEY,
numAsiento INT CHECK (numAsiento <= 500),
precio double,
idEvento INT,
FOREIGN KEY (idEvento) REFERENCES eventos(idEvento)
);

CREATE TABLE pagos (
idPago INT auto_increment PRIMARY KEY,
fecha date,
hora time,
dniCliente varchar(10),
precioTotal double,
FOREIGN KEY (dniCliente) REFERENCES clientes(dni),
idEvento INT DEFAULT 0,
FOREIGN KEY (idEvento) REFERENCES eventos(idEvento),
idProducto INT,
FOREIGN KEY (idProducto) REFERENCES productos(idProducto)
);

CREATE TABLE reportes (
idReporte INT auto_increment PRIMARY KEY,
descripcion text,
dniAdmin varchar(10),
FOREIGN KEY (dniAdmin) REFERENCES administrador(dni)
);
INSERT INTO `stdevents`.`administrador` (`dni`, `nombre`, `apellidos`, `telefono`, `correo`, `contrasena`) VALUES ('12345678A', 'Admin', 'admin', '123456789', 'admin@admin.com', 'admin');
INSERT INTO `stdevents`.`clientes` (`dni`, `nombre`, `apellidos`, `telefono`, `correo`, `contrasena`, `abonado`) VALUES ('71745254C', 'Cesar', 'Garcia', '123456789', 'cesar07@gmail.com', '1234', '0');
INSERT INTO `stdevents`.`clientes` (`dni`, `nombre`, `apellidos`, `telefono`, `correo`, `contrasena`, `abonado`) VALUES ('71186576N', 'Guillermo', 'Jimeno', '123456987', 'guillermo85@gmail.com', '12345', '0');
INSERT INTO `stdevents`.`clientes` (`dni`, `nombre`, `apellidos`, `telefono`, `correo`, `contrasena`, `abonado`) VALUES ('71959189D', 'Alba', 'Magdaleno', '123654789', 'alba94@gmail.com', '123', '0');
INSERT INTO `stdevents`.`clientes` (`dni`, `nombre`, `apellidos`, `telefono`, `correo`, `contrasena`, `abonado`) VALUES ('02770185L', 'Kevin', 'Alvarez', '123654987', 'kevin32@gmail.com', '123456', '0');
INSERT INTO `stdevents`.`clientes` (`dni`, `nombre`, `apellidos`, `telefono`, `correo`, `contrasena`, `abonado`) VALUES ('81686940W', 'Marcos', 'Martinez', '321456789', 'marcos54@gmail.com', '321', '0');
INSERT INTO `stdevents`.`clientes` (`dni`, `nombre`, `apellidos`, `telefono`, `correo`, `contrasena`, `abonado`) VALUES ('31482435N', 'Carlos', 'Fernandez', '321654789', 'carlos56@gmail.com', '4321', '0');
INSERT INTO `stdevents`.`clientes` (`dni`, `nombre`, `apellidos`, `telefono`, `correo`, `contrasena`, `abonado`) VALUES ('19355700G', 'Laura', 'Jimenez', '124356789', 'laura77@gmail.com', '5421', '0');
INSERT INTO `stdevents`.`clientes` (`dni`, `nombre`, `apellidos`, `telefono`, `correo`, `contrasena`, `abonado`) VALUES ('72642004T', 'Marta', 'Perez', '123546789', 'marta89@gmail.com', '4215', '0');
INSERT INTO `stdevents`.`clientes` (`dni`, `nombre`, `apellidos`, `telefono`, `correo`, `contrasena`, `abonado`) VALUES ('60039818C', 'Lucia', 'Gonzalez', '564321987', 'lucia04@gmail.com', '53421', '0');
INSERT INTO `stdevents`.`clientes` (`dni`, `nombre`, `apellidos`, `telefono`, `correo`, `contrasena`, `abonado`) VALUES ('64452661Z', 'Jose', 'Gomez', '897546231', 'jose23@gmail.com', '65321', '0');
INSERT INTO `stdevents`.`productos` (`idProducto`, `nombre`, `cantidad`, `precio`, `descripcion`, `talla`, `color`) VALUES ('1', 'Camiseta', '35', '15.99', 'Camiseta con logo de equipos', 'S', 'Negro');
INSERT INTO `stdevents`.`productos` (`idProducto`, `nombre`, `cantidad`, `precio`, `descripcion`, `talla`, `color`) VALUES ('2', 'Camiseta', '20', '15.99', 'Camiseta con logo de equipos', 'M', 'Negro');
INSERT INTO `stdevents`.`productos` (`idProducto`, `nombre`, `cantidad`, `precio`, `descripcion`, `talla`, `color`) VALUES ('3', 'Camiseta', '40', '15.99', 'Camiseta con logo de equipos', 'L', 'Negro');
INSERT INTO `stdevents`.`productos` (`idProducto`, `nombre`, `cantidad`, `precio`, `descripcion`, `talla`, `color`) VALUES ('4', 'Camiseta', '25', '15.99', 'Camiseta con logo de equipos', 'XL', 'Negro');
INSERT INTO `stdevents`.`productos` (`idProducto`, `nombre`, `cantidad`, `precio`, `descripcion`, `talla`, `color`) VALUES ('5', 'Camiseta', '10', '15.99', 'Camiseta con logo de equipos', 'S', 'Blanco');
INSERT INTO `stdevents`.`productos` (`idProducto`, `nombre`, `cantidad`, `precio`, `descripcion`, `talla`, `color`) VALUES ('6', 'Camiseta', '18', '15.99', 'Camiseta con logo de equipos', 'M', 'Blanco');
INSERT INTO `stdevents`.`productos` (`idProducto`, `nombre`, `cantidad`, `precio`, `descripcion`, `talla`, `color`) VALUES ('7', 'Camiseta', '26', '15.99', 'Camiseta con logo de equipos', 'L', 'Blanco');
INSERT INTO `stdevents`.`productos` (`idProducto`, `nombre`, `cantidad`, `precio`, `descripcion`, `talla`, `color`) VALUES ('8', 'Camiseta', '37', '15.99', 'Camiseta con logo de equipos', 'XL', 'Blanco');
INSERT INTO `stdevents`.`productos` (`idProducto`, `nombre`, `cantidad`, `precio`, `descripcion`, `talla`, `color`) VALUES ('9', 'Sudadera', '40', '25.99', 'Sudadera con tematica del evento mas proximo', 'S', 'Marron');
INSERT INTO `stdevents`.`productos` (`idProducto`, `nombre`, `cantidad`, `precio`, `descripcion`, `talla`, `color`) VALUES ('10', 'Sudadera', '55', '25.99', 'Sudadera con tematica del evento mas proximo', 'M', 'Marron');
INSERT INTO `stdevents`.`productos` (`idProducto`, `nombre`, `cantidad`, `precio`, `descripcion`, `talla`, `color`) VALUES ('11', 'Sudadera', '20', '25.99', 'Sudadera con tematica del evento mas proximo', 'L', 'Verde');
INSERT INTO `stdevents`.`productos` (`idProducto`, `nombre`, `cantidad`, `precio`, `descripcion`, `talla`, `color`) VALUES ('12', 'Sudadera', '30', '25.99', 'Sudadera con tematica del evento mas proximo', 'XL', 'Negro');
INSERT INTO `stdevents`.`productos` (`idProducto`, `nombre`, `cantidad`, `precio`, `descripcion`, `talla`, `color`) VALUES ('13', 'Pantalon', '22', '28.99', 'Pantalon de chandal marca STD', 'S', 'Azul');
INSERT INTO `stdevents`.`productos` (`idProducto`, `nombre`, `cantidad`, `precio`, `descripcion`, `talla`, `color`) VALUES ('14', 'Pantalon', '10', '28.99', 'Pantalon de chandal marca STD', 'L', 'Negro');
INSERT INTO `stdevents`.`productos` (`idProducto`, `nombre`, `cantidad`, `precio`, `descripcion`, `talla`, `color`) VALUES ('16', 'Pantalon', '6', '28.99', 'Pantalon de chandal marca STD', 'M', 'Negro');
INSERT INTO `stdevents`.`productos` (`idProducto`, `nombre`, `cantidad`, `precio`, `descripcion`, `talla`, `color`) VALUES ('17', 'Pantalon', '9', '28.99', 'Pantalon de chandal marca STD', 'XL', 'Blanco');
INSERT INTO `stdevents`.`productos` (`idProducto`, `nombre`, `cantidad`, `precio`, `descripcion`, `talla`, `color`) VALUES ('18', 'Bufanda', '15', '9.99', 'Bufanda para evento proximo', 'S', 'Blanco');
INSERT INTO `stdevents`.`productos` (`idProducto`, `nombre`, `cantidad`, `precio`, `descripcion`, `talla`, `color`) VALUES ('19', 'Bufanda', '20', '9.99', 'Bufanda para evento proximo', 'M', 'Blanco');
INSERT INTO `stdevents`.`productos` (`idProducto`, `nombre`, `cantidad`, `precio`, `descripcion`, `talla`, `color`) VALUES ('20', 'Calcetines', '11', '5.99', 'Calcetines marca STD', 'S', 'Negro');
INSERT INTO `stdevents`.`productos` (`idProducto`, `nombre`, `cantidad`, `precio`, `descripcion`, `talla`, `color`) VALUES ('21', 'Calcetines', '14', '5.99', 'Calcetines marca STD', 'M', 'Negro');
INSERT INTO `stdevents`.`productos` (`idProducto`, `nombre`, `cantidad`, `precio`, `descripcion`, `talla`, `color`) VALUES ('22', 'Calcetines', '17', '5.99', 'Calcetines marca STD', 'L', 'Negro');
INSERT INTO `stdevents`.`productos` (`idProducto`, `nombre`, `cantidad`, `precio`, `descripcion`, `talla`, `color`) VALUES ('23', 'Cazadora', '18', '45.99', 'Cazadora marca STD', 'S', 'Verde');
INSERT INTO `stdevents`.`productos` (`idProducto`, `nombre`, `cantidad`, `precio`, `descripcion`, `talla`, `color`) VALUES ('24', 'Cazadora', '20', '45.99', 'Cazadora marca STD', 'M', 'Verde');
INSERT INTO `stdevents`.`productos` (`idProducto`, `nombre`, `cantidad`, `precio`, `descripcion`, `talla`, `color`) VALUES ('25', 'Cazadora', '24', '45.99', 'Cazadora marca STD', 'L', 'Blanca');
INSERT INTO `stdevents`.`productos` (`idProducto`, `nombre`, `cantidad`, `precio`, `descripcion`, `talla`, `color`) VALUES ('26', 'Cazadora', '26', '45.99', 'Cazadora marca STD', 'XL', 'Negra');
INSERT INTO `stdevents`.`eventos` (`idEvento`, `nombre`, `descripcion`, `fecha`, `hora`, `tipo`, `dniAdmin`) VALUES ('1', 'Partido de Futbol', 'Partido Barcelona - Real Madrid', '2024-01-23', '16:00:00', 'Deportivo', '12345678A');
INSERT INTO `stdevents`.`eventos` (`idEvento`, `nombre`, `descripcion`, `fecha`, `hora`, `tipo`, `dniAdmin`) VALUES ('2', 'Partido de Futbol', 'Partido Atletico Madrid - Getafe', '2024-01-30', '16:30:00', 'Deportivo', '12345678A');
INSERT INTO `stdevents`.`eventos` (`idEvento`, `nombre`, `descripcion`, `fecha`, `hora`, `tipo`, `dniAdmin`) VALUES ('3', 'Partido de Futbol', 'Partido Girona - Sevilla', '2024-02-5', '18:20:00', 'Deportivo', '12345678A');
INSERT INTO `stdevents`.`eventos` (`idEvento`, `nombre`, `descripcion`, `fecha`, `hora`, `tipo`, `dniAdmin`) VALUES ('4', 'Partido de Baloncesto', 'Partido Unicaja - Zunder Palencia', '2024-02-18', '21:00:00', 'Deportivo', '12345678A');
INSERT INTO `stdevents`.`eventos` (`idEvento`, `nombre`, `descripcion`, `fecha`, `hora`, `tipo`, `dniAdmin`) VALUES ('5', 'Partido de Baloncesto', 'Partido Real Madrid - Baskonia', '2024-02-23', '21:20:00', 'Deportivo', '12345678A');
INSERT INTO `stdevents`.`eventos` (`idEvento`, `nombre`, `descripcion`, `fecha`, `hora`, `tipo`, `dniAdmin`) VALUES ('6', 'Partido de Baloncesto', 'Partido UCAM Murcia - Lenovo Tenerife', '2024-02-28', '17:30:00', 'Deportivo', '12345678A');
INSERT INTO `stdevents`.`eventos` (`idEvento`, `nombre`, `descripcion`, `fecha`, `hora`, `tipo`, `dniAdmin`) VALUES ('7', 'Concierto', 'Concierto de Green Day', '2024-03-10', '20:00:00', 'Extradeportivo', '12345678A');
INSERT INTO `stdevents`.`eventos` (`idEvento`, `nombre`, `descripcion`, `fecha`, `hora`, `tipo`, `dniAdmin`) VALUES ('8', 'Concierto', 'Concierto de The Rolling Stones', '2024-04-2', '21:30:00', 'Extradeportivo', '12345678A');
INSERT INTO `stdevents`.`eventos` (`idEvento`, `nombre`, `descripcion`, `fecha`, `hora`, `tipo`, `dniAdmin`) VALUES ('9', 'Concierto', 'Concierto de Metallica', '2024-04-23', '22:00:00', 'Extradeportivo', '12345678A');
INSERT INTO `stdevents`.`eventos` (`idEvento`, `nombre`, `descripcion`, `fecha`, `hora`, `tipo`, `dniAdmin`) VALUES ('10', 'Concierto', 'Concierto de Raphael', '2024-05-11', '19:40:00', 'Extradeportivo', '12345678A');