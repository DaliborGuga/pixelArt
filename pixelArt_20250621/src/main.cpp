/* 30/06/2025 Versión para entregar. Quise volver a meter los gifs, y fallé
  miserablemente. Volver a jugar con un ESP con más memoria, y/o rediseñar 
  la app BT y el hard con un HC-05 o algo así por UART nativo
| Lyla está llegando en breve, así que su versión será esta.
*/
/*
// 25/06/2025 Hago roll over en las esquinas en la app BT. Queda mejor
// Grabar en la app pushea a names. así que no hay que cargar app wifi
// para actualizar names.
// Darle una segunda oportunidad al GIF. Esta versión está bien limpia
// para salir a rolar
// 20/06/2025 Ajustados los metodos a la "nueva" app web. Retrys en el fill
// y algunas otras cosas bonitas. Funciona app BT y se cuelga mucho menos 
// con la lib async.
// Reescribo comando de clear canvas en app BT  que se disparaba en falso
// Ensayo un poco; empaqueto, documento. 
// Estoy dudando de poner una página para firmware update y un navegador para 
// (al menos) borrar archivos. 
// Por ahora documentar convenientemente
// Versión 2.0 Entregable!
// Probar app BT en otro dispositivo que no sea mi cel, y navegador IOS

// 19/06/2025 Cansado que el Bluetooth me cague a palos. Ya no listo el callback
// de conexión/desconexión que se roba precioso heap. Lo hago por polling
// y a la mierda! 
// 12/06/2025 Rediseñando index- acomodar métodos a nuevo frontend
// 29/05/2025 Utilizo versiones más actuales de Asyncwebserver y asynctcp
// Cambios en platformio.ini. Parece funcionar MUCHISIMO MEJOR!
// Evaluar desempeño. Los nombres los pide en el reload de page main
// ver por qué tarda tanto - hago flag y solo los pida una vez, si no hay cambios - done!
// (save) de new images - done!
// Arreglar los métodos ahora que tenemos nombre de archivo, para el loop de dibujos - done!
// 12/05/2025 Retomo para ver de arreglar algunas cositas.
// Para empezar en el FS hacer un dir y listar los archivos mismos y no utilizar ese txt
// rancio que tenía que terminaba funcionando mal - done!
// Acomodar cosillas en carpetas en la SD - done!
// Temporizar desde el arranque si no se hace nada (ni conexion wifi ni BT)
// y ponerse automáticamente a scrollear imágenes - done!
// Quiero arreglar la pintada, sólida, sin el bucle 
// para que funcione más mejor y no sature de peticiones - Done!
// Cambio la lógica. pinto todo y subo (sincronizo) todo el dibujo como
// si viniera del converter. El efecto no es muy lindo, pero resulta
// Ver si se puede acomodar para hacer caber los gifs.
// Quizás un explorador croto para copiar, descargar, eliminar files
// Ver si se puede hacer una página para conectarse a internet y descargar images 
// y gifs desde algún lado. 
// Arreglar la app BT para que no me dé falsos negativos cuando grabo archivos:
// me ha pasado y es muy molesto. Ver cómo flushear en la app móvil y ver si puede
// hacerse más fluida
*/
/*
// 29/08/2023
// Version Release 0.0. Buggy but working
// 29/08/2023 Quise ponerle los gifs. Un boton en el index
// que haga scroll de los gifs guardados; pero lamentablemente me vuelve
// a putear con la memoria. BT, se empieza a colgar; si le saco
// bytes a la tarea frertos engancha pero se jode la SD
// en fin. Está destinado a NO SER.
// Al menos tengo mi versión cero.
// Tiene cuelgues; se termina colgando después de pelotudear un rato
// a veces no lee bien de la SD. El converter muchas veces la pincha
// Se va quedando sin heap....
// Hace mucho, y así y todo nada del todo bien.
// Solo dibujar (pixel a pixel) y grabar es bastante inofensivo
// Funciona un largo rato. Puede mejorar. Muchísimo.
// Para ir aprendiendo sobre la marcha e integrar muchas (MUCHAS)
// boludeces estuvo buenísimo
// 24/08/2023 Casi logro que coopere!
// Voy por esta línea, donde sirvo todo desde la SD
// El Json lo hago dynamic y local del callback y recién
// así logro que funcione alguna vez TODO JUNTO!!!!
// Tiene los bugs cuando mando mucha cosa desde el converter
// pero al menos funciona
// En casa NO me funciona (compila; pero el BT y la SD NO cooperan juntos)
// En el laburo (me he traído micros compilados) SI me funciona
// Ver bien las versiones de todo (y dependencias) y lograr
// hacerlo cooperar. Ya se que puede funcionar; en casa lo estoy rompiendo
// Llevar al laburo, y yastaria la versión inicial
// Documentar maomeno bien. Y dejar el todo para mas luego
// El yeite estaba en el framework. Con el 2.0.4 puede funcionar todo junto
// con el 2.0.6 (master a esta altura) NO le quedaban descriptores
// al diskio...
//  platform_packages = framework-arduinoespressif32 @ https://github.com/espressif/arduino-esp32.git#2.0.4
// 13/08/2023 El crack de Isa me hizo un housing muy cheto
// Hago esta versión para tenerlo andando y que se vea un poco
// lindo. Mientras veo si resolveré de fondo (seguramente NO)
// Dejo todo el combo-wombo. Tecla de BT/WEB, led con modos de operación
// y dejo como AP! Ver si todo que  dapronto y dejar quietito por ahora
// Pero como no podía ser de otra manera ahora no funciona ni lo que antes funcionaba!
// Se rompió el BT y anda como el ojete (será por usar AP?)
// Mato el blinkeo de led a ver si es eso (no creo)-Saque el blinken y sigue muerto: debe ser otra cosa!
*/
/*
// 22/07/2023 Puse el index en progmem y TAMBIEN SE ROMPE
// Creo que tiene que ver con el AsyncTCP subyacente a asynwebserver
// Funca un par de veces, pero despues le da por romperse para siempre
// Voy a probar SACAR lo del bluetooth stack; ver si funciona bien SIN eso
// y de ser así: hacer DOS programas distintos, uno para el web server y otro para el bluetooth
// Voy a poner uno en cada particion OTA diferente y voy a toquetear el
// bootloader 2nd stage para bootear en una u otra partición dependiendo
// de un pin de entrada (boton de seleccion que ya tengo)
// UN PIJAZO! Pero primero probaré si sacar el bluetooth es
// la manganeta para que quede con vida más tiempo!
// El upload to device me mata todo despues....pescar si esa async request
// queda vida. Matarla y re-listarla!
// Debe ser por la memoria que le toma responder...¿? con 16 y 32 no se rompe SIEMPRE!
// Quizá se rompa con el paso del tiempo. Ver de "liberar memorias"
// Ver si el heap o algo así es el causante!
// 16/07/2023
// Casi siempre despues de un back de converter, se pincha!
// SI SUBIO UN FILE DE 64 (no grabar - solo subir al device)!!!
// Ver si desconectar/conectar (creo que tampoco)
// La función ARP NO es tan mágica. Se sigue colgando MUY seguido
// Y no quiere volver a la vida
// Me parece que lo arreglé a cachetazos limpios. En cada solicitud
// de archivos de la SD, cierro y abro filesystem de la SD
// Ver si saco la función ARP (porque si quiero descargar el APK-se rompe y no termina)
// Ver si es por la función ARP- La función ARP me salve de los AsyncTCP rx timeout
// y ack timeouts. Es casi indispensable!
// Ver si la descarga del APK siempre falla o fue solo esa pasada
// UFFF. Con la cachetada de SD y ARP se arragle casi por completo
// la navegación y servida de paginas. Solo se chotea el download APK
// Puedo espaciar un poco mas el ARP para que si el download cae entre
// dos pasada, pueda funcionar. Con 20 segundos, esta casi justito
// Pongo un minuto; ver si en el uso normal, implica que si "se cuelga"
// habrá que esperar al menos eso pa que responda again.
// Creo que servir / e index.html a LA VEZ HACIA CAGADAS!
// Ver si NO servir Favicon ICO (ponerlo inline, de última)
// Porque se puede estar llamando de adentro del otro callback!
// Ver si ese anidamiento me estaba jodiendo. (casi)Siempre que hago un back
// se chotea
// ....a veces funciona flama, a veces se chotea y nunca vuelve...no se que pensar
// quizá async no está tan bien escrita y H4 tiene razón.
// Con los "parches" puede andar un rato. Y enviando con el chunk manual parece funcionar MUCHISIMO MEJOR!
// Creo que lo dejaré con esa función y al joraca!
// Quizás los delays de los printfs¿?
// "Cuando se pone lento", es cuando deja de funcionar (veo la velocidad de los chunks)
// El index (o cualquier otra página) que quiera servir y "ver"
// lo que tarda puedo servirlo con el chunked manual y las lineas de depuración
// Lo de tamaño chiquito siempre funca. Comprimir todo (de paso)
*/
/*
// 15/07/2023 hoja de ruta: ver de cerca y considerar
// https://github.com/philbowles/h4plugins
// https://www.youtube.com/watch?v=O2W8uyC-Gio&ab_channel=H4Plugins
// H4 parece saber lo que dice! Creo que es por lo que he pasado
// Cuando quede sin responder. Stop en el web server (porque no hay descriptors de sd)
// Reload. y gralmente. agarra viaje!.
// Necesito AL MENOS 2 descriptors en la SD-> cuando mandan a leer, para poder imprimir
// en canvas físico y en la respuesta a la puta app web
// (Ya se por que era tan crudo el ejemplo primigenio y la concha que me parió)
// No quiere funcar con 2!!!!!!
// Hacer nueva lógica que "espere" a que haya descriptores de fs para utilizar!
// Done! casi que funciona. A veces se cuelga; hay que hacer stop en el buiscador y reload
// pero casi que coopera
// 15/07/2023 volvi a servir LittleFs por un lado y de a un solo file en SD
// y se rompió a la primera. Y mucho mas frecuentemente!
// Todo de la SD!!
// Creo que me tomaré el laburo de volcar a la SD todo y a la M. Ver si puede
// gz para reducir tamaños y al diablo
// OJO: cambio tambien el partitions para hacer particion spiffs(littlefs)
// Si no uso spi, la hago nvs (quizá eso ayuda)
// Pero de una buena vez: ABANDONO EL USO DEL LITTLEFS
// Guga del futuro: "te la diste mucho contra esto. No vuelvas a romper los huevos"
// Bancamos la SD. Funciona mucho mejor. Y seguro me dejará crecer el programa del futuro
// (gifs en el horizonte)
// RECORDAR QUE AL CAMBIAR INDEX U OTRA COSA DEL FS DEBO SUBIR A LA SD!
// 15/07/2023 Creo que el problema es "ir quedandose sin memoria"
// El littleFs termina por dejar de cooperar completamente
// Voy a ver de servir todo desdee la SD, abrir mas files
// y NO inicializar spiffs. Si con eso coopera, emprolijar tantito
// poner algunos cartelitos de save ok/not ok-medio pijazo porque guardo en diferido
// Si quiero abrir mas de 2 files al FS de la SD se rompe todo como el carajo
// Con uno solo file abierto; funciona las mas de las veces y el server se cuelga menos
// Ver en el js que cuando se rompe uncaught in promise
// ya no lee mas files (en load) (si de 16; ya no mas de 32 y 64)
// La rutina forceARP parece traer a la vida esta mierda!!!!!
// Magia negra. Cuando se cuelga el buscador pidiendo index o algo
// el fs falla por falta de descriptores; pero cancelando y haciendo
// refresh, puede volver a la vida. No sé; pero es maravilloso!
// Cuesta romperlo; a vece sno anda de una, pero un refresh lo puede
// traer a la vida. Me banco esos glitches!
// Cuando queda unresponsive; hacer STOP a la carga de la pagina y refresh!
// Eso suele hacerlo cooperar casi todas las veces
// Ver de dejarlo an AP (todas las pruebas fueron con STA)
// Y cerrar versión cero. 
// Casi siempre se rompe al volver del converter o al leer un file de 32 o 64
// Ver si con esto mismo y LittleFS funca lo mismo. Es más cómodo tener
// index y demas en data de littleFS
// Algunos cuelgues ocurren. Que se le va a hacer. 
// 12/07/2023 puteando MUCHO con la página html para que funcione lindo!
// Ya tengo cositas lindas como redibujar en app web al leer un file
// Pido cositas con fetch y timeout; que funcionan mucho mejor que xmlhhtp
// Conversor de imagenes, descarga del APK como adjunto..Cositas ricas.
// Hacer que por ws me deje el último dibujo convertido en el canvas digital
// Solo por tener el websocket por ahí, comienza a funcionar "no tan bien"
// Pierde más solicitudes, se rompe la lectura de load más frecuentemente
// ...así que: a la mierda! Saco el websocket!
// Desde el converter se puede grabar; y al hacer click en volver, se puede releer
// la imagen para seguir editandola; asi que a la mierda!
// Limpiar un poco por favor. Ver los printf que pueden hacer quilombo.
// Usar un rato y ver cuando "se rompe" y hacer algo para traerlo a la vida!
// Se rompe fácil despues de un par de entradas y salidas en la escritura.
// Ver de cerrar bien los files abiertos: entregare names (con posibilidad de chunks)
// con el método server.on tradicional. Ese puede estar jodiendo!
// Tambien los de files normales!

// mucha y buena data en 
// https://gist.github.com/pim-borst/17934bfd4454caea3ba4f74366c2135c
// 
*/
/*
// 09/07/2023 jugando con ws..
// y con fetch de js. 
// Timeoutear bien las cosas java cuando se pierden chunks (y lo hacen)
// Si pongo un delay inline al servir los files grandes; se corrompen muchisimo menos
// Y el fetch funciona mucho mejor que el xmlhttp !!!!!!
// 08/07/2023 Estaria "casi todo" viviendo junto.
// pero ahora quiero que al volver del pixel art converter se mantenga la imagen
// y la fuerce al canvas digital web. ver si por websockets lo consigo
// Me parece que es la forma; porque tengo que guardar en SD, leer y pushearselo
// al web browser sin que este haya hecho una solicitud de loadcanvas
// Ver si poner web sockets en el browser, para escuchar eventos 
// y en el ESP para subirselo; cuando haya terminado de escribir/leer
// OJO: ver si el ws puede mandar chunkeado!
// Es bastante quilombito. Suspendo y me voy a estudiar websockets un rato. 
// Dejo esta versión "casi" lista
// 06/07/2023 Formidablemente, ve queriendo cooperar
// Editando el html del Pixel Art converter, para dejarlo a mi medida
// Le faltan botones para navegar entre paginas (index de dibujo tradicional
// y "converter") Un botón de Save (que puede llamar al mismo método SAVE)
// en la página del converter sería agradable.
// Ponerlos a vivir juntos; asignarlos como AP; poner el led de status
// y hacer el PUTISIMO housing de una vez para poder "cerrarlo"
// Hacerse el tiempo de comentar/subir/agradecer y esas cuestiones
// 04/07/2023 Voy a toquetear Wled pixel Art converter html
// para mandar canvas size en el Json; que solo se puedan ajustar
// los tres tamaños predefinidos del canvas
// y dibujar en mi matriz. Me chupo todo lo que aquella página ya sabe hacer
// Tomar imagen, resizearla, armar los Json en chunks y todo eso
// O sea: robo a mano armada
// Voy a jugar a recibir desde WLED PixelArtConverter
// Por ahora veo de solo recibir los post como los manda.
// Si funca; sirvo el index modificado necesario
// los js y todo eso
// 27/06/2023 Arreglando web app y poniedo tod junto hard/soft
// cuando creo que algo coopera se va todo al carajo!
// Ver si NO SERVIR NI MIERDA LOS fontaweso (el WOFF2 de mierda)
// y bajar íconos en base64 inline y al joraca!
// PONGO TODO EN INDEX: pero lo sirvo gz.
// Si quiero cambiar algo en html, css, js debo volver a comprimir!
// Mientras pruebo; sirvo index.html: al final dejar en gz para que ande mejor
// 24/06/2023 Feliz cumple Tatita!
// Tengo lectura por chunks de names.txt y de los patterns para la web (incluso 64x64)
// La única cagada es que dibujar de 64 en web le demora 13 segundos!!!!!!
// Pero funca.
// Poniendo todo junto croto en el index logramos que funcione mejor
// Si no necesita algunos refresh... App web y BT viven juntas.
// Usan los mismos métodos write (desde ghost) y read
// Me robo unas rutinas para blinkear el led para mostrar el status de BT conectado o no y web app
*/
/*
// 23/06/2023 Mandando chunkeadas las respuestas puedo hacer maravillas y dejar la funcionalidad
// robusta y linda. Ver timeout y excepciones; pero estoy mandando names.txt chunkeado
// y ahora podré mandar canvas de 32x32 y de 64x64 a la web app!!! SIII
// Ver si dejar los scripts en el index todo mcho; porque anda mucho mejor.
// Depurar el método de pintar; porque se recontra cuelga despues de usarlo!!!!
// Ver si hacer una tarea que intente revivir la SD cuando no la encuentra
// Cuidado los "formatos" de gusrdada entre BT app y web!!!!
// Y cuando son de distintos tamaños y van por save ghost
// o por post!!!!
// 22/06/2023 Creo que finalmente lo tengo. El filesystem de la SPI interna LittleFS
// sirve (poquitas cosas y rápido!)
// En la SD solo puedo acceder de a UN FILE A LA VEZ (pero es lo que hago; así que no hay bronca)
// Saqué lo boostrapeado (que era el arreglo en columnas) porque implicaba cargar
// mucho más de lo que se banca (con todo junto)
// Una versión solo online (sin BT) puede tener una WEB MUCHISIMO MAS LINDA!
// Funciona perfecto con: 4 files en LittleFS y 2 files en SD
// Una Web page (el canvas online lindo) y el BT pueden vivir en el mismo
// Programa con partición huge_app.csv (le dejo la Guga ppor si quiero jugar algo más)
// Probar boton, hacer efectos al led de estado y chau (puedo hacer rutina rtos copada mil)
// Ver si entra lo del puto DNS
// ES CRITICO DONDE PONEMOS EL INIT SD_SPI!
// Se cuelga más erráticamente y no manda bien los files al web
// me parece que se queda sin mem en los callbacks
// Quizá deba cambiar el callback de /load: 
// Bajar a un array en memoria y contestar desde ahí. Ver....es lo que hago CONCHA!
// Con 16x16 parece funcionar siempre, con 32x32 a veces cuelga el micro y la respuesta
// al web server NUNCA le llega como para que lo dibuje....
// Una garcha. Parece estar al límite en varios aspectos, así que no podré
// tener todas las funciones que quisiera...
// Carga en el canvas; pero no en la Webapp para seguir editandolo...
// very very sad...
// A menos que chunkee respuestas; o haga otra cosa...
// O que guarde los archivos como Json y los sirva desde la SD
// o alguna otra manganeta; por ahora, omito respuesta a web app del canvas
// para 64 y 32. Los de 16 los dejo porque parecen cooperar muy bien
// para que no se resetee el puto micro, al menos!
// Al no mandar el Json, el canvas web no se acomoda al tamaño y es feo para editar despues
// A menos que en el Json ponga el tamaño y cambie como la web app
// sabe el tamaño (que lo infería del tamaño de archivo)
// Se lo puedo meter en el JSON; pero ni ganas
// Si quiero el puto bluetooth; el uso de la web app se ve disminuído
// Se pueden "gambetear las deficiencias" Pero por ahora, me quedo con mi pequeña
// victoria. Hacer la tarea del led del boton y ya
// Victoria mis huevos: o anda el web o el bt pero no juntos aun!
// hago método para inicializar la SD con numero variable de files; porque en BT SOLO PUEDE VIVIR con 1!
// Así SI puedo hacerlos coexistir. Una web app disminuida, yet usable
// Puedo "encajarle" el cursor y hacerlo aparecer/desaparecer para editar
// tamaños de 32 y 64 "un poquito más amablemente"
// Quizá mañana. Dotar de grises al selector de la app BT
// Versión 0; sin led!
*/
/*
// 21/06/2023
// Ver si servir "todo de una" aunque sea chunkeado si no le da a los buffers
// y/o a la cantidad de punteros que pued tener abiertos
// en la SD! Creo que viene por ahí la mano
// Usar lo mínimo e indispensable
// 20/06/2023 Me parece que el problemon es cuando comencé a servir
// múltiples cosas desde littlefs Y SD.
// Creo que ahí empezó a funcionar como el orto!
// Ver si es así
// Cuando la SD coopera NUNCA funca la puta página web!!!
// Ver!!!Y si sirvo TODO desde ls SD ¡?¡?¡?¡?¡?¡?¡?¡?
// Probar; si total no funciona esta mierda!
// 19/06/2023 Trato de servir el apk desde la SD con StreamFile
// Hacer un index para disparar las apps web o descarga de archivo
// y dejar esta versión como versón "usable" 0
// Intentando servir el apk desde la SD
// En escritorio funciona; pero tarda bastante un huevo
// en celu no lo sé aún
// Creo que voy a romper todo lo bonito de servir muchos archivitos por separado
// voy a poner todos los tyles, scripts y mierdas en un solo puto y gran archivo 
// y a la mierda
// 17/06/2023 Acomodo algunas cosillas de la app android y coordino con programa.
// depurando. me guardo versiones a hoy de la app en el proyecto y me descargo ael apk
// Si solo permito de a UN file en el filesystem de la SD
// y le doy bastante tamaño al nvs partition: recién ahí; puedo hacer andar todo junto
// (Display, SD y Bluetooth por un lado: NO WEB SERVER)
// Un boton seleccionará el modo de operación
// Pero se pudo. Limpiar de mierdas; volver las tareas
// de BT al core (creo que eso NO es necesario)
// Probar lo del boton; emprolijar web pages
// depurar app de BT (terminarla-le faltan algunas cosillas) 
// Y hacer un puto hard para cerrar la version 0
// Usando la app de android aparecen cientos de bugs.
// Ver si agarrar evento de cliene desconectado para reiniciar BT
// porque aunque la app salga limpia, no se puede volver a reconectar!
// Hacer portal web y probar lo del boton (y que no haya roto todo lo otro)
// 16/06/2023 Darle batalla: tiene que andar!
// Y si no quiere cooperar: mandar las funciones de file read/write y demás al otro core!
// A ver si podemos hacer las task en otro core (del BT o del File system?)
// Sabemos que el DMA del display y el filesystem de la SD FUNCIONAN JUNTOS
// Ver si pdemos mudar el Bluetooth al otro core!
// 14/06/2023 y como, por supuesto, no podía ser fácil; al juntar bluetooth y SD(SPI)
// TAMPOCO ANDABA. Tuve que hacer una inicialización de la SD con UN SOLO FILE!
// (tenía 5 por defecto ) igual, solo uso de a uno por vez; y recién ahí me
// funca el BT y puede montar la SD
// Ver porque cambie el raiz de la SD a /sd y ahora no lee los archivos!!!!!!!
// depurar todo junto y LCDSHP
// ver porque joraca no puedo leer files; probar otra vez desde AP
// y acomodar peración desde AP o BT. O mandar todo a la mierda...
// PARECE QUE SOLO DE UN FILE PUEDO ABRIR!
// Limpiar mi cabeza y seguir. Not now. Not here
// https://blog.drorgluska.com/2022/06/esp32-sd-card-optimization.html
// Probando cambiar el partition y otras yerbas. Parece que todo junto NO entra!
// filesystem se come nvs memory y BT el SD card no cooeran; por lo pronto
// si arrancan de BT NO inicializo littlefs(total no tengo nada que servir)
// 12/06/2023 Wifi y BT juntos NO quieren cooperar: hacemos lo más fácil del mundo:
// un botón. Si. Un puto botón. En una posición dispara el BT, en la otra el AP
// con las páginas. Una página que dispare "otras páginas con distintas funciones"
// Hacer que el boton de BT pueda cambiar "on the fly"Guardar algunas cosillas en eeprom
// para hacer funciones automáticas, por ejemplo. Al prender temporizar y entrar a modo
// togglear imágenes automáticamente, o algo así.
// Darle un puto cierre a la versión 0 de firmware
// Hacer el hardware de una vez- conseguir difractor y hacer housing bonito
// (con botoncito, luces, ranura para la SD y esas mierdas)
// Terminar la puta interfaz de Android para el BT joystick
// Ver si podré servir el apk en el ESP con (stream) o que lo descarguen
// de la SD.
// 06/06/2023 haciendo metodos para el control remoto BT. Despues mixturar bien
// Parece que utilizar bluetooth se come la memoria del micro
// Sirviendo el AP NO PUEDO NI AGREGAR LA CLASE BLUETOOTH
// Me parece que quedará trunca la cuestion del Bluetooth o hacer 
// una aplicacion especifica: No guga boludo!
// Usa un csv con file partition para app mas grande!!!!!!
// Igualmente: cuando actvemos el BT el WiFi dejará de cooperar (creo-por compartir antena)
// Hacer un index que permita disparar app canvas web, app web controled movement
// y app BT control. Hacer boton en BT para volver y las cosas que hagan falta
// Probar el csv, hacer caber y seguir desde ahí
// Joya: con default csv=79%, con huge app = 29%
// Meterle fichas!
// 30/05/2023 Tengo dos versiones, casi lindas funcionando. Hacerlas convivir
// desde una sola page Index; y ver cómo resolver si prende como AP o por STA
// Ver si podemos servir un archivo GRANDE. Para servir un posible APK para control por bluetooth
// desde un celu!
// 28/05/2023 
// Bastante bonito. revisar los metodos de lectura escritura!
// Chequear migración a control Bluetooth y servir el APK desde el mismo ESP!
// Ver archivos grandes!
// Hacer convivir versiones y comenzar a disfrutar!
// 27/05/2023 Cambio la forma de dibujar: desde el Web server: PERO, moviendome pixel a pixel
// y dejando "pegado" el pixel en cuestión
// Haciendo versiones 2 de index, function.js y style, porque quizá 
// luego quiera hacerlas coexistir
// Me hago nuevos metodos, post y solicitudes para la "nueva" forma de dibujar
// No voy a heredar pintar y otras cosas
// Por ahora empiezo por moverme; y publicarle a la WEB posición (x,Y o index y color del pixel actual)
// Hacer metodo para ocultar pixeles y demás...
// 26/05/2023 El bueno de ISA Gatica creó un github donde dejó más linda y usable
// la pagina web. Separó html, css y js; utilizó bootstrap para dejar bonito
// y otras yerbas. Trato de usar esas cositas ricas
// Parece que los métodos serveStatic son más rápidos para mandarle al navegador
// Verificar: pero cuando me puse a servir mucho bootstrap y mierdas
// se me empezó a colgar seguido la página. con static va mejor
// pero cuando  estaba todo en un solo index, funcaba SIEMPRE!
// Si no: volver al index grande roñoso con los scripts y styles
// y buscar el método column del bbotsptrap!!!!
// Ver. Coopera: hasta ahí. Pero ya se puede usar en celu
// 22/05/2023 Dejarlo usable desde Celu; hacer que pueda gestionarse "automaticamente"
// como AP o conectandose a una red y ponerlo a rolar.
// Le doy nombre: Lylart. En honor a la musa que me puso a estudiar
// Hagamosle un lindo bootsplash screen; quiza una instrucciones sencillas
// y timeouteemos acciones por defecto ante inacción 
// 21/05/2023 Me rompí los cuernos para hacer un color picker: y ya había uno!
// jajajajajaja que pajero!!!!!!
// 18/05/2023 Lo pongo como AP y le doy nombre por DNS para no tener que poner la IP
// Queda cheto. Si puedo poner un color picker tool para elegir 
// color desde el canvas estaría lindo .
// Acomodando el tamaño de cosillas y pudiendo hacer que el size esté bien en celu
// esta como un lindo beta.
// Poner info de bootsplash screen (y algún easter egg)
// Para usar en PC/Celu más cómodamente, hacer una variable en EEprom que
// le permita bootear como AP o en la red Guga
// Hago version nueva porque quiero el color picker y seguro rompa el index
// 17/05/2023 Me descargo y sirvo font-awesome icons y algunos archivos que necesita
// para que funcione offline como AP
// Consumo todo blanco 1.228A
// Consumo todo negro: 0.142A
// 06/05/2023 Casi lindo. Con 16x16 y 32x32 (se acomoda solito el canvas)
// El Save funciona siempre que no borremos nada. Lo voy a hacer desaparecer
// El puto botón del tamaño del lienzo está feo
// Arreglar los containers para celular y casi que es un lindo beta
// Estudiar el WLED con su JSON polenta y su resizeador de imágenes!
// Para canvas de 64x64, si el get/post no puede alojar todo; puedo hacer
// que el micro se acuerde solito los pixeles, y cuando dan clic a save
// lo guarde desde "su caché". Workaround pa guardar,: no se podrá cargar en el web server
// pero algo es algo
// 05/05/2023 Quiero creer que algo he aprendido este tiempo. Como está de origen el código
// dudo que funcione mucho más alla de 16x16 (quizá 32x32)
// Creo que merece más esfuerzo desasnarme del JSON de WLED que puede recbir un JSON grandote
// en partes; y quizá despues reconvertir el c+odigo del pixel ar, para que entregue lo mismo
// Para dejarlo "semi funcional" sacar el tamaño del canvas del file size
// (o ponerlo en el JSON), iterar escritura y lectura hasta ese tamaño
// y a la raja.:insisto en que no creo que llegue a mas de 32x32 sin "partir"
// el Json....
// Despues de save a file; reload index! así veo los iles recien creados!
// NOP! no funciona así...pide getNames cuando reload el navegador y crea el canvas...
// El programa se acomoda solito el tamaño del canvas usado (en la pantalla LED)
// Hay que hacer que la web también pueda acomodarse ;)....
// 30/04/2023 Parto de ejemplos varios (MatrixPanelDMA + Arduino WebServer PixelArt)
// Y trato de hacer una primera aproximación. Web server embebid que permita dibujar
// en la matriz y refrescarla con métodos de paneles 64x64 en lugar
// de los de FASTLED de tira de leds tipo el 2812...
// primero crudazo, después iré puliendo (ponele)
// Cuidado que al traer las librerías DMS I2S me rompe el pin map y deja de andar todo!
*/

