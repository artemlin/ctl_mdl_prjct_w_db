# ctl_mdl_prjct_w_db

Проект: управляемая при помощи базы данных трехмерная модель в среде 3D-движка Unigine.

- Проект заключается в разработке системы, позволяющей управлять при помощи базы данных трёхмерной моделью существа, находящегося в среде Unigine. В качестве базы данных используется база данных MySQL, так как это довольно распространённый вид баз данных, к которому можно обращаться при помощи языка программирования C++. Разработка производилась с помощью C++, SDK Unigine и API MySQL для C++, которое было подключено при помощи библиотек (MySQL C++ Connector). В качестве среды разработки использовался Visual Studio 2022. Управление базой данных осуществляется при помощи MySQL Workbench.   


- В рамках проекта стояла задача реализовать возможность удалённого управления трёхмерной моделью, находящейся в виртуальной среде, а также получение обратной связи  от неё. В данном случае необходимо было реализовать возможность передачи информации, включающей положение конечностей существа - угол по вертикали и по горизонтали, в общей сложности шесть конечностей, каждая из которых принимает два параметра. То есть всего нужно было отправлять 12 параметров из базы данных, которые задаёт пользователь. В то же время модель, помимо получения информации, должна была записывать в ту же базу данных информацию о своём положении (в данном случае это координаты туловища) с некоторым временным промежутком (например, каждые 5 секунд).  

- Принцип работы системы:
При инициализации программы создаётся трёхмерная модель, состоящая из параллелепипедов и шарниров. Всего шесть конечностей, каждая из которых может перемещаться по вертикали и горизонтали. Положение конечностей задаётся конкретным углом. При инициализации - это интервал от -90 до 90. Также при инициализации программа подключается к базе данных по адресу сервера, логину и паролю. После успешного подключения происходит инициализации двух таблиц - setPosition и bodyPosition. Если таблицы уже существовали, то они перезаписываются. После создания таблиц пользователь может добавлять по одной строке в таблицу setPosition при помощи приложения MySQL Workbench. После введения значений при первой инициализации те ячейки, где остались значения null, указываются как нули. При дальнейшей инициализации модель запоминает предыдущее положение и меняет положение только тех конечностей, где пользователь указал значение. Сама модель в то же время каждые 5 секунд отправляет информацию о своём положении в среде, указывая X, Y, Z координаты туловища в пространстве.

Для сборки проекта используются
- библиотеки Unigine
- библиотека MySQL для C++ 
