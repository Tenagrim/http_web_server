________________________________________________________________

#### <p align=center>HTTP web server</p> ####
________________________________________________________________

<details>
<summary>Описание задачи</summary>

________________________________________________________________

<p>Написать HTTP сервер по стандарту RFC 7230-7235 на С++, реализовав:</p>
<p>1. Соединение клиент-сервер;</p>
<p>2. Запуск двух и более серверов;</p>
<p>3. Методы GET, POST, PUT, HEAD;</p>
<p>4. Коды состояний, обработка ошибок;</p>
<p>5. Заголовки запроса/ответа</p>
<p>6. Принятие chunked запроса</p>
<p>7. Автоиндексация</p>
<p>8. Поддержку CGI скриптов</p>
<p>9. Авторизацию клиентов</p>
<p>10. Настраиваемый конфигурационный файл</p>
<p>За основу было взято оригинальное поведение <b>Nginx</b>.</p>

________________________________________________________________
</details>

<details>
<summary>Настройка конфигурационного файла</summary>

________________________________________________________________


<p><b>В основной структуре сервера мы можем указать:</b></p>
<p>1. listen - порты сервера;</p>
<p><sub>Пример: "listen 80 81"</sub></p>
<p>2. server_name - наименование сервера;</p>
<p><sub>Пример: "server_name example.com"</sub></p>
<p>3. root - корневая директория;</p>
<p><sub>Пример: "root /Users/pcatrina/Desktop/workspace/webserv/webserv/resources"</sub></p>
<p>4. error_page - путь до файла, который будет отображаться вместо страницы ошибки;</p>
<p><sub>Пример: "error_page 405 /40x.html"</sub></p>
<p>5. autoindex - on/off автоиндексацию;</p>
<p><sub>Пример: "autoindex off"</sub></p>

________________________________________________________________

<p><b>В структуре location мы можем указать:</b></p>
<p>1. root - корневая директория;</p>
<p><sub>Пример: "root /Users/pcatrina/Desktop/workspace/webserv/webserv/resources/42_test"</sub></p>
<p>2. index - отображаемая страница;</p>
<p><sub>Пример: "index index.html"</sub></p>
<p>3. limit_except - разрешенные методы у location;</p>
<p><sub>Пример: "limit_except POST GET"</sub></p>
<p>4. limit_client_body_size - лимит на посылаемое body от клиента;</p>
<p><sub>Пример: "limit_client_body_size 10"</sub></p>
<p>5. fastcgi_pass - путь до интерпретатора CGI скриптов;</p>
<p><sub>Пример: "fastcgi_pass /Users/pcatrina/Desktop/workspace/webserv/webserv/resources/42_test/cgi_tester;"</sub></p>
<p>6. auth_basic - заголовок авторизации;</p>
<p><sub>Пример: "auth_basic ruslan:ruslan"</sub></p>
<p>Авторизация в данном проекте сделана посредством Basic-авторизации. Логин:пароль авторизованных клиентов хранится в файле.</p>
<p>7. client_max_body_size - ограничение на максимальный размер тела запроса;</p>
<p><sub>Пример: "client_max_body_size 100"</sub></p>

________________________________________________________________

<p><sub>(!) Программа принимает конфигурационный файл в качестве аргумента. (!)</sub></p>
</details>

<details>
<summary>Ссылки</summary>
<p></p>
<p><a href="https://tools.ietf.org/html/rfc7230">RFC 7230</a></p>
<p><a href="http://www.stolyarov.info/books/programming_intro/vol3">А. В. Столяров "Системы и сети"</a></p>
<p><a href="https://developer.mozilla.org/ru/docs/Web/HTTP/Headers">HTTP заголовки</a></p>
<p><a href="https://developer.mozilla.org/ru/docs/Web/HTTP/Status">HTTP коды состояний</a></p>
<p><a href="https://www.notion.so/Webserv-04aced0ffcb54259a2d6a0d32da25d88">Заметки по проекту</a></p>
</details>


Проект написан по стандарту С++ 98.