#include <main.h>
#include "../include/FileHandling.cpp"
#include "../include/APServer.cpp"
#include "../include/MatrixFunctions.cpp"
#include "../include/bootsplash.cpp"
#include "../include/BT_Joy_Ctrl.cpp"
#include <../include/blink/BaseBlinker.cpp>


#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

#if !defined(CONFIG_BT_SPP_ENABLED)
#error Serial Bluetooth not available or not enabled. It is only available for the ESP32 chip.
#endif


// Returns state of input pin. Mode of operation: BT or WiFi
// Crudazo, sin antirrebote ni nada. Calculo que no hara falta
// Pero poner un cap por las putas
bool check_input()
{
  return(digitalRead(PIN_INPUT_BT_CONTROL_ENABLE));
}

// Efectos del led de modo de operacion
// BT no conectado = parpadear rápido -.-.-
// BT conectado = parpadear lento -----.-----.
// Web = prendido sólido   

void led_operation_mode()
{
  if(BT_CONTROL_ACTIVE  && !CLIENTE_BT_CONECTADO)
  {
    statusLedSettings.on_ms = 500;
    statusLedSettings.off_ms = 500;
    statusLedSettings.pause_ms = 500;
    statusLedSettings.ending_ms = 500;
    statusLed.setSpeed(statusLedSettings);
    statusLed.pattern(2,true);
  }
  if(BT_CONTROL_ACTIVE  && CLIENTE_BT_CONECTADO)
  {
    statusLedSettings.on_ms = 2500;
    statusLedSettings.off_ms = 800;
    statusLedSettings.pause_ms = 2500;
    statusLedSettings.ending_ms = 1800;
    statusLed.setSpeed(statusLedSettings);
    statusLed.pattern(1,1,true);    
  }
  if(!BT_CONTROL_ACTIVE)
  {
    statusLed.on();
    // statusLed.pattern(3, 5, SPEED_FAST);
  }

}



