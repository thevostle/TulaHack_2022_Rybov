##Поднятие бэкенда

Наш способ - открытие на локальной машине портов `:5173` и `:8080` при помощи `ngrok`.
Порт `5173` используется для обращения к фронтенду на Vite, а `:8080` для передачи HTTP-запросов на бэк.
В таком случае доменом сайта будет адрес ngrok, выданный на порт `5173`, а с фронтэнда запросы будут передаваться
на домен, выданный на порт `8080`.

##API

###Note: Вместо ngrok.example.adress.io должен быть фронтенд-адрес, выданный `ngrok` при прокидывании портов.

Register user
```
URL: http://ngrok.example.adress.io/user/register
POST: login:string, password:integer
```

Authentification
```
URL: http://ngrok.example.adress.io/user/login
POST: login:string, password:integer
```