// Playing
void printDirectory(File dir, int numTabs) {
  while (true) {
    File entry =  dir.openNextFile();
    if (! entry) {
      // no more files
      break;
    }
    for (uint8_t i = 0; i < numTabs; i++) {
      Serial.print('\t');
    }
    Serial.print(entry.name());
    if (entry.isDirectory()) {
      Serial.println("/");
      printDirectory(entry, numTabs + 1);
    } else {
      // files have sizes, directories do not
      Serial.print("\t\t");
      Serial.println(entry.size(), DEC);
    }
    entry.close();
  }
}

void start_server_and_handlers()
{
  register_events();
  handleRoot();
  handleNotFound();
  handlePlain();
  handleMode();
  handleGetNames();
  handleLoad();
  handleSave();
  handleDelete();
  handleChangeCanvas();
  handleAPKDownload();
  handleJsonFromConverter();
  handleUploadPattern();
  server.begin();    
}

// #define DEBUG_WEB 
void setup() 
{
  delay(300);         //Sanity delay 
  
  Serial.begin(115200);
  Serial.println("Hello World!");
  print_heap(0);
  pinMode(PIN_INPUT_BT_CONTROL_ENABLE,INPUT_PULLUP);
  pinMode(PIN_OUTPUT_LED_OPERATION_MODE,OUTPUT);
  // FALLA_SD = init_spi_sd();
  // Hacer algo lindo: como avisar en la pantalla!
  // if(FALLA_SD)
  // {
  //   Serial.println("An Error has occurred while mounting FS");
  //   return;      
  // }

  // Initialize FS - NO MORE FS en mem SPI!!!!!!
  // Se pudre con todo junto!
  // if(!LittleFS.begin(true))
  // A ver si reservendo max open files mas grande
  // if(!LittleFS.begin(false,"/littlefs",8,"spiffs" ))
  // {
  //   Serial.println("An Error has occurred while mounting FS");
  //   return;
  // }

  // Module configuration
  HUB75_I2S_CFG mxconfig
  (
    PANEL_RES_X,   // module width
    PANEL_RES_Y,   // module height
    PANEL_CHAIN    // Chain length
  );

  mxconfig.gpio.e = 17;
  mxconfig.driver = HUB75_I2S_CFG::SHIFTREG;
  mxconfig.latch_blanking = 4;
  mxconfig.i2sspeed = HUB75_I2S_CFG::HZ_10M; //8,10,15 y 20
  // Bajo a 6 bits a ver si ahorra algo de heap

  // Dejando colores de lado para que entre en memoria todo: ver si cambia con el default de 8!
  //mxconfig.setPixelColorDepthBits(6);

  // Display Setup
  dma_display = new MatrixPanel_I2S_DMA(mxconfig);

  dma_display->begin();
  dma_display->setBrightness8(90); //0-255
  dma_display->clearScreen();

  print_heap(1);

// Serial.println("MAX_FDS:"+ String(FD_SETSIZE));  //Era una buena alternativa: pero no resultó!
// Se lo dejo al Guga del futuro


  // delay(100);  //wait BT to be ready
  // FALLA_SD = init_spi_sd(); // THEN initalise SD on SPI. porque si hago al revés: se cuelga y el BT no parte!

  // Según el switch diparamos control por Wifi o por Bluetooth
  // Chequear en el bucle por conexiones para los efectos del led de estado
  // y por si cambian el modo On the fly --> reset cpu y a la mierda!
  BT_CONTROL_ACTIVE = check_input();

  #ifdef DEBUG_WEB
    BT_CONTROL_ACTIVE = false;
  #endif

  if(BT_CONTROL_ACTIVE)
  { 
  //   // Ver si esto es necesario cuando voy de una prendida con una aplicacion a la otra
  //   // WiFi.disconnect(true);
  //   // WiFi.mode(WIFI_OFF);
    print_heap(59);
    SplashScreenBT(65);
    print_heap(60);
    // Crear las task que sean necesarias para que el puto buetooh vaya al otro core
    Serial.println("Modo de control por Bluetooth. Emparejar con LylArt_BT_Control, correr Android App y disfrutar" );
  print_heap(55);
  BT_init_no_RTOS();
    // xTaskCreatePinnedToCore(
    //                     BT_init,    /* função que implementa a tarefa */
    //                     "BT_Init",  /* nome da tarefa */
    //                     10000,      /* número de palavras a serem alocadas para uso com a pilha da tarefa */
    //                     NULL,       /* parâmetro de entrada para a tarefa (pode ser NULL) */
    //                     1,          /* prioridade da tarefa (0 a N) */
    //                     NULL,       /* referência para a tarefa (pode ser NULL) */
    //                     taskCoreZero);         /* Núcleo que executará a tarefa */
                        
print_heap(56);
    delay(5999);    //check!""
    // delay(4000); //tempo para a tarea iniciar
    // print_heap(57);
// Creo que al crecer el programa tengo problemas con el tamaño de pila que le deje
// con 2000 se cuelga y resetea permanentemente,
// con 3000 muestra el nombre, permite vincular, pero ya no me deja conectarme
// con 4000 y pa´rriba NO ME DEJA CONECTARME
// 
    // print_heap(54);
    FIND_CURSOR = true;
    canvas_size = 16;
    color_to_deposit = 0;
    CLIENTE_BT_CONECTADO = false;
    Serial.println("Start Fucking SD filesystem");
    FALLA_SD = init_spi_sd(1);
    if(!FALLA_SD)
    {
      read_names_to_vector();
    }
  // //ver si hacer un método para cerrar SD(spi) e invocar aquí para liberar todo el heap posible"
  // // despoues de baner hecho el dir solo necesito Un descriptor de archivos para leer o escribir

  //   //free_SD_descriptors(;)
    // SD.end();
    // FALLA_SD = init_spi_sd(1);
    // if(!FALLA_SD)
    // {
    //   Serial.println("Close and reopen with ONE descriptor");
    // }
    // else
    // {
    //   Serial.println("Close and reopen FAILED");
    // }

  }
  else
  {
    print_heap(2);
    Serial.println("Modo de control por Wifi. Conectarse a LylaArtToy y navegar a 192.168.2.1 ");
    SplashScreenWeb(0);  //ver para que era el int de entrada!
    // WiFi.mode(WIFI_STA);
    // WiFi.begin(ssid,password);

    WiFi.mode(WIFI_MODE_AP);
    IPAddress LocalIP = apIP;   // IPAddress;
    // IPAddress GatewayIP = WiFi.gatewayIP();
    WiFi.softAPConfig(LocalIP, IPAddress(0, 0, 0, 0), IPAddress(255, 255, 255, 0)); // IPAddress(192,168,1,1);
    WiFi.softAP(APssid, APpassword);  
    LocalIP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(LocalIP);

    print_heap(3);
    //WiFi.begin(APSSID,APPSK);
    // AP y station (en red guga) siempre. mientras depuro es mejor usar la PC
    // y no tego dongle Wifi 

    bool keep_trying_con = false;  //Solo tiene sentido si nos conectamos auna red. cuando somos AP no
      //dejo como AP, pongo a FALSE; pero si llego a volver a usar como STATION pongo true y ya
    int retry_cons = 0;
    while(keep_trying_con)
    {
      if (WiFi.status() == WL_CONNECTED)
      {
          // Check for the connection

          // Serial.println("Sta IP address:" + WiFi.localIP());
          keep_trying_con = false;
      }
      else
      {
        Serial.println(".");
        retry_cons++;
        delay(1000);
      }
      if(retry_cons >= 10)
      {
        keep_trying_con = false;
      }
    }

    FALLA_SD = init_spi_sd(3);  //empiezo ambicioso con 10-server no puede iniciar
                                //con 8-server failed to start
                                //con 6-si pudo y no habia cerrado root.
                                // con 6, cerrando root no sirve un joraca!
                                // con 3 y sirviendo chunkeado favicon SI
                                // creo que el tema va con los servestatic! VER:!!!!
                                // server.on (favicon.ico solito) funciona (entra 2 veces a mother!)
                                // probar servir sin todo el programon y ver cómo anda y despues evaluar
                                // Con 2 puede servir al menos una vez!
                                // Con 1 se queda sin descriptors a veces; pero
                                // cuelga MENOS el server! o Al menos, cuando falla y hacemos refresh
                                // vuelve a la vida!
    if(!FALLA_SD)
    {
      listDir(SD,"/img",0);         //para llenar el vector v una vez al menos
      /*       File root = SD.open("/");
      printDirectory(root, 0);
      root.close(); */
    }
    else
    {
      //deberia hacer un return: porque no se podría hacer nada sin file system!!!
      Serial.println("No se pudo inicializar SD");
      //Avisar en el canvas!!!
    }
    print_heap(5);
    start_server_and_handlers();
    print_heap(6);
  }

  //debug sdcard and dma of matrix
  #ifdef DEBUG_WEB
  BT_CONTROL_ACTIVE = false;
  web_page_selected = 1;
  #endif
  // live=false;
}


// Si existe el nombre de archivo lo dibujo y devuelvo 0
// si no existe devuelvo 1 (para que la app de BT pueda dar la vuelta)
bool prepare_read_and_draw(int Index)
{
  String name_to_read;
  name_to_read = v[Index];  //asegurarse de hacer al menos una vez el vector v para el BT
  // SD.end();
  // init_spi_sd(1);


  if (!(SD.exists("/img/" + name_to_read))) 
  {      
    return(1);    //file does not exist
  }  
  File loadPat = SD.open("/img/" + name_to_read, FILE_READ);
  size_t estimated_size = loadPat.size();
  // int bucle_read_file2 = 255;
  canvas_size = 16;       //default, check further to see if not

  if(estimated_size > 2304) //if 32x32 canvas: file size will be greater than..
  {
    // bucle_read_file2 = 1023;    
    canvas_size = 32; 
  }
  //check file size of 64x64 fie and make some answer for web server
  if(estimated_size > 20000)
  {
    // bucle_read_file2 = 4096;    
    canvas_size = 64;   
  }  
  // Depurar operación con la pantalla
  loadPat.close();
  ruta = "/img/";
  name_to_load.clear();
  name_to_load = v[Index]; 
  ruta += name_to_load;
  readFile(ruta, pattern);
  showPattern(estimated_size);
  // loadPat.close();
  // llevar cursor a (0,0)-si cambian de tamaño y el cursor estaba fuera de los límites del nuevo
  // canvas "se pierde"
  // Además, cuando leen un file cargar el ghost con el dibujo; porque si quieren manipular y chupar color
  // o modificar algo y guardarlo con otro nombre, está todo roto
  // la pantalla muestra una cosa, pero el ghost (desde donde graba) tiene otra!
  // for(int itera=0; itera < NUM_LEDS; itera++)
  // {
  //   large_canvas_ghost[itera] = pattern[itera];
  // }
  actualIndex = 0;
  return(0);
}


// Función para pushear nuevo nombre en el vector y para subir a names.txt
// para que no tengan que pasar por usar la app wifi para crear names de vuelta
// y puedan aparecer los dibujos "nuevos" hechos con la app bluetooth
// Entuerto de no tener descriptores disponibles!
#define VERBOSE_PUSH_TO_VECTOR
void push_name_to_vector(void)
{
  #ifdef VERBOSE_PUSH_TO_VECTOR
    Serial.println("Push to vector and file namefile:" +String(name_to_deferred)); 
  #endif
  name_to_deferred += ".txt";                //le agrego extensión
  v.push_back(name_to_deferred.c_str());
  files_found++;
  // Ver si appendea bien!
  File names = SD.open("/names.txt", FILE_APPEND);
  if(names)
  {
    names.println(name_to_deferred.c_str());
  }
  names.close();
}

// Hago funciones para BT, que siempre escriben desde ghost
void save_16()
{
  if(SAVE_16_FILE)
  {
    Serial.println("16x16 save fired!");
    SAVE_16_FILE = false;
    long millis_enter = millis();
    File newFile = SD.open("/img/" + String(name_to_deferred) + ".txt", FILE_WRITE);
    for (int j= 0 ; j <= 255; j++)
    {
      newFile.print("0x" );    //manteniendo el formato del ejemplo de partida
      newFile.printf("%06lx\n", large_canvas_ghost[j] , 16 );
      // Serial.println(j);   //si quiero ver jota creciendo en consola... jajaja
    }       
    newFile.close(); 
    long millis_leave = millis();
    Serial.println("Task Save 16x16 took:" + String (millis_leave-millis_enter) + "ms"); 
    // En modo BT solo puedo tener UN descriptor al FS, así que no actualizo names.txt
    if(BT_CONTROL_ACTIVE == false)
    {
      SKIP_NAMES_CREATION = false;
    }
    else
    {
      push_name_to_vector();
    }
  }  
}

void save_32()
{
  if(SAVE_32_FILE)
  {
    Serial.println("32x32 save fired!");
    SAVE_32_FILE = false;
    long millis_enter = millis();
    File newFile = SD.open("/img/" + String(name_to_deferred) + ".txt", FILE_WRITE);
    for (int j= 0 ; j <= 1023; j++)
    {
      newFile.print("0x" );    //manteniendo el formato del ejemplo de partida
      newFile.printf("%06lx\n", large_canvas_ghost[j] , 16 );
      // Serial.println(j);   //si quiero ver jota creciendo en consola... jajaja
    }       
    newFile.close(); 
    long millis_leave = millis();
    Serial.println("Task Save 32x32 took:" + String (millis_leave-millis_enter) + "ms"); 
    // En modo BT solo puedo tener UN descriptor al FS, así que no actualizo names.txt
    if(BT_CONTROL_ACTIVE == false)
    {    
      SKIP_NAMES_CREATION = false;
    }
    else
    {
      push_name_to_vector();
    }    
  }   
}

// Funcion para evitar cuelgues de WDT en async tcp cuando guardan CANVAS de 64x64
// Poner numero de archivo (nombre de archivo) en variable global "name_to_deferred"
void save_large()
{
  uint16_t color_16_complete; 
  if(SAVE_LARGE_FILE)
  {
    Serial.println("Large save fired!");
    long millis_enter = millis();
    SAVE_LARGE_FILE = false;
    File newFile = SD.open("/img/" + String(name_to_deferred) + ".txt", FILE_WRITE);
    for (int j= 0 ; j <= 4095; j++)
    {
      // Serial.println(large_canvas_ghost[j] , 16);
      newFile.print("0x" );    //manteniendo el formato del ejemplo de partida
      newFile.printf("%06lx\n", large_canvas_ghost[j] , 16 );
    }       
    newFile.close(); 
    long millis_leave = millis();
    Serial.println("Task Save Large took:" + String (millis_leave-millis_enter) + "ms"); 
    // En modo BT solo puedo tener UN descriptor al FS, así que no actualizo names.txt
    if(BT_CONTROL_ACTIVE == false)
    {    
      SKIP_NAMES_CREATION = false; 
    }
    else
    {
      push_name_to_vector();
    }
  }
  return;
}

// si estaba en web app y pasan a BTapp- reseteo y viceversa
void verificar_modo_uso()
{
  if(BT_CONTROL_ACTIVE && !check_input())  
  {
    Serial.println("De modo Bluetooth a modo Web. Reset");
    Serial.flush();
    esp_restart();
  }
  if(!BT_CONTROL_ACTIVE && check_input())
  {
    Serial.println("De modo Web a modo Bluetooth. Reset");
    Serial.flush();
    esp_restart();    
  }
}

// Para no cargar el callback de la web
// Verifico además que la respuesta async, haya soltado
// el recurso de la SD (tengo un solo filñe para usar a la vez)
void print_deferred()
{
  if(PRINT_SCREEN_DIFERIDO)
  {
    int can_you_print=0;
    // check for fs availability!
      Serial.println("Print de canvas diferido al método web load");
      can_you_print = readFile(ruta, pattern);
      if(can_you_print != 0)
      {
        PRINT_SCREEN_DIFERIDO = false;
        extinguir_solicitud_load = 0;
        showPattern(estimated_size_for_deferred_print);
      }
      else
      {
        extinguir_solicitud_load++;
        Serial.println("No pudo abrir el file, reintentar");
      }
      // con poquitos es suficiente
      if(extinguir_solicitud_load >= 5)  //ver cuantas veces reintentar!
      {
        PRINT_SCREEN_DIFERIDO = false;
        extinguir_solicitud_load = 0;
        Serial.println("Extingo solicitud de apertura de archivo");
      }
  }
}

// llenar en pattern el pixel del tamaño adecuado!!!
void fill_pixel(int x,int y,long referenceColor)
{
    uint16_t xy_to_index;
    if(x>=0 && x<=(canvas_size-1) && y>=0 && y <=(canvas_size-1) && max_iterations>0)
    {
      max_iterations--;
      xy_to_index = y*canvas_size+x;
      Serial.println("index:"+String(xy_to_index));
      if(pattern[xy_to_index] == referenceColor)
      {
        if(canvas_size == 32)
        {
         //pattern[xy_to_index] = fill_color_current_color;  // marcar como ya visitado
        }
        else if(canvas_size == 16)
        {

        }
        else //64*64-pixel by pixel
        {
          //probar si anda en 64x64 y extrapolar!
          // si no:cambiar de óptica!!!
          pattern[xy_to_index] = fill_color_current_color;  // marcar como ya visitado
        }          
        draw(xy_to_index,fill_color_current_color);
        fill_pixel(x+1,y,referenceColor);
        fill_pixel(x-1,y,referenceColor);
        
        fill_pixel(x,y+1,referenceColor);
        fill_pixel(x,y-1,referenceColor);
        
      }
    }
}

void fill_deferred()
{
  if(FILL_DEFERRED == true)
  {
    FILL_DEFERRED = false;
    //max_iterations = 1024;
    Serial.println("Exec. fill deferred!");
    fill_pixel(fill_x,fill_y,fill_color_reference_color);
  }

}
// Esto parece traer a la vida la puta cosa cuando ocurren asyntcp
// errors. pcb_null, ack timeout y esas cosas.
// No será lo mas bonito del mundo, pero parece funcionar!
extern "C" {
   char *netif_list;
   uint8_t etharp_request(char *, char *);
 }
long last_clean;
void forceARP()
{
  char *netif = netif_list;
  if(millis()-last_clean > 35000)
  {
  Serial.println("Limpiando con la manganeta a ver si asynctcp ack error se recupera"); 
    
    while(netif)
    {
      Serial.println("Limpiando");  //a ver si lo hace!!!!¡?¡?¡?¡?
      netif = *((char **) netif); 
    }
  last_clean = millis();

  //probando cosas con rudeza! reseteo y reinicio server cada n segundos
  // No trae un carajo a la vida. Casi siempre despues de un back de converter, se pincha!
    // server.reset();
    // start_server_and_handlers();
    //no ayuda...
  }
}

// Print de heap memory para depurar. Solo si lo permite el define
//#define PRINT_HEAP_MES
void print_heap(int k)
{
  #ifdef PRINT_HEAP_MES
    Serial.println("");
    Serial.print("HEAP "+ String(k) + ": ");
    Serial.println(ESP.getFreeHeap());
    Serial.println("");
  #endif
}

// Si vemos que no hacen nada desde el arranque, despues de algún tiempo
// poner a scrollear los dibujos
// "Hacer algo" es conectarse por BT, o pedir una vez la página / (index)
#define INACTIVITY_PERIOD 180000 //tres minutos de inactividad?
void check_user_incativity()
{
  if(!ACTIVITY_BIT)
  {
    if(millis() - millis_inactivity > INACTIVITY_PERIOD)
    {
      Serial.println("Inactivity period of 3 mins. Loop saved images automatically");
      live = false;         //empieza a escrollear
      FIND_CURSOR = false;  //si está en modo BT que esconda el cursor
      millis_inactivity = millis();
    }
  }
}

uint8_t wheelval = 0;
size_t size_of_file = 0;
long test;
long relax_vato;
// Por ahora, dibujando en AP con canvas reticulado O por BT y cursor parpadeante
void loop() 
{

  // ws_push_canvas();
  // ws.cleanupClients();

  // Efectos del led para indicar giladas
  led_operation_mode();
  statusLed.update();

  #ifndef DEBUG_WEB
  verificar_modo_uso();
  #endif

  if(BT_CONTROL_ACTIVE)
  {
    BT_loop();
    if(millis() - relax_vato >= 100)
    {
    blink_cursor(actualIndex,color_to_deposit); //Para index2 tambien necesito estos métodos! Ver de invocarlos apropiadamente si están en index 2
    check_cursor_movements();   
    relax_vato = millis() ;  
    }
  }
  else
  {
    // forceARP(); //ver si el force AP limpia y mantine con vida
    // Si estámn en control web, de cursor, llamo a los métodos necesarios
    if( web_page_selected == 2)
    {
      blink_cursor(actualIndex,color_to_deposit); //Para index2 tambien necesito estos métodos! Ver de invocarlos apropiadamente si están en index 2
      check_cursor_movements();    
    }
    // dnsServer.processNextRequest(); //si no uso DNS NO PONER PORQUE MATA TODO!!!!!!
  }

  // Si disparan guardar imagen lo hago en el main. Hay variables globales por todos lados
  // para coordinar las tareas. Si lo pongo en los callbacks se cuelga!
  // (el de 64x64; los otros no, pero por las dudas) Además es más fácil para usar desde
  // web o desde BT. Los web 16 y 32 guardan en el mismo callback que recibe desde la webapp
  //
  save_large();
  save_16();
  save_32();
  print_deferred();
  fill_deferred();
  check_user_incativity();

  currentMillis = millis();
  if (currentMillis - prevMillis >= interval )
  { 
    prevMillis = millis(); 
    // Hacer algun dibujito lindo de NO hay mem SD (ponerlo en filesystem y mostrar)
    // A modo de error se puede loopear texto
    if( FALLA_SD )
    {
      Serial.println("Falla SD reintentar INIT de SD"); 
      SD.end();
      delay(50);
      FALLA_SD = init_spi_sd(3);  //ver si uno, dos  o tres
    }
    else if(live == false)
    {
      // Si no está en modo live, escroleo por los dibujos almacenados en la tarjeta SD
      // cuando loopee debo saber el file size para hacer el canvas del tamaño adecuado      
      // Si sacan la tarjeta en la mitad de la maniobra (o sea que ya habia iniciado)
      // Para que se de cuenta y pueda re-inicializarla
      if(!FALLA_SD && !(SD.exists("/names.txt")))  
      {
        Serial.println("La SD anduvo, pero ya no más-volver a avisar");
        falla_lectura_sd++;
        if(falla_lectura_sd >= 3 )
        {
          FALLA_SD = true;
          falla_lectura_sd = 0;
        }
      }
      //if the mode is looping through the saved pictures and its time for a new one
      bool image_error = prepare_read_and_draw(loopIndex);
      if(image_error)
      {
        loopIndex = 0;
      }
      else
      {
        loopIndex++;
        if(loopIndex>=v.size())
        {
          loopIndex = 0;
          Serial.println("Todas las imagenes se han reproducido.Vuelvo a empezar");
        }
      }
    }
  }
  
  //scroll_texto();
}